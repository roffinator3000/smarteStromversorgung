
#include <Wire.h>
#include <i2cSimpleTransfer.h>
// https://github.com/getsurreal/i2cSimpleTransfer

#include "datastructures.h"


void setup() {
  Serial.begin(9600);
  Serial.println("Hi");

  Wire.begin();  // join I2C bus as the master
  moduleSetup();
}


void loop() {
  moduleLoop();
}
