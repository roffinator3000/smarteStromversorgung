#include "submodule_encoder.hpp"

Socket::Socket(int number, int relayPin, int buttonPin, int ledPin, int ammeterPin)
  : number(number), power(false),
    relay(relayPin), button(buttonPin),
    led(ledPin), ledModeVal(Sync), ammeter(ammeterPin),
    interval(60), hasChanges(true) {
  pinMode(relay, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(ammeter, INPUT_PULLUP);
}

void Socket::setPower(bool newPower) {
  power = newPower;
  digitalWrite(relay, newPower);
  switch (ledModeVal) {
    // case Off: // stays off
    case Sync:
      digitalWrite(led, newPower);
      break;
    case Invert:
      digitalWrite(led, !newPower);
      break;
      // case Bicolor: // needs two leds
  }
}
void Socket::togglePower() {
  setPower(!power);
}

void Socket::setLedMode(LedMode newMode) {
  ledModeVal = newMode;
  switch (newMode) {
    case Off:
      digitalWrite(led, LOW);
      break;
    case Bicolor:
      ledModeVal = Sync;  // only one led is in use
      hasChanges = true;  // needs to be sent back
      break;
    default:
      ledModeVal = newMode;
      break;
  }
}
void Socket::setLedMode(const String& mode) {
  String modeLow = mode;
  modeLow.toLowerCase();
  if (modeLow == "off")
    setLedMode(Off);
  else if (modeLow == "sync")
    setLedMode(Sync);
  else if (modeLow == "invert")
    setLedMode(Invert);
  else if (modeLow == "bicolor")
    setLedMode(Bicolor);
  else
    setLedMode(Sync);  // Sync is default
}

void Socket::setInterval(int newInterval) {
  if (newInterval < 10) {
    interval = 10;
    hasChanges = true;  // needs to be sent back
  } else
    interval = newInterval;
}

int Socket::getNumber() const {
  return number;
}
int Socket::getMAmp() const {
  return digitalRead(ammeter);
}
bool Socket::getButton() const {
  return digitalRead(button);
}

// only returns whether something changed
bool Socket::hasUpdate() {
  return buttonState != getButton()
         | millis() > timestamp + interval
         | hasChanges;
}

// return actual changes as JSON
String Socket::getUpdate() {
  String updateString = "";
  JsonDocument updateJson;

// by breaking the update into sections the String gets shortened
// this is necesarry as the wire library only allows to transmit up to 32 bytes at a time
  if (buttonState != getButton()) {
    buttonState = !buttonState;
    if (buttonState)
      togglePower();
    updateJson["button"] = buttonState;
    updateJson["power"] = power;

  } else if (millis() > timestamp + interval) {
    timestamp = millis();
    updateJson["mAmp"] = getMAmp();

  } else if (hasChanges) {
    switch (ledModeVal) {
      case Off:
        updateJson["ledMode"] = "off";
        break;
      case Sync:
        updateJson["ledMode"] = "sync";
        break;
      case Invert:
        updateJson["ledMode"] = "invert";
        break;
    }
    updateJson["interval"] = interval;
  }

  serializeJson(updateJson, updateString);

  Serial.print("sending: ");
  Serial.println(updateString);

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
    const char* keyName = keyValue.key().c_str();  // Get the key name as a C-string

    if (keyName == "power")
      setPower(newValJ["power"]);
    else if (keyName == "ledMode")
      setLedMode(newValJ["ledMode"].as<const char*>());
    else if (keyName == "interval")
      setInterval(newValJ["interval"]);
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
}
