#ifndef Axum_Rack_CNxH
#define Axum_Rack_CNxH

/********************************/
/* Define Ports                 */
/********************************/
//CobraNet HMI
/*
#define PINA.0
#define PINA.1
#define PINA.2
#define PINA.3
#define PINA.4
#define PINA.5
#define PINA.6
#define PINA.7
*/
#define  nSS            PORTB.0
#define  SCK_PSCK       PORTB.1
#define  MOSI           PORTB.2
#define  MISO           PINB.3
#define  SLOTADR0       PINB.4
#define  SLOTADR1       PINB.5
#define  SLOTADR2       PINB.6
#define  SLOTADR3       PINB.7

#define HWREV0 PINC.0
#define HWREV1 PINC.1
#define HWREV2 PINC.2
#define HWREV3 PINC.3

#define  WD             PIND.1
#define  nACT_LED       PORTD.2
#define  DE_RCLK        PORTD.3
#define  RS_CAN         PORTD.4
#define  TXD_CAN        PORTD.5
#define  RXD_CAN        PIND.6
#define  IO115          PIND.7

#define  PDI            PORTE.0
#define  PDO            PORTE.1
#define  nHEN           PORTE.2

#define  HADDR0          PORTF.0
#define  HADDR1          PORTF.1
#define  HADDR2          PORTF.2
#define  HADDR3          PORTF.3
#define  HRnW            PORTF.4
#define  nHREQ           PINF.5
#define  nHDS            PINF.6
#define  nHACK           PORTF.7

#define  IO113          PING.0
#define  IO112          PING.1
#define  IO114          PING.2
#define  READ_SLOTADR   PORTG.3
#define  CAN_INT        PING.4

/********************************/
/* Specific defines             */
/********************************/
#define SWITCHDELAY              10
#define TRACK_WIBBLE             4

#define OSCILLATOR_FREQUENCY     16000000

unsigned int cntTimer0;
unsigned int cntMilliSecond;
unsigned int PreviousMilliSecond;
unsigned int PreviousMilliSecondReservation;
unsigned int PreviousLEDBlinkMilliSecond;

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

char SwitchCheck(unsigned char cntRow, unsigned char SwitchNr, char SwitchReturn);
void ReadSwitches();
void DoSwitch(unsigned char LogicSwitchNr, int Event);
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