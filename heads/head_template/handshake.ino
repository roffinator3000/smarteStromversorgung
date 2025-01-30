
#include <ArduinoJson.h>

// // version 1
// struct Handshake {
//   uint8_t id;         // unique module ID
//   String type;        // name of modul type
//   uint8_t consuming;  // how much energy can be drawn by this module
//   bool closed;        // is the modules connection closed
// };

Handshake decodeHandshake(const String& hsString) {
  JsonDocument hsJson;
  DeserializationError error = deserializeJson(hsJson, hsString);

  if (error) {
    Serial.print("Deserialization failed: ");
    Serial.println(error.c_str());
    return Handshake{ 0, "", 0, false };
  }

  Serial.print("recieved: ");
  Serial.println(hsString);

  return Handshake{
    hsJson["id"],
    hsJson["type"],
    hsJson["consuming"],
    hsJson["closed"]
  };
}
