#include "MicroBit.h"

MicroBit uBit;

// BTN 1 - 4
// BTN 2 - 6
// BTN 3 - 7
// BTN 4 - 9

// LED 1 - 0
// LED 2 - 1
// LED 3 - 2
// LED 4 - 3

int main() {
    
    uBit.init();
    bool gameOver = false;
    int level = 0;
    string sequence[10];
    
    while(gameOver == false) {
        
        level++;
        
        // add action to sequence, if array is full than double the size
        
        if (level == sizeof(sequence)/sizeof(*sequence)) {
            string newSequence[sizeof(sequence)/sizeof(*sequence) * 2];
            for (int i = 0; i < level; i++) {
                newSequence[i] = sequence[i];
                sequence = newSequence;
            }
        }
        
        sequence[level-1] = selectRandomAction();
        
        // display sequence with LEDS
        
        for (int i = 0; i < level; i++) {
            displayAction(sequence[i]);
        }
        
        // wait for user input until sequence is complete or time for input runs out, if input is incorrect then end game and exit loop, if not increment level and repeat loop
        
        for (int i = 0; i < level; i++) {
            bool inputIsCorrect = listenForInput(sequence[i]);
            if (inputIsCorrect == false {
                gameOver = true;
                onIncorrectInput();
                break;
            } else {
                onCorrectInput();
            }
        }
        
    }
    
    release_fiber();
}

string selectRandomAction() {
    
    int random = rand() % 4; 
    string action = "";
    
    if (random == 0) {
        action = "BTN1";
    } else if (random == 1) {
        action = "BTN2";
    } else if (random == 2) {
        action = "BTN3";
    } else if (random == 3) {
        action = "BTN4";
    }
    
    return action;
}

void diplayAction(string action) {
    
}

bool listenForInput() {
    
}

// display something happy on microcontroller
void onCorrectInput() {
    
}

// display something sad on microcontroller
void onIncorrectInput() {
    
}
