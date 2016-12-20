//
//  LED.h
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/5/15.
//
//

#ifndef __Kushal_Quadcopter__LED__
#define __Kushal_Quadcopter__LED__

#include <Arduino.h>
#include <stdio.h>

class LED {
  public:
    LED(int pin);
    void on();
    void off();
    boolean state();
  private:
    int LedPin;
    boolean isOn;
};


#endif /* defined(__Kushal_Quadcopter__LED__) */
