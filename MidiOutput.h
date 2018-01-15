#ifndef MIDIOUTPUT_H
#define MIDIOUTPUT_H

#include <Arduino.h>
#include <SoftwareSerial.h>

/*
 * A simple class for sending notes though the midi interface.
 * 
 * The millisNoteDelay specifies how many milliseconds to wait for another note value
 * before sending the noteOn. This is to prevent the notes from being sent too quickly
 * and will also filter out some very short notes that should not be sent.
 * 
 * Makes sure that only one note can be played at any time. So this midi class is only
 * monophonic.
 * 
 * We use the SoftwareSerial so that we still have the normal Serial for debugging.
 */

class MidiOutput {
    private:
        const int millisNoteDelay = 4;
        const byte midiNoteOn = 144;
        const byte midiNoteOff = 128;
        const int voiceMidiChannel = 0;
        const int midiVelocity = 100;
        
        long startTime;
        int activeNote;
        SoftwareSerial* midi; // RX, TX
        void command(int command, int note, int velocity);
        
    public:
        MidiOutput();
        void noteOn(int note);
        void noteOff();
        void idle();        
};

#endif
