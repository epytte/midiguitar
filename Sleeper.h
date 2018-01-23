#ifndef SLEEPER_H
#define SLEEPER_H

#include <Arduino.h>



class Sleeper {
    private:
        unsigned long lastNoteTime;        

    public:
        Sleeper();
        void idle(int note);
        void sleep();    
};

#endif
