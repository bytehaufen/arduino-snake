#ifndef SYSTEM_H
#define SYSTEM_H

#include <Arduino.h>

class Sys {
private:
  const uint8_t X_PIN = A2;
  const uint8_t Y_PIN = A1;
  const uint8_t BUTTON_PIN = 14;

  const uint16_t AD_THRESH = 200;
  const uint16_t AD_MAX = 1023;

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
