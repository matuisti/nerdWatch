#include "Clock.h"

Clock::Clock()
{
    init();
    SetTime( 1, 0, 0, true);
}

Clock::Clock(uint8_t hours, uint8_t minutes, uint8_t seconds, bool am)
{
    init();
    SetTime( hours, minutes, seconds, am);
}

void Clock::init()
{
    _millis = millis();
    _hasChanged = true;
}

void Clock::Update()
{
    long int now = millis();
    if ((now - _millis) < 0) {
        // millis() wrapped around - it happens about every 50 days
        _millis = 0;
    }
    if ((now - _millis) >= 1000) {
        // A second has past since I last updated my values ... update again
        _millis = now;
        _seconds++;
        _hasChanged = true;
        if (_seconds == 60) {
            // Carry over to minutes
            _seconds = 0;
            _minutes++;
            if (_minutes == 60) {
                // Carry over to hours
                _minutes = 0;
                _hours++;
                if (_hours == 12) {
                    // Toggle am
                    _am = !_am;
                } else if (_hours == 13) {
                    // Wrap back to 1:00
                    _hours = 1;
                }
            }
        }
    }
}

void Clock::SetTime( uint8_t hours, uint8_t minutes, uint8_t seconds, bool am)
{
    _hours = hours;
    _minutes = minutes;
    _seconds = seconds;
    _am = am;
    _millis = millis();
}

long int modularDifference( long int a, long int n, long int m)
{
    long int an = (a-n)%m;
    long int na = (n-a)%m;
    if (abs(na) < abs(an)) {
        return na;
    }
    return an;
}

long int Clock::DifferenceInSeconds(Clock c)
{
    long int thisInSeconds = (_hours * 60 + _minutes) * 60 + _seconds;
    long int secondsIn12Hours = ((long int) 12) * ((long int) 3600);
    long int secondsIn24Hours = ((long int) 12) * ((long int) 3600);

    if (!_am) {
        thisInSeconds += secondsIn12Hours;
    }
    long int cInSeconds = (c._hours * 60 + c._minutes) * 60 + c._seconds;
    if (!c._am) {
        cInSeconds += secondsIn12Hours;
    }
    return modularDifference( thisInSeconds, cInSeconds, secondsIn24Hours);
}



