#include "StateMachine.h"

StateMachine::StateMachine(Timer &t)
    : currentState(STATE::INIT), MENU_ITEMS{"Start", "Difficulty"},
      DIFFICULTY_ITEMS{"Easy", "Medium", "Hard", "Hardest", "Impossible"},
      timer(&t) {}

void StateMachine::setState(STATE newState) { currentState = newState; }

StateMachine::STATE StateMachine::getState() { return currentState; }

void StateMachine::run() {
  static bool isFirstCall = true;
  static uint16_t clockCounter;

  switch (currentState) {
  case STATE::INIT:

    if (isFirstCall) {
      clockCounter = 0;
      isFirstCall = false;
    }

    // Wait for for 10 cycles
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

    if (!introFinished && clockCounter++ % 10 == 0 &&
        Display::getInstance().printSerialized("Welcome to   Snake!")) {

      Display::getInstance().drawLogo(220, 120);
      introFinished = true;
      clockCounter = 0;
    }
    // Wait for 2 seconds IF intro is finished
    if (introFinished && clockCounter++ > 200) {
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

    pressedButton = Input::getInstance().getPressedButton();

    if (isFirstCall) {
      Display::getInstance().clear();
    }

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
          Input::getInstance().consumeJoystick();
          break;
        case MENU_ITEM::DIFFICULTY:
          currentState = STATE::DIFFICULTY;
          Input::getInstance().consumeJoystick();
          break;
        }

        isFirstCall = true;
        break;
      }
      Display::getInstance().printMenu("Menu", MENU_ITEMS, MENU_ITEMS_COUNT,
                                       static_cast<uint8_t>(selectedItem));
    }
    break;

  case STATE::GAME:
    if (isFirstCall) {
      isFirstCall = false;
      srand(timer->milliSeconds());
      game = new Game(selectedDifficulty);
      Input::getInstance().consumeJoystick();
    } else {
      // Run game
      lastScore = game->run();
      if (lastScore != Game::GAME_RUNNING) {
        delete game;
        isFirstCall = true;
        currentState = STATE::SCORE_POPUP;
      }
    }

    break;

  case STATE::SCORE_POPUP:
    // TODO Implement
    if (isFirstCall) {
      clockCounter = 0;
      isFirstCall = false;
      Display::getInstance().printScorePopup(lastScore);
    }

    // Wait for 300 cycles
    if (clockCounter++ > 300) {
      currentState = STATE::MENU;
      clockCounter = 0;
      isFirstCall = true;
    }

    break;
  case STATE::DIFFICULTY:
    pressedButton = Input::getInstance().getPressedButton();

    if (isFirstCall) {
      Display::getInstance().clear();
    }

    if (isFirstCall || (pressedButton != Input::BUTTON::NONE)) {
      isFirstCall = false;
      if (pressedButton == Input::BUTTON::UP) {
        selectPrevDifficulty(selectedDifficulty);
      } else if (pressedButton == Input::BUTTON::DOWN) {
        selectNextDifficulty(selectedDifficulty);
      } else if (pressedButton == Input::BUTTON::MIDDLE) {
        currentState = STATE::MENU;
        clockCounter = 0;
        isFirstCall = true;
      }
      Display::getInstance().printMenu(
          "Difficulty", DIFFICULTY_ITEMS, DIFFICULTY_ITEMS_COUNT,
          selectedDifficulty == Game::DIFFICULTY::IMPOSSIBLE ? 4
          : selectedDifficulty == Game::DIFFICULTY::HARDEST  ? 3
          : selectedDifficulty == Game::DIFFICULTY::HARD     ? 2
          : selectedDifficulty == Game::DIFFICULTY::MEDIUM   ? 1
                                                             : 0);
    }
    break;
  }
};

void StateMachine::selectPrevMenuItem(MENU_ITEM &item) {
  switch (item) {
  case MENU_ITEM::DIFFICULTY:
    item = static_cast<MENU_ITEM>(static_cast<uint8_t>(item) - 1);
    break;
  default:
    break;
  }
}
void StateMachine::selectNextMenuItem(MENU_ITEM &item) {
  switch (item) {
  case MENU_ITEM::START:
    item = static_cast<MENU_ITEM>(static_cast<uint8_t>(item) + 1);
    break;
  default:
    break;
  }
};
void StateMachine::selectPrevDifficulty(Game::DIFFICULTY &selectedDifficulty) {
  switch (selectedDifficulty) {

  case Game::DIFFICULTY::MEDIUM:
    selectedDifficulty = Game::DIFFICULTY::EASY;
    break;
  case Game::DIFFICULTY::HARD:
    selectedDifficulty = Game::DIFFICULTY::MEDIUM;
    break;
  case Game::DIFFICULTY::HARDEST:
    selectedDifficulty = Game::DIFFICULTY::HARD;
    break;
  case Game::DIFFICULTY::IMPOSSIBLE:
    selectedDifficulty = Game::DIFFICULTY::HARDEST;
    break;
  default:
    break;
  }
}
void StateMachine::selectNextDifficulty(Game::DIFFICULTY &selectedDifficulty) {
  switch (selectedDifficulty) {
  case Game::DIFFICULTY::EASY:
    selectedDifficulty = Game::DIFFICULTY::MEDIUM;
    break;
  case Game::DIFFICULTY::MEDIUM:
    selectedDifficulty = Game::DIFFICULTY::HARD;
    break;
  case Game::DIFFICULTY::HARD:
    selectedDifficulty = Game::DIFFICULTY::HARDEST;
    break;
  case Game::DIFFICULTY::HARDEST:
    selectedDifficulty = Game::DIFFICULTY::IMPOSSIBLE;
    break;
  default:
    break;
  }
}
