//
//  Controls.hpp
//  PawelskiCopter
//
//  Created by Kushal Jaligama on 1/28/16.
//  Copyright © 2016 Kushal Jaligama. All rights reserved.
//

#ifndef Controls_hpp
#define Controls_hpp

#include <stdio.h>

class Controls {
public:
    Controls();
    float getThrottle();
    float getRoll();
    float getPitch();
    float getYaw();
    void read();
private:
    
};

#endif /* Controls_hpp */
