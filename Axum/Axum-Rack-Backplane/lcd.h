#ifndef LcdH
#define LcdH

#include <delay.h>

#define LCD_DELAY1 10       //10us
#define LCD_DELAY2 100      //100us
#define LCD_DELAY3 10       //4.1ms
#define LCD_DELAY4 10       //10ms Max Delay after Enable Low

void WaitLCDBusy()
{
   int cntTimeOut;
   
   LCD_D7_nBF = 0;
	delay_us(LCD_DELAY2);	
	cntTimeOut = LCD_DELAY4;
   while ((cntTimeOut) && (LCD_BF))
   {
	   delay_ms(1);   
	   cntTimeOut--;
   }
   LCD_D7_nBF = 1;
}

void SetupLCD()
{
   LCD_D7_nBF = 1;
              
	delay_us(LCD_DELAY2);	
	E_LCD = 0;
	delay_us(LCD_DELAY2);	
	
	// Setup/Reset Display
	RS_LCD = 0;
	RW_LCD = 0;
	D7LCD = 0;
	D6LCD = 0;
	D5LCD = 1;
	D4LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 0;
	delay_us(LCD_DELAY1);	
	// wait minimal 4.1 ms
	delay_ms(LCD_DELAY3);

	// Setup/Reset Display
	RS_LCD = 0;
	RW_LCD = 0;
	D7LCD = 0;
	D6LCD = 0;
	D5LCD = 1;
	D4LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 0;
	delay_us(LCD_DELAY2);	
	// wait minimal 100 us
	delay_ms(LCD_DELAY3);

	// Setup/Reset Display
	RS_LCD = 0;
	RW_LCD = 0;
	D7LCD = 0;
	D6LCD = 0;
	D5LCD = 1;
	D4LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 0;
	delay_us(LCD_DELAY2);	

	// Busy cannot be checked
	delay_ms(LCD_DELAY3);

	// Setup/Reset Display to 4 bit mode
	RS_LCD = 0;
	RW_LCD = 0;
	D7LCD = 0;
	D6LCD = 0;
	D5LCD = 1;
	D4LCD = 0;
	delay_us(LCD_DELAY2);	
	E_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 0;

   //from now -> timeout after every E_LCD = 0  
   WaitLCDBusy();
   
	// Set number of lines etc...
	RS_LCD = 0;
	RW_LCD = 0;
	D7LCD = 0;		// Function set
	D6LCD = 0;		// Function set
	D5LCD = 1;		// Function set
	D4LCD = 0;		// 4 bit
	delay_us(LCD_DELAY2);	
	E_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 0;
   //timeout after E_LCD = 0 for processing
   WaitLCDBusy();

	RS_LCD = 0;
	RW_LCD = 0;
	D7LCD = 1;		// 2 lines
	D6LCD = 0;		// 5x7 dots chars
	D5LCD = 0;		// *
	D4LCD = 0;		// *
	delay_us(LCD_DELAY2);	
	E_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 0;
   //timeout after E_LCD = 0 for processing
   WaitLCDBusy();

	D7LCD = 1;
	RS_LCD = 0;
	RW_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 0;
   //timeout after E_LCD = 0 for processing
   WaitLCDBusy();

	// Display Off
	RS_LCD = 0;
	RW_LCD = 0;
	D7LCD = 0;		// Function set
	D6LCD = 0;		// Function set
	D5LCD = 0;		// Function set
	D4LCD = 0;		
	delay_us(LCD_DELAY2);	
	E_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 0;
   //timeout after E_LCD = 0 for processing
   WaitLCDBusy();

	RS_LCD = 0;
	RW_LCD = 0;
	D7LCD = 1;		// Display off
	D6LCD = 1;		
	D5LCD = 0;	 	// Cursor on
	D4LCD = 0;	 	// Cursor Blink
	delay_us(LCD_DELAY2);	
	E_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 0;
   //timeout after E_LCD = 0 for processing
   WaitLCDBusy();

	D7LCD = 1;
	RS_LCD = 0;
	RW_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 0;
   //timeout after E_LCD = 0 for processing
   WaitLCDBusy();

	// Display Clear
	RS_LCD = 0;
	RW_LCD = 0;
	D7LCD = 0;		// Function set
	D6LCD = 0;		// Function set
	D5LCD = 0;		// Function set
	D4LCD = 0;		
	delay_us(LCD_DELAY2);	
	E_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 0;
   //timeout after E_LCD = 0 for processing
   WaitLCDBusy();

	RS_LCD = 0;
	RW_LCD = 0;
	D7LCD = 0;		
	D6LCD = 0;		
	D5LCD = 0;	 
	D4LCD = 1;		
	delay_us(LCD_DELAY2);	
	E_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 0;
   //timeout after E_LCD = 0 for processing
   WaitLCDBusy();

	D7LCD = 1;
	RS_LCD = 0;
	RW_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 0;

   //timeout after E_LCD = 0 for processing
   WaitLCDBusy();

	// Entry mode
	RS_LCD = 0;
	RW_LCD = 0;
	D7LCD = 0;
	D6LCD = 0;
	D5LCD = 0;
	D4LCD = 0;		
	delay_us(LCD_DELAY2);	
	E_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 0;
   //timeout after E_LCD = 0 for processing
   WaitLCDBusy();

	RS_LCD = 0;
	RW_LCD = 0;
	D7LCD = 0;		
	D6LCD = 1;
	D5LCD = 1;		// Position increment after char
	D4LCD = 0;		// No shift
	delay_us(LCD_DELAY2);	
	E_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 0;
   //timeout after E_LCD = 0 for processing
   WaitLCDBusy();

	D7LCD = 1;
	RS_LCD = 0;
	RW_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 0;
   //timeout after E_LCD = 0 for processing
   WaitLCDBusy();

/***********/
	// Display on
	RS_LCD = 0;
	RW_LCD = 0;
	D7LCD = 0;
	D6LCD = 0;
	D5LCD = 0;
	D4LCD = 0;		
	delay_us(LCD_DELAY2);	
	E_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 0;
   //timeout after E_LCD = 0 for processing
   WaitLCDBusy();

	RS_LCD = 0;
	RW_LCD = 0;
	D7LCD = 1;		
	D6LCD = 1;
	D5LCD = 0;
	D4LCD = 0; 
	delay_us(LCD_DELAY2);	
	E_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 0;
   //timeout after E_LCD = 0 for processing
   WaitLCDBusy();

	D7LCD = 1;
	RS_LCD = 0;
	RW_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 1;
	delay_us(LCD_DELAY2);	
	E_LCD = 0;
   //timeout after E_LCD = 0 for processing
   WaitLCDBusy();
}

/****************************************
* place data on LCD	RS = 0:	Instruction *
*					RS = 1:	Data        *
****************************************/
void SetLCD(char RS, char *Buffer)
{
	unsigned char cntBuffer;

	cntBuffer = 0;
	
	delay_us(LCD_DELAY1);	
	E_LCD = 0;
	delay_us(LCD_DELAY1);	

	while (Buffer[cntBuffer] != 0)
	{
		// Entry mode
		delay_us(LCD_DELAY1);	
		E_LCD = 1;
		delay_us(LCD_DELAY1);	
		RS_LCD = RS;
		RW_LCD = 0;
		D7LCD = (unsigned char)Buffer[cntBuffer]&0x80;
		D6LCD = (unsigned char)Buffer[cntBuffer]&0x40;
		D5LCD = (unsigned char)Buffer[cntBuffer]&0x20;
		D4LCD = (unsigned char)Buffer[cntBuffer]&0x10;		
		delay_us(LCD_DELAY1);	
		E_LCD = 0;
		delay_us(LCD_DELAY1);	

		D7LCD = 1;
		RS_LCD = 0;
		RW_LCD = 1;
		delay_us(LCD_DELAY1);	
		E_LCD = 1;
		delay_us(LCD_DELAY1);	
		E_LCD = 0;

	 	delay_us(LCD_DELAY2);

		E_LCD = 1;
		delay_us(LCD_DELAY1);	
		RS_LCD = RS;
		RW_LCD = 0;
		D7LCD = (unsigned char)Buffer[cntBuffer]&0x08;
		D6LCD = (unsigned char)Buffer[cntBuffer]&0x04;
		D5LCD = (unsigned char)Buffer[cntBuffer]&0x02;
		D4LCD = (unsigned char)Buffer[cntBuffer]&0x01;
		delay_us(LCD_DELAY1);	
		E_LCD = 0;
		delay_us(LCD_DELAY1);	

		D7LCD = 1;
		RS_LCD = 0;
		RW_LCD = 1;
		delay_us(LCD_DELAY1);	
		E_LCD = 1;
		delay_us(LCD_DELAY1);	
		E_LCD = 0;

	 	delay_us(100);
	 		 		
		cntBuffer++;
	}
}

void SetLCDModule(unsigned char Module, unsigned char LineNr, char *Buffer)
{
	char Position[2];
	Position[0] = 0x80;
	Position[1] = 0;

	if (LineNr&0x01)
		Position[0] = 0xC0;

	Position[0] += (Module&0x03)*10;

	SetLCD(0, Position);
	SetLCD(1, Buffer);
}                    


#endif