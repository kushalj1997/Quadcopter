void setup() {
  // put your setup code here, to run once:

  DDRB |= B01100000;
  DDRH |= B00110000;
  /*
    pinMode(12, OUTPUT); //OUT1 (PB6/OC1B)
    pinMode(11, OUTPUT); //OUT2 (PB5/OC1A)
    pinMode(8, OUTPUT);  //OUT3 (PH5/OC4C)
    pinMode(7, OUTPUT);  //OUT4 (PH4/OC4B)
  */

  //Remember the registers not declared here remains zero by default...
  TCCR1A = (1 << WGM11) | (1 << COM1A1) | (1 << COM1B1) | (1 << COM1C1);
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
  ICR1 = 5000;

  OCR1B = 0xFFFF;
  OCR1A = 0xFFFF;

  TCCR4A = (1 << WGM41) | (1 << COM4A1) | (1 << COM4B1) | (1 << COM4C1);
  TCCR4B = (1 << WGM43) | (1 << WGM42) | (1 << CS41);
  ICR4 = 5000;

  OCR4C = 0xFFFF;
  OCR4B = 0xFFFF;

  // Datasheets have all this info. (ATMEGA2560)
  // n refers to which Timer/Counter we are talking about
  // Sets the Prescaler to 8, 0.5 microsecond resolution per tick (1 << CSn1)
  // Sets PWM to Fast PWM (1 << WGMn1, 1 << WGMn2, 1 << WGMn3)
  // Sets the Compare Output Mode to Clear OCnA/OCnB/OCnC on comapre match
  // Set OCnA/B/C at BOTTOM (non-inverting)
  // (1 << COMnA1, 1 << COMnB1, 1 << COMnC1)
  // Sets the TOP Value at 5000 ticks (ICRn = 5000)
  // With a resolution of 0.5us, a complete PWM cycle takes 5000ticks * 0.5us = 0.0025 seconds per cycle
  // This gives us a PWM frequency of 400Hz (yay!)
  // ESC's cant handle 500 Hz apparently lol

  commandAllMotors(1900);
  delay(3000);
  commandAllMotors(1000);
  delay(5000);

}

void loop() {
  // put your main code here, to run repeatedly:
  OCR1B = 2200;
  delay(3000);
  OCR1B = 2000;
  delay(500);
  OCR1A = 2200;
  delay(3000);
  OCR1A = 2000;
  delay(500);
  OCR4C = 2200;
  delay(3000);
  OCR4C = 2000;
  delay(500);
  OCR4B = 2200;
  delay(3000);
  OCR4B = 2000;
  delay(5000);
  /*
    for (int i = 1000; i <= 2000; i += 50) {
    commandAllMotors(i);
    delay(100);
    }
    delay(1000);
    for (int i = 2000; i >= 1000; i -= 50) {
    commandAllMotors(i);
    delay(100);
    }
    delay(1000);
  */
}

void commandAllMotors(uint16_t speed) {
  OCR1B = speed * 2;
  OCR1A = speed * 2;
  OCR4C = speed * 2;
  OCR4B = speed * 2;
}

