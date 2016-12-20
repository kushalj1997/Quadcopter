//
//  Sensor.h
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/5/15.
//
//

#ifndef __Kushal_Quadcopter__Sensor__
#define __Kushal_Quadcopter__Sensor__

#include <stdio.h>
#include <Wire.h>
#include <Arduino.h>

class Sensor{
public:
    Sensor();
    void i2c_write(int address, byte reg, byte data);
    unsigned char i2c_read(char address, char registerAddress);
};

#endif /* defined(__Kushal_Quadcopter__Sensor__) */
