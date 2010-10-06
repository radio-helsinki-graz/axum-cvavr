#ifndef Axum_Rack_ETXBaseH
#define Axum_Rack_ETXBaseH

/********************************/
/* Define Ports                 */
/********************************/
#define  SERIRQ         PORTA.5
#define  CAN-INT        PORTA.6
#define  E_RCLK         PORTA.7

#define  SCK_SPI        PINB.1
#define  nRI2           PORTB.2
#define  nCTS2          PORTB.3
#define  nDSR2          PORTB.4
#define  nDCD2          PORTB.5
#define  nDTR2          PINB.6
#define  nRTS2          PINB.7

#define     READ_SLOTADR   PORTC.0
#define     SLOTADR0        PINC.1
#define     SLOTADR1        PINC.2
#define     SLOTADR2        PINC.3
#define     SLOTADR3        PINC.4

#define  LEDGRN         PORTC.6
#define  nFCLK_SINK_LED PORTC.7

#define  TXD2           PIND.2
#define  RXD2           PORTD.3
#define  RS_CAN         PORTD.4
#define  TXD_CAN        PORTD.5
#define  RXD_CAN        PIND.6
#define  RCLK           PIND.7

#define  PDI            PINE.0
#define  PDO            PORTE.1
#define  nRING          PORTE.2
#define  nRSMRST        PORTE.3
#define  FCLK           PINE.6

#define  HARDWARE_REV1  PINF.0
#define  HARDWARE_REV2  PINF.1
#define  HARDWARE_REV3  PINF.2
#define  HARDWARE_REV4  PINF.3
#define  PLUS_5V        PINF.4
#define  PLUS_5VP       PINF.5
#define  PLUS_15VP      PINF.6
#define  MIN_15VP       PINF.7

/********************************/
/* Specific defines             */
/********************************/
#define OSCILLATOR_FREQUENCY     16000000

/********************************/
/* global declarations          */
/********************************/
unsigned int cntTimer0;
volatile unsigned int cntMilliSecond;
unsigned int PreviousMilliSecond;
unsigned int PreviousLEDBlinkMilliSecond;


//Information required for CANTransportLayer.h
#define CAN_ADDRESS_SERVER

unsigned char CANServices                 = 0x01;        //Gateway/CAN Address server


//One of the following functions needs to be implemented, the other should be NULL
//void ProcessMambaNetMessage7BitsDataFromCAN_Imp(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength);
//void (*ProcessMambaNetMessage7BitsDataFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress,unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength) = ProcessMambaNetMessage7BitsDataFromCAN_Imp;
//void (*ProcessMambaNetMessage7BitsDataFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength) == NULL;

//void ProcessMambaNetMessageFromCAN(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength);
//void (*ProcessMambaNetMessageFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength) = NULL;

#endif