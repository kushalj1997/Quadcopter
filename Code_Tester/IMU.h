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
#include "ITG3200.h"
#include "BMA180.h"

class IMU {
  public:
    IMU();
    static float getRoll(bool mode);
    static float getPitch(bool mode);
    static float getYaw(bool mode);
    static float getDownGForce();
    static void read();
    static void init();
    static void printGyroData();
    static void printAccelData();
  private:
    static float gyroRoll, gyroPitch, gyroYaw;
    static float accelRoll, accelPitch, accelDownGForce;
    static float complementaryFilter();
};

#endif /* defined(__Kushal_Quadcopter__IMU__) */
