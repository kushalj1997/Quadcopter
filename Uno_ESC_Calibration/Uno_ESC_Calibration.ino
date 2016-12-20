#include <Servo.h>

// #define AeroquadUnov1.8
// #define AeroquadMegav2.1
// #define APMMicro

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

#ifndef M1

#error

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

  motor1.writeMicroseconds(2000);
  motor2.writeMicroseconds(2000);
  motor3.writeMicroseconds(2000);
  motor4.writeMicroseconds(2000);

  digitalWrite(13, HIGH);
  delay(3000);
  digitalWrite(13, LOW);

  motor1.writeMicroseconds(1000);
  motor2.writeMicroseconds(1000);
  motor3.writeMicroseconds(1000);
  motor4.writeMicroseconds(1000);

  delay(3000);

}

void loop() {
  // put your main code here, to run repeatedly:
  motor1.writeMicroseconds(1100);
  motor2.writeMicroseconds(1100);
  motor3.writeMicroseconds(1100);
  motor4.writeMicroseconds(1100);


}
