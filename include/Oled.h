#ifndef OLED_H
#define OLED_H

#include <Adafruit_GFX.h>
/* #include <Adafruit_SH1106.h> */
#include <Adafruit_ST7789.h>

class Oled {
private:
  Adafruit_ST7789 display;
  Oled();

public:
  // Singleton pattern
  static Oled &getInstance();

  bool printSerialized(const String &message);
  void printMenu(const String menuItems[], const uint8_t menuItemsCount,
                 const uint8_t selectedItem);
};

#endif // OLED_H
