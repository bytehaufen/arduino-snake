#include "StateMachine.h"
#include "Arduino.h"
#include "Oled.h"
#include "Sys.h"
#include "WString.h"

StateMachine::StateMachine() : currentState(STATE::INIT) {}

void StateMachine::setState(STATE newState) { currentState = newState; }

STATE StateMachine::getState() { return currentState; }

void StateMachine::run() {
  const unsigned long DELAY = 1000;
  const unsigned long DELAY_INIT = 1000;
  // TODO: change back to 3000
  const unsigned long DELAY_TO_MENU = 1;
  static unsigned long initLastMillis = millis();
  static unsigned long introLastMillis = millis();
  static unsigned long gameLastMillis = millis();
  static unsigned long scoreLastMillis = millis();

  const String MENU_ITEMS[] = {F("Start"), F("Score")};

  switch (currentState) {
  case STATE::INIT:
    Oled::getInstance();
    if (millis() - initLastMillis >= DELAY_INIT) {
      currentState = STATE::INTRO;
    }

    break;

  case STATE::INTRO:
    static bool introFinished = false;

    if (!introFinished &&
        Oled::getInstance().printSerialized(F("Welcome to Snake!"))) {
      introFinished = true;
    }
    if (introFinished && millis() - introLastMillis >= DELAY_TO_MENU) {
      currentState = STATE::MENU;
    }
    break;

  case STATE::MENU:
    static uint8_t selectedItem = 0;

    // TODO: Implement
    Oled::getInstance().printMenu(MENU_ITEMS, 2, selectedItem);

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
    break;

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
      currentState = STATE::INTRO;
    }
    break;
  }
};
