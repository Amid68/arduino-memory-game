/**
 * @file input.c
 * @brief Implementation of input handling for buttons.
 *
 * @author Ameed Othman
 * @date 2024-10-17
 */

#include "input.h"
#include "../config/config.h"

/* Function prototypes */
static uint8_t ReadButtonState(uint8_t buttonPin);

/**
 * @brief Initializes the input buttons.
 */
void Input_Init(void) {
    /* Set button pins as inputs with pull-up resistors */
    GPIO_SetPinInputPullup(BUTTON_PIN_1);
    GPIO_SetPinInputPullup(BUTTON_PIN_2);
    GPIO_SetPinInputPullup(BUTTON_PIN_3);
    GPIO_SetPinInputPullup(BUTTON_PIN_4);
}

/**
 * @brief Gets a button press from the user
 * @return Button number (1-4)
 */
uint8_t Input_GetButtonPress(void) {
    uint8_t buttonPressed = 0;
    
    while (!buttonPressed) {
        if (ReadButtonState(BUTTON_PIN_1) == 0) {
            buttonPressed = 1;
        } else if (ReadButtonState(BUTTON_PIN_2) == 0) {
            buttonPressed = 2;
        } else if (ReadButtonState(BUTTON_PIN_3) == 0) {
            buttonPressed = 3;
        } else if (ReadButtonState(BUTTON_PIN_4) == 0) {
            buttonPressed = 4;
        }
    }

    /* Debounce delay */
    Delay_ms(200);
    return buttonPressed;
}

/**
 * @brief Reads the state of a button.
 * @param buttonPin The GPIO pin of the button.
 * @return 0 if pressed, 1 if not pressed.
 */
static uint8_t ReadButtonState(uint8_t buttonPin) {
    /* Assuming a function GPIO_ReadPin is available */
    return GPIO_ReadPin(buttonPin);
}

/**
 * @brief Initializes the random number generator.
 */
void Random_Init(void) {
    /* Seed the random number generator */
    srand(ADC_Read(0)); 
}

/**
 * @brief Generates a random number within a range.
 * @param min Minimum value (inclusive).
 * @param max Maximum value (inclusive).
 * @return Random number between min and max.
 */
uint8_t Random_GetNumber(uint8_t min, uint8_t max) {
    return (rand() % (max - min + 1)) + min;
}


