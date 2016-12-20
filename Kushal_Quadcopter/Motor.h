//
//  Motor.h
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/5/15.
//
//

#ifndef __Kushal_Quadcopter__Motor__
#define __Kushal_Quadcopter__Motor__

#include <Arduino.h>
#include <stdio.h>
#include <Servo.h>

class Motor {
  public:
    Motor(int pin);
    void run(int speed);
    void kill();
  private:
    Servo ESC;
};

#endif /* defined(__Kushal_Quadcopter__Motor__) */
