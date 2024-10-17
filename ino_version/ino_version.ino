#include <Tone.h>

Tone speakerpin;
int starttune[] = {NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_C4,
                   NOTE_F4, NOTE_C4, NOTE_F4, NOTE_G4, NOTE_F4,
                   NOTE_E4, NOTE_F4, NOTE_G4};
int duration2[] = {100, 200, 100, 200, 100, 400, 100, 100, 100, 100,
                   200, 100, 500};
int button[] = {2, 3, 4, 5};    // Pins connected to pushbutton inputs
int ledpin[] = {8, 9, 10, 11};  // Pins connected to LEDs
int turn = 1;                   // Turn counter (starts from 1)
int buttonstate = 0;            // Check pushbutton state
int randomArray[100];           // Array that can store up to 100 inputs
int inputArray[100];
bool melodyPlayed = false;      // Track if the initial melody was played
int happyTune[] = {NOTE_C5, NOTE_E5, NOTE_G5, NOTE_C6, NOTE_G5, NOTE_E5, NOTE_C5};
int happyDuration[] = {200, 200, 200, 400, 200, 200, 400};  // Durations of happy tune
int maxTurnAchieved = 0;        // Highest turn ever achieved
int nextMilestone = 5;          // Next milestone for happy melody

void setup() {
  Serial.begin(9600);
  speakerpin.begin(12); // Pin connected to piezo buzzer

  for (int x = 0; x < 4; x++) {
    pinMode(ledpin[x], OUTPUT); // Set LED pins as output
    pinMode(button[x], INPUT);  // Set pushbutton pins as inputs
    digitalWrite(button[x], HIGH); // Enable internal pullup
  }

  randomSeed(analogRead(0));  // Seed random number generator
}

void playMelodyAndBlinkLEDs() {
  for (int thisNote = 0; thisNote < 13; thisNote++) {
    // Play the note with the specified (shortened) duration
    speakerpin.play(starttune[thisNote], duration2[thisNote] * 0.7); // 30% faster

    // Light the corresponding LEDs based on the note index
    if (thisNote == 0 || thisNote == 2 || thisNote == 4 || thisNote == 6) {
      digitalWrite(ledpin[0], HIGH);
    }
    if (thisNote == 1 || thisNote == 3 || thisNote == 5 || thisNote == 7 || thisNote == 9 || thisNote == 11) {
      digitalWrite(ledpin[1], HIGH);
    }
    if (thisNote == 8 || thisNote == 12) {
      digitalWrite(ledpin[2], HIGH);
    }
    if (thisNote == 10) {
      digitalWrite(ledpin[3], HIGH);
    }

    // Wait for the shortened duration of the note
    delay(duration2[thisNote] * 0.9); // 30% faster

    // Turn off all LEDs
    digitalWrite(ledpin[0], LOW);
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], LOW);
    digitalWrite(ledpin[3], LOW);

    // Shorter pause between notes (if needed)
    delay(10); // Reduced delay
  }
  delay(500);  // Shorter pause after the melody finishes
}

void generateRandomPattern() {
  for (int y = 0; y < turn; y++) {
    // Display the pattern up to the current turn
    Serial.print("Sequence at position ");
    Serial.print(y);
    Serial.print(": ");
    Serial.println(randomArray[y]);

    // Light corresponding LED
    if (randomArray[y] == 1) digitalWrite(ledpin[0], HIGH);
    if (randomArray[y] == 2) digitalWrite(ledpin[1], HIGH);
    if (randomArray[y] == 3) digitalWrite(ledpin[2], HIGH);
    if (randomArray[y] == 4) digitalWrite(ledpin[3], HIGH);

    delay(500);  // Display the pattern
    digitalWrite(ledpin[0], LOW);
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], LOW);
    digitalWrite(ledpin[3], LOW);
    delay(500);  // Pause between patterns
  }
}

void loop() {
  if (!melodyPlayed) {
    playMelodyAndBlinkLEDs();
    melodyPlayed = true;
    turn = 1;  // Start from turn 1
    randomArray[0] = random(1, 5);  // Generate the first random number
  }

  generateRandomPattern();

  if (input()) {
    // Input was correct, proceed to next turn

    // Update maxTurnAchieved if this is the highest turn achieved
    if (turn > maxTurnAchieved) {
      maxTurnAchieved = turn;
    }

    // Check if the player has reached a new milestone
    if (turn >= nextMilestone) {
      playHappyMelody();  // Play happy melody at new milestones
      nextMilestone += 5; // Set the next milestone
    }

    // Generate the next random number
    randomArray[turn] = random(1, 5);  // Generate the next random number
    turn++;  // Increment the turn
  } else {
    // Input was incorrect, reset the game
    turn = 1;
    // Do not reset melodyPlayed, nextMilestone, or maxTurnAchieved
    randomArray[0] = random(1, 5);  // Generate a new first random number
  }
}

bool input() {
  for (int x = 0; x < turn;) {
    bool buttonPressed = false;
    for (int y = 0; y < 4; y++) {
      buttonstate = digitalRead(button[y]); // Check for button push

      if (buttonstate == LOW) {
        buttonPressed = true;

        digitalWrite(ledpin[y], HIGH);

        // Map button presses to input values
        inputArray[x] = y + 1;

        // Play corresponding note
        switch (y) {
          case 0:
            speakerpin.play(NOTE_G3, 100);
            break;
          case 1:
            speakerpin.play(NOTE_A3, 100);
            break;
          case 2:
            speakerpin.play(NOTE_B3, 100);
            break;
          case 3:
            speakerpin.play(NOTE_C4, 100);
            break;
        }

        delay(200);
        digitalWrite(ledpin[y], LOW);
        delay(250);

        // Check if the input matches the pattern
        if (inputArray[x] != randomArray[x]) {
          fail();
          return false;  // Return false to indicate failure
        }
        x++;  // Move to the next input
        break;  // Exit the inner loop since a button was pressed
      }
    }
    if (!buttonPressed) {
      delay(50); // Small delay to avoid busy loop
    }
  }
  delay(500);
  return true;  // Return true to indicate success
}

void fail() {
  for (int y = 0; y <= 2; y++) {
    digitalWrite(ledpin[0], HIGH);
    digitalWrite(ledpin[1], HIGH);
    digitalWrite(ledpin[2], HIGH);
    digitalWrite(ledpin[3], HIGH);
    speakerpin.play(NOTE_G3, 300);
    delay(200);
    digitalWrite(ledpin[0], LOW);
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], LOW);
    digitalWrite(ledpin[3], LOW);
    speakerpin.play(NOTE_C3, 300);
    delay(200);
  }
  delay(500);
}

void playHappyMelody() {
  for (int i = 0; i < 7; i++) {
    // Play the note
    speakerpin.play(happyTune[i]);

    // Blink all LEDs
    digitalWrite(ledpin[0], HIGH);
    digitalWrite(ledpin[1], HIGH);
    digitalWrite(ledpin[2], HIGH);
    digitalWrite(ledpin[3], HIGH);

    // Wait for the duration of the note
    delay(happyDuration[i]);

    // Stop the note
    speakerpin.stop();

    // Turn off all LEDs
    digitalWrite(ledpin[0], LOW);
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], LOW);
    digitalWrite(ledpin[3], LOW);

    // Short delay between notes
    delay(50);
  }
  delay(500);  // Pause after the melody finishes
}
