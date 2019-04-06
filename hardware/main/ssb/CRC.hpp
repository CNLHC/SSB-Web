#include "CRCTable.h"

unsigned char CRC8(unsigned char *p, char counter) ;

unsigned char CRC8(unsigned char *p, char counter) {
  unsigned char crc8 = 0;
  for (; counter > 0; counter--)
  {
    crc8 = crc_array[crc8 ^ *p]; //Generate CRC Code from Table
    p++;
  }
  return crc8;
}