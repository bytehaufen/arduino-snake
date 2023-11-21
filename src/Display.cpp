#include "Display.h"

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

bool Display::printSerialized(const char *message) {
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
  if (message[i] == '\0') {
    i = 0;
    clockCounter = 0;
    return true;
  }
  return false;
}

void Display::printMenu(const char *heading, const char *menuItems[],
                        const uint8_t menuItemsCount,
                        const uint8_t selectedItem) {
  display.setTextColor(ST77XX_YELLOW);
  display.setTextSize(3);
  display.setCursor(20, 20);
  display.println(heading);
  display.setTextSize(MENU_TEXT_SIZE);
  display.setTextColor(ST77XX_WHITE);

  for (uint8_t i = 0; i < menuItemsCount; i++) {
    const uint16_t MENU_Y = MENU_Y_OFFSET + i * MENU_Y_SPACE;

    if (i == selectedItem) {
      display.drawRGBBitmap(
          MENU_X_OFFSET, MENU_Y, SnakeheadEast::image_data,
          SnakeheadEast::image_width, SnakeheadEast::image_height);

    } else {
      display.fillRect(MENU_X_OFFSET, MENU_Y, SnakeheadEast::image_width,
                       SnakeheadEast::image_height, ST77XX_BLACK);
    }
    display.setCursor(MENU_X_OFFSET + 30, MENU_Y);
    display.println(menuItems[i]);
  }
}

void Display::clear() { display.fillScreen(ST77XX_BLACK); }

void Display::drawGameBorder(const uint16_t x0, const uint16_t y0,
                             const uint16_t x1, const uint16_t y1) {
  const uint16_t COLOR = ST77XX_ORANGE;
  display.drawRect(x0, y0, x1, y1, COLOR);
}

void Display::printSimpleText(const char *message) {
  display.setCursor(20, 20);
  display.setTextColor(ST77XX_WHITE);
  display.setTextSize(4);
  display.println(message);
}

void Display::printScoreInfo(const uint16_t score, const bool init) {
  static uint16_t lastScore = 0;

  if (init) {
    display.setTextWrap(false);
    display.setCursor(30, 2);
    display.setTextColor(ST77XX_YELLOW, ST77XX_BLACK);
    display.setTextSize(2);
    display.print("Score: ");
  } else if (lastScore == score) {
    return;
  }

  display.setTextWrap(false);
  display.setCursor(105, 2);
  display.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  display.setTextSize(2);

  display.print(score);

  lastScore = score;
}

// TODO: @HadesTeufel refactor!
void Display::printScorePopup(const uint16_t score) {
  const uint8_t MARGIN = 5;
  const uint8_t PADDING = 5;
  uint16_t textWidth = 0;  // used to store the textWidth of the score sentence
  uint16_t textHeight = 0; // used to store the general textHeight of texts
  const uint8_t SCORE_TEXT_LENGTH = 5;
  char scoreText[SCORE_TEXT_LENGTH + 1];
  char scoreSentence[8 + SCORE_TEXT_LENGTH + 1] = "Score: ";
  itoa(score, scoreText, 10);
  strcat(scoreSentence, scoreText);

  display.getTextBounds(
      scoreSentence, 0, 0, 0, 0, &textWidth,
      &textHeight); // stores the calculated width and height in textX
  printScoreInfo(textWidth, true);
  display.fillRoundRect(
      SCREEN_WIDTH / 2 -
          (PADDING + MARGIN +
           textWidth / 2), // position in horizontal middle and go (half the
                           // textWidth + padding + margin) to the left
      (SCREEN_HEIGHT - 2 * PADDING - 2 * MARGIN - 3 * textHeight) /
          2, // position in vertical middle and go (3 halfs of the textHeight +
             // padding + margin) up
      2 * PADDING + 2 * MARGIN +
          textWidth, // rect width = textWidth + margin (left and right) +
                     // padding (left and right)
      3 * textHeight + 2 * MARGIN +
          2 * PADDING, // rect height = 3 * textHeight + margin (top and bottom)
                       // + padding (top + bottom)
      10, ST77XX_BLUE);
  display.drawRoundRect(
      SCREEN_WIDTH / 2 -
          (MARGIN + textWidth / 2), // position in horizontal middle and go
                                    // (helf the text + margin) to the left
      (SCREEN_HEIGHT - 2 * MARGIN - 3 * textHeight) /
          2, // position in vertical middle and go (3 halfs of the textHeight +
             // margin) up
      2 * MARGIN +
          textWidth, // rect width = textWidth + margin (left and right)
      3 * textHeight +
          2 * MARGIN, // rect height = 3 * textHeight + margin (top and bottom)
      10, ST77XX_WHITE);
  display.setTextColor(ST77XX_WHITE);
  display.setCursor(
      (SCREEN_WIDTH - textWidth) / 2,
      (SCREEN_HEIGHT - 3 * textHeight) / 2 +
          1); // +1 needs to be done in order to correctly include border width
  display.println("U died!");
  display.setCursor(
      (SCREEN_WIDTH - textWidth) / 2,
      (SCREEN_HEIGHT + textHeight) / 2 +
          1); // +1 needs to be done in order to correctly include border width
  display.print("Score: ");
  display.println(score);
}

void Display::drawSegment(const int8_t x, const int8_t y,
                          Display::SEGMENT segment) {
  uint16_t xPixel = Display::X_OFFSET + 2 + x * SEGMENT_SIZE;
  uint16_t yPixel = Display::Y_OFFSET + 2 + y * SEGMENT_SIZE;

  switch (segment) {
  case Display::SEGMENT::BODY:
    display.drawRGBBitmap(xPixel, yPixel, Snakebody::image_data,
                          Snakebody::image_width, Snakebody::image_height);
    break;
  case Display::SEGMENT::NONE:
    display.fillRect(xPixel, yPixel, SEGMENT_SIZE, SEGMENT_SIZE, ST77XX_BLACK);
    break;
  case Display::SEGMENT::HEAD_EAST:
    display.drawRGBBitmap(xPixel, yPixel, SnakeheadEast::image_data,
                          SnakeheadEast::image_width,
                          SnakeheadEast::image_height);
    break;
  case SEGMENT::HEAD_NORTH:
    display.drawRGBBitmap(xPixel, yPixel, SnakeheadNorth::image_data,
                          SnakeheadNorth::image_width,
                          SnakeheadNorth::image_height);
    break;
  case SEGMENT::HEAD_SOUTH:
    display.drawRGBBitmap(xPixel, yPixel, SnakeheadSouth::image_data,
                          SnakeheadSouth::image_width,
                          SnakeheadSouth::image_height);
    break;
  case SEGMENT::HEAD_WEST:
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

void Display::drawLogo(const uint16_t x, const uint16_t y) {
  display.drawRGBBitmap(x, y, SnakeheadWest::image_data,
                        SnakeheadWest::image_width,
                        SnakeheadWest::image_height);
}
