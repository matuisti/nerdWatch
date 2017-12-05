#ifndef LED_H
#define LED_H

#include "Arduino.h"


class LED {
  public:
    typedef enum {
        OFF,
        ON,
        SMOOTH_OFF,
        SMOOTH_ON,
        THROB,
        BLINK,
        MOMENTARY,
        MOMENTARY_DOWN,
    } Mode;

    LED( uint8_t pinNumber);
	
    LED();
	
    int GetMode() {
        return mode;
    }
    
    uint8_t GetIntensity() {
      return intensity;
    }

    void Initialize( uint8_t pinNumber );

    void SetIntensity( uint8_t newIntensity);
    
    void SetIsOnWhenHigh( bool aBool) {
        isOnWhenHigh = aBool;
    }

    void SetMode(Mode newMode);
    
    // Wait this many ticks when changing intensity during smooth on, off, and trob.
    // Bigger numbers mean slower fades. Default is 2.
    void SetSmoothDelay( uint8_t delay) {
        smoothDelay= delay;
    }

    void Update();
    
  private:
    uint8_t         intensity;
    Mode            mode;
    uint8_t         pin;  
    unsigned int    pwmCounter;
    uint8_t         ticks;
    uint8_t         smoothDelay;
    bool            throbbingUp;
    bool            isOnWhenHigh;
};

#endif

