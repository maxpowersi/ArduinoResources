/*
  EB - TiltSensor demo code
 
 Output the information to Serial Monitor when the sensor tilted. 
 
 http://makerstudio.cc
 */
const int tiltSensorPin = 8;     // tilt sensor connected to pin 8
// variables will change:
int tiltState = 0;         // variable for reading the sensor status
void setup() {
  // initialize the sensor pin as an input:
  pinMode(tiltSensorPin, INPUT);     
  Serial.begin(9600);
}
void loop(){
  // read the state of the sensor value:
  tiltState = digitalRead(tiltSensorPin);
  // if the sensor is tilted in one direction, it outputs HIGH:
  if (tiltState == HIGH) {     
    Serial.println("The sensor is tilteld in one direction");
  } 
}
