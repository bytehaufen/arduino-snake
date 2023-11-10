#ifndef OLED_H
#define OLED_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

class Display {
private:
  const uint16_t SCREEN_WIDTH = 240;
  const uint16_t SCREEN_HEIGHT = 280;
  // Display pins
  const uint8_t TFT_CS = 10;
  const uint8_t TFT_DC = 8;
  const uint8_t TFT_RST = 9;
  const uint8_t TFT_MOSI = 11;
  const uint8_t TFT_SCLK = 13;

  Adafruit_ST7789 display;
  Display();

public:
  static Display &getInstance();

  bool printSerialized(const String &message);
  void printMenu(const String menuItems[], const uint8_t menuItemsCount,
                 const uint8_t selectedItem);
  void clear();
};

#endif // OLED_H
