#include "GuitarString.h"
#include "MidiOutput.h"
#include "Sleeper.h"

// Guitar strings are connected to D3-D8.
// D2 connected to A0.
// A0 connected to VCC through 470k.
// A0 connected to D10 through 1k.

// D10 is used to activate the voltage divider for the AD-converter.
// When D10 is in high impedance mode, A0/D2 is pulled high through a 470k resistor
// and will be pulled low when a string connects to a fret for triggering the 
// interrupt to wake up from sleep.


Sleeper sleeper;
GuitarString e2String(41, A0, 8);
GuitarString aString(46, A0, 7);
GuitarString dString(51, A0, 6);
GuitarString gString(56, A0, 5);
GuitarString bString(60, A0, 4);
GuitarString eString(65, A0, 3);
MidiOutput midi;

void setup() {    
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);   // Set 1k resistor high.
    //Serial.begin(9600);
    //Serial.println("Starting");
}

void loop() {
    // Start with the lowest string.
    int note = e2String.getNote();
    if (note < 0)
        note = aString.getNote();
    if (note < 0)
        note = dString.getNote();
    if (note < 0)
        note = gString.getNote();
    if (note < 0)
        note = bString.getNote();
    if (note < 0)
        note = eString.getNote();

    midi.noteOn(note);  // Note can be -1 if no note is pressed. Will then send noteOff.
    sleeper.idle(note);
}
