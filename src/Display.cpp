#include "Display.h"
#include "Adafruit_ST77xx.h"
#include "images/Snakebody.h"
#include "images/SnakeheadEast.h"
#include "images/SnakeheadNorth.h"
#include "images/SnakeheadSouth.h"
#include "images/SnakeheadWest.h"

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
    display.setCursor(20, 80);
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

void Display::printMenu(const String &heading, const String menuItems[],
                        const uint8_t menuItemsCount,
                        const uint8_t selectedItem) {
  display.setTextSize(MENU_TEXT_SIZE);
  display.setTextColor(ST77XX_YELLOW);
  display.setCursor(20, 20);
  display.println(heading);

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

void Display::printScoreInfo(const String &score, const bool init) {
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

// TODO: @HadesTeufel refactor!
void Display::printScorePopup(const String &score) {
  const uint8_t MARGIN = 5;
  const uint8_t PADDING = 5;
  display.fillRoundRect(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 3,
                        SCREEN_HEIGHT / 4, 10, ST77XX_BLUE);
  display.drawRoundRect(SCREEN_WIDTH / 3 + MARGIN, SCREEN_HEIGHT / 4 + MARGIN,
                        SCREEN_WIDTH / 3 - 2 * MARGIN,
                        SCREEN_HEIGHT / 4 - 2 * MARGIN, 10, ST77XX_WHITE);
  display.setCursor(SCREEN_WIDTH / 3 + PADDING + MARGIN, SCREEN_HEIGHT / 2);
  display.setTextColor(ST77XX_WHITE);
  display.println("Your Score: " + score);
}

void Display::drawSegment(const int8_t x, const int8_t y,
                          Display::Segments segment) {
  uint16_t xPixel = Display::X_OFFSET + 2 + x * SEGMENT_SIZE;
  uint16_t yPixel = Display::Y_OFFSET + 2 + y * SEGMENT_SIZE;

  switch (segment) {
  case Display::Segments::BODY:
    display.drawRGBBitmap(xPixel, yPixel, Snakebody::image_data,
                          Snakebody::image_width, Snakebody::image_height);
    break;
  case Display::Segments::NONE:
    display.fillRect(xPixel, yPixel, SEGMENT_SIZE, SEGMENT_SIZE, ST77XX_BLACK);
    break;
  case Display::Segments::HEAD_EAST:
    display.drawRGBBitmap(xPixel, yPixel, SnakeheadEast::image_data,
                          SnakeheadEast::image_width,
                          SnakeheadEast::image_height);
    break;
  case Segments::HEAD_NORTH:
    display.drawRGBBitmap(xPixel, yPixel, SnakeheadNorth::image_data,
                          SnakeheadNorth::image_width,
                          SnakeheadNorth::image_height);
    break;
  case Segments::HEAD_SOUTH:
    display.drawRGBBitmap(xPixel, yPixel, SnakeheadSouth::image_data,
                          SnakeheadSouth::image_width,
                          SnakeheadSouth::image_height);
    break;
  case Segments::HEAD_WEST:
    display.drawRGBBitmap(xPixel, yPixel, SnakeheadWest::image_data,
                          SnakeheadWest::image_width,
                          SnakeheadWest::image_height);
    break;
  }
}

void Display::drawFood(const uint8_t x, const uint8_t y,
                       const uint16_t *image_data, const uint16_t w,
                       const uint16_t h) {
  display.drawRGBBitmap(Display::X_OFFSET + 2 + x * SEGMENT_SIZE,
                        Display::Y_OFFSET + 2 + y * SEGMENT_SIZE, image_data,
                        16, 16);
}

void Display::drawLogo(const int16_t x, const int16_t y) {
  display.drawRGBBitmap(x, y, SnakeheadWest::image_data,
                        SnakeheadWest::image_width,
                        SnakeheadWest::image_height);
}
