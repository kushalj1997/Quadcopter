//
//  Variables.h
//  Kushal Quadcopter
//
//  Created by Kushal Jaligama on 5/6/15.
//
//

#ifndef Kushal_Quadcopter_Variables_h
#define Kushal_Quadcopter_Variables_h

#define MINCOMMAND 1100
#define MIDCOMMAND 1470
#define MAXCOMMAND 1800

#define TXMIN 1076
#define TXMAX 1876

#define MAXANGLE 45

#define GYROMODE 0
#define ATTITUDEMODE 1

#define PADD 0
#define IADD 4
#define DADD 8

boolean armed;
byte flightMode;
byte lastFlightMode;

Motor *frontLeft;
Motor *frontRight;
Motor *rearRight;
Motor *rearLeft;

unsigned int rxCmd[6] = {0, 0, 0, 0, 0, 0};

float frontLeftCmd, frontRightCmd, rearRightCmd, rearLeftCmd;

PID *rollPID;
PID *pitchPID;
PID *yawPID;

float pgain, igain, dgain;

double IMUpitch, IMUroll, IMUyaw = 0;
double pitchOutput, rollOutput, yawOutput = 0;
double pitchTarget, rollTarget, yawTarget = 0;

LED greenLED(13);
LED redLED(12);

unsigned long currentTime = 0;
unsigned long previousTime = 0;
unsigned long deltaTime = 0;
unsigned long frameCounter = 0;

#endif
