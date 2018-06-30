#include <Arduino.h>
#include <Wire.h>
#include <D6T.h>

// based on WireExt library

#define I2C_ADDR_D6T 0x0a
#define CMD 0x4c

D6T::D6T()
{
  Wire.begin();
}

D6T::~D6T()
{
}

/*
void D6T::beginRead(uint8_t i2c_addr)
{
  // implementation for ATmega328-based Arduinos
  // ref: WireExt, https://fenrir.naruoka.org/archives/000773.html  

  // send START
  TWCR = _BV(TWEN) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTA);
  while(!(TWCR & _BV(TWINT)));

  switch(TW_STATUS){
    case TW_START:     // in case of START sent
    case TW_REP_START: // in case of RepSTART sent
      TWDR = TW_READ | (address << 1); // request read
      TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);
      break;
    case TW_BUS_ERROR: // bus error, illegal stop/start
    default:
      twi_stop();
      return -1;
  }
  while(!(TWCR & _BV(TWINT)));

  switch(TW_STATUS){
    case TW_MR_SLA_ACK: // SLA+R transmitted, ACK received
      break;
    case TW_MR_ARB_LOST: // arbitration lost in SLA+R or NACK 
      twi_releaseBus();
      return -1;
    case TW_MR_SLA_NACK: // SLA+R transmitted, NACK received
    case TW_BUS_ERROR: // bus error, illegal stop/start
    default:
      twi_stop();
      return -1;
  }
}

void D6T::get_byte()
{
  // clear flag and prepare for sending ack
  TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);
  while(!(TWCR & _BV(TWINT)));

  switch(TW_STATUS){
    case TW_MR_DATA_ACK: // data received, ACK returned
      break;
    default:
      return 0;
  }
  return(TWDR);
}
*/

float D6T::read_temp(uint8 x, uint8_t y)
{
  uint8_t buf[35];
  Wire.beginTransmission(I2C_ADDR_D6T);
  Wire.write(CMD);
  Wire.endTransmission();

  //  beginRead(I2C_ADDR_D6T);
  Wire.requestFrom(i2c_addr, 35);
  int i;
  //  for (i = 0; i < 35; i++) buf[i] = get_byte();
  for (i = 0; i < 35; i++) buf[i] = Wire.read();
  Wire.endTransmission();

  float temp;
  i = x + (y * 4)
  temp = (buf[(i*2+2)] + (buf[(i*2+3)]<<8)) * 0.1;
  return(temp);
}


float *D6T::read_temp(float *pix)
{
  uint8_t buf[35];
  //  float t_PTAT;
  
  Wire.beginTransmission(I2C_ADDR_D6T);
  Wire.write(CMD);
  Wire.endTransmission();

  beginRead(I2C_ADDR_D6T);
  int i;
  for (i = 0; i < 35; i++) buf[i] = get_byte();
  Wire.endTransmission();

  //  t_PTAT = (rbuf[0]+(rbuf[1]<<8))*0.1;
  for (i = 0; i < 16; i++)
    pix[i] = (buf[(i*2+2)] + (buf[(i*2+3)]<<8)) * 0.1;

  return(pix);
}
