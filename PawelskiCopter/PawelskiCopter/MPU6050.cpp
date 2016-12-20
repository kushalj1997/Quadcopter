//
//  MPU6050.cpp
//  PawelskiCopter
//
//  Created by Kushal Jaligama on 1/31/16.
//  Copyright © 2016 Kushal Jaligama. All rights reserved.
//

#include "MPU6050.hpp"

void MPU6050Init() {
    TWIStart();
    TWIWrite(MPU6050ADDR);
    TWIWrite(0x6b); // PWR_MGMT_1 Register
    TWIWrite(0); // Wake Device
    TWIStop();
    
    // Set 2000 deg/s
    TWIStart();
    TWIWrite(MPU6050ADDR);
    TWIWrite(0x1b);
    TWIWrite(0x18);
    TWIStop();
    
}

void MPU6050Read() {
    TWIStart();
    TWIWrite(MPU6050ADDR);
    TWIWrite(0x3b);
    TWIStart();
    TWIWrite(MPU6050ADDR);
    TWIReadNACK();
    
    /**
     * Begin reading values sequentally
     * all values are 16 bit, transfered as big endian.
     */
    ax = (TWIReadACK()<<8) | TWIReadACK();
    ay = (TWIReadACK()<<8) | TWIReadACK();
    az = (TWIReadACK()<<8) | TWIReadACK();
    temp = (double)((TWIReadACK()<<8) | TWIReadACK()) / 340.00 + 36.53;
    gx = ((TWIReadACK()<<8) | TWIReadACK()) - z_gx;
    gy = ((TWIReadACK()<<8) | TWIReadACK()) - z_gy;
    gz = ((TWIReadACK()<<8) | TWIReadNACK()) - z_gz;
    
    const double gyroK = (long double)/* max deg/s */2000 /
    ((long double)/* 2^15 */32768) * /*Deg to rad*/(3.14159265359/180);
    
    gx *= gyroK;
    gy *= gyroK;
    gz *= gyroK;
    
    TWIStop();
}

double MPU6050GyroX() {
    return gx;
}

double MPU6050GyroY() {
    return gy;
}

double MPU6050GyroZ() {
    return gz;
}

double MPU6050AccelX() {
    return RAD2DEG * atan((float)-ay /
                          sqrt(pow((float)ax, 2) + pow((float)az, 2)));

}

double MPU6050Accely() {
    return RAD2DEG * atan((float)-ax /
                          sqrt(pow((float)ay, 2) + pow((float)az, 2)));;
}

double MPU6050AccelZ () {
    return az;
}
