#include "Input.h"
#include "StateMachine.h"
#include "Timer.h"

#define DEBUG

Timer timer;
StateMachine stateMachine(timer);

void setup() {
  // Initialize Display
  Display::getInstance().clear();

  // TODO: rm
  Serial.begin(115200);
}

void loop() {
  // Run Input
  Input::getInstance().run(&timer);

  static uint32_t lastMillis = 0;
  static uint32_t benchMarkmillis = timer.milliSeconds();

  // Run StateMachine every 10ms = 100 Hz
  if (timer.milliSeconds() - lastMillis >= 10) {
    stateMachine.run();
    lastMillis = timer.milliSeconds();
  }
  // TODO: Rm DEBUG
  uint16_t timeElapsed = timer.milliSeconds() - benchMarkmillis;
  if (timeElapsed) {
    Serial.println(timer.milliSeconds() - benchMarkmillis);
  }
  benchMarkmillis = timer.milliSeconds();
}
