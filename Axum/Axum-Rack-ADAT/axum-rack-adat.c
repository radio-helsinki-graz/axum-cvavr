/*****************************************************
This program was produced by the
CodeWizardAVR V1.25.3 Standard
Automatic Program Generator
© Copyright 1998-2007 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Axum-Rack-DD
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

#include "Axum-Rack-ADAT.h"
#include "CANTransportLayer.h"
#include "Axum-Rack-ADAT-MambaNet.h"

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
   // Func7=In Func6=In Func5=Out Func4=Out Func3=In Func2=In Func1=Out Func0=Out
   // State7=T State6=T State5=0 State4=0 State3=T State2=T State1=0 State0=0
   PORTA=0x00;
   DDRA=0x33;

   // Port B initialization
   // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=Out Func1=Out Func0=Out
   // State7=T State6=T State5=T State4=T State3=T State2=0 State1=0 State0=1
   PORTB=0x01;
   DDRB=0x07;

   // Port C initialization
   // Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out
   // State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0
   PORTC=0x00;
   DDRC=0xFF;

   // Port D initialization
   // Func7=In Func6=In Func5=Out Func4=Out Func3=In Func2=In Func1=In Func0=In
   // State7=T State6=T State5=0 State4=1 State3=T State2=T State1=T State0=T
   PORTD=0x10;
   DDRD=0x30;

   // Port E initialization
   // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=Out Func0=In
   // State7=T State6=T State5=T State4=T State3=T State2=T State1=0 State0=T
   PORTE=0x00;
   DDRE=0x02;

   // Port F initialization
   // Func7=Out Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
   // State7=0 State6=T State5=T State4=T State3=T State2=T State1=T State0=T
   PORTF=0x00;
   DDRF=0x80;

   // Port G initialization
   // Func4=In Func3=Out Func2=In Func1=In Func0=In
   // State4=T State3=0 State2=T State1=T State0=T
   PORTG=0x00;
   DDRG=0x08;

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

   PORTA |= 0x0F;
   delay_us(100);
   HardwareMinorRevision = PINA&0x0F;
   PORTA &= 0xF0;

   delay_ms(200);

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

   LEDMode[0] = 0x00;
   LEDMode[1] = 0x00;
   LEDMode[2] = 0x00;
   LEDMode[3] = 0x00;

   LEDData[0] = 0x01;
   LEDData[1] = 0x01;
   LEDData[2] = 0x01;
   LEDData[3] = 0x01;
   SetLEDs();

   delay_ms(500);

   LEDData[0] = 0x00;
   LEDData[1] = 0x00;
   LEDData[2] = 0x00;
   LEDData[3] = 0x00;
   SetLEDs();

   for (cntByte=0; cntByte<16; cntByte++)
   {
      InputStereoSelect[cntByte] = 0x01<<(cntByte&0x01);
      InputLevel[cntByte] = 0x00;
      InputPhase[cntByte] = 0x00;

      OutputStereoSelect[cntByte] = 0x01<<(cntByte&0x01);
      OutputLevel[cntByte] = 0x00;
      OutputDim[cntByte] = 0x00;
      OutputDimLevel[cntByte] = -10;
      OutputMute[cntByte] = 0x00;
      OutputPhase[cntByte] = 0x00;
      if (cntByte<4)
      {
         OutputTalkback[cntByte] = 0x00;
      }
      OutputTalkbackLevel[cntByte] = 0x00;
      OutputTalkbackStereoSelect[cntByte] = 0x00;
      OutputTalkbackPhase[cntByte] = 0x00;
      SetRoutingAndLevel(cntByte);
   }

   PreviousMilliSecond = 0;

   RackSlotNr = GetSlotNr();

   if (FPGAFirmwareType != DefaultNodeObjects.ProductID)
   {
      LEDData[0] = 0;
      LEDData[1] = 1;
      LEDData[2] = 0;
      LEDData[3] = 1;
//      LEDData[4] = 0;
//      LEDData[5] = 1;
//      LEDData[6] = 0;
//      LEDData[7] = 1;
      SetLEDs();
   }

   // Global enable interrupts
   #asm("sei")

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
         NewInputSignalState = (((unsigned int)FPGAData[2])<<8) | FPGAData[3];
         for  (cntChannel=0; cntChannel<16; cntChannel++)
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
               SendSensorChangeToMambaNet(1037+cntChannel, STATE_DATATYPE, 1, TransmitBuffer);
            }
         }
         InputSignalState = NewInputSignalState;

         NewOutputSignalState = (((unsigned int)FPGAData[2])<<8) | FPGAData[3];
         for  (cntChannel=0; cntChannel<16; cntChannel++)
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
               SendSensorChangeToMambaNet(1053+cntChannel, STATE_DATATYPE, 1, TransmitBuffer);
            }
         }
         OutputSignalState = NewOutputSignalState;

         PreviousLEDBlinkMilliSecond = cntMilliSecond;
      }
//      ReadSwitches();
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
      }
      else if ((LogicSwitchNr>=8) && (LogicSwitchNr<16))
      {
         ObjectNr = LogicSwitchNr + 1059 - 8;
      }

      TransmitBuffer[0] = 0;
      if (Event == 1)
      {
         TransmitBuffer[0] = 1;
      }
      SendSensorChangeToMambaNet(ObjectNr, STATE_DATATYPE, 1, TransmitBuffer);
   }
}
*/

void SetLEDs()
{
   char cntLED;
   for (cntLED=0; cntLED<4; cntLED++)
   {
      unsigned char Green = 0;
      unsigned char Red = 0;
      if (LEDData[cntLED]&0x01)
      {
         switch (LEDMode[cntLED])
         {
            case 0:
            {  //green
               Green = 1;
            }
            break;
            case 1:
            {  //red
               Red = 1;
            }
            break;
            case 2:
            {  //green blink
               Green = 1;
            }
            break;
            case 3:
            {  //red blink
               Red = 1;
            }
            break;
            case 4:
            {  //toggel red/green
               if (LEDState[cntLED])
               {
                  Red = 1;
               }
            }
            break;
         }
      }
      else
      {
         switch (LEDMode[cntLED])
         {
            case 4:
            {  //toggel red/green
               if (LEDState[cntLED])
               {
                  Green = 1;
               }
            }
            break;
         }
      }

      switch (cntLED)
      {
         case 0:
         {
            ADAT1_IN_LEDGRN = Green;
            ADAT1_IN_LEDRED = Red;
         }
         break;
         case 1:
         {
            ADAT1_OUT_LEDGRN = Green;
            ADAT1_OUT_LEDRED = Red;
         }
         break;
         case 2:
         {
            ADAT2_IN_LEDGRN = Green;
            ADAT2_IN_LEDRED = Red;
         }
         break;
         case 3:
         {
            ADAT2_OUT_LEDGRN = Green;
            ADAT2_OUT_LEDRED = Red;
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
               unsigned char TransmitBuffer[8];

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
                  TransmitBuffer[5] = 16;

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
                  TransmitBuffer[5] = 16;

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1027) && (ObjectNr<1029))
               {  //FPGA Firmware version
               }
               else if ((ObjectNr>=1037) && (ObjectNr<1039))
               {  //ADAT-input-status
               }
               else if ((ObjectNr>=1039) && (ObjectNr<1055))
               {  //Digital in peak hold
               }

               if (!MessageDone)
               {
                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                  TransmitBuffer[3] = NO_DATA_DATATYPE;

                  SendMambaNetMessageToCAN(0x10000000, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 4);
               }
            }
            break;
            case  MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE:
            {       //Not implemented
            }
            break;
            case  MAMBANET_OBJECT_ACTION_GET_ACTUATOR_DATA:
            {       //Not yet implemented.
               unsigned char TransmitBuffer[4];

               TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
               TransmitBuffer[1] = ObjectNr&0xFF;
               TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE;
               TransmitBuffer[3] = NO_DATA_DATATYPE;

               SendMambaNetMessageToCAN(0x10000000, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 4);
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

               DataType = Data[3];
               DataSize = Data[4];

               if ((ObjectNr>=1029) && (ObjectNr<1033))
               {  //LED
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        unsigned char LEDNr;
                        LEDNr = ObjectNr-1029;

                        LEDState[LEDNr] = Data[5];
                        LEDData[LEDNr] = LEDState[LEDNr];
                        SetLEDs();
                     }
                  }
               }
               else if ((ObjectNr>=1033) && (ObjectNr<1037))
               {  //LED mode
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        unsigned char LEDNr;
                        LEDNr = ObjectNr-1033;

                        LEDMode[LEDNr] = Data[5];
                        LEDData[LEDNr] = LEDState[LEDNr];
                        SetLEDs();
                     }
                  }
               }
/*             else if ((ObjectNr>=1091) && (ObjectNr<1099))
               {  //Digital-in routing
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1091;
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        InputStereoSelect[ChannelNr] = Data[5];
                        SetRoutingAndLevel(ChannelNr);
                     }
                  }
               }
               else if ((ObjectNr>=1099) && (ObjectNr<1107))
               {  //Digital-in level
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1099;
                  if (DataType == FLOAT_DATATYPE)
                  {
                     if (DataSize == 2)
                     {
                        float FloatData;
                        if (VariableFloat2Float(&Data[5], DataSize, &FloatData) == 0)
                        {
                           InputLevel[ChannelNr] = FloatData;
                           SetRoutingAndLevel(ChannelNr);
                        }
                     }
                  }
               }
               else if ((ObjectNr>=1107) && (ObjectNr<1115))
               {  //Digital-in phase
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1107;
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        InputPhase[ChannelNr] = Data[5];
                        SetRoutingAndLevel(ChannelNr);
                     }
                  }
               }
               else if ((ObjectNr>=1123) && (ObjectNr<1131))
               {  //Digital-out routing
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1123;
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        OutputStereoSelect[ChannelNr] = Data[5];
                        SetRoutingAndLevel(ChannelNr);
                     }
                  }
               }
               else if ((ObjectNr>=1131) && (ObjectNr<1139))
               {  //Digital-out level
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1131;
                  if (DataType == FLOAT_DATATYPE)
                  {
                     if (DataSize == 2)
                     {
                        float FloatData;
                        if (VariableFloat2Float(&Data[5], DataSize, &FloatData) == 0)
                        {
                           OutputLevel[ChannelNr] = FloatData;
                           SetRoutingAndLevel(ChannelNr);
                        }
                     }
                  }
               }
               else if ((ObjectNr>=1139) && (ObjectNr<1147))
               {  //Digital-out phase
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1139;
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        OutputPhase[ChannelNr] = Data[5];
                        SetRoutingAndLevel(ChannelNr);
                     }
                  }
               }
               else if ((ObjectNr>=1147) && (ObjectNr<1155))
               {  //Digital-out dim
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1147;

                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        OutputDim[ChannelNr] = Data[5];
                        SetRoutingAndLevel(ChannelNr);
                     }
                  }
               }
               else if ((ObjectNr>=1155) && (ObjectNr<1163))
               {  //Digital-out dim level
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1155;

                  if (DataType == FLOAT_DATATYPE)
                  {
                     if (DataSize == 2)
                     {
                        float FloatData;
                        if (VariableFloat2Float(&Data[5], DataSize, &FloatData) == 0)
                        {
                           OutputDimLevel[ChannelNr] = FloatData;
                           SetRoutingAndLevel(ChannelNr);
                        }
                     }
                  }
               }
               else if ((ObjectNr>=1163) && (ObjectNr<1167))
               {  //Digital-out talkback
                  unsigned char TalkbackNr;

                  TalkbackNr = ObjectNr-1163;

                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        OutputTalkback[TalkbackNr] = Data[5];
                        SetRoutingAndLevel(TalkbackNr<<1);
                     }
                  }
               }
               else if ((ObjectNr>=1167) && (ObjectNr<1175))
               {  //Digital-out talkback routing
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1167;
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        OutputTalkbackStereoSelect[ChannelNr] = Data[5];
                        SetRoutingAndLevel(ChannelNr);
                     }
                  }
               }
               else if ((ObjectNr>=1175) && (ObjectNr<1183))
               {  //Digital-out talkback level
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1175;

                  if (DataType == FLOAT_DATATYPE)
                  {
                     if (DataSize == 2)
                     {
                        float FloatData;
                        if (VariableFloat2Float(&Data[5], DataSize, &FloatData) == 0)
                        {
                           OutputTalkbackLevel[ChannelNr] = FloatData;
                           SetRoutingAndLevel(ChannelNr);
                        }
                     }
                  }
               }
               else if ((ObjectNr>=1183) && (ObjectNr<1191))
               {  //Digital-out talkback phase
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1183;
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        OutputTalkbackPhase[ChannelNr] = Data[5];
                        SetRoutingAndLevel(ChannelNr);
                     }
                  }
               }
               else if ((ObjectNr>=1191) && (ObjectNr<1199))
               {  //Digital-out mute
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1191;
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        OutputMute[ChannelNr] = Data[5];
                        SetRoutingAndLevel(ChannelNr);
                     }
                  }
               }
               else if ((ObjectNr>=1203) && (ObjectNr<1207))
               {  //Transmitter control register
               }*/
               else if (ObjectNr == 1270)
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
                     }
                  }
               }

               if (!MessageDone)
               {
                  unsigned char TransmitBuffer[23];

                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE;
                  TransmitBuffer[3] = ERROR_DATATYPE;

                  TransmitBuffer[4] = 18;
                  sprintf(&TransmitBuffer[5], "No actuator object");

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
   nSS=0;
}

void SetRoutingAndLevel(unsigned char ChannelNr)
{
   unsigned char FPGAAddress;
   unsigned int StereoSelect;
   float Level;
   unsigned int IntegerLevel;

   FPGAAddress = (((ChannelNr&0xFE)<<2)+5);

   StereoSelect = (InputStereoSelect[(ChannelNr&0xFE)]&0x03);
   StereoSelect |= (unsigned int)(InputStereoSelect[(unsigned char)((ChannelNr&0xFE)+1)]&0x03)<<2;
   StereoSelect |= ((unsigned int)(OutputTalkback[ChannelNr>>1]&0x1F))<<8;

   SetFPGA((FPGAAddress+0), StereoSelect);

   Level = InputLevel[ChannelNr];
   IntegerLevel = ((float)16)/pow(10, (float)Level/20);
   if (InputPhase[ChannelNr])
   {
      IntegerLevel *= -1;
   }
   SetFPGA(FPGAAddress+1+(ChannelNr&0x01), IntegerLevel);

   Level = OutputLevel[ChannelNr];
   if (OutputDim[ChannelNr])
   {
      Level += OutputDimLevel[ChannelNr];
   }

   IntegerLevel = ((float)16)/pow(10, (float)Level/20);
   if (OutputPhase[ChannelNr])
   {
      IntegerLevel *= -1;
   }
   SetFPGA(FPGAAddress+3+(ChannelNr&0x01), IntegerLevel);

   IntegerLevel = ((float)16)/pow(10, (float)OutputTalkbackLevel[ChannelNr]/20);
   if (OutputTalkbackPhase[ChannelNr])
   {
      IntegerLevel *= -1;
   }
   SetFPGA(FPGAAddress+5+(ChannelNr&0x01), IntegerLevel);

   StereoSelect = (OutputStereoSelect[(ChannelNr&0xFE)]&0x03);
   StereoSelect |= (unsigned int)(OutputStereoSelect[(unsigned char)((ChannelNr&0xFE)+1)]&0x03)<<2;
   if (OutputMute[ChannelNr])
   {
      StereoSelect |= 0x0100<<(ChannelNr&0x01);
   }
   StereoSelect |= (unsigned int)(OutputTalkbackStereoSelect[(ChannelNr&0xFE)]&0x03)<<4;
   StereoSelect |= (unsigned int)(OutputTalkbackStereoSelect[(unsigned char)((ChannelNr&0xFE)+1)]&0x03)<<6;
   SetFPGA(FPGAAddress+7, StereoSelect);
}

void CanBussError()
{
   AddressValidated = 0;
   timerReservationInfo = 1;
}