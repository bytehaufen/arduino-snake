#include "Input.h"

Input::Input() : joystickConsumed(true) {
  // Set middle button as INPUT_PULLUP
  /* pinMode(BUTTON_PIN, INPUT_PULLUP); */
  DDRC &= ~(1 << BUTTON_PIN);
  PORTC |= (1 << BUTTON_PIN);
}

Input &Input::getInstance() {
  static Input instance;
  return instance;
}

void Input::run() {
  // Reset all pressed buttons if joystick is consumed
  if (joystickConsumed) {
    middleButtonPressed = false;
    rightButtonPressed = false;
    leftButtonPressed = false;
    upButtonPressed = false;
    downButtonPressed = false;

    // If middle button is pressed
    if (!(PINC & (1 << BUTTON_PIN))) {
      middleButtonPressed = true;
      joystickConsumed = false;
      // If joystick moved right
    } else if (static_cast<uint16_t>(analogRead(X_PIN)) >
               (AD_MAX / 2) + AD_THRESH) {
      rightButtonPressed = true;
      joystickConsumed = false;
      // If joystick moved left
    } else if (static_cast<uint16_t>(analogRead(X_PIN)) <
               (AD_MAX / 2) - AD_THRESH) {
      leftButtonPressed = true;
      joystickConsumed = false;
      // If joystick moved up
    } else if (static_cast<uint16_t>(analogRead(Y_PIN)) <
               (AD_MAX / 2) - AD_THRESH) {
      upButtonPressed = true;
      joystickConsumed = false;
      // If joystick moved down
    } else if (static_cast<uint16_t>(analogRead(Y_PIN)) >
               (AD_MAX / 2) + AD_THRESH) {
      downButtonPressed = true;
      joystickConsumed = false;
    }
  }
  // TODO: Replace delay
  delay(20);
}

Input::BUTTON Input::getPressedButton() {
  BUTTON retVal = BUTTON::NONE;

  // If joystick is not consumed (not handled input)
  if (!joystickConsumed) {
    if (middleButtonPressed) {
      retVal = BUTTON::MIDDLE;
    } else if (rightButtonPressed) {
      retVal = BUTTON::RIGHT;
    } else if (leftButtonPressed) {
      retVal = BUTTON::LEFT;
    } else if (upButtonPressed) {
      retVal = BUTTON::UP;
    } else if (downButtonPressed) {
      retVal = BUTTON::DOWN;
    }
  }
  joystickConsumed = true;

  return retVal;
}

void Input::consumeJoystick() { joystickConsumed = true; }
