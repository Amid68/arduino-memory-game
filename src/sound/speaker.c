/**
 * @file speaker.c
 * @brief Implementation of speaker control functions.
 *
 * @author: Ameed Othman
 * @date: 2024-10-18
 */

#include "speaker.h"
#include "../config/config.h"
#include "../hal/hal_gpio.h"
#include "../hal/hal_delay.h"
#include "../hal/hal_pwm.h"
#include "notes.h"

/* Speaker pin */
static uint8_t speakerPin;

/**
 * @brief Initializes the speaker.
 * @param pin The GPIO pin connected to the speaker.
 */
void Speaker_Init(uint8_t pin) {
    speakerPin = pin;
    GPIO_SetPinOutput(speakerPin);
    PWM_Init();
}

/**
 * @brief Plays a note.
 * @param note The frequency of the note.
 * @param duration The duration of the note in milliseconds.
 */
void Speaker_PlayNote(uint16_t note, uint16_t duration) {
    if (note == 0) return;
    PWM_PlayTone(speakerPin, note);
    Delay_ms(duration);
    PWM_StopTone(speakerPin);
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
    
    Speaker_PlayNote(note, 100);
}

/**
 * @brief Plays the failure tone.
 */
void Speaker_PlayFailureTone(void) {
    Speaker_PlayNote(NOTE_G3, 300);
    Delay_ms(200);
    Speaker_PlayNote(NOTE_C3, 300);
}

