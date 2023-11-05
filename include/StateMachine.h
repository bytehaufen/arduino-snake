#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "Oled.h"

#include <Arduino.h>

enum class STATE {INIT, INTRO, MENU, GAME, SCORE };

class StateMachine {
private:
  STATE currentState;

public:
  StateMachine();

  void setState(STATE newState);
  STATE getState();

  void run();
};

#endif // STATEMACHINE_H
