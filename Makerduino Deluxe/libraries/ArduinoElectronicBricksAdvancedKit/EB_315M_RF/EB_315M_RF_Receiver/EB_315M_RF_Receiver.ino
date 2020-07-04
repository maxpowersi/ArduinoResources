/*
  EB - 315MHz_RF_Receiver demo code
  
  Wait to receive message sent from the transimtter
  
  http://makerstudio.cc
 */
 
#include <Wire.h>
#include <VirtualWire.h>

int RF_RX_PIN = 2;

void setup()
{
  Serial.begin(9600);
  Serial.println("setup");
  vw_set_rx_pin(RF_RX_PIN);  // Setup receive pin.
  vw_setup(2000); // Transmission speed in bits per second.
  vw_rx_start(); // Start the PLL receiver.
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  if(vw_get_message(buf, &buflen)) // non-blocking I/O
  {
    int i;
    // Message with a good checksum received, dump HEX
    Serial.print("Got: ");
    for(i = 0; i < buflen; ++i)
    {
      Serial.print(char(buf[i]));
      //Serial.print(" ");
    }
    Serial.println("");
  }
}

