#include "Game.h"
#include "Display.h"

Game::Game() {
  display = &Display::getInstance();
  display->clear();
  display->drawGameBorder(X_OFFSET, Y_OFFSET,
                          Display::SCREEN_WIDTH - 2 * X_OFFSET,
                          Display::SCREEN_HEIGHT - 2 * Y_OFFSET);

  headpos = {X_OFFSET + 100, Y_OFFSET + 100};
}

bool Game::run() {
  display->printInfo("Score " + String(snakedItems));

  display->drawSegment(headpos.x, headpos.y, 1);

  headpos.x += 16;

  return snakedItems++ < uint8_t(-1UL);
}
