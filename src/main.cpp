#include "Input.h"
#include "StateMachine.h"
#include "Timer.h"

// TODO: Remove in production
/* #define DEBUG */

Timer timer;
StateMachine stateMachine(timer);

/**
 * @brief Calculates the free memory by measuring the distance between current
 * stack pointer and the heap pointers.
 *  NOTE: No exact value (that's impossible on avr mcu)
 *  @return free memory
 */
int getFreeMemory();

void setup() {
  // Initialize Display
  Display::getInstance().clear();

#ifdef DEBUG
  Serial.begin(115200);
#endif
}

void loop() {
  // Run Input
  Input::getInstance().run(&timer);

  static uint32_t lastMillis = 0;

  // Run StateMachine every 10ms = 100 Hz
  if (timer.milliSeconds() - lastMillis >= 10) {
    stateMachine.run();
    lastMillis = timer.milliSeconds();
  }

#ifdef DEBUG
  static uint32_t benchMarkmillis = timer.milliSeconds();
  uint16_t timeElapsed = timer.milliSeconds() - benchMarkmillis;
  if (timeElapsed) {
    Serial.print("Elapsed time for one loop: ");
    Serial.println(timer.milliSeconds() - benchMarkmillis);
    Serial.print("Free memory: ");
    Serial.println(getFreeMemory());
  }
  benchMarkmillis = timer.milliSeconds();
#endif
}

#ifdef DEBUG
extern unsigned int __heap_start;
extern void *__brkval;

int getFreeMemory() {
  int free_memory;
  if ((int)__brkval == 0) {
    free_memory = ((int)&free_memory) - ((int)&__heap_start);
  } else {
    free_memory = ((int)&free_memory) - ((int)__brkval);
  }
  return free_memory;
}
#endif
