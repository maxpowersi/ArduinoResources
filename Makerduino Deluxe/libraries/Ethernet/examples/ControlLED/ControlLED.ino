/*
 Yeelink sensor client power switch example
 */

#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>
#include <math.h>
 
int LED_Pin=4; 
int Relay_Pin = 5;

byte buff[2];

// for yeelink api
#define APIKEY         "90a0a22b9658b99594caef47b3247a46" // 此处替换为你自己的API KEY
#define DEVICEID       340660 // 此处替换为你的设备编号
#define SENSORID       377375 // 此处替换为你的传感器编号

// assign a MAC address for the ethernet controller.
byte mac[] = { 0x00, 0x1D, 0x72, 0x82, 0x35, 0x9D};
IPAddress ip(192,168,1,177);
// initialize the library instance:
EthernetClient client ;
char server[] = "api.yeelink.net";   // name address for yeelink API

unsigned long lastConnectionTime = 0;          // last time you connected to the server, in milliseconds
boolean lastConnected = false;                 // state of the connection last time through the main loop
const unsigned long postingInterval = 3*1000; // delay between 2 datapoints, 30s
String returnValue = ""; 
boolean ResponseBegin = false;

void setup() {
  pinMode(LED_Pin, OUTPUT);
  pinMode(Relay_Pin, OUTPUT);
  Wire.begin();
  // start serial port:
 Serial.begin(9600);
 Ethernet.begin(mac, ip);
 /*
  // start the Ethernet connection with DHCP:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    for(;;)
      ;
  }
  else {
    Serial.println("Ethernet configuration OK");
  }*/
}

void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:

  if (client.available()) {
    char c = client.read();
   // Serial.print(c);
      if (c == '{')
        ResponseBegin = true;
      else if (c == '}')
        ResponseBegin = false;

      if (ResponseBegin)
        returnValue += c;   
  }
  if (returnValue.length() !=0 && (ResponseBegin == false))
  {
    Serial.println(returnValue);
    
    if (returnValue.charAt(returnValue.length() - 1) == '1') {
      Serial.println("turn on the LED and Relay"); 
      digitalWrite(LED_Pin, HIGH);
	  digitalWrite(Relay_Pin, HIGH);
    } 
      else if(returnValue.charAt(returnValue.length() - 1) == '0') {
      Serial.println("turn off the LED and Relay"); 
      digitalWrite(LED_Pin, LOW);
	  digitalWrite(Relay_Pin, LOW);

      }
     returnValue = "";
  }
  // if there's no net connection, but there was one last time
  // through the loop, then stop the client:
  if (!client.connected() && lastConnected) {
    
    Serial.println("disconnecting.");
	Serial.println();
	
    client.stop();
  }
  
  // if you're not connected, and ten seconds have passed since
  // your last connection, then connect again and send data:
  if(!client.connected() && (millis() - lastConnectionTime > postingInterval)) {
    // read sensor data, replace with your code
    //int sensorReading = readLightSensor();
    Serial.print("yeelink:");
    //get data from server  
    getData();
  }
  // store the state of the connection for next time through
  // the loop:

  lastConnected = client.connected();
}



// this method makes a HTTP connection to the server and get data back
void getData(void) {
  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP GET request:
    
    client.print("GET /v1.0/device/");
    client.print(DEVICEID);
    client.print("/sensor/");
    client.print(SENSORID);
    client.print("/datapoints");
    client.println(" HTTP/1.1");
    client.println("Host: api.yeelink.net");
    client.print("Accept: *");
    client.print("/");
    client.println("*");
    client.print("U-ApiKey: ");
    client.println(APIKEY);
    client.println("Content-Length: 0");
    client.println("Connection: close");
    client.println();
    Serial.println("print get done.");
    
  } 
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
    Serial.println("disconnecting.");
	Serial.println();
    client.stop();
  }
   // note the time that the connection was made or attempted:
  lastConnectionTime = millis();
}

 
