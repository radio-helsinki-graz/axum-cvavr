#ifndef Axum_UI_ETXBaseH
#define Axum_UI_ETXBaseH

/********************************/
/* Define Ports                 */
/********************************/
#define  HARDWARE_REV1  PORTA.4
#define  HARDWARE_REV2  PORTA.5
#define  HARDWARE_REV3  PORTA.6
#define  HARDWARE_REV4  PORTA.7

#define  SCK_SPI        PINB.1
#define  SERIRQ         PORTB.7

#define     nDTR2          PINC.0
#define     nRTS2           PINC.1
#define     nRI2            PORTC.2
#define     nCTS2           PORTC.3
#define nDSR2           PORTC.4
#define nDCD2               PORTC.5

#define  TXD2           PIND.2
#define  RXD2           PORTD.3

#define  TXD_CAN        PORTD.5
#define  RXD_CAN        PIND.6
#define  RS_CAN         PORTD.7

#define  PDI            PINE.0
#define  PDO            PORTE.1

#define  PWR_IN         PINF.0
#define  VS             PINF.1

/********************************/
/* Specific defines             */
/********************************/
#define OSCILLATOR_FREQUENCY     16000000

/********************************/
/* global declarations          */
/********************************/
volatile unsigned int cntMilliSecond;

//Information required for CANTransportLayer.h
#define CAN_ADDRESS_SERVER

unsigned char CANServices                 = 0x01;        //Gateway/CAN Address server?

#endif