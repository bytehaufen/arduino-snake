#include "Game.h"
#include "Display.h"
#include "Input.h"
#include "Timer.h"

Game::Game() {
  // initialize snake segment array
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      segment[i][j] = 0;
    }
  }
  // initialize snake head and tail position
  xHead = (uint8_t)cols / 2;
  yHead = (uint8_t)rows / 2;
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
  headpos = {Display::X_OFFSET + 100, Display::Y_OFFSET + 100};

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
    direc = 64;
    break;
  case Input::BUTTON::DOWN:
    direc = 16;
    break;
  case Input::BUTTON::LEFT:
    direc = 32;
    break;
  case Input::BUTTON::RIGHT:
    direc = 128;
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
  // positions and draws new head
  segment[yHead][xHead] |= direc;
  switch (direc) {
  case 128:
    xHead += 1;
    break;
  case 64:
    yHead -= 1;
    break;
  case 32:
    xHead -= 1;
    break;
  case 16:
    yHead += 1;
    break;
  default:
    return false;
    break;
  }
  // check ...
  if (((segment[yHead][xHead] > 0) &&             // if snake hits itself
       ((xHead != xTail) || (yHead != yTail))) || // if the snake hits its tail
      (xHead >= cols) || // if the head is right of border
      (xHead < 0) ||     // if the head is left of border
      (yHead >= rows) || // if the head is under border
      (yHead < 0))  // if the head is above border
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
    display->printScore(String(segment[yTail][xTail] & 240) + "DUDUDUUMM"); // debug :)
    return false;
    break;
  }
  segment[yHead][xHead] = 1; // set value of new head to 1 -> no direction at that point
  display->drawSegment(xHead, yHead, 1); // draw new head

  display->printScore(String(++snakedItems));

  return true;
}
