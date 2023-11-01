#include <Arduino.h>

#include "StateMachine.h"

StateMachine stateMachine;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  stateMachine.run();
  delay(100);
}
