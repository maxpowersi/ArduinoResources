/*
  Demo code for Project 13 - PIRMotionSensor
  
  Turns on a LED connected to digital  
  pin 13, when people nearby moves. The
  state of LED will keep a while, then
  go off.
 
  by Maker Studio

 */

// constants won't change. They're used here to 
// set pin numbers:
const int PIRSensorPin = 2;     // the number of the Sensor pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int sensorState = 0;         // variable for reading the Sensor status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the Sensor pin as an input:
  pinMode(PIRSensorPin, INPUT);     
}

void loop(){
  // read the state of the Sensor value:
  sensorState = digitalRead(PIRSensorPin);

  // check if the moving people sensed.
  // if it is, the sensorState is HIGH:
  if (sensorState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  }
}
