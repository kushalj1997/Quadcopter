//Kushal Jaligama
//I have modified this from http://playground.arduino.cc/Main/BarebonesPIDForEspresso#pid

// Simple extension to the EEPROM library
// Tim Hirzel
// All code released under
// Creative Commons Attribution-Noncommercial-Share Alike 3.0 

float readFloat(int address) {
  float out;
  eeprom_read_block((void *) &out, (unsigned char *) address ,4 );
  return out;
}

void writeFloat(float value, int address) {
  eeprom_write_block((void *) &value, (unsigned char *) address ,4);
}

// END EEPROM Float