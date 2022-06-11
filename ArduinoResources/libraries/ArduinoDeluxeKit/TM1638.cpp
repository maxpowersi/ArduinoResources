
/*
	www.makerstudio.cc
*/
#include "TM1638.h"
#include <Arduino.h>
						   
static uint8_t lineAddr[] = {0xC0,0xC2,0xC4,0xC6,0xC8,0xCA,0xCC,0xCE};//line address

static uint8_t bitMask[] = {0x7F,0xBF,0xDF,0xEF,0xF7,0xFB,0xFD,0xFE};//for controling colume data

TM1638::TM1638(uint8_t STB, uint8_t CLK, uint8_t DIO)
{
  STB_pin = STB;
  CLK_pin = CLK;
  DIO_pin = DIO;
  pinMode(STB_pin,OUTPUT);
  pinMode(CLK_pin,OUTPUT);
  pinMode(DIO_pin,OUTPUT);
  for(int i = 0; i < 8; i++){
	matrixDat[i] = 0;
  }
}

void TM1638::writeByte(uint8_t wr_data)
{
  uint8_t i,count1;   
  for(i=0;i<8;i++)        //sent 8bit data
  {
    digitalWrite(CLK_pin,LOW);      
    if(wr_data & 0x01){
		digitalWrite(DIO_pin,HIGH);//LSB first
    }else{
		digitalWrite(DIO_pin,LOW);
	}
    wr_data >>= 1;      
    digitalWrite(CLK_pin,HIGH);
  }  
}

void TM1638::writeByteMSB(uint8_t wr_data)
{
  uint8_t i,count1;   
  for(i=0;i<8;i++)        //sent 8bit data
  {
    digitalWrite(CLK_pin,LOW);      
    if(wr_data & 0x80){
		digitalWrite(DIO_pin,HIGH);//MSB first
    }else{
		digitalWrite(DIO_pin,LOW);
	}
    wr_data <<= 1;      
    digitalWrite(CLK_pin,HIGH);
  }  
}

void TM1638::writeCmd(uint8_t cmd)
{
	digitalWrite(STB_pin,HIGH);
    digitalWrite(STB_pin,LOW);
	writeByte(cmd);
	
}

void TM1638::writeDat(uint8_t gridAddr, uint8_t wr_data)
{
	writeCmd(0x44);//fix address
	
	writeCmd(gridAddr);
		
	//writeByte(wr_data);
	writeByteMSB(wr_data);
	
	writeCmd(0x8F);
	
	digitalWrite(STB_pin,HIGH);
}

void TM1638::displayMatrixDat()
{
	uint8_t startAddr = 0xC0;
	for(int i = 0; i < 8; i++){
		writeDat(startAddr,matrixDat[i]);
		startAddr +=2;
	}
}

void TM1638::clear()
{
	for(int i = 0; i < 8; i++){
		matrixDat[i] = 0;
	}
	displayMatrixDat();
}

void TM1638::displayAll()
{
	for(int i = 0; i < 8; i++){
		matrixDat[i] = 0xFF;
	}
	displayMatrixDat();
}

void TM1638::displayPic(uint8_t picDat[8])
{
	for(int i = 0; i < 8; i++){
		setLine(i, picDat[i]);
	}
}

void TM1638::setPoint(uint8_t line, uint8_t colume, uint8_t state)
{
	if(line<8 && colume<8){
		if(state == 0){
			matrixDat[line] &= bitMask[colume];
		}else{
			matrixDat[line] |= ~bitMask[colume];
		}
		displayMatrixDat();
	}	
}

void TM1638::displayLine(uint8_t line)
{	
	if(line>=0 && line<=7){
		writeDat(lineAddr[line],(uint8_t)0xff);	
	}
}

void TM1638::clearLine(uint8_t line)
{
	if(line>=0 && line<=7){
		writeDat(lineAddr[line], (uint8_t)0x0);	
	}
}

void TM1638::setLine(uint8_t line, uint8_t lineDat)
{
	if(line>=0 && line<=7){
	
		writeDat(lineAddr[line], lineDat);	
	}
}

void TM1638::displayColume(uint8_t colume)
{
	if(colume<8){
		for(int line=0; line < 8; line++){
			matrixDat[line] |= ~bitMask[colume];
		}
		displayMatrixDat();
	}	
}

void TM1638::clearColume(uint8_t colume)
{
	if(colume<8){
		for(int line=0; line < 8; line++){
			matrixDat[line] &= bitMask[colume];
		}
		displayMatrixDat();
	}
}

void TM1638::setColume(uint8_t colume, uint8_t columeDat)
{
	uint8_t bit = 0x80;
	if(colume<8){
		for(int line=0; line < 8; line++){
			if((columeDat&bit) == 0){
				matrixDat[line] &= bitMask[colume];
			}else{
				matrixDat[line] |= ~bitMask[colume];
			}
			bit >>= 1;
		}
		displayMatrixDat();
	}		
}

/*
uint8_t TM1638::exchangeBits(uint8_t dat)
{
	uint8 tempDat = 0;
	uint8 count = 0;
	for(int i = 7; i >= 1;){
		tempDat |= (dat<<i)&(0x80>>count);
		tempDat |= (dat>>i)&(0x01<<count++);
		i -= 2;
	}
}
*/