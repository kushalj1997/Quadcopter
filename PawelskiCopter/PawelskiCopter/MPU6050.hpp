//
//  MPU6050.hpp
//  PawelskiCopter
//
//  Created by Kushal Jaligama on 1/31/16.
//  Copyright © 2016 Kushal Jaligama. All rights reserved.
//

#ifndef MPU6050_hpp
#define MPU6050_hpp

#define MPU6050ADDR 0x68

#include <stdio.h>
#include <math.h>
#include "I2C.hpp"

double ax, ay, az = 0;
double gx, gy, gz = 0;
double z_gx, z_gy, z_gz = 0;
double temp = 0;
double lastgx = 0.0, lastgy = 0.0, lastgz = 0.0;

void MPU6050Init();
void MPU6050Read();
void MPU6050GyroX();
void MPU6050GyroY();
void MPU6050GyroZ();
void MPU6050AccelX();
void MPU6050AccelY();
void MPU6050AccelZ();

#endif /* MPU6050_hpp */
