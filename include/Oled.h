#ifndef OLED_H
#define OLED_H

#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

class Oled {
private:
  Adafruit_SH1106 display;
  Oled();

public:
  // Singleton pattern
  static Oled &getInstance();

  bool printSerialized(const String &message);
  /* void printMenu(const char *menuItems, const uint8_t size, const uint8_t selectedItem); */
  void printMenu(const String menuItems[], const uint8_t size, const uint8_t selectedItem);
};

#endif // OLED_H
