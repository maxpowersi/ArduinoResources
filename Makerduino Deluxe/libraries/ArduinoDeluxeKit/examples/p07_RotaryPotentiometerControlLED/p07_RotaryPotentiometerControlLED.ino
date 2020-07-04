/*
    Demo code for Project 7 - Rotary Potentiometer Control LED
*/
int potentiometerPin = A0;//pin the potentiometer is connected to
int ledPinR = 9;
int ledPinG = 10;
int ledPinB = 11;
int value =0;
void setup()
{
    pinMode(potentiometerPin,INPUT);
    pinMode(ledPinR,OUTPUT);
	pinMode(ledPinG,OUTPUT);
	pinMode(ledPinB,OUTPUT);
}
void loop()
{
    value = analogRead(potentiometerPin);
    //get the value from potentiometerPin 
    value = map(value,0,1023,0,255);
    //map the range from[0,1023] to [0,255]
    analogWrite(ledPinR,value);
	analogWrite(ledPinG,value);
	analogWrite(ledPinB,value);
    //adjust the brightness of led by the value   
}
