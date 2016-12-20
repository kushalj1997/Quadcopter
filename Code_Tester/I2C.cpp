//
//  I2C.cpp
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/6/15.
//
//

#include "I2C.h"

I2C::I2C() {

}

//Writes val to address register
void I2C::writeTo(int DEVICE, byte address, byte val)
{
  Wire.beginTransmission(DEVICE);   //start transmission
  Wire.write(address);               //send register address
  Wire.write(val);                   //send value to write
  Wire.endTransmission();           //end transmisson
}
//reads num bytes starting from address register in to buff array
void I2C::readFrom(int DEVICE, byte address, int num, byte *buff)
{
  Wire.beginTransmission(DEVICE); //start transmission
  Wire.write(address);            //send reguster address
  Wire.endTransmission();        //end transmission

  Wire.beginTransmission(DEVICE); //start transmission
  Wire.requestFrom(DEVICE, num); //request 6 bits from

  int i = 0;
  while (Wire.available())       //Wait for data
  {
    buff[i] = Wire.read();        //receive a byte
    i++;
  }
  Wire.endTransmission();         //end transmission
}
