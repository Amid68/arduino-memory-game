/**
 * @file speaker.h
 * @brief Speaker control functions.
 *
 * @author Ameed Othman
 * @date 2024-10-18
 */

#ifndef __SPEAKER_H__
#define __SPEAKER_H__

#include <stdint.h>

/* Function prototypes */
void Speaker_Init(uint8_t pin);
void Speaker_PlayNote(uint16_t note, uint16_t duration);
void Speaker_PlayNoteForButton(uint8_t button);
void Speaker_PlayFailureTone(void);

#endif

