/*
  EB - Button demo code
  
  Detect the state of a button and display the information on Serial Monitor
  
  http://makerstudio.cc
*/

// constants won't change. They're used here to 
// set pin numbers:
const int buttonPin = 2;     // the pushbutton pin

int buttonState = LOW;
void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);     
  Serial.begin(9600);
}
void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
   
  Serial.print("Button State: ");
  Serial.println(buttonState);
}
