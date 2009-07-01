#ifndef Axum_Rack_DSPH
#define Axum_Rack_DSPH

/********************************/
/* Define Ports                 */
/********************************/
#define  GPIO4          PINA.0
#define  GPIO5          PINA.1
#define  nACT_LED       PORTA.7

#define  nSS            PORTB.0
#define  SCK_PSCK       PORTB.1
#define  MOSI           PORTB.2
#define  MISO           PINB.3
#define  SLOTADR0       PINB.4
#define  SLOTADR1       PINB.5
#define  SLOTADR2       PINB.6
#define  SLOTADR3       PINB.7

#define  RS_CAN         PORTD.4
#define  TXD_CAN        PORTD.5
#define  RXD_CAN        PIND.6
#define  nHSENUM        PIND.7

#define  PDI            PINE.0
#define  PDO            PINE.1
#define  IO51           PINE.7

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

unsigned char RackSlotNr;

char GetSlotNr();
void SetFPGA(unsigned char FunctionNr, unsigned int FunctionData);

//Information required for CANTransportLayer.h
//#define CAN_ADDRESS_SERVER

//One of the following functions needs to be implemented, the other should be NULL
//void ProcessMambaNetMessage7BitsDataFromCAN(unsigned long int ToAddress, unsigned long int FromAddress, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength);
void (*ProcessMambaNetMessage7BitsDataFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength) = NULL;

void ProcessMambaNetMessageFromCAN_Imp(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength);
void (*ProcessMambaNetMessageFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength) = ProcessMambaNetMessageFromCAN_Imp;
//void (*ProcessMambaNetMessageFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength) = NULL;

#endif