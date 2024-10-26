/**
 * @file hal_pwm.c
 * @brief Implementation of PWM operations for AVR microcontroller.
 *
 * Author: Ameed Othman
 * Date: 2024-10-26
 */

#include "hal_pwm.h"
#include "hal_gpio.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stddef.h>
#include "pin_mapping.h"

static volatile uint8_t *timer1_tone_port = NULL;
static uint8_t timer1_tone_bit_mask = 0;

static volatile uint8_t *timer2_tone_port = NULL;
static uint8_t timer2_tone_bit_mask = 0;

void PWM_Init(void) {
    // Nothing to initialize here
}

void PWM_PlayTone(uint8_t pin, uint16_t frequency) {
    volatile uint8_t *ddr, *port, *pin_reg;
    uint8_t bit_mask;
    map_pin_to_port(pin, &ddr, &port, &pin_reg, &bit_mask);
    if (ddr == NULL || port == NULL) {
        // Invalid pin
        return;
    }

    // Set the pin as output
    *ddr |= bit_mask;

    cli(); // Disable interrupts

    if (frequency < 500) {
        // Use Timer1 for low frequencies
        timer1_tone_port = port;
        timer1_tone_bit_mask = bit_mask;

        // Configure Timer1 for CTC mode
        TCCR1A = 0;
        TCCR1B = (1 << WGM12) | (1 << CS10); // CTC mode, no prescaling

        // Calculate OCR1A value for the desired frequency
        uint32_t toggle_count = (F_CPU / (frequency * 2UL)) - 1;
        if (toggle_count > 65535) {
            // Adjust prescaler if necessary
            TCCR1B = (1 << WGM12) | (1 << CS11); // Prescaler = 8
            toggle_count = (F_CPU / (8UL * frequency * 2UL)) - 1;
            if (toggle_count > 65535) {
                TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10); // Prescaler = 64
                toggle_count = (F_CPU / (64UL * frequency * 2UL)) - 1;
                if (toggle_count > 65535) {
                    TCCR1B = (1 << WGM12) | (1 << CS12); // Prescaler = 256
                    toggle_count = (F_CPU / (256UL * frequency * 2UL)) - 1;
                    if (toggle_count > 65535) {
                        TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // Prescaler = 1024
                        toggle_count = (F_CPU / (1024UL * frequency * 2UL)) - 1;
                        if (toggle_count > 65535) {
                            // Frequency too low
                            sei();
                            return;
                        }
                    }
                }
            }
        }
        OCR1A = (uint16_t)toggle_count;
        // Clear Timer on Compare Match
        TCNT1 = 0;
        // Enable Timer1 Compare Match A interrupt
        TIMSK1 |= (1 << OCIE1A);
    } else {
        // Use Timer2 for higher frequencies
        timer2_tone_port = port;
        timer2_tone_bit_mask = bit_mask;

        // Configure Timer2 for CTC mode
        TCCR2A = (1 << WGM21); // CTC mode
        TCCR2B = (1 << CS20);  // No prescaling

        // Calculate OCR2A value for the desired frequency
        uint32_t toggle_count = (F_CPU / (frequency * 2UL)) - 1;
        if (toggle_count > 255) {
            // Adjust prescaler if necessary
            TCCR2B = (1 << CS21); // Prescaler = 8
            toggle_count = (F_CPU / (8UL * frequency * 2UL)) - 1;
            if (toggle_count > 255) {
                TCCR2B = (1 << CS21) | (1 << CS20); // Prescaler = 32
                toggle_count = (F_CPU / (32UL * frequency * 2UL)) - 1;
                if (toggle_count > 255) {
                    TCCR2B = (1 << CS22); // Prescaler = 64
                    toggle_count = (F_CPU / (64UL * frequency * 2UL)) - 1;
                    if (toggle_count > 255) {
                        // Frequency too low for Timer2
                        sei();
                        return;
                    }
                }
            }
        }
        OCR2A = (uint8_t)toggle_count;
        // Clear Timer on Compare Match
        TCNT2 = 0;
        // Enable Timer2 Compare Match A interrupt
        TIMSK2 |= (1 << OCIE2A);
    }
    sei(); // Enable interrupts
}

void PWM_StopTone(uint8_t pin) {
    // Determine if Timer1 or Timer2 was used
    // Based on which timer's port and bit_mask are set
    if (timer1_tone_port != NULL) {
        // Disable Timer1 interrupts
        TIMSK1 &= ~(1 << OCIE1A);
        // Turn off Timer1
        TCCR1B = 0;
        // Set the pin low
        *timer1_tone_port &= ~timer1_tone_bit_mask;
        timer1_tone_port = NULL;
        timer1_tone_bit_mask = 0;
    }
    if (timer2_tone_port != NULL) {
        // Disable Timer2 interrupts
        TIMSK2 &= ~(1 << OCIE2A);
        // Turn off Timer2
        TCCR2B = 0;
        // Set the pin low
        *timer2_tone_port &= ~timer2_tone_bit_mask;
        timer2_tone_port = NULL;
        timer2_tone_bit_mask = 0;
    }
}

// Timer1 Compare Match A Interrupt Service Routine
ISR(TIMER1_COMPA_vect) {
    if (timer1_tone_port != NULL) {
        // Toggle the pin
        *timer1_tone_port ^= timer1_tone_bit_mask;
    }
}

// Timer2 Compare Match A Interrupt Service Routine
ISR(TIMER2_COMPA_vect) {
    if (timer2_tone_port != NULL) {
        // Toggle the pin
        *timer2_tone_port ^= timer2_tone_bit_mask;
    }
}

