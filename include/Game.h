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
  static const uint8_t rows = (uint8_t)(Display::SCREEN_HEIGHT - 2 * Display::Y_OFFSET - 4)/Display::SEGMENT_SIZE;
  static const uint8_t cols = (uint8_t)(Display::SCREEN_WIDTH - 2 * Display::X_OFFSET - 4)/Display::SEGMENT_SIZE;

  /**
   * @brief two-dimensional array holding snake segments
  */
  uint8_t segment[rows][cols];

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

  /**
   * @brief start position of snake; just for testing purposes -> delete later
  */
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
