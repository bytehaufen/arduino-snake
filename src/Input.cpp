#include "Input.h"

Input::Input() : joystickConsumed(true) {
  // Set middle button as INPUT_PULLUP
  DDRC &= ~(1 << BUTTON_PIN);
  PORTC |= (1 << BUTTON_PIN);

  // Set internal reference voltage for ADC
  ADMUX |= (1 << REFS0);
  // Set ADC prescaler to 128 (0b111) (for 16 MHz clock, this results in 125
  // kHz ADC clock) => 16 MHz uC clock / 128 = 125 kHz Value have to be 50 kHz
  // to 200 kHz (datasheet)
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  // Enable ADC
  ADCSRA |= (1 << ADEN);
  // Dummy read to warmup ADC
  ADCSRA |= (1 << ADSC);
  while (ADCSRA & (1 << ADSC)) {
  }
  (void)ADCL;
  (void)ADCH;
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
    } else {
      uint16_t xValue = adcRead(X_PIN);
      uint16_t yValue = adcRead(Y_PIN);

      if (xValue > (AD_MAX / 2) + AD_THRESH) {
        rightButtonPressed = true;
        joystickConsumed = false;
        // If joystick moved left
      } else if (xValue < (AD_MAX / 2) - AD_THRESH) {
        leftButtonPressed = true;
        joystickConsumed = false;
        // If joystick moved up
      } else if (yValue < (AD_MAX / 2) - AD_THRESH) {
        upButtonPressed = true;
        joystickConsumed = false;
        // If joystick moved down
      } else if (yValue > (AD_MAX / 2) + AD_THRESH) {
        downButtonPressed = true;
        joystickConsumed = false;
      }
    }
  }
  // TODO: Replace delay
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

uint16_t Input::adcRead(uint8_t pin) {
  // Select ADC channel (bit 7, 6, 5 have to save their value)
  ADMUX = (ADMUX & ~(0x1F)) | pin;
  // Start conversion
  ADCSRA |= (1 << ADSC);
  // Wait for conversion
  while (ADCSRA & (1 << ADSC)) {
  }

  uint16_t value = ADCL;
  value |= (ADCH << 8);
  // Return ADC value
  return value;
}
