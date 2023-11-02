#ifndef SYSTEM_H
#define SYSTEM_H

#include <Arduino.h>

class Sys {
private:
public:
  static const uint8_t RIGHT_PIN = 10;
  static const uint8_t UP_PIN = 11;
  static const uint8_t LEFT_PIN = 12;
  static const uint8_t DOWN_PIN = 13;

  static void init();
};

#endif // SYSTEM_H
