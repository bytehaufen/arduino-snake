# Notes for documentation

## Solved Problems

- Joystick is analog, but input have to be digital
- Some classes must to be instantiated once -> singleton pattern
- On avr microcontrollers the memory of static variables in class methods is not reallocated when a
new object is created -> fix: do not use static variables in class methods, use class variables instead
