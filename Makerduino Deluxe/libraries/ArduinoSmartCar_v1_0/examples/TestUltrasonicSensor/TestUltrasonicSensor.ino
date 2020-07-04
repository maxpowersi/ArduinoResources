/*
  Demo code for Ultrasonic Sensor
  
  by Maker Studio
*/
#include "EB_UltrasonicSensor.h"
#include <SoftwareSerial.h>

//Connect the Ultrasonic Sensor Trig to A2(D16, Echo to A3(D17)
EB_UltrasonicSensor myUltrasonicSensor(16,17);

void setup()
{
	myUltrasonicSensor.begin();
	Serial.begin(9600);
}

void loop()
{
	int distance = myUltrasonicSensor.distance();
	Serial.print("Distance cm:");
	Serial.println(distance);
	delay(1000);
}
