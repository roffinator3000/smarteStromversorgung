
int safetyButton;
bool previousSafetyButtonState;

void setupSafetyButton(int safetyButtonPin) {
  safetyButton = safetyButtonPin;
  pinMode(safetyButton, INPUT_PULLUP);
  previousSafetyButtonState = getSafetyButtonState();
}

bool getSafetyButtonState() {
  return digitalRead(safetyButton);
}

void checkSafetyButton() {
  if (previousSafetyButtonState & !getSafetyButtonState()) {
    publish(Message{
      0,     // submodule 0 is the Module itself
      "",    // no payload string needed
      false  // actual payload
    });
    Serial.println("Safety button not pressed!");
  } else if (!previousSafetyButtonState & getSafetyButtonState()) {
    publish(Message{
      0,    // submodule 0 is the Module itself
      "",   // no payload string needed
      true  // actual payload
    });
    Serial.println("Safety button pressed again");
  }
}
