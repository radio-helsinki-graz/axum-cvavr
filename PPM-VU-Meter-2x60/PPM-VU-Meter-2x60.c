/*****************************************************
This program was produced by the
CodeWizardAVR V1.25.3 Standard
Automatic Program Generator
© Copyright 1998-2007 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Axum-Rack-Backplane
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

#include "PPM-VU-Meter-2x60.h"
#include "CANTransportLayer.h"
#include "PPM-VU-Meter-2x60-MambaNet.h"
#include "stdlib.h"

unsigned char cntDebug;

int NewLeftPos;
int NewRightPos;

unsigned char MambaNetLeftData[2];
unsigned char MambaNetRightData[2];

unsigned char LeftNrOfLEDs;
unsigned char RightNrOfLEDs;
unsigned char LeftHoldLEDNr;
unsigned char RightHoldLEDNr;     
unsigned char cntLeftHoldTime;
unsigned char cntRightHoldTime;

unsigned char cntBlock;
unsigned int LEDDataLeft[4];
unsigned int LEDDataRight[4];


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

      //SetTLC5920(cntBlock++&0x03);     
   }
}

/**********************************/
// Timer 3 output compare interrupt service routine
interrupt [TIM3_COMPA] void timer3_compa_isr(void)
{
   #asm("sei") //Nested interrupt required for CAN/MambaNet SetTLC5920 blocks to long!
   SetTLC5920(cntBlock++&0x03);     
}


#define FIRST_ADC_INPUT 0
#define LAST_ADC_INPUT 7
unsigned int adc_data[LAST_ADC_INPUT-FIRST_ADC_INPUT+1];
#define ADC_VREF_TYPE 0x40

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
   // Func7=In Func6=In Func5=In Func4=In Func3=Out Func2=In Func1=In Func0=In
   // State7=T State6=T State5=P State4=T State3=0 State2=T State1=T State0=T
   PORTB=0x20;
   DDRB=0x88;

   // Port C initialization
   // Func7=In Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out
   // State7=T State6=0 State5=0 State4=0 State3=0 State2=1 State1=0 State0=0
   PORTC=0x14;
   DDRC=0x7F;

   // Port D initialization
   // Func7=Out Func6=In Func5=Out Func4=In Func3=Out Func2=In Func1=In Func0=In
   // State7=0 State6=T State5=0 State4=T State3=0 State2=T State1=T State0=T
   PORTD=0x00;
   DDRD=0xB8;

   // Port E initialization
   // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=Out Func0=In
   // State7=T State6=T State5=T State4=T State3=T State2=T State1=0 State0=T
   PORTE=0x00;
   DDRE=0x02;

   // Port F initialization
   // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
   // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
   PORTF=0x00;
   DDRF=0x00;

   // Port G initialization
   // Func4=In Func3=In Func2=In Func1=In Func0=In
   // State4=T State3=T State2=T State1=T State0=T
   PORTG=0x00;
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

/*
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
*/

// Timer/Counter 3 initialization
// Clock source: System Clock
// Clock value: 2000.000 kHz
// Mode: CTC top=OCR3A
// Noise Canceler: Off
// Input Capture on Falling Edge
// OC3A output: Discon.
// OC3B output: Discon.
// OC3C output: Discon.
// Timer 3 Overflow Interrupt: On
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
// Compare C Match Interrupt: Off
TCCR3A=0x00;
TCCR3B=0x0A;
TCNT3H=0x00;
TCNT3L=0x00;
ICR3H=0x00;
ICR3L=0x00;
OCR3AH=((int)(((OSCILLATOR_FREQUENCY/8)*0.001)-1)>>8)&0xFF;
OCR3AL=((int)((OSCILLATOR_FREQUENCY/8)*0.001)-1)&0xFF; //((OSCILLATOR_FREQUENCY/8)*0.0001)-1 => 100uS
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
   TIMSK3=0x02;

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
   
   HardwareMinorRevision = 0;
   FPGAFirmwareMajorRevision = 0;
   FPGAFirmwareMinorRevision = 0;


   // CAN Controller initialization
   InitializeCAN();
   
   
   BLANK = 0;
    
   TransmitCANMessageBufferLength = 0;
   cntTransmitCANMessageBuffer = 0;

   PreviousMilliSecond = 0;

//               SendMambaNetMessageToCAN(0x10000000, LocalMambaNetAddress, 0, 1, TransmitBuffer, 4);
   LocalMambaNetAddress = 0x00000110;

   cntBlock = 0;
   LeftNrOfLEDs = 0;
   RightNrOfLEDs = 0;
   LeftHoldLEDNr = 0;
   RightHoldLEDNr = 0;       
   NewLeftPos = 0;
   NewRightPos = 0;
   
   // Global enable interrupts
   #asm("sei")

   while (1)
   {
      ProcessCAN();
      
//      SetTLC5920(cntBlock++&0x03);     

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
         PreviousMilliSecond = cntMilliSecond;

         //Release
         if (LeftNrOfLEDs)
         {
            if (LeftNrOfLEDs>NewLeftPos)
            {
               LeftNrOfLEDs--;
            }
         }
         if (RightNrOfLEDs)
         {
            if (RightNrOfLEDs>NewRightPos)
            {
               RightNrOfLEDs--;
            }
         }
         
         
         if (LocalMambaNetAddress == 0x00000000)
         {
            float dB = (20*log10((float)adc_data[0]/1023));
            dB += 60;
            if (dB<0)
            {
               NewLeftPos = 0;
            }
            else if (dB>60)
            {
               NewLeftPos = 60;
            }
            else
            {
               NewLeftPos = dB;
            }

            if (NewLeftPos>LeftNrOfLEDs)
            {
               LeftNrOfLEDs = NewLeftPos;
            }
         }
         
         if (LocalMambaNetAddress == 0x00000000)
         {
            float dB = (20*log10((float)adc_data[3]/1023));
            dB += 60;
            if (dB<0)
            {
               NewRightPos = 0;
            }
            else if (dB>60)
            {
               NewRightPos = 60;
            }
            else
            {
               NewRightPos = dB;
            }

            if (NewRightPos>RightNrOfLEDs)
            {
               RightNrOfLEDs = NewRightPos;
            }
         }

        
         SetLeftLEDNr(LeftHoldLEDNr, 0);
         SetRightLEDNr(RightHoldLEDNr, 0);
         if (NewLeftPos>LeftHoldLEDNr)
         {
            LeftHoldLEDNr = NewLeftPos;
            cntLeftHoldTime = 20;
         }
         if (NewRightPos>RightHoldLEDNr)
         {
            RightHoldLEDNr = NewRightPos;
            cntRightHoldTime = 20;
         }
         
         if (PPM_VU)
         {
            if (cntLeftHoldTime)
            {
               cntLeftHoldTime--;
            }
            else
            {
               if (LeftHoldLEDNr)
               {
                  LeftHoldLEDNr--;
                  cntLeftHoldTime++;
               }
            }
            if (cntRightHoldTime)
            {
               cntRightHoldTime--;
            }
            else
            {
               if (RightHoldLEDNr)
               {
                  RightHoldLEDNr--;
                  cntRightHoldTime++;
               }
            }
         }
         
         SetLeftNrOfLEDs(LeftNrOfLEDs);
         SetRightNrOfLEDs(RightNrOfLEDs);
         SetLeftLEDNr(LeftHoldLEDNr, 1);
         SetRightLEDNr(RightHoldLEDNr, 1);
      }

      if (cntMilliSecond - PreviousLEDBlinkMilliSecond > 250)
      {  //LED Blink 4 times per second.
         PreviousLEDBlinkMilliSecond = cntMilliSecond;

         cntDebug++;
         if (cntDebug>4)
         {
            cntDebug=0;
         }

         LEDDataLeft[0] &= 0x7FFF;
         LEDDataLeft[1] &= 0x7FFF;
         LEDDataLeft[2] &= 0x7FFF;
         LEDDataLeft[3] &= 0x7FFF;
         
         switch (cntDebug)
         {
            case 1:
            {
               LEDDataLeft[0] |= 0x8000;
            }
            break;
            case 2:
            {
               LEDDataLeft[0] |= 0x8000;
               LEDDataLeft[1] |= 0x8000;
            }
            break;
            case 3:
            {
               LEDDataLeft[0] |= 0x8000;
               LEDDataLeft[1] |= 0x8000;
               LEDDataLeft[2] |= 0x8000;
            }
            break;
            case 4:
            {
               LEDDataLeft[0] |= 0x8000;
               LEDDataLeft[1] |= 0x8000;
               LEDDataLeft[2] |= 0x8000;
               LEDDataLeft[3] |= 0x8000;
            }
            break;
         }            
      }      

      //ReadSwitches();
   }
}

/*
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
   //Switch Rows
   char ReturnValue;
   unsigned char Overload;
   unsigned char Mask;
   unsigned char cntBit;

	ReturnValue = SwitchCheck(0, 0, nGPI1);
   DoSwitch(0, ReturnValue);

	ReturnValue = SwitchCheck(0, 1, nGPI2);
   DoSwitch(1, ReturnValue);

	ReturnValue = SwitchCheck(0, 2, nGPI3);
   DoSwitch(2, ReturnValue);

	ReturnValue = SwitchCheck(0, 3, nGPI4);
   DoSwitch(3, ReturnValue);

	ReturnValue = SwitchCheck(0, 4, nGPI5);
   DoSwitch(4, ReturnValue);

	ReturnValue = SwitchCheck(0, 5, nGPI6);
   DoSwitch(5, ReturnValue);

	ReturnValue = SwitchCheck(0, 6, nGPI7);
   DoSwitch(6, ReturnValue);

	ReturnValue = SwitchCheck(0, 7, nGPI8);
   DoSwitch(7, ReturnValue);

   Overload = PORTA;

   for (cntBit=0; cntBit<8; cntBit++)
   {
      Mask = 0x80>>cntBit;

      if (SwitchData[1][cntBit] !=  (Overload&Mask))
      {
         if (Overload&Mask)
         {
            DoSwitch(8+cntBit, 1);
         }
         else
         {
            DoSwitch(8+cntBit, -1);
         }
         SwitchData[1][cntBit] = Overload&Mask;
      }
   }
}

void DoSwitch(unsigned char LogicSwitchNr, int Event)
{
    if ((Event == 1) || (Event == -1))
    {
        unsigned char TransmitBuffer[6];
        unsigned int ObjectNr;

        if ((LogicSwitchNr>=0) && (LogicSwitchNr<8))
        {
            ObjectNr = LogicSwitchNr + 1027;
        }
        else if ((LogicSwitchNr>=8) && (LogicSwitchNr<16))
        {
            ObjectNr = LogicSwitchNr + 1059 - 8;
        }

        TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
        TransmitBuffer[1] = ObjectNr&0xFF;
        TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_CHANGED;
        TransmitBuffer[3] = STATE_DATATYPE;
        TransmitBuffer[4] = 1;
        TransmitBuffer[5] = 0;
        if (Event == 1)
        {
           TransmitBuffer[5] = 1;
        }

        SendMambaNetMessageToCAN(0x10000000, LocalMambaNetAddress, 0, 1, TransmitBuffer, 6);
    }
}
*/

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
            case MAMBANET_OBJECT_ACTION_GET_INFORMATION:
            {  // static objects are handled in the stack
               if ((ObjectNr>=(1024+NumberOfStaticObjects)) && (ObjectNr<(1024+DefaultNodeObjects.NumberOfObjects)))
               {  //Only for the non-standard objects
               }   
            }
            break;            
            case  MAMBANET_OBJECT_ACTION_INFORMATION_RESPONSE:
            {       //Not yet implemented
            }
            break;
            case  MAMBANET_OBJECT_ACTION_GET_SENSOR_DATA:
            {       //Not yet implemented
            }
            break;
            case  MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE:
            {       //Not implemented
            }
            break;
            case  MAMBANET_OBJECT_ACTION_GET_ACTUATOR_DATA:
            {       //Not yet implemented.
            }
            break;
            case  MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE:
            {       //Not implemented
            }
            break;
            case  MAMBANET_OBJECT_ACTION_SET_ACTUATOR_DATA:
            {
               switch (ObjectNr)               
               {
                  case 1024:
                  {
                     if ((Data[3] == FLOAT_DATATYPE) && (Data[4]==2))
                     {                   
                        float Value;
                        if (VariableFloat2Float(&Data[5], Data[4], &Value) == 0)
                        {
                           float dB = Value+20;
                           dB += 50;
                           if (dB<0)
                           {
                              NewLeftPos = 0;
                           }
                           else if (dB>60)
                           {
                              NewLeftPos = 60;
                           }
                           else
                           {
                              NewLeftPos = dB;
                           }

                           if (NewLeftPos>LeftNrOfLEDs)
                           {
                              LeftNrOfLEDs = NewLeftPos;
                           }
                        }
                     }
                  }
                  break;
                  case 1025:
                  {
                     if (Data[3] == FLOAT_DATATYPE)
                     {
                        float Value;
                        if (VariableFloat2Float(&Data[5], Data[4], &Value) == 0)
                        {
                           float dB = Value+20;
                           dB += 50;
                           if (dB<0)
                           {
                              NewRightPos = 0;
                           }
                           else if (dB>60)
                           {
                              NewRightPos = 60;
                           }
                           else
                           {
                              NewRightPos = dB;
                           }

                           if (NewRightPos>RightNrOfLEDs)
                           {
                              RightNrOfLEDs = NewRightPos;
                           }
                        }
                     }
                  }
                  break;
               }
            }
            break;
         }
      }
      break;
   }
}

void SetTLC5920(char cntBlock)
{  
   char cntBit;
   unsigned int Mask;
    
   SCLK = 0;     
   for (cntBit=0; cntBit<16; cntBit++)
   {
      Mask = 0x8000>>cntBit;
      
      if (LEDDataLeft[cntBlock]&Mask)
      {   
         SINL = 1;
      }
      else
      {
         SINL = 0;
      }

      if (LEDDataRight[cntBlock]&Mask)
      {   
         SINR = 1;
      }
      else
      {
         SINR = 0;
      }
 
      SCLK = 1;
      SCLK = 0;
   }
   
   BLANK = 1;
   nLATCH = 1;
   nLATCH = 0;
   CSEL0 = cntBlock&0x01;
   CSEL1 = cntBlock&0x02; 
   BLANK = 0;
}

void SetLeftNrOfLEDs(int NrOfLEDs)
{     
   char cntBlock; 
   char NrOfFullBlocks;
   char NrOfLEDsInBlock;
   char cntLEDs;
   unsigned int MSB;
   
   NrOfFullBlocks = NrOfLEDs/15;
   
   for (cntBlock=0; cntBlock<4; cntBlock++)
   {
      if (cntBlock<NrOfFullBlocks)
      {
         LEDDataLeft[cntBlock] |= 0x7FFF;
      }
      else
      {
         NrOfLEDsInBlock = NrOfLEDs-((int)cntBlock*15);
         LEDDataLeft[cntBlock] &= 0x8000;
         if (NrOfLEDsInBlock>0)
         {
            MSB = LEDDataLeft[cntBlock]&0x8000;
            LEDDataLeft[cntBlock] = 0x0000;
            for (cntLEDs=0; cntLEDs<NrOfLEDsInBlock; cntLEDs++)
            {             
               LEDDataLeft[cntBlock] <<= 1;
               LEDDataLeft[cntBlock] |= 0x0001;
            }
            LEDDataLeft[cntBlock] |= MSB;
         }     
      }
   }
}

void SetRightNrOfLEDs(int NrOfLEDs)
{
   char cntBlock; 
   char NrOfFullBlocks;
   char NrOfLEDsInBlock;
   char cntLEDs;
   unsigned int MSB;
   
   NrOfFullBlocks = NrOfLEDs/15;
   
   for (cntBlock=0; cntBlock<4; cntBlock++)
   {
      if (cntBlock<NrOfFullBlocks)
      {
         LEDDataRight[cntBlock] |= 0x7FFF;
      }
      else
      {
         NrOfLEDsInBlock = NrOfLEDs-((int)cntBlock*15);
         LEDDataRight[cntBlock] &= 0x8000;
         if (NrOfLEDsInBlock>0)
         {
            MSB = LEDDataRight[cntBlock]&0x8000;
            LEDDataRight[cntBlock] = 0x0000;
            for (cntLEDs=0; cntLEDs<NrOfLEDsInBlock; cntLEDs++)
            {             
               LEDDataRight[cntBlock] <<= 1;
               LEDDataRight[cntBlock] |= 0x0001;
            }
            LEDDataRight[cntBlock] |= MSB;
         }     
      }
   }
}

void SetLeftLEDNr(int LEDNr, char State)
{     
   char Block; 
   char LEDNrInBlock;
   char cntLEDs;
   unsigned int Mask;
    
   if (LEDNr>0)
   {         
      Block = (LEDNr-1)/15; 
      LEDNrInBlock = (LEDNr-1)-((int)Block*15);
   
      Mask = 0x0001;
      Mask <<= LEDNrInBlock;
                                   
      if (State)
      {
         LEDDataLeft[Block] |= Mask;
      }
      else
      {
         LEDDataLeft[Block] &= Mask^0xFFFF;
      }
   }
}

void SetRightLEDNr(int LEDNr, char State)
{
   char Block; 
   char LEDNrInBlock;
   char cntLEDs;
   unsigned int Mask;
   
   if (LEDNr>0)
   {         
      Block = (LEDNr-1)/15; 
      LEDNrInBlock = (LEDNr-1)-((int)Block*15);
   
      Mask = 0x0001;
      Mask <<= LEDNrInBlock;
                                    
      if (State)
      {
         LEDDataRight[Block] |= Mask;
      }
      else
      {     
         LEDDataRight[Block] &= Mask^0xFFFF;
      }
   }
}

void CanBussError()
{
   AddressValidated = 0;
   timerReservationInfo = 1;
}