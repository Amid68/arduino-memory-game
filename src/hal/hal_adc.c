/**
 * @file hal_adc.c
 * @brief Implementation of ADC operations for AVR microcontroller.
 *
 * This file contains functions for configuring and reading from the ADC
 * (Analog-to-Digital Converter) on the AVR microcontroller. The functions
 * provide a simple interface for initializing the ADC and reading analog values
 * from specified channels.
 *
 * @author Ameed Othman
 * @date 2024-10-18
 */

#include "hal_adc.h"
#include <avr/io.h>

/**
 * @brief Initializes the ADC module.
 *
 * This function configures the ADC by enabling it and setting the prescaler to
 * 128, which divides the system clock (16 MHz) down to 125 kHz for the ADC.
 * It also sets the reference voltage to AVcc.
 */
void ADC_Init(void) {
    ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    ADMUX |= (1 << REFS0);
}

/**
 * @brief Reads the analog value from a specified ADC channel.
 *
 * This function starts an ADC conversion on the specified channel (0-7) and
 * waits for the conversion to complete. It then returns the 10-bit result
 * of the conversion.
 *
 * @param channel The ADC channel to read from (0-7).
 * @return uint16_t The 10-bit digital value corresponding to the analog input.
 */
uint16_t ADC_Read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    return ADC;
}
