#include "MicroBit.h"
#include "vector"

MicroBit uBit;

MicroBitPin BTN1(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_ALL);
MicroBitPin BTN2(MICROBIT_ID_IO_P1, MICROBIT_PIN_P1, PIN_CAPABILITY_ALL);
MicroBitPin BTN3(MICROBIT_ID_IO_P2, MICROBIT_PIN_P2, PIN_CAPABILITY_ALL);
MicroBitPin BTN4(MICROBIT_ID_IO_P8, MICROBIT_PIN_P8, PIN_CAPABILITY_ALL);
MicroBitPin LIGHT1(MICROBIT_ID_IO_P12, MICROBIT_PIN_P12, PIN_CAPABILITY_ALL);
MicroBitPin LIGHT2(MICROBIT_ID_IO_P13, MICROBIT_PIN_P13, PIN_CAPABILITY_ALL);
MicroBitPin LIGHT3(MICROBIT_ID_IO_P14, MICROBIT_PIN_P14, PIN_CAPABILITY_ALL);
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

void displayAction(char* action, float delay) {
    
    if (strcmp(action, "BTN1") == 0) {
        LIGHT1.setDigitalValue(1);
        wait(delay);
        LIGHT1.setDigitalValue(0);
    } else if (strcmp(action, "BTN2") == 0) {
        LIGHT2.setDigitalValue(1);
        wait(delay);
        LIGHT2.setDigitalValue(0);
    } else if (strcmp(action, "BTN3") == 0) {
        LIGHT3.setDigitalValue(1);
        wait(delay);
        LIGHT3.setDigitalValue(0);
    } else if (strcmp(action, "BTN4") == 0) {
        LIGHT4.setDigitalValue(1);
        wait(delay);
        LIGHT4.setDigitalValue(0);
    }
    
}

bool listenForInput(char* action) {
    
    int start = clock();
    double diff;
    
    // for each, add event listener, then remove after 3 seconds
    if (strcmp(action, "BTN1") == 0) {
        
        do {
            if (BTN1.getDigitalValue() == 1) { 
                displayAction("BTN1", 0.3);
                return true; 
            }
            if (BTN2.getDigitalValue() == 1) { 
                displayAction("BTN2", 0.3);
                return false; 
            }
            if (BTN3.getDigitalValue() == 1) { 
                displayAction("BTN3", 0.3);
                return false; 
            }
            if (BTN4.getDigitalValue() == 1) { 
                displayAction("BTN4", 0.3);
                return false; 
            }
            diff = (clock()-start)/(double)(CLOCKS_PER_SEC);
        } while (diff < 3);
        
    } else if (strcmp(action, "BTN2") == 0) {
        
        do {
            if (BTN1.getDigitalValue() == 1) { 
                displayAction("BTN1", 0.3);
                return false; 
            }
            if (BTN2.getDigitalValue() == 1) { 
                displayAction("BTN2", 0.3);
                return true; 
            }
            if (BTN3.getDigitalValue() == 1) { 
                displayAction("BTN3", 0.3);
                return false; 
            }
            if (BTN4.getDigitalValue() == 1) { 
                displayAction("BTN4", 0.3);
                return false; 
            }
            diff = (clock()-start)/(double)(CLOCKS_PER_SEC);
        } while (diff < 3);
        
    } else if (strcmp(action, "BTN3") == 0) {
        
        do {
            if (BTN1.getDigitalValue() == 1) { 
                displayAction("BTN1", 0.3);
                return false; 
            }
            if (BTN2.getDigitalValue() == 1) { 
                displayAction("BTN2", 0.3);
                return false; 
            }
            if (BTN3.getDigitalValue() == 1) { 
                displayAction("BTN3", 0.3);
                return true; 
            }
            if (BTN4.getDigitalValue() == 1) { 
                displayAction("BTN4", 0.3);
                return false; 
            }
            diff = (clock()-start)/(double)(CLOCKS_PER_SEC);
        } while (diff < 3);
        
    } else if (strcmp(action, "BTN4") == 0) {
        
        do {
            if (BTN1.getDigitalValue() == 1) { 
                displayAction("BTN1", 0.3);
                return false; 
            }
            if (BTN2.getDigitalValue() == 1) { 
                displayAction("BTN2", 0.3);
                return false; 
            }
            if (BTN3.getDigitalValue() == 1) { 
                displayAction("BTN3", 0.3);
                return false; 
            }
            if (BTN4.getDigitalValue() == 1) { 
                displayAction("BTN4", 0.3);
                return true; 
            }
            diff = (clock()-start)/(double)(CLOCKS_PER_SEC);
        } while (diff < 3);
        
    }
    
    return false;
    
}

void onIncorrectInput() {
    uBit.display.scroll("GAME OVER :(");
}

int main() {
    
    uBit.init();
    bool gameOver = false;
    int level = 0;
    std::vector<char*> sequence;
    
    while(gameOver == false) {
        
        level = level+1;
        
        uBit.display.print(level);
        wait(0.5);
        uBit.display.print("");
        
        sequence.push_back(selectRandomAction());
        
        // display sequence with LEDS
        
        for (int i = 0; i < level; i++) {
            displayAction(sequence[i], 1);
        }
        
        // wait for user input until sequence is complete or time for input runs out, if input is incorrect then end game and exit loop, if not repeat loop
        
        for (int i = 0; i < level; i++) {
            bool inputIsCorrect = listenForInput(sequence[i]);
            if (inputIsCorrect == false) {
                gameOver = true;
                break;
            }
            wait(0.25);
        }
        
    }
    
    onIncorrectInput();
    release_fiber();
}
