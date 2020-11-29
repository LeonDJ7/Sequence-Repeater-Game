#include "MicroBit.h"
#include "string"

MicroBit uBit;

// BTN 1 - 0
MicroBitPin BTN1(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_ALL);
// BTN 2 - 1
MicroBitPin BTN2(MICROBIT_ID_IO_P1, MICROBIT_PIN_P1, PIN_CAPABILITY_ALL);
// BTN 3 - 2
MicroBitPin BTN3(MICROBIT_ID_IO_P2, MICROBIT_PIN_P2, PIN_CAPABILITY_ALL);
// BTN 4 - 3
MicroBitPin BTN4(MICROBIT_ID_IO_P3, MICROBIT_PIN_P3, PIN_CAPABILITY_ALL);

// LED 1 - 4
MicroBitPin LIGHT1(MICROBIT_ID_IO_P12, MICROBIT_PIN_P12, PIN_CAPABILITY_ALL);
// LED 2 - 6
MicroBitPin LIGHT2(MICROBIT_ID_IO_P13, MICROBIT_PIN_P13, PIN_CAPABILITY_ALL);
// LED 3 - 7
MicroBitPin LIGHT3(MICROBIT_ID_IO_P14, MICROBIT_PIN_P14, PIN_CAPABILITY_ALL);
// LED 4 - 9
MicroBitPin LIGHT4(MICROBIT_ID_IO_P15, MICROBIT_PIN_P15, PIN_CAPABILITY_ALL);

char* selectRandomAction() {
    
    int random = rand() % 4;
    
    if (random == 0) {
        return "BTN1";
    } else if (random == 1) {
        return "BTN2";
    } else if (random == 2) {
        return "BTN3";
    } else if (random == 3) {
        return "BTN4";
    } else {
        return "";
    }
}

void displayAction(char* action) {
    
    if (strcmp(action, "BTN1") == 0) {
        LIGHT1.setDigitalValue(1);
        wait(1);
        LIGHT1.setDigitalValue(0);
    } else if (strcmp(action, "BTN2") == 0) {
        LIGHT2.setDigitalValue(1);
        wait(1);
        LIGHT2.setDigitalValue(0);
    } else if (strcmp(action, "BTN3") == 0) {
        LIGHT3.setDigitalValue(1);
        wait(1);
        LIGHT3.setDigitalValue(0);
    } else if (strcmp(action, "BTN4") == 0) {
        LIGHT4.setDigitalValue(1);
        wait(1);
        LIGHT4.setDigitalValue(0);
    }
    
}

bool listenForInput(char* action) {
    
    int start = clock();
    double diff;
    
    // for each, add event listener, then remove after 3 seconds
    if (strcmp(action, "BTN1") == 0) {
        
        do {
            if (BTN1.getDigitalValue() == 1) { return true; }
            diff = (clock()-start)/(double)(CLOCKS_PER_SEC);
        } while (diff < 3);
        
    } else if (strcmp(action, "BTN2") == 0) {
        
        do {
            if (BTN2.getDigitalValue() == 1) { return true; }
            diff = (clock()-start)/(double)(CLOCKS_PER_SEC);
        } while (diff < 3);
        
    } else if (strcmp(action, "BTN3") == 0) {
        
        do {
            if (BTN3.getDigitalValue() == 1) { return true; }
            diff = (clock()-start)/(double)(CLOCKS_PER_SEC);
        } while (diff < 3);
        
    } else if (strcmp(action, "BTN4") == 0) {
        
        do {
            if (BTN4.getDigitalValue() == 1) { return true; }
            diff = (clock()-start)/(double)(CLOCKS_PER_SEC);
        } while (diff < 3);
        
    }
    
    return false;
    
}

void onCorrectInput() {
    uBit.display.scroll(":)");
}

void onIncorrectInput() {
    uBit.display.scroll("GAME OVER :(");
}

int main() {
    
    uBit.init();
    bool gameOver = false;
    int level = 0;
    char* sequence[10];
    
    uBit.display.scroll("START!");
    
    while(gameOver == false) {
        
        
        level = level+1;
        
        // add action to sequence, if array is full than double the size
        
        if (level == sizeof(sequence)/sizeof(*sequence)) {
            char* newSequence[sizeof(sequence)/sizeof(*sequence) * 2];
            for (int i = 0; i < level; i++) {
                newSequence[i] = sequence[i];
                std::copy(newSequence, newSequence + level, sequence);
            }
        }
        
        sequence[level-1] = selectRandomAction();;
        
        
        // display sequence with LEDS
        
        for (int i = 0; i < level; i++) {
            displayAction(sequence[i]);
        }
        
        
        
        /*
        
        // wait for user input until sequence is complete or time for input runs out, if input is incorrect then end game and exit loop, if not repeat loop
        
        for (int i = 0; i < level; i++) {
            bool inputIsCorrect = listenForInput(sequence[i]);
            if (inputIsCorrect == false) {
                gameOver = true;
                onIncorrectInput();
                break;
            } else {
                onCorrectInput();
            }
        }
        
        */
        
    }
    
    
    
    release_fiber();
}
