/*  
  Demo code for Project 17 - bluetooth
  
  by Maker Studio
*/
#include "EB_Bluetooth.h"
#include <SoftwareSerial.h>

//EB_Bluetooth(RX, TX)
EB_Bluetooth myBluetooth(11,10);

void setup()
{
	Serial.begin(9600);
	myBluetooth.begin();
	if(myBluetooth.setName("MakerStudio")){
		Serial.println("Set Bluetooth Name Ok");
	}else{
		Serial.println("Set Bluetooth Name Failed");
	}
	Serial.println("Waiting to be connected");
}

void loop()
{
	char dat;
	if(myBluetooth.available()){
		dat = myBluetooth.read();
		Serial.print(dat);
	}
	if(Serial.available()){
		dat = Serial.read();
		myBluetooth.print(dat);
	}
}