#include <Servo.h>

Servo motors[4];
unsigned int motorThrust[4];

void setSpeed(int motor, int speed)
{
  int fakeAngle = map(speed, 0, 100, 0, 180);
  motors[motor].write(fakeAngle);
}

void setup() {
  pinMode(13, OUTPUT);
  motors[0].attach(3, 1000, 2000);
  motors[1].attach(9, 1000, 2000);
  motors[2].attach(10, 1000, 2000);
  motors[3].attach(11, 1000, 2000);

  for (int i = 0; i < 4; i++) {
    setSpeed(i, 0);
  }

  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
}

void loop() {
  for (int i = 0; i < 4; i++) {
      setSpeed(i, 11);
    }
}

/*

for (int s = 0; s < 75; s++) {
    for (int i = 0; i < 4; i++) {
      setSpeed(i, s);
      delay(10);
    }
  }
  for (int s = 74; s > 0; s--) {
    for (int i = 0; i < 4; i++) {
      setSpeed(i, s);
      delay(10);
    }
  }
  
  */
