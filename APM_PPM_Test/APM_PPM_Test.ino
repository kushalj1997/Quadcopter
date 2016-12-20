#include <PinChangeInt.h>

#define SYNC 2700

unsigned long timer = 0;
unsigned int ppmArray[6] = {1500, 1500, 1500, 1500, 1500, 1500};

void setup() {
  // put your setup code here, to run once:
  TCNT5 = 0;
  TIFR5 = 0;

  /* Set timer 8x prescaler fast PWM mode toggle compare at OCRA with rising edge input capture */
  TCCR5A = _BV(WGM50) | _BV(WGM51);
  TCCR5B |= _BV(WGM53) | _BV(WGM52) | _BV(CS51) | _BV(ICES5);
  OCR5A  = 40000 - 1; // -1 to correct for wrap

  /* OCR5B and OCR5C will be used by RCOutput_APM2. Init to 0xFFFF to prevent premature PWM output */
  OCR5B  = 0xFFFF;
  OCR5C  = 0xFFFF;

  /* Enable input capture interrupt */
  TIMSK5 |= _BV(ICIE5);
  PCintPort::attachInterrupt(48, getPPM, HIGH);
  Serial.begin(115200);
  DDRA |= 00111000;
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(ppmArray[0]);
  Serial.println("loop");

}

int counter = 0;
bool newFrame;
void getPPM()
{
  unsigned long signal = micros() - timer;
  if (signal >= SYNC) {
    newFrame = true;
    counter = 0;
  } else {
    ppmArray[counter] = signal;
    counter++;
  }

}
