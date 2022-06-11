/*
  Arduino Electronic Brick Starter Kit example
  Project 6 - LightControlBreathingLED
  
  This example shows the LED breathing in different speed
  based on the light sensed
  
  http://makerstudio.cc/
 */


int ledPin = 9;     // LED connected to digital pin 9
int analogInPin = A0; // Light sensor pin
int sensorValue = 0;// value read from the sensor

void setup()  { 
  // nothing happens in setup 
} 

void loop()  { 
  // read the light sensor value:
  sensorValue = analogRead(analogInPin);
  
  // get the meaningful fading value
  int gapValue = map(sensorValue,10,1024,2,30);
  
  // fade in from min to max in increments of 5 points:
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);         
    // wait for some milliseconds to see the dimming effect    
    delay(gapValue);                            
  } 

  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);         
    // wait for some milliseconds to see the dimming effect    
    delay(gapValue);                            
  } 
}
