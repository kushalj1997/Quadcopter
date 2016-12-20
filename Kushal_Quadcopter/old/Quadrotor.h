//
//  Quadrotor.h
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/5/15.
//
//

#ifndef __Kushal_Quadcopter__Quadrotor__
#define __Kushal_Quadcopter__Quadrotor__

#include <stdio.h>
#include <Arduino.h>
#include "Motor.h"
#include "LED.h"
#include "IMU.h"

#define MINCOMMAND 1100
#define MIDCOMMAND 1450
#define MAXCOMMAND 1800

class Quadrotor {
  public:
    Quadrotor();
    void stabilize();
    boolean isArmed();
  private:
    boolean armed;

    unsigned int pitchTarget;
    unsigned int rollTarget;
    unsigned int yawTarget;

    Motor *frontLeft;
    Motor *frontRight;
    Motor *rearRight;
    Motor *rearLeft;
    
    void commandAllMotors(unsigned int speed);
    void killAllMotors();
    void corrections();
};

#endif /* defined(__Kushal_Quadcopter__Quadrotor__) */
