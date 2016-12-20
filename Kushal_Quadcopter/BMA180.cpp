//
//  BMA180.cpp
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/6/15.
//
//

#include "BMA180.h"

float BMA180::ax = 0;
float BMA180::ay = 0;
float BMA180::az = 0;

BMA180::BMA180() {
}

void BMA180::init() {
    byte temp[1];
    byte temp1;

    I2C::writeTo(BMA, RESET, 0xB6);

    I2C::writeTo(BMA, PWR, 0x10); //wake up mode

    I2C::readFrom(BMA, BW, 1, temp); // low pass filter to 10Hz
    temp1 = temp[0] & 0x0F;
    I2C::writeTo(BMA, BW, temp1);

    I2C::readFrom(BMA, RANGE, 1 , temp); // range +/- 2g
    temp1 = (temp[0] & 0xF1) | 0x04;
    I2C::writeTo(BMA, RANGE, temp1);
}

void BMA180::read() {
    // read in the 3 axis data, each one is 14 bits

    byte result[6];
    I2C::readFrom(BMA, DATA, 6, result);

    //    Read the stuff from the I2C bus and then convert it to acceleration in G's
    ax = ((( result[0] | result[1] << 8) >> 2) + OFFX) / LSBTOGS;
    ay = ((( result[2] | result[3] << 8 ) >> 2) + OFFY) / LSBTOGS;
    az = ((( result[4] | result[5] << 8 ) >> 2) + OFFZ) / LSBTOGS;
}

float BMA180::getPitch() {
    // Pitch is the x axis on the sensor
    //    Commented calculations give 90 as level reading, I want 0 as level reading so I use the second calculation
    //    float fv = getForceVector();
    //    return RAD2DEG * acos(ax/fv);
    return RAD2DEG * atan(-ax / sqrt(pow(ay, 2) + pow(az, 2)));
}

float BMA180::getRoll() {
    // Roll is the y axis on the sensor
    //    Commented calculations give 90 as level reading, I want 0 as level reading so I use the second calculation
    //    float fv = getForceVector();
    //    return RAD2DEG * acos(ay/fv);
    return RAD2DEG * atan(-ay / sqrt(pow(ax, 2) + pow(az, 2)));
}

float BMA180::getDownGForce() {
    float fv = getForceVector();
    return RAD2DEG * atan(sqrt(pow(ax, 2) + pow(ay,2)) / az);
}

float BMA180::getForceVector() {
    return sqrt(pow(ax, 2) + pow(ay, 2) + pow(az, 2));  
}

