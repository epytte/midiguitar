#include "GuitarString.h"
#include "MidiOutput.h"

GuitarString e2String(41, A0, 7);
GuitarString aString(46, A0, 6);
GuitarString dString(51, A0, 5);
GuitarString gString(56, A0, 4);
GuitarString bString(60, A0, 3);
GuitarString eString(65, A0, 2);
MidiOutput midi;

void setup() {
    //Serial.begin(9600);
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
    midi.idle();        // Let the midi class handle its timing.
}
