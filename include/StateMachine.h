#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "Oled.h"
#include "Sys.h"
#include <Arduino.h>

enum class STATE { INIT, INTRO, MENU, GAME, SCORE };

class StateMachine {

private:
  STATE currentState;
  const unsigned long DELAY = 1000;
  const unsigned long DELAY_INIT = 1000;
  // TODO: change back to 3000
  const unsigned long DELAY_TO_MENU = 1;

  static const uint8_t MENU_ITEMS_COUNT = 2;
  const String MENU_ITEMS[MENU_ITEMS_COUNT];

  /* Oled &oled = Oled::getInstance(); */
  /* Sys &sys = Sys::getInstance(); */

public:
  StateMachine();

  void setState(STATE newState);
  STATE getState();

  void run();
};

#endif // STATEMACHINE_H
