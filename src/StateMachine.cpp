#include "StateMachine.h"

StateMachine::StateMachine()
    : currentState(STATE::INIT), MENU_ITEMS{"Start", "Score"} {}

void StateMachine::setState(STATE newState) { currentState = newState; }

StateMachine::STATE StateMachine::getState() { return currentState; }

void StateMachine::run() {
  static bool isFirstCall = true;
  static uint8_t clockCounter;

  switch (currentState) {
  case STATE::INIT:

    if (isFirstCall) {
      clockCounter = 0;
      isFirstCall = false;
    }

    // Wait for 1 second
    if (clockCounter++ > 10) {
      currentState = STATE::INTRO;
      clockCounter = 0;
      isFirstCall = true;
    }

    break;

  case STATE::INTRO:
    static bool introFinished = false;

    if (isFirstCall) {
      clockCounter = 0;
      isFirstCall = false;
      Display::getInstance().clear();
    }

    if (!introFinished &&
        Display::getInstance().printSerialized("Welcome to   Snake!")) {
      introFinished = true;
    }
    // Wait for 1 second IF intro is finished
    if (introFinished && clockCounter++ > 10) {
      currentState = STATE::MENU;
      introFinished = false;
      isFirstCall = true;
      clockCounter = 0;
      Input::getInstance().consumeJoystick();

      // TODO: clear intro before menu?
      /* Display::getInstance().clear(); */
    }
    break;

  case STATE::MENU:
    static MENU_ITEM selectedItem = MENU_ITEM::START;

    Input::BUTTON pressedButton;
    pressedButton = Input::getInstance().getPressedButton();

    if (isFirstCall || (pressedButton != Input::BUTTON::NONE)) {
      isFirstCall = false;
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
        isFirstCall = true;
        break;
      }
      Display::getInstance().printMenu(MENU_ITEMS, MENU_ITEMS_COUNT,
                                       static_cast<uint8_t>(selectedItem));
    }
    break;

  case STATE::GAME:
    if (isFirstCall) {
      isFirstCall = false;
      game = new Game();
      Input::getInstance().consumeJoystick();
    }
    // Done with game
    if (!game->run()) {
      delete game;
      isFirstCall = true;
      currentState = STATE::SCORE;
    }

    break;

  case STATE::SCORE:
    // TODO Implement

    if (Display::getInstance().printSerialized("Score!")) {
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
