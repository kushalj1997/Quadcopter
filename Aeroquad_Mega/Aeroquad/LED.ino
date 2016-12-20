// LED

#define GREEN0 13
#define GREEN1 4
#define RED 31

#define ON 1
#define OFF 0

void initLEDs() {
  pinMode(GREEN0, OUTPUT);
  pinMode(GREEN1, OUTPUT);
  pinMode(RED, OUTPUT);

  green0(ON);
  green1(ON);
  red(ON);
  delay(250);
  green0(OFF);
  green1(OFF);
  red(OFF);
  delay(250);
  green0(ON);
  green1(ON);
  red(ON);
  delay(250);
  green0(OFF);
  green1(OFF);
  red(OFF);

  Serial.println("LEDs initialized");
}

bool lastGreen0 = false;
int fadeValue = 5;
int increment = 10;

void processLEDs() {
  (armed) ? red(ON) : red(OFF);
  (autoLevel) ? green1(ON) : green1(OFF);
  green0Fader(fadeValue);
  fadeValue += increment;
  if (fadeValue >= 255 || fadeValue <= 10) {
    increment *= -1;
  }
}

void red(bool state) {
  (state) ? digitalWrite(RED, HIGH) : digitalWrite(RED, LOW);
}

void green0(bool state) {
  (state) ? digitalWrite(GREEN0, HIGH) : digitalWrite(GREEN0, LOW);
}

void green0Fader(int val) {
  analogWrite(GREEN0, val);
}

void green1(bool state) {
  (state) ? digitalWrite(GREEN1, HIGH) : digitalWrite(GREEN1, LOW);
}
