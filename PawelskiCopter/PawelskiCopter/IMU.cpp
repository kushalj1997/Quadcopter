//
//  IMU.cpp
//  PawelskiCopter
//
//  Created by Kushal Jaligama on 1/22/16.
//  Copyright © 2016 Kushal Jaligama. All rights reserved.
//

#include "IMU.hpp"

IMU::IMU() {
    MPU6050Init();
}

float IMU::getPitch() {
    this->pitch = compFilter(MPU6050GyroX(), MPU6050AccelX(), this->pitch);
    return this->pitch;
}

float IMU::getRoll() {
    this->roll compFilter(MPU6050GyroY(), MPU6050AccelY(), this->roll);
    return this->roll;
}

float IMU::getYaw() {
    this->yaw = MPU6050GyroZ();
    return this->yaw;
}

void IMU::setMode(int flightMode) {
    this->flightMode = flightMode;
}

void IMU::read() {
    MPU6050Read();
}

double IMU::compFilter(double rate, double angle, double oldAngle) {
    return 0.98 * (oldAngle + rate * systemTimer()) + 0.02 * angle;
}