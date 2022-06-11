/*
  EB - Relay demo code
  
  Turns on an Relay for one second, then off for one second, repeatedly.
  
  http://makerstudio.cc
 */
// connect Relay to arduino pin 9
const int relay = 9;
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(relay, OUTPUT);     
}
// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(relay, HIGH);   // turn the Relay on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(relay, LOW);    // turn the Relay off by making the voltage LOW
  delay(1000);               // wait for a second
}
