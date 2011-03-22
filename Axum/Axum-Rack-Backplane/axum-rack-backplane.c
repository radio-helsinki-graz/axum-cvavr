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

#include "Axum-Rack-Backplane.h"
#include "lcd.h"
#include "CANTransportLayer.h"
#include "Axum-Rack-Backplane-MambaNet.h"

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
   unsigned int cntTransmitReservation=0;

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
   // Func7=In Func6=In Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out
   // State7=T State6=T State5=0 State4=0 State3=0 State2=0 State1=0 State0=0
   PORTA=0x00;
   DDRA=0x3F;

   // Port B initialization
   // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=Out Func1=Out Func0=Out
   // State7=T State6=T State5=T State4=T State3=T State2=0 State1=0 State0=1
   PORTB=0x01;
   DDRB=0x07;

   // Port C initialization
   // Func7=In Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out
   // State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0
   PORTC=0x00;
   DDRC=0xFF;

   // Port D initialization
   // Func7=Out Func6=In Func5=Out Func4=Out Func3=Out Func2=In Func1=In Func0=In
   // State7=0 State6=T State5=0 State4=0 State3=0 State2=T State1=T State0=T
   PORTD=0x00;
   DDRD=0xB8;

   // Port E initialization
   // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=Out Func0=In
   // State7=P State6=P State5=P State4=P State3=T State2=T State1=0 State0=T
   PORTE=0xF0;
   DDRE=0x02;

   // Port F initialization
   // Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out
   // State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0
   PORTF=0x05; //48kHz
   DDRF=0xFF;

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

   PLLC0 = 1;
   PLLC1 = 0;
   PLLC2 = 1;
   PLLC3 = 0;

   HardwareMinorRevision = (PINE>>4)&0x0F;

   delay_ms(500);

   ReadFPGA();
   FPGAFirmwareMajorRevision = FPGAData[0];
   FPGAFirmwareMinorRevision = FPGAData[1];
   FPGAFirmwareType = ((((unsigned int)FPGAData[2])<<8) | FPGAData[3])&0x7FFF;
   if (FPGAData[2]&0x80)
   {
      FPGAPLLLock = 0;
   }
   else
   {
      FPGAPLLLock = 1;
   }

   EnableSum[0] = 0;
   EnableSum[1] = 0;
   EnableSum[2] = 0;
   EnableSum[3] = 0;

   Samplerate = 2;

   PreviousPLLLock = 0;
   PLLLock = 0;

   // CAN Controller initialization
   InitializeCAN();

   SetupLCD();
   delay_ms(500);

   {
      unsigned char TextString[40];
      sprintf(TextString, "Axum-Rack-Backplane ");
      SetLCDModule(0, 0, TextString);

      sprintf(TextString, "debug: ");
      SetLCDModule(0, 1, TextString);
   }

   TransmitCANMessageBufferLength = 0;
   cntTransmitCANMessageBuffer = 0;

   PreviousMilliSecond = 0;

//               SendMambaNetMessageToCAN(0x10000000, LocalMambaNetAddress, 0, 1, TransmitBuffer, 4);
   LocalMambaNetAddress = 0x00000106;

   //SetPLL1706(2);

   SetFPGA(0x0800, 0x000E);


   // Global enable interrupts
   #asm("sei")

   Parent[0] = (ManufacturerID>>8)&0xFF;
   Parent[1] = ManufacturerID&0xFF;
   Parent[2] = (ProductID>>8)&0xFF;
   Parent[3] = ProductID&0xFF;
   Parent[4] = (UniqueIDPerProduct>>8)&0xFF;
   Parent[5] = UniqueIDPerProduct&0xFF;

   CheckUniqueIDPerProduct();

   while (1)
   {
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

         {
            unsigned char TextString[40];
            sprintf(TextString, "Mob1 B:%d, S:%d, C:%d, F:%d, A:%d", cntCANBitErrorMob1, cntCANStuffErrorMob1, cntCANCRCErrorMob1, cntCANFormErrorMob1, cntCANAckErrorMob1);
            SetLCDModule(0, 0, TextString);
            sprintf(TextString, "Gen       S:%d, C:%d, F:%d, A:%d", cntCANStuffErrorGeneral, cntCANCRCErrorGeneral, cntCANFormErrorGeneral, cntCANAcknowledgementErrorGeneral);
            SetLCDModule(0, 1, TextString);
         }
         cntTransmitReservation++;

         SendCANParentControlMessage();
      }

      if (cntMilliSecond - PreviousMilliSecond > 40)
      {  //Send track/relative information maximal 25 times per second.
         PreviousMilliSecond = cntMilliSecond;

         PLLLock = EXTR_LOCK;
         if (PreviousPLLLock != PLLLock)
         {
            SendSensorChangeToMambaNet(1031, STATE_DATATYPE, 1, &PLLLock);
            PreviousPLLLock = PLLLock;
         }
      }

      if (cntMilliSecond - PreviousLEDBlinkMilliSecond > 250)
      {  //LED Blink 4 times per second.
         PreviousLEDBlinkMilliSecond = cntMilliSecond;
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
                  unsigned char TransmitBuffer[96];
                  char cntSize;
                  unsigned long int TempData;
                  char cntChar;
                  char *TextStart;
                  int OutputNr;

                  unsigned char BlockNr;
                  unsigned char BlockChannelNr;

                  unsigned char SlotNr;
                  unsigned char ChannelNr;

                  OutputNr = ObjectNr-(NumberOfStaticObjects+1024);

                  cntSize=0;
                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_INFORMATION_RESPONSE;
                  TransmitBuffer[3] = OBJECT_INFORMATION_DATATYPE;
                  TransmitBuffer[4] = cntSize;  //updated later...
                  TextStart = &TransmitBuffer[(unsigned char)(5+cntSize)];
                  for (cntChar=0; cntChar<32; cntChar++)
                  {
                     TransmitBuffer[(unsigned char)(5+cntSize++)] = 0x00;
                  }
                  BlockNr = (OutputNr>>5);
                  BlockChannelNr = (OutputNr&0x1F);

                  if (BlockNr<56)
                  {
                     if (BlockNr<15)
                     {
                        SlotNr = BlockNr;
                        ChannelNr = BlockChannelNr;
                     }
                     else if (BlockNr<35)
                     {
                        unsigned char DSPSlotNr;
                        unsigned char DSPLineNr;

                        DSPSlotNr = (BlockNr-15)/5;
                        DSPLineNr = (BlockNr-15)%5;

                        SlotNr = 15+DSPSlotNr;
                        ChannelNr = BlockChannelNr+(DSPLineNr*32);
                     }
                     else
                     {
                        SlotNr = BlockNr-14;
                        ChannelNr = BlockChannelNr;
                     }
                     //max length 32
                     sprintf(TextStart, "Audio to slot %d, channel %d", SlotNr+1, ChannelNr+1);
                  }
                  else
                  {
                     //max length 32
                     sprintf(TextStart, "Audio to all slots, channel %d",  BlockChannelNr+1);
                  }

                  TransmitBuffer[(unsigned char)(5+cntSize++)] = 0x00; //services

                  //Sensor
                  TransmitBuffer[(unsigned char)(5+cntSize++)] = NO_DATA_DATATYPE;
                  TransmitBuffer[(unsigned char)(5+cntSize++)] = 0; //data size

                  //Actuator
                  TransmitBuffer[(unsigned char)(5+cntSize++)] = UNSIGNED_INTEGER_DATATYPE;
                  TransmitBuffer[(unsigned char)(5+cntSize++)] = 2; //data size

                  TempData = 0;  //min
                  for (cntChar=0; cntChar<2; cntChar++)
                  {
                     TransmitBuffer[(unsigned char)(5+cntSize++)] = (TempData>>(unsigned char)(((2-cntChar)-1)<<3))&0xFF;
                  }
                  TempData = 1664; //max
                  for (cntChar=0; cntChar<2; cntChar++)
                  {
                     TransmitBuffer[(unsigned char)(5+cntSize++)] = (TempData>>(unsigned char)(((2-cntChar)-1)<<3))&0xFF;
                  }
                  TempData = 0; //default
                  for (cntChar=0; cntChar<2; cntChar++)
                  {
                     TransmitBuffer[(unsigned char)(5+cntSize++)] = (TempData>>(unsigned char)(((2-cntChar)-1)<<3))&0xFF;
                  }
                  //Adjust the size
                  TransmitBuffer[4] = cntSize;

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, cntSize+5);
               }
            }
            break;
            case  MAMBANET_OBJECT_ACTION_INFORMATION_RESPONSE:
            {       //Not yet implemented
            }
            break;
            case  MAMBANET_OBJECT_ACTION_GET_SENSOR_DATA:
            {
               unsigned char TransmitBuffer[21];

               // if (ObjectNr<1024) is handled in the stack
               if ((ObjectNr>=1025) && (ObjectNr<1026))
               {  //FPGA PLL Lock
                  ReadFPGA();
                  if (FPGAData[2]&0x80)
                  {
                     FPGAPLLLock = 0;
                  }
                  else
                  {
                     FPGAPLLLock = 1;
                  }

                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = FPGAPLLLock;

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1031) && (ObjectNr<1032))
               {  //PLL Lock

                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = EXTR_LOCK;

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
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
            case  MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE:
            {       //Not implemented
            }
            break;
            case  MAMBANET_OBJECT_ACTION_GET_ACTUATOR_DATA:
            {
               unsigned char TransmitBuffer[23];

               TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
               TransmitBuffer[1] = ObjectNr&0xFF;
               TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE;

               if ((ObjectNr>=1024) && (ObjectNr<1025))
               {  //Clock frequency
                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = Samplerate;

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1026) && (ObjectNr<1030))
               {
                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = EnableSum[ObjectNr-1026];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1030) && (ObjectNr<1031))
               {
                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = PLLC1;

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);
               }
               else if ((ObjectNr>=1032) && (ObjectNr<2857))
               {  //Write FPGA + Routng
                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                  TransmitBuffer[3] = ERROR_DATATYPE;
                  TransmitBuffer[4] = 15;
                  TransmitBuffer[5] = 'N';
                  TransmitBuffer[6] = 'o';
                  TransmitBuffer[7] = 't';
                  TransmitBuffer[8] = ' ';
                  TransmitBuffer[9] = 'I';
                  TransmitBuffer[10] = 'm';
                  TransmitBuffer[11] = 'p';
                  TransmitBuffer[12] = 'l';
                  TransmitBuffer[13] = 'e';
                  TransmitBuffer[14] = 'm';
                  TransmitBuffer[15] = 'e';
                  TransmitBuffer[16] = 'n';
                  TransmitBuffer[17] = 't';
                  TransmitBuffer[18] = 'e';
                  TransmitBuffer[19] = 'd';

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 20);
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
            case  MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE:
            {       //Not implemented
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

               if ((ObjectNr>=1024) && (ObjectNr<1025))
               {  //Clock frequency
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        Samplerate = Data[5];

                        switch (Samplerate)
                        {
                           case 0:
                           {  //32kHz
                              PLLC2 = 0;
                              PLLC3 = 0;
                           }
                           break;
                           case 1:
                           {  //44.1kHz
                              PLLC2 = 0;
                              PLLC3 = 1;
                           }
                           break;
                           case 2:
                           {  //48kHz
                              PLLC2 = 0;
                              PLLC3 = 0;
                              PLLC2 = 1;
                           }
                           break;
                        }
                        break;

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1026) && (ObjectNr<1030))
               {
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        unsigned int FunctionNr = 0x0800;
                        unsigned int FunctionData = 0x0000;
                        char cnt;

                        EnableSum[ObjectNr-1026] = Data[5];

                        for (cnt=0; cnt<4; cnt++)
                        {
                           if (EnableSum[cnt] == 0)
                           {
                              FunctionData |= (unsigned char)(0x01<<cnt);
                           }
                        }

                        SetFPGA(FunctionNr, FunctionData);

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1030) && (ObjectNr<1031))
               {
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        if (Data[5])
                        {
                           PLLC1 = 1;
                        }
                        else
                        {
                           PLLC1 = 0;
                        }

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1032) && (ObjectNr<1033))
               {  //Write FPGA
                  if (DataType == OCTET_STRING_DATATYPE)
                  {
                     if (DataSize == 4)
                     {
                        unsigned int FunctionNr;
                        unsigned int FunctionData;

                        FunctionNr = Data[5];
                        FunctionNr <<= 8;
                        FunctionNr |= Data[6];

                        FunctionData = Data[7];
                        FunctionData <<= 8;
                        FunctionData |= Data[8];

                        SetFPGA(FunctionNr, FunctionData);

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1033) && (ObjectNr<2857))
               {
                  if (DataType == UNSIGNED_INTEGER_DATATYPE)
                  {
                     if (DataSize == 2)
                     {
                        unsigned int InputNr;
                        unsigned int FunctionNr;
                        unsigned char SlotNr;
                        unsigned char ChannelNr;

                        InputNr = Data[5];
                        InputNr <<= 8;
                        InputNr |= Data[6];

                        ChannelNr = (ObjectNr-1032)&0x1F;
                        SlotNr = ((ObjectNr-1032)>>5)&0x3F;

                        FunctionNr = ChannelNr;
                        FunctionNr <<= 5;
                        FunctionNr |= (SlotNr&0x1F);
                        if (SlotNr&0x20)
                        {
                           FunctionNr |= 0x400;
                        }

                        SetFPGA(FunctionNr, InputNr);

                        FormatError = 0;
                        MessageDone = 1;
                     }
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
   ToAddress++;
   DataLength++;
}

void ReadFPGA()
{
   unsigned char cntBit;
   unsigned char cntByte;
   unsigned char Mask;
   unsigned char DataByte;

   SCK = 0;
   nSS = 0;

   for (cntByte=0; cntByte<4; cntByte++)
   {
      Mask = 0x80;
      DataByte = 0x00;
      for (cntBit=0; cntBit<8; cntBit++)
      {
         MOSI = 1;// write 1's has no influence in FPGA
         SCK = 1;
         //Read data
         if (MISO)
         {
            DataByte |= Mask;
         }
         Mask >>= 1;
         SCK = 0;
      }
      FPGAData[cntByte] = DataByte;
   }

   nSS=1;
}

void SetFPGA(unsigned int FunctionNr, unsigned int FunctionData)
{
   unsigned char cntBit;
   unsigned char Mask;
   unsigned char FunctionNrBuffer[2];
   unsigned char FunctionDataBuffer[2];

   FunctionNrBuffer[0] = (FunctionNr>>8)&0xFF;
   FunctionNrBuffer[1] = (FunctionNr   )&0xFF;

   FunctionDataBuffer[0] = (FunctionData>>8)&0xFF;
   FunctionDataBuffer[1] = (FunctionData   )&0xFF;

   nSS = 0;
   SCK = 0;

   Mask = 0x80;
   for (cntBit=0; cntBit<8; cntBit++)
   {
      MOSI = FunctionNrBuffer[0]&Mask;
      Mask >>= 1;
      SCK = 1;
      SCK = 0;
   }
   Mask = 0x80;
   for (cntBit=0; cntBit<8; cntBit++)
   {
      MOSI = FunctionNrBuffer[1]&Mask;
      Mask >>= 1;
      SCK = 1;
      SCK = 0;
   }

   Mask = 0x80;
   for (cntBit=0; cntBit<8; cntBit++)
   {
      MOSI = FunctionDataBuffer[0]&Mask;
      Mask >>= 1;
      SCK = 1;
      SCK = 0;
   }
   Mask = 0x80;
   for (cntBit=0; cntBit<8; cntBit++)
   {
      MOSI = FunctionDataBuffer[1]&Mask;
      Mask >>= 1;
      SCK = 1;
      SCK = 0;
   }
   nSS=1;
   nSS=0;
}

void CanBussError()
{
//   AddressValidated = 0;
//   timerReservationInfo = 1;
}