/*
  EB - RGB LED demo code
  
  Change the RGB LED Color and light intensity repeatedly.
  
  http://makerstudio.cc
 */
// connect led to arduino pin 9,10,11
const int pinR = 9;
const int pinG = 10;
const int pinB = 11;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(pinR, OUTPUT);     
  pinMode(pinG, OUTPUT); 
  pinMode(pinB, OUTPUT); 
  digitalWrite(pinR, HIGH);
  digitalWrite(pinG, HIGH);
  digitalWrite(pinB, HIGH);
}

// the loop routine runs over and over again forever:
void loop() {
fading(pinR);
fading(pinG);
fading(pinB);
}

void fading(int ledPin)  { 
  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 
  
  // fade in from min to max in increments of 5 points:
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 
}
