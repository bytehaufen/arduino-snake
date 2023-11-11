/**
 * @file StateMachine.h
 * @brief Class that handles the state of the game.
 */

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "Display.h"
#include "Game.h"
#include "Input.h"

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
  enum class STATE { INIT, INTRO, MENU, GAME, SCORE };
  /**
   * @brief Enum for the different menu items.
   */
  enum class MENU_ITEM { START = 0, SCORE = 1 };
  // Holds the active state
  STATE currentState;
  // StateMachine time constants
  const unsigned long DELAY = 1000;
  const unsigned long DELAY_INIT = 1000;
  // TODO: change back to 300
  const unsigned long DELAY_TO_MENU = 1;

  // Menu items
  static const uint8_t MENU_ITEMS_COUNT = 2;
  const String MENU_ITEMS[MENU_ITEMS_COUNT];
  // Pointer to game
  Game *game;

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

public:
  /**
   * @brief Constructor for the StateMachine.
   */
  StateMachine();

  /**
   * @brief Runs the state machine. Needs to be called in the main loop.
   */
  void run();
};

#endif // STATEMACHINE_H
