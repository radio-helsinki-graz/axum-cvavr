#ifndef Axum_Rack_BackplaneH
#define Axum_Rack_BackplaneH

/********************************/
/* Define Ports                 */
/********************************/
#define  PSCK           PINB.1
//#define  nRST_USB       PORTB.4
//#define  PPM_VU         PINB.5
//#define  J18            PINB.6
//#define  J19            PINB.7

#define 	CSEL1          PORTC.0
#define 	CSEL0          PORTC.1
#define 	BLANK  			PORTC.2
#define 	SCLK  			PORTC.3
#define	nLATCH		   PORTC.4
#define	SINL  			PORTC.5
#define	SINR  			PORTC.6

//#define  RXD_USB        PIND.2
//#define  TXD_USB        PORTD.3

#define  TXD_CAN        PORTD.5
#define  RXD_CAN        PIND.6
#define  RS_CAN         PORTD.7

#define  PDI            PINE.0
#define  PDO            PORTE.1

#define  LEFT_LO        PORTF.0
#define  LEFT_HI        PORTF.1
#define  RIGHT_LO       PORTF.2
#define  RIGHT_HI       PORTF.3

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

//char SwitchCheck(unsigned char cntRow, unsigned char SwitchNr, char SwitchReturn);
//void ReadSwitches();
//void DoSwitch(unsigned char LogicSwitchNr, int Event);
void SetTLC5920(char cntBlock);
void SetLeftNrOfLEDs(int NrOfLEDs);
void SetRightNrOfLEDs(int NrOfLEDs);
void SetLeftLEDNr(int LEDNr, char State);
void SetRightLEDNr(int LEDNr, char State);

//Information required for CANTransportLayer.h
//#define CAN_ADDRESS_SERVER

//One of the following functions needs to be implemented, the other should be NULL
//void ProcessMambaNetMessage7BitsDataFromCAN(unsigned long int ToAddress, unsigned long int FromAddress, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength);
void (*ProcessMambaNetMessage7BitsDataFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength) = NULL;

void ProcessMambaNetMessageFromCAN_Imp(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength);
void (*ProcessMambaNetMessageFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength) = ProcessMambaNetMessageFromCAN_Imp;
//void (*ProcessMambaNetMessageFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength) = NULL;

#endif