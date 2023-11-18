/**
 * @file Display.h
 * @brief Class to interact with Oled Display.
 */

#ifndef OLED_H
#define OLED_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

/**
 * @brief Singleton class to interact with Oled Display.
 */
class Display {
private:
  // Display pins
  // TODO: rm arduino behavior
  const uint8_t TFT_CS = 10;
  const uint8_t TFT_DC = 8;
  const uint8_t TFT_RST = 9;
  const uint8_t TFT_MOSI = 11;
  const uint8_t TFT_SCLK = 13;
  // Delay for Display::printSerialized() -> divider for game clock
  const uint8_t CLK_DIVIDER = 2;
  // Constants for Display::printMenu()
  const uint16_t MENU_X_OFFSET = 100;
  const uint16_t MENU_Y_OFFSET = 130;
  const uint16_t MENU_Y_SPACE = 35;
  const uint8_t MENU_TEXT_SIZE = 3;

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
   * @brief heigt and width of a snake segment
   */
  static const uint8_t SEGMENT_SIZE = 16;
  /**
   * @brief horizontal offset of the game area
   */
  static const uint16_t X_OFFSET = 20;
  /**
   * @brief vertical offset of the game area
   */
  static const uint16_t Y_OFFSET = 20;

  /**
   * @brief number of rows
   */
  static constexpr uint8_t ROWS =
      (uint8_t)(Display::SCREEN_HEIGHT - 2 * Display::Y_OFFSET - 4) /
      Display::SEGMENT_SIZE;

  /**
   * @brief number of columns
   */
  static constexpr uint8_t COLS =
      (uint8_t)(Display::SCREEN_WIDTH - 2 * Display::X_OFFSET - 4) /
      Display::SEGMENT_SIZE;
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
  bool printSerialized(const String &message);

  /**
   * @brief Enum for drawSegment()
   */
  enum class Segments {
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
  void drawSegment(const int8_t x, const int8_t y, Segments segment);

  /**
   * @brief Print a menu on the display.
   * @param menuItems Menu items to be printed.
   * @param menuItemsCount Number of menu items.
   * @param selectedItem Selected menu item.
   */
  void printMenu(const String menuItems[], const uint8_t menuItemsCount,
                 const uint8_t selectedItem);

  /**
   * @brief Clear the display.
   */
  void clear();

  /**
     @brief    Draw a line
     @param    x0  Start point x coordinate
     @param    y0  Start point y coordinate
     @param    x1  End point x coordinate
     @param    x2  End point y coordinate
     @param    color 16-bit 5-6-5 Color to draw with
  */
  void drawGameBorder(const uint16_t x0, const uint16_t y0, const uint16_t x1,
                      const uint16_t y1);

  /**
   * @brief Print a simple text on the display.
   * @param message The message to print.
   */
  void printSimpleText(const String &message);

  /** @brief Print information on the display.
   * @param message The message to print.
   * @param init True if the message is the first to be printed, false
   * otherwise.
   */
  void printScore(const String &score, const bool init = false);

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
};

#endif // OLED_H
