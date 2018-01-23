#include "MidiOutput.h"

MidiOutput::MidiOutput() {
    activeNote = 0;
    startTime = 0;
    midi = new SoftwareSerial(12, 9);  // RX=12, TX=9
    midi->begin(31250);
}

void MidiOutput::noteOn(int note) {
   if (note <= 0)  // Note <= 0 means send noteOff if necessary.
      noteOff();
   else if (note != activeNote) {
       noteOff();  // Make sure any playing note is turned off.
       activeNote = note;
       startTime = millis();      
   }

   // Check if we have a waiting note to send.
   if (startTime > 0 && (millis() > startTime + millisNoteDelay)) {
      // After the timeout, we actually send the noteOn.
      command(midiNoteOn, activeNote, midiVelocity);  // Send the noteOn.
      startTime = 0;
   }
}

/*
 * Turn off any playing note. Does nothing if no note is active.
 */
void MidiOutput::noteOff() {
   // Check that we have an active note and that a noteOn has been sent.
   if (activeNote > 0 && startTime == 0) {
      command(midiNoteOff, activeNote, midiVelocity);
      activeNote = 0;
   }
}

void MidiOutput::command(int command, int note, int velocity) {
    midi->write(command + voiceMidiChannel);
    midi->write(note);
    midi->write(velocity); 
}
