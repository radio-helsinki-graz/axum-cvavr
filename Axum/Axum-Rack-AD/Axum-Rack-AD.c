/*****************************************************
This program was produced by the
CodeWizardAVR V1.25.3 Standard
Automatic Program Generator
© Copyright 1998-2007 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Axum-Rack-AD
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

#include "Axum-Rack-AD.h"
#include "CANTransportLayer.h"
#include "Axum-Rack-AD-MambaNet.h"

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
   // State7=T State6=T State5=T State4=T State3=P State2=P State1=P State0=P
   PORTA=0x0F;
   DDRA=0x00;

   // Port B initialization
   // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=Out Func1=Out Func0=Out
   // State7=T State6=T State5=T State4=T State3=T State2=0 State1=0 State0=1
   PORTB=0x01;
   DDRB=0x07;

   // Port C initialization
   // Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out
   // State7=0 State6=0 State5=1 State4=1 State3=0 State2=0 State1=1 State0=1
   PORTC=0x33;
   DDRC=0xFF;

   // Port D initialization
   // Func7=In Func6=In Func5=Out Func4=Out Func3=Out Func2=Out Func1=In Func0=In
   // State7=T State6=T State5=0 State4=1 State3=0 State2=1 State1=T State0=T
   PORTD=0x14;
   DDRD=0x3C;

   // Port E initialization
   // Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out
   // State7=0 State6=0 State5=1 State4=1 State3=0 State2=0 State1=1 State0=1
   PORTE=0xCC;
   DDRE=0xFF;

   // Port F initialization
   // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
   // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
   PORTF=0x00;
   DDRF=0x00;

   // Port G initialization
   // Func4=In Func3=Out Func2=In Func1=Out Func0=Out
   // State4=T State3=0 State2=T State1=0 State0=0
   PORTG=0x00;
   DDRG=0x0B;

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
   
   nREAD_OVL = 1;
   PORTA |= 0x0F;
   delay_us(100);
   HardwareMinorRevision = PINA&0x0F;
   PORTA &= 0xF0;
   nREAD_OVL = 0;
   
   delay_ms(150);
   
   nSS = 1;

   ReadFPGA();  
   FPGAFirmwareMajorRevision = FPGAData[8];
   FPGAFirmwareMinorRevision = FPGAData[9];
   FPGAFirmwareType = (((unsigned int)FPGAData[10])<<8) | FPGAData[11];
   
   // CAN Controller initialization
   InitializeCAN();

   LEDState[0] = 0x00;
   LEDState[1] = 0x00;
   LEDState[2] = 0x00;
   LEDState[3] = 0x00;
   LEDState[4] = 0x00;
   LEDState[5] = 0x00;
   LEDState[6] = 0x00;
   LEDState[7] = 0x00;

   LEDMode[0] = 0x00;
   LEDMode[1] = 0x00;
   LEDMode[2] = 0x00;
   LEDMode[3] = 0x00;
   LEDMode[4] = 0x00;
   LEDMode[5] = 0x00;
   LEDMode[6] = 0x00;
   LEDMode[7] = 0x00;

   LEDData[0] = 0x01;
   LEDData[1] = 0x01;
   LEDData[2] = 0x01;
   LEDData[3] = 0x01;
   LEDData[4] = 0x01;
   LEDData[5] = 0x01;
   LEDData[6] = 0x01;
   LEDData[7] = 0x01;
   SetLEDs();

   OverloadState[0] = 0;
   OverloadState[1] = 0;
   OverloadState[2] = 0;
   OverloadState[3] = 0;
   OverloadState[4] = 0;
   OverloadState[5] = 0;
   OverloadState[6] = 0;
   OverloadState[7] = 0;
   
   NewSignalState = 0;
   SignalState = 0;

   GPIState[0] = 0;
   GPIState[1] = 0;
   GPIState[2] = 0;
   GPIState[3] = 0;
   GPIState[4] = 0;
   GPIState[5] = 0;
   GPIState[6] = 0;
   GPIState[7] = 0;
   
   GPIActiveState[0] = 1;
   GPIActiveState[1] = 1;
   GPIActiveState[2] = 1;
   GPIActiveState[3] = 1;
   GPIActiveState[4] = 1;
   GPIActiveState[5] = 1;
   GPIActiveState[6] = 1;
   GPIActiveState[7] = 1;

   GetGPIOModes();

   GPOPulseTime[0] = 50;
   GPOPulseTime[1] = 50;
   GPOPulseTime[2] = 50;
   GPOPulseTime[3] = 50;
   GPOPulseTime[4] = 50;
   GPOPulseTime[5] = 50;
   GPOPulseTime[6] = 50;
   GPOPulseTime[7] = 50;

   GPOActiveState[0] = 1;
   GPOActiveState[1] = 1;
   GPOActiveState[2] = 1;
   GPOActiveState[3] = 1;
   GPOActiveState[4] = 1;
   GPOActiveState[5] = 1;
   GPOActiveState[6] = 1;
   GPOActiveState[7] = 1;
   
   GPOState[0] = !GPOActiveState[0];
   GPOState[1] = !GPOActiveState[1];
   GPOState[2] = !GPOActiveState[2];
   GPOState[3] = !GPOActiveState[3];
   GPOState[4] = !GPOActiveState[4];
   GPOState[5] = !GPOActiveState[5];
   GPOState[6] = !GPOActiveState[6];
   GPOState[7] = !GPOActiveState[7];
   SetGPOs();

   delay_ms(500);

   LEDData[0] = 0x00;
   LEDData[1] = 0x00;
   LEDData[2] = 0x00;
   LEDData[3] = 0x00;
   LEDData[4] = 0x00;
   LEDData[5] = 0x00;
   LEDData[6] = 0x00;
   LEDData[7] = 0x00;
   SetLEDs();

   for (cntByte=0; cntByte<8; cntByte++)
   {
      InputStereoSelect[cntByte] = 0x01<<(cntByte&0x01);
      InputLevel[cntByte] = 0x00;
      InputPhase[cntByte] = 0x00;
      SetInputRoutingAndLevel(cntByte);
   }
   
   TransmitCANMessageBufferLength = 0;
   cntTransmitCANMessageBuffer = 0;

   PreviousMilliSecond = 0;

   RackSlotNr = GetSlotNr();

   if (FPGAFirmwareType != DefaultNodeObjects.ProductID)
   {
      LEDData[0] = 0;
      LEDData[1] = 1;
      LEDData[2] = 0;
      LEDData[3] = 1;
      LEDData[4] = 0;
      LEDData[5] = 1;
      LEDData[6] = 0;
      LEDData[7] = 1;
      SetLEDs();      
   }

   IO113 = 1; //nRST-AD
   IO112 = 0; //DR/nSR

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
         unsigned char cntLED;
         unsigned char DoSetLEDs;
         unsigned char cntChannel;


         DoSetLEDs = 0;
         for (cntLED=0; cntLED<8; cntLED++)
         {
            if (FPGAFirmwareType == DefaultNodeObjects.ProductID)
            {
               if (LEDMode[cntLED])
               {
                  if (LEDState[cntLED])
                  {
                     LEDData[cntLED] ^= 0x01;
                     DoSetLEDs = 1;
                  }
                  else if (LEDData[cntLED])
                  {
                     LEDData[cntLED] = 0;
                     DoSetLEDs = 1;
                  }
               }
            }
            else
            { //wrong FPGA firmware
               LEDData[cntLED] ^= 0x01;
               DoSetLEDs = 1;
            }
         }
         if (DoSetLEDs)
         {
            SetLEDs();
         }

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
         NewSignalState = FPGAData[3];
         for  (cntChannel=0; cntChannel<8; cntChannel++)
         {
            unsigned char Mask = 0x01<<cntChannel;
            
            if ((SignalState^NewSignalState)&Mask)
            {
               unsigned char TransmitBuffer[1];
                             
               TransmitBuffer[0] = 0;
               if (NewSignalState&Mask)
               {
                  TransmitBuffer[0] = 1;
               }
               SendSensorChangeToMambaNet(1099+cntChannel, STATE_DATATYPE, 1, TransmitBuffer);
            }
         }
         SignalState = NewSignalState;

         PreviousLEDBlinkMilliSecond = cntMilliSecond;
      }

      {
         unsigned char cntGPO;
         unsigned char DoSetGPOs;

         for (cntGPO=0; cntGPO<8; cntGPO++)
         {
            if (GPOPulseTime[cntGPO] > 0)
            {
               if ((cntMilliSecond - GPOStartTime[cntGPO]) > GPOPulseTime[cntGPO])
               {
                  GPOState[cntGPO] = !GPOActiveState[cntGPO];
                  DoSetGPOs = 1;
               }
            }
         }

         if (DoSetGPOs)
         {
            SetGPOs();
         }
      }

      ReadSwitches();
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

   Overload = PINA;

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
      unsigned char TransmitBuffer[1];
      unsigned int ObjectNr;

      if ((LogicSwitchNr>=0) && (LogicSwitchNr<8))
      {
         ObjectNr = LogicSwitchNr + 1027;

         TransmitBuffer[0] = !GPIActiveState[LogicSwitchNr];
         if (Event == 1)
         {
            TransmitBuffer[0] = GPIActiveState[LogicSwitchNr];
         }

         GPIState[LogicSwitchNr] = TransmitBuffer[0];
      }
      else if ((LogicSwitchNr>=8) && (LogicSwitchNr<16))
      {
         ObjectNr = (LogicSwitchNr-8) + 1091;

         TransmitBuffer[0] = 0;
         if (Event == 1)
         {
            TransmitBuffer[0] = 1;
         }

         OverloadState[LogicSwitchNr-8] = TransmitBuffer[0];
      }
      SendSensorChangeToMambaNet(ObjectNr, STATE_DATATYPE, 1, TransmitBuffer);
   }
}

void SetLEDs()
{
   nLO_L1 = !(LEDData[0]&0x01);
   nLG_L1 = !(LEDData[1]&0x01);
   nLO_L2 = !(LEDData[2]&0x01);
   nLG_L2 = !(LEDData[3]&0x01);
   nLO_L3 = !(LEDData[4]&0x01);
   nLG_L3 = !(LEDData[5]&0x01);
   nLO_L4 = !(LEDData[6]&0x01);
   nLG_L4 = !(LEDData[7]&0x01);
}

void SetGPOs()
{
   GPO1 = GPOState[0]&0x01;
   GPO2 = GPOState[1]&0x01;
   GPO3 = GPOState[2]&0x01;
   GPO4 = GPOState[3]&0x01;
   PDI_GPO5 = GPOState[4]&0x01;
   PDO_GPO6 = GPOState[5]&0x01;
   GPO7 = GPOState[6]&0x01;
   GPO8 = GPOState[7]&0x01;
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
            //MAMBANET_OBJECT_ACTION_INFORMATION_RESPONSE, only for response of a node
            case  MAMBANET_OBJECT_ACTION_GET_SENSOR_DATA:
            {
               unsigned char TransmitBuffer[21];

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
                  TransmitBuffer[5] = 8;

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
                  TransmitBuffer[5] = 0;

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);
                  
                  MessageDone = 1;
               }               
               else if ((ObjectNr>=1027) && (ObjectNr<1035))
               {  //GPI
                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = GPIState[ObjectNr-1027];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);
                  
                  MessageDone = 1;               
               }
               else if ((ObjectNr>=1043) && (ObjectNr<1051))
               {  //GPIO Mode
                  GetGPIOModes();

                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = GPIOMode[ObjectNr-1043];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);
                  
                  MessageDone = 1;
               }
               else if ((ObjectNr>=1091) && (ObjectNr<1099))
               {  //Overload ADC
                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = OverloadState[ObjectNr-1091];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);
                  
                  MessageDone = 1;        
               }
               else if ((ObjectNr>=1099) && (ObjectNr<1107))
               {  //input signal >-28dB
                  unsigned char Mask = 0x01<<(ObjectNr-1099);
                  
                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  if (SignalState&Mask)
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
            //MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE, only for responding
            case  MAMBANET_OBJECT_ACTION_GET_ACTUATOR_DATA:
            {       //Not yet implemented.
               unsigned char TransmitBuffer[23];

               TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
               TransmitBuffer[1] = ObjectNr&0xFF;
               TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE;

               if ((ObjectNr>=1035) && (ObjectNr<1043))
               {  //GPO-Active-state
                  unsigned char GPINr;
                  GPINr = ObjectNr-1035;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = GPIActiveState[GPINr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1051) && (ObjectNr<1059))
               {  //GPO
                  unsigned char GPONr;
                  GPONr = ObjectNr-1051;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = GPOState[GPONr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1059) && (ObjectNr<1067))
               {  //GPO-Time
                  unsigned char GPONr;
                  GPONr = ObjectNr-1059;

                  TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = GPOPulseTime[GPONr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1067) && (ObjectNr<1075))
               {  //GPO-Active-state
                  unsigned char GPONr;
                  GPONr = ObjectNr-1067;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = GPOActiveState[GPONr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1075) && (ObjectNr<1083))
               {  //LED Orange/Green IO
                  unsigned char LEDNr;
                  LEDNr = ObjectNr-1075;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = LEDState[LEDNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1083) && (ObjectNr<1091))
               {  //LED Orange/Green IO mode
                  unsigned char LEDNr;
                  LEDNr = ObjectNr-1083;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = LEDMode[LEDNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1107) && (ObjectNr<1115))
               {  //Line-in routing
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1107;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = InputStereoSelect[ChannelNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1115) && (ObjectNr<1123))
               {  //Line-in level
                  unsigned char ChannelNr;
                  unsigned char VariableFloat[2];

                  ChannelNr = ObjectNr-1115;
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
               else if ((ObjectNr>=1123) && (ObjectNr<1131))
               {  //Digital-in phase
                  unsigned char ChannelNr;
                  ChannelNr = ObjectNr-1123;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = InputPhase[ChannelNr];

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

               if ((ObjectNr>=1035) && (ObjectNr<1043))
               {  //GPI-Active-state
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        unsigned char GPINr;
                        GPINr = ObjectNr-1035;
                        GPIActiveState[GPINr] = Data[5];

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }                  
               }
               if ((ObjectNr>=1051) && (ObjectNr<1059))
               {  //GPO
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        unsigned char GPONr;
                        GPONr = ObjectNr-1051;
                        
                        if (Data[5])
                        {
                           GPOState[GPONr] = GPOActiveState[GPONr];
                        }
                        else
                        {
                           GPOState[GPONr] = !GPOActiveState[GPONr];
                        }
                        GPOStartTime[GPONr] = cntMilliSecond;
                        SetGPOs();

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }

               }
               else if ((ObjectNr>=1059) && (ObjectNr<1067))
               {  //GPO-Time
                  if (DataType == UNSIGNED_INTEGER_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        unsigned char GPONr;
                        GPONr = ObjectNr-1059;

                        GPOPulseTime[GPONr] = Data[5];
                        SetGPOs();

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1067) && (ObjectNr<1075))
               {  //GPO-Active-state
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        unsigned char GPONr;
                        GPONr = ObjectNr-1067;
                        GPOActiveState[GPONr] = Data[5];
                        SetGPOs();
                        
                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1075) && (ObjectNr<1083))
               {  //LED Orange/Green IO
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        unsigned char LEDNr;
                        LEDNr = ObjectNr-1075;

                        LEDState[LEDNr] = Data[5];
                        LEDData[LEDNr] = LEDState[LEDNr];
                        SetLEDs();
                     
                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1083) && (ObjectNr<1091))
               {  //LED Orange/Green IO mode
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        unsigned char LEDNr;
                        LEDNr = ObjectNr-1083;

                        LEDMode[LEDNr] = Data[5];
                        LEDData[LEDNr] = LEDState[LEDNr];
                        SetLEDs();

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1107) && (ObjectNr<1115))
               {  //Line-in routing
                  unsigned char ChannelNr;                 
                  ChannelNr = ObjectNr-1107;

                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        InputStereoSelect[ChannelNr] = Data[5];
                        SetInputRoutingAndLevel(ChannelNr);

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1115) && (ObjectNr<1123))
               {  //Line-in level
                  unsigned char ChannelNr;                  
                  ChannelNr = ObjectNr-1115;

                  if (DataType == FLOAT_DATATYPE)
                  {
                     if (DataSize == 2)
                     {
                        float FloatData;
                        if (VariableFloat2Float(&Data[5], DataSize, &FloatData) == 0)
                        {
                           InputLevel[ChannelNr] = FloatData;
                           if (InputLevel[ChannelNr] > 24)
                           {
                              InputLevel[ChannelNr] = 24;
                           }
                           else if (InputLevel[ChannelNr] < -60)
                           {
                              InputLevel[ChannelNr] = -60;
                           }
                           SetInputRoutingAndLevel(ChannelNr);

                           FormatError = 0;
                           MessageDone = 1;
                        }
                     }
                  }
               }
               else if ((ObjectNr>=1123) && (ObjectNr<1131))
               {  //Digital-in phase
                  unsigned char ChannelNr;                  
                  ChannelNr = ObjectNr-1123;

                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        InputPhase[ChannelNr] = Data[5];
                        SetInputRoutingAndLevel(ChannelNr);

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if (ObjectNr == 1131)
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

   PORTB &= 0x0F;
   READ_SLOTADR = 0;
   delay_ms(10);
   TempSlotNrA = (PINB>>4)&0x0F;

   PORTB |= 0xF0;
   READ_SLOTADR = 1;
   delay_ms(10);
   TempSlotNrB = (PINB>>4)&0x0F;

   TempSlotNrFloat = TempSlotNrA^TempSlotNrB;

   SlotNr = 0;
   for (cntBit=0; cntBit<4; cntBit++)
   {
      unsigned char Weight;

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
   unsigned char cntByte;
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
   nSS=0;
}

void SetInputRoutingAndLevel(unsigned char ChannelNr)
{          
   unsigned char FPGABlockAddress; 
   unsigned int StereoSelect;          
   float Level;
   unsigned int IntegerLevel;

   //Input                 
   FPGABlockAddress = ((ChannelNr&0xFE)<<3);

   StereoSelect = (InputStereoSelect[(ChannelNr&0xFE)]&0x03);
   StereoSelect |= (InputStereoSelect[(ChannelNr&0xFE)+1]&0x03)<<2;
   SetFPGA(FPGABlockAddress+2, StereoSelect);

   Level = InputLevel[ChannelNr]; 
   IntegerLevel = ((float)32)/pow(10, (float)Level/20);
   if (InputPhase[ChannelNr])
   {
      IntegerLevel *= -1;
   }
   SetFPGA(FPGABlockAddress+(ChannelNr&0x01), IntegerLevel);     
}

void CanBussError()
{
 //  AddressValidated = 0;
//   timerReservationInfo = 1;
}

void GetGPIOModes()
{
   char cntBit;
   unsigned char GPIOModesA;
   unsigned char GPIOModesB;

   READ_SLOTADR = 0;
   delay_ms(1);
   GPIOModesA = PINF;
   READ_SLOTADR = 1;
   delay_ms(1);
   GPIOModesB = PINF;
      
   for (cntBit=0; cntBit<8; cntBit++)
   {
      unsigned char Mask = 0x80>>cntBit;
      if ((GPIOModesA&Mask) == (GPIOModesB&Mask)) 
      {
         GPIOMode[cntBit] = 1;
      }
      else
      {
         GPIOMode[cntBit] = 0;
      }
   }
}