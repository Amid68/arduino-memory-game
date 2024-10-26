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
#include <stddef.h>
#include "pin_mapping.h"

/**
 * @brief Configures a GPIO pin as input with a pull-up resistor enabled.
 *
 * @param pin The pin number to configure (Arduino digital pins 0-19).
 */
void GPIO_SetPinInputPullup(uint8_t pin) {
    volatile uint8_t *ddr, *port, *pin_reg;
    uint8_t bit_mask;
    map_pin_to_port(pin, &ddr, &port, &pin_reg, &bit_mask);
    /* Set the pin as input and enable the pull-up resistor */
    if (ddr != NULL)
    {
        *ddr &= ~bit_mask;
        *port |= bit_mask;
    }
}

/**
 * @brief Configures a GPIO pin as output.
 *
 * @param pin The pin number to configure (Arduino digital pins 0-19).
 */
void GPIO_SetPinOutput(uint8_t pin) {
    volatile uint8_t *ddr, *port, *pin_reg;
    uint8_t bit_mask;
    map_pin_to_port(pin, &ddr, &port, &pin_reg, &bit_mask);
    /* Set the pin as output */
    if (ddr != NULL) {
        *ddr |= bit_mask; 
    }
}

/**
 * @brief Writes a HIGH or LOW state to a GPIO pin.
 *
 * @param pin The pin number to write to (Arduino digital pins 0-19).
 * @param state The state to set (HIGH or LOW).
 */
void GPIO_WritePin(uint8_t pin, uint8_t state) {
    volatile uint8_t *ddr, *port, *pin_reg;
    uint8_t bit_mask;
    map_pin_to_port(pin, &ddr, &port, &pin_reg, &bit_mask);
    if (port != NULL) {
        if (state == HIGH) {
            *port |= bit_mask; 
        } else {
            *port &= ~bit_mask;
        }
    }
}

/**
 * @brief Reads the state of a GPIO pin.
 *
 * @param pin The pin number to read (Arduino digital pins 0-19).
 * @return uint8_t Returns HIGH if pin is set, otherwise LOW.
 */
uint8_t GPIO_ReadPin(uint8_t pin) {
    volatile uint8_t *ddr, *port, *pin_reg;
    uint8_t bit_mask;
    map_pin_to_port(pin, &ddr, &port, &pin_reg, &bit_mask);
    /* Read the state of the pin */
    if (pin_reg != NULL) {
        return ((*pin_reg & bit_mask) != 0) ? HIGH : LOW;
    }
    return LOW;
}

