#include "Input.h"
#include "StateMachine.h"

#include "util/delay.h"

#define DEBUG

StateMachine stateMachine;

void setup() { Serial.begin(115200); }

void loop() {
  stateMachine.run();
  Input::getInstance().run();

  // TODO rm DEBUG
#ifdef DEBUG
  // Input::printi2cdevices();
#endif // DEBUG

  // TODO rm delay and make unblocking
  _delay_ms(100);
}
