#ifndef Axum_UI_PCRH
#define Axum_UI_PCRH

/********************************/
/* Define Ports                 */
/********************************/
#define  nSW1           PINA.0
#define  nSW2           PINA.1
#define  nSW3           PINA.2
#define  nSW4           PINA.3
#define  nSW5           PINA.4
#define  nSW6           PINA.5
#define  nSW7           PINA.6
#define  nSW8           PINA.7

#define  nROW2          PORTB.0
#define  SCK_SPI        PINB.1
#define  nROW3          PORTB.2
#define  nROW4          PORTB.3
#define  nROW5          PORTB.4
#define  nROW6          PORTB.5
#define  nROW7          PORTB.6
#define  nROW8          PORTB.7

#define  nSW_3B         PINC.0
#define  nSW_3A         PINC.1
#define  nSW_2C         PINC.2
#define  nSW_2B         PINC.3
#define  nSW_2A         PINC.4
#define  nSW_1B         PINC.5
#define  nSW_1A         PINC.6

#define  TXD_CAN        PORTD.5
#define  RXD_CAN        PIND.6
#define  RS_CAN         PORTD.7

#define  PDI            PINE.0
#define  PDO            PORTE.1
#define  SCLK           PORTE.2
#define  SIN            PORTE.3
#define  XLAT           PORTE.4
#define  BLANK          PORTE.5
#define  nROW1          PORTE.7 

#define  nDL86          PORTF.0
#define  nDL85          PORTF.1
#define  nDL84          PORTF.2
#define  nDL83          PORTF.3
#define  HW_REV1        PINF.4
#define  HW_REV2        PINF.5
#define  HW_REV3        PINF.6
#define  HW_REV4        PINF.7

/********************************/
/* Specific defines             */
/********************************/
#define SWITCHDELAY              10

#define OSCILLATOR_FREQUENCY     16000000

const unsigned char SwitchNr2LogicSwitchNr[64] =
{
    0,  1,  2,
    //Encoder switch
    8,  
    3,  4,  5,  6,
   
   11, 12,  13, 14,
   15, 16,  17, 18,
   19, 20,  21, 22,
   23, 24,  25, 26,
   27, 28,  29, 30,
   31, 32,  33, 34,
   35, 36,  37, 38,
   39, 40,  41, 42,

   43, 44,  45, 46,
   47, 48,  49, 50,

   51, 52, 53, 54,
   //Encoder switch 
   56,

   57, 58, 59, 60,
   61, 62, 63, 64,
   65, 66, 67
};

const unsigned char LogicLEDNr2LEDNr[68] =
{
};

unsigned int cntTimer0;
unsigned int cntMilliSecond;
unsigned int PreviousMilliSecond;
unsigned int PreviousMilliSecondReservation;

#define NR_OF_LOGIC_LEDS 68
unsigned char LogicLEDData[NR_OF_LOGIC_LEDS]; //Index calculated from object number
unsigned char SwitchColorOn[NR_OF_LOGIC_LEDS];
unsigned char SwitchColorOff[NR_OF_LOGIC_LEDS];

#define NR_OF_LEDS 96 
unsigned char TLC5921DAPData[NR_OF_LEDS/8];

unsigned char SwitchData[8][8];

#define NR_OF_LOGIC_SWITCHES 68
unsigned char SwitchState[NR_OF_LOGIC_SWITCHES]; //Index calculated from object number

unsigned char EncoderABStatus;
unsigned char PreviousEncoderABStatus;

unsigned int EncoderPosition[3];
unsigned int PreviousEncoderPosition[3];
unsigned int EncoderPreviousUpTime[3];
unsigned int EncoderPreviousDownTime[3];

void SetTLC5921DAP();
void selectRow(unsigned char Row);
char SwitchCheck(unsigned char cntRow, unsigned char SwitchNr, char SwitchReturn);
void ReadSwitches();
void ChangeEncoder(unsigned char EncoderNr, unsigned char UpDown);
void ReadEncoders();
void DoSwitch(unsigned char LogicSwitchNr, int Event);
void SetLEDs();

//Information required for CANTransportLayer.h
//#define CAN_ADDRESS_SERVER

//One of the following functions needs to be implemented, the other should be NULL
//void ProcessMambaNetMessage7BitsDataFromCAN(unsigned long int ToAddress, unsigned long int FromAddress, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength);
void (*ProcessMambaNetMessage7BitsDataFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength) = NULL;

void ProcessMambaNetMessageFromCAN_Imp(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength);
void (*ProcessMambaNetMessageFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength) = ProcessMambaNetMessageFromCAN_Imp;
//void (*ProcessMambaNetMessageFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength) = NULL;

#endif
