/**
 * @file Input.h
 * @brief Singleton class that handles input.
 */

#ifndef SYSTEM_H
#define SYSTEM_H

#include "Timer.h"
#include <avr/io.h>
#include <stdint.h>

/**
 * @class Input
 * @brief Singleton class that handles input.
 *
 */
class Input {
private:
  // Joystick middle button pin
  const uint8_t BUTTON_PIN = PC0; // Arduino A0

  // ADC pins for joystick
  const uint8_t X_PIN = 2; // Arduino A2
  const uint8_t Y_PIN = 1; // Arduino A1
  // Threshold for ADC
  const uint16_t AD_THRESH = 200;
  // Max ADC value
  const uint16_t AD_MAX = 1023;
  // Debounce time
  const uint8_t DEBOUNCE_TIME = 20;

  // Helper variables to check if button is pressed
  bool middleButtonPressed;
  bool lastMiddleButtonPressed = false;
  bool rightButtonPressed;
  bool upButtonPressed;
  bool downButtonPressed;
  bool leftButtonPressed;
  bool joystickConsumed;

  /**
   * @brief Private constructor
   */
  Input();

  /**
   * @brief Read ADC value.
   *
   * @param pin ADC pin
   * @return ADC value
   */
  uint16_t adcRead(uint8_t pin);

public:
  /**
   * @brief Enum for button
   */
  enum class BUTTON { UP, DOWN, LEFT, RIGHT, MIDDLE, NONE };

  /*
   * @brief Get the instance object.
   * @return Instance object
   */
  static Input &getInstance();
  /**
   * @brief Run method to periodically check for input, needs to be called in
   * main loop.
   */
  void run(Timer *timer);
  /**
   * @brief Get the pressed button.
   * @return The pressed button as BUTTON enum
   */
  BUTTON getPressedButton();
  /**
   * @brief Delete all pressed buttons.
   */
  void consumeJoystick();
};

#endif // SYSTEM_H
