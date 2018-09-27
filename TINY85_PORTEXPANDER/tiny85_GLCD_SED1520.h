

#ifndef TINY85_GLCD_SED1520
#define TINY85_GLCD_SED1520

	#define SED1820_DATA_PORT	PX_GPIOB
	#define SED1820_DATA_DDR	PX_IODIRB	
	
	#define SED1820_CTRL_PORT	PX_GPIOA
	#define SED1820_CTRL_DDR	PX_IODIRA	
	
	#define SED1820_WR			1
	#define SED1820_E			2
	#define SED1820_nCS1		3
	#define SED1820_nCS2		4
	#define SED1820_A0			5
	
	
	
	#define SED1820_DISPLAY_ON		0xAF
	#define SED1820_DISPLAY_OFF		0xAE
	#define SED1820_RESET			0xE2
	
	void init_SED1820(void);
	void SED1820_writeData(unsigned char data);
	void SED1820_writeCommand(unsigned char command);
	
	


#endif /* TINY85_GLCD_SED1520 */