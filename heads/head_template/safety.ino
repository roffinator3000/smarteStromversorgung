
int safetySwitch;
int safetyButton;
bool previousSafetyButtonClosed;

void setupSafetyButton(int safetyButtonPin) {
  safetyButton = safetyButtonPin;
  pinMode(safetyButton, INPUT_PULLUP);
  previousSafetyButtonClosed = getSafetyButtonClosed();
}

bool getSafetyButtonClosed() {
  return true;
  return digitalRead(safetyButton);
}

void checkSafetyButton() {
  if (previousSafetyButtonClosed & !getSafetyButtonClosed()) {
    setSystemMode(Error);
    Serial.println("Safety button not pressed!");
  } else if (!previousSafetyButtonClosed & getSafetyButtonClosed()) {
    setSystemMode(Initialising);
    Serial.println("Safety button pressed again");
  }
}

void setupSafetySwitch(int safetySwitchPin) {
  safetySwitch = safetySwitchPin;
  pinMode(safetyButton, OUTPUT);
  setSafetySwitchState(false);
}

void setSafetySwitchState(bool newState) {
  digitalWrite(safetyButton, newState);
}