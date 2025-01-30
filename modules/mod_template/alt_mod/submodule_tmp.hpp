#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <Arduino.h>
#include <ArduinoJson.h>
#include "datastructures.h"

// enum LedMode {
// Off = 0, // LED is always off
// Sync, // LED is equivalent to the state of the relay
// Invert, // LED is inverted to the state of the relay
// Bicolour // LED alternates between red and green for off and on
// };

class Socket {
private:
  const int number;  // to differentiate between objects
  bool power;        // state of relay
  const int relay;   // pin of controled relay
  const int led;     // pin of indicator LED
  LedMode ledModeVal;

  const int button;  // pin of button
  bool buttonState;  // remember state to detect changes

  const int ammeter;        // pin of ammeter
  unsigned int interval;    // Time interval for updating in seconds
  unsigned long timestamp;  // last time the meter was read

  bool hasChanges;  // are there unsent changes?

public:
  Socket(int number, int relayPin, int buttonPin, int ledPin, int ammeterPin);

  void setPower(bool newPower);
  void togglePower();
  void setLedMode(LedMode newMode);
  void setLedMode(const String& mode);
  void setInterval(int newInterval);

  int getNumber() const;
  int getMAmp() const;
  bool getButton() const;

  bool hasUpdate();
  String getUpdate();
  void setValues(String newValues);
};

#endif  // SOCKET_HPP
