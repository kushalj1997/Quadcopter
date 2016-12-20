//
//  ITG3200.cpp
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/6/15.
//
//

#include "ITG3200.h"

float ITG3200::gx = 0;
float ITG3200::gy = 0;
float ITG3200::gz = 0;

float XOFF = 0;
float YOFF = 0;
float ZOFF = 0;

ITG3200::ITG3200() {
}

void ITG3200::init() {
  I2C::writeTo(ITG, RESET, 0x80); // Reset Gyro
  I2C::writeTo(ITG, FILTER, 0x1D); // Low Pass filter to 10 Hz
  I2C::writeTo(ITG, RESET, 0x01); // Use internal oscillator

  delay(1000); // So that calibration doesn't get screwed, settling time I guess

  // Calibration
  for (int i = 0; i < 500; i++) {
    read();
    XOFF += gx;
    YOFF += gy;
    ZOFF += gz;
  }

  XOFF /= 500;
  YOFF /= 500;
  ZOFF /= 500;
}

void ITG3200::read() {
  byte buffer[6];
  I2C::readFrom(ITG, DATA, 6, buffer);
  gx = ((((int16_t)buffer[0]) << 8) | buffer[1]) / LSBTODEGS;
  gy = ((((int16_t)buffer[2]) << 8) | buffer[3]) / LSBTODEGS;
  gz = ((((int16_t)buffer[4]) << 8) | buffer[5]) / LSBTODEGS;
}

float ITG3200::getPitch() {
  // Y axis
  return (gy - YOFF);
}

float ITG3200::getRoll() {
  // X Axis
  return (gx - XOFF);
}

float ITG3200::getYaw() {
  // Z Axis
  return (gz - ZOFF);
}
