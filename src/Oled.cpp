#include "Oled.h"
#include "Adafruit_ST77xx.h"
#include "HardwareSerial.h"
#include "SPI.h"
#include "WString.h"

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 280

#define TFT_CS 10
#define TFT_DC 8
#define TFT_RST 9
#define TFT_MOSI 11
#define TFT_SCLK 13

Oled::Oled() : display( TFT_CS, TFT_DC, TFT_RST) {
  display.init(SCREEN_WIDTH, SCREEN_HEIGHT);
  display.setRotation(1);
  display.fillScreen(ST77XX_BLACK);
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
// TODO: change back to 200
const unsigned long CHARDELAY = 1;
bool Oled::printSerialized(const String &message) {
  static uint16_t i = 0;
  static unsigned long lastTime = 0;

  Serial.print(i);

  if (i == 0) {
    display.fillScreen(ST77XX_BLACK);
    display.setCursor(30, 100);
    display.setTextColor(ST77XX_WHITE);
    display.setTextSize(2);
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

void Oled::printMenu(const String menuItems[], const uint8_t menuItemsCount,
                     const uint8_t selectedItem) {
  const uint16_t X_OFFSET = 30;
  const uint16_t Y_OFFSET = 100;
  const uint16_t Y_SPACE = 20;

  /* display.fillScreen(ST77XX_BLACK); */
  display.fillRect(X_OFFSET, Y_OFFSET, X_OFFSET + 200, Y_OFFSET + 200, ST77XX_BLACK);
  display.setCursor(30, 50);
  display.setTextSize(2);

  for (uint8_t i = 0; i < menuItemsCount; i++) {
    display.setCursor(X_OFFSET, Y_OFFSET + i * Y_SPACE);
    if (i == selectedItem) {
      display.print("->  ");
      /* display.setTextColor(ST77XX_BLACK, ST77XX_WHITE); */
    } else {
      display.print("   ");
      /* display.setTextColor(ST77XX_WHITE, ST77XX_BLACK); */
    }
    display.println(menuItems[i]);
  }
  /* display.display(); */
}
