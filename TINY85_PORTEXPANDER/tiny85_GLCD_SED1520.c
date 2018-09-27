
#include "tiny85_GLCD_SED1520.h"
#include "tiny85_software_SPI.h"
#define F_CPU 8000000ul
#include <util/delay.h>



void init_SED1820(void)
{
	PX_writeByte(SED1820_DATA_DDR,0x00);//PA7..PA0 output
	PX_writeByte(SED1820_CTRL_DDR,0x00);//PB7..PB0 output
	
	//set nCSx to 1
	PX_readSetWrite(SED1820_CTRL_PORT,(1<<SED1820_nCS1));
	PX_readSetWrite(SED1820_CTRL_PORT,(1<<SED1820_nCS2));
	//set E to 0
	PX_readClearWrite(SED1820_CTRL_PORT,SED1820_E);
	
	
	SED1820_writeCommand(SED1820_RESET);
	_delay_ms(50);
	SED1820_writeCommand(SED1820_DISPLAY_ON);
	_delay_ms(50);
	SED1820_writeCommand(0b11000000);//start line 0
	_delay_ms(50);
	
}

void SED1820_writeData(unsigned char data)
{
	//A0 set to 1
	PX_readSetWrite(SED1820_CTRL_PORT,(1<<SED1820_A0));
	//W/R set to 0
	PX_readClearWrite(SED1820_CTRL_PORT,(1<<SED1820_WR));
	//CS1 set to 0 (1-->0)  chip1 selected
	PX_readToggleWrite(SED1820_CTRL_PORT,(1<<SED1820_nCS1));
	_delay_us(10);

	//toggle E (0-->1)
	PX_readToggleWrite(SED1820_CTRL_PORT,(1<<SED1820_E));
	_delay_us(10);
	
	//output data
	PX_writeByte(SED1820_DATA_PORT,data);
	_delay_us(10);

	//toggle E (1-->0)
	PX_readToggleWrite(SED1820_CTRL_PORT,(1<<SED1820_E));
	//CS1 set to 1 (0-->1)  chip1 selected
	PX_readToggleWrite(SED1820_CTRL_PORT,(1<<SED1820_nCS1));
}

void SED1820_writeCommand(unsigned char command)
{
	
	//A0 set to 0
	PX_readClearWrite(SED1820_CTRL_PORT,(1<<SED1820_A0));
	//W/R set to 0
	PX_readClearWrite(SED1820_CTRL_PORT,(1<<SED1820_WR));
	//CS1 set to 0 (1-->0)  chip1 selected
	PX_readToggleWrite(SED1820_CTRL_PORT,(1<<SED1820_nCS1));
	_delay_us(10);

	//toggle E (0-->1)
	PX_readToggleWrite(SED1820_CTRL_PORT,(1<<SED1820_E));
	_delay_us(10);
	
	//output data
	PX_writeByte(SED1820_DATA_PORT,command);
	_delay_us(10);

	//toggle E (1-->0)
	PX_readToggleWrite(SED1820_CTRL_PORT,(1<<SED1820_E));
	//CS1 set to 1 (0-->1)  chip1 selected
	PX_readToggleWrite(SED1820_CTRL_PORT,(1<<SED1820_nCS1));

}