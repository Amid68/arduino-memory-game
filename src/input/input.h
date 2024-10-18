/**
 * @file input.h
 * @brief Input handling for buttons.
 *
 * @author Ameed Othman
 * @date 2024-10-17
 */

#ifndef __INPUT_H__
#define __INPUT_H__

#include <stdint.h>

/* Function prototypes */
void Input_Init(void);
uint8_t Input_GetButtonPress(void);
void Random_Init(void);
uint8_t Random_GetNumber(uint8_t min, uint8_t max);

#endif
