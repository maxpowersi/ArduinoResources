/*
  Demo code for Project 25 - Wireless Remote Control Kit
  
  Detect the state of D7-D11 and display the information on Serial Monitor
  
  http://makerstudio.cc
*/

// constants won't change. They're used here to 
// set pin numbers:
const int Pin0 = 7;     
const int Pin1 = 8;
const int Pin2 = 9;
const int Pin3 = 10;
const int Pin4 = 11;
//set low state ;
int State0 = LOW;
int State1 = LOW;
int State2 = LOW;
int State3 = LOW;
int State4 = LOW;

void setup() {
  // initialize the Recever pins as  input:
pinMode(Pin0, INPUT);
pinMode(Pin1, INPUT);
pinMode(Pin2, INPUT);
pinMode(Pin3, INPUT);
pinMode(Pin4, INPUT);
  Serial.begin(9600);
}
void loop(){
  // read the state of the pushbutton value:
 State0 = digitalRead(Pin0);
 State1 = digitalRead(Pin1);
 State2 = digitalRead(Pin2);
 State3 = digitalRead(Pin3);
 State4 = digitalRead(Pin4);
if(State4)//State4 act as the flag of received message.
//it equals 1 when received message,else equals 0.
 { 
    //print matched flag of the received message;
    if(State0){Serial.println("received data:B");}
    if(State1){Serial.println("received data:D");}
    if(State2){Serial.println("received data:A");}
    if(State3){Serial.println("received data:C");} 
 }  
else          
 {  
   //no message received.
 }
  delay(100);
}

