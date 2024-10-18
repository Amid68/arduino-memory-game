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

/* Intro melody notes and durations */
static const uint16_t introNotes[] = { /* Note frequencies */ };
static const uint16_t introDurations[] = { /* Durations in ms */ };

/* Happy melody notes and durations */
static const uint16_t happyNotes[] = { /* Note frequencies */ };
static const uint16_t happyDurations[] = { /* Durations in ms */ };

/**
 * @brief Plays the happy melody at milestones.
 */
void Melody_PlayHappy(void) {
    for (uint8_t i = 0; i < sizeof(happyNotes)/sizeof(happyNotes[0]); i++) {
        Speaker_PlayNoteWithLED(happyNotes[i], happyDurations[i]);
    }
}

