/**
 * @file speaker.c
 * @brief Implementation of speaker control functions.
 *
 * @author Ameed Othman
 * @date 2024-10-18
 */

#include "speaker.h"
#include "../config/config.h"
#include "../output/output.h"

/* Speaker pin */
static uint8_t speakerPin;

/**
 * @brief Initializes the speaker.
 * @param pin The GPIO pin connected to the speaker.
 */

void Speaker_Init(uint8_t pin) {
    speakerPin = pin;
    GPIO_SetPinOutput(speakerPin);
}

/**
 * @brief Plays a note and blinks LEDs.
 * @param note The frequency of the note.
 * @param duration The duration of the note in milliseconds.
 */
void Speaker_PlayNoteWithLED(uint16_t note, uint16_t duration) {
    /* Play note */
    PWM_PlayTone(speakerPin, note);
    /* Turn on all LEDs */
    GPIO_WritePin(LED_PIN_1, HIGH);
    GPIO_WritePin(LED_PIN_2, HIGH);
    GPIO_WritePin(LED_PIN_3, HIGH);
    GPIO_WritePin(LED_PIN_4, HIGH);
    /* Wait for duration */
    Delay_ms(duration);
    /* Stop note */
    PWM_StopTone(speakerPin);
    /* Turn off all LEDs */
    GPIO_WritePin(LED_PIN_1, LOW);
    GPIO_WritePin(LED_PIN_2, LOW);
    GPIO_WritePin(LED_PIN_3, LOW);
    GPIO_WritePin(LED_PIN_4, LOW);
    /* Short delay */
    Delay_ms(50);
}

/**
 * @brief Plays a note corresponding to a button press.
 * @param button The button number pressed.
 */
void Speaker_PlayNoteForButton(uint8_t button) {
    uint16_t note;
    switch (button) {
        case 1:
            note = NOTE_G3;
            break;
        case 2:
            note = NOTE_A3;
            break;
        case 3:
            note = NOTE_B3;
            break;
        case 4:
            note = NOTE_C4;
            break;
        default:
            note = 0;
            break;
    }
    
    PWM_PlayTone(speakerPin, note);
    Delay_ms(100);
    PWM_StopTone(speakerPin);
}

/**
 * @brief Plays the failure tone.
 */
void Speaker_PlayFailureTone(void) {
    PWM_PlayTone(speakerPin, NOTE_G3);
    Delay_ms(300);
    PWM_StopTone(speakerPin);
    Delay_ms(200);
    PWM_PlayTone(speakerPin, NOTE_C3);
    Delay_ms(300);
    PWM_StopTone(speakerPin);
}


