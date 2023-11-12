/**
 * @file Game.h
 * @brief Game class file.
 */

#ifndef GAME_H
#define GAME_H

#include "Display.h"

/**
 * @class Game
 * @brief Class that holds the game loop.
 */
class Game {
private:
  // TODO: Only for test -> maybe a complete class for the snake
  struct Headpos {
    uint16_t x;
    uint16_t y;
  };

  // Offsets for game area
  const uint16_t X_OFFSET = 20;
  const uint16_t Y_OFFSET = 20;

  // Pointer to Display instance for easy access
  Display *display;

  // Game variables
  uint32_t snakedItems = 0;

  Headpos headpos;

public:
  Game();
  /**
   * @brief Progress one step of the game.
   * @return True if game is running, false otherwise
   */
  bool run();
};

#endif // GAME_H
