#include "Game.h"
#include "Display.h"
#include "Input.h"
#include "Timer.h"
#include "images/Ba.h"
#include "images/Snakehead.h"
#include "images/Strawberry.h"

Game::Game() {
  // initialize snake segment array
  for (int i = 0; i < Display::ROWS; i++) {
    for (int j = 0; j < Display::COLS; j++) {
      segment[i][j] = Element::NONE;
    }
  }
  // initialize snake head and tail position
  xHead = (uint8_t)Display::COLS / 2;
  yHead = (uint8_t)Display::ROWS / 2;
  xTail = xHead;
  yTail = yHead;
  segment[yHead][xHead] = Element::HEAD | Element::TAIL | Direction::DOWN;
  // set up display
  display = &Display::getInstance();
  display->clear();
  display->drawGameBorder(Display::X_OFFSET, Display::Y_OFFSET,
                          Display::SCREEN_WIDTH - 2 * Display::X_OFFSET,
                          Display::SCREEN_HEIGHT - 2 * Display::Y_OFFSET);
  display->drawSegment(xHead, yHead, 1);

  display->printScore("0", true);
}

bool Game::run() {
  Input::BUTTON bAction;
  static uint8_t clk = 0;

  // Skip 100 clk cycles -> execute every 1s
  if (clk++ < 100) {
    return true;
  }
  clk = 0;

  // Read input and set direction
  bAction = Input::getInstance().getPressedButton();
  switch (bAction) {
  case Input::BUTTON::UP:
    if (direc == Direction::DOWN) {
      break;
    }
    direc = Direction::UP;
    break;
  case Input::BUTTON::DOWN:
    if (direc == Direction::UP) {
      break;
    }
    direc = Direction::DOWN;
    break;
  case Input::BUTTON::LEFT:
    if (direc == Direction::RIGHT) {
      break;
    }
    direc = Direction::LEFT;
    break;
  case Input::BUTTON::RIGHT:
    if (direc == Direction::LEFT) {
      break;
    }
    direc = Direction::RIGHT;
    break;
  case Input::BUTTON::MIDDLE:
    return false;
    break;
  case Input::BUTTON::NONE:
    break;
  default:
    return false;
    break;
  }
  // NOTE: test to display bitmap
  display->drawFood(randomXcoord(), randomYcoord(), Strawberry::image_data,
                    Strawberry::image_width, Strawberry::image_height);
  display->drawFood(randomXcoord(), randomYcoord(), Ba::image_data,
                    Ba::image_width, Ba::image_height);
  display->drawFood(randomXcoord(), randomYcoord(), Snakehead::image_data,
                    Snakehead::image_width, Snakehead::image_height);

  // Delete old head from array
  segment[yHead][xHead] &= ~Element::HEAD;
  // Set direction of last segment to point to new head
  segment[yHead][xHead] |= direc;
  // Set position for new head
  switch (direc) {
  case Direction::RIGHT:
    xHead += 1;
    break;
  case Direction::UP:
    yHead -= 1;
    break;
  case Direction::LEFT:
    xHead -= 1;
    break;
  case Direction::DOWN:
    yHead += 1;
    break;
  default:
    return false;
    break;
  }

  // Check snake dies
  if (((segment[yHead][xHead] & Element::BODY) ||
       (segment[yHead][xHead] & Element::HEAD)) || // if snake hits itself
                                                   // TODO: remove outcommented?
      /* ((xHead != xTail) || (yHead != yTail)) || // if the snake hits its tail
       */
      (xHead >= Display::COLS) || // if the head is right of border
      (xHead < 0) ||              // if the head is left of border
      (yHead >= Display::ROWS) || // if the head is under border
      (yHead < 0)) {              // if the head is above border

    // TODO: Implement Game finished
    return false;
  }

  // Erase tail
  display->drawSegment(xTail, yTail, 0);

  // Filter direction and delete tail element from array
  switch (segment[yTail][xTail] & (Direction::RIGHT | Direction::UP |
                                   Direction::LEFT | Direction::DOWN)) {
  case Direction::RIGHT:
    segment[yTail][xTail++] = 0;
    break;
  case Direction::UP:
    segment[yTail--][xTail] = 0;
    break;
  case Direction::LEFT:
    segment[yTail][xTail--] = 0;
    break;
  case Direction::DOWN:
    segment[yTail++][xTail] = 0;
    break;
  default:
    return false;
    break;
  }
  // TODO: Check anton
  /* segment[yHead][xHead] = */
  /*     1; // set value of new head to 1 -> no direction at that point */
  segment[yHead][xHead] = direc | Element::HEAD;

  display->drawSegment(xHead, yHead, 1); // draw new head

  display->printScore(String(++snakedItems));

  return true;
}

const uint16_t Game::randomXcoord() { return rand() % Display::COLS; }

const uint16_t Game::randomYcoord() { return rand() % Display::ROWS; }
