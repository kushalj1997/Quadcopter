//
//  IMU.hpp
//  PawelskiCopter
//
//  Created by Kushal Jaligama on 1/22/16.
//  Copyright © 2016 Kushal Jaligama. All rights reserved.
//

#ifndef IMU_hpp
#define IMU_hpp

#include <stdio.h>
#include "MPU6050.hpp"

class IMU {
public:
    IMU();
    float getRoll();
    float getPitch();
    float getYaw();
    void setMode(int flightMode);
    void read();
private:
    float roll, pitch, yaw;
    int flightMode;
    double compFilter(double rate, double angle);
};

#endif /* IMU_hpp */