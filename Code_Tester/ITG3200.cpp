//
//  ITG3200.cpp
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/6/15.
//
//

#include "ITG3200.h"

int ITG3200::gyrox = 0;
int ITG3200::gyroy = 0;
int ITG3200::gyroz = 0;

ITG3200::ITG3200() {
}

void ITG3200::init() {
  I2C::writeTo(ITG, RESET, 0x80); // Reset Gyro
  I2C::writeTo(ITG, FILTER, 0x1D); // Low Pass filter to 10 Hz
  I2C::writeTo(ITG, RESET, 0x01); // Use internal oscillator
}

void ITG3200::read() {
  byte buffer[6];
  I2C::readFrom(ITG, DATA, 6, buffer);
  gyrox = (((int16_t)buffer[0]) << 8) | buffer[1];
  gyroy = (((int16_t)buffer[2]) << 8) | buffer[3];
  gyroz = (((int16_t)buffer[4]) << 8) | buffer[5];
}

float ITG3200::getPitch() {
  return gyrox / LSBTODEGS;
}

float ITG3200::getRoll() {
  return gyroy / LSBTODEGS;
}

float ITG3200::getYaw() {
  return gyroz / LSBTODEGS;
}
