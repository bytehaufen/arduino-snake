#ifndef SYSTEM_H
#define SYSTEM_H

#include <Arduino.h>


class Sys {
private:
  static const uint8_t RIGHT_PIN = 10;
  static const uint8_t UP_PIN = 11;
  static const uint8_t LEFT_PIN = 12;
  static const uint8_t DOWN_PIN = 13;
  bool middleButtonPressed;
  bool rightButtonPressed;
  bool upButtonPressed;
  bool downButtonPressed;
  bool leftButtonPressed;

public:
  enum class BUTTON { UP, DOWN, LEFT, RIGHT, MIDDLE, NONE };

  Sys();
  void run();
  BUTTON getPressedButton();

  static void printi2cdevices();
};

#endif // SYSTEM_H
