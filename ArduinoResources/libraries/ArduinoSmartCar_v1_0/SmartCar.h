/*************************************************** 
  This is a library for Control Car in different way
  
  MakerStudio invests time and resources providing this open source code, 
  please support MakerStudio and open-source hardware by purchasing 
  products from MakerStudio!

  Written by Steve for MakerStudio.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#ifndef _SMART_CAR_H
#define _SMART_CAR_H
#include "EB_Bluetooth.h"
#include "EB_MotorDriver.h"
#include "EB_UltrasonicSensor.h"
#include "EB_LineFinder.h"



class SmartCar {
public:

  SmartCar();
  void begin();
  void readCommand();
  void processCommand();
  void joysticMode(char direction, int speed);
  void lineFinderMode(int speed);
  void ultrasonicMode(int speed);
  
  
private:
  char modeDat;
  char directionDat;
  char speedDat;
  int speedPWM;
  
};

#endif
