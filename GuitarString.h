#ifndef GUITARSTRING_H
#define GUITARSTRING_H

#include <Arduino.h>

/*
 * Represents one guitar string. Have a reference to an anlog pin where the analog fretvalue is read.
 * Also has a startNode which is the lowest note for the string (for an open string).
 * 
 * The dpin is the digital pin that needs to be set to 0 when the fretvalue is being read. When
 * this string is not reading the fret value, the dpin must be set in high impedance mode to
 * not interfere with the other strings. Only one string is grounded at a time to get an analog
 * value from the voltage divider.
 */

class GuitarString {
    private:
        int startNote;
        int apin;
        int dpin;

    public:
        GuitarString(int startNote_, int apin_, int dpin_);
        int getNote();    
};

#endif
