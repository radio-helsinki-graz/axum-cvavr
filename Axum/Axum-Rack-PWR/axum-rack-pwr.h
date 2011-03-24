#ifndef Axum_Rack_PWRH
#define Axum_Rack_PWRH

/********************************/
/* Define Ports                 */
/********************************/
#define  HARDWARE_REV1  PORTA.0
#define  HARDWARE_REV2  PORTA.1
#define  HARDWARE_REV3  PORTA.2
#define  HARDWARE_REV4  PORTA.3
#define  LEDRED         PORTA.6
#define	LEDGRN			PORTA.7

#define  SCK            PORTB.1
#define  PSCK           PINB.1
#define  SLOTADR0       PINB.4
#define  SLOTADR1       PINB.5
#define  SLOTADR2       PINB.6
#define  SLOTADR3       PINB.7

#define  I2C_SCL        PIND.0
#define  I2C_SDA        PIND.1
#define  ALERT          PIND.2
#define  RS_CAN         PORTD.4
#define  TXD_CAN        PORTD.5
#define  RXD_CAN        PIND.6

#define  PDI            PINE.0
#define  PDO            PINE.1
#define  POWER_FAN      PORTE.2
#define  PWM_FAN        PORTE.3
#define  ENB_FAN        PORTE.4
#define  FAN_TACH0      PINE.7

#define  PRE_5V         PINF.0
#define  PRE_15V        PINF.2
#define  PRE_n15V       PINF.4

#define  READ_SLOTADR   PORTG.3
#define  CAN_INT        PING.4


/********************************/
/* Specific defines             */
/********************************/
#define LOGIC_LEDS(a)    LEDRED = 0;  \
                         LEDGRN = a;
#define SWITCHDELAY              10
#define TRACK_WIBBLE             4

#define OSCILLATOR_FREQUENCY     16000000

//unsigned char Debug[512];

unsigned int cntTimer0;
unsigned int cntMilliSecond;
unsigned int PreviousMilliSecond;
unsigned int PreviousMilliSecondReservation;
unsigned int PreviousLEDBlinkMilliSecond;
unsigned int PreviousPre_5VCheckMilliSecond;
unsigned int PreviousPre_15VCheckMilliSecond;
unsigned int PreviousPre_n15VCheckMilliSecond;
unsigned int PreviousFanSpeedCheckMilliSecond;
unsigned int PreviousTemperatureCheckMilliSecond;
//unsigned int PreviousFanMilliSecond;
//unsigned int FanSpeedDifference;
//unsigned int PreviousFanSpeedDifference;
long int FanTimerCount;
long int FanTachoCount;

unsigned char RackSlotNr;

float PreviousPre_5V;
float PreviousPre_15V;
float PreviousPre_n15V;
float PreviousTemperature;
int PreviousFanSpeed;
float Pre_5V;
float Pre_15V;
float Pre_n15V;
float CurrentTemperature;
int FanSpeed;
int SpeedSet;

char GetSlotNr();
//void SetFPGA(unsigned char FunctionNr, unsigned int FunctionData);
unsigned int GetMillisecondsToWaitFromObjectFrequency(unsigned char ObjectFrequency);
void InitTMP75();
float ReadTMP75();

//Information required for CANTransportLayer.h
//#define CAN_ADDRESS_SERVER

//One of the following functions needs to be implemented, the other should be NULL
//void ProcessMambaNetMessage7BitsDataFromCAN(unsigned long int ToAddress, unsigned long int FromAddress, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength);
void (*ProcessMambaNetMessage7BitsDataFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength) = NULL;

void ProcessMambaNetMessageFromCAN_Imp(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength);
void (*ProcessMambaNetMessageFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength) = ProcessMambaNetMessageFromCAN_Imp;
//void (*ProcessMambaNetMessageFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength) = NULL;

#endif