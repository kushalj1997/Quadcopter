#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "System.hpp"
#include "Controls.hpp"
#include "I2C.hpp"
#include "IMU.hpp"
#include "PID.hpp"

float PGAIN = 1;
float IGAIN = 0.01;
float DGAIN = 0.1;

float YPGAIN = 1;
float YIGAIN = 0.01;
float YDGAIN = 0.1;

PID rollPID(PGAIN, IGAIN, DGAIN);
PID pitchPID(PGAIN, IGAIN, DGAIN);
PID yawPID(YPGAIN, YIGAIN, YDGAIN);

Controls controls;
IMU imu;
float throttle, rollCommand, pitchCommand, yawCommand;

void initIO(void) {
    TWIInit();
}

int main(void) {
    
	initIO();

	while (1) {
        controls.read();
        imu.read();
        rollCommand = rollPID.compute(controls.getRoll(), imu.getRoll());
        pitchCommand = pitchPID.compute(controls.getPitch(), imu.getPitch());
        yawCommand = yawPID.compute(controls.getYaw(), imu.getYaw());
        
        writeMotors(controls.getThrottle(), rollCommand,
                    pitchCommand, yawCommand);
        
	}
	return 0; // never reached
}
