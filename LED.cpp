#include "LED.h"

#define TICKS_PER_CYCLE      20           // Number of ticks in a PWM cycle
#define SMOOTH_INCREMENT      1           // Add this much to smooth modes per tick
#define TICKS_PER_BLINK     100           // Blinks on and off in this many ticks 

LED::LED( uint8_t pinNumber)
{
    Initialize( pinNumber);
}

LED::LED() {
}

void LED::Initialize( uint8_t pinNumber)
{
    pinMode( pinNumber, OUTPUT);
    pin = pinNumber;
    mode = OFF;
    ticks = 0;
    intensity = 0;
    isOnWhenHigh = true;
    smoothDelay = 2;
}

    
void LED::SetIntensity( uint8_t newIntensity)
{
    intensity = newIntensity;
    pwmCounter = 0;
}

void LED::SetMode(Mode newMode)
{
    mode = (Mode) newMode;
    switch (mode) {
    case ON:
        SetIntensity(255);
        break;
    case OFF:
        SetIntensity(0);
        break;
    case SMOOTH_ON:
        break;
    case SMOOTH_OFF:
        break;
    case THROB:
        if (intensity == 0) {
            throbbingUp = true;
        } else {
            throbbingUp = false;
        }
        break;
    case BLINK:
        intensity = 0;
        break;
    case MOMENTARY:
        break;
    }
}

void LED::Update() {
    ++ticks;
    switch(mode) {
    case SMOOTH_ON:
        if (intensity + SMOOTH_INCREMENT <= 255) {
            intensity += SMOOTH_INCREMENT;
        } else {
            intensity = 255;
        }
        break;
    case SMOOTH_OFF:
        if (intensity - SMOOTH_INCREMENT >= 0) {
            if (ticks % smoothDelay == 0) intensity -= SMOOTH_INCREMENT;
        } else {
            intensity = 0;
        }
        break;
    case THROB:
        if (intensity == 0) {
            throbbingUp = true;
        } else if (intensity == 255) {
            throbbingUp = false;
        }
        if (throbbingUp)  {
            if (ticks % smoothDelay == 0) intensity += 1;
        } else {
            if (ticks % smoothDelay == 0) intensity -= 1;
        }
        break;    
    case BLINK:
        if ((ticks % TICKS_PER_BLINK) < TICKS_PER_BLINK/2) {
            // Turn off
            digitalWrite( pin, isOnWhenHigh ? LOW : HIGH);
        } else {
            // Turn on
            digitalWrite( pin, isOnWhenHigh? HIGH : LOW);
        }
        return;
        break;
    case MOMENTARY:
        if (intensity == 255) {
            mode = MOMENTARY_DOWN;
        } else {
            intensity++;
        }
        break;
    case MOMENTARY_DOWN:
        if (intensity == 0) {
            mode = OFF;
        } else {
            intensity--;
        }
        break;
    }
    pwmCounter += intensity;
    if (pwmCounter >= 255) {
        // Turn on
        digitalWrite( pin, isOnWhenHigh ? HIGH : LOW);
        pwmCounter -= 255;
    } else {
        // Turn off
        digitalWrite( pin, isOnWhenHigh ? LOW : HIGH);
    }
}
