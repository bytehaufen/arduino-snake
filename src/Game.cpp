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
      segment[i][j] = 0;
    }
  }
  // initialize snake head and tail position
  xHead = (uint8_t)Display::COLS / 2;
  yHead = (uint8_t)Display::ROWS / 2;
  xTail = xHead;
  yTail = yHead;
  segment[yHead][xHead] = 1 | 16;
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

  bAction = Input::getInstance().getPressedButton();
  switch (bAction) {
  case Input::BUTTON::UP:
    direc = Direction::UP;
    break;
  case Input::BUTTON::DOWN:
    direc = Direction::DOWN;
    break;
  case Input::BUTTON::LEFT:
    direc = Direction::LEFT;
    break;
  case Input::BUTTON::RIGHT:
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

  // positions and draws new head
  segment[yHead][xHead] |= static_cast<uint8_t>(direc);
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
  // check ...
  if (((segment[yHead][xHead] > 0) &&             // if snake hits itself
       ((xHead != xTail) || (yHead != yTail))) || // if the snake hits its tail
      (xHead >= Display::COLS) || // if the head is right of border
      (xHead < 0) ||              // if the head is left of border
      (yHead >= Display::ROWS) || // if the head is under border
      (yHead < 0))                // if the head is above border
    return false;
  // erase tail first, then draw new head
  display->drawSegment(xTail, yTail, 0);
  switch (segment[yTail][xTail] & 240) {
  case 128:
    segment[yTail][xTail++] = 0;
    break;
  case 64:
    segment[yTail--][xTail] = 0;
    break;
  case 32:
    segment[yTail][xTail--] = 0;
    break;
  case 16:
    segment[yTail++][xTail] = 0;
    break;
  default:
    display->printScore(String(segment[yTail][xTail] & 240) +
                        "DUDUDUUMM"); // debug :)
    return false;
    break;
  }
  segment[yHead][xHead] =
      1; // set value of new head to 1 -> no direction at that point
  display->drawSegment(xHead, yHead, 1); // draw new head

  display->printScore(String(++snakedItems));

  return true;
}

const uint16_t Game::randomXcoord() { return rand() % Display::COLS; }

const uint16_t Game::randomYcoord() { return rand() % Display::ROWS; }
