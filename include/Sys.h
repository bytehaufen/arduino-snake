#ifndef SYSTEM_H
#define SYSTEM_H

#include <Arduino.h>

class Sys {
private:
  const uint8_t RIGHT_PIN = 10;
  const uint8_t UP_PIN = 11;
  const uint8_t LEFT_PIN = 12;
  const uint8_t DOWN_PIN = 13;
  bool middleButtonPressed;
  bool rightButtonPressed;
  bool upButtonPressed;
  bool downButtonPressed;
  bool leftButtonPressed;
  bool joystickConsumed;
  Sys();

public:
  enum class BUTTON { UP, DOWN, LEFT, RIGHT, MIDDLE, NONE };

  static Sys &getInstance();
  void run();
  BUTTON getPressedButton();
  void consumeJoystick();

  static void printI2Cdevices();
};

#endif // SYSTEM_H
