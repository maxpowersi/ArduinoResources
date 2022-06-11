
/*
	www.makerstudio.cc
*/
#include "TM1650.h"
#include <Arduino.h>
static int8_t TubeTab[] = {
						   0x00,0xC0,0xf9,0xa4,
						   0xb0,0x99,0x92,0x82,
                           0xf8,0x80,0x90,0x88,
                           0x83,0xa7,0xa1,0x86,
                           0x8e,0x7f
						   };//0~9,A,B,C,D,E,F    
				   
						   
static int8_t Cmd_Addr[] = {0x68,0x6A,0x6C,0x6E};//LED address

TM1650::TM1650(uint8_t Data, uint8_t Clk)
{
  Clkpin = Clk;
  Datapin = Data;
  pinMode(Clkpin,OUTPUT);
  pinMode(Datapin,OUTPUT);
}

void TM1650::init(void)
{
  clearDisplay();
}

void TM1650::writeByte(int8_t wr_data)
{
  uint8_t i,count1;   
  for(i=0;i<8;i++)        //sent 8bit data
  {
    digitalWrite(Clkpin,LOW);      
    if(wr_data & 0x80)digitalWrite(Datapin,HIGH);//MSB first
    else digitalWrite(Datapin,LOW);
    wr_data <<= 1;      
	//delayMicroseconds(50);
    digitalWrite(Clkpin,HIGH);
    //delayMicroseconds(50);  
  }  
  digitalWrite(Clkpin,LOW); 
  pinMode(Datapin,INPUT);
  
  while(digitalRead(Datapin)); //wait for the ACK    
  
  digitalWrite(Clkpin,HIGH);
  
  pinMode(Datapin,OUTPUT);
  
  
}

uint8_t TM1650::readByte()//read 8bit from to TM1650
{
  uint8_t rd_data=0;
  
  uint8_t i,count1;   
  uint8_t temp = 0x80;
  
  pinMode(Datapin,INPUT);
  digitalWrite(Clkpin,LOW);
  
  for(i=0;i<8;i++)        //read 8bit data
  {
    digitalWrite(Clkpin,HIGH);
	
    if(digitalRead(Datapin))//MSB first
	{
		rd_data |= temp;      
    }
    temp >>=1;
    digitalWrite(Clkpin,LOW);
	
  }  
  
  digitalWrite(Clkpin,LOW); //wait for the ACK
  pinMode(Datapin,INPUT);
  
  //while(digitalRead(Datapin))    
  { 
    /*count1 +=1;
    if(count1 == 200)//
    {
     pinMode(Datapin,OUTPUT);
     digitalWrite(Datapin,LOW);
     count1 =0;
    }
    pinMode(Datapin,INPUT);*/
  }
  digitalWrite(Clkpin,HIGH);
  
  //pinMode(Datapin,OUTPUT);
  
  return rd_data;
}

uint8_t TM1650::readKey()//read and output key value 
{
	uint8_t keyCode = 0;
	
	start();
	writeByte(READ_KEY_CMD);
	keyCode = readByte();
	stop();
	return keyCode;
	
}

//send start signal to TM1650
void TM1650::start(void)
{
  pinMode(Datapin,OUTPUT);
  digitalWrite(Clkpin,HIGH);//send start signal to TM1650
  
  digitalWrite(Datapin,HIGH); 
  
  digitalWrite(Datapin,LOW); 
  
  digitalWrite(Clkpin,LOW); 
  
} 

//End of transmission
void TM1650::stop(void)
{
  pinMode(Datapin,OUTPUT);
  digitalWrite(Clkpin,LOW);
  digitalWrite(Datapin,LOW);
  digitalWrite(Clkpin,HIGH);
  
  digitalWrite(Datapin,HIGH); 
  
}
//display function.Write to full-screen.
void TM1650::display(int8_t DispData[])
{
  int8_t SegData[4];
  uint8_t i;
  for(i = 0;i < 4;i ++)
  {
    SegData[i] = DispData[i];
  }
  coding(SegData);
  start();          //start signal sent to TM1650 from MCU
  writeByte(MODE_CMD);//write command for display
  writeByte(BRIGHT_DARKEST);//set light grade and open display
  for(i=0;i < 4;i ++){
	stop();           //
	start();          //
	writeByte(Cmd_Addr[i]);//
    writeByte(SegData[i]);        //
	stop();           //
	start();          //
  }
}
//******************************************
void TM1650::display(uint8_t BitAddr,int8_t DispData)
{

  int8_t ledDat = coding(DispData);
  start();          //start signal sent to TM1650 from MCU
  writeByte(MODE_CMD);//write command for display
  writeByte(BRIGHT_DARKEST);//set light grade and open display
	
	stop();           //
	start();          //
	writeByte(Cmd_Addr[BitAddr]);//
    writeByte(ledDat); //
	stop();           //
	start();          //
	
}

void TM1650::clearDisplay(void)
{
  display(0x00,0x7f);
  display(0x01,0x7f);
  display(0x02,0x7f);
  display(0x03,0x7f);  
}
//To take effect the next time it displays.
void TM1650::set(uint8_t brightness,uint8_t SetData,uint8_t SetAddr)
{
  Cmd_SetData = SetData;
  Cmd_SetAddr = SetAddr;
  Cmd_DispCtrl = 0x88 + brightness;//Set the brightness and it takes effect the next time it displays.
}

//Whether to light the clock point ":".
//To take effect the next time it displays.
void TM1650::point(boolean PointFlag)
{
  _PointFlag = PointFlag;
}
void TM1650::coding(int8_t DispData[])
{
  uint8_t PointData;
  if(_PointFlag == POINT_ON)PointData = 0x80;
  else PointData = 0; 
  for(uint8_t i = 0;i < 4;i ++)
  {
    if(DispData[i] == 0x7f)DispData[i] = 0x00;
    else DispData[i] = TubeTab[DispData[i]] + PointData;
  }
}
int8_t TM1650::coding(int8_t DispData)
{
  uint8_t PointData;
  if(_PointFlag == POINT_ON)PointData = 0x80;
  else PointData = 0; 
  if(DispData == 0x7f) DispData = 0x00 + PointData;//The bit digital tube off
  else DispData = TubeTab[DispData] + PointData;
  return DispData;
}


