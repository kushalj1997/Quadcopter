//
//  Gyroscope.cpp
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/5/15.
//
//

#include "Gyroscope.h"

Gyroscope::Gyroscope(){
  device = new Sensor();
  roll = pitch = yaw = 0;
  for (int i=0;i<3;++i) {
    gyro_data[i] = 0;
  }
}

void Gyroscope::read() {
  byte bytes[6];
  memset(bytes,0,6);

  //read 6 bytes from the ITG3200
  device->i2c_read(ITG3200_ADDRESS, ITG3200_REGISTER_XMSB, 6, bytes);  //now unpack the bytes
  for (int i=0;i<3;++i) {
    gyro_data[i] = ((int)bytes[2*i + 1] + (((int)bytes[2*i]) << 8))/(14.375);
  }
  pitch = gyro_data[0];
  roll = gyro_data[1];
  yaw = gyro_data[2];
}

void Gyroscope::init() {
  byte data = 0;

  //Set DLPF to 42 Hz (change it if you want) and
  //set the scale to "Full Scale"
  device->i2c_write(ITG3200_ADDRESS, ITG3200_REGISTER_DLPF_FS, ITG3200_FULLSCALE | ITG3200_42HZ);

  //Sanity check! Make sure the register value is correct.
  device->i2c_read(ITG3200_ADDRESS, ITG3200_REGISTER_DLPF_FS, 1, &data);

}

float Gyroscope::getRoll(){
  return roll;
}

float Gyroscope::getPitch(){
  return pitch;
}

float Gyroscope::getYaw(){
  return yaw;
}

