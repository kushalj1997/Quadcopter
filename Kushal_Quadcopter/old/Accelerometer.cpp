//
//  Accelerometer.cpp
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/5/15.
//
//

#include "Accelerometer.h"

Sensor *device;

Accelerometer::Accelerometer(){
  device = new Sensor();
  roll = pitch = yaw = 0;
  for (int i=0;i<3;++i) {
    accelerometer_data[i] = 0;
  }
}

void Accelerometer::read() {
  byte bytes[6];
  memset(bytes,0,6);

  //read 6 bytes from the ADXL345
  device->i2c_read(ADXL345_ADDRESS, ADXL345_REGISTER_XLSB, 6, bytes);

  //now unpack the bytes
  for (int i=0;i<3;++i) {
    accelerometer_data[i] = ((int)bytes[2*i] + (((int)bytes[2*i + 1]) << 8))*(.4); //(0.004) OR (0.0392)*(9.1836) instead??
  }
  pitch = accelerometer_data[0];
  roll = accelerometer_data[1];
  yaw = accelerometer_data[2];
}

void Accelerometer::init() {
  byte data = 0;

  device->i2c_write(ADXL345_ADDRESS, ADXL_REGISTER_PWRCTL, ADXL_PWRCTL_MEASURE);

  //Check to see if it worked!
  device->i2c_read(ADXL345_ADDRESS, ADXL_REGISTER_PWRCTL, 1, &data);
}

float Accelerometer::getRoll(){
  return roll;
}

float Accelerometer::getPitch(){
  return pitch;
}

float Accelerometer::getYaw(){
  return yaw;
}

