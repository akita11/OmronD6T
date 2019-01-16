// Arduion Library for Omron D6T
// 2019/1/16: akita11 (akita@ifdl.jp)
// ATmega-based Arduino & ESP32-based Arduino
// Note: D6T's I2C clock maximum freq. = 100kHz

#include "OmronD6T.h"
#include "Wire.h"

#ifdef ARDUINO_ARCH_AVR
// use WireExt library for ATmega
#include <WireExt.h>
#endif
/*
extern "C" {
  #include <stdlib.h>
  #include <string.h>
  #include <inttypes.h>
  #include "utility/twi.h"
}
#endif
*/

#define I2C_ADDR_D6T 0x0a
#define CMD 0x4c

OmronD6T::OmronD6T()
{
  Wire.begin();
}

void OmronD6T::scanTemp() {
  uint8_t buf[35];
  int value;

  Wire.beginTransmission(I2C_ADDR_D6T);
  Wire.write(CMD);
  Wire.endTransmission();

  int i = 0;
#ifdef ARDUINO_ARCH_AVR
  if (WireExt.beginReception(I2C_ADDR_D6T) >= 0) {
    for (i = 0; i < 35; i++) buf[i] = WireExt.get_byte();
    WireExt.endReception();
  }
#else
  Wire.requestFrom(I2C_ADDR_D6T, 35);
  while (Wire.available() && i < 35){
    buf[i++] = Wire.read();
  }
  Wire.endTransmission();
#endif
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      i = x + (y * 4);
      value = buf[(i * 2 + 2)] + (buf[(i * 2 + 3)] << 8);
      temp[y][x] = value * 0.1;
    }
  }
}

