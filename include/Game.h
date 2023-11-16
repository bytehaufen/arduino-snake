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
  /**
   * @brief two-dimensional array holding snake segments
   */
  uint8_t segment[Display::ROWS][Display::COLS];

  /**
   * @brief direction value;
   * @brief right: 128;
   * @brief up: 64;
   * @brief left: 32;
   * @brief down: 16;
   * @brief starting downwards
   */
  uint8_t direc = 16;
  // current position values
  /**
   * @brief current horizontal position of the snake head
   */
  int8_t xHead = 0;
  /**
   * @brief current vertical position of the snake head
   */
  int8_t yHead = 0;
  /**
   * @brief current horizontal position of the snake tail
   */
  int8_t xTail = 0;
  /**
   * @brief current vertical position of the snake tail
   */
  int8_t yTail = 0;
  /**
   * @brief Pointer to Display instance for easy access
   */
  Display *display;

  // Game variables
  /**
   * length of snake
   */
  uint32_t snakedItems = 0;

public:
  Game();
  /**
   * @brief Progress one step of the game.
   * @return True if game is running, false otherwise
   */
  bool run();
  /**
   * @brief Creates a random X coordinate.
   * @return The random X coordinate.
   */
  const uint16_t randomXcoord();
  /**
   * @brief Creates a random Y coordinate.
   * @return The random Y coordinate.
   */
  const uint16_t randomYcoord();
};

#endif // GAME_H
