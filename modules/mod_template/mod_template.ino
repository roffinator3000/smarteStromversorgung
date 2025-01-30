
#include <Wire.h>
#include <i2cSimpleTransfer.h>
// https://github.com/getsurreal/i2cSimpleTransfer

#include "datastructures.h"

Message i2cMessage(1, "", false);

void setup() {
  Serial.begin(9600);
  Serial.println("Hi");

  Wire.begin(getShortId());  // join I2C bus as slave
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  moduleSetup();
}

void loop() {
  moduleLoop();
}

//received data handler function
void receiveEvent(int payloadLen) {
  Serial.print("got called ");
  if (payloadLen == sizeof(i2cMessage)) {
    i2cSimpleRead(i2cMessage);
    setValues(i2cMessage);
  }
}

// requests data handler function
void requestEvent() {
  Serial.println("got asked for data");
  getValues();
}
