//
//  Transmitter.h
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/5/15.
//
//

#ifndef __Kushal_Quadcopter__Transmitter__
#define __Kushal_Quadcopter__Transmitter__

#include <stdio.h>
#include <Arduino.h>

#define THROTTLEPIN 4
#define ROLLPIN 2
#define PITCHPIN 5
#define YAWPIN 6
#define GEARPIN 7
#define FLAPPIN 8

#define TRANSMITTERMIN 1100
#define TRANSMITTERZERO 1450
#define TRANSMITTERMAX 1800
#define MAXDEGS 30

class Transmitter {
  public:
    Transmitter();
    float getThrottle();
    float getRoll();
    float getPitch();
    float getYaw();
    short getGear();
    short getFlap();
    void read();
    boolean isArmed();
    void printData();
  private:
    float throttle, roll, pitch, yaw;
    short gear, flap;
    boolean armed;
    float mapReceiverToDegrees(unsigned int axis);
    unsigned int getRaw(int pin);
};

#endif /* defined(__Kushal_Quadcopter__Transmitter__) */
