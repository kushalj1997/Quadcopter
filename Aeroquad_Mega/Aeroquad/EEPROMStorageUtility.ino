// EEPROM Storage Utility

float readFloat(int address) {
  float out;
  eeprom_read_block((void *) &out, (unsigned char *) address , 4 );
  return out;
}

void writeFloat(float value, int address) {
  eeprom_write_block((void *) &value, (unsigned char *) address , 4);
}
