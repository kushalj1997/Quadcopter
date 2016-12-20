//
//  IMU.cpp
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/6/15.
//
//

#include "IMU.h"

float IMU::gyroRoll = 0;
float IMU::gyroPitch = 0;
float IMU::gyroYaw = 0;
float IMU::accelRoll = 0;
float IMU::accelPitch = 0;
float IMU::accelDownGForce = 0;

IMU::IMU() {
}

void IMU::init() {
  ITG3200::init();
  BMA180::init();
}

void IMU::read() {
  ITG3200::read();
  gyroRoll = ITG3200::getRoll();
  gyroPitch = ITG3200::getPitch();
  gyroYaw = ITG3200::getYaw();

  BMA180::read();
  accelRoll = BMA180::getRoll();
  accelPitch = BMA180::getPitch();
  accelDownGForce = BMA180::getDownGForce();
}


// TODO!
float IMU::getRoll(bool mode) {
  return 0;
}

float IMU::getPitch(bool mode) {
  return 0;
}

float IMU::getYaw(bool mode) {
  return 0;
}

float IMU::getDownGForce() {
  return BMA180::getDownGForce();
}

float IMU::complementaryFilter() {
  return 0;
}

void IMU::printGyroData() {
  Serial.print("Gyro Roll: ");
  Serial.print(gyroRoll);
  Serial.print(" Pitch: ");
  Serial.print(gyroPitch);
  Serial.print(" Yaw: ");
  Serial.println(gyroYaw);
}

void IMU::printAccelData() {
  Serial.print("Accel Roll: ");
  Serial.print(accelRoll);
  Serial.print(" Pitch: ");
  Serial.print(accelPitch);
  Serial.print(" Down G's: ");
  Serial.println(accelDownGForce);
}
