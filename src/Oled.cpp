#include "Oled.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Oled::Oled() {
  Adafruit_SH1106 display(4);
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  // Clear the buffer.
  display.clearDisplay();

  // draw a single pixel
  display.drawPixel(10, 10, WHITE);
  display.display();
  delay(2000);
  display.clearDisplay();
}
