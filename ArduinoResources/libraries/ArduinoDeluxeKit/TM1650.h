
/*
	www.makerstudio.cc
*/

#ifndef TM1650_h
#define TM1650_h
#include <inttypes.h>
#include <Arduino.h>
//************definitions for TM1650*********************
#define READ_KEY_CMD	0x49
#define MODE_CMD 		0x48

/**** definitions for the clock point of the digit tube *******/
#define POINT_ON   1
#define POINT_OFF  0
/**************definitions for brightness***********************/
#define  BRIGHT_DARKEST 0x01
#define  BRIGHT_TYPICAL 0x21
//#define  BRIGHTEST      7

class TM1650
{
  public:
    uint8_t Cmd_SetData;
    uint8_t Cmd_SetAddr;
    uint8_t Cmd_DispCtrl;
    boolean _PointFlag;     //_PointFlag=1:the clock point on
    TM1650(uint8_t, uint8_t);
    void init(void);        //To clear the display
    void writeByte(int8_t wr_data);//write 8bit data to TM1650
	uint8_t readByte();//read 8bit from to TM1650
	uint8_t readKey();//read and output key value 
    
    void display(int8_t DispData[]);
    void display(uint8_t BitAddr,int8_t DispData);
    void clearDisplay(void);
    void set(uint8_t = BRIGHT_TYPICAL,uint8_t = 0x40,uint8_t = 0xc0);//To take effect the next time it displays.
    void point(boolean PointFlag);//whether to light the clock point ":".To take effect the next time it displays.
    void coding(int8_t DispData[]); 
    int8_t coding(int8_t DispData);
	int8_t keycoding(int8_t keyCode);
  private:
    uint8_t Clkpin;
    uint8_t Datapin;
	
	void start(void);//send start bits
    void stop(void); //send stop bits
	void tempDelay();
	
};
#endif
