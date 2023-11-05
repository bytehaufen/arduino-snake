#include "StateMachine.h"
#include "Arduino.h"
#include "Oled.h"
#include "Sys.h"
#include "WString.h"

enum class MENU_ITEM { START = 0, SCORE = 1 };

StateMachine::StateMachine()
    : currentState(STATE::INIT), MENU_ITEMS{F("Start"), F("Score")} {}

void StateMachine::setState(STATE newState) { currentState = newState; }

STATE StateMachine::getState() { return currentState; }

void StateMachine::run() {
  static unsigned long initLastMillis = millis();
  static unsigned long introLastMillis = millis();

  void selectPrevMenuItem(MENU_ITEM & item);
  void selectNextMenuItem(MENU_ITEM & item);

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
    static MENU_ITEM selectedItem = MENU_ITEM::START;
    static bool firstCall = true;

    Sys::BUTTON pressedButton;
    pressedButton = Sys::getInstance().getPressedButton();

    if (firstCall || (pressedButton != Sys::BUTTON::NONE)) {
      if (pressedButton == Sys::BUTTON::UP) {
        selectPrevMenuItem(selectedItem);
      } else if (pressedButton == Sys::BUTTON::DOWN) {
        selectNextMenuItem(selectedItem);
      } else if (pressedButton == Sys::BUTTON::MIDDLE) {
        switch (selectedItem) {
        case MENU_ITEM::START:
          currentState = STATE::GAME;
          // TODO:change delay
          delay(100);
          Sys::getInstance().consumeJoystick();
          break;
        case MENU_ITEM::SCORE:
          currentState = STATE::SCORE;
          // TODO:change delay
          delay(100);
          Sys::getInstance().consumeJoystick();
          break;
        }
        firstCall = true;
        break;
      }
      Oled::getInstance().printMenu(MENU_ITEMS, MENU_ITEMS_COUNT,
                                    static_cast<uint8_t>(selectedItem));

      firstCall = false;
    }
    break;

  case STATE::GAME:
    // TODO Implement
    if (Oled::getInstance().printSerialized(F("Game!"))) {
      currentState = STATE::SCORE;
    }

    break;

  case STATE::SCORE:
    // TODO Implement

    if (Oled::getInstance().printSerialized(F("Score!"))) {
      currentState = STATE::MENU;
    }
    break;
  }
};

void selectPrevMenuItem(MENU_ITEM &item) {
  switch (item) {
  case MENU_ITEM::START:
    break;
  case MENU_ITEM::SCORE:
    item = MENU_ITEM::START;
    break;
  }
}
void selectNextMenuItem(MENU_ITEM &item) {
  switch (item) {
  case MENU_ITEM::START:
    item = MENU_ITEM::SCORE;
    break;
  case MENU_ITEM::SCORE:
    break;
  }
};
