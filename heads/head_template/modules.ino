
#include <BasicLinkedList.h>

/*
// version 1
struct Handshake {
  uint8_t id;         // unique module ID
  String type;        // name of modul type
  uint8_t devices;    // number of subdevices
  uint8_t consuming;  // how much energy can be drawn by this module
  bool closed;        // is the modules connection closed
};
enum Mode : uint8_t {
  Starting = 0,  // head not yet ready
  Initialising,  // initialising system
  Run,           // system in normal opation
  Error          // system in safety mode
};*/

class Module {
public:
  uint8_t address;  // I2C address
  uint8_t id;       // unique module ID
  String type;      // name of module type
  uint8_t devices;  // number of subdevices

  Module(const uint8_t addr, const Handshake& handshake) {
    address = addr;
    id = handshake.id;
    type = handshake.type;
    devices = handshake.devices;
  }
};

SystemMode systemMode;

LinkedList<Module> moduleList;

// how much energy is allowed to be consumed through modules and what is currently possible
uint8_t consumptionSum;
const uint8_t consumptionMax = 10;


void moduleSetup() {
  setupSafetyButton(A0);
  setupSafetySwitch(A1);

  setSystemMode(Initialising);
  scanForModules();
}


void setSystemMode(SystemMode newMode) {
  systemMode = newMode;

  switch (systemMode) {
    case Initialising:
      break;
    case Error:
      setSafetySwitchState(false);
      sendErrorToModules();
      break;
    case Run:
      setSafetySwitchState(true);
  }
}

void moduleLoop() {
  checkSafetyButton();
  // ask modules for updates
}

void sendErrorToModules() {}

void scanForModules() {
  bool modulesClosed = true;

  for (byte address = 10; address < 128; ++address) {
    // i2c_scanner uses the return value of the Wire.endTransmission to see if a device did acknowledge to the address
    Wire.beginTransmission(address);
    byte retVal = Wire.endTransmission();

    if (retVal == 0) {
      Serial.print("I2C device found at address 0x");
      Serial.println(address, HEX);

      Wire.beginTransmission(address);
      i2cSimpleWrite(Message(0, "", (Initialising)));
      Wire.endTransmission();

      Wire.requestFrom(address, sizeof(uint32_t));  // len of handshake varies with modulename
      Handshake handshakeI;
      if (Wire.available()) {
        i2cSimpleRead(handshakeI);

        moduleList.append(Module(address, handshakeI));
        consumptionSum += handshakeI.consuming;
        modulesClosed &= handshakeI.closed;
      }
      encodeHandshake(handshakeI.type, handshakeI.devices, handshakeI.consuming);
    }
  }

  if (!modulesClosed || !getSafetyButtonClosed()) {
    setSystemMode(Error);
    Serial.println("some Safety button not pressed!");
    // send error by mqtt
  } else if (consumptionSum > consumptionMax) {
    setSystemMode(Error);
    Serial.println(consumptionSum);
    Serial.println(consumptionMax);
    Serial.println("System in overload");
    // send error by mqtt
  } else if (moduleList.isEmpty()) {
    setSystemMode(Error);
    Serial.println("System has no modules");
    // send error by mqtt
  } else
    setSystemMode(Run);
}
