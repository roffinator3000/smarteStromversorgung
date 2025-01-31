
#include <ArduinoJson.h>


String encode() {
  String message = "";
  JsonDocument doc;
  int count = 0;

  float temp = random(1500, 3300) / 100.0f;
  float hum = random(7500, 9000) / 100.0f;

  /// Example of creating a JSON document
  doc["temp"] = temp;
  doc["hum"] = hum;
  doc["bool"] = true;
  doc["count"] = ++count;
  doc["sumth"] = "sumth";
  doc["json"] = "{\"key\":\"value\"}";

  /// Serialize the doc object into JSON format into the message variable
  /// Example Output message => { "temperature": 25,"humidity":75 }
  serializeJson(doc, message);

  Serial.print("sending: ");
  Serial.println(message);

  return message;
}



void decode(const String message) {

  JsonDocument doc;
  deserializeJson(doc, message);
  if (doc.is<JsonObject>()) {
    // JsonObject obj = doc.as<JsonObject>();  // Get JsonObject from the document

    // Iterate through each key-value pair in the JsonObject
    // for (JsonPair keyValue : obj) {
    for (JsonPair keyValue : doc.as<JsonObject>()) {
      // const char* keyName = keyValue.key().c_str();  // Get the key name as a C-string

      // Serial.print("Value of ");
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
