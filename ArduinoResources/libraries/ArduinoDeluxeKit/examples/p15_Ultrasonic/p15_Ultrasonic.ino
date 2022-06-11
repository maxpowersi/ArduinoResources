/*
  Demo code for Project 15 - Ultrasonic
  
  Meseaure the distance by HC-SR04 Ultrasonic Ranging Module

  by Maker Studio
  http://makerstudio.cc
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




