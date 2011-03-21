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

char pos_to_db_lo[1024];
char pos_to_db_hi[1024];
char db_to_led[120];

int NewLeftPos;
int NewRightPos;

unsigned char LeftNrOfLEDs;
unsigned char RightNrOfLEDs;
unsigned char LeftHoldLEDNr;
unsigned char RightHoldLEDNr;
unsigned char cntLeftHoldTime;
unsigned char cntRightHoldTime;

unsigned char cntBlock;
unsigned char LeftPeak, RightPeak;


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

   LeftPeak = 0;
   RightPeak = 0;

   {
      unsigned int cntPos;

      for (cntPos=0; cntPos<44; cntPos++)
      {
        pos_to_db_lo[cntPos] = 0;
      }
      for (cntPos=44; cntPos<60; cntPos++)
      {
        pos_to_db_lo[cntPos] = 1;
      }
      for (cntPos=60; cntPos<80; cntPos++)
      {
        pos_to_db_lo[cntPos] = 2;
      }
      for (cntPos=80; cntPos<108; cntPos++)
      {
        pos_to_db_lo[cntPos] = 3;
      }
      for (cntPos=108; cntPos<134; cntPos++)
      {
        pos_to_db_lo[cntPos] = 4;
      }
      for (cntPos=134; cntPos<179; cntPos++)
      {
        pos_to_db_lo[cntPos] = 5;
      }
      for (cntPos=179; cntPos<217; cntPos++)
      {
        pos_to_db_lo[cntPos] = 6;
      }
      for (cntPos=217; cntPos<270; cntPos++)
      {
        pos_to_db_lo[cntPos] = 7;
      }
      for (cntPos=270; cntPos<334; cntPos++)
      {
        pos_to_db_lo[cntPos] = 8;
      }
      for (cntPos=334; cntPos<409; cntPos++)
      {
        pos_to_db_lo[cntPos] = 9;
      }
      for (cntPos=409; cntPos<470; cntPos++)
      {
        pos_to_db_lo[cntPos] = 10;
      }
      for (cntPos=470; cntPos<578; cntPos++)
      {
        pos_to_db_lo[cntPos] = 11;
      }
      for (cntPos=578; cntPos<711; cntPos++)
      {
        pos_to_db_lo[cntPos] = 12;
      }
      for (cntPos=711; cntPos<820; cntPos++)
      {
        pos_to_db_lo[cntPos] = 13;
      }
      for (cntPos=820; cntPos<947; cntPos++)
      {
        pos_to_db_lo[cntPos] = 14;
      }
      for (cntPos=947; cntPos<1024; cntPos++)
      {
        pos_to_db_lo[cntPos] = 15;
      }

      for (cntPos=0; cntPos<24; cntPos++)
      {
        pos_to_db_hi[cntPos] = 15;
      }
      for (cntPos=24; cntPos<25; cntPos++)
      {
        pos_to_db_hi[cntPos] = 16;
      }
      for (cntPos=25; cntPos<26; cntPos++)
      {
        pos_to_db_hi[cntPos] = 18;
      }
      for (cntPos=26; cntPos<28; cntPos++)
      {
        pos_to_db_hi[cntPos] = 19;
      }
      for (cntPos=28; cntPos<30; cntPos++)
      {
        pos_to_db_hi[cntPos] = 20;
      }
      for (cntPos=30; cntPos<32; cntPos++)
      {
        pos_to_db_hi[cntPos] = 21;
      }
      for (cntPos=32; cntPos<34; cntPos++)
      {
        pos_to_db_hi[cntPos] = 22;
      }
      for (cntPos=34; cntPos<37; cntPos++)
      {
        pos_to_db_hi[cntPos] = 23;
      }
      for (cntPos=37; cntPos<38; cntPos++)
      {
        pos_to_db_hi[cntPos] = 24;
      }
      for (cntPos=38; cntPos<41; cntPos++)
      {
        pos_to_db_hi[cntPos] = 25;
      }
      for (cntPos=41; cntPos<47; cntPos++)
      {
        pos_to_db_hi[cntPos] = 26;
      }
      for (cntPos=47; cntPos<50; cntPos++)
      {
        pos_to_db_hi[cntPos] = 27;
      }
      for (cntPos=50; cntPos<55; cntPos++)
      {
        pos_to_db_hi[cntPos] = 28;
      }
      for (cntPos=55; cntPos<62; cntPos++)
      {
        pos_to_db_hi[cntPos] = 29;
      }
      for (cntPos=62; cntPos<65; cntPos++)
      {
        pos_to_db_hi[cntPos] = 30;
      }
      for (cntPos=65; cntPos<72; cntPos++)
      {
        pos_to_db_hi[cntPos] = 31;
      }
      for (cntPos=72; cntPos<78; cntPos++)
      {
        pos_to_db_hi[cntPos] = 32;
      }
      for (cntPos=78; cntPos<82; cntPos++)
      {
        pos_to_db_hi[cntPos] = 33;
      }
      for (cntPos=82; cntPos<92; cntPos++)
      {
        pos_to_db_hi[cntPos] = 34;
      }
      for (cntPos=92; cntPos<100; cntPos++)
      {
        pos_to_db_hi[cntPos] = 35;
      }
      for (cntPos=100; cntPos<111; cntPos++)
      {
        pos_to_db_hi[cntPos] = 36;
      }
      for (cntPos=111; cntPos<117; cntPos++)
      {
        pos_to_db_hi[cntPos] = 37;
      }
      for (cntPos=117; cntPos<126; cntPos++)
      {
        pos_to_db_hi[cntPos] = 38;
      }
      for (cntPos=126; cntPos<132; cntPos++)
      {
        pos_to_db_hi[cntPos] = 39;
      }
      for (cntPos=132; cntPos<149; cntPos++)
      {
        pos_to_db_hi[cntPos] = 40;
      }
      for (cntPos=149; cntPos<159; cntPos++)
      {
        pos_to_db_hi[cntPos] = 41;
      }
      for (cntPos=159; cntPos<168; cntPos++)
      {
        pos_to_db_hi[cntPos] = 42;
      }
      for (cntPos=168; cntPos<178; cntPos++)
      {
        pos_to_db_hi[cntPos] = 43;
      }
      for (cntPos=178; cntPos<200; cntPos++)
      {
        pos_to_db_hi[cntPos] = 44;
      }
      for (cntPos=200; cntPos<216; cntPos++)
      {
        pos_to_db_hi[cntPos] = 45;
      }
      for (cntPos=216; cntPos<227; cntPos++)
      {
        pos_to_db_hi[cntPos] = 46;
      }
      for (cntPos=227; cntPos<241; cntPos++)
      {
        pos_to_db_hi[cntPos] = 47;
      }
      for (cntPos=241; cntPos<255; cntPos++)
      {
        pos_to_db_hi[cntPos] = 48;
      }
      for (cntPos=255; cntPos<272; cntPos++)
      {
        pos_to_db_hi[cntPos] = 49;
      }
      for (cntPos=272; cntPos<287; cntPos++)
      {
        pos_to_db_hi[cntPos] = 50;
      }
      for (cntPos=287; cntPos<307; cntPos++)
      {
        pos_to_db_hi[cntPos] = 51;
      }
      for (cntPos=307; cntPos<325; cntPos++)
      {
        pos_to_db_hi[cntPos] = 52;
      }
      for (cntPos=325; cntPos<347; cntPos++)
      {
        pos_to_db_hi[cntPos] = 53;
      }
      for (cntPos=347; cntPos<367; cntPos++)
      {
        pos_to_db_hi[cntPos] = 54;
      }
      for (cntPos=367; cntPos<388; cntPos++)
      {
        pos_to_db_hi[cntPos] = 55;
      }
      for (cntPos=388; cntPos<413; cntPos++)
      {
        pos_to_db_hi[cntPos] = 56;
      }
      for (cntPos=413; cntPos<444; cntPos++)
      {
        pos_to_db_hi[cntPos] = 57;
      }
      for (cntPos=444; cntPos<467; cntPos++)
      {
        pos_to_db_hi[cntPos] = 58;
      }
      for (cntPos=467; cntPos<494; cntPos++)
      {
        pos_to_db_hi[cntPos] = 59;
      }
      for (cntPos=494; cntPos<1024; cntPos++)
      {
        pos_to_db_hi[cntPos] = 60;
      }

      for (cntPos=0; cntPos<3; cntPos++)
      {
        db_to_led[cntPos] = 0;
      }
      for (cntPos=3; cntPos<7; cntPos++)
      {
        db_to_led[cntPos] = 1;
      }
      for (cntPos=7; cntPos<11; cntPos++)
      {
        db_to_led[cntPos] = 2;
      }
      for (cntPos=11; cntPos<15; cntPos++)
      {
        db_to_led[cntPos] = 3;
      }
      for (cntPos=15; cntPos<18; cntPos++)
      {
        db_to_led[cntPos] = 4;
      }
      for (cntPos=18; cntPos<22; cntPos++)
      {
        db_to_led[cntPos] = 5;
      }
      for (cntPos=22; cntPos<25; cntPos++)
      {
        db_to_led[cntPos] = 6;
      }
      for (cntPos=25; cntPos<28; cntPos++)
      {
        db_to_led[cntPos] = 7;
      }
      for (cntPos=28; cntPos<31; cntPos++)
      {
        db_to_led[cntPos] = 8;
      }
      for (cntPos=31; cntPos<34; cntPos++)
      {
        db_to_led[cntPos] = 9;
      }
      for (cntPos=34; cntPos<36; cntPos++)
      {
        db_to_led[cntPos] = 10;
      }
      for (cntPos=36; cntPos<39; cntPos++)
      {
        db_to_led[cntPos] = 11;
      }
      for (cntPos=39; cntPos<42; cntPos++)
      {
        db_to_led[cntPos] = 12;
      }
      for (cntPos=42; cntPos<44; cntPos++)
      {
        db_to_led[cntPos] = 13;
      }
      for (cntPos=44; cntPos<46; cntPos++)
      {
        db_to_led[cntPos] = 14;
      }
      for (cntPos=46; cntPos<49; cntPos++)
      {
        db_to_led[cntPos] = 15;
      }
      for (cntPos=49; cntPos<51; cntPos++)
      {
        db_to_led[cntPos] = 16;
      }
      for (cntPos=51; cntPos<53; cntPos++)
      {
        db_to_led[cntPos] = 17;
      }
      for (cntPos=53; cntPos<55; cntPos++)
      {
        db_to_led[cntPos] = 18;
      }
      for (cntPos=55; cntPos<57; cntPos++)
      {
        db_to_led[cntPos] = 19;
      }
      for (cntPos=57; cntPos<59; cntPos++)
      {
        db_to_led[cntPos] = 20;
      }
      for (cntPos=59; cntPos<61; cntPos++)
      {
        db_to_led[cntPos] = 21;
      }
      for (cntPos=61; cntPos<63; cntPos++)
      {
        db_to_led[cntPos] = 22;
      }
      for (cntPos=63; cntPos<65; cntPos++)
      {
        db_to_led[cntPos] = 23;
      }
      for (cntPos=65; cntPos<66; cntPos++)
      {
        db_to_led[cntPos] = 24;
      }
      for (cntPos=66; cntPos<68; cntPos++)
      {
        db_to_led[cntPos] = 25;
      }
      for (cntPos=68; cntPos<70; cntPos++)
      {
        db_to_led[cntPos] = 26;
      }
      for (cntPos=70; cntPos<71; cntPos++)
      {
        db_to_led[cntPos] = 27;
      }
      for (cntPos=71; cntPos<73; cntPos++)
      {
        db_to_led[cntPos] = 28;
      }
      for (cntPos=73; cntPos<75; cntPos++)
      {
        db_to_led[cntPos] = 29;
      }
      for (cntPos=75; cntPos<76; cntPos++)
      {
        db_to_led[cntPos] = 30;
      }
      for (cntPos=76; cntPos<78; cntPos++)
      {
        db_to_led[cntPos] = 31;
      }
      for (cntPos=78; cntPos<79; cntPos++)
      {
        db_to_led[cntPos] = 32;
      }
      for (cntPos=79; cntPos<80; cntPos++)
      {
        db_to_led[cntPos] = 33;
      }
      for (cntPos=80; cntPos<82; cntPos++)
      {
        db_to_led[cntPos] = 34;
      }
      for (cntPos=82; cntPos<83; cntPos++)
      {
        db_to_led[cntPos] = 35;
      }
      for (cntPos=83; cntPos<85; cntPos++)
      {
        db_to_led[cntPos] = 36;
      }
      for (cntPos=85; cntPos<86; cntPos++)
      {
        db_to_led[cntPos] = 37;
      }
      for (cntPos=86; cntPos<87; cntPos++)
      {
        db_to_led[cntPos] = 38;
      }
      for (cntPos=87; cntPos<88; cntPos++)
      {
        db_to_led[cntPos] = 39;
      }
      for (cntPos=88; cntPos<90; cntPos++)
      {
        db_to_led[cntPos] = 40;
      }
      for (cntPos=90; cntPos<91; cntPos++)
      {
        db_to_led[cntPos] = 41;
      }
      for (cntPos=91; cntPos<92; cntPos++)
      {
        db_to_led[cntPos] = 42;
      }
      for (cntPos=92; cntPos<93; cntPos++)
      {
        db_to_led[cntPos] = 43;
      }
      for (cntPos=93; cntPos<95; cntPos++)
      {
        db_to_led[cntPos] = 44;
      }
      for (cntPos=95; cntPos<96; cntPos++)
      {
        db_to_led[cntPos] = 45;
      }
      for (cntPos=96; cntPos<97; cntPos++)
      {
        db_to_led[cntPos] = 46;
      }
      for (cntPos=97; cntPos<98; cntPos++)
      {
        db_to_led[cntPos] = 47;
      }
      for (cntPos=98; cntPos<99; cntPos++)
      {
        db_to_led[cntPos] = 48;
      }
      for (cntPos=99; cntPos<100; cntPos++)
      {
        db_to_led[cntPos] = 49;
      }
      for (cntPos=100; cntPos<101; cntPos++)
      {
        db_to_led[cntPos] = 50;
      }
      for (cntPos=101; cntPos<102; cntPos++)
      {
        db_to_led[cntPos] = 51;
      }
      for (cntPos=102; cntPos<103; cntPos++)
      {
        db_to_led[cntPos] = 52;
      }
      for (cntPos=103; cntPos<104; cntPos++)
      {
        db_to_led[cntPos] = 53;
      }
      for (cntPos=104; cntPos<105; cntPos++)
      {
        db_to_led[cntPos] = 54;
      }
      for (cntPos=105; cntPos<106; cntPos++)
      {
        db_to_led[cntPos] = 55;
      }
      for (cntPos=106; cntPos<107; cntPos++)
      {
        db_to_led[cntPos] = 56;
      }
      for (cntPos=107; cntPos<108; cntPos++)
      {
        db_to_led[cntPos] = 57;
      }
      for (cntPos=108; cntPos<109; cntPos++)
      {
        db_to_led[cntPos] = 58;
      }
      for (cntPos=109; cntPos<110; cntPos++)
      {
        db_to_led[cntPos] = 59;
      }
      for (cntPos=110; cntPos<120; cntPos++)
      {
        db_to_led[cntPos] = 60;
      }
   }
   // CAN Controller initialization
   InitializeCAN();

   BLANK = 0;

   TransmitCANMessageBufferLength = 0;
   cntTransmitCANMessageBuffer = 0;

   PreviousMilliSecond = 0;

   cntBlock = 0;
   LeftNrOfLEDs = 0;
   RightNrOfLEDs = 0;
   LeftHoldLEDNr = 0;
   RightHoldLEDNr = 0;
   NewLeftPos = 0;
   NewRightPos = 0;

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

/* ADC data debug output via MambaNet
         {
            unsigned char mData[2];
            mData[0] = (((int)adc_data[0])>>8)&0xFF;
            mData[1] = ((int)adc_data[0])&0xFF;
            SendSensorChangeToMambaNet(1100, UNSIGNED_INTEGER_DATATYPE, 2, mData);

            mData[0] = (((int)adc_data[1])>>8)&0xFF;
            mData[1] = ((int)adc_data[1])&0xFF;
            SendSensorChangeToMambaNet(1101, UNSIGNED_INTEGER_DATATYPE, 2, mData);
         }
*/
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


         if (!AddressValidated)
         {
            if (adc_data[0]<1023)
            {
              LeftPeak = 0;
              NewLeftPos = pos_to_db_lo[adc_data[0]];
            }
            else if (adc_data[1]<1023)
            {
              LeftPeak = 0;
              NewLeftPos = pos_to_db_hi[adc_data[1]];
            }
            else
            {
              LeftPeak = 1;
              NewLeftPos = pos_to_db_hi[1023];
            }

            if (NewLeftPos>LeftNrOfLEDs)
            {
               LeftNrOfLEDs = NewLeftPos;
            }

            if (adc_data[2]<1023)
            {
              RightPeak = 0;
              NewRightPos = pos_to_db_lo[adc_data[2]];
            }
            else if (adc_data[3]<1023)
            {
              RightPeak = 0;
              NewRightPos = pos_to_db_hi[adc_data[3]];
            }
            else
            {
              RightPeak = 1;
              NewRightPos = pos_to_db_hi[1023];
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

         //Peak hold
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

         SetLeftNrOfLEDs(LeftNrOfLEDs);
         SetRightNrOfLEDs(RightNrOfLEDs);
         SetLeftLEDNr(LeftHoldLEDNr, 1);
         SetRightLEDNr(RightHoldLEDNr, 1);
      }

      if (AddressValidated)
      {
        LEDDataLeft[0] |= 0x8000;
      }
      else
      {
         LEDDataLeft[0] &= 0x7FFF;
      }
      LEDDataRight[0] |= 0x8000;

      if (LeftPeak)
      {
        LEDDataLeft[3] |= 0x8000;
      }
      else
      {
        LEDDataLeft[3] &= 0x7FFF;
      }

      if (RightPeak)
      {
        LEDDataRight[3] |= 0x8000;
      }
      else
      {
        LEDDataRight[3] &= 0x7FFF;
      }
   }
}

void ProcessMambaNetMessageFromCAN_Imp(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength)
{
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
                              int Pos = (dB*2);
                              NewLeftPos = db_to_led[Pos];
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
                              int Pos = (dB*2);
                              NewRightPos = db_to_led[Pos];
                           }

                           if (NewRightPos>RightNrOfLEDs)
                           {
                              RightNrOfLEDs = NewRightPos;
                           }
                        }
                     }
                  }
                  break;
                  case 1026:
                  {
                     if (Data[3] == STATE_DATATYPE)
                     {
                        LeftPeak = Data[5];
                     }
                  }
                  break;
                  case 1027:
                  {
                     if (Data[3] == STATE_DATATYPE)
                     {
                        RightPeak = Data[5];
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
   ToAddress++;
   FromAddress++;
   DataLength++;
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