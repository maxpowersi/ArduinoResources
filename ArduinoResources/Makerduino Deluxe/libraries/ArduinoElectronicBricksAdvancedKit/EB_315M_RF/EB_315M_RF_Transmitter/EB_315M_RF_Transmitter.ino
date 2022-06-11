/*
  EB - 315MHz_RF_Transmitter demo code
  
  Tansmit message "Hello" to the Receiver every other second
  
  http://makerstudio.cc
 */
#include <Wire.h>
#include <VirtualWire.h>

int RF_TX_PIN = 2;

void setup()
{
  vw_set_tx_pin(RF_TX_PIN); // Setup transmit pin
  vw_setup(2000); // Transmission speed in bits per second.
}
void loop()
{
  const char *msg = "Hello";
  vw_send((uint8_t *)msg, strlen(msg));  // Send 'Hello' every 1000ms.
  delay(1000);
}
