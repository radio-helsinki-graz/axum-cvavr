#ifndef Axum_Rack_BackplaneH
#define Axum_Rack_BackplaneH

/********************************/
/* Define Ports                 */
/********************************/
#define  SWF1_LCD       PINA.7			
#define  SWF2_LCD       PINA.6			

#define  nSS            PORTB.0
#define  SCK            PORTB.1
#define  MOSI           PORTB.2
#define  MISO           PINB.3
#define  PB4            PINB.4

#define 	RW_LCD    		PORTC.0
#define 	RS_LCD         PORTC.1

#define 	E_LCD          PORTC.3
#define  D4LCD          PORTC.4
#define	D5LCD  			PORTC.5
#define	D6LCD  			PORTC.6
#define  LCD_D7_nBF     DDRC.7
#define  LCD_BF         PINC.7
#define  D7LCD          PORTC.7

#define  nCON_T         PIND.0
#define  nOTI_T         PIND.1
#define  nWR_T          PIND.2
#define  SCLK_T         PORTD.3
#define  DATA_T         PORTD.4
#define  TXD_CAN        PORTD.5
#define  RXD_CAN        PIND.6
#define  RS_CAN         PORTD.7

#define  PDI            PINE.0
#define  PDO            PORTE.1
#define  EXTR_LOCK      PINE.2
#define  JUMPER1        PINE.4
#define  JUMPER2        PINE.5
#define  JUMPER3        PINE.6
#define  JUMPER4        PINE.7

#define  PLLC0          PORTF.0
#define  PLLC1          PORTF.1
#define  PLLC2          PORTF.2
#define  PLLC3          PORTF.3
#define  PLLC4          PORTF.4
#define  PLLC5          PORTF.5
#define  PLLC6          PORTF.6
#define  PLLC7          PORTF.7

#define  CAN_INT        PING.4

/********************************/
/* Specific defines             */
/********************************/
#define SWITCHDELAY              10
#define TRACK_WIBBLE             4

#define OSCILLATOR_FREQUENCY     16000000

unsigned int cntTimer0;
volatile unsigned int cntMilliSecond;
unsigned int PreviousMilliSecond;
unsigned int PreviousMilliSecondReservation;
unsigned int PreviousLEDBlinkMilliSecond;

unsigned FPGAData[4];
unsigned int FPGAFirmwareType;   

unsigned char FPGAPLLLock;
unsigned char EnableSum[4];
unsigned char Samplerate;

unsigned char PreviousPLLLock;
unsigned char PLLLock;

void ReadFPGA();
void SetFPGA(unsigned int FunctionNr, unsigned int FunctionData);
//void SetPLL1706(unsigned char Mode);
//char SwitchCheck(unsigned char cntRow, unsigned char SwitchNr, char SwitchReturn);
//void ReadSwitches();
//void DoSwitch(unsigned char LogicSwitchNr, int Event);

//Information required for CANTransportLayer.h
//#define CAN_ADDRESS_SERVER

//One of the following functions needs to be implemented, the other should be NULL
//void ProcessMambaNetMessage7BitsDataFromCAN(unsigned long int ToAddress, unsigned long int FromAddress, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength);
void (*ProcessMambaNetMessage7BitsDataFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength) = NULL;

void ProcessMambaNetMessageFromCAN_Imp(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength);
void (*ProcessMambaNetMessageFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength) = ProcessMambaNetMessageFromCAN_Imp;
//void (*ProcessMambaNetMessageFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength) = NULL;

#endif