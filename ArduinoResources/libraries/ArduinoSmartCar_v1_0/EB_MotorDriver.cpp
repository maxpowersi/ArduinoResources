/*************************************************** 
  This is a library for the EB-Motor Driver

  The control signal and the motor use individual power supply.
  
  MakerStudio invests time and resources providing this open source code, 
  please support MakerStudio and open-source hardware by purchasing 
  products from MakerStudio!

  Written by Steve for MakerStudio.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#include"EB_MotorDriver.h"
 
EB_MotorDriver::EB_MotorDriver(uint8_t M1_EN, uint8_t M1_IN2, uint8_t M1_IN1, uint8_t M2_EN, uint8_t M2_IN2, uint8_t M2_IN1)
{
	M1_EN_pin = M1_EN;
	M1_IN1_pin = M1_IN1;
	M1_IN2_pin = M1_IN2;
  
	M2_EN_pin = M2_EN;
	M2_IN1_pin = M2_IN1;
	M2_IN2_pin = M2_IN2;
}

void EB_MotorDriver::begin()
{
	pinMode(M1_EN_pin, OUTPUT);
	pinMode(M1_IN1_pin, OUTPUT);
	pinMode(M1_IN2_pin, OUTPUT);
	pinMode(M2_EN_pin, OUTPUT);
	pinMode(M2_IN1_pin, OUTPUT);
	pinMode(M2_IN2_pin, OUTPUT);
	
	digitalWrite(M1_EN_pin, LOW);
	digitalWrite(M1_IN1_pin, LOW);
	digitalWrite(M1_IN2_pin, LOW);
	digitalWrite(M2_EN_pin, LOW);
	digitalWrite(M2_IN1_pin, LOW);
	digitalWrite(M2_IN2_pin, LOW);	
}

// the M1_Speed_PWM and M2_Speed_PWM should be between -255 and 255
void EB_MotorDriver::run(int M1_Speed_PWM, int M2_Speed_PWM)
{
	//int adjustSpeed = map(M2_Speed_PWM, 0, 255, 0, 250);
	setM1Speed(M1_Speed_PWM);
	//setM2Speed(adjustSpeed);
	setM2Speed(M2_Speed_PWM);
}

// the Speed_PWM should be between -255 and 255  
void EB_MotorDriver::setM1Speed(int Speed_PWM)
{
	int m1Speed = 0;
	if(Speed_PWM >= 0 && Speed_PWM <= 255){
		digitalWrite(M1_IN1_pin,HIGH);
		digitalWrite(M1_IN2_pin,LOW);
		m1Speed = Speed_PWM;
	}else if(Speed_PWM < 0 && Speed_PWM >= -255){
		digitalWrite(M1_IN1_pin,LOW);
		digitalWrite(M1_IN2_pin,HIGH);
		m1Speed = -Speed_PWM;
	}else{
		digitalWrite(M1_IN1_pin,LOW);
		digitalWrite(M1_IN2_pin,LOW);
	}
	analogWrite(M1_EN_pin,m1Speed);
}

// the Speed_PWM should be between -255 and 255  
void EB_MotorDriver::setM2Speed(int Speed_PWM)
{
	int m2Speed = 0;
	if(Speed_PWM >= 0 && Speed_PWM <= 255){
		digitalWrite(M2_IN1_pin,HIGH);
		digitalWrite(M2_IN2_pin,LOW);
		m2Speed = Speed_PWM;
	}else if(Speed_PWM < 0 && Speed_PWM >= -255){
		digitalWrite(M2_IN1_pin,LOW);
		digitalWrite(M2_IN2_pin,HIGH);
		m2Speed = -Speed_PWM;
	}else{
		digitalWrite(M2_IN1_pin,LOW);
		digitalWrite(M2_IN2_pin,LOW);
	}
	analogWrite(M2_EN_pin,m2Speed);
}
  
void EB_MotorDriver::stop()
{
	digitalWrite(M1_EN_pin,HIGH);
	digitalWrite(M1_IN1_pin,LOW);
	digitalWrite(M1_IN2_pin,LOW);
	
	digitalWrite(M2_EN_pin,HIGH);
	digitalWrite(M2_IN1_pin,LOW);
	digitalWrite(M2_IN2_pin,LOW);
}
