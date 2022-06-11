/*
  EB - Toggle Touch Sensor demo code
  
  Detect the state of a Touch Sensor and display the information on Serial Monitor
  When the sensor is touched, the instruction LED on the board will turn on.
  When takes the finger off the sensor, the light will keep on.
  When touch again, the light will turn off.
  
  http://makerstudio.cc
*/

// constants won't change. They're used here to 
// set pin numbers:
const int sensorPin = 2;     // Touch the sensor on the top side or the bottom side

int sensorState = LOW;
int saveState = LOW;
void setup() {
  // initialize the sensor pin as an input:
  pinMode(sensorPin, INPUT);     
  Serial.begin(9600);
}
void loop(){
  // read the state of the sensor value:
  sensorState = digitalRead(sensorPin);
  
  if(sensorState != saveState){
		saveState = sensorState;
		Serial.println("Sensor is touched ");
	}
}
