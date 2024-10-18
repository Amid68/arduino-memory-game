/**
 * @file hal_gpio.c
 * @brief Implementation of GPIO operations for AVR microcontroller.
 *
 * @author Ameed Othman
 * @date 2024-10-18
 *
 * This file contains functions for configuring and controlling GPIO pins
 * on the AVR microcontroller. It includes functions for setting pins as
 * inputs or outputs, enabling pull-up resistors, and reading/writing pin states.
 */

#include "hal_gpio.h"
#include <avr/io.h>

/**
 * @brief Configures a GPIO pin as input with a pull-up resistor enabled.
 *
 * This function sets the specified pin as an input and avtivates the 
 * internal pull-up resistor. It assumes the pin belongs to PORTD.
 *
 * @param pin The pin number to configure (0-7 for PORTD).
 */
void GPIO_SetPinInputPullup(uint8_t pin) {
    /* Set the pin as input and enable the pull-up resistor */
    DDRD &= ~(1 << pin);
    PORTD |= (1 << pin);
}

/**
 * @brief Configures a GPIO pin as output.
 *
 * This function sets the specified pin as an output. It assumes the pin
 * belongs to PORTD.
 *
 * @param pin The pin number to configure (0-7 for PORTD).
 */
void GPIO_SetPinOutput(uint8_t pin) {
    /* Set the pin as output */
    DDRD |= (1 << pin);
}

/**
 * @brief Writes a HIGH or LOW state to a GPIO pin.
 *
 * This function writes the specified state (HIGH or LOW) to the pin. It
 * assumes the pin belongs to PORTD.
 *
 * @param pin The pin number to write to (0-7 for PORTD).
 * @param state The state to set (HIGH or LOW).
 */
void GPIO_WritePin(uint8_t pin, uint8_t state) {
    if (state == HIGH) {
        PORTD |= (1 << pin);
    } else {
        PORTD &= ~(1 << pin);
    }
}

/**
 * @brief Reads the state of a GPIO pin.
 *
 * This function reads and returns the state of the specified pin. It
 * assumes the pin belongs to PORTD.
 *
 * @param pin The pin number to read (0-7 for PORTD).
 * @return uint8_t Returns HIGH if pin is set, otherwise LOW.
 */
uint8_t GPIO_ReadPin(uint8_t pin) {
    /* Read the state of the pin */
    return (PIND & (1 << pin)) ? HIGH : LOW;
}


