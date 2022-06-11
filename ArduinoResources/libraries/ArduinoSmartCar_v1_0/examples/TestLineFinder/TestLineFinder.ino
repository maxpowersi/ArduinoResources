/*
  Demo code for testing Line Finder
  
  by Maker Studio
*/
#include "EB_LineFinder.h"
#include <SoftwareSerial.h>

//Connect Line Finder Sensor1 D14(A0), Sensor2 to D15(A1)
EB_LineFinder myLineFinder(14,15);

void setup()
{
	myLineFinder.begin();
	Serial.begin(9600);
}

void loop()
{
	Serial.print("Sensor1:");
	Serial.println(myLineFinder.sensor1());
	Serial.print("Sensor2:");
	Serial.println(myLineFinder.sensor2());
	Serial.println();
	
	delay(1000);
}