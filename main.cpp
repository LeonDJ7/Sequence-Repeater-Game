#include "MicroBit.h"
#include "string"

string selectRandomAction();
void displayAction(string action);
bool listenForInput(string action);
void onCorrectInput();
void onIncorrectInput();

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
MicroBitPin LIGHT1(MICROBIT_ID_IO_P4, MICROBIT_PIN_P4, PIN_CAPABILITY_ALL);
// LED 2 - 6
MicroBitPin LIGHT2(MICROBIT_ID_IO_P6, MICROBIT_PIN_P6, PIN_CAPABILITY_ALL);
// LED 3 - 7
MicroBitPin LIGHT3(MICROBIT_ID_IO_P7, MICROBIT_PIN_P7, PIN_CAPABILITY_ALL);
// LED 4 - 9
MicroBitPin LIGHT4(MICROBIT_ID_IO_P9, MICROBIT_PIN_P9, PIN_CAPABILITY_ALL);

int main() {
    
    uBit.init();
    bool gameOver = false;
    int level = 0;
    string sequence[10] = {};
    
    //uBit.display.print("test");
    
    LIGHT1.setDigitalValue(0);
    wait(0.5);
    LIGHT1.setDigitalValue(1);
    wait(0.5);
    LIGHT1.setDigitalValue(0);
    wait(0.5);
    LIGHT1.setDigitalValue(1);
    
    while(gameOver == false) {
        
        level++;
        
        // add action to sequence, if array is full than double the size
        
        if (level == sizeof(sequence)/sizeof(*sequence)) {
            string newSequence[sizeof(sequence)/sizeof(*sequence) * 2] = {};
            for (int i = 0; i < level; i++) {
                newSequence[i] = sequence[i];
                std::copy(newSequence, newSequence + level, sequence);
            }
        }
        
        sequence[level-1] = selectRandomAction();
        
        // display sequence with LEDS
        
        for (int i = 0; i < level; i++) {
            displayAction(sequence[i]);
        }
        
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
        
    }
    
    release_fiber();
}

string selectRandomAction() {
    
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

void displayAction(string action) {
    
    if (action == "BTN1") {
        LIGHT1.setDigitalValue(1);
        wait(0.5);
        LIGHT1.setDigitalValue(0);
    } else if (action == "BTN2") {
        LIGHT2.setDigitalValue(1);
        wait(0.5);
        LIGHT2.setDigitalValue(0);
    } else if (action == "BTN3") {
        LIGHT3.setDigitalValue(1);
        wait(0.5);
        LIGHT3.setDigitalValue(0);
    } else if (action == "BTN4") {
        LIGHT4.setDigitalValue(1);
        wait(0.5);
        LIGHT4.setDigitalValue(0);
    }
    
}

bool listenForInput(string action) {
    
    // for each, add event listener, then remove after 3 seconds
    if (action == "BTN1") {
        
    } else if (action == "BTN2") {
        
    } else if (action == "BTN3") {
        
    } else if (action == "BTN4") {
        
    }
    
}

// display something happy on microcontroller
void onCorrectInput() {
    uBit.display.print(":)");
}

// display something sad on microcontroller
void onIncorrectInput() {
    uBit.display.print(":(");
}


