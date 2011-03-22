#ifndef Axum_Rack_DDH
#define Axum_Rack_DDH

/********************************/
/* Define Ports                 */
/********************************/
#define ADAT2_IN_96_n48    PINA.7
#define ADAT2_IN_ERROR     PINA.6
#define ADAT2_OUT_96_n48   PORTA.5
#define ADAT2_OUT_nRESET   PORTA.4
#define ADAT1_IN_96_n48    PINA.3
#define ADAT1_IN_ERROR     PINA.2
#define ADAT1_OUT_96_n48   PORTA.1
#define ADAT1_OUT_nRESET   PORTA.0

#define  nSS            PORTB.0
#define  SCK_PSCK       PORTB.1
#define  PSCK           PINB.1
#define  MOSI           PORTB.2
#define  MISO           PINB.3
#define  SLOTADR0       PINB.4
#define  SLOTADR1       PINB.5
#define  SLOTADR2       PINB.6
#define  SLOTADR3       PINB.7

#define 	ADAT1_IN_LEDGRN   PORTC.0
#define 	ADAT1_OUT_LEDGRN  PORTC.1
#define 	ADAT2_IN_LEDGRN   PORTC.2
#define 	ADAT2_OUT_LEDGRN  PORTC.3
#define	ADAT1_IN_LEDRED   PORTC.4
#define	ADAT1_OUT_LEDRED  PORTC.5
#define	ADAT2_IN_LEDRED   PORTC.6
#define  ADAT2_OUT_LEDRED  PORTC.7

#define  RS_CAN         PORTD.4
#define  TXD_CAN        PORTD.5
#define  RXD_CAN        PIND.6
#define  IO115          PIND.7

#define  PDI            PORTE.0
#define  PDO            PORTE.1

#define  nACT_LED        PORTF.7

#define  IO113          PING.0
#define  IO112          PING.1
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
unsigned int cntMilliSecond;
unsigned int PreviousMilliSecond;
unsigned int PreviousMilliSecondReservation;
unsigned int PreviousLEDBlinkMilliSecond;

unsigned char LEDState[4];
unsigned char LEDMode[4];
unsigned char LEDData[4];
//bicolor leds LEDs

//unsigned char SwitchData[2][8];
//Row 0: GPIx
//Row 1: OVLx

unsigned int NewInputSignalState;
unsigned int InputSignalState;
unsigned int NewOutputSignalState;
unsigned int OutputSignalState;

unsigned char FPGAData[12];
unsigned int FPGAFirmwareType;

unsigned char RackSlotNr;


unsigned char InputStereoSelect[16];
float InputLevel[16];
unsigned char InputPhase[16];

unsigned char OutputStereoSelect[16];
float OutputLevel[16];
unsigned char OutputDim[16];
float OutputDimLevel[16];
unsigned char OutputMute[16];
unsigned char OutputPhase[16];

unsigned char OutputTalkback[16];
float OutputTalkbackLevel[16];
unsigned char OutputTalkbackStereoSelect[16];
unsigned char OutputTalkbackPhase[16];

void SetLEDs();
char GetSlotNr();
void ReadFPGA();
void SetFPGA(unsigned char FunctionNr, unsigned int FunctionData);
void SetRoutingAndLevel(unsigned char ChannelNr);

//Information required for CANTransportLayer.h
//#define CAN_ADDRESS_SERVER

//One of the following functions needs to be implemented, the other should be NULL
//void ProcessMambaNetMessage7BitsDataFromCAN(unsigned long int ToAddress, unsigned long int FromAddress, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength);
void (*ProcessMambaNetMessage7BitsDataFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength) = NULL;

void ProcessMambaNetMessageFromCAN_Imp(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength);
void (*ProcessMambaNetMessageFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength) = ProcessMambaNetMessageFromCAN_Imp;
//void (*ProcessMambaNetMessageFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength) = NULL;

#endif