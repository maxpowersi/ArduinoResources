/*
  EB - MemorialButton demo code
  
  Detect the state of a button and display the information on Serial Monitor 
  The momentary button will keep the state untill you push it again.
  
  http://makerstudio.cc
*/

// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

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
