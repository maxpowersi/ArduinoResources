/*
	Demo code of P23 - Soft Keypad 
	by maker studio
*/
#include "TM1650.h"

TM1650 keyPad(18,19);

void setup()
{
	Serial.begin(9600);
}

void loop()
{   char key=0;
	switch(keyPad.readKey())
    {
		case 0x4c:key='1'; break;
		case 0x4d:key='4'; break;
		case 0x4e:key='7'; break;
		case 0x4f:key='*'; break;
		case 0x54:key='2'; break;
		case 0x55:key='5'; break;
		case 0x56:key='8'; break;
		case 0x57:key='0'; break;
		case 0x64:key='3'; break;
		case 0x65:key='6'; break;
		case 0x66:key='9'; break;
		case 0x67:key='#'; break;
		case 0x74:key='A'; break;
		case 0x75:key='B'; break;
		case 0x76:key='C'; break;
		case 0x77:key='D'; break;
		default: break;
		}
	Serial.println(key);
	delay(200);
}
