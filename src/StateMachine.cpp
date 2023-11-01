#ifndef STATEMCHINE_H
#define STATEMCHINE_H

#include "StateMachine.h"

#include <Arduino.h>

StateMachine::StateMachine() : currentState(State::intro) {}

void StateMachine::setState(State newState) { currentState = newState; }

State StateMachine::getState() { return currentState; }

void StateMachine::run() {
  static unsigned long delay = 1000;
  static unsigned long introLastMillis = millis();
  static unsigned long menuLastMillis = millis();
  static unsigned long gameLastMillis = millis();
  static unsigned long scoreLastMillis = millis();

  Serial.println((int)currentState);

  switch (currentState) {
  case State::intro:

    pinMode(13, HIGH);

    if (millis() - introLastMillis >= delay) {
      currentState = State::menu;
      menuLastMillis = millis();
    }
    break;

  case State::menu:

    pinMode(13, LOW);

    if (millis() - menuLastMillis >= delay) {
      currentState = State::game;
      gameLastMillis = millis();
    }
    break;

  case State::game:

    pinMode(13, HIGH);

    if (millis() - gameLastMillis >= delay) {
      scoreLastMillis = millis();
      currentState = State::score;
    }
    break;

  case State::score:

    pinMode(13, LOW);

    if (millis() - scoreLastMillis >= delay) {
      introLastMillis = millis();
      currentState = State::intro;
    }
    break;
  }
};

#endif // !STATEMCHINE_H
