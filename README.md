# Arduino Snake

<!-- markdownlint-disable MD013 -->

## Overview

Arduino Snake is a classic snake game ported to the Arduino platform. It is written in C++ and utilizes the `Adafruit GFX` library. The game is designed to run on an Arduino Uno, with a joystick for input and a 280x240 OLED display with an ST7789 driver for output.

> [!note]
> This project was developed as a study project to learn more about Arduino programming and interfacing with hardware components.

## Features

- Classic snake gameplay
- Adjustable difficulty levels
- High score tracking
- Smooth graphics using the Adafruit GFX library
- Responsive joystick controls

## Components

- Arduino Uno
- Joystick
- 280x240 OLED Display with ST7789 driver

## Schematic

For wiring details, refer to the [Schematic](doc/schematics/images/schematic.png).

## Installation

1. **Clone the repository:**

   ```sh
   git clone https://github.com/yourusername/arduino-snake.git
   cd arduino-snake
   ```

2. **Install PlatformIO:**
   Follow the instructions on the [PlatformIO website](https://platformio.org/install).

3. **Initialize the project:**

   ```sh
   pio project init --board=uno
   ```

4. **Install dependencies:**

   ```sh
   pio lib install
   ```

## Usage

1. **Build and upload the project:**

   ```sh
   pio run -t upload
   ```

2. **Monitor the serial output:**

   ```sh
   pio device monitor
   ```

## License

This project is licensed under the [Unlicense](LICENSE).
