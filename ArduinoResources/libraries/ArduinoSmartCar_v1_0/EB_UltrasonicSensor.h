/*************************************************** 
  This is a library for the EB-Ultrasonic Sensor

  The Ultrasonic Sensor uses Trig and Echo Digital pin.
  
  MakerStudio invests time and resources providing this open source code, 
  please support MakerStudio and open-source hardware by purchasing 
  products from MakerStudio!

  Written by Steve for MakerStudio.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#ifndef _EB_ULTRASONIC_SENSOR_H
#define _EB_ULTRASONIC_SENSOR_H
#include <Arduino.h>

class EB_UltrasonicSensor {
public:

  EB_UltrasonicSensor(uint8_t trig, uint8_t echo);
  void begin();
  
  //return distance in cm
  long distance();
  
private:
  uint8_t trigPin;
  uint8_t echoPin;
  
};

#endif
