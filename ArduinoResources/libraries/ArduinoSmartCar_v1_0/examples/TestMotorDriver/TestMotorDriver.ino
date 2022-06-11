/*
  Demo code for testing Motor Driver
  
  by Maker Studio
*/
#include "EB_MotorDriver.h"
#include "SoftwareSerial.h"

//M1_EN,M1_IN2,M1_IN1, M2_EN,M2_IN2,M2_IN1
EB_MotorDriver myMotorDriver(5,12,13, 6,7,8);

int speed = 250;

void setup()
{
	myMotorDriver.begin();
}

void loop()
{
	myMotorDriver.run(speed,speed);
	delay(2000);
	myMotorDriver.run(-speed,-speed);
	delay(2000);
	myMotorDriver.run(speed,-speed);
	delay(2000);
	myMotorDriver.run(-speed,speed);
	delay(2000);
	myMotorDriver.stop();
	delay(2000);
}