
/*
	www.makerstudio.cc
*/

#ifndef TM1638_h
#define TM1638_h
#include <inttypes.h>
#include <Arduino.h>

//************display mode for TM1638*********************
#define DISPALY_ON_MODE		0x8F
#define DISPALY_OFF_MODE	0x87

//************data command (address mode) for TM1638*********************
#define AUTO_ADDR	0x40
#define FIXED_ADDR	0x44

//************address command for TM1638*********************
#define GRID1_ADDR	0xC0
#define GRID2_ADDR	0xC2
#define GRID3_ADDR	0xC4
#define GRID4_ADDR	0xC6
#define GRID5_ADDR	0xC8
#define GRID6_ADDR	0xCA
#define GRID7_ADDR	0xCC
#define GRID8_ADDR	0xCE


class TM1638
{
  public:
    uint8_t Cmd_SetData;
    uint8_t Cmd_SetAddr;
    uint8_t Cmd_DispCtrl;
    TM1638(uint8_t, uint8_t, uint8_t);
    
	void clear();
    void displayAll();
	void displayPic(uint8_t picDat[8]);
    void setPoint(uint8_t line, uint8_t colume, uint8_t state);
    void displayLine(uint8_t line);
	void clearLine(uint8_t line);
	void setLine(uint8_t line, uint8_t lineDat);
	void displayColume(uint8_t colume);
	void clearColume(uint8_t colume);
	void setColume(uint8_t colume, uint8_t columeDat);
	
  private:
    uint8_t STB_pin;
    uint8_t CLK_pin;
    uint8_t DIO_pin;
	uint8_t matrixDat[8];
	
	void writeByte(uint8_t wr_data);//write 8bit data to TM1638
	void writeByteMSB(uint8_t wr_data);//write 8bit data to TM1638 with MSB
	void writeCmd(uint8_t cmd);
	void writeDat(uint8_t gridAddr, uint8_t wr_data);
	void displayMatrixDat();
	/*uint8_t exchangeBits(uint8_t dat);*/
};
#endif
