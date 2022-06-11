/*************************************************** 
  This is a library for the EB-LineFinder

  The EB-LineFinder integrates two line sensors.
  
  MakerStudio invests time and resources providing this open source code, 
  please support MakerStudio and open-source hardware by purchasing 
  products from MakerStudio!

  Written by Steve for MakerStudio.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#ifndef _EB_LINE_FINDER_H
#define _EB_LINE_FINDER_H

#include <Arduino.h>

class EB_LineFinder{
public:

  EB_LineFinder(uint8_t sensor_1, uint8_t sensor_2);
  void begin();
  
  int sensor1();
  int sensor2();
  
private:
  uint8_t sensor1Pin;
  uint8_t sensor2Pin;
  
};

#endif
