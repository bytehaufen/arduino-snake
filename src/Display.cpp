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
  static uint8_t clockCounter = 0;

  // If first iteration
  if (i == 0) {
    display.fillScreen(ST77XX_BLACK);
    display.setCursor(20, 20);
    display.setTextColor(ST77XX_WHITE);
    display.setTextSize(4);
  }

  // Reduce clock for slower printing
  if (clockCounter++ % CLK_DIVIDER == 0) {
    // Print next character and increment index
    display.print(message[i++]);
  }
  // If last character is printed return true
  if (i == message.length()) {
    i = 0;
    clockCounter = 0;
    return true;
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

void Display::printScore(const String &score, const bool init) {
  static String lastScore = "";

  if (lastScore == score) {
    return;
  }

  if (init) {
    display.setTextWrap(false);
    display.setCursor(30, 2);
    display.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    display.setTextSize(2);
    display.print("Score: ");
  }

  display.setTextWrap(false);
  display.setCursor(105, 2);
  display.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  display.setTextSize(2);

  display.print(score);

  lastScore = score;
}

void Display::drawSegment(const int8_t x, const int8_t y, bool c) {
  if (c) {
    display.fillRect(Display::X_OFFSET + 2 + x * SEGMENT_SIZE,
                     Display::Y_OFFSET + 2 + y * SEGMENT_SIZE, SEGMENT_SIZE,
                     SEGMENT_SIZE, 0xFFFFU);
  } else {
    display.fillRect(Display::X_OFFSET + 2 + x * SEGMENT_SIZE,
                     Display::Y_OFFSET + 2 + y * SEGMENT_SIZE, SEGMENT_SIZE,
                     SEGMENT_SIZE, 0);
  }
}
