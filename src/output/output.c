/**
 * @file output.c
 * @brief Implementation of output handling for LEDs and feedback.
 *
 * @author Ameed Othman
 * @date 2024-10-17
 */

#include "output.h"
#include "../config/config.h"
#include "../sound/speaker.h"
#include "../sound/melody.h"
#include "../hal/hal_delay.h"
#include "../hal/hal_gpio.h"

/* Function prototypes */
static void LightLED(uint8_t ledPin);
static void TurnOffAllLEDs(void);

/**
 * @brief Initializes the output LEDs.
 */
void Output_Init(void) {
    /* Set LED pins as outputs */
    GPIO_SetPinOutput(LED_PIN_1);
    GPIO_SetPinOutput(LED_PIN_2);
    GPIO_SetPinOutput(LED_PIN_3);
    GPIO_SetPinOutput(LED_PIN_4);
}

/**
 * @brief Displays the sequence to the user.
 * @param sequence The sequence array.
 * @param length The length of the sequence.
 */
void Output_DisplaySequence(uint8_t *sequence, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        LightLED(sequence[i]);
        Delay_ms(500);
        TurnOffAllLEDs();
        Delay_ms(500);
    }
}

/**
 * @brief Plays feedback when a button is pressed.
 * @param button The button number pressed.
 */
void Output_PlayFeedback(uint8_t button) {
    LightLED(button);
    Speaker_PlayNoteForButton(button);
    Delay_ms(200);
    TurnOffAllLEDs();
    Delay_ms(250);
}

/**
 * @brief Plays the failure sequence.
 */
void Output_PlayFailure(void) {
    for (uint8_t i = 0; i < 3; i++) {
        LightLED(1);
        LightLED(2);
        LightLED(3);
        LightLED(4);
        Speaker_PlayFailureTone();
        Delay_ms(200);
        TurnOffAllLEDs();
        Delay_ms(200);
    }
}

/**
 * @brief Lights up a specific LED.
 * @param ledNumber The LED number to light up.
 */
static void LightLED(uint8_t ledNumber) {
    switch(ledNumber) {
        case 1:
            GPIO_WritePin(LED_PIN_1, HIGH);
            break;
        case 2:
            GPIO_WritePin(LED_PIN_2, HIGH);
            break;
        case 3:
            GPIO_WritePin(LED_PIN_3, HIGH);
            break;
        case 4:
            GPIO_WritePin(LED_PIN_4, HIGH);
            break;
        default:
            break;
    }
}

/**
 * @brief Turns off all LEDs.
 */
static void TurnOffAllLEDs(void) {
    GPIO_WritePin(LED_PIN_1, LOW);
    GPIO_WritePin(LED_PIN_2, LOW);
    GPIO_WritePin(LED_PIN_3, LOW);
    GPIO_WritePin(LED_PIN_4, LOW);
}


