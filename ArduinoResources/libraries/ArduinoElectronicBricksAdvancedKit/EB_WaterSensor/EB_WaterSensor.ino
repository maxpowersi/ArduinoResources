/*
  EB - Water Sensor demo code
  
  See the changes when there's water and no water on the sensor. 
  
  http://makerstudio.cc
 */
// Connect the sensor to Analog input 5
const int sensorPin = A5;
int sensorValue = 0;
void setup() {
  // initialize serial communications at 9600 bps:                
  Serial.begin(9600);
}
// the loop routine runs over and over again forever:
void loop() {
  // read the analog in value:
  sensorValue = analogRead(sensorPin);            
  // print the results to the serial monitor
  Serial.print("sensor = " );//see the difference when there's water or not                      
  Serial.println(sensorValue);      
  delay(1000);// Do sampling every other second
}
