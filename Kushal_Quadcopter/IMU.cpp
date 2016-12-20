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
float IMU::roll = 0;
float IMU::pitch = 0;
float IMU::yaw = 0;
bool IMU::_mode = GYROMODE;
Kalman *IMU::rollKalman;
Kalman *IMU::pitchKalman;
unsigned long timer = 0;

IMU::IMU() {
}

void IMU::init() {
    ITG3200::init();
    BMA180::init();
    rollKalman = new Kalman();
    pitchKalman = new Kalman();
    rollKalman->setAngle(accelRoll);
    pitchKalman->setAngle(accelPitch);
}

void IMU::read(bool mode) {
    _mode = mode;
    
    double dt = (double)(micros() - timer) / 1000000; // Calculate delta time
    timer = micros();
    
    ITG3200::read();
    gyroRoll = ITG3200::getRoll();
    gyroPitch = ITG3200::getPitch();
    gyroYaw = ITG3200::getYaw();
    
    BMA180::read();
    accelRoll = BMA180::getRoll();
    accelPitch = BMA180::getPitch();
    accelDownGForce = BMA180::getDownGForce();
    
    
    pitch += gyroPitch * dt;
    roll += gyroRoll * dt;
    yaw += gyroYaw * dt;
}

float IMU::getRoll() {
    return (_mode == ATTITUDEMODE) ? complementaryFilter(roll, accelRoll) : gyroRoll;
}

float IMU::getPitch() {
    return (_mode == ATTITUDEMODE) ? complementaryFilter(pitch, accelPitch) : gyroPitch;
}

float IMU::getYaw() {
    return gyroYaw;
}

float IMU::getDownGForce() {
    return accelDownGForce;
}

float IMU::complementaryFilter(float rate, float angle) {
    return (0.95 * rate + 0.05 * angle);
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

void IMU::printData() {
    Serial.print("IMU Roll: ");
    Serial.print(getRoll());
    Serial.print(" IMU Pitch: ");
    Serial.print(getPitch());
    Serial.print(" IMU Yaw: ");
    Serial.print(getYaw());
    Serial.print(" Down G's: ");
    Serial.println(accelDownGForce);
}
