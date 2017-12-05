#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>

//
// A class to represent a clock that keeps track of hours, minutes, and seconds
//
// Written by Tony DeRose, November 2012
//

class Clock
{
public:
    Clock();
    
    Clock( uint8_t hours, uint8_t minutes, uint8_t seconds, bool am);
    
    void Update();               // Call every time the loop() function is entered
    
    uint8_t GetSeconds() {
        return _seconds;
    }
    
    uint8_t GetMinutes() {
        return _minutes;
    }
    
    uint8_t GetHours() {
        return _hours;
    }
    
    bool    GetAm() {
        return _am;
    }
    
    bool HasChanged() {
        if (_hasChanged) {
            _hasChanged = false;
            return true;
        }
        return false;
    }
    
    void SetTime( uint8_t hours, uint8_t minutes, uint8_t seconds, bool am);
    
    // Return this - c in seconds
    long int DifferenceInSeconds(Clock c);
    
private:
    void init();
    uint8_t _seconds;
    uint8_t _minutes;
    uint8_t _hours;
    bool    _am;
    long int _millis;
    bool     _hasChanged;
};

#endif

