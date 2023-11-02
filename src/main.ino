#include <Arduino.h>

#include "StateMachine.h"
#include "Sys.h"
#include "Menu.h"


StateMachine stateMachine;

void setup() {
  Serial.begin(9600);
  Sys::init();
}

void loop() {
  stateMachine.run();

  delay(100);
}
