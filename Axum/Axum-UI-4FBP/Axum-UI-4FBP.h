#ifndef Axum_UI_4FBPH
#define Axum_UI_4FBPH

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

#define  nROW1          PORTB.0
#define  SCK_SPI        PINB.1
#define  TOUCH1         PINB.2
#define  TOUCH2         PINB.3
#define  PWM_M3_B       PORTB.4
#define  PWM_M3_A       PORTB.5
#define  PWM_M4_A       PORTB.6
#define  PWM_M4_B       PORTB.7

#define 	D4LCD  		   PORTC.0
#define 	D5LCD  			PORTC.1
#define 	D6LCD  			PORTC.2
#define 	D7LCD  			PORTC.3
#define	RW_LCD			PORTC.4
#define	E_LCD				PORTC.5
#define	RS_LCD			PORTC.6
#define  BLANK          PORTC.7
#define LCD_D7_nBF      DDRC.3
#define LCD_BF          PINC.3

#define  nROW2          PORTD.0
#define  nROW3          PORTD.1
#define  nROW4          PORTD.2
#define  nROW5          PORTD.3
#define  nROW6          PORTD.4
#define  TXD_CAN        PORTD.5
#define  RXD_CAN        PIND.6
#define  RS_CAN         PORTD.7

#define  PDI            PINE.0
#define  PDO            PORTE.1
#define  PWM_M1_B       PORTE.2
#define  PWM_M1_A       PORTE.3
#define  PWM_M2_A       PORTE.4
#define  PWM_M2_B       PORTE.5
#define  ENB_MTRS       PORTE.6
#define  SYNC_TOUCH     PORTE.7

#define  WIPER_FADER1   PINF.0
#define  WIPER_FADER2   PINF.1
#define  WIPER_FADER3   PINF.2
#define  WIPER_FADER4   PINF.3
#define  JUMPER1        PINF.4
#define  JUMPER2        PINF.5
#define  JUMPER3        PINF.6
#define  JUMPER4        PINF.7
                              
#define  SIN            PORTG.0
#define  SCLK           PORTG.1
#define  XLAT           PORTG.2
#define  TOUCH3         PING.3
#define  TOUCH4         PING.4

/********************************/
/* Specific defines             */
/********************************/
#define OSCILLATOR_FREQUENCY     16000000

#define NR_OF_TLC5921DAP_ICS     10
#define SWITCHDELAY              2

#define FADER_WIBBLE             4
#define MOTOR_POSITION_DEADZONE  6
             
/********************************/
/* global declarations          */
/********************************/
unsigned char cntLEDDebug;

/*const unsigned char LogicSwitchNr2SwitchNr[36] =
{
   33, 18, 19, 16, 17,  9,  8, 1, 0,
   35, 22, 23, 20, 21, 11, 10, 3, 2,
   37, 26, 27, 24, 25, 13, 12, 5, 4,
   39, 30, 31, 28, 29, 15, 14, 7, 6
};*/

const unsigned char SwitchNr2LogicSwitchNr[40] =
{
    8,  7, 17, 16, 26, 25, 35, 34,
    6,  5, 15, 14, 24, 23, 33, 32,
    3,  4,  1,  2, 12, 13, 10, 11,
   21, 22, 19, 20, 30, 31, 28, 29,
    0,  0,  9,  9, 18, 18, 27, 27
};

const unsigned char LogicLEDNr2LEDNr[80] =
{
   33, 32, 35, 34, 37, 36, 39, 38, 
   48, 49, 50, 51, 52, 53, 54, 55,
   67, 66, 68, 69,
   46, 47, 44, 45, 42, 43, 40, 41,   
   56, 57, 58, 59, 60, 61, 62, 63,
   65, 64, 70, 71,
   17, 16, 19, 18, 21, 20, 23, 22,
    0,  1,  2,  3,  4,  5,  6,  7,
   79, 78, 72, 73,
   30, 31, 28, 29, 26, 27, 24, 25,
    8,  9, 10, 11, 12, 13, 14, 15,
   77, 76, 74, 75
};

unsigned int cntTimer0;
volatile unsigned int cntMilliSecond;
unsigned int PreviousMilliSecond;
unsigned int PreviousMilliSecondReservation;

#define NR_OF_LEDS 80
unsigned char LogicLEDData[NR_OF_LEDS/8];
unsigned char TLC5921DAPData[NR_OF_TLC5921DAP_ICS];

unsigned char SwitchData[5][8];
unsigned int SwitchPressedTime[5][8];

unsigned char EncoderABStatus;
unsigned char PreviousEncoderABStatus;

unsigned int EncoderPosition[4];
unsigned int PreviousEncoderPosition[4];
unsigned int EncoderPreviousUpTime[4];
unsigned int EncoderPreviousDownTime[4];

unsigned int PreviousADC_Data[4];
unsigned int FaderPosition[4];
unsigned int PreviousFaderPosition[4];
//unsigned int FaderData[4];

unsigned char CurrentTouch[4];
unsigned char PreviousTouch[4];

char MotorActive[4];
unsigned int MotorPosition[4];
unsigned int PreviousMotorPosition[4];
int MotorSpeed[4];
int StepSizeUp = 1;
int StepSizeDown = 4;
int MinPWMSpeed = 300;
int MaxPWMSpeed = 600;
int PreviousDifference[4];
char Direction[4];  

unsigned char SwitchColorOn[4][4];
unsigned char SwitchColorOff[4][4];
unsigned char DualColorSwitchState[4][4];

unsigned char LCDTextString[8][9];
unsigned char SwitchState[36];


void SetTLC5921DAP();
void selectRow(unsigned char Row);
char SwitchCheck(unsigned char cntRow, unsigned char SwitchNr, char SwitchReturn);
void ReadSwitches();
void ReadEncoders();
void ReadFaders();
void DoSwitch(unsigned char LogicSwitchNr, int Event);
void SetLEDs();
void ReadTouch();
void ControlMotors();

//Information required for CANTransportLayer.h
//#define CAN_ADDRESS_SERVER

//One of the following functions needs to be implemented, the other should be NULL
//void ProcessMambaNetMessage7BitsDataFromCAN(unsigned long int ToAddress, unsigned long int FromAddress, unsigned long MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength);
void (*ProcessMambaNetMessage7BitsDataFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength) = NULL;

void ProcessMambaNetMessageFromCAN_Imp(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength);
void (*ProcessMambaNetMessageFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength) = ProcessMambaNetMessageFromCAN_Imp;
//void (*ProcessMambaNetMessageFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned long MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength) = NULL;

#endif