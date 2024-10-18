/**
 * @file hal_delay.c
 * @brief Implementationof delay functions for AVR microcontroller.
 *
 * This file provides a function for creating delays in milliseconds using the
 * AVR's built-in `_delay_ms()` function. It allows for timed delays in the code
 * without requiring hardware timers.
 *
 * @author Ameed Othman
 * @date 2024-10-18
 */

#include "hal_delay.h"
#include <util/delay.h>

/**
 * @brief Delays execution for a specified number of milliseconds.
 * @param ms The number of milliseconds to delay.
 */
void Delay_ms(uint16_t ms) {
    while (ms--) {
        _delay_ms(1);
    }
}

