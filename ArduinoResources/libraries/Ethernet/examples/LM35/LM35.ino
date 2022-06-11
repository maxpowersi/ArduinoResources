#include <Ethernet.h>
#include <WiFi.h>
#include <SPI.h>
#include <yl_data_point.h>
#include <yl_device.h>
#include <yl_w5100_client.h>
#include <yl_wifi_client.h>
#include <yl_messenger.h>
#include <yl_sensor.h>
#include <yl_value_data_point.h>
#include <yl_sensor.h>

//this example reads data from a lm35dz sensor, convert value to degree Celsius
//and then post it to yeelink.net

//replace 2633 3539 with ur device id and sensor id
yl_device ardu(340660);  //此处替换为你的设备编号
yl_sensor therm(377377, &ardu);//此处替换为你的传感器编号
//replace first param value with ur u-apikey
yl_w5100_client client;
yl_messenger messenger(&client, "90a0a22b9658b99594caef47b3247a46", "api.yeelink.net");   //此处替换为你自己的API KEY

const int THERM_PIN  = A0;

float lm35_convertor(int analog_num)
{
	return analog_num * (5.0 / 1024.0 * 100);
}

void setup()
{
    Serial.begin(9600);	//for output information
	byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xAA};
	if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    for(;;)
      ;
  }
  else {
    Serial.println("Ethernet configuration OK");
  }
}

void loop()
{
	int v = analogRead(THERM_PIN);
        Serial.println(lm35_convertor(v));
		yl_value_data_point dp(lm35_convertor(v));
		therm.single_post(messenger, dp);
		delay(1000);
}
