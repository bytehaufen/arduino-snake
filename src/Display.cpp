#include "Display.h"
#include "Adafruit_ST77xx.h"
#include "HardwareSerial.h"
#include "SPI.h"
#include "WString.h"

Display::Display() : display(TFT_CS, TFT_DC, TFT_RST) {
  display.init(SCREEN_WIDTH, SCREEN_HEIGHT);
  display.setRotation(1);
  display.fillScreen(ST77XX_BLACK);
}

Display &Display::getInstance() {
  static Display instance;
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
bool Display::printSerialized(const String &message) {
  static uint16_t i = 0;
  static unsigned long lastTime = 0;

  if (i == 0) {
    display.fillScreen(ST77XX_BLACK);
    display.setCursor(20, 20);
    display.setTextColor(ST77XX_WHITE);
    display.setTextSize(4);
    /* display.display(); */
  }

  if (millis() - lastTime >= CHARDELAY) {
    display.print(message[i]);
    /* display.display(); */
    lastTime = millis();

    if (i == message.length() - 1) {
      i = 0;
      return true;
    }
    i++;
  }

  return false;
}

void Display::printMenu(const String menuItems[], const uint8_t menuItemsCount,
                     const uint8_t selectedItem) {
  const uint16_t X_OFFSET = 100;
  const uint16_t Y_OFFSET = 130;
  const uint16_t Y_SPACE = 30;

  display.fillRect(X_OFFSET, Y_OFFSET, X_OFFSET + 200, Y_OFFSET + 200,
                   ST77XX_BLACK);
  display.setTextSize(3);

  for (uint8_t i = 0; i < menuItemsCount; i++) {
    display.setCursor(X_OFFSET, Y_OFFSET + i * Y_SPACE);
    if (i == selectedItem) {
      display.setTextColor(ST77XX_BLACK, ST77XX_WHITE);
    } else {
      display.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    }
    display.println(menuItems[i]);
  }
}

void Display::clear() { display.fillScreen(ST77XX_BLACK); }
