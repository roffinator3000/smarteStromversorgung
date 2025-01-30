
#include <Bonezegei_WS2812.h>

Bonezegei_WS2812 rgbLed(48);
const int button = 5;
const int relay = 17;

enum LedMode : uint8_t {
  Off = 0,  // LED is always off
  Sync,     // LED is equivalent to the state of the relay
  Invert,   // LED is inverted to the state of the relay
  Bicolor   // LED alternates between red and green for off and on
};

LedMode mode = Sync;
bool power = false;
bool buttonStateOld = false;

void setup_socket() {
  pinMode(button, INPUT_PULLDOWN);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, false);
  rgbLed.begin();
}

bool getButtonChanged() {
  return digitalRead(button) != buttonStateOld;
}

bool getButtonState() {
  buttonStateOld = digitalRead(button);
  return buttonStateOld;
}

void setPower(String newPower) {
  newPower.toLowerCase();
  if (newPower == "true")
    power = true;
  else
    power = false;
  digitalWrite(relay, power);
  updateLed();
}

void setLedMode(String newMode) {
  newMode.toLowerCase();
  if (newMode == "off")
    mode = Off;
  else if (newMode == "invert")
    mode = Invert;
  else if (newMode == "bicolor")
    mode = Bicolor;
  else
    mode = Sync;  // Sync is default
  updateLed();
}

void updateLed() {
  switch (mode) {
    case Off:
      rgbLed.setPixel(0x000000);  // off
      break;
    case Sync:
      if (power)
        rgbLed.setPixel(0x222222);  // on
      else
        rgbLed.setPixel(0x000000);  // off
      break;
    case Invert:
      if (power)
        rgbLed.setPixel(0x000000);  // off
      else
        rgbLed.setPixel(0x222222);  // on
      break;
    case Bicolor:
      if (power)
        rgbLed.setPixel(0x005500);  // green
      else
        rgbLed.setPixel(0x550000);  // red
      break;
  }
}
