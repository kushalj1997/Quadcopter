//
//  BMA180.h
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/6/15.
//  Using code from www.geeetech.com, modified it for quadcopter application
//

#ifndef Kushal_Quadcopter_BMA180_h
#define Kushal_Quadcopter_BMA180_h

//BMA180 triple axis accelerometer sample code//
//www.geeetech.com//

#include <stdio.h>
#include "I2C.h"

#define BMA 0x40  //address of the accelerometer
#define RESET 0x10
#define PWR 0x0D
#define BW 0X20
#define RANGE 0X35
#define DATA 0x02
#define LSBTOGS 4096.0

#define OFFX 31
#define OFFY 47
#define OFFZ -23

class BMA180 {
  public:
    BMA180();
    static void init();
    static void read();
    static float getPitch();
    static float getRoll();
    static float getDownGForce();
  private:
    static int accelx, accely, accelz;
};

#endif
