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

#include "axum-rack-pwr.h"
#include "CANTransportLayer.h"
#include "axum-rack-pwr-MambaNet.h"
// I2C Bus functions
#asm
   .equ __i2c_port=0x0B ;PORTD
   .equ __sda_bit=1
   .equ __scl_bit=0
#endasm
#include <i2c.h>

unsigned int cntFanTimer;
unsigned int Previous_cntFanTimer;
unsigned int Previous_cntDebug;

unsigned char PowerFail;
unsigned char cntDebugLED;

/**********************************/
// Timer 0 output compare interrupt service routine
interrupt [TIM0_COMP] void timer0_comp_isr(void)
{
   //every 100 useconds a pulse.
   cntTimer0++;
   if (cntTimer0 > 10)
   {  //1mS
      cntTimer0 = 0;
      cntMilliSecond++;
   }
   cntFanTimer++;
}

// External Interrupt 7 service routine
interrupt [EXT_INT7] void ext_int7_isr(void)
{
   FanTimerCount += cntFanTimer-Previous_cntFanTimer;
   FanTachoCount++; 
      
   Previous_cntFanTimer = cntFanTimer;
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
   // Func7=Out Func6=Out Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
   // State7=1 State6=1 State5=T State4=T State3=P State2=P State1=P State0=P
   PORTA=0xCF;
   DDRA=0xC0;

   // Port B initialization
   // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
   // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
   PORTB=0x00;
   DDRB=0x00;

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
   // Func7=In Func6=In Func5=In Func4=Out Func3=Out Func2=Out Func1=Out Func0=In
   // State7=T State6=T State5=T State4=1 State3=1 State2=1 State1=0 State0=T
   PORTE=0x1C;
   DDRE=0x1E;

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
   // Clock value: 16000.000 kHz
   // Mode: Ph. correct PWM top=03FFh
   // OC3A output: Non-Inv.
   // OC3B output: Discon.
   // OC3C output: Discon.
   // Noise Canceler: Off
   // Input Capture on Falling Edge
   // Timer 3 Overflow Interrupt: Off
   // Input Capture Interrupt: Off
   // Compare A Match Interrupt: Off
   // Compare B Match Interrupt: Off
   // Compare C Match Interrupt: Off
   TCCR3A=0x83;
   TCCR3B=0x01;
   TCNT3H=0x00;
   TCNT3L=0x00;
   ICR3H=0x00;
   ICR3L=0x00;
   OCR3AH=0x02;
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
   // INT7: On
   // INT7 Mode: Rising Edge
   EICRA=0x00;
   EICRB=0xC0;
   EIMSK=0x80;
   EIFR=0x80;

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
   
   delay_ms(250);
   
   HardwareMinorRevision = PINA&0x0F;
   FPGAFirmwareMajorRevision = 0;
   FPGAFirmwareMinorRevision = 0;

   // I2C Bus initialization
   i2c_init(); 

   // CAN Controller initialization
   InitializeCAN();

   TransmitCANMessageBufferLength = 0;
   cntTransmitCANMessageBuffer = 0;

   PreviousMilliSecond = 0;

   RackSlotNr = GetSlotNr();
   
   PreviousPre_5V    = 0;
   PreviousPre_15V   = 0;
   PreviousPre_n15V  = 0;
   FanSpeed = 0;
   SpeedSet = 1023;
   
   InitTMP75(); 
   
   LEDRED = 0;
   LEDGRN = 1;
   delay_ms(500);
   LEDRED = 1;
   LEDGRN = 0;
   delay_ms(500);
   LEDRED = 0;
   LEDGRN = 0;
   delay_ms(500);
                 
   PowerFail = 0;
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

      if ((cntMilliSecond - PreviousLEDBlinkMilliSecond) > 250)
      {  //LED Blink 4 times per second.       
         PreviousLEDBlinkMilliSecond = cntMilliSecond;
//         Debug[500] = cntDebug;

         if (AddressValidated)
         {
            if (PowerFail) 
            {
               LEDRED = cntDebugLED++&0x04;
               LEDGRN = 0;        
            }
            else
            {
               LEDRED = 0;        
               LEDGRN = cntDebugLED++&0x04;
            }
         }
         else
         {
            if (PowerFail)
            {
               LEDRED = cntDebugLED++&0x01;
               LEDGRN = 0;        
            }
            else
            {
               LEDRED = 0;        
               LEDGRN = cntDebugLED++&0x01;
            }
         }


         if (FanTachoCount != 0)
         {
            FanSpeed = (int)((float)10000/((float)FanTimerCount/FanTachoCount));
         }
         FanTimerCount = 0;
         FanTachoCount = 0; 

         CurrentTemperature = ReadTMP75();            
      }
      
      Pre_5V  = ((float)adc_data[0]*(5*((10+10)/10)))/1023;
      Pre_15V  = ((float)adc_data[2]*(5*((1+10)/1)))/1023;
      Pre_n15V  = 5-(((5-(((float)adc_data[4]*5)/1023))/2)*(2+10));
      if ((Pre_5V>4.5) && (Pre_15V>14) && (Pre_n15V<-14))
      {
         PowerFail = 0;
      }
      else if (PowerFail == 0)
      {
         PowerFail = 1;
         LEDRED = 1;
         LEDGRN = 0;
      }
                   
      if (ObjectWritableInformation[1].UpdateFrequency)
      {
         unsigned int ms_to_wait = GetMillisecondsToWaitFromObjectFrequency(ObjectWritableInformation[1].UpdateFrequency);
         
         if ((cntMilliSecond - PreviousPre_5VCheckMilliSecond) > ms_to_wait)
         {
            if (PreviousPre_5V != Pre_5V) 
            {
               unsigned char Voltage[2];
               
               Float2VariableFloat(Pre_5V, 2, Voltage);

               SendSensorChangeToMambaNet(1025, FLOAT_DATATYPE, 2, Voltage);
               PreviousPre_5V = Pre_5V;
            }
            PreviousPre_5VCheckMilliSecond = cntMilliSecond;
         }         
      }
      
      if (ObjectWritableInformation[2].UpdateFrequency)
      {
         unsigned int ms_to_wait = GetMillisecondsToWaitFromObjectFrequency(ObjectWritableInformation[2].UpdateFrequency);

         if ((cntMilliSecond - PreviousPre_15VCheckMilliSecond) > ms_to_wait)
         {
            if (PreviousPre_15V != Pre_15V)
            {
               unsigned char Voltage[2];
               
               Float2VariableFloat(Pre_15V, 2, Voltage);

               SendSensorChangeToMambaNet(1026, FLOAT_DATATYPE, 2, Voltage);
               PreviousPre_15V = Pre_15V;
            }
            PreviousPre_15VCheckMilliSecond = cntMilliSecond;
         }         
      }            

      if (ObjectWritableInformation[3].UpdateFrequency)
      {
         unsigned int ms_to_wait = GetMillisecondsToWaitFromObjectFrequency(ObjectWritableInformation[3].UpdateFrequency);

         if ((cntMilliSecond - PreviousPre_n15VCheckMilliSecond) > ms_to_wait)
         {
            if (PreviousPre_n15V != Pre_n15V)
            {
               unsigned char Voltage[2];
               
               Float2VariableFloat(Pre_n15V, 2, Voltage);

               SendSensorChangeToMambaNet(1027, FLOAT_DATATYPE, 2, Voltage);
               PreviousPre_n15V = Pre_n15V;
            }
            PreviousPre_n15VCheckMilliSecond = cntMilliSecond;
         }
      }

      
      if (ObjectWritableInformation[4].UpdateFrequency == 1)
      {
         unsigned int ms_to_wait = GetMillisecondsToWaitFromObjectFrequency(ObjectWritableInformation[4].UpdateFrequency);

         if ((cntMilliSecond - PreviousFanSpeedCheckMilliSecond) > ms_to_wait)
         {           
            if (PreviousFanSpeed != FanSpeed)
            {
               unsigned char FanSpeedData[2];
                              
               FanSpeedData[0] = (((int)FanSpeed)>>8)&0xFF;
               FanSpeedData[1] = ((int)FanSpeed)&0xFF;

               SendSensorChangeToMambaNet(1028, UNSIGNED_INTEGER_DATATYPE, 2, FanSpeedData);
               PreviousFanSpeed = FanSpeed;
            }        
         }
      }

      if (ObjectWritableInformation[5].UpdateFrequency == 1)
      {
         unsigned int ms_to_wait = GetMillisecondsToWaitFromObjectFrequency(ObjectWritableInformation[5].UpdateFrequency);

         if ((cntMilliSecond - PreviousTemperatureCheckMilliSecond) > ms_to_wait)
         {
            if (PreviousTemperature != CurrentTemperature)
            {
               unsigned char TemperatureData[2];   
               
               Float2VariableFloat(CurrentTemperature, 2, TemperatureData);

               SendSensorChangeToMambaNet(1029, FLOAT_DATATYPE, 2, TemperatureData);               
               PreviousTemperature = CurrentTemperature;
            }
            PreviousTemperatureCheckMilliSecond = cntMilliSecond;        
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
               unsigned char TransmitBuffer[21];

               // if (ObjectNr<1024) is handled in the stack
               if ((ObjectNr>=1024) && (ObjectNr<1025))
               {  //Rack slot address
                  RackSlotNr = GetSlotNr();
                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                  TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                  TransmitBuffer[4] = 1;
                  TransmitBuffer[5] = RackSlotNr;

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1025) && (ObjectNr<1028))   
               {  //+5V Pre  
                  float Voltage;
                  
                  switch (ObjectNr)
                  {
                     case 1025:
                     {
                        Voltage = Pre_5V;
                     }
                     break;
                     case 1026:
                     {
                        Voltage = Pre_15V;
                     }
                     break;
                     case 1027:
                     {
                        Voltage = Pre_n15V;
                     }
                     break;
                  }
                  
                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                  TransmitBuffer[3] = FLOAT_DATATYPE;
                  TransmitBuffer[4] = 2;
                  Float2VariableFloat(Voltage, 2, &TransmitBuffer[5]);

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 7);

                  MessageDone = 1;
               }
               else if ((ObjectNr>=1028) && (ObjectNr<1029))   
               {  //Fan speed                    
                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                  TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                  TransmitBuffer[4] = 2;
                  TransmitBuffer[5] = (FanSpeed>>8)&0xFF;
                  TransmitBuffer[6] = FanSpeed&0xFF;

                  SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 7);

                  MessageDone = 1;
               }               
               else if ((ObjectNr>=1029) && (ObjectNr<1030))   
               {  //Temperature                    
                  TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                  TransmitBuffer[1] = ObjectNr&0xFF;
                  TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                  TransmitBuffer[3] = FLOAT_DATATYPE;
                  TransmitBuffer[4] = 2;
                  Float2VariableFloat(CurrentTemperature, 2, &TransmitBuffer[5]);

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

               if ((ObjectNr>=1028) && (ObjectNr<1029))
               {  //FAN Speed
                  TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                  TransmitBuffer[4] = 2;
                  TransmitBuffer[5] = ((SpeedSet>>8)&0xFF);
                  TransmitBuffer[6] = (SpeedSet&0xFF);

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

               if ((ObjectNr>=1028) && (ObjectNr<1029))
               {  //FAN Speed
                  if (DataType == UNSIGNED_INTEGER_DATATYPE)
                  {
                     if (DataSize == 2)
                     {
                        unsigned int PWMValue;
                        
                        SpeedSet = ((unsigned int)Data[5]<<8) | Data[6];
                        
                        PWMValue = (0x3FF*SpeedSet)/1023;

                        OCR3AH=(PWMValue>>8)&0xFF;
                        OCR3AL=PWMValue&0xFF;
                         
                        if (SpeedSet>=512)
                        {
                           POWER_FAN = 1;
                        }
                        else
                        {
                           POWER_FAN = 0;
                        }

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
   delay_ms(2);
   TempSlotNrA = (PINB>>4)&0x0F;

   READ_SLOTADR = 1;
   delay_ms(2);
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

void CanBussError()
{
   //AddressValidated = 0;
   //timerReservationInfo = 1;
}

unsigned int GetMillisecondsToWaitFromObjectFrequency(unsigned char ObjectFrequency)
{
   unsigned int MillisecondsToWait = 0;
   switch (ObjectFrequency)
   {
      default:
      {
         MillisecondsToWait = 1000;
      }
      break;
      case 1:
      {
         MillisecondsToWait = 1000;
      }
      break;
      case 2:
      {
         MillisecondsToWait = 40;
      }
      break;
      case 3:
      {
         MillisecondsToWait = 100;
      }
      break;
      case 4:
      {
         MillisecondsToWait = 200;
      }
      break;
      case 5:
      {
         MillisecondsToWait = 1000;
      }
      break;
      case 6:
      {
         MillisecondsToWait = 5000;
      }
      break;
      case 7:
      {
         MillisecondsToWait = 10000;
      }
      break;
   }     
   
   return MillisecondsToWait;
}

void InitTMP75()
{
   i2c_start();
   i2c_write(0x90);
   i2c_write(0x01);
   i2c_write(0x60);
   i2c_stop();
}

float ReadTMP75()
{
   int IntegerTemperature;
   float FloatTemperature;

   i2c_start();
   i2c_write(0x90);
   i2c_write(0x00);
   i2c_stop();
   i2c_start();
   i2c_write(0x91);
   IntegerTemperature = i2c_read(1);
   IntegerTemperature <<= 8;
   IntegerTemperature |= i2c_read(0);
   i2c_stop();
   
   FloatTemperature = (float)((float)IntegerTemperature)/256; 

   return FloatTemperature;
}