#include <Arduino.h>

#include "StateMachine.h"
#include "Sys.h"

#define DEBUG

StateMachine stateMachine;

void setup() {
  Serial.begin(115200);
}

void loop() {
  stateMachine.run();
  Sys::getInstance().run();

  // TODO rm DEBUG
#ifdef DEBUG
  // Sys::printi2cdevices();
#endif // DEBUG

// TODO rm delay and make unblocking
  delay(100);
}
