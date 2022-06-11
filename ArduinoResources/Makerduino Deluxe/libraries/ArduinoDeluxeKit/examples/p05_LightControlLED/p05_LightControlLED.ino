/*
  Demo code for Project 5 Light Control LED
  
  Read the light information and then control led on or off.
 
  by Maker Studio
  http://makerstudio.cc
 */

int sensorPin = A0;    // select the input pin for the light sensor
int ledPin = 9;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);  
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);    
  if(sensorValue < 300){
    // turn the ledPin on
    digitalWrite(ledPin, HIGH);  
  }else{
    // turn the ledPin off:        
    digitalWrite(ledPin, LOW);   
  }
}
