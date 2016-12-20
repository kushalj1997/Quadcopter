#define channumber 6 //How many channels have your radio?
int value[channumber];

void setup()
{
  Serial.begin(115200); //Serial Begin
  pinMode(48, INPUT); //Pin 48 as input
}

void loop()
{
  while (pulseIn(48, HIGH) < 2700) {} //Wait for the beginning of the frame
  for (int x = 0; x <= channumber - 1; x++) //Loop to store all the channel position
  {
    value[x] = pulseIn(48, HIGH) + 400;
  }
  for (int x = 0; x <= channumber - 1; x++) //Loop to print and clear all the channel readings
  {
    Serial.print(value[x]); //Print the value
    Serial.print(" ");
    value[x] = 0; //Clear the value afeter is printed
  }
  Serial.println(""); //Start a new line
}
