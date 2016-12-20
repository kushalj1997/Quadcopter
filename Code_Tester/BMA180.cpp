//
//  BMA180.cpp
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/6/15.
//
//

#include "BMA180.h"

int BMA180::accelx = 0;
int BMA180::accely = 0;
int BMA180::accelz = 0;

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

  accelx = (( result[0] | result[1] << 8) >> 2) + OFFX;
  accely = (( result[2] | result[3] << 8 ) >> 2) + OFFY;
  accelz = (( result[4] | result[5] << 8 ) >> 2) + OFFZ;
}

float BMA180::getPitch() {
  return accelx / LSBTOGS;
}

float BMA180::getRoll() {
  return accely / LSBTOGS;
}

float BMA180::getDownGForce() {
  return accelz / LSBTOGS;
}
