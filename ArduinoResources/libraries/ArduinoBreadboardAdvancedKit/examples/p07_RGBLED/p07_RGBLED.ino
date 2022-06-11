/*
  Arduino Advanced Kit example
  Project 7 - RGBLED
 
  Control RGB LED lighting with different color
 
  http://makerstudio.cc/
 */


const int redPin = 9;    // LED connected to digital pin 9
const int greenPin = 10;
const int bluePin = 11;

void setup()  { 
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  digitalWrite(redPin,HIGH);
  digitalWrite(greenPin,HIGH);
  digitalWrite(bluePin,HIGH);  
} 

void loop()  { 
  //turn LED red
  digitalWrite(redPin,LOW);
  digitalWrite(greenPin,HIGH);
  digitalWrite(bluePin,HIGH);  
  delay(1000);
  
  //turn LED green
  digitalWrite(redPin,HIGH);
  digitalWrite(greenPin,LOW);
  digitalWrite(bluePin,HIGH);  
  delay(1000);  
  
  //turn LED blue
  digitalWrite(redPin,HIGH);
  digitalWrite(greenPin,HIGH);
  digitalWrite(bluePin,LOW);  
  delay(1000);
  
  //turn LED yellow 
  digitalWrite(redPin,LOW);
  digitalWrite(greenPin,LOW);
  digitalWrite(bluePin,HIGH);  
  delay(1000);
  
  //turn LED purple
  digitalWrite(redPin,LOW);
  digitalWrite(greenPin,HIGH);
  digitalWrite(bluePin,LOW);  
  delay(1000);
  
  //turn LED 
  digitalWrite(redPin,HIGH);
  digitalWrite(greenPin,LOW);
  digitalWrite(bluePin,LOW);  
  delay(1000);
  
  //turn LED sky blue
  digitalWrite(redPin,LOW);
  digitalWrite(greenPin,LOW);
  digitalWrite(bluePin,LOW);  
  delay(1000);
}



