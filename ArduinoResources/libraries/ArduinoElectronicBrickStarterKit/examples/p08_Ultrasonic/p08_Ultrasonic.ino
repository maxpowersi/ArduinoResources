/*
  Arduino Electronic Brick Starter Kit example
  Project 08 - Ultrasonic
  
  Meseaure the distance by HC-SR04 Ultrasonic Ranging Module

  http://makerstudio.cc/
*/

#include "Ultrasonic.h"

Ultrasonic ultrasonic(11,10);//(Trig,Echo)

void setup() {
	Serial.begin(9600);
}

void loop()
{
	//output the distance in cm
	Serial.println(ultrasonic.Ranging(CM)); 
	delay(100);
}
