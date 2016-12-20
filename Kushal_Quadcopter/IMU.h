//
//  IMU.h
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/6/15.
//
//

#ifndef __Kushal_Quadcopter__IMU__
#define __Kushal_Quadcopter__IMU__

#include <stdio.h>
#include <Arduino.h>
#include <Kalman.h>

#include "ITG3200.h"
#include "BMA180.h"

#define GYROMODE 0
#define ATTITUDEMODE 1

class IMU {
  public:
    IMU();
    static float getRoll();
    static float getPitch();
    static float getYaw();
    static float getDownGForce();
    static void read(bool mode);
    static void init();
    static void printGyroData();
    static void printAccelData();
    static void printData();
  private:
    static float gyroRoll, gyroPitch, gyroYaw;
    static float accelRoll, accelPitch, accelDownGForce;
    static float roll, pitch, yaw;
    static float complementaryFilter(float rate, float angle);
    static bool _mode;
    static Kalman *rollKalman;
    static Kalman *pitchKalman;
};

#endif /* defined(__Kushal_Quadcopter__IMU__) */
