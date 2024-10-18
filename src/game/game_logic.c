/**
 * @file game_logic.c
 * @brief Implementation of game logic and state management.
 *
 * @author Ameed Othman
 * @date 2024-10-17
 */

#include "game_logic.h"
#include "../config/config.h"
#include "../sound/melody.h"
#include "../sound/speaker.h"
#include "../input/input.h"
#include "../output/output.h"

/* Static variables */
static uint8_t sequence[MAX_SEQUENCE_LENGTH];
static uint8_t userInput[MAX_SEQUENCE_LENGTH];
static uint8_t turn = 1;
static uint8_t maxTurnAchieved = 0;
static uint8_t nextMilestone = HAPPY_MELODY_MILESTONE;
static uint8_t melodyPlayed = 0;

/* Function prototypes */
static void GenerateRandomSequence(void);
static uint8_t GetUserInput(void);
static void PlayFailureSequence(void);

/**
 * @brief Initializes the game state.
 */
void Game_Init(void) {
    if (!melodyPlayed) {
        Melody_PlayIntro();
        melodyPlayed = 1;
    }

    turn = 1;
    maxTurnAchieved = 0;
    nextMilestone = HAPPY_MELODY_MILESTONE;
    GenerateRandomSequence();
}

/**
 * @brief Runs one iteration of then game loop.
 */
void Game_Run(void) {
    Output_DisplaySequence(sequence, turn);

    if (GetUserInput()) {
        /* Correct input */
        if (turn > maxTurnAchieved) {
            maxTurnAchieved = turn;
        }

        /* Check for milestone */
        if (turn >= nextMilestone) {
            Melody_PlayHappy();
            nextMilestone += HAPPY_MELODY_MILESTONE;
        }

        turn++;
        GenerateRandomSequence();
    } else {
        /* Incorrect input */
        PlayFailureSequence();
        Game_Init();
    }
}

/**
 * @brief Generates the random sequence for the game.
 */
static void GenerateRandomSequence(void) {
    sequence[turn - 1] = Random_GetNumber(1, 4);
}

/**
 * @brief Gets user input and compares it with the sequence.
 * @return 1 if input is correct, 0 otherwise.
 */
static uint8_t GetUserInput(void) {
    for (uint8_t i = 0; i < turn; i++) {
        userInput[i] = Input_GetButtonPress();
        Output_PlayFeedback(userInput[i]);

        if (userInput[i] != sequence[i]) {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Plays the failure sequence when the user makes a mistake.
 */
static void PlayFailureSequence(void) {
    Output_PlayFailure();
}


