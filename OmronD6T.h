#ifndef OmronD6T_h
#define OmronD6T_h
#include <Wire.h>
#include <Arduino.h>

class OmronD6T
{
 private:
  
 public:
  OmronD6T();
  float temp[4][4]; //[degC]
  void scanTemp();
};

#endif

