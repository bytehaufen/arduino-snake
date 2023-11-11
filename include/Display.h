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
  // Delay for Display::printSerialized()
  const unsigned long CHARDELAY = 200;
  // Constants for Display::printMenu()
  const uint16_t MENU_X_OFFSET = 100;
  const uint16_t MENU_Y_OFFSET = 130;
  const uint16_t MENU_Y_SPACE = 35;
  const uint8_t MENU_TEXT_SIZE = 3;
  const uint8_t SEGMENT_SIZE = 16;
  /**
   * @brief Private constructor.
   */
  Display();

  // Display object
  Adafruit_ST7789 display;

public:
  // Display constraints
  static const uint16_t SCREEN_WIDTH = 280;
  static const uint16_t SCREEN_HEIGHT = 240;
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
   * @brief Draws a segment at given coordinates with given color.
   * @param x X coordinate of rectangle.
   * @param y Y coordinate of rectangle.
   * @param c Bool value representing the color of the segment to draw; either black (0) or white (1).
   */
  void drawSegment(const int16_t x, const int16_t y, bool c);
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
};

#endif // OLED_H
