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

  /**
   * @brief two-dimensional array holding snake segments
  */
  uint8_t segment[(uint8_t)(Display::SCREEN_WIDTH - 2 * Display::X_OFFSET - 4)/Display::SEGMENT_SIZE][(uint8_t)(Display::SCREEN_HEIGHT - 2 * Display::Y_OFFSET - 4)/Display::SEGMENT_SIZE];

  // direction values; starting downwards
  /**
   * @brief current step size along the horizontal axis
  */
  int8_t xDirec = 0;
  /**
   * @brief current step size along the vertical axis
  */
  int8_t yDirec = 1;
  // current position values
  /**
   * @brief current horizontal position of the snake head
  */
  int8_t xPos = 0;
  /**
   * @brief current vertical position of the snake head
  */
  int8_t yPos = 1;
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
