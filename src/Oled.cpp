#include "Oled.h"
#include "HardwareSerial.h"
#include "WString.h"

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Oled::Oled() : display(4) {
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}

Oled &Oled::getInstance() {
  static Oled instance;
  return instance;
}

/*
 * Prints a message char by char
 * Needs to be called continuously
 * Returns true if all chars are printed
 *
 * @param message the message to be printed
 * @return true if all chars are printed
 */
const unsigned long CHARDELAY = 200;
bool Oled::printSerialized(const String &message) {
  static uint16_t i = 0;
  static unsigned long lastTime = 0;

  /* Serial.print(i); */

  if (i == 0) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextColor(WHITE);
    display.setTextSize(2);
  }

  if (millis() - lastTime >= CHARDELAY) {
    display.print(message[i]);
    display.display();
    lastTime = millis();

    if (i == message.length() - 1) {
      i = 0;
      return true;
    }
    i++;
  }

  return false;
}

/* void Oled::printMenu(const char *menuItems, const uint8_t itemCount, */
/*                      const uint8_t selectedItem) { */
  void Oled::printMenu(const String menuItems[], const uint8_t size, const uint8_t selectedItem) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);

  for (uint8_t i = 0; i < size; i++) {
    if (i == selectedItem) {
      display.setTextColor(WHITE, BLACK);
    } else {
      display.setTextColor(BLACK, WHITE);
    }
    display.println(menuItems[i]);
  }
  display.display();
}
