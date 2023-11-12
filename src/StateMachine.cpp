#include "StateMachine.h"

StateMachine::StateMachine()
    : currentState(STATE::INIT), MENU_ITEMS{F("Start"), F("Score")} {}

void StateMachine::setState(STATE newState) { currentState = newState; }

StateMachine::STATE StateMachine::getState() { return currentState; }

void StateMachine::run() {
  static unsigned long initLastMillis = millis();
  static unsigned long introLastMillis = millis();

  switch (currentState) {
  case STATE::INIT:
    Display::getInstance();
    // Async delay
    if (millis() - initLastMillis >= DELAY_INIT) {
      currentState = STATE::INTRO;
    }

    break;

  case STATE::INTRO:
    static bool introFinished = false;

    if (!introFinished &&
        Display::getInstance().printSerialized(F("Welcome to   Snake!"))) {
      introFinished = true;
    }
    if (introFinished && millis() - introLastMillis >= DELAY_TO_MENU) {
      currentState = STATE::MENU;
      introFinished = false;
      // TODO: clear intro before menu?
      /* Display::getInstance().clear(); */
    }
    break;

  case STATE::MENU:
    static MENU_ITEM selectedItem = MENU_ITEM::START;
    static bool firstCall = true;

    Input::BUTTON pressedButton;
    pressedButton = Input::getInstance().getPressedButton();

    if (firstCall || (pressedButton != Input::BUTTON::NONE)) {
      if (pressedButton == Input::BUTTON::UP) {
        selectPrevMenuItem(selectedItem);
      } else if (pressedButton == Input::BUTTON::DOWN) {
        selectNextMenuItem(selectedItem);
      } else if (pressedButton == Input::BUTTON::MIDDLE) {
        switch (selectedItem) {
        case MENU_ITEM::START:
          currentState = STATE::GAME;
          // TODO:change delay
          Input::getInstance().consumeJoystick();
          break;
        case MENU_ITEM::SCORE:
          currentState = STATE::SCORE;
          // TODO:change delay
          Input::getInstance().consumeJoystick();
          break;
        }
        firstCall = true;
        break;
      }
      Display::getInstance().printMenu(MENU_ITEMS, MENU_ITEMS_COUNT,
                                       static_cast<uint8_t>(selectedItem));

      firstCall = false;
    }
    break;

  case STATE::GAME:
    // TODO Implement
    static bool init = true;
    if (init) {
      init = false;
      game = new Game();
    }
    // Done with game
    if (!game->run()) {
      delete game;
      init = true;
      currentState = STATE::SCORE;
    }

    break;

  case STATE::SCORE:
    // TODO Implement

    if (Display::getInstance().printSerialized(F("Score!"))) {
      currentState = STATE::INTRO;
      Display::getInstance().clear();
    }
    break;
  }
};

void StateMachine::selectPrevMenuItem(MENU_ITEM &item) {
  switch (item) {
  case MENU_ITEM::START:
    break;
  case MENU_ITEM::SCORE:
    item = MENU_ITEM::START;
    break;
  }
}
void StateMachine::selectNextMenuItem(MENU_ITEM &item) {
  switch (item) {
  case MENU_ITEM::START:
    item = MENU_ITEM::SCORE;
    break;
  case MENU_ITEM::SCORE:
    break;
  }
};
