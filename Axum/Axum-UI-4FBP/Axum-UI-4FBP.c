/*****************************************************
This program was produced by the
CodeWizardAVR V1.25.3 Standard
Automatic Program Generator
© Copyright 1998-2007 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Axum-UI-4FBP
Version :
Date    : 1-10-2007
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

#include "Axum-UI-4FBP.h"
#include "CANTransportLayer.h"
#include "Axum-UI-4FBP-MambaNet.h"

#include "lcd.h"

unsigned char TextString[9];

extern unsigned long int ObjectNrInformationCount;
extern unsigned long int LastObjectInformationRequested;

//unsigned char LocalCANGIE;
//unsigned char LocalCANSIT2;
//unsigned char LocalCANSTMOB;
//unsigned char LocalCANCDMOB;
//unsigned char LocalCANIDT4;
//unsigned char LocalCANIDT3;
//unsigned char LocalCANIDT2;
//unsigned char LocalCANIDT1;

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

      PDO = !PDO;
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
   // Declare your local variables here
   char cntModule;
   char cntByte;

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
   // Func7=Out Func6=Out Func5=Out Func4=Out Func3=In Func2=In Func1=In Func0=Out
   // State7=0 State6=0 State5=0 State4=0 State3=T State2=T State1=T State0=1
   PORTB=0x01;
   DDRB=0xF1;

   // Port C initialization
   // Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out
   // State7=1 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0
   PORTC=0x80;
   DDRC=0xFF;

   // Port D initialization
   // Func7=Out Func6=In Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out
   // State7=1 State6=T State5=1 State4=1 State3=1 State2=1 State1=1 State0=1
   PORTD=0xBF;
   DDRD=0xBF;

   // Port E initialization
   // Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=In
   // State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=T
   PORTE=0x00;
   DDRE=0xFE;

   // Port F initialization
   // Func7=OUT Func6=OUT Func5=OUT Func4=OUT Func3=In Func2=In Func1=In Func0=In
   // State7=T State6=T State5=T State4=0 State3=T State2=T State1=T State0=T
   PORTF=0x00;
   DDRF=0xF0;

   // Port G initialization
   // Func4=In Func3=In Func2=Out Func1=Out Func0=Out
   // State4=T State3=T State2=0 State1=0 State0=0
   PORTG=0x00;
   DDRG=0x07;

   // Timer/Counter 0 initialization
   // Clock source: System Clock
   // Clock value: 1000,000 kHz
   // Mode: CTC top=OCR0
   // OC0 output: Disconnected
   TCCR0A=0x0A;
   TCNT0=0x00;
   OCR0A=((OSCILLATOR_FREQUENCY/8)*0.0001)-1;

   // Timer/Counter 1 initialization
   // Clock source: System Clock
   // Clock value: 16000,000 kHz
   // Mode: Ph. correct PWM top=03FFh
   // OC1A output: Non-Inv.
   // OC1B output: Non-Inv.
   // OC1C output: Discon.
   // Noise Canceler: Off
   // Input Capture on Falling Edge
   // Timer 1 Overflow Interrupt: Off
   // Input Capture Interrupt: Off
   // Compare A Match Interrupt: Off
   // Compare B Match Interrupt: Off
   // Compare C Match Interrupt: Off
   TCCR1A=0xA3;
   TCCR1B=0x01;
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
   // Clock value: 16000,000 kHz
   // Mode: Ph. correct PWM top=03FFh
   // Noise Canceler: Off
   // Input Capture on Falling Edge
   // OC3A output: Non-Inv.
   // OC3B output: Non-Inv.
   // OC3C output: Discon.
   // Timer 3 Overflow Interrupt: Off
   // Input Capture Interrupt: Off
   // Compare A Match Interrupt: Off
   // Compare B Match Interrupt: Off
   // Compare C Match Interrupt: Off
   TCCR3A=0xA3;
   TCCR3B=0x01;
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
   // ADC Voltage Reference: VCC
   // Digital input buffers on ADC0: On, ADC1: On, ADC2: On, ADC3: On
   // ADC4: On, ADC5: On, ADC6: On, ADC7: On
   DIDR0=0x00;
   ADMUX=FIRST_ADC_INPUT | (ADC_VREF_TYPE & 0xff);
   ADCSRA=0xCC;

   HardwareMinorRevision = (PINF>>4)&0x0F;

   FPGAFirmwareMajorRevision = 0;
   FPGAFirmwareMinorRevision = 0;

   // CAN Controller initialization
   InitializeCAN();

   delay_ms(1000);

   for (cntByte=0; cntByte<NR_OF_LEDS/8; cntByte++)
   {
      LogicLEDData[cntByte] = 0xFF;
   }
   SetLEDs();
	BLANK = 0;

   delay_ms(500);

   SetupLCD();
   for (cntByte=0; cntByte<NR_OF_LEDS/8; cntByte++)
   {
      LogicLEDData[cntByte] = 0x00;
   }

   for (cntByte=0; cntByte<36; cntByte++)
   {
      SwitchState[cntByte] = 0;
   }
   for (cntByte=0; cntByte<4; cntByte++)
   {
      sprintf(LCDTextString[cntByte], "  4FBP  ");
   }
   for (cntByte=4; cntByte<8; cntByte++)
   {
      sprintf(LCDTextString[cntByte], "Waiting!");
   }

   SetLEDs();

	BLANK = 0;

   delay_ms(500);

   for (cntModule=0; cntModule<4; cntModule++)
   {
      sprintf(TextString, "  4FBP  ");
      SetLCDModule(cntModule, 0, TextString);
      sprintf(TextString, "Waiting!");
      SetLCDModule(cntModule, 1, TextString);
   }

   for (cntModule=0; cntModule<4; cntModule++)
   {
      SwitchColorOn[cntModule][0] = 2;
      SwitchColorOn[cntModule][1] = 2;
      SwitchColorOn[cntModule][2] = 2;
      SwitchColorOn[cntModule][3] = 2;
      SwitchColorOff[cntModule][0] = 0;
      SwitchColorOff[cntModule][1] = 0;
      SwitchColorOff[cntModule][2] = 0;
      SwitchColorOff[cntModule][3] = 0;
      DualColorSwitchState[cntModule][0] = 0;
      DualColorSwitchState[cntModule][1] = 0;
      DualColorSwitchState[cntModule][2] = 0;
      DualColorSwitchState[cntModule][3] = 0;
   }

   cntMilliSecond = 0;
   PreviousMilliSecond = 0;
   EncoderPreviousUpTime[0] = 0;
   EncoderPreviousUpTime[1] = 0;
   EncoderPreviousUpTime[2] = 0;
   EncoderPreviousUpTime[3] = 0;
   EncoderPreviousDownTime[0] = 0;
   EncoderPreviousDownTime[1] = 0;
   EncoderPreviousDownTime[2] = 0;
   EncoderPreviousDownTime[3] = 0;
   PreviousFaderPosition[0] = 0;
   PreviousFaderPosition[1] = 0;
   PreviousFaderPosition[2] = 0;
   PreviousFaderPosition[3] = 0;

   MotorActive[0] = 20;
   MotorActive[1] = 20;
   MotorActive[2] = 20;
   MotorActive[3] = 20;

   MoveByFader[0] = 0;
   MoveByFader[1] = 0;
   MoveByFader[2] = 0;
   MoveByFader[3] = 0;

   PWM_M1_A = 0;
   PWM_M1_B = 0;
   PWM_M2_A = 0;
   PWM_M2_B = 0;
   PWM_M3_A = 0;
   PWM_M3_B = 0;
   PWM_M4_A = 0;
   PWM_M4_B = 0;
   ENB_MTRS = 1;

//   LocalMambaNetAddress = 2;

   // Global enable interrupts
   #asm("sei")

   while (1)
   {
      ProcessCAN();

      if (DoSetLEDs)
      {
        DoSetLEDs = 0;
        SetLEDs();
      }

      // Place your code here
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

         /*{
            unsigned char DebugString[64];

            sprintf(DebugString, "cntCAN:%d P:0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X", cntReceiveCANControl, Parent[0], Parent[1], Parent[2], Parent[3], Parent[4], Parent[5]);
            SetLCDModule(0, 0, DebugString);

            sprintf(DebugString, "Count:%d, last %d", ObjectNrInformationCount, LastObjectInformationRequested);
            SetLCDModule(0, 1, DebugString);
         }*/
      }

      ReadSwitches();
      ReadEncoders();
      ReadTouch();
      ReadFaders();
      ControlMotors();

      if (cntMilliSecond - PreviousMilliSecond > 20)
      {
         for (cntModule=0; cntModule<4; cntModule++)
         {
            if (PreviousEncoderPosition[cntModule] != EncoderPosition[cntModule])
            {
               unsigned char TransmitBuffer[1];
               unsigned int ObjectNr;
               int Difference;

               ObjectNr = 1032+cntModule;
               Difference = EncoderPosition[cntModule]-PreviousEncoderPosition[cntModule];

               TransmitBuffer[0] = Difference&0xFF;
               SendSensorChangeToMambaNet(ObjectNr, SIGNED_INTEGER_DATATYPE, 1, TransmitBuffer);

               PreviousEncoderPosition[cntModule] = EncoderPosition[cntModule];
            }

            if ((!MotorActive[cntModule]) || (CurrentTouch[cntModule]))
            {
               if (PreviousFaderPosition[cntModule] != FaderPosition[cntModule])
               {
                  unsigned char TransmitBuffer[2];
                  unsigned int ObjectNr;

                  MoveByFader[cntModule] = 25;
                  MotorPosition[cntModule] = FaderPosition[cntModule];

                  ObjectNr = 1104+cntModule;

                  TransmitBuffer[0] = (FaderPosition[cntModule]>>8)&0xFF;
                  TransmitBuffer[1] = FaderPosition[cntModule]&0xFF;

                  SendSensorChangeToMambaNet(ObjectNr, UNSIGNED_INTEGER_DATATYPE, 2, TransmitBuffer);
                  PreviousFaderPosition[cntModule] = FaderPosition[cntModule];
               }
               else
               {
                  if (MoveByFader[cntModule])
                  {
                    MoveByFader[cntModule]--;
                  }
               }
            }
            else
            {
              if (MotorActive[cntModule])
              {
                MotorActive[cntModule]--;
              }
              MoveByFader[cntModule] = 0;
            }
         }

/*
         LocalCANGIE = CANGIE;
         CANGIE &= 0x7F;
         CANPAGE = 0x10;
         LocalCANGIT = CANGIT;
         LocalCANSIT2 = CANSIT2;
         LocalCANSTMOB = CANSTMOB;
         LocalCANCDMOB = CANCDMOB;
         LocalCANIDT4 = CANIDT4;
         LocalCANIDT3 = CANIDT3;
         LocalCANIDT2 = CANIDT2;
         LocalCANIDT1 = CANIDT1;
         CANGIE = LocalCANGIE;
*/


//         sprintf(TextString,"Address:");
//         SetLCDModule(0, 0, TextString);
//         sprintf(TextString,"%04X%04X", (LocalCANAddress>>16)&0xFFFF, LocalCANAddress&0xFFFF);
//         SetLCDModule(0, 0, TextString);


//         sprintf(TextString,"ProdID: ");
//         SetLCDModule(1, 0, TextString);
//         sprintf(TextString,"%8d", ProductID);
//         SetLCDModule(1, 1, TextString);
//         sprintf(TextString,"%2d %2d %2d", ReceivedManufacturerID, ReceivedProductID, ReceivedUniqueIDPerProduct);
//         SetLCDModule(2, 0, TextString);
/*
         sprintf(TextString,"%02X %02X %02X", LocalCANGIT, LocalCANGIE, LocalCANSIT2);
         SetLCDModule(1, 0, TextString);
         sprintf(TextString,"%02X %02X   ", LocalCANSTMOB, LocalCANCDMOB);
         SetLCDModule(1, 1, TextString);
*/
/*         sprintf(TextString,"%02X %02X   ", LocalCANIDT4, LocalCANIDT3);
         SetLCDModule(2, 0, TextString);
         sprintf(TextString,"%02X %02X   ", LocalCANIDT2, LocalCANIDT1);
         SetLCDModule(2, 1, TextString);

         LocalCANGIE = CANGIE;
         CANGIE &= 0x7F;
         CANPAGE = 0x00;
         LocalCANGIT = CANGIT;
         LocalCANSIT2 = CANSIT2;
         LocalCANSTMOB = CANSTMOB;
         LocalCANCDMOB = CANCDMOB;
         LocalCANIDT4 = CANIDT4;
         LocalCANIDT3 = CANIDT3;
         LocalCANIDT2 = CANIDT2;
         LocalCANIDT1 = CANIDT1;
         CANGIE = LocalCANGIE;

         sprintf(TextString,"%02X %02X   ", LocalCANIDT4, LocalCANIDT3);
         SetLCDModule(3, 0, TextString);
         sprintf(TextString,"%02X %02X   ", LocalCANIDT2, LocalCANIDT1);
         SetLCDModule(3, 1, TextString);*/

/*
         sprintf(TextString,"%02X%02X%02X%02X", LastBuffer[0][0], LastBuffer[1][0], LastBuffer[2][0], LastBuffer[3][0]);
         SetLCDModule(0, 0, TextString);
         sprintf(TextString,"%02X%02X%02X%02X", LastBuffer[4][0], LastBuffer[5][0], LastBuffer[6][0], LastBuffer[7][0]);
         SetLCDModule(0, 1, TextString);

         sprintf(TextString,"%02X%02X%02X%02X", LastBuffer[0][1], LastBuffer[1][1], LastBuffer[2][1], LastBuffer[3][1]);
         SetLCDModule(1, 0, TextString);
         sprintf(TextString,"%02X%02X%02X%02X", LastBuffer[4][1], LastBuffer[5][1], LastBuffer[6][1], LastBuffer[7][1]);
         SetLCDModule(1, 1, TextString);

         sprintf(TextString,"%02X%02X%02X%02X", LastBuffer[0][2], LastBuffer[1][2], LastBuffer[2][2], LastBuffer[3][2]);
         SetLCDModule(2, 0, TextString);
         sprintf(TextString,"%02X%02X%02X%02X", LastBuffer[4][2], LastBuffer[5][2], LastBuffer[6][2], LastBuffer[7][2]);
         SetLCDModule(2, 1, TextString);

         sprintf(TextString,"%02X%02X%02X%02X", LastBuffer[0][3], LastBuffer[1][3], LastBuffer[2][3], LastBuffer[3][3]);
         SetLCDModule(3, 0, TextString);
         sprintf(TextString,"%02X%02X%02X%02X", LastBuffer[4][3], LastBuffer[5][3], LastBuffer[6][3], LastBuffer[7][3]);
         SetLCDModule(3, 1, TextString);
*/

         /*
         for (cntModule=0; cntModule<4; cntModule++)
         {
            sprintf(TextString,"%8u", MotorSpeed[cntModule]);
            SetLCDModule(cntModule, 1, TextString);
         }*/

         //sprintf(TextString,"%8u", cntCANMob2StatusInterruptRXOK);
         //SetLCDModule(0, 0, TextString);
         //sprintf(TextString,"%8u", cntCANInterrupt);
         //SetLCDModule(0, 1, TextString);

         /*sprintf(TextString,"%4u%4u", MotorPosition[0], FaderData[0]);
         SetLCDModule(1, 0, TextString);
         sprintf(TextString,"%8u", cntCANStuffErrorGeneral);
         SetLCDModule(2, 0, TextString);
         sprintf(TextString,"%8u", cntCANCRCErrorGeneral);
         SetLCDModule(3, 0, TextString);

         sprintf(TextString,"%8u", cntCANFormErrorGeneral);
         SetLCDModule(0, 1, TextString);
         sprintf(TextString,"%8u", cntCANAcknowledgementErrorGeneral);
         SetLCDModule(1, 1, TextString);
         sprintf(TextString,"%8u", cntCANTimerOverrun);
         SetLCDModule(2, 1, TextString);
         sprintf(TextString,"%8u", cntCANMob1StatusInterrupt);
         SetLCDModule(3, 1, TextString);*/

         PreviousMilliSecond = cntMilliSecond;
      }
   }
}

void SetTLC5921DAP()
{
	unsigned char cntBit;
	unsigned char cntByte;

	for (cntByte=NR_OF_TLC5921DAP_ICS; cntByte<=NR_OF_TLC5921DAP_ICS; cntByte--)
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
   unsigned char cntRow;

   //Switch Rows
   for (cntRow=0; cntRow<5; cntRow++)
   {
      char ReturnValue;
      unsigned char LogicSwitchNr;
      unsigned char SwitchOffset;

      selectRow(cntRow);

      SwitchOffset = cntRow*8;

		ReturnValue = SwitchCheck(cntRow, 0, nSW1);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[SwitchOffset+0];
      DoSwitch(LogicSwitchNr, ReturnValue);

		ReturnValue = SwitchCheck(cntRow, 1, nSW2);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[SwitchOffset+1];
      DoSwitch(LogicSwitchNr, ReturnValue);

		ReturnValue = SwitchCheck(cntRow, 2, nSW3);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[SwitchOffset+2];
      DoSwitch(LogicSwitchNr, ReturnValue);

		ReturnValue = SwitchCheck(cntRow, 3, nSW4);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[SwitchOffset+3];
      DoSwitch(LogicSwitchNr, ReturnValue);

		ReturnValue = SwitchCheck(cntRow, 4, nSW5);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[SwitchOffset+4];
      DoSwitch(LogicSwitchNr, ReturnValue);

		ReturnValue = SwitchCheck(cntRow, 5, nSW6);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[SwitchOffset+5];
      DoSwitch(LogicSwitchNr, ReturnValue);

		ReturnValue = SwitchCheck(cntRow, 6, nSW7);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[SwitchOffset+6];
      DoSwitch(LogicSwitchNr, ReturnValue);

		ReturnValue = SwitchCheck(cntRow, 7, nSW8);
      LogicSwitchNr = SwitchNr2LogicSwitchNr[SwitchOffset+7];
      DoSwitch(LogicSwitchNr, ReturnValue);
   }

   //Encoder Row
   //selectRow(5);
}

void ReadEncoders()
{
   char cntEncoder;
   unsigned char EncoderABStatusChanged;

   //Encoder Row
   selectRow(5);

	//Check Encoder
	EncoderABStatus = PINA;
	EncoderABStatusChanged = PreviousEncoderABStatus^EncoderABStatus;
	PreviousEncoderABStatus = EncoderABStatus;

	for (cntEncoder=0; cntEncoder<4; cntEncoder++)
	{
	   unsigned char Mask = 0x01<<(2*cntEncoder);

   	if (EncoderABStatusChanged&Mask)
     	{ 	//Pulse Change
   		if ((EncoderABStatus&Mask) != ((EncoderABStatus>>1)&Mask))
   		{  //Up
   		   unsigned int Difference;

   		   Difference = cntMilliSecond - EncoderPreviousUpTime[cntEncoder];

            //EncoderPosition[cntEncoder] = cntMilliSecond;
            //EncoderPosition[cntEncoder+1] = EncoderPreviousUpTime[cntEncoder];
            //EncoderPosition[cntEncoder+2] = Difference;
            //EncoderPosition[cntEncoder+3] = cntMilliSecond - EncoderPreviousUpTime[cntEncoder];

            EncoderPreviousUpTime[cntEncoder] = cntMilliSecond;

      	   if (Difference < 50)
      	   {
           	 	EncoderPosition[cntEncoder]+=5;
      	   }
      	   else if (Difference < 100)
      	   {
           	 	EncoderPosition[cntEncoder]+=2;
      	   }
      	   else
      	   {
           	 	EncoderPosition[cntEncoder]++;
      	   }

   		}
   		else
   		{  //Down
      		unsigned int Difference;

      		Difference = cntMilliSecond-EncoderPreviousDownTime[cntEncoder];
         	EncoderPreviousDownTime[cntEncoder] = cntMilliSecond;

            //EncoderPosition[cntEncoder] = cntMilliSecond;
            //EncoderPosition[cntEncoder+1] = EncoderPreviousUpTime[cntEncoder];
            //EncoderPosition[cntEncoder+2] = Difference;
            //EncoderPosition[cntEncoder+3] = cntMilliSecond - EncoderPreviousUpTime[cntEncoder];

            if (Difference < 50)
            {
         		EncoderPosition[cntEncoder]-=5;
         	}
         	else if (Difference < 100)
         	{
         		EncoderPosition[cntEncoder]-=2;
         	}
         	else
         	{
         		EncoderPosition[cntEncoder]--;
         	}
   		}
   	}
   }
}

void ReadFaders()
{
   int Difference;
	unsigned char cntTrack;

	for (cntTrack=0; cntTrack<4; cntTrack++)
	{
      Difference = PreviousADC_Data[cntTrack]-adc_data[cntTrack];
      if (abs(Difference)>FADER_WIBBLE)
      {
   		FaderPosition[cntTrack] = adc_data[cntTrack];

   		PreviousADC_Data[cntTrack] = adc_data[cntTrack];
		}
	}
}

void DoSwitch(unsigned char LogicSwitchNr, int Event)
{
   if ((Event == 1) || (Event == -1))
   {
      unsigned char TransmitBuffer[1];
      unsigned int ObjectNr;
      int ModuleNr;
      int SwitchNr;

      ObjectNrInformationCount = 0;
      LastObjectInformationRequested = 0;


      ModuleNr = LogicSwitchNr/9;
      SwitchNr = LogicSwitchNr%9;
      ObjectNr = 1036+ModuleNr+(SwitchNr<<2);
      TransmitBuffer[0] = 0;
      if (Event == 1)
      {
         TransmitBuffer[0] = 1;
      }

      SwitchState[ModuleNr+(SwitchNr<<2)] = TransmitBuffer[0];

      SendSensorChangeToMambaNet(ObjectNr, STATE_DATATYPE, 1, TransmitBuffer);
    }

   if (Event == 1)
   {	//ON
/*    sprintf(TextString, "Sw%2d On ", LogicSwitchNr%9);
      SetLCDModule(LogicSwitchNr/9, 1, TextString);

      cntLEDDebug++;
      if (cntLEDDebug>=80)
      {
         cntLEDDebug=0;
      }
      sprintf(TextString, "LED: %2d ", cntLEDDebug);
      SetLCDModule(3, 0, TextString);
*/
/*      switch (LogicSwitchNr)
      {
         case 0:
         {
            //Debug
            //CANGIE &= 0x7F;
         }
         break;
         case 7:
         {
            PreviousMotorPosition[0] = FaderData[0];
            MotorPosition[0] = 790;
         }
         break;
         case 8:
         {
            PreviousMotorPosition[0] = FaderData[0];
            MotorPosition[0] = 160;
         }
         break;
         case 16:
         {
            PreviousMotorPosition[1] = FaderData[1];
            MotorPosition[1] = 790;
         }
         break;
         case 17:
         {
            PreviousMotorPosition[1] = FaderData[1];
            MotorPosition[1] = 160;
         }
         break;
         case 25:
         {
            PreviousMotorPosition[2] = FaderData[2];
            MotorPosition[2] = 790;
         }
         break;
         case 26:
         {
            PreviousMotorPosition[2] = FaderData[2];
            MotorPosition[2] = 160;
         }
         break;
         case 34:
         {
            PreviousMotorPosition[3] = FaderData[3];
            MotorPosition[3] = 790;
         }
         break;
         case 35:
         {
            PreviousMotorPosition[3] = FaderData[3];
            MotorPosition[3] = 160;
         }
         break;
      }*/
   }
	else if (Event == -1)
	{	//OFF
      /*
      sprintf(TextString, "Sw%2d Off", LogicSwitchNr%9);
      SetLCDModule(LogicSwitchNr/9, 1, TextString);
      */
      /*
      switch (LogicSwitchNr)
      {
         case 0:
         {
         }
         break;
         case 7:
         {
         }
         break;
         case 8:
         {
         }
         break;
         case 16:
         {
         }
         break;
         case 17:
         {
         }
         break;
         case 25:
         {
         }
         break;
         case 26:
         {
         }
         break;
         case 34:
         {
         }
         break;
         case 35:
         {
         }
         break;
      }
      */
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

void ReadTouch()
{
   char cntModule;

   CurrentTouch[0] = TOUCH1;
   CurrentTouch[1] = TOUCH2;
   CurrentTouch[2] = TOUCH3;
   CurrentTouch[3] = TOUCH4;

   for (cntModule=0; cntModule<4; cntModule++)
   {
      if (PreviousTouch[cntModule] != CurrentTouch[cntModule])
      {
        unsigned char TransmitBuffer[1];
        unsigned int ObjectNr;

        ObjectNr = 1108+cntModule;

        TransmitBuffer[0] = CurrentTouch[cntModule];

        SendSensorChangeToMambaNet(ObjectNr, STATE_DATATYPE, 1, TransmitBuffer);

        PreviousTouch[cntModule] = CurrentTouch[cntModule];
      }
   }
}

void ControlMotors()
{
   int Difference;
   int PartDone;
   int TotalMove;
   char cntModule;
   unsigned int PWMValue;

   for (cntModule=0; cntModule<4; cntModule++)
   {
      Difference = MotorPosition[cntModule]-FaderPosition[cntModule];

      if ( (Difference<0) != Direction[cntModule])
      {
         Direction[cntModule] = (Difference<0);
         MotorSpeed[cntModule] = MinPWMSpeed;
      }

      if (abs(Difference)>MOTOR_POSITION_DEADZONE)
      {
         if (PreviousDifference[cntModule] == Difference)
         {
            MotorSpeed[cntModule] += StepSizeUp;
            if (MotorSpeed[cntModule] > MaxPWMSpeed)
            {
               MotorSpeed[cntModule] = MaxPWMSpeed;
            }
         }
         else
         {
            TotalMove = MotorPosition[cntModule] - PreviousMotorPosition[cntModule];
            PartDone = ((long)Difference*100)/TotalMove;

            if (PartDone > 50)
            {
               MotorSpeed[cntModule]+=StepSizeUp;
               if (MotorSpeed[cntModule] > MaxPWMSpeed)
               {
                  MotorSpeed[cntModule] = MaxPWMSpeed;
               }
            }
            else
            {
               MotorSpeed[cntModule]-=StepSizeDown;
               if (MotorSpeed[cntModule] < MinPWMSpeed)
               {
                  MotorSpeed[cntModule] = MinPWMSpeed;
               }
            }
         }
      }
      else
      {
         MotorSpeed[cntModule] = MinPWMSpeed;
      }
      PreviousDifference[cntModule] = Difference;
   }

   if (CurrentTouch[0])
   {
      MotorPosition[0] = FaderPosition[0];
      if (PWM_M1_B)
      {
         OCR3AH=0xFF;
         OCR3AL=0xFF;
      }
      else
      {
         OCR3AH=0x00;
         OCR3AL=0x00;
      }
   }
   else
   {
      if (MotorActive[0])
      {
         Difference = MotorPosition[0]-FaderPosition[0];
         if (Difference>MOTOR_POSITION_DEADZONE)
         {
            PWMValue = MotorSpeed[0];
            PWMValue ^= 0xFFFF;

            OCR3AH=(PWMValue>>8)&0xFF;
            OCR3AL=PWMValue&0xFF;
            PWM_M1_B = 1;
         }
         else if (Difference<-MOTOR_POSITION_DEADZONE)
         {
            PWMValue = MotorSpeed[0];

            OCR3AH=(PWMValue>>8)&0xFF;
            OCR3AL=PWMValue&0xFF;
            PWM_M1_B = 0;
         }
         else
         {  //Motor off
            //MotorActive[0] = 0;
            if (PWM_M1_B)
            {
               OCR3AH=0xFF;
               OCR3AL=0xFF;
            }
            else
            {
               OCR3AH=0x00;
               OCR3AL=0x00;
            }
            //Also make fader positions equal, so its not going to transmit if motor is active
            PreviousFaderPosition[0] = FaderPosition[0];
         }
      }
      else
      {  //Motor off
         if (PWM_M1_B)
         {
            OCR3AH=0xFF;
            OCR3AL=0xFF;
         }
         else
         {
            OCR3AH=0x00;
            OCR3AL=0x00;
         }
      }
   }

   if (CurrentTouch[1])
   {
      MotorPosition[1] = FaderPosition[1];
      if (PWM_M2_B)
      {
         OCR3BH=0xFF;
         OCR3BL=0xFF;
      }
      else
      {
         OCR3BH=0x00;
         OCR3BL=0x00;
      }
   }
   else
   {
      if (MotorActive[1])
      {
         Difference = MotorPosition[1]-FaderPosition[1];
         if (Difference>MOTOR_POSITION_DEADZONE)
         {
            PWMValue = MotorSpeed[1];
            PWMValue ^= 0xFFFF;

            OCR3BH=(PWMValue>>8)&0xFF;
            OCR3BL=PWMValue&0xFF;
            PWM_M2_B = 1;
         }
         else if (Difference<-MOTOR_POSITION_DEADZONE)
         {
            PWMValue = MotorSpeed[1];

            OCR3BH=(PWMValue>>8)&0xFF;
            OCR3BL=PWMValue&0xFF;
            PWM_M2_B = 0;
         }
         else
         {  //motor off
            //MotorActive[1] = 0;
            if (PWM_M2_B)
            {
               OCR3BH=0xFF;
               OCR3BL=0xFF;
            }
            else
            {
               OCR3BH=0x00;
               OCR3BL=0x00;
            }
            //Also make fader positions equal, so its not going to transmit if motor is active
            PreviousFaderPosition[1] = FaderPosition[1];
         }
      }
      else
      {  //motor off
         if (PWM_M2_B)
         {
            OCR3BH=0xFF;
            OCR3BL=0xFF;
         }
         else
         {
            OCR3BH=0x00;
            OCR3BL=0x00;
         }
      }
   }

   if (CurrentTouch[2])
   {
      MotorPosition[2] = FaderPosition[2];

      if (PWM_M3_B)
      {
         OCR1AH=0xFF;
         OCR1AL=0xFF;
      }
      else
      {
         OCR1AH=0x00;
         OCR1AL=0x00;
      }
   }
   else
   {
      if (MotorActive[2])
      {
         Difference = MotorPosition[2]-FaderPosition[2];
         if (Difference>MOTOR_POSITION_DEADZONE)
         {
            PWMValue = MotorSpeed[2];
            PWMValue ^= 0xFFFF;

            OCR1AH=(PWMValue>>8)&0xFF;
            OCR1AL=PWMValue&0xFF;
            PWM_M3_B = 1;
         }
         else if (Difference<-MOTOR_POSITION_DEADZONE)
         {
            PWMValue = MotorSpeed[2];

            OCR1AH=(PWMValue>>8)&0xFF;
            OCR1AL=PWMValue&0xFF;
            PWM_M3_B = 0;
         }
         else
         {  //Motor off
            //MotorActive[2] = 0;
            if (PWM_M3_B)
            {
               OCR1AH=0xFF;
               OCR1AL=0xFF;
            }
            else
            {
               OCR1AH=0x00;
               OCR1AL=0x00;
            }
            //Also make fader positions equal, so its not going to transmit if motor is active
            PreviousFaderPosition[2] = FaderPosition[2];
         }
      }
      else
      {  //Motor off
         if (PWM_M3_B)
         {
            OCR1AH=0xFF;
            OCR1AL=0xFF;
         }
         else
         {
            OCR1AH=0x00;
            OCR1AL=0x00;
         }
      }
   }

   if (CurrentTouch[3])
   {
      MotorPosition[3] = FaderPosition[3];

      if (PWM_M4_B)
      {
         OCR1BH=0xFF;
         OCR1BL=0xFF;
      }
      else
      {
         OCR1BH=0x00;
         OCR1BL=0x00;
      }
   }
   else
   {
      if (MotorActive[3])
      {
         Difference = MotorPosition[3]-FaderPosition[3];
         if (Difference>MOTOR_POSITION_DEADZONE)
         {
            PWMValue = MotorSpeed[3];
            PWMValue ^= 0xFFFF;

            OCR1BH=(PWMValue>>8)&0xFF;
            OCR1BL=PWMValue&0xFF;
            PWM_M4_B = 1;
         }
         else if (Difference<-MOTOR_POSITION_DEADZONE)
         {
            PWMValue = MotorSpeed[3];

            OCR1BH=(PWMValue>>8)&0xFF;
            OCR1BL=PWMValue&0xFF;
            PWM_M4_B = 0;
         }
         else
         {  //Motor off
            //MotorActive[3] = 0;
            if (PWM_M4_B)
            {
               OCR1BH=0xFF;
               OCR1BL=0xFF;
            }
            else
            {
               OCR1BH=0x00;
               OCR1BL=0x00;
            }
            //Also make fader positions equal, so its not going to transmit if motor is active
            PreviousFaderPosition[3] = FaderPosition[3];
         }
      }
      else
      {  //Motor off
         if (PWM_M4_B)
         {
            OCR1BH=0xFF;
            OCR1BL=0xFF;
         }
         else
         {
            OCR1BH=0x00;
            OCR1BL=0x00;
         }
      }
   }
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
               unsigned char TransmitBuffer[21];

               TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
               TransmitBuffer[1] = ObjectNr&0xFF;
               TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;

               if ((ObjectNr>=1032) && (ObjectNr<1036))
               {  //Encoder
                  TransmitBuffer[3] = SIGNED_INTEGER_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = 0;
                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1036) && (ObjectNr<1072))
               {  //Switches
                  char SwitchNr = ObjectNr-1036;
                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = SwitchState[SwitchNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1104) && (ObjectNr<1108))
               {  //FaderPosition
                  char ModuleNr = (ObjectNr-1104)&0x03;

                  TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                  TransmitBuffer[4] = 2;
                  TransmitBuffer[5] = (FaderPosition[ModuleNr]>>8)&0xFF;
                  TransmitBuffer[6] = (FaderPosition[ModuleNr]&0xFF);

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 7);

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
            case  MAMBANET_OBJECT_ACTION_GET_ACTUATOR_DATA:
            {       //Net yet implemented.
               unsigned char TransmitBuffer[23];

               TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
               TransmitBuffer[1] = ObjectNr&0xFF;
               TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE;

               if ((ObjectNr>=1024) && (ObjectNr<1032))
               {  //LCD
                  unsigned char DisplayNr = ObjectNr-1024;

                  TransmitBuffer[3] = OCTET_STRING_DATATYPE;
                  TransmitBuffer[4] = 8;
                  TransmitBuffer[5] = LCDTextString[DisplayNr][0];
                  TransmitBuffer[6] = LCDTextString[DisplayNr][1];
                  TransmitBuffer[7] = LCDTextString[DisplayNr][2];
                  TransmitBuffer[8] = LCDTextString[DisplayNr][3];
                  TransmitBuffer[9] = LCDTextString[DisplayNr][4];
                  TransmitBuffer[10] = LCDTextString[DisplayNr][5];
                  TransmitBuffer[11] = LCDTextString[DisplayNr][6];
                  TransmitBuffer[12] = LCDTextString[DisplayNr][7];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 13);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1040) && (ObjectNr<1056))
               {  //Switches with a single LED
                  char TemporySwitchNr = ObjectNr-1040;
                  char ModuleNr = TemporySwitchNr&0x03;
                  char LEDNr = (TemporySwitchNr>>2) + (ModuleNr*20);
                  char ByteNr = LEDNr>>3;
                  char Mask = 0x01<<(LEDNr&0x7);

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  if (LogicLEDData[ByteNr]&Mask)
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
               else if ((ObjectNr>=1056) && (ObjectNr<1072))
               {  //Switches with a bicolor LED
                  char TemporySwitchNr = ObjectNr-1056;
                  char ModuleNr = TemporySwitchNr&0x03;
                  char LEDNr = (4+((TemporySwitchNr>>1)&0xFE)) + (ModuleNr*20);
                  char ByteNr;
                  char Mask;
                  char TransmitLength;

                  if (ObjectNr >= 1064)
                  {
                     LEDNr+=8;
                  }
                  ByteNr = LEDNr>>3;

                  Mask = (0x03<<(LEDNr&0x7));

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = DualColorSwitchState[ModuleNr][TemporySwitchNr/4];
                  TransmitLength = 6;

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, TransmitLength);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1072) && (ObjectNr<1104))
               {  //LEDs
                  char TemporySwitchNr = ObjectNr-1072;
                  char ModuleNr = TemporySwitchNr&0x03;
                  char LEDNr = (8+(TemporySwitchNr>>2)) + (ModuleNr*20);
                  char ByteNr = LEDNr>>3;
                  char Mask = 0x01<<(LEDNr&0x7);

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  if (LogicLEDData[ByteNr]&Mask)
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
               else if ((ObjectNr>=1104) && (ObjectNr<1108))
               {  //MotorPosition
                  char ModuleNr = (ObjectNr-1104)&0x03;

                  TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                  TransmitBuffer[4] = 2;
                  TransmitBuffer[5] = (MotorPosition[ModuleNr]>>8)&0xFF;
                  TransmitBuffer[6] = (MotorPosition[ModuleNr]&0xFF);

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 7);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1112) && (ObjectNr<1128))
               {  //on color
                  char TemporySwitchNr = ObjectNr-1112;
                  char ModuleNr = TemporySwitchNr&0x03;
                  char SwitchNr = TemporySwitchNr/4;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = SwitchColorOn[ModuleNr][SwitchNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1128) && (ObjectNr<1144))
               {  //off Color
                  char TemporySwitchNr = ObjectNr-1128;
                  char ModuleNr = TemporySwitchNr&0x03;
                  char SwitchNr = TemporySwitchNr/4;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = SwitchColorOff[ModuleNr][SwitchNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

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

               if ((ObjectNr>=1024) && (ObjectNr<1032))
               {  //LCD
                  if (DataType == OCTET_STRING_DATATYPE)
                  {
                     if (DataSize<=8)
                     {
                        char cntChar;
                        unsigned char DisplayNr = ObjectNr-1024;

                        for (cntChar=0; cntChar<(8-DataSize); cntChar++)
                        {
                           LCDTextString[DisplayNr][cntChar] = ' ';
                        }
                        for (cntChar=(8-DataSize); cntChar<8; cntChar++)
                        {
                           LCDTextString[DisplayNr][cntChar] = Data[5+cntChar-(8-DataSize)];
                           if ((LCDTextString[DisplayNr][cntChar]<0x20) || (LCDTextString[DisplayNr][cntChar] > 0x7E))
                           {
                              LCDTextString[DisplayNr][cntChar] = ' ';
                           }
                        }
                        LCDTextString[DisplayNr][8] = 0;

                        if (ObjectNr<1028)
                        {
                           SetLCDModule(ObjectNr-1024, 0, LCDTextString[DisplayNr]);
                        }
                        else
                        {
                           SetLCDModule(ObjectNr-1028, 1, LCDTextString[DisplayNr]);
                        }

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1040) && (ObjectNr<1056))
               {  //Switches with a single LED
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        char TemporySwitchNr = ObjectNr-1040;
                        char ModuleNr = TemporySwitchNr&0x03;
                        char LEDNr = (TemporySwitchNr>>2) + (ModuleNr*20);
                        char ByteNr = LEDNr>>3;
                        char Mask = 0x01<<(LEDNr&0x7);

                        if (Data[5])
                        {
                           LogicLEDData[ByteNr] |= Mask;
                        }
                        else
                        {
                           LogicLEDData[ByteNr] &= Mask^0xFF;
                        }
                        DoSetLEDs = 1;
                        //SetLEDs();

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1056) && (ObjectNr<1072))
               {  //Switches with a bicolor LED
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        char TemporySwitchNr = ObjectNr-1056;
                        char ModuleNr = TemporySwitchNr&0x03;
                        char LEDNr = (4+((TemporySwitchNr>>1)&0xFE)) + (ModuleNr*20);
                        char ByteNr;
                        char Mask;
                        char MaskOff;

                        if (ObjectNr >= 1064)
                        {
                          LEDNr+=8;
                        }
                        ByteNr = LEDNr>>3;

                        MaskOff = (0x03<<(LEDNr&0x7))^0xFF;

                        DualColorSwitchState[ModuleNr][TemporySwitchNr/4] = Data[5];
                        if (Data[5])
                        {
                           Mask = SwitchColorOn[ModuleNr][TemporySwitchNr/4]<<(LEDNr&0x7);
                        }
                        else
                        {
                           Mask = SwitchColorOff[ModuleNr][TemporySwitchNr/4]<<(LEDNr&0x7);
                        }
                        LogicLEDData[ByteNr] &= MaskOff;
                        LogicLEDData[ByteNr] |= Mask;
                        DoSetLEDs = 1;
                        //SetLEDs();

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1072) && (ObjectNr<1104))
               {  //LEDs
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        char TemporySwitchNr = ObjectNr-1072;
                        char ModuleNr = TemporySwitchNr&0x03;
                        char LEDNr = (8+(TemporySwitchNr>>2)) + (ModuleNr*20);
                        char ByteNr = LEDNr>>3;
                        char Mask = 0x01<<(LEDNr&0x7);

                        if (Data[5])
                        {
                           LogicLEDData[ByteNr] |= Mask;
                        }
                        else
                        {
                           LogicLEDData[ByteNr] &= Mask^0xFF;
                        }

                        DoSetLEDs=1;
                        //SetLEDs();

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1104) && (ObjectNr<1108))
               {
                  if (DataType == UNSIGNED_INTEGER_DATATYPE)
                  {
                     if (DataSize == 2)
                     {
                        char ModuleNr = (ObjectNr-1104)&0x03;

                        PreviousMotorPosition[ModuleNr] = FaderPosition[ModuleNr];
                        MotorPosition[ModuleNr] = ((unsigned int)Data[5]<<8) | Data[6];
                        if (!MoveByFader[ModuleNr])
                        {
                          MotorActive[ModuleNr] = 20;
                        }

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1112) && (ObjectNr<1128))
               {  //Set on olor
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        char TemporySwitchNr = ObjectNr-1112;
                        char ModuleNr = TemporySwitchNr&0x03;
                        char SwitchNr = TemporySwitchNr/4;
                        char LEDNr = (4+((TemporySwitchNr>>1)&0xFE)) + (ModuleNr*20);
                        char ByteNr;
                        char Mask;
                        char MaskOff;

                        if (ObjectNr >= 1120)
                        {
                           LEDNr+=8;
                        }
                        ByteNr = LEDNr>>3;

                        Mask = (0x03<<(LEDNr&0x7));

                        SwitchColorOn[ModuleNr][SwitchNr] = Data[5];
                        if (SwitchColorOn[ModuleNr][SwitchNr]>3)
                        {
                           SwitchColorOn[ModuleNr][SwitchNr] = 3;
                        }

                        MaskOff = (0x03<<(LEDNr&0x7))^0xFF;
                        if (DualColorSwitchState[ModuleNr][TemporySwitchNr/4])
                        {
                           Mask = SwitchColorOn[ModuleNr][SwitchNr]<<(LEDNr&0x7);
                        }
                        else
                        {
                           Mask = SwitchColorOff[ModuleNr][SwitchNr]<<(LEDNr&0x7);
                        }
                        LogicLEDData[ByteNr] &= MaskOff;
                        LogicLEDData[ByteNr] |= Mask;
                        DoSetLEDs=1;
                        //SetLEDs();

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1128) && (ObjectNr<1144))
               {  //Set off Color
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        char TemporySwitchNr = ObjectNr-1128;
                        char ModuleNr = TemporySwitchNr&0x03;
                        char SwitchNr = TemporySwitchNr/4;
                        char LEDNr = (4+((TemporySwitchNr>>1)&0xFE)) + (ModuleNr*20);
                        char ByteNr;
                        char Mask;
                        char MaskOff;

                        if (ObjectNr >= 1136)
                        {
                           LEDNr+=8;
                        }
                        ByteNr = LEDNr>>3;

                        Mask = (0x03<<(LEDNr&0x7));

                        SwitchColorOff[ModuleNr][SwitchNr] = Data[5];
                        if (SwitchColorOff[ModuleNr][SwitchNr]>3)
                        {
                           SwitchColorOff[ModuleNr][SwitchNr] = 3;
                        }

                        MaskOff = (0x03<<(LEDNr&0x7))^0xFF;
                        if (DualColorSwitchState[ModuleNr][TemporySwitchNr/4])
                        {
                           Mask = SwitchColorOn[ModuleNr][SwitchNr]<<(LEDNr&0x7);
                        }
                        else
                        {
                           Mask = SwitchColorOff[ModuleNr][SwitchNr]<<(LEDNr&0x7);
                        }
                        LogicLEDData[ByteNr] &= MaskOff;
                        LogicLEDData[ByteNr] |= Mask;
                        DoSetLEDs=1;
                        //SetLEDs();

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
}

void CanBussError()
{
   AddressValidated = 0;
   timerReservationInfo = 1;
}
