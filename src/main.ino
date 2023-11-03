#include <Arduino.h>

#include "StateMachine.h"
#include "Sys.h"
#include "Menu.h"
#include "Oled.h"

#define DEBUG

StateMachine stateMachine;
Sys sys;

void setup() {
  Serial.begin(115200);
  Oled oled;

}

void loop() {                 
  stateMachine.run();
  sys.run();

  // TODO rm DEBUG
#ifdef DEBUG
  // Sys::printi2cdevices();

  Sys::BUTTON button = sys.getPressedButton();
  if (button == Sys::BUTTON::MIDDLE) {
    Serial.println("Middle button pressed");
  }
  if (button == Sys::BUTTON::UP) {
    Serial.println("UP button pressed");
  }
  if (button == Sys::BUTTON::LEFT) {
    Serial.println("Left button pressed");
  }
  if (button == Sys::BUTTON::DOWN) {
    Serial.println("Down button pressed");
  }
  if (button == Sys::BUTTON::RIGHT) {
    Serial.println("Right button pressed");
  }
#endif // DEBUG

// TODO rm delay and make unblocking
  delay(100);
}
