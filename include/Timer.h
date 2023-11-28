#ifndef TIMER_H
#define TIMER_H

#include <avr/interrupt.h>
#include <stdint.h>

/**
 * @class Timer
 * @brief Timer class, for all timing purposes.
 *
 */
class Timer {
private:
  /**
   * @brief Calculates the value for OCR1A
   *
   * @param targetFreq Target frequency
   * @return Value for OCR1A
   */
  uint16_t calculate_OCR1A(uint16_t targetFreq);

public:
  Timer();
  /**
   * @brief Get the current time in milli-seconds
   */
  uint32_t milliSeconds();
};
#endif // TIMER_H
