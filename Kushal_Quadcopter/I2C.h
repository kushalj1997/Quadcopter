//
//  I2C.h
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/6/15.
//
//

#ifndef __Kushal_Quadcopter__I2C__
#define __Kushal_Quadcopter__I2C__

#include <stdio.h>
#include <Wire.h>
#include <Arduino.h>

class I2C {
  public:
    I2C();
    static void writeTo(int DEVICE, byte address, byte val);
    static void readFrom(int DEVICE, byte address , int num , byte *buff);
};

#endif /* defined(__Kushal_Quadcopter__I2C__) */
