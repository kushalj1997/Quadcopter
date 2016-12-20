#include <PID_v1.h>

// Globals

#define PADD 0
#define IADD 4
#define DADD 8

#define YAWP 12
#define YAWI 16
#define YAWD 20

#define ALADDP 24
#define ALADDI 28
#define ALADDD 32

#define HEADINGP 36
#define HEADINGI 40
#define HEADINGD 44

#define ALTHOLDP 48
#define ALTHOLDI 52
#define ALTHOLDD 56

// [axis][gain]
byte gainArray[5][3] = {
  {PADD, IADD, DADD},
  {YAWP, YAWI, YAWD},
  {ALADDP, ALADDI, ALADDD},
  {HEADINGP, HEADINGI, HEADINGD},
  {ALTHOLDP, ALTHOLDI, ALTHOLDD}
};

bool armed = false;
bool autoLevel = false;
bool headingHold = false;
bool override = false;

float mapFloats(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Final Quadcopter Attitude

double quadRoll;
double quadPitch;
double quadYaw;
double quadAltitude;

// RX Data

int thrust;
double RXrollAngleSet;
double RXPitchAngleSet;
double RXYawAngleSet;
bool gearSwitch;
bool flapSwitch;

// PID Gains

double autoLevelP;
double autoLevelI;
double autoLevelD;

double headingP;
double headingI;
double headingD;

double accroP;
double accroI;
double accroD;

double yawP;
double yawI;
double yawD;

// PID Variables

double rollTheta;
double pitchTheta;
double yawTheta;

double rollOmega;
double pitchOmega;
double yawOmega;

// PID Variables

// PID var(processVariable, output, setpoint, Pgain, Igain, Dgain, direction);

PID rollAutoLevel(&quadRoll, &rollTheta, &RXrollAngleSet, autoLevelP, autoLevelI, autoLevelD, DIRECT);
PID rollPID(&quadRoll, &rollOmega, &rollTheta, accroP, accroI, accroD, DIRECT);

PID pitchAutoLevel(&quadPitch, &pitchTheta, &RXPitchAngleSet, autoLevelP, autoLevelI, autoLevelD, DIRECT);
PID pitchPID(&quadPitch, &pitchOmega, &pitchTheta, accroP, accroI, accroD, DIRECT);

PID headingHoldControl(&quadYaw, &yawTheta, &RXYawAngleSet, headingP, headingI, headingD, DIRECT);
PID yawPID(&quadYaw, &yawOmega, &yawTheta, yawP, yawI, yawD, DIRECT);

// Motor Outputs

#define TOPTH 2000
#define MIDTH 1500
#define BOTTH 1000
#define MINARM 1100

unsigned int motorCommand[4];

// Serial Stuff

bool printMotorData = false;
bool printReceiverData = false;
bool printPIDData = false;
bool printSensorData = false;
bool printCommandAngles = false;
