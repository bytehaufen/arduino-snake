#include "Input.h"
#include "Arduino.h"
#include <Wire.h>



Input::Input() : joystickConsumed(true) { pinMode(BUTTON_PIN, INPUT_PULLUP); }

Input &Input::getInstance() {
  static Input instance;
  return instance;
}

void Input::run() {
  if (joystickConsumed) {

    middleButtonPressed = false;
    rightButtonPressed = false;
    leftButtonPressed = false;
    upButtonPressed = false;
    downButtonPressed = false;

    if (!digitalRead(BUTTON_PIN)) {
      middleButtonPressed = true;
      joystickConsumed = false;
    } else if (analogRead(X_PIN) > (AD_MAX / 2) + AD_THRESH) {
      rightButtonPressed = true;
      joystickConsumed = false;
    } else if (analogRead(X_PIN) < (AD_MAX / 2) - AD_THRESH) {
      leftButtonPressed = true;
      joystickConsumed = false;
    } else if (analogRead(Y_PIN) < (AD_MAX / 2) - AD_THRESH) {
      upButtonPressed = true;
      joystickConsumed = false;
    } else if (analogRead(Y_PIN) > (AD_MAX / 2) + AD_THRESH) {
      downButtonPressed = true;
      joystickConsumed = false;
    }
  }
  // TODO: Replace delay
  delay(20);
}

Input::BUTTON Input::getPressedButton() {
  BUTTON retVal = BUTTON::NONE;

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

void Input::consumeJoystick() {
  joystickConsumed = true;
}

void Input::printI2Cdevices() {
#define WIRE Wire

  Wire.begin();

  while (!Serial)
    delay(10);
  Serial.println("\nI2C Scanner");
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++) {
    WIRE.beginTransmission(address);
    error = WIRE.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000); // wait 5 seconds for next scan
}
