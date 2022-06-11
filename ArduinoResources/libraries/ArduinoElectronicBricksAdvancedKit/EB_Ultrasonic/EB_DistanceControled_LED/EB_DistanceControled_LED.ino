/*
  EB - DistanceControled_LED demo code
  
  Change the lighting strength based on the distance of closing object
  
  http://makerstudio.cc
 
*/

#include "Ultrasonic.h"

Ultrasonic ultrasonic(11,10);//(Trig,Echo)

int distance = 0;
const int LED = 3;//Digital pin 3 with PWM function
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
	Serial.begin(9600);
}

void loop()
{
	//output the distance in cm
	distance = ultrasonic.Ranging(CM);
	Serial.println(distance); 
	
	if(distance < 20){
	  outputValue = map(distance, 0, 20, 255, 0);
	  // change the analog out value:
	  analogWrite(LED, outputValue); 
	}else{
	  digitalWrite(LED, LOW);
	}
	delay(100);
}