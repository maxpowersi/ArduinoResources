/*
	Demo code of P21 - 4 Digital 7-Segment LED with Time Separator
	by maker studio
*/
#include "TM1650.h"
#include <inttypes.h>

TM1650 DigitalLED(18,19);
int8_t number[] = {0,0,0,0};
void setup()
{
	//Serial.begin(9600);
}

void loop()
{
	for(int i  = 0; i< 4; i++)
	{
		number[i]+=1;
	}
	DigitalLED.display(number);
	
	delay(1000);
}