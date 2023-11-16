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
  Input::getInstance().run();

  static uint32_t lastMillis = 0;

  // Run StateMachine every 10ms = 100 Hz
  if (timer.milliSeconds() - lastMillis >= 10) {
    stateMachine.run();
    lastMillis = timer.milliSeconds();
  }

  // TODO rm DEBUG
#ifdef DEBUG
  // Input::printi2cdevices();
#endif // DEBUG
}
