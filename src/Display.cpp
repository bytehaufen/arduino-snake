#include "Display.h"
#include "Adafruit_ST77xx.h"

// Initialize display
Display::Display() : display(TFT_CS, TFT_DC, TFT_RST) {
  display.init(SCREEN_HEIGHT,
               SCREEN_WIDTH); // height, width -> cause of rotation
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

void Display::drawGameBorder(const uint16_t x0, const uint16_t y0,
                             const uint16_t x1, const uint16_t y1) {
  const uint16_t COLOR = ST77XX_ORANGE;
  display.drawRect(x0, y0, x1, y1, COLOR);
}

void Display::printSimpleText(const String &message) {
  display.setCursor(20, 20);
  display.setTextColor(ST77XX_WHITE);
  display.setTextSize(4);
  display.println(message);
}
