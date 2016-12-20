//
//  Accelerometer.h
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/5/15.
//
//

#ifndef __Kushal_Quadcopter__Accelerometer__
#define __Kushal_Quadcopter__Accelerometer__


#include <Arduino.h>
#include <stdio.h>
#include "Sensor.h"

class Accelerometer : public Sensor{
public:
    Accelerometer();
    float getRoll();
    float getPitch();
    float getYaw();
    void read();
    void init();
private:
    float roll, pitch, yaw;
    float accelerometer_data[3];
};

#endif /* defined(__Kushal_Quadcopter__Accelerometer__) */
