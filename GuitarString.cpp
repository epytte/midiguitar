#include "GuitarString.h"

GuitarString::GuitarString(int startNote_, int apin_, int dpin_) {
    startNote = startNote_;
    apin = apin_;
    dpin = dpin_;
    pinMode(dpin, INPUT);  // Set the pin in high impedance mode.
    digitalWrite(dpin, LOW);
}

int GuitarString::getNote() {
    pinMode(dpin, OUTPUT);
    digitalWrite(dpin, LOW);   // Put the string to ground.
    delayMicroseconds(5);
    
    int test = analogRead(apin);   // Now read the fret value.
    int count = 0;                 // We need to read the same value a few times to be satisfied.

    for (int i=0; i<1000; i++) {   // Lets try max 1000 samples to find a steady value.
        int input = analogRead(apin);
        if (input == test || input - test < 4 || test - input < 4) {  // Allow a vlue of +/- 2.
            if (++count == 10) {
                if (input > 1010)   // The string is not touching the fret.
                    break;
                pinMode(dpin, INPUT);  // Set the pin in high impedance mode.
                return (20 - (input + 25)/50) + startNote;
            }
        }
        else {
            test = input;
            count = 0;
        }
    }
    pinMode(dpin, INPUT);  // Set the pin in high impedance mode.
    return -1;  // No fret contact could be found.
}
