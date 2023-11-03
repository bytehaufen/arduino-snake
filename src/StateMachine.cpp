#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "StateMachine.h"
#include "Menu.h"
#include "Sys.h"

StateMachine::StateMachine() : currentState(STATE::INTRO) {}

void StateMachine::setState(STATE newState) { currentState = newState; }

STATE StateMachine::getState() { return currentState; }

void StateMachine::run() {
  const unsigned long DELAY = 1000;
  static unsigned long introLastMillis = millis();
  static unsigned long gameLastMillis = millis();
  static unsigned long scoreLastMillis = millis();

  // TODO rm DEBUG
  /* Serial.print("State: "); */
  /* Serial.println((int)currentState); */

  switch (currentState) {
  case STATE::INTRO:
    // TODO Implement

    if (millis() - introLastMillis >= DELAY) {
      currentState = STATE::MENU;
    }
    break;

  case STATE::MENU:
    // TODO Implement

    /* if (!digitalRead(Sys::DOWN_PIN)) { */
    /*   menu.next(); */
    /* } else if (!digitalRead(Sys::UP_PIN)) { */
    /*   menu.prev(); */
    /* } else if (!digitalRead(Sys::RIGHT_PIN)) { */
    /*   if (menu.getSelectedMenuItem() == MENU_ITEM::START) { */
    /*     currentState = STATE::GAME; */
    /*   } else if (menu.getSelectedMenuItem() == MENU_ITEM::SCORE) { */
    /*     currentState = STATE::SCORE; */
    /*   } */
    /* } */
    /* break; */

  case STATE::GAME:
    // TODO Implement

    if (millis() - gameLastMillis >= DELAY) {
      scoreLastMillis = millis();
      currentState = STATE::SCORE;
    }
    break;

  case STATE::SCORE:
    // TODO Implement

    if (millis() - scoreLastMillis >= DELAY) {
      introLastMillis = millis();
      currentState = STATE::INTRO;
    }
    break;
  }
};

#endif // STATEMACHINE_H
