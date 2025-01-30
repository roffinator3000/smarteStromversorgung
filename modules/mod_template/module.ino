
// enum LedMode {
//   Off = 0,  // LED ist immer aus
//   Sync,     // LED ist äquivalent zum Zustand des Relays
//   Invert,   // LED ist invertiert zum Zustand des Relays
//   Bicolor   // LED wechselt zwischen Rot und Grün für aus und an
// };

#include "datastructures.h"
#include "submodule_socket_I_B_A.hpp"

// (0, relayPin1, buttonPin1, ledPin1, ammeterPin1);
SocketIBA socket1(1, 1, 2, 3, 4);
SocketIBA socket2(2, 5, 6, 7, 8);
SystemMode operationMode = Starting;

void moduleSetup() {
  setupSafetyButton(A0);
}

void moduleLoop() {
  switch (operationMode) {
    //no need to check during startup or init
    case Run:
    case Error:
      checkSafetyButton();
      // sends a mesage if needed

      if (socket1.hasUpdate()) {
        publish(Message{
          1,                    // submodule 1
          socket1.getUpdate(),  // new Values as JSON in String
          { 0 }                 // ignored
        });
      }
      if (socket2.hasUpdate()) {
        publish(Message{
          2,                    // submodule 2
          socket2.getUpdate(),  // new Values as JSON in String
          { 0 }                 // ignored
        });
      }
  }
}

void publish(const Message messageObj) {
}

void getValues() {
  switch (operationMode) {
    case Initialising:
      i2cSimpleWrite(getHandshake("socketx2_I_B", 6));
      // dual socket with indicator and button; two sockets, each socket can consume 3
      return;
    case Run:
      i2cSimpleWrite("teststring");
      return;
  }
}

void setValues(const Message newValues) {
  switch (newValues.submodule) {
    case 0:
      operationMode = newValues.statusI.modeI;
      break;
    case 1:
      socket1.setValues(newValues.payload);
      break;
    case 2:
      socket2.setValues(newValues.payload);
      break;
  }
}
