//
//  I2C.hpp
//  PawelskiCopter
//
//  Created by Kushal Jaligama on 1/28/16.
//  Copyright © 2016 Kushal Jaligama. All rights reserved.
//

#ifndef I2C_hpp
#define I2C_hpp

#include <stdio.h>

void TWIInit();
void TWIStart();
void TWIStop();
void TWIWrite();
void TWIReadACK();
void TWIReadNACK();
void TWIGetStatus();


#endif /* I2C_hpp */
