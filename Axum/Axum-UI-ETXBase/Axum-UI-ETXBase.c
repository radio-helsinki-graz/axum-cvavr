/*****************************************************
This program was produced by the
CodeWizardAVR V1.25.3 Standard
Automatic Program Generator
© Copyright 1998-2007 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Axum-UI-ETXBase
Version : 
Date    : 5-10-2007
Author  : Anton Prins        
Company : DR Electronica Weesp b.v.       
Comments: 


Chip type           : AT90CAN32
Program type        : Application
Clock frequency     : 8,000000 MHz
Memory model        : Small
External SRAM size  : 0
Data Stack size     : 512
*****************************************************/

//#define LCD_CONNECTED

#include <90can32.h>
#include <stdio.h>
#include <string.h>

#include "Axum-UI-ETXBase.h"
#include "CANTransportLayerGateway.h"
//processor must run 16 Mhz
//you require to have defined:
//- the CAN processor via an included header
//- RS_CAN (port to enable the physical driver
//- implementation of the function:
//  extern void ProcessMambaNetMessage7BitsDataFromCAN(unsigned long int ToAddress, unsigned long int FromAddress, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength);
//- add the include-path to your project
//- implementation of the global variabls:
//  unsigned int ManufacturerID;
//  unsigned int ProductID;
//  eeprom unsigned int UniqueIDPerProduct;
//  extern unsigned char CANServices;
//#include "Axum-UI-ETXBase-MambaNet.h"


#ifdef LCD_CONNECTED            
   #define 	D4LCD  		   PORTA.7
   #define 	D5LCD  			PORTA.6
   #define 	D6LCD  			PORTA.5
   #define 	D7LCD  			PORTA.4
   #define 	LCD_D7_nBF     DDRA.4
   #define  LCD_BF         PINA.4
   #define	RW_LCD			PORTA.3
   #define	E_LCD				PORTA.2
   #define	RS_LCD			PORTA.1
   #define  BLANK          PORTA.0

   #include "lcd.h"
#else
   #define	DEBUG_LED		PORTA.3
   
   unsigned char LEDDebug;
#endif

extern unsigned char AddressValidated;

unsigned long int cntAlive;
#ifdef LCD_CONNECTED            
unsigned char DebugString[64];  
#endif
unsigned long int cntUSART1DataOverrun;
unsigned long int cntUSART1FramingError;
unsigned long int cntUSART1ParityError;
                                          
unsigned long int cntMambaNetFormatErrorFromSerial;
unsigned long int cntTransmitOverrunToUART;

unsigned char cntReceivedSerialMessageBuffer;
unsigned char ReceivedSerialMessageBuffer[128];
//unsigned char ReceivedSerialMessageBuffer[4][128];
unsigned char SerialReceiveMambaNetMessage;

//unsigned int ReceivedSerialMessageBufferToCANAddress[4];
//unsigned char ReceivedSerialMessageBufferLength[4];
//unsigned char cntReceivedSerialMessageBufferTop=0;
//unsigned char cntReceivedSerialMessageBufferBottom=0;


/**********************************/
// Timer 0 output compare interrupt service routine
interrupt [TIM0_COMP] void timer0_comp_isr(void)
{
   //every 100 useconds a pulse.
//   cntTimer0++;
//   if (cntTimer0 == 10)
//   {  //1mS
//      cntTimer0 = 0;
      cntMilliSecond++;     
//   }
}

#define FIRST_ADC_INPUT 0
#define LAST_ADC_INPUT 1
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

// 2 Wire bus interrupt service routine
interrupt [TWI] void twi_isr(void)
{
   // Place your code here

}

#define RXB8 1
#define TXB8 0
#define UPE 2
#define OVR 3
#define FE 4
#define UDRE 5
#define RXC 7

#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<UPE)
#define DATA_OVERRUN (1<<OVR)
#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)

// USART1 Receiver buffer
#ifdef _CHIP_AT90CAN32_
   #define RX_BUFFER_SIZE1 128
#else
   #define RX_BUFFER_SIZE1 512
#endif
char rx_buffer1[RX_BUFFER_SIZE1];

#if RX_BUFFER_SIZE1<256
unsigned char rx_wr_index1,rx_rd_index1,rx_counter1;
#else
unsigned int rx_wr_index1,rx_rd_index1,rx_counter1;
#endif

// This flag is set on USART1 Receiver buffer overflow
bit rx_buffer_overflow1;

// USART1 Receiver interrupt service routine
interrupt [USART1_RXC] void usart1_rx_isr(void)
{
   char status,data;
   status=UCSR1A;
   data=UDR1;
   if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
   {
      rx_buffer1[rx_wr_index1]=data;
      if (++rx_wr_index1 == RX_BUFFER_SIZE1) 
      {
         rx_wr_index1=0;
      }

      if (++rx_counter1 == RX_BUFFER_SIZE1)
      {
         rx_counter1=0;
         rx_buffer_overflow1=1;
      };
   }
   else
   {
      if (status & DATA_OVERRUN)
      {
         cntUSART1DataOverrun++;
      }
      if (status & FRAMING_ERROR)
      {
         cntUSART1FramingError++;
      }
      if (status & PARITY_ERROR)
      {
         cntUSART1ParityError++;
      }
   }
}

// Get a character from the USART1 Receiver buffer
#pragma used+
char getchar1(void)
{
   char data;
   while (rx_counter1==0);
   data=rx_buffer1[rx_rd_index1];
   if (++rx_rd_index1 == RX_BUFFER_SIZE1)
   {
      rx_rd_index1=0;
   }
   #asm("cli")
   --rx_counter1;
   #asm("sei")
   return data;
}
#pragma used-

// USART1 Transmitter buffer
#ifdef _CHIP_AT90CAN32_
   #define TX_BUFFER_SIZE1 256
#else   
   #define TX_BUFFER_SIZE1 1024
#endif   
char tx_buffer1[TX_BUFFER_SIZE1];

#if TX_BUFFER_SIZE1<256
unsigned char tx_wr_index1,tx_rd_index1,tx_counter1;
#else
unsigned int tx_wr_index1,tx_rd_index1,tx_counter1;
#endif

// USART1 Transmitter interrupt service routine
interrupt [USART1_TXC] void usart1_tx_isr(void)
{
   if (tx_counter1)
   {
      --tx_counter1;
      UDR1=tx_buffer1[tx_rd_index1];
      if (++tx_rd_index1 == TX_BUFFER_SIZE1) 
      {
         tx_rd_index1=0;
      }
   };
}

// Write a character to the USART1 Transmitter buffer
#pragma used+
void putchar1(char c)
{
   while (tx_counter1 == TX_BUFFER_SIZE1);
   #asm("cli")
   if (tx_counter1 || ((UCSR1A & DATA_REGISTER_EMPTY)==0))
   {
      tx_buffer1[tx_wr_index1]=c;
      if (++tx_wr_index1 == TX_BUFFER_SIZE1) 
      {
         tx_wr_index1=0;
      }
      ++tx_counter1;
   }
   else
   {
      UDR1=c;
   }
   #asm("sei")
}
#pragma used-

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
   // State7=T State6=T State5=T State4=T State3=P State2=P State1=P State0=P 
   PORTA=0x0F;
   DDRA=0x00;
   
   // Port B initialization
   // Func7=Out Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
   // State7=0 State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
   PORTB=0x00;
   DDRB=0x00;        //SerIRQ if input
   
   // Port C initialization
   // Func7=In Func6=In Func5=Out Func4=Out Func3=Out Func2=Out Func1=In Func0=In 
   // State7=T State6=T State5=1 State4=1 State3=1 State2=1 State1=T State0=T 
   PORTC=0x3C;
   DDRC=0x3C;
   
   // Port D initialization
   // Func7=Out Func6=In Func5=Out Func4=In Func3=Out Func2=In Func1=In Func0=In 
   // State7=1 State6=T State5=0 State4=T State3=0 State2=T State1=T State0=T 
   PORTD=0x80;
   DDRD=0xA8;
   
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
//   OCR0A=((OSCILLATOR_FREQUENCY/8)*0.0001)-1; //((OSCILLATOR_FREQUENCY/8)*0.0001)-1 => 100uS
   OCR0A=((OSCILLATOR_FREQUENCY/8)*0.001)-1; //((OSCILLATOR_FREQUENCY/8)*0.0001)-1 => 100uS
   
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
   
   // USART1 initialization
   // Communication Parameters: 8 Data, 1 Stop, No Parity
   // USART1 Receiver: On
   // USART1 Transmitter: On
   // USART1 Mode: Asynchronous
   // USART1 Baud rate: 500k (Double Speed Mode)   <- give linux overruns
   // USART1 Baud rate: 250k (Double Speed Mode)
   // USART1 Baud rate: 115200 (Double Speed Mode)
   //250000
   UCSR1A=0x02;
   UCSR1B=0xD8;
   UCSR1C=0x06;
   UBRR1H=0x00;
   UBRR1L=0x07;
   
//UBRR1L=0x22;//57600
//UBRR1L=0x33;//38400
//UBRR1L=0xCF;//9600   
   
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
   ADCSRA=0xCB;
   
   // 2 Wire Bus initialization
   // Generate Acknowledge Pulse: On
   // 2 Wire Bus Slave Address: 0h
   // General Call Recognition: On
   // Bit Rate: 400,000 kHz
   TWSR=0x00;
   TWBR=0x02;
   TWAR=0x01;
   TWCR=0x45;
                       
   InitializeCAN();
   AddressValidated = 1;
   
//   AddressReservationData[0].ManufacturerID        = ManufacturerID;
//   AddressReservationData[0].ProductID             = ProductID;
//   AddressReservationData[0].UniqueIDPerProduct    = UniqueIDPerProduct;
//   AddressReservationData[0].CANAddress            = 0x00000001;
   SetLocalCANAddress(0x00000001);  
   
   cntUSART1DataOverrun = 0;
   cntUSART1FramingError = 0;
   cntUSART1ParityError = 0;
   cntMambaNetFormatErrorFromSerial = 0;
   cntTransmitOverrunToUART = 0;

#ifdef LCD_CONNECTED            
   SetupLCD();
   delay_ms(500);
   sprintf(DebugString, "Start value %04X%04X", GlobalReceiveSequenceCANAddress>>16, GlobalReceiveSequenceCANAddress&0xFFFF);
   SetLCDModule(0, 0, DebugString);
#endif
   cntAlive=0;

   // Global enable interrupts
   #asm("sei")
   
   while (1)
   {             
      // Place your code here     
      if ((cntMilliSecond-PreviousMilliSecond)>1000)
      {
         PreviousMilliSecond = cntMilliSecond;
                               
//         SendCANParentControlMessage();
         
         cntAlive++;  
         
#ifndef LCD_CONNECTED            
         //LEDDebug = !LEDDebug;
         //DEBUG_LED = LEDDebug;
#endif
         
         
         
#ifdef LCD_CONNECTED   
         sprintf(DebugString, "Alive (%d) %04X%04X - S:%02X C:%02X", cntAlive, GlobalReceiveSequenceCANAddress>>16, GlobalReceiveSequenceCANAddress&0xFFFF, Debug_SerialTransmitBufferCount, Debug_CANReceiveBufferCount);
         SetLCDModule(0, 0, DebugString);
#endif         
#ifdef LCD_CONNECTED   
         sprintf(DebugString, "D%d S%d O%d, M%d O%d R%d T%d ", cntUSART1DataOverrun, cntMambaNetFormatErrorFromSerial, cntTransmitOverrunToUART, cntMambaNetFormatErrorFromCAN, cntMambaNetOverrunFromCAN, cntGlobalCANMessageReceived, cntCANMessageTransmitted);
         SetLCDModule(0, 1, DebugString);               
#endif         
      }

     
      while (rx_counter1)
      {
         unsigned char ReceivedByte;

         ReceivedByte = getchar1();       
         
         switch (ReceivedByte)
         {
            case 0xE0:
            {
               if (cntReceivedSerialMessageBuffer>10)
               {
                  cntReceivedSerialMessageBuffer = 0;
               }
            }
            break;
            default:
            {
               switch (cntReceivedSerialMessageBuffer)
               {
                  case 0:
                  {
                     if (ReceivedByte&0x40)
                     {
                        SerialReceiveMambaNetMessage = 0;               
                     }
                     else
                     {
                        SerialReceiveMambaNetMessage = 1;               
                     }                  
                     ToCANAddress = (ReceivedByte<<7)&0x1F;
                  }
                  break;
                  case 1:
                  {
                     ToCANAddress |= ReceivedByte&0x7F;
                  }
                  break; 
                  case 2:
                  {
                     SequenceNumber = ReceivedByte&0x0F; 
                  }
                  break;
                  default: 
                  {
                     if (SerialReceiveMambaNetMessage)
                     {
                        ReceivedSerialMessageBuffer[(SequenceNumber*8)+cntReceivedSerialMessageBuffer-3] = ReceivedByte;
                        if (ReceivedByte == 0xFF)
                        {
                           SendMambaNetMessageToCAN_DedicatedAddress(ToCANAddress, ReceivedSerialMessageBuffer, ((SequenceNumber*8)+cntReceivedSerialMessageBuffer-3)+1);
                        }
                     }
                     else
                     { //CAN Control message
                        ReceivedSerialMessageBuffer[cntReceivedSerialMessageBuffer-3] = ReceivedByte;
                     } 
                  }
                  break; 
               }
               cntReceivedSerialMessageBuffer++; 
            }
            break;
            case 0xE1:
            {
               if (!SerialReceiveMambaNetMessage)
               {  //Parent control message received
                  if (cntReceivedSerialMessageBuffer == 11)
                  {     
                     SendCANParentControlMessage(ReceivedSerialMessageBuffer);
                  }
               }
            }
            break;
         }       
      }


      while (UARTTransmitBufferBottom != UARTTransmitBufferTop)
      {
         char cntTransmitByte;
                 
         for (cntTransmitByte=0; cntTransmitByte<13; cntTransmitByte++)
         {         
            putchar1(UARTTransmitBuffer[UARTTransmitBufferBottom][cntTransmitByte]);
         }
         UARTTransmitBufferBottom++;
         if (UARTTransmitBufferBottom>(NR_OF_UART_BUFFERS-1))
         {
            UARTTransmitBufferBottom = 0;
         }
      }
   }
}

void CanBussError()
{
   //AddressValidated = 0;
   //timerReservationInfo = 1;
}
