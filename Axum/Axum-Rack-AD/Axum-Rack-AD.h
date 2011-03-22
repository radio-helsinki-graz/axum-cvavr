#ifndef Axum_Rack_ADH
#define Axum_Rack_ADH

/********************************/
/* Define Ports                 */
/********************************/
#define  OVL8           PINA.0
#define  OVL7           PINA.1
#define  OVL6           PINA.2
#define  OVL5           PINA.3
#define  OVL4           PINA.4
#define  OVL3           PINA.5
#define  OVL2           PINA.6
#define  OVL1           PINA.7

#define  nSS            PORTB.0
#define  SCK_PSCK       PORTB.1
#define  PSCK           PINB.1
#define  MOSI           PORTB.2
#define  MISO           PINB.3
#define  SLOTADR0       PINB.4
#define  SLOTADR1       PINB.5
#define  SLOTADR2       PINB.6
#define  SLOTADR3       PINB.7

#define 	nLO_L1 		   PORTC.0
#define 	nLG_L1  			PORTC.1
#define 	GPO2  			PORTC.2
#define 	GPO1  			PORTC.3
#define	nLO_L2			PORTC.4
#define	nLG_L2			PORTC.5
#define	GPO4  			PORTC.6
#define  GPO3           PORTC.7

#define  nREAD_OVL      PORTD.2
#define  nACT_LED       PORTD.3
#define  RS_CAN         PORTD.4
#define  TXD_CAN        PORTD.5
#define  RXD_CAN        PIND.6
#define  IO115          PIND.7

#define  PDI_GPO5       PORTE.0
#define  PDO_GPO6       PORTE.1
#define  nLO_L3         PORTE.2
#define  nLG_L3         PORTE.3
#define  GPO7           PORTE.4
#define  GPO8           PORTE.5
#define  nLO_L4         PORTE.6
#define  nLG_L4         PORTE.7

#define  nGPI8           PINF.0
#define  nGPI7           PINF.1
#define  nGPI6           PINF.2
#define  nGPI5           PINF.3
#define  nGPI4           PINF.4
#define  nGPI3           PINF.5
#define  nGPI2           PINF.6
#define  nGPI1           PINF.7

#define  IO113          PORTG.0
#define  IO112          PORTG.1
#define  IO114          PING.2
#define  READ_SLOTADR   PORTG.3
#define  CAN_INT        PING.4

/********************************/
/* Specific defines             */
/********************************/
#define LOGIC_LEDS(a)            nACT_LED = a;
#define SWITCHDELAY              10
#define TRACK_WIBBLE             4

#define OSCILLATOR_FREQUENCY     16000000

unsigned int cntTimer0;
volatile unsigned int cntMilliSecond;
unsigned int PreviousMilliSecond;
unsigned int PreviousMilliSecondReservation;
unsigned int PreviousLEDBlinkMilliSecond;

unsigned char LEDState[8];
unsigned char LEDMode[8];
unsigned char LEDData[8];
//RJ45 LEDs

unsigned char OverloadState[8];
unsigned char SignalState;
unsigned char NewSignalState;

unsigned char GPIState[8];
unsigned char GPIActiveState[8];
unsigned char GPIOMode[8];
unsigned int GPOStartTime[8];
unsigned char GPOPulseTime[8];
unsigned char GPOState[8];
unsigned char GPOActiveState[8];

unsigned char SwitchData[2][8];
//Row 0: GPIx
//Row 1: OVLx

unsigned char RackSlotNr;

unsigned char FPGAData[12];
unsigned int FPGAFirmwareType;

unsigned char InputStereoSelect[8];
float InputLevel[8];
unsigned char InputPhase[8];

char SwitchCheck(unsigned char cntRow, unsigned char SwitchNr, char SwitchReturn);
void ReadSwitches();
void DoSwitch(unsigned char LogicSwitchNr, int Event);
void SetLEDs();
void SetGPOs();
char GetSlotNr();
void ReadFPGA();
void SetFPGA(unsigned char FunctionNr, unsigned int FunctionData);
void SetInputRoutingAndLevel(unsigned char ChannelNr);
void GetGPIOModes();

//Information required for CANTransportLayer.h
//#define CAN_ADDRESS_SERVER

//One of the following functions needs to be implemented, the other should be NULL
//void ProcessMambaNetMessage7BitsDataFromCAN(unsigned long int ToAddress, unsigned long int FromAddress, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength);
void (*ProcessMambaNetMessage7BitsDataFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength) = NULL;

void ProcessMambaNetMessageFromCAN_Imp(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength);
void (*ProcessMambaNetMessageFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength) = ProcessMambaNetMessageFromCAN_Imp;
//void (*ProcessMambaNetMessageFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength) = NULL;

#endif