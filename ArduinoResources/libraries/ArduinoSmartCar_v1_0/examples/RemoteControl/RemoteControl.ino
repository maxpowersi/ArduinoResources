/*
  Remote Control the Toy Car through Bluetooth 2.0
  
  by Maker Studio
*/

#include "EB_Bluetooth.h"
#include "EB_MotorDriver.h"
#include "SmartCar.h"
#include <SoftwareSerial.h>

SmartCar mySmartCar;

void setup()
{
	Serial.begin(9600);
	mySmartCar.begin();
}

void loop()
{
	mySmartCar.readCommand();
	mySmartCar.processCommand();
}


