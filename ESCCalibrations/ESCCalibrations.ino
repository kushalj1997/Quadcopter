#include <Servo.h>

// #define AeroquadUnov1.8
#define AeroquadMegav2.1
// #define APMMicro

#define TOPTH 1950
#define BOTTH 1100
#define TESTTH 1200

#ifdef AeroquadMegav2.1

#define M1 2
#define M2 3
#define M3 5
#define M4 6

#endif

#ifdef AeroquadUnov1.8

#define M1 3
#define M2 9
#define M3 10
#define M4 11

#endif

#ifdef APMMicro

#define M1 12
#define M2 11
#define M3 8
#define M4 7

#endif

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);

  motor1.attach(M1);
  motor2.attach(M2);
  motor3.attach(M3);
  motor4.attach(M4);

  motor1.writeMicroseconds(TOPTH);
  motor2.writeMicroseconds(TOPTH);
  motor3.writeMicroseconds(TOPTH);
  motor4.writeMicroseconds(TOPTH);

  digitalWrite(13, HIGH);
  delay(3000);
  digitalWrite(13, LOW);

  motor1.writeMicroseconds(BOTTH);
  motor2.writeMicroseconds(BOTTH);
  motor3.writeMicroseconds(BOTTH);
  motor4.writeMicroseconds(BOTTH);

  delay(3000);

}

void loop() {
  // put your main code here, to run repeatedly:
  motor1.writeMicroseconds(TESTTH);
  delay(1000);
  motor1.writeMicroseconds(BOTTH);
  delay(100);
  motor2.writeMicroseconds(TESTTH);
  delay(1000);
  motor2.writeMicroseconds(BOTTH);
  delay(100);
  motor3.writeMicroseconds(TESTTH);
  delay(1000);
  motor3.writeMicroseconds(BOTTH);
  delay(100);
  motor4.writeMicroseconds(TESTTH);
  delay(1000);
  motor4.writeMicroseconds(BOTTH);
  delay(100);

  digitalWrite(13, HIGH);
  delay(2000);
  digitalWrite(13, LOW);
}

#ifndef M1

#error No Device Chosen

#endif

#ifdef AeroquadMegav2.1

#ifdef AeroquadUnov1.8
#error Too Many Devices
#endif

#ifdef APMMicro
#error Too Many Devices
#endif

#endif
//(#ifdef AeroquadMegav2.1 && #ifdef APMMicro) ||
//(#ifdef AeroquadUnov1.8 && #ifdef APMMicro)
