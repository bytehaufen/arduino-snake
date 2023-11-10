/**
 * @file Game.h
 * @brief Game class file.
 */

#ifndef GAME_H
#define GAME_H

#include <Arduino.h>

/**
 * @class Game
 * @brief Class that holds the game loop.
 */
class Game {
private:
  // NOTE: Variable to demonstrate save of state in class for continuously
  // called method (bool run())
  // FIX: Remove
  uint8_t testCounter = 0;

public:
  Game();
  /**
   * @brief Progress one step of the game.
   * @return True if game is running, false otherwise
   */
  bool run();
};

#endif // GAME_H
