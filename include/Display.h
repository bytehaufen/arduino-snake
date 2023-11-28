/**
 * @file Display.h
 * @brief Class to interact with Oled Display.
 */

#ifndef OLED_H
#define OLED_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#include "images/Snakebody.h"
#include "images/SnakeheadEast.h"
#include "images/SnakeheadNorth.h"
#include "images/SnakeheadSouth.h"
#include "images/SnakeheadWest.h"

/**
 * @brief Singleton class to interact with Oled Display.
 */
class Display {
private:
  // Display pins
  const uint8_t TFT_CS = 10;
  const uint8_t TFT_DC = 8;
  const uint8_t TFT_RST = 9;
  const uint8_t TFT_MOSI = 11;
  const uint8_t TFT_SCLK = 13;
  // Delay for Display::printSerialized() -> divider for game clock
  const uint8_t CLK_DIVIDER = 2;
  // Constants for Display::printMenu()
  const uint16_t MENU_X_OFFSET = 50;
  const uint16_t MENU_Y_OFFSET = 80;
  const uint16_t MENU_Y_SPACE = 30;
  const uint8_t MENU_TEXT_SIZE = 2;

  /**
   * @brief Private constructor.
   */
  Display();

  // Display object
  Adafruit_ST7789 display;

public:
  // Display constraints
  /**
   * @brief width of the screen
   */
  static const uint16_t SCREEN_WIDTH = 280;
  /**
   * @brief height of the screen
   */
  static const uint16_t SCREEN_HEIGHT = 240;
  /**
   * @brief height and width of a snake segment
   */
  static const uint8_t SEGMENT_SIZE = 16;
  /**
   * @brief minimal vertical offset of the game area
   **/
  static const uint16_t MIN_X_OFFSET = 20;
  /**
   * @brief horizontal offset of the game area
   */
  static constexpr uint16_t X_OFFSET =
      (SCREEN_WIDTH -
       (SCREEN_WIDTH - 2 * MIN_X_OFFSET) / SEGMENT_SIZE * SEGMENT_SIZE) /
      2;
  /**
   * @brief minimal horizontal offset of the game area
   */
  static const uint16_t MIN_Y_OFFSET = 20;
  /**
   * @brief vertical offset of the game area
   */
  static constexpr uint16_t Y_OFFSET =
      (SCREEN_HEIGHT -
       (SCREEN_HEIGHT - 2 * MIN_Y_OFFSET) / SEGMENT_SIZE * SEGMENT_SIZE) /
      2;

  /**
   * @brief number of rows
   */
  static constexpr uint8_t ROWS = (SCREEN_HEIGHT - 2 * Y_OFFSET) / SEGMENT_SIZE;

  /**
   * @brief number of columns
   */
  static constexpr uint8_t COLS = (SCREEN_WIDTH - 2 * X_OFFSET) / SEGMENT_SIZE;

  /**
   * @brief Get the singleton instance of Display.
   * @return The singleton instance of Display.
   */
  static Display &getInstance();

  /**
   * @brief Print a message char by char on the display.
   * @param message The message to print.
   * @return True if the message is done printing, false otherwise.
   */
  bool printSerialized(const char *message);

  /**
   * @brief Enum for drawSegment()
   */
  enum class SEGMENT {
    NONE, // Clear
    BODY,
    HEAD_NORTH,
    HEAD_SOUTH,
    HEAD_EAST,
    HEAD_WEST,
  };
  /**
   * @brief Draws a segment at given coordinates with given color.
   * @param x X coordinate of rectangle.
   * @param y Y coordinate of rectangle.
   * @param segment Segment to draw. Type of enum Segments.
   */
  void drawSegment(const int8_t x, const int8_t y, SEGMENT segment);

  /**
   * @brief Print a menu on the display.
   * @param menuItems Menu items to be printed.
   * @param menuItemsCount Number of menu items.
   * @param selectedItem Selected menu item.
   */
  void printMenu(const char *heading, const char *menuItems[],
                 const uint8_t menuItemsCount, const uint8_t selectedItem);

  /**
   * @brief Clear the display.
   */
  void clear();

  /**
   * @brief Draw the game border on the display.
   */
  void drawGameBorder();

  /**
   * @brief Print a simple text on the display.
   * @param message The message to print.
   */
  void printSimpleText(const char *message);

  /**
   * @brief Print information on the display.
   * @param message The message to print.
   * @param init True if the message is the first to be printed, false
   * otherwise.
   */
  void printScoreInfo(const uint16_t score, const bool init = false);

  /**
   * @brief Print score centered on the display.
   * @param score The score to print.
   */
  void printScorePopup(const uint16_t score);

  /**
   * @brief Draw an image on the display.
   * @param x X field point.
   * @param y Y field point.
   * @param image_data Pointer to image data.
   * @param w Image width.
   * @param h Image height.
   */
  void drawFood(const uint8_t x, const uint8_t y, const uint16_t *image_data,
                const uint16_t w, const uint16_t h);
  /**
   * @brief Draw the logo on the display.
   * @param x Point on the x axis.
   * @param y Point on the y axis.
   */
  void drawLogo(const uint16_t x, const uint16_t y);
};

#endif // OLED_H
