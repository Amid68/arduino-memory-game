/**
 * @file melody.c
 * @brief Implementation of melody playback functions.
 *
 * @author Ameed Othman
 * @date 2024-10-18
 */

#include "melody.h"
#include "speaker.h"
#include "../output/output.h"
#include "../config/config.h"
#include "../sound/notes.h"
#include "../hal/hal_gpio.h"
#include "../hal/hal_delay.h"

/* Intro melody notes and durations */
static const uint16_t introNotes[] = { 
    NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_C4,
    NOTE_F4, NOTE_C4, NOTE_F4, NOTE_G4, NOTE_F4,
    NOTE_E4, NOTE_F4, NOTE_G4
};
static const uint16_t introDurations[] = {
    100, 200, 100, 200, 100, 400, 100, 100, 100, 100,
    200, 100, 500
};

/* Happy melody notes and durations */
static const uint16_t happyNotes[] = { 
    NOTE_C5, NOTE_E5, NOTE_G5, NOTE_C6, NOTE_G5, NOTE_E5, NOTE_C5
};
static const uint16_t happyDurations[] = {
    200, 200, 200, 400, 200, 200, 400
};

/**
 * @brief Plays the happy melody with all LEDs blinking together.
 */
void Melody_PlayHappy(void) {
    for (uint8_t i = 0; i < sizeof(happyNotes)/sizeof(happyNotes[0]); i++) {
        // Turn on all LEDs
        GPIO_WritePin(LED_PIN_1, HIGH);
        GPIO_WritePin(LED_PIN_2, HIGH);
        GPIO_WritePin(LED_PIN_3, HIGH);
        GPIO_WritePin(LED_PIN_4, HIGH);
        
        // Play the note
        Speaker_PlayNote(happyNotes[i], happyDurations[i]);

        // Turn off all LEDs
        GPIO_WritePin(LED_PIN_1, LOW);
        GPIO_WritePin(LED_PIN_2, LOW);
        GPIO_WritePin(LED_PIN_3, LOW);
        GPIO_WritePin(LED_PIN_4, LOW);

        // Short delay between notes
        Delay_ms(20); // Adjust this delay if you want longer intervals between blinks
    }
    Delay_ms(500);  // Short pause after the melody finishes
}

/**
 * @brief Plays the intro melody.
 */
void Melody_PlayIntro(void) 
{
    for (uint8_t i = 0; i < sizeof(introNotes) / sizeof(introNotes[0]); i++)
    {
        // Determine which LED to light up based on the note index
        if (i == 0 || i == 2 || i == 4 || i == 6) {
            GPIO_WritePin(LED_PIN_1, HIGH);
        }
        if (i == 1 || i == 3 || i == 5 || i == 7 || i == 9 || i == 11) {
            GPIO_WritePin(LED_PIN_2, HIGH);
        }
        if (i == 8 || i == 12) {
            GPIO_WritePin(LED_PIN_3, HIGH);
        }
        if (i == 10) {
            GPIO_WritePin(LED_PIN_4, HIGH);
        }

        Speaker_PlayNote(introNotes[i], (uint16_t)(introDurations[i] * 0.7)); // Adjust duration as needed

        // Turn off all LEDs
        GPIO_WritePin(LED_PIN_1, LOW);
        GPIO_WritePin(LED_PIN_2, LOW);
        GPIO_WritePin(LED_PIN_3, LOW);
        GPIO_WritePin(LED_PIN_4, LOW);

        // Shorter pause between notes (if needed)
        Delay_ms(10); // Reduced delay
    }
    Delay_ms(500);  // Shorter pause after the melody finishes
}

