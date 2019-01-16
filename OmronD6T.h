// Arduion Library for Omron D6T
// 2019/1/16: akita11 (akita@ifdl.jp)

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

