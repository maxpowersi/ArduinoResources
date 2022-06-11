/*************************************************** 
  This is a library for the EB-LineFinder

  The EB-LineFinder integrates two line sensors.
  
  MakerStudio invests time and resources providing this open source code, 
  please support MakerStudio and open-source hardware by purchasing 
  products from MakerStudio!

  Written by Steve for MakerStudio.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
 #include "EB_LineFinder.h"
 
 EB_LineFinder::EB_LineFinder(uint8_t sensor_1, uint8_t sensor_2)
 {
	sensor1Pin = sensor_1;
	sensor2Pin = sensor_2;
 }
 void EB_LineFinder::begin()
 {
	pinMode(sensor1Pin, INPUT);
	pinMode(sensor2Pin, INPUT);
 }
  
 int EB_LineFinder::sensor1()
 {
	return digitalRead(sensor1Pin);
 }
 
 int EB_LineFinder::sensor2()
 {
	return digitalRead(sensor2Pin);
 }
 