#include "submodule_socket.hpp"

Socket::Socket(int number, int relayPin)
  : number(number), power(false),
    hasChanges(true), hasError(false), errorStr("") {
  pinMode(relay, OUTPUT);
}

void Socket::setPower(bool newPower) {
  power = newPower;
  digitalWrite(relay, newPower);
}

int Socket::getNumber() const {
  return number;
}
bool Socket::hasUpdate() {
  return hasChanges | hasError;
}

String Socket::getUpdate() {

  if (hasError)
    return errorStr;

  String updateString = "";
  JsonDocument updateJson;

  updateJson["power"] = "power";
  serializeJson(updateJson, updateString);
  return updateString;
}

// read in external changes from JSON
void Socket::setValues(const String newValues) {
  JsonDocument newValJ;

  DeserializationError error = deserializeJson(newValJ, newValues);
  if (error) {
    Serial.print("Deserialization failed: ");
    Serial.println(error.c_str());
  }

  for (JsonPair keyValue : newValJ.as<JsonObject>()) {
    const char* keyName = keyValue.key().c_str();

    if (keyName == "power")
      setPower(newValJ["power"]);
    else {
      // build tmp JSON object so the invalid part can be sent back and published as error
      Serial.print(F("recived partially invalid JSON "));
      JsonDocument tmp;
      tmp[keyValue.key()] = keyValue.value();
      serializeJson(errorStr, tmpMessage);
      hasError = true;
    }
  }
}
