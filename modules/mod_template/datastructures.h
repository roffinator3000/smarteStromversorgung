
#ifndef STRUCTS_HPP
#define STRUCTS_HPP

struct Handshake {
  // version 1
  uint16_t id;        // unique module ID
  String type;        // name of modul type
  uint8_t consuming;  // how much energy can be drawn by this module
  bool closed;        // is the modules connection closed
};

enum LedMode : uint8_t {
  Off = 0,  // LED is always off
  Sync,     // LED is equivalent to the state of the relay
  Invert,   // LED is inverted to the state of the relay
  Bicolor   // LED alternates between red and green for off and on
};


enum SystemMode : uint8_t {
  Starting = 0,  // head not yet ready
  Initialising,  // initialising system
  Run,           // system in normal opation
  Error          // system in safety mode
};


union Status {
  bool closed;       // modules transmit whether their port is closed
  SystemMode modeI;  // head defines the system's mode
};

struct Message {
  uint8_t submodule;  // ID of submodule
  String payload;     // JSON as String
  Status statusI;     // mode from head, closed from module

  Message(uint8_t sub, const String& pl, SystemMode mode)
    : submodule(sub), payload({ pl }), statusI({ mode }) {}
  Message(uint8_t sub, const String& pl, bool closed)
    : submodule(sub), payload({ pl }), statusI({ closed }) {}
};

#endif  // STRUCTS_HPP
