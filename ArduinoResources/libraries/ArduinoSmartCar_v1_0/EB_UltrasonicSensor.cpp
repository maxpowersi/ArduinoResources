/*************************************************** 
  This is a library for the EB-Ultrasonic Sensor

  The Ultrasonic Sensor uses Trig and Echo Digital pin.
  
  MakerStudio invests time and resources providing this open source code, 
  please support MakerStudio and open-source hardware by purchasing 
  products from MakerStudio!

  Written by Steve for MakerStudio.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#include "EB_UltrasonicSensor.h" 

EB_UltrasonicSensor::EB_UltrasonicSensor(uint8_t trig, uint8_t echo)
{
	trigPin = trig;
	echoPin = echo;

}

void EB_UltrasonicSensor::begin()
{
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
}
  
//return distance in cm
long EB_UltrasonicSensor::distance()
{
	long distance = 0;
	long duration = 0;
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin,HIGH);
	distance = duration /29 / 2 ;
	return distance;
}
