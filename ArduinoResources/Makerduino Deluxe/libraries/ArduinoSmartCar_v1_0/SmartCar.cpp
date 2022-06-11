/*************************************************** 
  This is a library for Control Car in different way
  
  MakerStudio invests time and resources providing this open source code, 
  please support MakerStudio and open-source hardware by purchasing 
  products from MakerStudio!

  Written by Steve for MakerStudio.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#include "SmartCar.h"

//Macros for direction
#define FORWARD			'U'
#define BACKWARD		'D'
#define LEFT			'L'
#define RIGHT			'R'
#define LEFT_FORWARD	'X'
#define RIGHT_FORWARD	'Y'
#define LEFT_BACK		'W'
#define RIGHT_BACK		'Z'

//Macros for mode
#define	_MODE_HEAD		"ABC"
#define _JOYSTIC_HEAD	"ULDRWXYZ"

#define JOYSTIC_MODE	'A'
#define LINEFINDER_MODE	'B'
#define ULTRASONIC_MODE	'C'

//speed difference for two motors when turning big round
#define SPEED_DIF 50

const int speed_pwm[] = {0,120,154,187, 221,255};

//MotorDriver Pins (M1_EN,M1_IN2,M1_IN1, M2_EN,M2_IN2,M2_IN1)
EB_MotorDriver motorDriver(5,12,13, 6,7,8);

//Bluetooth Pins (TX, RX, INT)
EB_Bluetooth bluetooth(11,10,9);

//Ultrasonic Pins(Trig,Echo)
EB_UltrasonicSensor ultrasonicSensor(16,17);

//LineFinder Pins(Sensor1, Sensor2)
EB_LineFinder lineFinder(14, 15);

//define string vairalbe for mode and joystic head
String modeHead(_MODE_HEAD);
String joystickHead(_JOYSTIC_HEAD);
  
SmartCar::SmartCar()
{}

void SmartCar::begin()
{
	//Initialize the global va
	modeDat = JOYSTIC_MODE;
	directionDat = FORWARD;
	speedDat = '0';
    
	//Initialize motorDirver
	motorDriver.begin();
	
	//Initialize bluetooth
	bluetooth.begin();
	
	//Initialize ultrasonicSensor
	ultrasonicSensor.begin();
	
	//Initiallize lineFinder
	lineFinder.begin();
	
	//get the random seed for ultrasonic mode
	randomSeed(analogRead(0));
}

void SmartCar::readCommand(){
	char dat;
	if(bluetooth.available()){
		dat = bluetooth.read();
		Serial.print(dat);
		if(modeHead.indexOf(dat) != -1){//receive mode command
			//Serial.println("Receive mode command");
			modeDat = dat;
			dat = bluetooth.read();
			Serial.println(dat);
			if(dat >= '0' && dat <= '5'){
			speedDat = dat;
			}
		}else if(joystickHead.indexOf(dat) != -1){//receive joystic command
			//Serial.println("Receive joystic command");
			directionDat = dat;
			dat = bluetooth.read();
			Serial.println(dat);
			if(dat >= '0' && dat <= '5'){
			speedDat = dat;
			}
		}
	}
}

void SmartCar::processCommand()
{
	speedPWM = speed_pwm[speedDat - '0'];
	
	switch(modeDat){
		case JOYSTIC_MODE:joysticMode(directionDat,speedPWM);break;
		case LINEFINDER_MODE:lineFinderMode(speedPWM);break;
		//case ULTRASONIC_MODE:ultrasonicMode(speedPWM);break;
		default:break;
	}
}

void SmartCar::joysticMode(char direction, int speed)
{
	int differentialSpeed = 0;
	
	if(speed >= SPEED_DIF){
		differentialSpeed = speed - SPEED_DIF;
	}
	
	switch(direction){
		case FORWARD:motorDriver.run(speed, speed);break;//forward
		case BACKWARD:motorDriver.run(-speed, -speed);break;//backward
		case LEFT:motorDriver.run(-speed, speed);break;//left
		case RIGHT:motorDriver.run(speed, -speed);break;//right
		case LEFT_FORWARD:motorDriver.run(differentialSpeed, speed);break;//leftforward
		case RIGHT_FORWARD:motorDriver.run(speed, differentialSpeed);break;//rightforward
		case LEFT_BACK:motorDriver.run(-differentialSpeed, -speed);break;//leftback
		case RIGHT_BACK:motorDriver.run(-speed, -differentialSpeed);break;//rightback
		default:break;
	}
}

void SmartCar::lineFinderMode(int speed)
{	
	//get the speed for two motors
	int differentialSpeed = 0;
	
	if(speed >= SPEED_DIF){
		differentialSpeed = speed - SPEED_DIF;
	}
	
	//try to make the car run along with the black line
	static char lastDirection = FORWARD;
	int sensor1 = lineFinder.sensor1();
	int sensor2 = lineFinder.sensor2();
		
	if( 0 == sensor1 && 0 == sensor2 ){//move forward
		motorDriver.run(speed, speed);
		lastDirection = FORWARD;
	}else if( 1 == sensor1 && 0 == sensor2 ){//turn left
		motorDriver.run(-speed, speed);
		lastDirection = LEFT;
	}else if( 0 == sensor1 && 1 == sensor2 ){//turn right
		motorDriver.run(speed, -speed);
		lastDirection = RIGHT;
	}else if( 1 == sensor1 && 1 == sensor2 ){//get back to the line
		if(LEFT == lastDirection){//turn left forward
			motorDriver.run(50, 100);
			//lastDirection = RIGHT;
		}else if(RIGHT == lastDirection){//turn right forward
			motorDriver.run(100, 50);
			//lastDirection = LEFT;
		}
	}
	
}

void SmartCar::ultrasonicMode(int speed)
{
	static int randomFlag = 1;
	static int randomDirection = 0;
	if(1 == randomFlag){
		randomDirection = random(0,2);
		//Serial.println(randomDirection);
	}
	int distance = ultrasonicSensor.distance();
	//delay(10);
	//Serial.println(distance);
	
	if(distance > 40){
		motorDriver.run(speed, speed);
		randomFlag = 1;
	}else{
		if(randomDirection == 0){//turn left
			motorDriver.run(-speed,speed);
			randomFlag = 0;
		}else{//turn right
			motorDriver.run(speed,-speed);
			randomFlag = 0;
		}
	}
	
}
