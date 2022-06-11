/*
  Demo code for Project 9 - Digital LED
  
  Control 7-segment LED
 
  by Maker Studio
  http://makerstudio.cc
 */

// The segment of LED connected to Arduino Pins
const int EPin = 13;    
const int DPin = 12;
const int CPin = 11;
const int DPPin = 10;
const int BPin = 9;
const int APin = 8;
const int FPin = 7;
const int GPin = 6;

int gapTime = 1000; // 100ms

void setup()  { 
  //set the pins OUTPUT
  pinMode(APin,OUTPUT);
  pinMode(BPin,OUTPUT);
  pinMode(CPin,OUTPUT);
  pinMode(DPin,OUTPUT);
  pinMode(EPin,OUTPUT);
  pinMode(FPin,OUTPUT);
  pinMode(GPin,OUTPUT);
  pinMode(DPPin,OUTPUT);
  
  
} 

void loop()  { 
//display digital number from 0 to 9
display0();
delay(gapTime);

display1();
delay(gapTime);

display2();
delay(gapTime);

display3();
delay(gapTime);

display4();
delay(gapTime);

display5();
delay(gapTime);

display6();
delay(gapTime);

display7();
delay(gapTime);

display8();
delay(gapTime);

display9();
delay(gapTime);

//display the point
displayDP();
delay(gapTime);

//allOn();
//delay(gapTime);

}

void display0(){
  allOn();
  digitalWrite(GPin,HIGH);
  digitalWrite(DPPin,HIGH);
}

void display1(){
  allOff();
  digitalWrite(BPin,LOW);
  digitalWrite(CPin,LOW);
}

void display2(){
  allOn();
  digitalWrite(FPin,HIGH);
  digitalWrite(CPin,HIGH);
  digitalWrite(DPPin,HIGH);
  
}

void display3(){
  allOn();
  digitalWrite(EPin,HIGH);
  digitalWrite(FPin,HIGH);
  digitalWrite(DPPin,HIGH);
}

void display4(){
  allOn();
  digitalWrite(APin,HIGH);
  digitalWrite(DPin,HIGH);
  digitalWrite(EPin,HIGH);
  digitalWrite(DPPin,HIGH);
}

void display5(){
  allOn();
  digitalWrite(BPin,HIGH);
  digitalWrite(EPin,HIGH);
  digitalWrite(DPPin,HIGH);
  
}

void display6(){
  allOn();
  digitalWrite(BPin,HIGH);
  digitalWrite(DPPin,HIGH);
}

void display7(){
  allOff();
  digitalWrite(APin,LOW);
  digitalWrite(BPin,LOW);
  digitalWrite(CPin,LOW);
}

void display8(){
allOn();
digitalWrite(DPPin,HIGH);
}

void display9(){
display8();
digitalWrite(EPin,HIGH);
}

void displayDP(){
  allOff();
  digitalWrite(DPPin,LOW);
}

void allOn(){
  digitalWrite(APin,LOW);
  digitalWrite(BPin,LOW);
  digitalWrite(CPin,LOW);  
  digitalWrite(DPin,LOW);
  digitalWrite(EPin,LOW);
  digitalWrite(FPin,LOW);
  digitalWrite(GPin,LOW);
  digitalWrite(DPPin,LOW);
}

void allOff(){
  digitalWrite(APin,HIGH);
  digitalWrite(BPin,HIGH);
  digitalWrite(CPin,HIGH);  
  digitalWrite(DPin,HIGH);
  digitalWrite(EPin,HIGH);
  digitalWrite(FPin,HIGH);
  digitalWrite(GPin,HIGH);
  digitalWrite(DPPin,HIGH);
}

