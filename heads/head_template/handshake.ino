
#include <ArduinoJson.h>

// // version 2
// struct Handshake {
//   uint8_t id;         // unique module ID
//   String type;        // name of modul type
//   uint8_t devices;    // number of subdevices
//   uint8_t consuming;  // how much energy can be drawn by this module
//   bool closed;        // is the modules connection closed
// };

Handshake decodeHandshake(const String& hsString) {
  JsonDocument hsJson;
  DeserializationError error = deserializeJson(hsJson, hsString);

  if (error) {
    Serial.print("Deserialization failed: ");
    Serial.println(error.c_str());
    // Rückgabe einer leeren Handshake-Struktur im Fehlerfall
    return Handshake{ 0, "", 0, 0, false };
  }

  Serial.print("recieved: ");
  Serial.println(hsString);

  return Handshake{
    hsJson["id"],
    hsJson["type"],
    hsJson["devices"],
    hsJson["consuming"],
    hsJson["closed"]
  };
}


String encodeHandshake(String typeName, uint8_t numSubdevices, uint8_t energyConsumption) {
  String hsString = "";
  JsonDocument hsJson;

  hsJson["type"] = typeName;
  hsJson["devices"] = numSubdevices;
  hsJson["consuming"] = energyConsumption;

  serializeJson(hsJson, hsString);

  Serial.print("sending: ");
  Serial.println(hsString);

  return hsString;
}
