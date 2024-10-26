/**
 * @file pin_mapping.c
 * @brief Pin mapping utility for AVR microcontroller.
 *
 * Defines the `map_pin_to_port` function to map Arduino pins to AVR ports.
 *
 * @author Ameed Othman
 * @date 2024-10-26
 */

#include "pin_mapping.h"
#include <avr/io.h>
#include <stddef.h> // for NULL

void map_pin_to_port(uint8_t pin, volatile uint8_t **ddr, volatile uint8_t **port, volatile uint8_t **pin_reg, uint8_t *bit_mask)
{
    if (pin <= 7) 
    {
        *ddr = &DDRD;
        *port = &PORTD;
        *pin_reg = &PIND;
        *bit_mask = (1 << pin);
    } 
    else if (pin <= 13)
    {
        *ddr = &DDRB;
        *port = &PORTB;
        *pin_reg = &PINB;
        *bit_mask = (1 << (pin - 8));
    }
    else if (pin <= 19)
    {
        *ddr = &DDRC;
        *port = &PORTC;
        *pin_reg = &PINC;
        *bit_mask = (1 << (pin - 14));
    }
    else 
    {
        *ddr = NULL;
        *port = NULL;
        *pin_reg = NULL;
        *bit_mask = 0;
    }
}

