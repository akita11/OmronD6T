#include "Arduino.h"

#ifndef D6T_h
#define D6T_h

class D6T
{
 private:
  void beginRead(uint8_t i2c_addr);
  uint8_t get_byte();
  
 public:
  D6T();
  virtual ~D6T();
  float read_temp(uint8 x, uint8_t y); // [degC]
  float *read_temp(float *pix); // [degC]
};

#endif
