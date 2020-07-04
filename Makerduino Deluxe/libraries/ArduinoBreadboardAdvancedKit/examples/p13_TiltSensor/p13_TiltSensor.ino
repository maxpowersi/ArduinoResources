/*
  Arduino Advanced Kit example
  Project 13 - TiltSensor
 
 Turns on LED connected to pin 13, when the sensor
 tilted. 
 
  
 http://makerstudio.cc/
 */

// constants won't change. They're used here to 
// set pin numbers:
const int tiltSensorPin = 8;     // tilt sensor connected to pin 8
const int ledPin =  13;      // LED pin

// variables will change:
int tiltState = 0;         // variable for reading the sensor status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the sensor pin as an input:
  pinMode(tiltSensorPin, INPUT);     
}

void loop(){
  // read the state of the sensor value:
  tiltState = digitalRead(tiltSensorPin);

  // check if the sensor is tilted.
  // if it is, the sensor is HIGH:
  if (tiltState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  }
}
