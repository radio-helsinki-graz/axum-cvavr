/*****************************************************
This program was produced by the
CodeWizardAVR V1.25.3 Standard
Automatic Program Generator
© Copyright 1998-2007 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Axum-Rack-Firewire
Version :
Date    : 04-05-2010
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

#include "Axum-Rack-Firewire.h"
#include "CANTransportLayer.h"
#include "Axum-Rack-Firewire-MambaNet.h"

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
   // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
   // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
   PORTA=0x00;
   DDRA=0x00;

   // Port B initialization
   // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=Out Func1=Out Func0=Out
   // State7=T State6=T State5=T State4=T State3=T State2=0 State1=0 State0=1
   PORTB=0x01;
   DDRB=0x07;

   // Port C initialization
   // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
   // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
   PORTC=0x00;
   DDRC=0x00;

   // Port D initialization
   // Func7=In Func6=In Func5=Out Func4=Out Func3=In Func2=In Func1=In Func0=In
   // State7=T State6=T State5=0 State4=1 State3=T State2=T State1=T State0=T
   PORTD=0x10;
   DDRD=0x30;

   // Port E initialization
   // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=Out Func0=In
   // State7=T State6=T State5=T State4=T State3=T State2=T State1=0 State0=T
   PORTE=0x08;
   DDRE=0x0A;

   // Port F initialization
   // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
   // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
   PORTF=0x00;
   DDRF=0x00;

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

   PORTE |= 0xF0;
   delay_us(100);
   HardwareMinorRevision = (PINE>>4)&0x0F;
   PORTE &= 0x0F;

   delay_ms(200);

   nSS = 1;

   //ReadFPGA();
   FPGAFirmwareMajorRevision = FPGAData[8];
   FPGAFirmwareMinorRevision = FPGAData[9];
   FPGAFirmwareType = (((unsigned int)FPGAData[10])<<8) | FPGAData[11];

   // CAN Controller initialization
   InitializeCAN();

   delay_ms(500);

   for (cntByte=0; cntByte<16; cntByte++)
   {
      InputStereoSelect[cntByte] = 0x01<<(cntByte&0x01);
      InputLevel[cntByte] = -20;
      InputPhase[cntByte] = 0x00;

      OutputStereoSelect[cntByte] = 0x01<<(cntByte&0x01);
      OutputLevel[cntByte] = 0x00;
      OutputDim[cntByte] = 0x00;
      OutputDimLevel[cntByte] = -10;
      OutputMute[cntByte] = 0x00;
      OutputPhase[cntByte] = 0x00;
      OutputTalkback[0][cntByte] = 0x00;
      OutputTalkback[1][cntByte] = 0x00;
      OutputTalkback[2][cntByte] = 0x00;
      OutputTalkback[3][cntByte] = 0x00;
      OutputTalkback[5][cntByte] = 0x00;
      OutputTalkback[6][cntByte] = 0x00;
      OutputTalkback[7][cntByte] = 0x00;
      OutputTalkbackLevel[cntByte] = 0x00;
      OutputTalkbackStereoSelect[cntByte] = 0x00;
      OutputTalkbackPhase[cntByte] = 0x00;
   }

   for (cntByte=0; cntByte<16; cntByte++)
   {
      SetRoutingAndLevel(cntByte);
   }

   PreviousMilliSecond = 0;

   RackSlotNr = GetSlotNr();

   if (FPGAFirmwareType != DefaultNodeObjects.ProductID)
   {
   }

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
         //ReadFPGA();
         NewInputSignalState = (((unsigned int)FPGAData[2])<<8) | FPGAData[3];
         for  (cntChannel=0; cntChannel<16; cntChannel++)
         {
            unsigned int Mask = ((unsigned int)0x01)<<cntChannel;

            if ((InputSignalState^NewInputSignalState)&Mask)
            {
               unsigned char TransmitBuffer[1];

               TransmitBuffer[0] = 0;
               if (NewInputSignalState&Mask)
               {
                  TransmitBuffer[0] = 1;
               }
               SendSensorChangeToMambaNet(1027+cntChannel, STATE_DATATYPE, 1, TransmitBuffer);
            }
         }
         InputSignalState = NewInputSignalState;

         NewOutputSignalState = (((unsigned int)FPGAData[2])<<8) | FPGAData[3];
         for  (cntChannel=0; cntChannel<16; cntChannel++)
         {
            unsigned int Mask = ((unsigned int)0x01)<<cntChannel;

            if ((OutputSignalState^NewOutputSignalState)&Mask)
            {
               unsigned char TransmitBuffer[1];

               TransmitBuffer[0] = 0;
               if (NewOutputSignalState&Mask)
               {
                  TransmitBuffer[0] = 1;
               }
               SendSensorChangeToMambaNet(1091+cntChannel, STATE_DATATYPE, 1, TransmitBuffer);
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
               unsigned char TransmitBuffer[24];

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
               else if ((ObjectNr>=1027) && (ObjectNr<1043))
               {  //Digital in signal >-28dB
                  unsigned int Mask = 0x01<<(ObjectNr-1027);

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
               else if ((ObjectNr>=1091) && (ObjectNr<1107))
               {  //Digital out signal >-28dB )
                  unsigned int Mask = 0x01<<(ObjectNr-1091);

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
               unsigned char TransmitBuffer[23];

               TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
               TransmitBuffer[1] = ObjectNr&0xFF;
               TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE;

               if ((ObjectNr>=1043) && (ObjectNr<1059))
               {  //Digital-in routing
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1043;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = InputStereoSelect[ChannelNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1059) && (ObjectNr<1075))
               {  //Digital-in level
                  unsigned char ChannelNr;
                  unsigned char VariableFloat[2];

                  ChannelNr = ObjectNr-1059;
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
               else if ((ObjectNr>=1075) && (ObjectNr<1091))
               {  //Digital-in phase
                  unsigned char ChannelNr;
                  ChannelNr = ObjectNr-1075;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = InputPhase[ChannelNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1107) && (ObjectNr<1123))
               {  //Digital-out routing
                  unsigned char ChannelNr;
                  ChannelNr = ObjectNr-1107;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = OutputStereoSelect[ChannelNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1123) && (ObjectNr<1139))
               {  //Digital-out level
                  unsigned char ChannelNr;
                  unsigned char VariableFloat[2];

                  ChannelNr = ObjectNr-1123;

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
               else if ((ObjectNr>=1139) && (ObjectNr<1155))
               {  //Digital-out phase
                  unsigned char ChannelNr;
                  ChannelNr = ObjectNr-1139;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = OutputPhase[ChannelNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1155) && (ObjectNr<1171))
               {  //Digital-out dim
                  unsigned char ChannelNr;
                  ChannelNr = ObjectNr-1155;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = OutputDim[ChannelNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1171) && (ObjectNr<1187))
               {  //Digital-out dim level
                  unsigned char ChannelNr;
                  unsigned char VariableFloat[2];

                  ChannelNr = ObjectNr-1171;

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
               else if ((ObjectNr>=1187) && (ObjectNr<1315))
               {  //Digital-out talkback
                  unsigned char TalkbackNr;
                  unsigned char OutputNr;

                  TalkbackNr = (ObjectNr-1187)&0x0F;
                  OutputNr = (ObjectNr-1187)>>4;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = OutputTalkback[OutputNr][TalkbackNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1315) && (ObjectNr<1331))
               {  //Digital-out talkback routing
                  unsigned char ChannelNr;
                  ChannelNr = ObjectNr-1315;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = OutputTalkbackStereoSelect[ChannelNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1331) && (ObjectNr<1347))
               {  //Digital-out talkback level
                  unsigned char ChannelNr;
                  unsigned char VariableFloat[2];

                  ChannelNr = ObjectNr-1331;

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
               else if ((ObjectNr>=1347) && (ObjectNr<1363))
               {  //Digital-out talkback phase
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1347;
                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = OutputTalkbackPhase[ChannelNr];

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1363) && (ObjectNr<1379))
               {  //Digital-out mute
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1363;

                  TransmitBuffer[3] = STATE_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = OutputMute[ChannelNr];

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

               if ((ObjectNr>=1043) && (ObjectNr<1059))
               {  //Digital-in routing
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1043;
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        InputStereoSelect[ChannelNr] = Data[5];
                        SetRoutingAndLevel(ChannelNr);

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1059) && (ObjectNr<1075))
               {  //Digital-in level
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1059;
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
               else if ((ObjectNr>=1075) && (ObjectNr<1091))
               {  //Digital-in phase
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1075;
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
               else if ((ObjectNr>=1107) && (ObjectNr<1123))
               {  //Digital-out routing
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1107;
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        OutputStereoSelect[ChannelNr] = Data[5];
                        SetRoutingAndLevel(ChannelNr);

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1123) && (ObjectNr<1139))
               {  //Digital-out level
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1123;
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
               else if ((ObjectNr>=1139) && (ObjectNr<1155))
               {  //Digital-out phase
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1139;
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
               else if ((ObjectNr>=1155) && (ObjectNr<1171))
               {  //Digital-out dim
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1155;

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
               else if ((ObjectNr>=1171) && (ObjectNr<1187))
               {  //Digital-out dim level
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1171;

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
               else if ((ObjectNr>=1187) && (ObjectNr<1315))
               {  //Digital-out talkback
                  unsigned char TalkbackNr;
                  unsigned char OutputNr;

                  TalkbackNr = (ObjectNr-1187)&0x0F;
                  OutputNr = ((ObjectNr-1187)>>4)&0x07;

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
               else if ((ObjectNr>=1315) && (ObjectNr<1331))
               {  //Digital-out talkback routing
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1315;
                  if (DataType == STATE_DATATYPE)
                  {
                     if (DataSize == 1)
                     {
                        OutputTalkbackStereoSelect[ChannelNr] = Data[5];
                        SetRoutingAndLevel(ChannelNr);

                        FormatError = 0;
                        MessageDone = 1;
                     }
                  }
               }
               else if ((ObjectNr>=1331) && (ObjectNr<1347))
               {  //Digital-out talkback level
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1331;

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
               else if ((ObjectNr>=1347) && (ObjectNr<1363))
               {  //Digital-out talkback phase
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1347;
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
               else if ((ObjectNr>=1363) && (ObjectNr<1379))
               {  //Digital-out mute
                  unsigned char ChannelNr;

                  ChannelNr = ObjectNr-1363;
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
               else if (ObjectNr == 1379)
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

   MOSI = 1;// write 1's has no influence in FPGA
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
   nSS=1;
}

void SetRoutingAndLevel(unsigned char ChannelNr)
{
   unsigned char FPGABlockAddress;
   unsigned int StereoSelect;
   float Level;
   unsigned int IntegerLevel;
   char cntNrOfSummation;
   char cntTalkback;
   unsigned int TalkbackData[2];

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

   //Output
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

   StereoSelect = (OutputStereoSelect[(ChannelNr&0xFE)]&0x03);
   StereoSelect |= (OutputStereoSelect[(ChannelNr&0xFE)+1]&0x03)<<2;
   if (OutputMute[(ChannelNr&0xFE)])
   {
      StereoSelect |= 0x0100;
   }
   if (OutputMute[(ChannelNr&0xFE)+1])
   {
      StereoSelect |= 0x0200;
   }
   StereoSelect |= (OutputTalkbackStereoSelect[(ChannelNr&0xFE)]&0x03)<<4;
   StereoSelect |= (OutputTalkbackStereoSelect[(ChannelNr&0xFE)+1]&0x03)<<6;
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
   AddressValidated = 0;
   timerReservationInfo = 1;
}