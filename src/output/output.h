/**
 * @file output.h
 * @brief Output handling for LEDs and feedback.
 *
 * @author Ameed Othman
 * @date 2024-10-17
 */

#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <stdint.h>

/* Function prototypes */
void Output_Init(void);
void Output_DisplaySequence(uint8_t *sequence, uint8_t length);
void Output_PlayFeedback(uint8_t button);
void Output_PlayFailure(void);

#endif
