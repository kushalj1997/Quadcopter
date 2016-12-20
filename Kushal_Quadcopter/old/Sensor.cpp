//
//  Sensor.cpp
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 4/5/15.
//
//

#include "Sensor.h"

Sensor::Sensor(){

}

void Sensor::i2c_write(char address, char registerAddress, char data) {
    //Initiate a communication sequence with the desired i2c device
    Wire.beginTransmission(address);
    //Tell the I2C address which register we are writing to
    Wire.write(registerAddress);
    //Send the value to write to the specified register
    Wire.write(data);
    //End the communication sequence
    Wire.endTransmission();
}

unsigned char Sensor::i2c_read(char address, char registerAddress) {
    //This variable will hold the contents read from the i2c device.
    unsigned char data=0;
    
    //Send the register address to be read.
    Wire.beginTransmission(address);
    //Send the Register Address
    Wire.write(registerAddress);
    //End the communication sequence.
    Wire.endTransmission();
    
    //Ask the I2C device for data
    Wire.beginTransmission(address);
    Wire.requestFrom(address, 1);
    
    //Wait for a response from the I2C device
    if(Wire.available()){
        //Save the data sent from the I2C device
        data = Wire.read();
    }
    
    //End the communication sequence.
    Wire.endTransmission();
    
    //Return the data read during the operation
    return data;
}