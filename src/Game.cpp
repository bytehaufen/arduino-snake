#include "Game.h"

Game::Game() {
  Serial.println("New Game.");
}

bool Game::run() {
  Serial.println("testCounter: " + String(testCounter));

  return testCounter++ != 8;
}
