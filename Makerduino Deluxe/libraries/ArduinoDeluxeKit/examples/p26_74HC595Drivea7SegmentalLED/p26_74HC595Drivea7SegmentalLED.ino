/*
    Demo code for Project 26 - 74HC595 Drive a 7 Segmental LED 
*/
int latchPin = 8;
int clockPin = 12;
int dataPin = 11; //pins 74HC595 are connected to

void setup ()
{
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT); //set the pins OUTPUT
}

void loop()
{

  int a[]={
  249,164,176,153,146,130,248,128,144,//0~9  decimal of octet
  136,131,167,161,134,142
  //a~f
  };   //QO,Q1,Q2,Q3,Q4,Q5,Q6,Q7 - - a,b,c,d,e,f,g,dp 
  for(int x=0; x<16 ;x++ )                        
  {
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,MSBFIRST,a[x]);     
	// display a[] by function shiftOut(), MSB_First
    digitalWrite(latchPin,HIGH);
    delay(1000);
  }
}
