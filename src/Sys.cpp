#include "Sys.h"
#include "Arduino.h"
#include <Wire.h>

const uint8_t X_PIN = A1;
const uint8_t Y_PIN = A0;
const uint8_t BUTTON_PIN = 2;

const uint16_t AD_THRESH = 200;
const uint16_t AD_MAX = 1023;

Sys::Sys() { pinMode(BUTTON_PIN, INPUT_PULLUP); }

void Sys::run() {
#ifdef DEBUG
  /* Serial.print("X_PIN: "); */
  /* Serial.println(analogRead(X_PIN)); */
  /* Serial.print("Y_PIN: "); */
  /* Serial.println(analogRead(Y_PIN)); */
#endif // DEBUG

  if (!digitalRead(BUTTON_PIN)) {
    middleButtonPressed = true;
  } else if (analogRead(X_PIN) > (AD_MAX / 2) + AD_THRESH) {
    rightButtonPressed = true;
  } else if (analogRead(X_PIN) < (AD_MAX / 2) - AD_THRESH) {
    leftButtonPressed = true;
  } else if (analogRead(Y_PIN) < (AD_MAX / 2) - AD_THRESH) {
    upButtonPressed = true;
  } else if (analogRead(Y_PIN) > (AD_MAX / 2) + AD_THRESH) {
    downButtonPressed = true;
  }
}

Sys::BUTTON Sys::getPressedButton() {
  BUTTON retVal;
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
  } else {
    retVal = BUTTON::NONE;
  }
  if (retVal != BUTTON::NONE) {
    middleButtonPressed = false;
    rightButtonPressed = false;
    leftButtonPressed = false;
    upButtonPressed = false;
    downButtonPressed = false;
  }

  return retVal;
}

void Sys::printi2cdevices() {
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
