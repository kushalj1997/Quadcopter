// PA3 BLUE
// PA4 YELLOW
// PA5 RED

void setup() {
  // put your setup code here, to run once:
  DDRA |= B00111000;
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  PORTA |= B00111000;
  delay(500);
  PORTA &= B00000000;
  delay(500);
}
