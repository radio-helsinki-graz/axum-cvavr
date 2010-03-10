/*****************************************************
This program was produced by the
CodeWizardAVR V1.25.3 Standard
Automatic Program Generator
© Copyright 1998-2007 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Axum-Rack-Hybrid
Version :
Date    : 3-10-2008
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
#include <string.h>

#include "Axum-Rack-Hybrid.h"
#include "CANTransportLayer.h"
#include "Axum-Rack-Hybrid-MambaNet.h"
// I2C Bus functions
#asm
   .equ __i2c_port=0x0B ;PORTD
   .equ __sda_bit=1
   .equ __scl_bit=0
#endasm
#include <i2c.h>

unsigned char cntDebug;

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

void CMX865AInterrupt(unsigned char cntChip)
{
  unsigned int Test = ReadCMX865A(cntChip, 0xE6);

  StatusCMX865A[cntChip] = Test;
  SetStatusCMX865A[cntChip] = 1;

  switch(DetectMode[cntChip])
  {
    case IDLE_MODE:
    {
      if (Test&0x0040)
      { //Go to DTMF
        DetectMode[cntChip] = DTMF_MODE;
        SetCMX865A(cntChip, 0xE2, 0x1E01);//first set DTMF detect
        SetCMX865A(cntChip, 0xE0, 0x8141);//interrupt on DTMF tone
      }
      else if (Test&0x0080)
      {
        DetectMode[cntChip] = BT_FSK_MODE;
        FSKState[cntChip] = 1;
        SetCMX865A(cntChip, 0xE2, 0x1E04);//detect programmed tones
        SetCMX865A(cntChip, 0xE0, 0x8142);//only second programmed tone
      }
    }
    break;
    case DTMF_MODE:
    {
      if (Test&0x0020)
      { //DTMF detect
        char Digit = DTMFTable[Test&0x000F];

        ReceivedDTMFData[cntChip][ReceivedPtr[cntChip]++] = Digit;
        if (((ReceivedDTMFData[cntChip][0] == 'D') && ((Digit == 'C') || (Digit == '#'))) ||
            ((ReceivedDTMFData[cntChip][0] == 'A') && (Digit == '#')))
        { //Last received
          ReceivedDTMFData[cntChip][ReceivedPtr[cntChip]] = 0;
          strncpy(CallerID[cntChip], ReceivedDTMFData[cntChip], 64);
          CallerIDLength[cntChip] = strlen(CallerID[cntChip]);
          NewCallerIDSet[cntChip] = 1;

          ReceivedPtr[cntChip] = 0;
          //After DTMF we always start with the first ring
          RingCount[cntChip] = 0;
        }
      }
    }
    break;
    case BELL_FSK_MODE:
    {
      switch (FSKState[cntChip])
      {
        case 1:
        {
          if ((Test&0x0600) == 0x0600)
          { //Programmed channel seizure
            FSKState[cntChip] = 2;
          }
        }
        break;
        case 2:
        {
          if ((Test&0x0600) == 0x0400)
          { //channel seizure ends
            FSKState[cntChip] = 3;
            if ((Test&0x0580) == 0x0480)
            { //channel seizure ends
              FSKState[cntChip] = 4;
              ContinuousMarkTimer[cntChip] = cntMilliSecond;
            }
          }
        }
        break;
        case 3:
        {
          if ((Test&0x0580) == 0x0480)
          { //channel seizure ends
            FSKState[cntChip] = 4;
            ContinuousMarkTimer[cntChip] = cntMilliSecond;
          }
        }
        break;
        case 5:
        {
          if ((Test&0x0470) == 0x440)
          { //RxData
            FSKData[cntChip][FSKPtr[cntChip]++] = ReadByteCMX865A(cntChip, 0xE5);
            if (FSKPtr[cntChip] == 2)
            {
              if ((FSKData[cntChip][0] == 0x80) && (FSKPtr[cntChip] == 2))
              {
                FSKDataLength[cntChip] = FSKData[cntChip][1]+3;
              }
            }
            if (FSKPtr[cntChip] == FSKDataLength[cntChip])
            {
              unsigned char FSKLength = FSKPtr[cntChip];
              if (FSKLength>64)
              {
                FSKLength = 64;
              }
              memcpy(CallerID[cntChip], FSKData[cntChip], FSKLength);
              CallerIDLength[cntChip] = FSKLength;
              NewCallerIDSet[cntChip] = 1;
            }
          }
          else
          { //Data error
            if (Test&0x0020)
            { //Overrun
              FSKData[cntChip][FSKPtr[cntChip]++] = ReadByteCMX865A(cntChip, 0xE5);
            }
          }
        }
        break;
      }
    }
    break;
    case BT_FSK_MODE:
    {
      switch (FSKState[cntChip])
      {
        case 2:
        {
          if ((Test&0x0600) == 0x0600)
          { //Programmed channel seizure
            FSKState[cntChip] = 3;
          }
        }
        break;
        case 3:
        {
          if ((Test&0x0680) == 0x0480)
          { //channel seizure ends + continuous mark found
            FSKState[cntChip] = 4;
            SetCMX865A(cntChip, 0xE2, 0x5E36);//set progammed tone detect
            SetCMX865A(cntChip, 0xE0, 0x8141);//interrupt on Rx Data
            FSKPtr[cntChip] = 0;
          }
        }
        break;
        case 4:
        {
          if ((Test&0x0470) == 0x440)
          { //RxData
            FSKData[cntChip][FSKPtr[cntChip]++] = ReadByteCMX865A(cntChip, 0xE5);
            if (FSKPtr[cntChip] == 2)
            {
              if ((FSKData[cntChip][0] == 0x80) && (FSKPtr[cntChip] == 2))
              {
                FSKDataLength[cntChip] = FSKData[cntChip][1]+3;
              }
            }
            if (FSKPtr[cntChip] == FSKDataLength[cntChip])
            {
              unsigned char FSKLength = FSKPtr[cntChip];
              if (FSKLength>64)
              {
                FSKLength = 64;
              }
              memcpy(CallerID[cntChip], FSKData[cntChip], FSKLength);
              CallerIDLength[cntChip] = FSKLength;
              NewCallerIDSet[cntChip] = 1;
            }
          }
          else
          { //Data error
            if (Test&0x0020)
            { //Overrun
              FSKData[cntChip][FSKPtr[cntChip]++] = ReadByteCMX865A(cntChip, 0xE5);
            }
          }
        }
        break;
      }
    }
    break;
  }
}

// External Interrupt 4 service routine
interrupt [EXT_INT4] void ext_int4_isr(void)
{
  CMX865AInterrupt(0);
}

// External Interrupt 5 service routine
interrupt [EXT_INT5] void ext_int5_isr(void)
{
  CMX865AInterrupt(1);
}

// External Interrupt 6 service routine
interrupt [EXT_INT6] void ext_int6_isr(void)
{
  CMX865AInterrupt(2);
}

// External Interrupt 7 service routine
interrupt [EXT_INT7] void ext_int7_isr(void)
{
  CMX865AInterrupt(3);
}

// Declare your global variables here
void CheckPF(unsigned char cntChip)
{
  unsigned int Test = ReadCMX865A(cntChip, 0xE6);
  while (!(Test&0x2000))
  {
    Test = ReadCMX865A(cntChip, 0xE6);
  }
}

void main(void)
{
   char cntByte;
   unsigned char cntChip;

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
   // Func7=In Func6=In Func5=Out Func4=Out Func3=In Func2=In Func1=Out Func0=Out
   // State7=T State6=T State5=1 State4=1 State3=T State2=T State1=1 State0=1
   PORTA=0x22;
   DDRA=0x33;

   // Port B initialization
   // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=Out Func1=Out Func0=Out
   // State7=T State6=T State5=T State4=T State3=T State2=0 State1=0 State0=1
   PORTB=0x01;
   DDRB=0x07;

   // Port C initialization
   // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=Out Func1=Out Func0=In
   // State7=T State6=T State5=T State4=T State3=T State2=0 State1=0 State0=T
   PORTC=0x00;
   DDRC=0x06;

   // Port D initialization
   // Func7=In Func6=In Func5=In Func4=Out Func3=In Func2=Out Func1=Out Func0=Out
   // State7=0 State6=T State5=0 State4=1 State3=T State2=0 State1=1 State0=1
   PORTD=0x13;
   DDRD=0x3F;

   // Port E initialization
   // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=Out Func0=Out
   // State7=P State6=P State5=P State4=P State3=0 State2=0 State1=1 State0=1
   PORTE=0xF0;
   DDRE=0x03;

   // Port F initialization
   // Func7=In Func6=In Func5=Out Func4=Out Func3=In Func2=In Func1=Out Func0=Out
   // State7=T State6=T State5=1 State4=1 State3=T State2=T State1=1 State0=1
   PORTF=0x22;
   DDRF=0x33;

   // Port G initialization
   // Func4=In Func3=Out Func2=Out Func1=Out Func0=Out
   // State4=T State3=0 State2=0 State1=0 State0=0
   PORTG=0x07;
   DDRG=0x0F;

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
  // INT4: On
  // INT4 Mode: Falling Edge
  // INT5: On
  // INT5 Mode: Falling Edge
  // INT6: On
  // INT6 Mode: Falling Edge
  // INT7: On
  // INT7 Mode: Falling Edge
  EICRA=0x00;
  EICRB=0xAA;
  EIMSK=0xF0;
  EIFR=0xF0;

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

   // I2C Bus initialization
   i2c_init();

   PORTE |= 0xF0;
   delay_us(100);
   HardwareMinorRevision = (PINE&0xF0)>>4;
   PORTE &= 0x0F;

   for (cntChip=0; cntChip<4; cntChip++)
   {
     ResetCMX865A(cntChip);
     delay_ms(200);
     SetCMX865A(cntChip, 0xE0, 0x81C0);
   }
   delay_ms(200);

   for (cntChip=0; cntChip<4; cntChip++)
   {
     unsigned int Test;
     SetCMX865A(cntChip, 0xE0, 0x81C0);
     SetCMX865A(cntChip, 0xE0, 0x8140);//0x8141

     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 32769);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 0);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 400);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 32368);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 7726);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 25108);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 0);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 400);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 32368);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 7726);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 25108);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 35);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 195);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 216);
     CheckPF(cntChip);

     SetCMX865A(cntChip, 0xE8, 0);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 320);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 32448);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 7676);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 3603);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 0);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 320);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 32448);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 7676);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 3603);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 55);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 182);
     CheckPF(cntChip);
     SetCMX865A(cntChip, 0xE8, 202);
     CheckPF(cntChip);

/*
1633Hz
 Register Word 2 or 15 = 0
 Register Word 3 or 16 = 400
 Register Word 4 or 17 = 32368
 Register Word 5 or 18 = 7726
 Register Word 6 or 19 = 25108
 Register Word 7 or 20 = 0
 Register Word 8 or 21 = 400
 Register Word 9 or 22 = 32368
 Register Word 10 or 23 = 7726
 Register Word 11 or 24 = 25108
 Register Word 12 or 25 = 35
 Register Word 13 or 26 = 195
 Register Word 14 or 27 = 216


2750Hz
 Register Word 2 or 15 = 0
 Register Word 3 or 16 = 320
 Register Word 4 or 17 = 32448
 Register Word 5 or 18 = 7676
 Register Word 6 or 19 = 3603
 Register Word 7 or 20 = 0
 Register Word 8 or 21 = 320
 Register Word 9 or 22 = 32448
 Register Word 10 or 23 = 7676
 Register Word 11 or 24 = 3603
 Register Word 12 or 25 = 55
 Register Word 13 or 26 = 182
 Register Word 14 or 27 = 202
*/

     DetectMode[cntChip] = IDLE_MODE;
     SetCMX865A(cntChip, 0xE0, 0x8143);//interrupt on programmed tones
     SetCMX865A(cntChip, 0xE1, 0x1000);
     SetCMX865A(cntChip, 0xE2, 0x1E04);//detect programmed tones

     OffHookTimerEnabled[cntChip] = 0;
     OffHookTimer[cntChip] = 0;
     PreviousOffHookState[cntChip] = 0;
     OffHookState[cntChip] = 0;
     LastDialedNumber[cntChip][0] = 0;
     DialPtr[cntChip] = 32;
     ReceivedDTMFData[cntChip][0] = 0;
     ReceivedPtr[cntChip] = 0;

     DTMFTimerDelay[cntChip] = 0;
     DTMFTimer[cntChip] = 0;
     DTMFSpaceTimerDelay[cntChip] = 0;
     DTMFSpaceTimer[cntChip] = 0;

     Ring[cntChip] = 0;
     PreviousRing[cntChip] = 0;
     RingActive[cntChip] = 0;
     RingCount[cntChip] = 0;
     RingActiveTimer[cntChip] = 0;
     RingCountTimer[cntChip] = 0;

     FSKData[cntChip][0] = 0;
     FSKDataLength[cntChip] = 0;
   }

   delay_ms(500);

   nSS = 1;

   ReadFPGA();
   FPGAFirmwareMajorRevision = FPGAData[8];
   FPGAFirmwareMinorRevision = FPGAData[9];
   FPGAFirmwareType = (((unsigned int)FPGAData[10])<<8) | FPGAData[11];

   // CAN Controller initialization
   InitializeCAN();

   NewInputSignalState = 0;
   InputSignalState = 0;
   NewOutputSignalState = 0;
   OutputSignalState = 0;

   for (cntByte=0; cntByte<4; cntByte++)
   {
      char cntTalkback;

      HybridInputRouting[cntByte] = 0x01<<cntByte;
      InputLevel[cntByte] = 0x00;
      InputPhase[cntByte] = 0x00;

      OutputLevel[cntByte] = 0x00;
      OutputDim[cntByte] = 0x00;
      OutputDimLevel[cntByte] = -20;
      OutputMute[cntByte] = 0x00;
      OutputPhase[cntByte] = 0x00;
      for (cntTalkback=0; cntTalkback<16; cntTalkback++)
      {
        OutputTalkback[cntByte][cntTalkback] = 0x00;
      }
      OutputTalkbackLevel[cntByte] = 0x00;
      OutputTalkbackPhase[cntByte] = 0x00;

      SetRoutingAndLevel(cntByte);
   }

   TransmitCANMessageBufferLength = 0;
   cntTransmitCANMessageBuffer = 0;

   PreviousMilliSecond = 0;

   RackSlotNr = GetSlotNr();

   // Global enable interrupts
   #asm("sei")

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
      }

      if (cntMilliSecond - PreviousMilliSecond > 40)
      {  //Send track/relative information maximal 25 times per second.
         PreviousMilliSecond = cntMilliSecond;
      }

      if (cntMilliSecond - PreviousLEDBlinkMilliSecond > 250)
      {  //LED Blink 4 times per second.
         unsigned char cntChannel;

         if (AddressValidated)
         {
            nACT_LED = cntDebug++&0x04;
         }
         else
         {
            nACT_LED = cntDebug++&0x01;
         }

         //read signal
         ReadFPGA();
         NewInputSignalState = FPGAData[3];
         for  (cntChannel=0; cntChannel<4; cntChannel++)
         {
            unsigned char Mask = 0x01<<cntChannel;

            if ((InputSignalState^NewInputSignalState)&Mask)
            {
               unsigned char TransmitBuffer[1];

               TransmitBuffer[0] = 0;
               if (NewInputSignalState&Mask)
               {
                  TransmitBuffer[0] = 1;
               }
               SendSensorChangeToMambaNet(1043+cntChannel, STATE_DATATYPE, 1, TransmitBuffer);
            }
         }
         InputSignalState = NewInputSignalState;

         NewOutputSignalState = FPGAData[7];
         for  (cntChannel=0; cntChannel<4; cntChannel++)
         {
            unsigned char Mask = 0x01<<cntChannel;

            if ((OutputSignalState^NewOutputSignalState)&Mask)
            {
               unsigned char TransmitBuffer[1];

               TransmitBuffer[0] = 0;
               if (NewOutputSignalState&Mask)
               {
                  TransmitBuffer[0] = 1;
               }
               SendSensorChangeToMambaNet(1055+cntChannel, STATE_DATATYPE, 1, TransmitBuffer);
            }
         }
         OutputSignalState = NewOutputSignalState;

         PreviousLEDBlinkMilliSecond = cntMilliSecond;
      }

      Ring[0] = ((!nRING_HYB1) || (!nRING2_HYB1));
      Ring[1] = ((!nRING_HYB2) || (!nRING2_HYB2));
      Ring[2] = ((!nRING_HYB3) || (!nRING2_HYB3));
      Ring[3] = ((!nRING_HYB4) || (!nRING2_HYB4));

      for (cntChip=0; cntChip<4; cntChip++)
      {
        if (Ring[cntChip])
        {
          RingActiveTimer[cntChip] = cntMilliSecond;
        }

        if (PreviousRing[cntChip] != Ring[cntChip])
        {
          if (Ring[cntChip])
          {
            if (!RingActive[cntChip]++)
            {
              unsigned char Text[5];
              //RingActive[cntChip] = 1;
              RingCountTimer[cntChip] = cntMilliSecond;
              RingCount[cntChip]++;

              SendSensorChangeToMambaNet(1151+cntChip, STATE_DATATYPE, 1, &RingActive[cntChip]);
              //SendSensorChangeToMambaNet(1210+cntChip, UNSIGNED_INTEGER_DATATYPE, 1, &RingCount[cntChip]);

              ReceivedPtr[cntChip] = 0;
              //SetCMX865A(cntChip, 0xE2, 0x1E01);//first set DTMF detect
              //SetCMX865A(cntChip, 0xE0, 0x8141);//interrupt on DTMF tone
              DetectMode[cntChip] = IDLE_MODE;
              SetCMX865A(cntChip, 0xE2, 0x1E04);//detect programmed tones
              SetCMX865A(cntChip, 0xE0, 0x8143);//interrupt on programmed tones

            }
          }
          else if (RingActive[cntChip] == 2)
          { //Set FSK detect
            //SetCMX865A(cntChip, 0xE2, 0x1E04);//set progammed tone detect
            FSKState[cntChip] = 1;

            DetectMode[cntChip] = BELL_FSK_MODE;
            SetCMX865A(cntChip, 0xE2, 0x3E00);//set progammed tone detect
            SetCMX865A(cntChip, 0xE0, 0x8142);//interrupt on pattern 1010 detect
          }
          PreviousRing[cntChip] = Ring[cntChip];
        }
      }

      for (cntChip=0; cntChip<4; cntChip++)
      {
        if (RingActive[cntChip])
        {
          if ((cntMilliSecond-RingActiveTimer[cntChip]) > 250)
          {
            //SendSensorChangeToMambaNet(1220+cntChip, STATE_DATATYPE, 1, &RingActive[cntChip]);
            RingActive[cntChip] = 0;
            SendSensorChangeToMambaNet(1151+cntChip, STATE_DATATYPE, 1, &RingActive[cntChip]);
          }
        }
        if (RingCount[cntChip])
        {
          if ((cntMilliSecond-RingCountTimer[cntChip]) > 7500)
          {
            ReceivedPtr[cntChip] = 0;
            RingCount[cntChip] = 0;
            //SetCMX865A(cntChip, 0xE2, 0x1E01);//set DTMF detect
            //SetCMX865A(cntChip, 0xE0, 0x8141);//interrupt on DTMF tone
            DetectMode[cntChip] = IDLE_MODE;
            SetCMX865A(cntChip, 0xE2, 0x1E04);//detect programmed tones
            SetCMX865A(cntChip, 0xE0, 0x8143);//interrupt on programmed tones
          }
        }
      }

      for (cntChip=0; cntChip<4; cntChip++)
      {
        if (NewCallerIDSet[cntChip])
        {
          SendSensorChangeToMambaNet(1155+cntChip, OCTET_STRING_DATATYPE, CallerIDLength[cntChip], CallerID[cntChip]);
          NewCallerIDSet[cntChip] = 0;
        }
/*        if (SetStatusCMX865A[cntChip])
        {
          char Text[5];
          sprintf(Text,"%04X", StatusCMX865A[cntChip]);
          SendSensorChangeToMambaNet(1220+cntChip, OCTET_STRING_DATATYPE, 4, Text);
          SetStatusCMX865A[cntChip] = 0;
        }*/

        if ((DetectMode[cntChip] == BELL_FSK_MODE) && (FSKState[cntChip] == 4))
        {
          unsigned int Test = ReadCMX865A(cntChip, 0xE6);
          if ((Test&0x0580) == 0x0480)
          {
            if ((cntMilliSecond-ContinuousMarkTimer[cntChip]) >= 100)
            {
              SetCMX865A(cntChip, 0xE2, 0x3E36);//set progammed tone detect
              SetCMX865A(cntChip, 0xE0, 0x8141);//interrupt on Rx Data
              FSKPtr[cntChip] = 0;
              FSKState[cntChip] = 5;
            }
          }
        }
        if (DetectMode[cntChip] == BT_FSK_MODE)
        {
          if (FSKState[cntChip] == 1)
          {
            unsigned int Test = ReadCMX865A(cntChip, 0xE6);
            if (!(Test&0x0080))
            {
              FSKState[cntChip] = 2;
              SetCMX865A(cntChip, 0xE2, 0x5E00);//set FSK, V23
              SetCMX865A(cntChip, 0xE0, 0x8142);//interrupt on 1010 Pattern detect
            }
          }
        }
      }

      for (cntChip=0; cntChip<4; cntChip++)
      {
        CheckOffHook(cntChip);
      }

      for (cntChip=0; cntChip<4; cntChip++)
      {
        unsigned char DoDTMF = 1;
        if (DTMFTimerDelay[cntChip])
        {
          DoDTMF = 0;
          if (cntMilliSecond-DTMFTimer[cntChip] >= DTMFTimerDelay[cntChip])
          {
            SetCMX865A(cntChip, 0xE1, 0x1000);
            DTMFTimerDelay[cntChip] = 0;
            DTMFSpaceTimerDelay[cntChip] = DTMFSpace;
            DTMFSpaceTimer[cntChip] = cntMilliSecond;
          }
        }
        if (DTMFSpaceTimerDelay[cntChip])
        {
          DoDTMF = 0;
          if (cntMilliSecond-DTMFSpaceTimer[cntChip] >= DTMFSpaceTimerDelay[cntChip])
          {
            DTMFSpaceTimerDelay[cntChip] = 0;
            DoDTMF = 1;
          }
        }

        if (DoDTMF)
        {
          if (DialPtr[cntChip]<strlen(LastDialedNumber[cntChip]))
          {
            DTMFDigit(cntChip, LastDialedNumber[cntChip][DialPtr[cntChip]++]);
          }
          if (DialPtr[cntChip]>=strlen(LastDialedNumber[cntChip]))
          {
            OutputMute[cntChip] = 0;
            SetRoutingAndLevel(cntChip);
          }
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
            case  MAMBANET_OBJECT_ACTION_INFORMATION_RESPONSE:
            {       //Not yet implemented
            }
            break;
            case  MAMBANET_OBJECT_ACTION_GET_SENSOR_DATA:
            {
               unsigned char TransmitBuffer[48];

               // if (ObjectNr<1024) is handled in the stack
               if ((ObjectNr>=1024) && (ObjectNr<1025))
               {  //Rack slot address
                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                  TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = RackSlotNr;

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1025) && (ObjectNr<1026))
               {  //Input channel count
                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                  TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = 4;

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1026) && (ObjectNr<1027))
               {  //Output channel count
                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                  TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = 8;

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1043) && (ObjectNr<1047))
               {  //Digital in signal >-28dB
                  unsigned char Mask = 0x01<<(ObjectNr-1043);

                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  if (InputSignalState&Mask)
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
               else if ((ObjectNr>=1055) && (ObjectNr<1059))
               {  //Digital out signal >-28dB )
                  unsigned char Mask = 0x01<<(ObjectNr-1055);

                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  if (OutputSignalState&Mask)
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
               else if ((ObjectNr>=1151) && (ObjectNr<1155))
               {  //Ring
                  unsigned char HybridNr = ObjectNr-1151;

                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = RingActive[HybridNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1155) && (ObjectNr<1159))
               {  //CID
                  unsigned char HybridNr = ObjectNr-1155;
                  char cnt;

                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                  TransmitBuffer[3] = OCTET_STRING_DATATYPE;
                  TransmitBuffer[4] = CallerIDLength[HybridNr];
                  for (cnt=0; cnt<TransmitBuffer[4]; cnt++)
                  {
                    TransmitBuffer[5+cnt] = CallerID[HybridNr][cnt];
                  }
                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 5+TransmitBuffer[4]);

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
            {       //Not yet implemented.
               unsigned char TransmitBuffer[48];

               TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
               TransmitBuffer[1] = ObjectNr&0xFF;
               TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE;

               if ((ObjectNr>=1027) && (ObjectNr<1043))
               {  //Hybrid-to-input-routing
                  unsigned char HybridNr;
                  unsigned char InputNr;

                  HybridNr = (ObjectNr-1027)&0x03;
                  InputNr = (ObjectNr-1027)>>2;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  if (HybridInputRouting[InputNr]&(0x01<<HybridNr))
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
               else if ((ObjectNr>=1047) && (ObjectNr<1051))
               {  //Input-level
                  unsigned char ChannelNr;
                  unsigned char VariableFloat[2];

                  ChannelNr = ObjectNr-1047;
                  if (Float2VariableFloat(InputLevel[ChannelNr], 2, VariableFloat) == 0)
                  {
                     TransmitBuffer[3] = FLOAT_DATATYPE;
                     TransmitBuffer[4] = 2;
                     TransmitBuffer[5] = VariableFloat[0];
                     TransmitBuffer[6] = VariableFloat[1];

                     SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 7);

                     MessageDone = 1;
                  }
               }
               else if ((ObjectNr>=1051) && (ObjectNr<1055))
               {  //Input-phase
                  unsigned char ChannelNr;
                  ChannelNr = ObjectNr-1051;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = InputPhase[ChannelNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1059) && (ObjectNr<1063))
               {  //To-hybrid-level
                  unsigned char ChannelNr;
                  unsigned char VariableFloat[2];

                  ChannelNr = ObjectNr-1059;

                  if (Float2VariableFloat(OutputLevel[ChannelNr], 2, VariableFloat) == 0)
                  {
                     TransmitBuffer[3] = FLOAT_DATATYPE;
                     TransmitBuffer[4] = 2;
                     TransmitBuffer[5] = VariableFloat[0];
                     TransmitBuffer[6] = VariableFloat[1];

                     SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 7);

                     MessageDone = 1;
                  }
               }
               else if ((ObjectNr>=1063) && (ObjectNr<1067))
               {  //To-hybrid-phase
                  unsigned char ChannelNr;
                  ChannelNr = ObjectNr-1063;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = OutputPhase[ChannelNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1067) && (ObjectNr<1071))
               {  //To-hybrid-dim
                  unsigned char ChannelNr;
                  ChannelNr = ObjectNr-1067;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = OutputDim[ChannelNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1071) && (ObjectNr<1075))
               {  //To-hybrid-Dim-level
                  unsigned char ChannelNr;
                  unsigned char VariableFloat[2];

                  ChannelNr = ObjectNr-1071;

                  if (Float2VariableFloat(OutputDimLevel[ChannelNr], 2, VariableFloat) == 0)
                  {
                     TransmitBuffer[3] = FLOAT_DATATYPE;
                     TransmitBuffer[4] = 2;
                     TransmitBuffer[5] = VariableFloat[0];
                     TransmitBuffer[6] = VariableFloat[1];

                     SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 7);

                     MessageDone = 1;
                  }
               }
               else if ((ObjectNr>=1075) && (ObjectNr<1139))
               {  //To-hybrid-Talkback
                  unsigned char TalkbackNr;
                  unsigned char OutputNr;

                  TalkbackNr = (ObjectNr-1075)&0x0F;
                  OutputNr = (ObjectNr-1075)>>4;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = OutputTalkback[OutputNr][TalkbackNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1139) && (ObjectNr<1143))
               {  //To-hybrid-Talkback-level
                  unsigned char ChannelNr;
                  unsigned char VariableFloat[2];

                  ChannelNr = ObjectNr-1139;

                  if (Float2VariableFloat(OutputTalkbackLevel[ChannelNr], 2, VariableFloat) == 0)
                  {
                     TransmitBuffer[3] = FLOAT_DATATYPE;
                     TransmitBuffer[4] = 2;
                     TransmitBuffer[5] = VariableFloat[0];
                     TransmitBuffer[6] = VariableFloat[1];

                     SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 7);

                     MessageDone = 1;
                  }
               }
               else if ((ObjectNr>=1143) && (ObjectNr<1147))
               {  //To-hybrid-Talkback-phase
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1143;
                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = OutputTalkbackPhase[ChannelNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1147) && (ObjectNr<1151))
               {  //Total-to-hybrid-Mute
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1147;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = OutputMute[ChannelNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1159) && (ObjectNr<1163))
               {  //Off-Hook.
                  int HybridNr = ObjectNr-1159;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = OffHookState[HybridNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1163) && (ObjectNr<1167))
               {  //Dail number
                  int HybridNr = ObjectNr-1163;
                  char cntByte;

                  TransmitBuffer[3] = OCTET_STRING_DATATYPE;
                  TransmitBuffer[4] = strlen(LastDialedNumber[HybridNr]);
                  if (TransmitBuffer[4]>32)
                  {
                    TransmitBuffer[4] = 32;
                  }
                  for (cntByte=0; cntByte<TransmitBuffer[4]; cntByte++)
                  {
                    TransmitBuffer[5+cntByte] = LastDialedNumber[HybridNr][cntByte];
                  }

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, TransmitBuffer[4]+5);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1167) && (ObjectNr<1168))
               {  //Off-hook-loop-delay
                  TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = OffHookLoopDelay;

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1168) && (ObjectNr<1169))
               {  //DTMF-tone-length
                  TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                  TransmitBuffer[4] = 2;
                  TransmitBuffer[5] = (DTMFLength>>8)&0xFF;
                  TransmitBuffer[6] = DTMFLength&0xFF;

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 7);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1169) && (ObjectNr<1170))
               {  //DTMF-space-length
                  TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                  TransmitBuffer[4] = 2;
                  TransmitBuffer[5] = (DTMFSpace>>8)&0xFF;
                  TransmitBuffer[6] = DTMFSpace&0xFF;

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 7);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1170) && (ObjectNr<1171))
               {  //DTMF-comma-pause
                  TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                  TransmitBuffer[4] = 2;
                  TransmitBuffer[5] = (DTMFCommaPause>>8)&0xFF;
                  TransmitBuffer[6] = DTMFCommaPause&0xFF;

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 7);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1171) && (ObjectNr<1172))
               {  //DTMF-space-pause
                  TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                  TransmitBuffer[4] = 2;
                  TransmitBuffer[5] = (DTMFSpacePause>>8)&0xFF;
                  TransmitBuffer[6] = DTMFSpacePause&0xFF;

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 7);

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

               if ((ObjectNr>=1027) && (ObjectNr<1043))
               {  //Hybrid-to-input-Routing
                  unsigned char HybridNr;
                  unsigned char InputNr;

                  HybridNr = (ObjectNr-1027)&0x03;
                  InputNr = (ObjectNr-1027)>>2;

                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        unsigned char Mask = 0x01<<HybridNr;
                        if (Data[5])
                        {
                          HybridInputRouting[InputNr] |= Mask;
                        }
                        else
                        {
                          HybridInputRouting[InputNr] &= Mask^0xFF;
                        }

                        SetRoutingAndLevel(InputNr);

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1047) && (ObjectNr<1051))
               {  //Input-level
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1047;
                  if (DataType == FLOAT_DATATYPE)
                  {
                     if (DataSize == 2)
                     {
                        float FloatData;
                        if (VariableFloat2Float(&Data[5], DataSize, &FloatData) == 0)
                        {
                           InputLevel[ChannelNr] = FloatData;
                           if (InputLevel[ChannelNr]>24)
                           {
                              InputLevel[ChannelNr] = 24;
                           }
                           else if (InputLevel[ChannelNr]<-60)
                           {
                              InputLevel[ChannelNr] = -60;
                           }

                           SetRoutingAndLevel(ChannelNr);

                           FormatError = 0;
                           MessageDone = 1;
                        }
                     }
                  }
               }
               else if ((ObjectNr>=1051) && (ObjectNr<1055))
               {  //Input-phase
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1051;
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        InputPhase[ChannelNr] = Data[5];
                        SetRoutingAndLevel(ChannelNr);

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1059) && (ObjectNr<1063))
               {  //To-hybrid-level
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1059;
                  if (DataType == FLOAT_DATATYPE)
                  {
                     if (DataSize == 2)
                     {
                        float FloatData;
                        if (VariableFloat2Float(&Data[5], DataSize, &FloatData) == 0)
                        {
                           OutputLevel[ChannelNr] = FloatData;
                           if (OutputLevel[ChannelNr]>24)
                           {
                              OutputLevel[ChannelNr] = 24;
                           }
                           else if (OutputLevel[ChannelNr]<-60)
                           {
                              OutputLevel[ChannelNr] = -60;
                           }
                           SetRoutingAndLevel(ChannelNr);

                           FormatError = 0;
                           MessageDone = 1;
                        }
                     }
                  }
               }
               else if ((ObjectNr>=1063) && (ObjectNr<1067))
               {  //Digital-out phase
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1063;
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        OutputPhase[ChannelNr] = Data[5];
                        SetRoutingAndLevel(ChannelNr);

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1067) && (ObjectNr<1071))
               {  //To-hybrid-dim
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1067;

                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        OutputDim[ChannelNr] = Data[5];
                        SetRoutingAndLevel(ChannelNr);

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1071) && (ObjectNr<1075))
               {  //To-hybrid-dim-level
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1071;

                  if (DataType == FLOAT_DATATYPE)
                  {
                     if (DataSize == 2)
                     {
                        float FloatData;
                        if (VariableFloat2Float(&Data[5], DataSize, &FloatData) == 0)
                        {
                           OutputDimLevel[ChannelNr] = FloatData;
                           if (OutputDimLevel[ChannelNr]>24)
                           {
                              OutputDimLevel[ChannelNr] = 24;
                           }
                           else if (OutputDimLevel[ChannelNr]<-60)
                           {
                              OutputDimLevel[ChannelNr] = -60;
                           }
                           SetRoutingAndLevel(ChannelNr);

                           FormatError = 0;
                           MessageDone = 1;
                        }
                     }
                  }
               }
               else if ((ObjectNr>=1075) && (ObjectNr<1139))
               {  //To-hybrid-talkback
                  unsigned char TalkbackNr;
                  unsigned char OutputNr;

                  TalkbackNr = (ObjectNr-1075)&0x0F;
                  OutputNr = (ObjectNr-1075)>>4;

                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        OutputTalkback[OutputNr][TalkbackNr] = Data[5];
                        SetRoutingAndLevel(OutputNr<<1);

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1139) && (ObjectNr<1143))
               {  //To-hybrid-talkback-level
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1139;

                  if (DataType == FLOAT_DATATYPE)
                  {
                     if (DataSize == 2)
                     {
                        float FloatData;
                        if (VariableFloat2Float(&Data[5], DataSize, &FloatData) == 0)
                        {
                           OutputTalkbackLevel[ChannelNr] = FloatData;
                           if (OutputTalkbackLevel[ChannelNr]>24)
                           {
                              OutputTalkbackLevel[ChannelNr] = 24;
                           }
                           else if (OutputTalkbackLevel[ChannelNr]<-60)
                           {
                              OutputTalkbackLevel[ChannelNr] = -60;
                           }
                           SetRoutingAndLevel(ChannelNr);

                           FormatError = 0;
                           MessageDone = 1;
                        }
                     }
                  }
               }
               else if ((ObjectNr>=1143) && (ObjectNr<1147))
               {  //To-hybrid-talkback-phase
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1143;
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        OutputTalkbackPhase[ChannelNr] = Data[5];
                        SetRoutingAndLevel(ChannelNr);

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1147) && (ObjectNr<1151))
               {  //Total-to-hybrid-mute
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1147;
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        OutputMute[ChannelNr] = Data[5];
                        SetRoutingAndLevel(ChannelNr);

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               if ((ObjectNr>=1159) && (ObjectNr<1163))
               {  //Off-Hook.
                  int HybridNr = ObjectNr-1159;

                  if (DataType == STATE_DATATYPE)
                  {
                    if (DataSize == 1)
                    {
                      OffHookState[HybridNr] = Data[5];
                      if (!Data[5])
                      {
                        SetCMX865A(HybridNr, 0xE1, 0x1000);
                        DialPtr[HybridNr] = 32;
                      }

                      FormatError = 0;
                      MessageDone = 1;
                    }
                  }
               }
               else if ((ObjectNr>=1163) && (ObjectNr<1167))
               {  //Dail number
                  int HybridNr = ObjectNr-1163;

                  if (DataType == OCTET_STRING_DATATYPE)
                  {
                     if (DataSize <= 32)
                     {
                        unsigned char cntChar = 0;
                        unsigned char cntData;
                        for (cntData=0; cntData<DataSize; cntData++)
                        {
                          if (Data[5+cntData] == '+')
                          {
                            LastDialedNumber[HybridNr][cntChar++] = '0';
                            LastDialedNumber[HybridNr][cntChar++] = '0';
                          }
                          else
                          {
                            LastDialedNumber[HybridNr][cntChar++] = Data[5+cntData];
                          }
                        }
                        LastDialedNumber[HybridNr][DataSize] = 0;
                        DialPtr[HybridNr] = 0;

                        OutputMute[HybridNr] = 1;
                        SetRoutingAndLevel(HybridNr);

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1167) && (ObjectNr<1168))
               {  //Off-hook-loop-delay
                  if (DataType == UNSIGNED_INTEGER_DATATYPE)
                  {
                    if (DataSize == 1)
                    {
                      OffHookLoopDelay = Data[5];

                      FormatError = 0;
                      MessageDone = 1;
                    }
                  }
               }
               else if ((ObjectNr>=1168) && (ObjectNr<1169))
               {  //DTMF-tone-length
                  if (DataType == UNSIGNED_INTEGER_DATATYPE)
                  {
                    if (DataSize == 2)
                    {
                      DTMFLength = Data[5];
                      DTMFLength <<= 8;
                      DTMFLength |= Data[6];

                      FormatError = 0;
                      MessageDone = 1;
                    }
                  }
               }
               else if ((ObjectNr>=1169) && (ObjectNr<1170))
               {  //DTMF-space-length
                  if (DataType == UNSIGNED_INTEGER_DATATYPE)
                  {
                    if (DataSize == 2)
                    {
                      DTMFSpace = Data[5];
                      DTMFSpace <<= 8;
                      DTMFSpace |= Data[6];

                      FormatError = 0;
                      MessageDone = 1;
                    }
                  }
               }
               else if ((ObjectNr>=1170) && (ObjectNr<1171))
               {  //DTMF-comma-pause
                  if (DataType == UNSIGNED_INTEGER_DATATYPE)
                  {
                    if (DataSize == 2)
                    {
                      DTMFCommaPause = Data[5];
                      DTMFCommaPause <<= 8;
                      DTMFCommaPause |= Data[6];

                      FormatError = 0;
                      MessageDone = 1;
                    }
                  }
               }
               else if ((ObjectNr>=1171) && (ObjectNr<1172))
               {  //DTMF-space-pause
                  if (DataType == UNSIGNED_INTEGER_DATATYPE)
                  {
                    if (DataSize == 2)
                    {
                      DTMFSpacePause = Data[5];
                      DTMFSpacePause <<= 8;
                      DTMFSpacePause |= Data[6];

                      FormatError = 0;
                      MessageDone = 1;
                    }
                  }
               }
               else if (ObjectNr == 1172)
               {  //Set FPGA
                  if (DataType == OCTET_STRING_DATATYPE)
                  {
                     if (DataSize == 3)
                     {
                        unsigned char FunctionNr;
                        unsigned int FunctionData;

                        FunctionNr = Data[5];
                        FunctionData = Data[6];
                        FunctionData <<=8;
                        FunctionData |= Data[7];

                        SetFPGA(FunctionNr, FunctionData);

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


char GetSlotNr()
{
   unsigned char TempSlotNrA;
   unsigned char TempSlotNrB;
   unsigned char TempSlotNrFloat;
   unsigned char cntBit;
   char SlotNr;

   READ_SLOTADR = 0;
   delay_ms(10);
   TempSlotNrA = (PINB>>4)&0x0F;

   READ_SLOTADR = 1;
   delay_ms(10);
   TempSlotNrB = (PINB>>4)&0x0F;

   TempSlotNrFloat = TempSlotNrA^TempSlotNrB;

   SlotNr = 0;
   for (cntBit=0; cntBit<4; cntBit++)
   {
      SlotNr *= 3;

      if (TempSlotNrFloat&(0x08>>cntBit))
      {
         SlotNr += 1;
      }
      else
      {
         if (TempSlotNrA&(0x08>>cntBit))
         {
            SlotNr += 2;
         }
      }
   }

   return SlotNr;
}

void ReadFPGA()
{
   unsigned char cntBit;
   unsigned char cntByte;
   unsigned char Mask;
   unsigned char DataByte;

   SCK_PSCK = 0;
   nSS = 0;

   for (cntByte=0; cntByte<12; cntByte++)
   {
      Mask = 0x80;
      DataByte = 0x00;
      for (cntBit=0; cntBit<8; cntBit++)
      {
         MOSI = 1;// write 1's has no influence in FPGA
         SCK_PSCK = 1;
         //Read data
         if (MISO)
         {
            DataByte |= Mask;
         }
         Mask >>= 1;
         SCK_PSCK = 0;
      }
      FPGAData[cntByte] = DataByte;
   }

   nSS=1;
}

void SetFPGA(unsigned char FunctionNr, unsigned int FunctionData)
{
   unsigned char cntBit;
   unsigned char Mask;
   unsigned char FunctionDataBuffer[2];

   FunctionDataBuffer[0] = (FunctionData>>8)&0xFF;
   FunctionDataBuffer[1] = (FunctionData   )&0xFF;

   nSS = 0;
   SCK_PSCK = 0;

   Mask = 0x80;
   for (cntBit=0; cntBit<8; cntBit++)
   {
      MOSI = (FunctionNr&0x7F)&Mask;
      Mask >>= 1;
      SCK_PSCK = 1;
      SCK_PSCK = 0;
   }

   Mask = 0x80;
   for (cntBit=0; cntBit<8; cntBit++)
   {
      MOSI = FunctionDataBuffer[0]&Mask;
      Mask >>= 1;
      SCK_PSCK = 1;
      SCK_PSCK = 0;
   }

   Mask = 0x80;
   for (cntBit=0; cntBit<8; cntBit++)
   {
      MOSI = FunctionDataBuffer[1]&Mask;
      Mask >>= 1;
      SCK_PSCK = 1;
      SCK_PSCK = 0;
   }

   nSS=1;
}

void SetRoutingAndLevel(unsigned char ChannelNr)
{
   unsigned char FPGABlockAddress;
   unsigned int InputRouting=0;
   unsigned int StereoSelect=0;
   float Level;
   unsigned int IntegerLevel;
   char cntNrOfSummation;
   char cntTalkback;
   unsigned int TalkbackData[2];

   //Input
   FPGABlockAddress = ((ChannelNr&0xFE)<<3);

   InputRouting = HybridInputRouting[(ChannelNr&0xFE)];
   InputRouting |= HybridInputRouting[(ChannelNr&0xFE)+1]<<4;
   SetFPGA(FPGABlockAddress+2, InputRouting);

   Level = InputLevel[ChannelNr];
   IntegerLevel = ((float)32)/pow(10, (float)Level/20);
   if (InputPhase[ChannelNr])
   {
      IntegerLevel *= -1;
   }
   SetFPGA(FPGABlockAddress+(ChannelNr&0x01), IntegerLevel);

   //Output
//--LETOP 0x10, 0x20, 0x30, 0x40 for channels
   FPGABlockAddress += 0x10;

   Level = OutputLevel[ChannelNr];
   if (OutputDim[ChannelNr])
   {
      Level += OutputDimLevel[ChannelNr];
   }
   if (Level>24)
   {
      Level = 24;
   }
   else if (Level<-60)
   {
      Level = -60;
   }

   IntegerLevel = ((float)32)/pow(10, (float)Level/20);
   if (OutputPhase[ChannelNr])
   {
      IntegerLevel *= -1;
   }
   SetFPGA(FPGABlockAddress+3+(ChannelNr&0x01), IntegerLevel);

   IntegerLevel = ((float)32)/pow(10, (float)OutputTalkbackLevel[ChannelNr]/20);
   if (OutputTalkbackPhase[ChannelNr])
   {
      IntegerLevel *= -1;
   }
   SetFPGA(FPGABlockAddress+5+(ChannelNr&0x01), IntegerLevel);

   if (OutputMute[(ChannelNr&0xFE)])
   {
      StereoSelect |= 0x0100;
   }
   if (OutputMute[(ChannelNr&0xFE)+1])
   {
      StereoSelect |= 0x0200;
   }
   SetFPGA(FPGABlockAddress+7, StereoSelect);

   //Talkback
   FPGABlockAddress = ((ChannelNr&0xFE)<<3);

   cntNrOfSummation = 0;
   TalkbackData[0] = 0;
   TalkbackData[1] = 0;
   for (cntTalkback = 0; cntTalkback<16; cntTalkback++)
   {
      if (OutputTalkback[(ChannelNr>>1)][cntTalkback])
      {
         switch (cntNrOfSummation)
         {
            case 0:
            {
               TalkbackData[0] |= ((unsigned int)cntTalkback+1);
            }
            break;
            case 1:
            {
               TalkbackData[0] |= ((unsigned int)cntTalkback+1)<<8;
            }
            break;
            case 2:
            {
               TalkbackData[1] |= ((unsigned int)cntTalkback+1);
            }
            break;
            case 3:
            {
               TalkbackData[1] |= ((unsigned int)cntTalkback+1)<<8;
            }
            break;
         }
         cntNrOfSummation++;
      }
   }

   SetFPGA(FPGABlockAddress+8, TalkbackData[0]);
   SetFPGA(FPGABlockAddress+9, TalkbackData[1]);
}

void CanBussError()
{
//   AddressValidated = 0;
//   timerReservationInfo = 1;
}

unsigned int ReadCMX865A(unsigned char ChipNr, unsigned char Register)
{
  unsigned char cntBit;
  unsigned char ByteMSB = 0;
  unsigned char ByteLSB = 0;
  unsigned int ReturnValue = 0;

  IO113_AOnCSCMX = ChipNr&0x01;
  IO112_A1nCSCMX = ChipNr&0x02;
  IO114_A2nCSCMX = ChipNr&0x04;
  CLKCMX = 0;

  for (cntBit=0; cntBit<8; cntBit++)
  {
    DINCMX = Register&(0x80>>cntBit);
    CLKCMX = 1;
    CLKCMX = 0;
  }

  delay_ms(1);

  for (cntBit=0; cntBit<8; cntBit++)
  {
    CLKCMX = 1;
    if (DOUTCMX_3V3)
    {
       ByteMSB |= ((unsigned int)0x80>>cntBit);
    }
    CLKCMX = 0;
  }

  for (cntBit=0; cntBit<8; cntBit++)
  {
    CLKCMX = 1;
    if (DOUTCMX_3V3)
    {
       ByteLSB |= ((unsigned int)0x80>>cntBit);
    }
    CLKCMX = 0;
  }

  IO113_AOnCSCMX = 1;
  IO112_A1nCSCMX = 1;
  IO114_A2nCSCMX = 1;

  ReturnValue = ByteMSB;
  ReturnValue <<= 8;
  ReturnValue |= ByteLSB;

  return ReturnValue;
}

unsigned char ReadByteCMX865A(unsigned char ChipNr, unsigned char Register)
{
  unsigned char cntBit;
  unsigned char Byte = 0;
  unsigned int ReturnValue = 0;

  IO113_AOnCSCMX = ChipNr&0x01;
  IO112_A1nCSCMX = ChipNr&0x02;
  IO114_A2nCSCMX = ChipNr&0x04;
  CLKCMX = 0;

  for (cntBit=0; cntBit<8; cntBit++)
  {
    DINCMX = Register&(0x80>>cntBit);
    CLKCMX = 1;
    CLKCMX = 0;
  }

  delay_ms(1);

  for (cntBit=0; cntBit<8; cntBit++)
  {
    CLKCMX = 1;
    if (DOUTCMX_3V3)
    {
       Byte |= ((unsigned int)0x80>>cntBit);
    }
    CLKCMX = 0;
  }

  IO113_AOnCSCMX = 1;
  IO112_A1nCSCMX = 1;
  IO114_A2nCSCMX = 1;

  ReturnValue = Byte;
  return ReturnValue;
}

void SetCMX865A(unsigned char ChipNr, unsigned char Register, unsigned int Value)
{
  unsigned char cntBit;
  unsigned char Byte = Value>>8;

  IO113_AOnCSCMX = ChipNr&0x01;
  IO112_A1nCSCMX = ChipNr&0x02;
  IO114_A2nCSCMX = ChipNr&0x04;

  CLKCMX = 0;

  for (cntBit=0; cntBit<8; cntBit++)
  {
    DINCMX = Register&(0x80>>cntBit);
    CLKCMX = 1;
    CLKCMX = 0;
  }

  for (cntBit=0; cntBit<8; cntBit++)
  {
    DINCMX = Byte&(0x80>>cntBit);
    CLKCMX = 1;
    CLKCMX = 0;
  }
  Byte = Value&0xFF;
  for (cntBit=0; cntBit<8; cntBit++)
  {
    DINCMX = Byte&(0x80>>cntBit);
    CLKCMX = 1;
    CLKCMX = 0;
  }

  IO113_AOnCSCMX = 1;
  IO112_A1nCSCMX = 1;
  IO114_A2nCSCMX = 1;
}

void ResetCMX865A(unsigned char ChipNr)
{
  unsigned char cntBit;
  unsigned char Register = 0x01;

  IO113_AOnCSCMX = ChipNr&0x01;
  IO112_A1nCSCMX = ChipNr&0x02;
  IO114_A2nCSCMX = ChipNr&0x04;
  CLKCMX = 0;
  for (cntBit=0; cntBit<8; cntBit++)
  {
    DINCMX = Register&(0x80>>cntBit);
    CLKCMX = 1;
    CLKCMX = 0;
  }

  IO113_AOnCSCMX = 1;
  IO112_A1nCSCMX = 1;
  IO114_A2nCSCMX = 1;
}

void DTMFDigit(unsigned char ChipNr, char Digit)
{
  switch (Digit)
  {
    case '0':
    {
      SetCMX865A(ChipNr, 0xE1, 0x1010+10);
      DTMFTimerDelay[ChipNr] = DTMFLength;
      DTMFTimer[ChipNr] = cntMilliSecond;
    }
    break;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {
      SetCMX865A(ChipNr, 0xE1, 0x1010+(Digit-'0'));
      DTMFTimerDelay[ChipNr] = DTMFLength;
      DTMFTimer[ChipNr] = cntMilliSecond;
    }
    break;
    case '*':
    {
      SetCMX865A(ChipNr, 0xE1, 0x1010+11);
      DTMFTimerDelay[ChipNr] = DTMFLength;
      DTMFTimer[ChipNr] = cntMilliSecond;
    }
    break;
    case '#':
    {
      SetCMX865A(ChipNr, 0xE1, 0x1010+12);
      DTMFTimerDelay[ChipNr] = DTMFLength;
      DTMFTimer[ChipNr] = cntMilliSecond;
    }
    break;
    case 'A':
    case 'a':
    {
      SetCMX865A(ChipNr, 0xE1, 0x1010+13);
      DTMFTimerDelay[ChipNr] = DTMFLength;
      DTMFTimer[ChipNr] = cntMilliSecond;
    }
    break;
    case 'B':
    case 'b':
    {
      SetCMX865A(ChipNr, 0xE1, 0x1010+14);
      DTMFTimerDelay[ChipNr] = DTMFLength;
      DTMFTimer[ChipNr] = cntMilliSecond;
    }
    break;
    case 'C':
    case 'c':
    {
      SetCMX865A(ChipNr, 0xE1, 0x1010+15);
      DTMFTimerDelay[ChipNr] = DTMFLength;
      DTMFTimer[ChipNr] = cntMilliSecond;
    }
    break;
    case 'D':
    case 'd':
    {
      SetCMX865A(ChipNr, 0xE1, 0x1010+0);
      DTMFTimerDelay[ChipNr] = DTMFLength;
      DTMFTimer[ChipNr] = cntMilliSecond;
    }
    break;
    case ',':
    {
      SetCMX865A(ChipNr, 0xE1, 0x1000);
      DTMFTimerDelay[ChipNr] = DTMFCommaPause;
      DTMFTimer[ChipNr] = cntMilliSecond;
    }
    break;
    case ' ':
    {
      SetCMX865A(ChipNr, 0xE1, 0x1000);
      DTMFTimerDelay[ChipNr] = DTMFSpacePause;
      DTMFTimer[ChipNr] = cntMilliSecond;
    }
    break;
  }
}

void CheckOffHook(unsigned char cntChip)
{
  if (PreviousOffHookState[cntChip] != OffHookState[cntChip])
  {
    if (OffHookState[cntChip])
    {
      switch (cntChip)
      {
        case 0:
        {
          nOH_HYB1 = 0;
        }
        break;
        case 1:
        {
          nOH_HYB2 = 0;
        }
        break;
        case 2:
        {
          nOH_HYB3 = 0;
        }
        break;
        case 3:
        {
          nOH_HYB4 = 0;
        }
        break;
      }
      OffHookTimer[cntChip] = cntMilliSecond;
      OffHookTimerEnabled[cntChip] = 1;
    }
    else
    {
      switch (cntChip)
      {
        case 0:
        {
          nLOOP_HYB1 = 0;
        }
        break;
        case 1:
        {
          nLOOP_HYB2 = 0;
        }
        break;
        case 2:
        {
          nLOOP_HYB3 = 0;
        }
        break;
        case 3:
        {
          nLOOP_HYB4 = 0;
        }
        break;
      }
      OffHookTimer[cntChip] = cntMilliSecond;
      OffHookTimerEnabled[cntChip] = 1;
    }
    PreviousOffHookState[cntChip] = OffHookState[cntChip];
  }
  if (OffHookTimerEnabled[cntChip])
  {
    if (OffHookState[cntChip])
    {
      if ((cntMilliSecond-OffHookTimer[cntChip])>=OffHookLoopDelay)
      {
        switch (cntChip)
        {
          case 0:
          {
            nLOOP_HYB1 = 1;
          }
          break;
          case 1:
          {
            nLOOP_HYB2 = 1;
          }
          break;
          case 2:
          {
            nLOOP_HYB3 = 1;
          }
          break;
          case 3:
          {
            nLOOP_HYB4 = 1;
          }
          break;
        }
        OffHookTimerEnabled[cntChip] = 0;
      }
    }
    else
    {
      if ((cntMilliSecond-OffHookTimer[cntChip])>=OffHookLoopDelay)
      {
        switch (cntChip)
        {
          case 0:
          {
            nOH_HYB1 = 1;
          }
          break;
          case 1:
          {
            nOH_HYB2 = 1;
          }
          break;
          case 2:
          {
            nOH_HYB3 = 1;
          }
          break;
          case 3:
          {
            nOH_HYB4 = 1;
          }
          break;
        }
        OffHookTimerEnabled[cntChip] = 0;
      }
    }
  }
}
