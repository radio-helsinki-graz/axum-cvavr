/*****************************************************
This program was produced by the
CodeWizardAVR V1.25.3 Standard
Automatic Program Generator
© Copyright 1998-2007 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Axum-UI-CRMP
Version :
Date    : 3-10-2007
Author  : Anton Prins
Company : DR Electronica Weesp b.v.
Comments:


Chip type           : AT90CAN32
Program type        : Application
Clock frequency     : 16,000000 MHz
Memory model        : Small
External SRAM size  : 0
Data Stack size     : 512
*****************************************************/

#include <90can32.h>
#include <stdio.h>
#include <delay.h>
#include <math.h>
#include <stdlib.h>

// I2C Bus functions
//#asm
//   .equ __i2c_port=0x08
//   .equ __sda_bit=2
//   .equ __scl_bit=3
//#endasm
//#include <i2c.h>

#include "Axum-UI-CRMP.h"
#include "CANTransportLayer.h"
#include "Axum-UI-CRMP-MambaNet.h"

/**********************************/
// Timer 0 output compare interrupt service routine
interrupt [TIM0_COMP] void timer0_comp_isr(void)
{
   //every 100 useconds a pulse.
   cntTimer0++;
   if (cntTimer0 == 10)
   {  //1mS
      cntTimer0 = 0;
      cntMilliSecond++;
   }
}

#define FIRST_ADC_INPUT 0
#define LAST_ADC_INPUT 7
unsigned int adc_data[LAST_ADC_INPUT-FIRST_ADC_INPUT+1];
#define ADC_VREF_TYPE 0x00

// ADC interrupt service routine
// with auto input scanning
interrupt [ADC_INT] void adc_isr(void)
{
   static unsigned char input_index=0;
   // Read the AD conversion result
   adc_data[input_index]=ADCW;
   // Select next ADC input
   if (++input_index > (LAST_ADC_INPUT-FIRST_ADC_INPUT))
      input_index=0;
   ADMUX=(FIRST_ADC_INPUT | (ADC_VREF_TYPE & 0xff))+input_index;
   // Start the AD conversion
   ADCSRA|=0x40;
}

// Declare your global variables here

void main(void)
{
   char cntByte;

   // Declare your local variables here

   // Crystal Oscillator division factor: 1
   #pragma optsize-
   CLKPR=0x80;
   CLKPR=0x00;
   #ifdef _OPTIMIZE_SIZE_
   #pragma optsize+
   #endif

   // Input/Output Ports initialization
   // Port A initialization
   // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
   // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
   PORTA=0x00;
   DDRA=0x00;

   // Port B initialization
   // Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=In Func0=Out
   // State7=1 State6=1 State5=1 State4=1 State3=1 State2=1 State1=T State0=1
   PORTB=0xFD;
   DDRB=0xFD;

   // Port C initialization
   // Func7=In Func6=In Func5=In Func4=Out Func3=Out Func2=In Func1=Out Func0=In
   // State7=T State6=T State5=T State4=0 State3=1 State2=T State1=1 State0=T
   PORTC=0xEE;
   DDRC=0x1E;

   // Port D initialization
   // Func7=Out Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
   // State7=0 State6=T State5=T State4=T State3=T State2=T State1=T State0=T
   PORTD=0x80;
   DDRD=0x80;

   // Port E initialization
   // Func7=In Func6=In Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=In
   // State7=T State6=T State5=0 State4=0 State3=0 State2=0 State1=0 State0=T
   PORTE=0x20;
   DDRE=0x3E;

   // Port F initialization
   // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
   // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
   PORTF=0x00;
   DDRF=0x00;

   // Port G initialization
   // Func4=In Func3=In Func2=In Func1=In Func0=In
   // State4=T State3=T State2=T State1=T State0=T
   PORTG=0x04;
   DDRG=0x00;

   // Timer/Counter 0 initialization
   // Clock source: System Clock
   // Clock value: 1000,000 kHz
   // Mode: CTC top=OCR0
   // OC0 output: Disconnected
   TCCR0A=0x0A;
   TCNT0=0x00;
   OCR0A=((OSCILLATOR_FREQUENCY/8)*0.0001)-1; //((OSCILLATOR_FREQUENCY/8)*0.0001)-1 => 100uS

   // Timer/Counter 1 initialization
   // Clock source: System Clock
   // Clock value: Timer 1 Stopped
   // Mode: Normal top=FFFFh
   // OC1A output: Discon.
   // OC1B output: Discon.
   // OC1C output: Discon.
   // Noise Canceler: Off
   // Input Capture on Falling Edge
   // Timer 1 Overflow Interrupt: Off
   // Input Capture Interrupt: Off
   // Compare A Match Interrupt: Off
   // Compare B Match Interrupt: Off
   // Compare C Match Interrupt: Off
   TCCR1A=0x00;
   TCCR1B=0x00;
   TCNT1H=0x00;
   TCNT1L=0x00;
   ICR1H=0x00;
   ICR1L=0x00;
   OCR1AH=0x00;
   OCR1AL=0x00;
   OCR1BH=0x00;
   OCR1BL=0x00;
   OCR1CH=0x00;
   OCR1CL=0x00;

   // Timer/Counter 2 initialization
   // Clock source: System Clock
   // Clock value: Timer 2 Stopped
   // Mode: Normal top=FFh
   // OC2 output: Disconnected
   ASSR=0x00;
   TCCR2A=0x00;
   TCNT2=0x00;
   OCR2A=0x00;

   // Timer/Counter 3 initialization
   // Clock source: System Clock
   // Clock value: Timer 3 Stopped
   // Mode: Normal top=FFFFh
   // Noise Canceler: Off
   // Input Capture on Falling Edge
   // OC3A output: Discon.
   // OC3B output: Discon.
   // OC3C output: Discon.
   // Timer 3 Overflow Interrupt: Off
   // Input Capture Interrupt: Off
   // Compare A Match Interrupt: Off
   // Compare B Match Interrupt: Off
   // Compare C Match Interrupt: Off
   TCCR3A=0x00;
   TCCR3B=0x00;
   TCNT3H=0x00;
   TCNT3L=0x00;
   ICR3H=0x00;
   ICR3L=0x00;
   OCR3AH=0x00;
   OCR3AL=0x00;
   OCR3BH=0x00;
   OCR3BL=0x00;
   OCR3CH=0x00;
   OCR3CL=0x00;

   // External Interrupt(s) initialization
   // INT0: Off
   // INT1: Off
   // INT2: Off
   // INT3: Off
   // INT4: Off
   // INT5: Off
   // INT6: Off
   // INT7: Off
   EICRA=0x00;
   EICRB=0x00;
   EIMSK=0x00;

   // Timer/Counter 0 Interrupt(s) initialization
   TIMSK0=0x02;
   // Timer/Counter 1 Interrupt(s) initialization
   TIMSK1=0x00;
   // Timer/Counter 2 Interrupt(s) initialization
   TIMSK2=0x00;
   // Timer/Counter 3 Interrupt(s) initialization
   TIMSK3=0x00;

   // Analog Comparator initialization
   // Analog Comparator: Off
   // Analog Comparator Input Capture by Timer/Counter 1: Off
   ACSR=0x80;
   ADCSRB=0x00;

   // ADC initialization
   // ADC Clock frequency: 1000,000 kHz
   // ADC Voltage Reference: AVCC pin
   // Digital input buffers on ADC0: On, ADC1: On, ADC2: On, ADC3: On
   // ADC4: On, ADC5: On, ADC6: On, ADC7: On
   DIDR0=0x00;
   ADMUX=FIRST_ADC_INPUT | (ADC_VREF_TYPE & 0xff);
   ADCSRA=0xCC;

   HardwareMinorRevision = (((PINC>>4)&0xE) | ((PING>>2)&0x01))^0x0F;

   FPGAFirmwareMajorRevision = 0;
   FPGAFirmwareMinorRevision = 0;

   // CAN Controller initialization
   InitializeCAN();

   delay_ms(1000);   //else error?

   for (cntByte=0; cntByte<NR_OF_LEDS/8; cntByte++)
   {
      LogicLEDData[cntByte] = 0xFF;
   }
   SetLEDs();
	BLANK = 0;

   delay_ms(500);

   for (cntByte=0; cntByte<NR_OF_LEDS/8; cntByte++)
   {
      LogicLEDData[cntByte] = 0x00;
   }
   SetLEDs();
   
   for (cntByte=0; cntByte<64; cntByte++)
   {
      SwitchState[cntByte] = 0;      
   }

   PreviousEncoderABStatus = 0;

   TransmitCANMessageBufferLength = 0;
   cntTransmitCANMessageBuffer = 0;

   PreviousMilliSecond = 0;

   // Global enable interrupts
   #asm("sei")

   while (1)
   {
      unsigned char CurrentState_nSW_CC;
       
      // Place your code here
      ProcessCAN();

      if (cntMilliSecond - PreviousMilliSecondReservation > 1000)
      {
         PreviousMilliSecondReservation = cntMilliSecond;

         if (LocalCANAddress == 0x00000000)
         {
            SendCANReservationRequest();
         }
         else
         {
            SendMambaNetReservationInfo();
         }
      }

      if (cntMilliSecond - PreviousMilliSecond > 40)
      {  //Send track/relative information maximal 25 times per second.
         unsigned char cntTrack;

         if (PreviousEncoderPosition != EncoderPosition)
         {
            unsigned char TransmitBuffer[1];
            int Difference;
            Difference = EncoderPosition-PreviousEncoderPosition;

            TransmitBuffer[0] = Difference&0xFF;
            SendSensorChangeToMambaNet(1078, SIGNED_INTEGER_DATATYPE, 1, TransmitBuffer);

            PreviousEncoderPosition = EncoderPosition;
         }

         for (cntTrack=0; cntTrack<4; cntTrack++)
         {
            if (PreviousTrackPosition[cntTrack] != TrackPosition[cntTrack])
            {
               unsigned char TransmitBuffer[2];
               unsigned int ObjectNr;

               ObjectNr = 1081+cntTrack;

               TransmitBuffer[0] = (TrackPosition[cntTrack]>>8)&0xFF;
               TransmitBuffer[1] = TrackPosition[cntTrack]&0xFF;

               SendSensorChangeToMambaNet(ObjectNr, UNSIGNED_INTEGER_DATATYPE, 2, TransmitBuffer);

               PreviousTrackPosition[cntTrack] = TrackPosition[cntTrack];
            }
         }


         PreviousMilliSecond = cntMilliSecond;
      }

      ReadEncoders();
      ReadSwitches();

      //TrackData[0] = 0x03FF;
      ReadTracks();
      
      //read chipcard switch
      CurrentState_nSW_CC = nSW_CC;
      if (PreviousState_nSW_CC != CurrentState_nSW_CC)
      {        
         if (cntChipcardSwitchDelay<10)
         {         
            cntChipcardSwitchDelay++;
         }
         else if (cntChipcardSwitchDelay == 10)
         {
            unsigned char TransmitBuffer[1] = {0};
            unsigned int ObjectNr = 1086;

            PreviousState_nSW_CC = CurrentState_nSW_CC;
            SmartCardInserted = 0;
            if (CurrentState_nSW_CC == 0)
            {
               if (CheckForValidSmartCard(0xA0, 0x00))
		         {
   			      SmartCardInserted = 1;
   	            
   		         //Power-On, Reset and not Selected
   					RST_CC = 1;
   					nCS_CC = 1; 
   		
   		         //Out-Reset
   					RST_CC = 0;
   		
   		         //Select
   					nCS_CC = 0; 
   		
   		         //Do I2C
   		         I2CRead(0xA0, 0x0000, ChipCardData, 48);
   		
   		         //Deselect
   					nCS_CC = 1; 													
               }
            }
            TransmitBuffer[0] = SmartCardInserted;            
            SendSensorChangeToMambaNet(ObjectNr, STATE_DATATYPE, 1, TransmitBuffer);
            
            cntChipcardSwitchDelay = 100;
         }
      }
      else
      {
         cntChipcardSwitchDelay = 0; 
      }
   }
}

void SetTLC5921DAP()
{
	unsigned char cntBit;
	unsigned char cntByte;

	for (cntByte=NR_OF_LEDS/8; cntByte<=NR_OF_LEDS/8; cntByte--)
	{
		for (cntBit=7; cntBit<=7; cntBit--)
		{
			SIN = TLC5921DAPData[cntByte]&(0x01<<cntBit);
			SCLK = 1;
			SCLK = 0;
		}
	}
	XLAT = 1;
	XLAT = 0;
}

void selectRow(unsigned char Row)
{
   nROW1 = 1;
   nROW2 = 1;
   nROW3 = 1;
   nROW4 = 1;
   nROW5 = 1;
   nROW6 = 1;
   nROW7 = 1;

   switch (Row)
   {
      case 0:
      {
         nROW1 = 0;
      }
      break;
      case 1:
      {
         nROW2 = 0;
      }
      break;
      case 2:
      {
         nROW3 = 0;
      }
      break;
      case 3:
      {
         nROW4 = 0;
      }
      break;
      case 4:
      {
         nROW5 = 0;
      }
      break;
      case 5:
      {
         nROW6 = 0;
      }
      break;
      case 6:
      {
         nROW7 = 0;
      }
      break;
   }
}

char SwitchCheck(unsigned char cntRow, unsigned char SwitchNr, char SwitchReturn)
{
	char ReturnValue;
	ReturnValue = 0;

	if (SwitchReturn)
	{
		if (SwitchData[cntRow][SwitchNr] != SWITCHDELAY)
		{
			SwitchData[cntRow][SwitchNr]++;
			if (SwitchData[cntRow][SwitchNr]==SWITCHDELAY)
			{  //Unpressed
				ReturnValue = -1;
			}
		}
	}
	else
	{
		if (SwitchData[cntRow][SwitchNr])
		{
			SwitchData[cntRow][SwitchNr]--;
			if (SwitchData[cntRow][SwitchNr]==0)
			{  //Pressed
				ReturnValue = 1;
			}
		}
	}
	return ReturnValue;
}

void ReadSwitches()
{
   char cntRow;

   //Switch Rows
   for (cntRow=0; cntRow<7; cntRow++)
   {
      char ReturnValue;
      unsigned char LogicSwitchNr;

      selectRow(cntRow);

		ReturnValue = SwitchCheck(cntRow, 0, nSW1);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[(cntRow*8)+0];
      DoSwitch(LogicSwitchNr, ReturnValue);

		ReturnValue = SwitchCheck(cntRow, 1, nSW2);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[(cntRow*8)+1];
      DoSwitch(LogicSwitchNr, ReturnValue);

		ReturnValue = SwitchCheck(cntRow, 2, nSW3);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[(cntRow*8)+2];
      DoSwitch(LogicSwitchNr, ReturnValue);

		ReturnValue = SwitchCheck(cntRow, 3, nSW4);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[(cntRow*8)+3];
      DoSwitch(LogicSwitchNr, ReturnValue);

		ReturnValue = SwitchCheck(cntRow, 4, nSW5);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[(cntRow*8)+4];
      DoSwitch(LogicSwitchNr, ReturnValue);

		ReturnValue = SwitchCheck(cntRow, 5, nSW6);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[(cntRow*8)+5];
      DoSwitch(LogicSwitchNr, ReturnValue);

		ReturnValue = SwitchCheck(cntRow, 6, nSW7);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[(cntRow*8)+6];
      DoSwitch(LogicSwitchNr, ReturnValue);

		ReturnValue = SwitchCheck(cntRow, 7, nSW8);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[(cntRow*8)+7];
      DoSwitch(LogicSwitchNr, ReturnValue);
   }
}

void ReadEncoders()
{
   unsigned char EncoderABStatusChanged;

	//Check Encoder
	EncoderABStatus = (PING>>3)&0x03;

   EncoderABStatusChanged = PreviousEncoderABStatus^EncoderABStatus;
   PreviousEncoderABStatus = EncoderABStatus;

      if (EncoderABStatusChanged&0x02)
      { 	//Pulse Change
      	if ((EncoderABStatus&0x01) != ((EncoderABStatus>>1)&0x01))
      	{  //Up
      	   unsigned int Difference;

      	   Difference = cntMilliSecond - EncoderPreviousUpTime;

            EncoderPreviousUpTime = cntMilliSecond;

            if (Difference < 50)
            {
               	EncoderPosition+=5;
            }
            else if (Difference < 100)
            {
               	EncoderPosition+=2;
            }
            else
            {
               	EncoderPosition++;
            }

      	}
      	else
      	{  //Down
         	unsigned int Difference;

         	Difference = cntMilliSecond-EncoderPreviousDownTime;
            EncoderPreviousDownTime = cntMilliSecond;

            if (Difference < 50)
            {
            	EncoderPosition-=5;
            }
            else if (Difference < 100)
            {
            	EncoderPosition-=2;
            }
            else
            {
            	EncoderPosition--;
            }
      	}
      }
}

void ReadTracks()
{
   int Difference;
	unsigned char cntTrack;

	for (cntTrack=0; cntTrack<8; cntTrack++)
	{
      switch (cntTrack)
      {
         case 0:
         case 2:
         case 4:
         case 6:
         {
            Difference = PreviousADC_Data[cntTrack]-adc_data[cntTrack];
                
            if (abs(Difference)>TRACK_WIBBLE)
            {
               char TrackNr;
            
               TrackNr = cntTrack>>1;
               if (TrackNr == 1)
               {
                  TrackNr = 2;
               }
               else if (TrackNr == 2)
               {
                  TrackNr = 1;
               }

               TrackPosition[TrackNr] = adc_data[cntTrack];
                  
               PreviousADC_Data[cntTrack] = adc_data[cntTrack];              
            }
         }
         break;
		}
	}
}

void DoSwitch(unsigned char LogicSwitchNr, int Event)
{
   if ((Event == 1) || (Event == -1))
   {
      unsigned char TransmitBuffer[1];
      unsigned int ObjectNr;
      char SwitchNr;

      SwitchNr = LogicSwitchNr;
      if (SwitchNr == 22)
      {   //EncoderSwitch
         SwitchNr = 55;
      }
      else if (SwitchNr == 23)
      {   //Jumper
         SwitchNr = 61;
      }
      else if (SwitchNr >= 24)
      {   //Other switches
         SwitchNr -= 2;
      }
      
      ObjectNr = 1024+SwitchNr;

      TransmitBuffer[0] = 0;
      if (Event == 1)
      {
         TransmitBuffer[0] = 1;
      }

      SwitchState[SwitchNr] = TransmitBuffer[0];

      SendSensorChangeToMambaNet(ObjectNr, STATE_DATATYPE, 1, TransmitBuffer);
    }
}

void SetLEDs()
{
   unsigned char cntLogicLED;
   unsigned char LEDNr;
   unsigned char LogicLEDMask;
   unsigned char LogicLEDByteNr;
   unsigned char LEDMask;
   unsigned char LEDByteNr;

   for (cntLogicLED=0; cntLogicLED<NR_OF_LEDS; cntLogicLED++)
   {
      LEDNr = LogicLEDNr2LEDNr[cntLogicLED];

      LogicLEDMask = 0x01<<(cntLogicLED&0x07);
      LogicLEDByteNr = cntLogicLED>>3;

      LEDMask = 0x01<<(LEDNr&0x07);
      LEDByteNr = LEDNr>>3;

      if (LogicLEDData[LogicLEDByteNr]&LogicLEDMask)
      {
         TLC5921DAPData[LEDByteNr] |= LEDMask;
      }
      else
      {
         TLC5921DAPData[LEDByteNr] &= LEDMask^0xFF;
      }
   }
   SetTLC5921DAP();
}

void ProcessMambaNetMessageFromCAN_Imp(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength)
{
   unsigned char MessageDone;
   
   MessageDone = 0;
   

   if (MessageID)
   {
      Ack = 1;
   }
   
   switch (MessageType)
   {
      //MessageType = 0, handled in the stack
      case 1:
      {  //Object message
         unsigned int ObjectNr;
         unsigned char ObjectMessageAction;

         ObjectNr = ((unsigned int)Data[0]<<8) | Data[1];
         ObjectMessageAction = Data[2];

         switch (ObjectMessageAction)
         {
            //MAMBANET_OBJECT_ACTION_GET_INFORMATION, handled in the stack
            case  MAMBANET_OBJECT_ACTION_GET_SENSOR_DATA:
            {
               // if (ObjectNr<1024) is handled in the stack
               unsigned char TransmitBuffer[64];

               TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
               TransmitBuffer[1] = ObjectNr&0xFF;
               TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                   
               if ((ObjectNr>=1024) && (ObjectNr<1078))
               {  //Switches
                  char LogicSwitchNr = ObjectNr-1024;
                  
                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = SwitchState[LogicSwitchNr];
                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);
               
                  MessageDone = 1;
               }
               if ((ObjectNr>=1078) && (ObjectNr<1079))
               {  //Encoder
                  TransmitBuffer[3] = SIGNED_INTEGER_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = 0;
                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);
               
                  MessageDone = 1;
               }
               else if ((ObjectNr>=1079) && (ObjectNr<1080))
               {  //Encoder switch
                  char LogicSwitchNr = ObjectNr-1024;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = SwitchState[LogicSwitchNr];
                  
                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);
               
                  MessageDone = 1;
               }
               else if ((ObjectNr>=1081) && (ObjectNr<1085))
               {  //Potmeter
                  char PotmeterNr = ObjectNr-1081;

                  TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                  TransmitBuffer[4] = 2;
                  TransmitBuffer[5] = (TrackPosition[PotmeterNr]>>8)&0xFF;
                  TransmitBuffer[6] = TrackPosition[PotmeterNr]&0xFF;
                  
                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 7);
               
                  MessageDone = 1;
               }
               else if ((ObjectNr>=1085) && (ObjectNr<1086))
               {  //Jumper
                  char LogicSwitchNr = ObjectNr-1024;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = SwitchState[LogicSwitchNr];
                  
                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);
               
                  MessageDone = 1;
               }
               else if ((ObjectNr>=1086) && (ObjectNr<1087))
               {  //Chipcard switch switch
                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = SmartCardInserted;
                  
                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);
               
                  MessageDone = 1;
               }
               else if ((ObjectNr == 1087) || (ObjectNr == 1088))
               {
                  char cntByte;

                  TransmitBuffer[3] = OCTET_STRING_DATATYPE;
                  if (ObjectNr == 1087)
                  {
                     TransmitBuffer[4] = 32;
                     for (cntByte=0; cntByte<32; cntByte++)
                     {
                        TransmitBuffer[5+cntByte] = ChipCardData[cntByte];
                     }                  
                     SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 37);
                  }
                  else
                  {
                     TransmitBuffer[4] = 16;
                     for (cntByte=0; cntByte<16; cntByte++)
                     {
                        TransmitBuffer[5+cntByte] = ChipCardData[32+cntByte];
                     }                  
                     SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 21);
                  }
               }

               if (!MessageDone)
               {
                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                  TransmitBuffer[3] = ERROR_DATATYPE;
                  TransmitBuffer[4] = 16;
                  TransmitBuffer[5] = 'N';
                  TransmitBuffer[6] = 'o';
                  TransmitBuffer[7] = ' ';
                  TransmitBuffer[8] = 's';
                  TransmitBuffer[9] = 'e';
                  TransmitBuffer[10] = 'n';
                  TransmitBuffer[11] = 's';
                  TransmitBuffer[12] = 'o';
                  TransmitBuffer[13] = 'r';
                  TransmitBuffer[14] = ' ';
                  TransmitBuffer[15] = 'o';
                  TransmitBuffer[16] = 'b';
                  TransmitBuffer[17] = 'j';
                  TransmitBuffer[18] = 'e';
                  TransmitBuffer[19] = 'c';
                  TransmitBuffer[20] = 't';

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 21);            
               }            
            }
            break;
            case  MAMBANET_OBJECT_ACTION_GET_ACTUATOR_DATA:
            {  
               unsigned char TransmitBuffer[64];

               TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
               TransmitBuffer[1] = ObjectNr&0xFF;
               TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE;

               if ((ObjectNr>=1024) && (ObjectNr<1078))
               {  //Switches with a single LED
                  char TemporySwitchNr;
                  char LEDNr;
                  char ByteNr;
                  char Mask;

                  TemporySwitchNr = ObjectNr-1024;

                  if (TemporySwitchNr<22)
                  {
                     LEDNr = TemporySwitchNr;
                  }
                  else
                  {
                     LEDNr = TemporySwitchNr+7;
                  }

                  ByteNr = LEDNr>>3;
                  Mask = 0x01<<(LEDNr&0x7);

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;

                  if (LogicLEDData[ByteNr] & Mask)
                  {
                     TransmitBuffer[5] = 1;
                  }  
                  else
                  {
                     TransmitBuffer[5] = 0;
                  }

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1080) && (ObjectNr<1081))
               {  //Control LED Bar                 
                  TransmitBuffer[3] = BIT_STRING_DATATYPE;
                  TransmitBuffer[4] = 1;
                  
                  TransmitBuffer[5] = (LogicLEDData[2]>>6)&0x03; 
                  TransmitBuffer[5] |= (LogicLEDData[3]<<2)&0x7C; 

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr == 1087) || (ObjectNr == 1088))
               {
                  char cntByte;

                  TransmitBuffer[3] = OCTET_STRING_DATATYPE;
                  if (ObjectNr == 1087)
                  {
                     TransmitBuffer[4] = 32;
                     for (cntByte=0; cntByte<32; cntByte++)
                     {
                        TransmitBuffer[5+cntByte] = WriteChipCardData[cntByte];
                     }                  
                     SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 37);
                  }
                  else
                  {
                     TransmitBuffer[4] = 16;
                     for (cntByte=0; cntByte<16; cntByte++)
                     {
                        TransmitBuffer[5+cntByte] = WriteChipCardData[32+cntByte];
                     }                  
                     SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 21);
                  }
                  MessageDone = 1;
               }
               
               if (!MessageDone)
               {
                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE;
                  TransmitBuffer[3] = ERROR_DATATYPE;
                  TransmitBuffer[4] = 18;
                  TransmitBuffer[5] = 'N';
                  TransmitBuffer[6] = 'o';
                  TransmitBuffer[7] = ' ';
                  TransmitBuffer[8] = 'a';
                  TransmitBuffer[9] = 'c';
                  TransmitBuffer[10] = 't';
                  TransmitBuffer[11] = 'u';
                  TransmitBuffer[12] = 'a';
                  TransmitBuffer[13] = 't';
                  TransmitBuffer[14] = 'o';
                  TransmitBuffer[15] = 'r';
                  TransmitBuffer[16] = ' ';
                  TransmitBuffer[17] = 'o';
                  TransmitBuffer[18] = 'b';
                  TransmitBuffer[19] = 'j';
                  TransmitBuffer[20] = 'e';
                  TransmitBuffer[21] = 'c';
                  TransmitBuffer[22] = 't';

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 23);
               }               
            }
            break;
            case  MAMBANET_OBJECT_ACTION_SET_ACTUATOR_DATA:
            {
               unsigned char DataType;
               unsigned char DataSize;
               unsigned char FormatError;
               
               FormatError = 1;

               DataType = Data[3];
               DataSize = Data[4];

               if ((ObjectNr>=1024) && (ObjectNr<1078))
               {  //Switches with a single LED
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        char TemporySwitchNr;
                        char LEDNr;
                        char ByteNr;
                        char Mask;

                        TemporySwitchNr = ObjectNr-1024;

                        if (TemporySwitchNr<22)
                        {
                           LEDNr = TemporySwitchNr;
                        }
                        else
                        {
                           LEDNr = TemporySwitchNr+7;
                        }

                        ByteNr = LEDNr>>3;
                        Mask = 0x01<<(LEDNr&0x7);

                        if (Data[5])
                        {
                           LogicLEDData[ByteNr] |= Mask;
                        }
                        else
                        {
                           LogicLEDData[ByteNr] &= Mask^0xFF;
                        }
                        SetLEDs();

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1080) && (ObjectNr<1081))
               {  //Control LED Bar
                  if (DataType == BIT_STRING_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        //LEDNr     22, 23, 24, 25, 26, 27, 28
                        LogicLEDData[2] &= 0x3F;
                        LogicLEDData[2] |= (Data[5]<<6)&0xC0;
                        LogicLEDData[3] &= 0xE0;
                        LogicLEDData[3] |= (Data[5]>>2)&0x1F;
                        SetLEDs();

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr == 1087) || (ObjectNr == 1088))
               {
                  if (DataType == OCTET_STRING_DATATYPE)
                  {
                     char cntByte;
                     
                     if (ObjectNr == 1087)
                     {
                        if (DataSize<=32)
                        {
                           for (cntByte=0; cntByte<DataSize; cntByte++)
                           {
                              WriteChipCardData[cntByte] = Data[5+cntByte];
                           }
                           FormatError = 0;
                        }                  
                     }
                     else
                     {
                        if (DataSize<=16)
                        {
                           for (cntByte=0; cntByte<DataSize; cntByte++)
                           {
                              WriteChipCardData[32+cntByte] = Data[5+cntByte];
                           }
                           FormatError = 0;
                        }
                     }
                     
                     //Select
   					   nCS_CC = 0; 
   		
   		            //Do I2C
                     SmartCardWrite(0xA0, 0x0000, WriteChipCardData, 48);
   		
   		            //Deselect
   					   nCS_CC = 1; 													                  

                     MessageDone = 1;
                  }
               }
               else
               {
                  FormatError = 0;
               }

               if (!MessageDone)
               {
                  unsigned char TransmitBuffer[23];
                  
                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE;
                  TransmitBuffer[3] = ERROR_DATATYPE;
                  if (FormatError)
                  {
                     TransmitBuffer[4] = 12;
                     sprintf(&TransmitBuffer[5], "Format error");
                  }
                  else
                  {
                     TransmitBuffer[4] = 18;
                     sprintf(&TransmitBuffer[5], "No actuator object");
                  }

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, TransmitBuffer[4]+5);
               }
               else
               {
                  if (MessageID)
                  {
                     unsigned char TransmitBuffer[16];
                  
                     TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                     TransmitBuffer[1] = ObjectNr&0xFF;
                     TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE;
                     TransmitBuffer[3] = NO_DATA_DATATYPE;

                     SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 4);
                  }
               }                 
            }
            break;
         }
      }
      break;
   }
}

//I2C section for chipcard
void SetSDA(unsigned char SDAData)
{
	DDRC |= 0x04;//SDA Out
	PORTC.2 = SDAData;
}

unsigned char GetSDA()
{
	PORTC.2 = 1; //Pull-up
	DDRC &= 0xFB;   
	return PINC.2;
}

void SetSCL(unsigned char SCLData)
{
	DDRC |= 0x08;//SCL Out
	PORTC.3 = SCLData;
	delay_us(10);
}

void I2CStartCondition()
{
   SetSDA(1);
   SetSCL(1);

   SetSDA(0);
   delay_ms(1);
   SetSCL(0);
}

void I2CStopCondition()
{
   SetSCL(0);
   SetSDA(0);

   SetSCL(1);
   delay_ms(1);
   SetSDA(1);
}

unsigned char I2CByteWrite(unsigned char Byte)
{
   int cntBit;
   int ACK;

   //Clock low to change data
   SetSCL(0);

   //Set Address+Read
   for (cntBit=0; cntBit<8; cntBit++)
   {
      if (Byte&(0x80>>cntBit))
         SetSDA(1);
      else
         SetSDA(0);

      SetSCL(1);
      SetSCL(0);
   }

   //for ACK
   GetSDA();
   SetSCL(1);
   ACK = GetSDA();
   SetSCL(0);

   return ACK;
}

unsigned char I2CByteRead()
{
   int cntBit;
   unsigned char Data = 0x00;

   //Clock low to change data
   SetSCL(0);
   GetSDA();

   //Set Address+Read
   for (cntBit=0; cntBit<8; cntBit++)
   {
      SetSCL(1);
      if (GetSDA())
         Data |= (0x80>>cntBit);
      SetSCL(0);
   }

   //for NO-ACK
   SetSDA(0);
   SetSCL(1);
   SetSCL(0);

   return Data;
}

void SmartCardWrite(unsigned char I2CAddress, unsigned int StartAddress, unsigned char *Buffer, unsigned char Length)
{  //Write per 16bytes pages...
   unsigned int cntPage;
   unsigned int PageAddress;
   unsigned int BufferIndex;
   int BufferLength;

   PageAddress = StartAddress;
   BufferIndex = 0;

   for (cntPage=0; cntPage<(Length/16); cntPage++)
   {
      BufferLength = Length-BufferIndex;
      if (BufferLength>16)
         BufferLength = 16;
  
      I2CWrite(I2CAddress, PageAddress, &Buffer[BufferIndex], BufferLength);

      PageAddress += 16;
      BufferIndex += 16;
   }
}

void I2CWrite(unsigned char I2CAddress, unsigned int StartAddress, unsigned char *Buffer, unsigned char Length)
{
   unsigned char Address;
   unsigned char cntByte;

   //I2CAddress + Write + AddressOffset
   Address = (I2CAddress | ((StartAddress>>7)&0x0E)) & 0xFE;

   I2CStartCondition();

   I2CByteWrite(Address);
   I2CByteWrite(StartAddress&0xFF);

   for (cntByte=0; cntByte<Length; cntByte++)
   {
      I2CByteWrite(Buffer[cntByte]);
   }

   I2CStopCondition();

   delay_ms(400);
}

void I2CRead(unsigned char I2CAddress, unsigned int StartAddress, unsigned char *Buffer, unsigned char Length)
{
   unsigned char Address;
   unsigned char cntByte;

   //Make Read + AddressOffset
	Address = I2CAddress | ((StartAddress>>7)&0x0E) & 0xFE;

   I2CStartCondition();

   I2CByteWrite(Address);
   I2CByteWrite(StartAddress&0xFF);

   I2CStopCondition();

   delay_ms(10);

   I2CStartCondition();

   I2CByteWrite(Address | 0x01);

   for (cntByte=0; cntByte<Length; cntByte++)
   {
      Buffer[cntByte] = I2CByteRead();
   }

   I2CStopCondition();
}

unsigned char CheckForValidSmartCard(unsigned char I2CAddress, unsigned int StartAddress)
{
   unsigned char Address;
   unsigned char NoError = 1;

    //Reset and not Selected  
	RST_CC = 1;
	nCS_CC = 1; 

	//Out-Reset
	RST_CC = 0;

	//Select
	nCS_CC = 0; 

	//Make Read + AddressOffset
	Address = I2CAddress | ((StartAddress>>7)&0x0E) & 0xFE;

	I2CStartCondition();

	if (I2CByteWrite(Address))
	{
		NoError = 0;
	}
	
	if (I2CByteWrite(StartAddress&0xFF))
	{
    	NoError = 0;
	}


   I2CStopCondition();

   delay_ms(10);

   //Deselect
	nCS_CC = 1; 

   return NoError;
}

void CanBussError()
{
   AddressValidated = 0;
   timerReservationInfo = 1;
}