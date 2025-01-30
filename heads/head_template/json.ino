
#include <ArduinoJson.h>

void decode(const String message) {

  JsonDocument doc;
  deserializeJson(doc, message);
  if (doc.is<JsonObject>()) {
    for (JsonPair keyValue : doc.as<JsonObject>()) {

      Serial.print(keyValue.key().c_str());
      Serial.print(": ");

      //find out what type value is. sadly not switchable
      if (keyValue.value().is<long>())
        Serial.println(keyValue.value().as<long>());
      else if (keyValue.value().is<bool>())
        Serial.println(keyValue.value().as<bool>() ? "true" : "false");
      else if (keyValue.value().is<double>())
        Serial.println(keyValue.value().as<double>());
      else if (keyValue.value().is<const char*>())
        Serial.println(keyValue.value().as<const char*>());
      else {
        // build tmp JSON object so only invalid part is included in string to still be published
        Serial.print(F("recived partially invalid JSON "));
        JsonDocument tmp;
        String tmpMessage;
        tmp[keyValue.key()] = keyValue.value();
        serializeJson(tmp, tmpMessage);
        Serial.print(tmpMessage);
      }
    }
    Serial.println();
    return;

  } else {
    // pubish whole message as error
    Serial.print(F("recived invalid JSON "));
    Serial.print(message);
    Serial.println();
  }
}
