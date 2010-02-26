#ifndef Axum_Rack_HybridH
#define Axum_Rack_HybridH

/********************************/
/* Define Ports                 */
/********************************/
#define nRING2_HYB1     PINA.7
#define nRING_HYB1      PINA.6
#define nOH_HYB1        PORTA.5
#define nLOOP_HYB1      PORTA.4
#define nRING2_HYB2     PINA.3
#define nRING_HYB2      PINA.2
#define nOH_HYB2        PORTA.1
#define nLOOP_HYB2      PORTA.0

#define nSS             PORTB.0
#define SCK_PSCK        PORTB.1
#define MOSI            PORTB.2
#define MISO            PINB.3
#define SLOTADR0        PINB.4
#define SLOTADR1        PINB.5
#define SLOTADR2        PINB.6
#define SLOTADR3        PINB.7

#define CLKCMX          PORTC.1
#define DINCMX          PORTC.2
#define DOUTCMX_3V3     PINC.3
#define nIRQCMX1_3v3    PINC.4
#define nIRQCMX2_3v3    PINC.5
#define nIRQCMX3_3v3    PINC.6
#define nIRQCMX4_3v3    PINC.7

#define SCL_5V          PORTD.0
#define SDA_5V          PORTD.1
#define nACT_LED        PORTD.2
#define RS_CAN          PORTD.4
#define TXD_CAN         PORTD.5
#define RXD_CAN         PIND.6
#define IO115           PIND.7

#define PDI             PORTE.0
#define PDO             PORTE.1
#define HWREV0          PINE.4
#define HWREV1          PINE.5
#define HWREV2          PINE.6
#define HWREV3          PINE.7

#define nRING2_HYB3     PINF.7
#define nRING_HYB3      PINF.6
#define nOH_HYB3        PORTF.5
#define nLOOP_HYB3      PORTF.4
#define nRING2_HYB4     PINF.3
#define nRING_HYB4      PINF.2
#define nOH_HYB4        PORTF.1
#define nLOOP_HYB4      PORTF.0

#define IO113_AOnCSCMX  PORTG.0
#define IO112_A1nCSCMX  PORTG.1
#define IO114_A2nCSCMX  PORTG.2
#define READ_SLOTADR    PORTG.3
#define CAN_INT         PING.4

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

unsigned char NewInputSignalState;
unsigned char InputSignalState;
unsigned char NewOutputSignalState;
unsigned char OutputSignalState;

unsigned char FPGAData[12];
unsigned int FPGAFirmwareType;

unsigned char RackSlotNr;

unsigned char InputStereoSelect[8];
float InputLevel[8];
unsigned char InputPhase[8];

unsigned char OutputStereoSelect[8];
float OutputLevel[8];
unsigned char OutputDim[8];
float OutputDimLevel[8];
unsigned char OutputMute[8];
unsigned char OutputPhase[8];

unsigned char OutputTalkback[4][16];
float OutputTalkbackLevel[8];
unsigned char OutputTalkbackStereoSelect[8];
unsigned char OutputTalkbackPhase[8];
//unsigned char TalkbackFPGAAddress[8] = { 0x38, 0x00, 0x08, 0x10, 0x18, 0x20, 0x28, 0x30 };

unsigned char PreviousOffHookState[4];
unsigned char OffHookTimerEnabled[4];
unsigned int OffHookTimer[4];
unsigned char OffHookState[4];
char LastDialedNumber[4][64];
char DialPtr[4];

unsigned char Ring[4];
unsigned char PreviousRing[4];
unsigned char RingActive[4];
unsigned int RingActiveTimer[4];

unsigned int DTMFTimerDelay[4];
unsigned int DTMFTimer[4];
unsigned int DTMFSpaceTimerDelay[4];
unsigned int DTMFSpaceTimer[4];

unsigned char OffHookLoopDelay = 10;
unsigned int DTMFLength = 50;
unsigned int DTMFSpace = 50;
unsigned int DTMFCommaPause = 2000;
unsigned int DTMFSpacePause = 100;

char GetSlotNr();
void ReadFPGA();
void SetFPGA(unsigned char FunctionNr, unsigned int FunctionData);
void SetRoutingAndLevel(unsigned char ChannelNr);

unsigned int ReadCMX865A(unsigned char ChipNr, unsigned char Register);
void SetCMX865A(unsigned char ChipNr, unsigned char Register, unsigned int Value);
void ResetCMX865A(unsigned char ChipNr);

void DTMFDigit(unsigned char ChipNr, char Digit);
void CheckOffHook(unsigned char cntChip);

//Information required for CANTransportLayer.h
//#define CAN_ADDRESS_SERVER

//One of the following functions needs to be implemented, the other should be NULL
//void ProcessMambaNetMessage7BitsDataFromCAN(unsigned long int ToAddress, unsigned long int FromAddress, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength);
void (*ProcessMambaNetMessage7BitsDataFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength) = NULL;

void ProcessMambaNetMessageFromCAN_Imp(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength);
void (*ProcessMambaNetMessageFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength) = ProcessMambaNetMessageFromCAN_Imp;
//void (*ProcessMambaNetMessageFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength) = NULL;

#endif
