#include "OmronD6T.h"

OmronD6T sensor;

void setup() {
  Serial.begin(9600);
}

void loop() {
  sensor.scanTemp();
  Serial.println("-------------------------");
  int x, y;
  for (y = 0; y < 4; y++){
    for (x = 0; x < 4; x++){
      Serial.print(sensor.temp[x][y]);
      Serial.print(' ');
    }
    Serial.println("");
  }
  delay(1000);
}

