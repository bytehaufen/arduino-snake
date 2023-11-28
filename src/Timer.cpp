#include "Timer.h"

volatile uint32_t timerCount = 0;

Timer::Timer() {
  // Disable all interrupts
  cli();

  TCCR1B |=
      (1 << WGM12) // CTC mode - Clear Timer on Compare Match (Auto Reload)
      | (1 << CS11) | (1 << CS10); // Prescaler 64
  // Set ctc value to the desired 100 Hz
  OCR1A = calculate_OCR1A(100);

  // Enable Timer2 Compare Match A Interrupt
  TIMSK1 |= (1 << OCIE1A);

  // Enable all interrupts
  sei();
}

uint16_t Timer::calculate_OCR1A(uint16_t targetFreq) {
  // Wanted clock: clk = 1 / 1 ms = 1000 Hz
  // CPU clock: F_CPU = 16000000UL
  // Prescaler = 8
  // Timer1_res = 16 bit
  // Timer compare = OCR1A = F_CPU / (2 * prescaler * clk ) - 1 = 999

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

  const uint8_t PRESCALER = 8;

  return F_CPU / (2UL * PRESCALER * targetFreq) - 1;
}

uint32_t Timer::milliSeconds() {
  uint32_t retval;
  cli();
  retval = timerCount;
  sei();
  return retval;
}

// ISR for timer
ISR(TIMER1_COMPA_vect) { timerCount++; }
