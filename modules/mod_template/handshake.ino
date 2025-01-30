
#include <ArduinoJson.h>

/*
version 1:
struct Handshake {
  uint16_t id;        // unique module ID
  String type;        // name of modul type
  uint8_t consuming;  // how much energy can be drawn by this module
  bool closed;        // is the modules connection closed
};*/

Handshake getHandshake(String typeName, uint8_t energyConsumption) {

  return {
    getUniqueId(),
    typeName,
    energyConsumption,
    getSafetyButtonState()
  };
}

String encodeHandshake(String typeName, uint8_t energyConsumption) {
  String hsString = "";
  JsonDocument hsJson;

  hsJson["id"] = getUniqueId();
  hsJson["type"] = typeName;
  hsJson["consuming"] = energyConsumption;
  hsJson["closed"] = getSafetyButtonState();

  serializeJson(hsJson, hsString);
  return hsString;
}
