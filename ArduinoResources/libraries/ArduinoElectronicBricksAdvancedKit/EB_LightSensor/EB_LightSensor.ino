/*
  EB - LightSensor demo code
  
  Analog input, serial output
  Reads an analog input pin,and prints the results to the serial monitor.
  
  http://makerstudio.cc
 */
const int analogInPin = A5;  // Analog input pin 
int sensorValue = 0;        // value read from the sensor
void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}
void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);            
  // print the results to the serial monitor:
  Serial.print("sensor = " );                       
  Serial.println(sensorValue);      
  // wait 200 milliseconds before the next loop
  delay(200);                     
}
