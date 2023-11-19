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
public:
  /**
   * @brief Enum for the different difficulties.
   */
  enum class DIFFICULTY { EASY = 2, MEDIUM = 4, HARD = 8 };

private:
  /**
   * @brief two-dimensional array holding snake segments
   */
  uint8_t segment[Display::ROWS][Display::COLS];

  enum Element : uint8_t { NONE = 0, BODY = 1, FOOD = 8 };

  enum Direction : uint8_t {
    RIGHT = 128,
    UP = 64,
    LEFT = 32,
    DOWN = 16,
  };
  /**
   * @brief direction value;
   * @brief right: 128;
   * @brief up: 64;
   * @brief left: 32;
   * @brief down: 16;
   * @brief starting downwards
   */
  Direction direc = Direction::DOWN;

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
  /**
   * @brief Draw random food.
   * NOTE: All added foods have to be in this method.
   * @param x horizontal position
   * @param y vertical position
   */
  void placeRandomFood(uint8_t x, uint8_t y);

  // Game variables
  /**
   * length of snake
   */
  uint32_t snakedItems = 0;
  bool isFruitSpawned = false;
  uint16_t emptyFields = 0;
  DIFFICULTY selectedDifficulty;

public:
  static const uint8_t GAME_RUNNING = -1;
  Game(DIFFICULTY difficulty);
  /**
   * @brief Progress one step of the game.
   * @return Returns GAME_RUNNING if game is still running, otherwise returns
   * the reached score.
   */
  uint16_t run();
};

#endif // GAME_H
