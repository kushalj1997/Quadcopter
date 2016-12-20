//
//  Gyroscope.h
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/5/15.
//
//

#ifndef __Kushal_Quadcopter__Gyroscope__
#define __Kushal_Quadcopter__Gyroscope__


#include <Arduino.h>
#include <stdio.h>
#include "Sensor.h"

class Gyroscope : public Sensor{
public:
    Gyroscope();
    float getRoll();
    float getPitch();
    float getYaw();
    void read();
    void init();
private:
    float roll, pitch, yaw;
    float gyro_data[3];
    Sensor *device;
};

#endif /* defined(__Kushal_Quadcopter__Gyroscope__) */
