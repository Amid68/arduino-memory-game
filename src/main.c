/**
 * @file main.c
 * @brief main entry of the memory game
 * author: Ameed Othman
 * date: 17.10.2024
 */

#include <stdint.h>
#include "config/config.h"
#include "game/game_logic.h"
#include "sound/melody.h"
#include "sound/speaker.h"

/* Function prototypes */
void setup(void);
void loop(void);

/**
 * @brief Main function
 */
int main(void) {
    setup();
    
    while(1) {
        loop();
    }

    return 0;
}

/**
 * @brief Initializes hardware and game state.
 */
void setup(void) {
    /* Initialize hardware */
    Speaker_Init(SPEAKER_PIN);
    Input_Init();
    Output_Init();

    /* Seed the random number generator */
    Random_Init();

    /* Initialize game logic */
    Game_Init();
}

/**
 * @brief Main loop function
 */
void loop(void) {
    Game_Run();
}


