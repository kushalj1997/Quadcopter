//
//  ITG3200.h
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/6/15.
//
//

#ifndef __Kushal_Quadcopter__ITG3200__
#define __Kushal_Quadcopter__ITG3200__

#include <stdio.h>
#include "I2C.H"

#define ITG 0x69  //address of the gyroscope
#define RESET 0x3E
#define FILTER 0x16
#define INTOSC 0x01
#define DATA 0x1D
#define LSBTODEGS 14.375

class ITG3200 {
  public:
    ITG3200();
    static void init();
    static void read();
    static float getPitch();
    static float getRoll();
    static float getYaw();
  private:
    static int gyrox, gyroy, gyroz;
};

#endif /* defined(__Kushal_Quadcopter__ITG3200__) */
