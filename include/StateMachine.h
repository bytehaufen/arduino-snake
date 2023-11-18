/**
 * @file StateMachine.h
 * @brief Class that handles the state of the game.
 */

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "Display.h"
#include "Game.h"
#include "Input.h"
#include "Timer.h"

/**
 * @class StateMachine
 * @brief Class that handles the state of the game.
 *
 */
class StateMachine {
private:
  /**
   * @brief Enum for the different states of the game.
   */
  enum class STATE { INIT, INTRO, MENU, GAME, SCORE_POPUP, DIFFICULTY };
  /**
   * @brief Enum for the different menu items.
   */
  enum class MENU_ITEM { START = 0, DIFFICULTY = 1 };
  /**
   * @brief Enum for the different difficulties.
   */
  enum class DIFFICULTY { EASY = 0, MEDIUM = 1, HARD = 2 };
  // Holds the active state
  STATE currentState;
  // Menu items
  static const uint8_t MENU_ITEMS_COUNT = 2;
  const String MENU_ITEMS[MENU_ITEMS_COUNT];
  // Menu items
  static const uint8_t DIFFICULTY_ITEMS_COUNT = 3;
  const String DIFFICULTY_ITEMS[DIFFICULTY_ITEMS_COUNT];
  // Pointer to game
  Game *game;
  Timer *timer;
  // Stores the pressed button.
  Input::BUTTON pressedButton;
  // Stores the selected difficulty.
  DIFFICULTY selectedDifficulty = DIFFICULTY::EASY;
  /**
   * @brief Sets the state of the game.
   * @param newState The new state of the game.
   */
  void setState(STATE newState);
  /**
   * @brief Gets the state of the game.
   * @return The state of the game.
   */
  STATE getState();

  /**
   * @brief Selects the previous menu item.
   * @param item The Menu item object.
   */
  void selectPrevMenuItem(MENU_ITEM &item);
  /**
   * @brief Selects the next menu item.
   * @param item The Menu item object.
   */
  void selectNextMenuItem(MENU_ITEM &item);
  /**
   * @brief Selects the previous difficulty.
   * @param item The Difficulty item object.
   */
  void selectPrevDifficulty(DIFFICULTY &item);
  /**
   * @brief Selects the next difficulty.
   * @param item The Difficulty item object.j
   */
  void selectNextDifficulty(DIFFICULTY &item);

  /**
   * @brief Holds the last score.
   */
  uint16_t lastScore = 0;

public:
  /**
   * @brief Constructor for the StateMachine.
   * @param timer Timer object.
   */
  StateMachine(Timer &timer);

  /**
   * @brief Runs the state machine. Needs to be called in the main loop.
   */
  void run();
};

#endif // STATEMACHINE_H
