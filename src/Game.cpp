#include "Game.h"
#include "Display.h"
#include "Input.h"
#include "Timer.h"

Game::Game() {
  for (int i = 0; i<(uint8_t)(Display::SCREEN_WIDTH - 2 * Display::X_OFFSET - 4)/Display::SEGMENT_SIZE; i++) {
    for (int j = 0; j < (uint8_t)(Display::SCREEN_HEIGHT - 2 * Display::Y_OFFSET - 4)/Display::SEGMENT_SIZE; j++) {
      segment[i][j] = 0;
    }
  }
  xHead = (uint8_t)(Display::SCREEN_WIDTH - 2 * Display::X_OFFSET - 4)/Display::SEGMENT_SIZE/2;
  yHead = (uint8_t)(Display::SCREEN_HEIGHT - 2 * Display::Y_OFFSET - 4)/Display::SEGMENT_SIZE/2;
  xTail = xHead;
  yTail = yHead;
  segment[xHead][yHead] = 1;
  display = &Display::getInstance();
  display->clear();
  display->drawGameBorder(Display::X_OFFSET, Display::Y_OFFSET,
                          Display::SCREEN_WIDTH - 2 * Display::X_OFFSET,
                          Display::SCREEN_HEIGHT - 2 * Display::Y_OFFSET);
  display->drawSegment(xHead, yHead, 1);
  headpos = {Display::X_OFFSET + 100, Display::Y_OFFSET + 100};
}

bool Game::run() {
  display->printInfo("Score " + String(snakedItems));
  Input::BUTTON bAction;
  uint8_t clk = 0;
  while (clk++ < 10) {
    bAction = Input::getInstance().getPressedButton();
    switch (bAction) {
    case Input::BUTTON::UP:
      xDirec = 0;
      yDirec = -1;
      break;
    case Input::BUTTON::DOWN:
      xDirec = 0;
      yDirec = 1;
      break;
    case Input::BUTTON::LEFT:
      xDirec = -1;
      yDirec = 0;
      break;
    case Input::BUTTON::RIGHT:
      xDirec = 1;
      yDirec = 0;
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
  }
  xHead += xDirec;
  yHead += yDirec;
  display->drawSegment(xHead, yHead, 1);
  display->drawSegment(xTail, yTail, 0);
  xTail = xHead;
  yTail = yHead;

  return true;
}