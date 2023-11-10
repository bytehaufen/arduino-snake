#include "Display.h"

// Initialize display
Display::Display() : display(TFT_CS, TFT_DC, TFT_RST) {
  display.init(SCREEN_WIDTH, SCREEN_HEIGHT);
  display.setRotation(1);
  display.fillScreen(ST77XX_BLACK);
}

Display &Display::getInstance() {
  static Display instance;
  return instance;
}

bool Display::printSerialized(const String &message) {
  static uint16_t i = 0;
  static unsigned long lastTime = 0;

  // If first iteration
  if (i == 0) {
    display.fillScreen(ST77XX_BLACK);
    display.setCursor(20, 20);
    display.setTextColor(ST77XX_WHITE);
    display.setTextSize(4);
  }

  // If time has passed
  if (millis() - lastTime >= CHARDELAY) {
    display.print(message[i]);
    lastTime = millis();

    // If last character is printed return true
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
  display.setTextSize(MENU_TEXT_SIZE);

  for (uint8_t i = 0; i < menuItemsCount; i++) {
    display.setCursor(MENU_X_OFFSET, MENU_Y_OFFSET + i * MENU_Y_SPACE);
    // If selected item black text and white background, otherwise white text
    // and black background
    if (i == selectedItem) {
      display.setTextColor(ST77XX_BLACK, ST77XX_WHITE);
    } else {
      display.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    }
    display.println(menuItems[i]);
  }
}

void Display::clear() { display.fillScreen(ST77XX_BLACK); }
