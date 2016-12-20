//
//  EEPROMStorageUtil.h
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 5/6/15.
//
//

#ifndef Kushal_Quadcopter_EEPROMStorageUtil_h
#define Kushal_Quadcopter_EEPROMStorageUtil_h

float readFloat(int address) {
    float out;
    eeprom_read_block((void *) &out, (unsigned char *) address , 4 );
    return out;
}

void writeFloat(float value, int address) {
    eeprom_write_block((void *) &value, (unsigned char *) address , 4);
}

#endif