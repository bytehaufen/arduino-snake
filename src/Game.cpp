#include "Game.h"
#include "Display.h"

Game::Game() {
  Display::getInstance().drawGameBorder(X_OFFSET, Y_OFFSET,
                                        Display::SCREEN_WIDTH - 2 * X_OFFSET,
                                        Display::SCREEN_HEIGHT - 2 * Y_OFFSET);
}

bool Game::run() {
  // NOTE: @Anton this is executed until testCounter reaches 8
  // FIX: Remove
  Serial.println("testCounter: " + String(testCounter));
  Display::getInstance().printSimpleText("testCounter: " + String(testCounter));
  Display::getInstance().drawSegment(50, 50, 1);

  return testCounter++ != 8;
}
