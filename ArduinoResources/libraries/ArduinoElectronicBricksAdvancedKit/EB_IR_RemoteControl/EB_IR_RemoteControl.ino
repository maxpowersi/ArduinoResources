/*
 EB - IR Remote Control demo code
 
 Receive the signal from the IR controller, and output the key information
 
 http://makerstudio.cc
 */
 
#include <Wire.h>
#include "InfraredReceiver.h"

int key;//pressed key
//The code uses interrupt 0, and it works only when the module is connected to D2 of Arduino
InfraredReceiver infraredReceiver; 
void setup() {
  infraredReceiver.begin();
  Serial.begin(9600);
  Serial.println("Infrared Receiver is waiting for the control signal");
  Serial.println("Make sure the Infrared Module is connected to D2 of Arduino");
}

void loop() {
  key = infraredReceiver.read();// get the pressed key information
  if (key >= 0) 
  {
    Serial.print("Key=");//Display the key information 
    Serial.println(key);
    Serial.println();
  }
}