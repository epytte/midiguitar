#include "Sleeper.h"
#include "Interrupt.h"
#include <LowPower.h>

Sleeper::Sleeper() {
    lastNoteTime = 0;
    pinMode(2, INPUT);  // The interrupt pin.
}

void Sleeper::idle(int note) {
    if (note <= 0) {
        if (lastNoteTime == 0)
            lastNoteTime = millis();
        else if (lastNoteTime != 0 && millis() > lastNoteTime + 1000)
            sleep();
    }
    else
        lastNoteTime = 0;
}

void Sleeper::sleep() {
    pinMode(10, INPUT);  // Set the pin to the 1k resistor floating.
    digitalWrite(10, LOW);
    // Set all strings to ground so they can all trigger the interrupt.
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    attachInterrupt(0, digitalInterrupt, FALLING);
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    detachInterrupt(0);
    // Set all the strings to high impedance mode again.
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(7, INPUT);
    pinMode(8, INPUT);
    pinMode(10, OUTPUT);  // The pin to the 1k resistor.
    digitalWrite(10, HIGH); // Set the 1k resistor pin high.
}
