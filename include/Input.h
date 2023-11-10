/**
 * @file Input.h
 * @brief Singleton class that handles input.
 */

#ifndef SYSTEM_H
#define SYSTEM_H

// TODO: RM
#include <Arduino.h>
#include <avr/io.h>
#include <stdint.h>

/**
 * @class Input
 * @brief Singleton class that handles input.
 *
 */
class Input {
private:
  // Pins definitions
  const uint8_t X_PIN = A2;
  const uint8_t Y_PIN = A1;
  // TODO: RM
  /* const uint8_t BUTTON_PIN = 14; */
  // Arduino pin A0 as digital input
  const uint8_t BUTTON_PIN = PC0;

  // Threshold for ADC
  const uint16_t AD_THRESH = 200;
  // Max ADC value
  const uint16_t AD_MAX = 1023;

  // Helper variables to check if button is pressed
  bool middleButtonPressed;
  bool rightButtonPressed;
  bool upButtonPressed;
  bool downButtonPressed;
  bool leftButtonPressed;
  bool joystickConsumed;

  /**
   * @brief Private constructor
   */
  Input();

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
  void run();
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
