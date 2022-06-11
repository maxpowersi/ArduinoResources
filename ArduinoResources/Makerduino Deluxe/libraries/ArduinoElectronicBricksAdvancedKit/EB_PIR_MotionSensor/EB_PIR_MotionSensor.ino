/*
  EB - PIR_MotionSensor demo code
  
  Output the state when detecting people move nearby. 
  
  http://makerstudio.cc
 */
const int PIRSensorPin = 2;     // the number of the Sensor pin

// variables will change:
int sensorState = 0;         // variable for reading the Sensor status

int flag = 0; //use the flag to prevent continuous outputing when no moving people

void setup() {
  // initialize the Sensor pin as an input:
  pinMode(PIRSensorPin, INPUT);
  digitalWrite(PIRSensorPin, LOW);
  Serial.begin(9600);
}

void loop(){
  // read the state of the Sensor value:
  sensorState = digitalRead(PIRSensorPin);

  // check if the moving people sensed.
  // if it is, the sensorState is HIGH:
  if (sensorState == HIGH) {     
    // turn Buzzer on:    
    Serial.println("Moving people detected");
	flag = 0;
  } 
  else {
    if(flag == 0){
	  Serial.println("No moving people");
	  flag = 1;
	}
  }
}
