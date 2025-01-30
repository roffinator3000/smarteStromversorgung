#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <Arduino.h>
#include <ArduinoJson.h>
#include "datastructures.h"

class Socket {
private:
  const int number;  // to differentiate between objects
  bool power;        // state of relay
  const int relay;   // pin of controled relay

  bool hasChanges;  // are there unsent changes?
  bool hasError;    // are there unsent errors?
  String errorStr;

public:
  Socket(int number, int relayPin);

  void setPower(bool newPower);

  int getNumber() const;

  bool hasUpdate();
  String getUpdate();
  void setValues(String newValues);
};

#endif  // SOCKET_HPP
