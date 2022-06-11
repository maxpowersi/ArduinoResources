/*************************************************** 
  This is a library for the EB-Bluetooth

  The EB-Bluetooth uses software seiral and one extra pin for checking state.
  
  MakerStudio invests time and resources providing this open source code, 
  please support MakerStudio and open-source hardware by purchasing 
  products from MakerStudio!

  Written by Steve for MakerStudio.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#include "EB_Bluetooth.h"

EB_Bluetooth::EB_Bluetooth(uint8_t EB_Rx, uint8_t EB_Tx):swSerial(EB_Tx, EB_Rx)
{
	EB_rxPin = EB_Rx;
	EB_txPin = EB_Tx;
}

EB_Bluetooth::EB_Bluetooth(uint8_t EB_Rx, uint8_t EB_Tx, uint8_t EB_INT):swSerial(EB_Tx, EB_Rx)
{
	EB_rxPin = EB_Rx;
	EB_txPin = EB_Tx;
	EB_statePin = EB_INT;
}

//initialization
void EB_Bluetooth::begin()
{
	pinMode(EB_rxPin, OUTPUT);
	pinMode(EB_txPin, INPUT);
	pinMode(EB_statePin, INPUT);
	
	bluetoothState = 0;
	
	swSerial.begin(9600);// the default baudrate is 9600
}

int EB_Bluetooth::setName(String name)
{
	int isSuccess = 0;
	
	String recvBuf;
	char recvChar;
	
	String cmd("AT+NAME");
	cmd += name;
	cmd += '\r';
	cmd += '\n';
	int cmdLen = cmd.length();
	
	for(int i = 0; i < cmdLen; i++){
		swSerial.write(cmd[i]);
	}
	
	delay(200);
	int len = 0;
	if(len = available()){
		for(int i = 0; i < len; i++){
			recvChar = read();
			Serial.print(recvChar);
			recvBuf += recvChar;
		}
		if(recvBuf.indexOf(name) != -1){
			isSuccess= 1;
		}
	}
	
	return isSuccess;
}

int EB_Bluetooth::print(uint8_t byte)
{
	return(swSerial.write(byte));
}

int EB_Bluetooth::read()
{
	return(swSerial.read());
}

int EB_Bluetooth::available()
{
	return(swSerial.available());
}

//make sure the state pin is connected to the Arduino. return 1 - connected, 0 - unconnected
int EB_Bluetooth::connected()
{
	/*String conSymb = "+CONNECTED";//if connected, "+CONNECTED" will be sent back from the Bluetooth
	String parSymb = "+PAIRABLE";//if pairable, "+PAIRABLE" will be sent back from the Bluetooth
	String recvBuf;
	char recvChar;
	
	if(available()){
		recvChar = read();
		recvBuf += recvChar;
		if(recvBuf.indexOf(conSymb) != -1){
			bluetoothState = BLUETOOTH_CONNECTED;
		}
		if(recvBuf.indexOf(parSymb) != -1){
			bluetoothState = BLUETOOTH_PAIRABLE;
		}
	}*/
	
	int readState = digitalRead(EB_statePin);
	
	if(readState != bluetoothState){
		bluetoothState = readState;
		delay(1);
		swSerial.flush();
	}
	
	return bluetoothState;
}
