/******************************************/
/* Project : Axum-UI-CRMP                 */
/* Date    : 3-10-2007                    */
/* Author  : Anton Prins                  */
/* Company : DR Electronica Weesp b.v.    */
/*                                        */
/* Chip type           : AT90CAN32        */
/* Clock frequency     : 16,000000 MHz    */
/* Memory model        : Small            */
/******************************************/

// -- Implementation information -- //

//processor must run 16 Mhz
//you require to have defined/include:
//- the CAN processor via an included header
//
//- RS_CAN (port to enable the physical driver
//
//- implementation of the ProcessMambaNetMessage functions must be done before including CANTransportLayer.h:
//  One function may be defined, the other must be NULL
//  extern void ProcessMambaNetMessage7BitsDataFromCAN(unsigned long int ToAddress, unsigned long int FromAddress, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength);
//  extern void ProcessMambaNetMessageFromCAN(unsigned long int ToAddress, unsigned long int FromAddress, unsigned int MessageType, unsigned char *Data, unsigned char DataLength);
//
//- add the include-path to your project
//
//- implementation of the global variabls:
//  unsigned int ManufacturerID;
//  unsigned int ProductID;
//  eeprom unsigned int UniqueIDPerProduct;
//  extern unsigned char CANServices;

#ifndef CANTransportLayerH
#define CANTransportLayerH

#define PROTOCOL_MAJOR_VERSION   1
#define PROTOCOL_MINOR_VERSION   0

#define PROTOCOL_OVERHEAD        16 //16 bytes of defined overhead in the protcol

#define MAX_MAMBANET_CAN_BUFFER_SIZE   128
#define MAX_MAMBANET_DATA_SIZE              ((MAX_MAMBANET_CAN_BUFFER_SIZE-PROTOCOL_OVERHEAD)*7)/8    //112*7bit -> 98*8bit

#define MAMBANET_ADDRESS_RESERVATION_MESSAGETYPE   0
   //MAMBANET_ADDRESS_RESERVATION_
   #define MAMBANET_ADDRESS_RESERVATION_TYPE_RESERVATION    0
   #define MAMBANET_ADDRESS_RESERVATION_TYPE_PING           1
   #define MAMBANET_ADDRESS_RESERVATION_TYPE_RESPONSE       2

#define MAMBANET_OBJECT_MESSAGETYPE                1
   //Object Info
   #define MAMBANET_OBJECT_ACTION_GET_INFORMATION           0
   #define MAMBANET_OBJECT_ACTION_INFORMATION_RESPONSE      1
   #define MAMBANET_OBJECT_ACTION_GET_ENGINE_ADDRESS        2
   #define MAMBANET_OBJECT_ACTION_ENGINE_ADDRESS_RESPONSE   3
   #define MAMBANET_OBJECT_ACTION_SET_ENGINE_ADDRESS        4
   #define MAMBANET_OBJECT_ACTION_GET_OBJECT_FREQUENCY      5
   #define MAMBANET_OBJECT_ACTION_OBJECT_FREQUENCY_RESPONSE 6
   #define MAMBANET_OBJECT_ACTION_SET_OBJECT_FREQUENCY      7

   //Sensor
   #define MAMBANET_OBJECT_ACTION_GET_SENSOR_DATA              32
   #define MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE         33
   #define MAMBANET_OBJECT_ACTION_SENSOR_DATA_CHANGED          34

   //Actuator
   #define MAMBANET_OBJECT_ACTION_GET_ACTUATOR_DATA        64
   #define MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE   65
   #define MAMBANET_OBJECT_ACTION_SET_ACTUATOR_DATA        66
#define MAMBANET_DEBUG_MESSAGETYPE                 16383

#define NO_DATA_DATATYPE                        0
#define UNSIGNED_INTEGER_DATATYPE               1
#define SIGNED_INTEGER_DATATYPE                 2
#define STATE_DATATYPE                          3
#define OCTET_STRING_DATATYPE                   4
#define FLOAT_DATATYPE                          5
#define BIT_STRING_DATATYPE                     6
#define OBJECT_INFORMATION_DATATYPE             128
#define ERROR_DATATYPE                          255

//extern unsigned int ManufacturerID;
//extern unsigned int ProductID;
//extern eeprom unsigned int UniqueIDPerProduct;
//extern unsigned char CANServices;

unsigned char AddressValidated;
unsigned char BusError;

extern void CanBussError();

#define BROADCAST_CAN_ADDRESS                   0x10000000  //0x1000zzz0   z = from address
#define BROADCAST_ADDRESS_RESERVATION_ADDRESS   0x0FFF0000  //0x1FFFzzz0   z = from address
#define BROADCAST_PARENT_CONTROL_ADDRESS        0x0FFF0001  //0x1FFFzzz0   z = from address

unsigned long int LocalCANAddress;
unsigned long int ReceivedLocalCANAddress;
unsigned long int ReceivedGatewayCANAddress;
unsigned long int ReceiveSequenceCANAddress;
unsigned long int GlobalReceiveSequenceCANAddress;
unsigned long int TransmitSequenceCANAddress;

unsigned int ToCANAddress;
unsigned int SequenceNumber;

unsigned char CANControlMessage[8];

#define CAN_ADDRESS_TRANSMIT_BUFFER_LENGTH      16
unsigned char CANAddressTransmit[CAN_ADDRESS_TRANSMIT_BUFFER_LENGTH];
unsigned char cntCANAddressTransmitTop;

typedef eeprom struct
{
   unsigned long int CANAddress;
   unsigned int ManufacturerID;
   unsigned int ProductID;
   unsigned int UniqueIDPerProduct;
   unsigned long int MambaNetAddress;
} ADDRESS_RESERVATION_DATA_STRUCT;

typedef eeprom struct
{
   unsigned long int UpdateFrequency:3;
   unsigned long int EngineMambaNetAddress:29;
} OBJECT_WRITABLE_INFORMATION_STRUCT;

//defines for eeprom usage
#ifndef CAN_ADDRESS_SERVER
   #ifdef _CHIP_AT90CAN32_
      #define MAX_NR_OF_OBJECTS 245     //CAN 32
      #define NR_OF_UART_BUFFERS 32
   #endif
   #ifdef _CHIP_AT90CAN64_
      #define MAX_NR_OF_OBJECTS 501     //CAN 64
      #define NR_OF_UART_BUFFERS  32//176
   #endif
   #ifdef _CHIP_AT90CAN128_
      #define MAX_NR_OF_OBJECTS 1013    //CAN 128
      #define NR_OF_UART_BUFFERS  176
   #endif
#else
   #ifdef _CHIP_AT90CAN32_
      #define MAX_NR_OF_OBJECTS 77      //CAN 32
      #define NR_OF_UART_BUFFERS  32
   #endif
   #ifdef _CHIP_AT90CAN64_
      #define MAX_NR_OF_OBJECTS 333     //CAN 64
      #define NR_OF_UART_BUFFERS  96//64//176
   #endif
   #ifdef _CHIP_AT90CAN128_
      #define MAX_NR_OF_OBJECTS 845     //CAN 128
      #define NR_OF_UART_BUFFERS  176
   #endif
#endif

#ifdef CAN_ADDRESS_SERVER

#define CAN_ADDRESS_BUFFER_SIZE  48   //Depends on EEPROM Size

eeprom ADDRESS_RESERVATION_DATA_STRUCT AddressReservationData[CAN_ADDRESS_BUFFER_SIZE] =
{  //CANAddress,  ManID, ProdID, UniID, MambeNetAddress
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000},
   { 0x00000000, 0x0000, 0x0000, 0x0000, 0x00000000}
};
#endif


typedef flash struct
{
   unsigned char  Description[64];
//   unsigned char  Name[32]; // Stored in EEPROM
   unsigned int   ManufacturerID;
   unsigned int   ProductID;
//   unsigned int   UniqueMediaAccessID;
   unsigned char  HardwareMajorRevision;
   unsigned char  HardwareMinorRevision;
   unsigned char  FirmwareMajorRevision;
   unsigned char  FirmwareMinorRevision;
   unsigned char  ProtocolMajorRevision;
   unsigned char  ProtocolMinorRevision;
   unsigned int   NumberOfObjects;
} DEFAULT_NODE_OBJECT_STRUCT;

typedef flash struct
{
   unsigned char DataType;
   unsigned char DataSize;
   unsigned long int DataMinimal;   // is max 32 bits in AVR but could be 64 bits in the protocol
   unsigned long int DataMaximal;   // is max 32 bits in AVR but could be 64 bits in the protocol
} SENSOR_DATA_STRUCT;

typedef flash struct
{
   unsigned char DataType;
   unsigned char DataSize;
   unsigned long int DataMinimal;   // is max 32 bits in AVR but could be 64 bits in the protocol
   unsigned long int DataMaximal;   // is max 32 bits in AVR but could be 64 bits in the protocol
   unsigned long int DefaultData;   // is max 32 bits in AVR but could be 64 bits in the protocol
} ACTUATOR_DATA_STRUCT;

typedef flash struct
{
   unsigned char Description[32];
   unsigned char Services;

   SENSOR_DATA_STRUCT Sensor;
   ACTUATOR_DATA_STRUCT Actuator;
} OBJECT_VARIABLE_INFORMATION_STRUCT;

//Maybe must be a circular buffer?.
unsigned char TransmitCANMessageBuffer[MAX_MAMBANET_CAN_BUFFER_SIZE];
unsigned char TransmitCANMessageBufferLength;
unsigned char cntTransmitCANMessageBuffer;

//Warning cannot be easily changed; 255+ is automatically counting to '0' becayse I use an unsigned char if array-pointer.
#define CAN_RECEIVE_BUFFER_SIZE 256
#define GLOBAL_CAN_RECEIVE_BUFFER_SIZE 256

unsigned int cntCANBusOff = 0;
unsigned int cntCANFrameBufferReceiveInterrrupt = 0;
unsigned int cntCANStuffErrorGeneral = 0;
unsigned int cntCANCRCErrorGeneral = 0;
unsigned int cntCANFormErrorGeneral = 0;
unsigned int cntCANAcknowledgementErrorGeneral = 0;
unsigned int cntCANTimerOverrun = 0;
unsigned int cntCANMob0StatusInterruptRXOK = 0;
unsigned int cntCANMob1StatusInterruptRXOK = 0;
unsigned int cntCANMob2StatusInterruptTXOK = 0;
unsigned int cntCANInterrupt = 0;

unsigned int cntCANBitErrorMob1 = 0;
unsigned int cntCANStuffErrorMob1 = 0;
unsigned int cntCANCRCErrorMob1 = 0;
unsigned int cntCANFormErrorMob1 = 0;
unsigned int cntCANAckErrorMob1 = 0;


unsigned int cntReceiveCANControl = 0;

unsigned int cntMambaNetFormatErrorFromCAN;
unsigned int cntMambaNetOverrunFromCAN;

unsigned int cntCANMessageTransmitted = 0;

unsigned char timerReservationInfo = 1;

unsigned char UARTTransmitBufferTop = 0;
unsigned char UARTTransmitBufferBottom = 0;
unsigned char UARTTransmitBuffer[NR_OF_UART_BUFFERS][13];

void SetLocalCANAddress(unsigned long int NewLocalAddress);
void SendCANParentControlMessage(unsigned char *Buffer);
void SendCANReservationResponse(unsigned int ManufacturerID, unsigned int ProductID, unsigned int UniqueIDPerProduct, unsigned long int NewCANAddress);
void ProcessCANControlMessage(unsigned char CANControlMessageType);

// CAN Timer Overrun interrupt service routine
interrupt [CTIM_OVF] void can_timer_isr(void)
{
// Place your code here
   cntCANTimerOverrun++;
}

//unsigned char CANMessageBufferStatus;
//unsigned char CANMessageBufferNumber;
//unsigned char GlobalCANMessageBufferStatus;
//unsigned char GlobalCANMessageBufferNumber;

unsigned char MambaNetEndOfMessageFound;
unsigned char GlobalMambaNetEndOfMessageFound;


// CAN interrupt service routine
interrupt [CAN_IT] void can_isr(void)
{
   char cntByte;
   unsigned char SequenceNumber;
   unsigned int FromCANAddress;
   unsigned char OldCANPAGE;
   unsigned char CANControlMessageType;

//   PORTB.7 = 1;
//   PORTF.4 = 1;

   OldCANPAGE = CANPAGE;

if ((CANSIT1 & 0x40) == 0x40 ) /* MOb14 interrupt (SIT14=1) */
{
CANPAGE = (0x0E << 4); /* select MOb14 */
CANSTMOB = 0x00; /* reset MOb14 status */
CANCDMOB = 0x88; /* reception enable */
}                                                         

   /******** MOb0 ********/
   /* local receive A    */
   /**********************/
   if( CANSIT2 & 0x01)
   {   // CANSIT2 MOb2 Status interrupt
      CANPAGE  = 0x00; //(0X00 << 4); set page MOb

      if(CANSTMOB & 0x80)
      {  // DLCW: Data Length Code Warning
      }

      if(CANSTMOB & 0x40)
      {  // TXOK
         //CANCDMOB = 0;           // disable MOb

         CANSTMOB &= 0xbf; // reset TXOK bit
      }

      if(CANSTMOB & 0x20)
      {  // RXOK
         CANSTMOB &= 0xdf;       // reset RXOK bit
         
         BusError = 0;

   //PDO=1;

         SequenceNumber = (CANIDT4>>3)&0xF;
         FromCANAddress  = (CANIDT4>>7)&0x001;
         FromCANAddress |= (((unsigned int)CANIDT3)<<1)&0x1FE;
         FromCANAddress |= (((unsigned int)CANIDT2)<<9)&0xE00;
                 
         UARTTransmitBuffer[UARTTransmitBufferTop][0] = 0xE0;
         UARTTransmitBuffer[UARTTransmitBufferTop][1] = (FromCANAddress>>7)&0x1F;
         UARTTransmitBuffer[UARTTransmitBufferTop][2] = FromCANAddress&0x7F;
         UARTTransmitBuffer[UARTTransmitBufferTop][3] = SequenceNumber&0x0F;
         for (cntByte=0; cntByte<8; cntByte++)
         {
            UARTTransmitBuffer[UARTTransmitBufferTop][4+cntByte] = CANMSG;
         }
         UARTTransmitBuffer[UARTTransmitBufferTop][12] = 0xE1;

         if ((UARTTransmitBufferTop+1) == UARTTransmitBufferBottom)
         {
            cntMambaNetOverrunFromCAN++;
         }
         else
         {
            UARTTransmitBufferTop++;
            if (UARTTransmitBufferTop>(NR_OF_UART_BUFFERS-1))
            {
               UARTTransmitBufferTop = 0;
            }
         }
         
/*         if (MessageComplete)
         {
            ReceiveSequenceCANAddress = (LocalCANAddress<<16)&0xFFFF0000;
         }
         else
         {
            ReceiveSequenceCANAddress++;
         }*/
         /*
         CANIDT4  = (ReceiveSequenceCANAddress<<3)&0xF8;
         CANIDT3  = (ReceiveSequenceCANAddress>>5)&0xFF;
         CANIDT2  = (ReceiveSequenceCANAddress>>13)&0xFF;
         CANIDT1  = (ReceiveSequenceCANAddress>>21)&0xFF;

         CANCDMOB |= 0x10; // IDE = 1 CAN rev.2.0B (Indentifier 29bit)
         CANCDMOB |= 0x08; // DLC = 1 Data Length Code
         */         
         CANCDMOB |= 0x80; // CONMOB1:0: Configuration of Message Object = Reception
         
         cntCANMob0StatusInterruptRXOK++;
   //PDO=0;

      }

      if(CANSTMOB & 0x10)
      {  // BERR: Bit Error (The bit value monitored is different from the bit value sent
         CANSTMOB &= 0xef; // reset BERR bit
      }

      if(CANSTMOB & 0x08)
      {  // SERR: Stuff Error
         CANSTMOB &= 0xf7; // reset SERR bit
      }

      if(CANSTMOB & 0x04)
      {  // CERR: CRC Error
         CANSTMOB &= 0xfb; // reset CERR bit
      }

      if(CANSTMOB & 0x02)
      {  // FERR: Form Error
         CANSTMOB &= 0xfd; // reset FERR bit
      }

      if(CANSTMOB & 0x01)
      {  // AERR: Acknowledgment Error
         CANSTMOB &= 0xfe; // reset AERR bit
      }
   }

   /******** MOb1 ********/
   /* Global receive     */
   /**********************/
   if( CANSIT2 & 0x02)
   {   // CANSIT2 MOb1 Status interrupt
      CANPAGE  = 0x10; //(0X01 << 4); set page MOb

      if(CANSTMOB & 0x80)
      {  // DLCW: Data Length Code Warning
      }

      if(CANSTMOB & 0x40)
      {  // TXOK
         //CANCDMOB = 0;           // disable MOb

         CANSTMOB &= 0xbf; // reset TXOK bit
      }

      if(CANSTMOB & 0x20)
      {  // RXOK
         CANSTMOB &= 0xdf;       // reset RXOK bit

         BusError = 0;

         SequenceNumber = (CANIDT4>>3)&0xF;
         FromCANAddress  = (CANIDT4>>7)&0x001;
         FromCANAddress |= (((unsigned int)CANIDT3)<<1)&0x1FE;
         FromCANAddress |= (((unsigned int)CANIDT2)<<9)&0xE00;

         UARTTransmitBuffer[UARTTransmitBufferTop][0] = 0xE0;
         UARTTransmitBuffer[UARTTransmitBufferTop][1] = (FromCANAddress>>7)&0x1F;
         UARTTransmitBuffer[UARTTransmitBufferTop][2] = FromCANAddress&0x7F;
         UARTTransmitBuffer[UARTTransmitBufferTop][3] = SequenceNumber&0x0F;
         for (cntByte=0; cntByte<8; cntByte++)
         {
            UARTTransmitBuffer[UARTTransmitBufferTop][4+cntByte] = CANMSG;
         }
         UARTTransmitBuffer[UARTTransmitBufferTop][12] = 0xE1;

         if ((UARTTransmitBufferTop+1) == UARTTransmitBufferBottom)
         {
            cntMambaNetOverrunFromCAN++;
         }
         else
         {
            UARTTransmitBufferTop++;
            if (UARTTransmitBufferTop>(NR_OF_UART_BUFFERS-1))
            {
               UARTTransmitBufferTop = 0;
            }
         }

         CANCDMOB |= 0x80; // CONMOB1:0: Configuration of Massage Object = Reception
      }

      if(CANSTMOB & 0x10)
      {  // BERR: Bit Error (The bit value monitored is different from the bit value sent
         CANSTMOB &= 0xef; // reset BERR bit
      }

      if(CANSTMOB & 0x08)
      {  // SERR: Stuff Error
         CANSTMOB &= 0xf7; // reset SERR bit
      }

      if(CANSTMOB & 0x04)
      {  // CERR: CRC Error
         CANSTMOB &= 0xfb; // reset CERR bit
      }

      if(CANSTMOB & 0x02)
      {  // FERR: Form Error
         CANSTMOB &= 0xfd; // reset FERR bit
      }

      if(CANSTMOB & 0x01)
      {  // AERR: Acknowledgment Error
         CANSTMOB &= 0xfe; // reset AERR bit
      }
   }

   /******** MOb2 ********/
   /* Transmit           */
   /**********************/
   if( CANSIT2 & 0x04)
   {   // CANSIT2 MOb2 Status interrupt
      CANPAGE  = 0x20; //(0x20 << 4); set page MOb

      if(CANSTMOB & 0x80)
      {  // DLCW: Data Length Code Warning
      }

      if(CANSTMOB & 0x40)
      {  // TXOK
         CANSTMOB &= 0xbf;       // reset TXOK bit

         BusError = 0;

         if (cntTransmitCANMessageBuffer<TransmitCANMessageBufferLength)
         {
            TransmitSequenceCANAddress++;
            CANIDT4  = (TransmitSequenceCANAddress<<3)&0xF8;
            CANIDT3  = (TransmitSequenceCANAddress>>5)&0xFF;
            CANIDT2  = (TransmitSequenceCANAddress>>13)&0xFF;
            CANIDT1  = (TransmitSequenceCANAddress>>21)&0xFF;

            CANCDMOB |= 0x10; //IDE = 1
            CANCDMOB |= 0x08; //DLC = 1

            CANMSG = TransmitCANMessageBuffer[cntTransmitCANMessageBuffer++];
            CANMSG = TransmitCANMessageBuffer[cntTransmitCANMessageBuffer++];
            CANMSG = TransmitCANMessageBuffer[cntTransmitCANMessageBuffer++];
            CANMSG = TransmitCANMessageBuffer[cntTransmitCANMessageBuffer++];
            CANMSG = TransmitCANMessageBuffer[cntTransmitCANMessageBuffer++];
            CANMSG = TransmitCANMessageBuffer[cntTransmitCANMessageBuffer++];
            CANMSG = TransmitCANMessageBuffer[cntTransmitCANMessageBuffer++];
            CANMSG = TransmitCANMessageBuffer[cntTransmitCANMessageBuffer++];

            CANCDMOB |= 0x40; //Enable Transmission
         }
         else
         {
            cntCANMessageTransmitted++;
         }
         cntCANMob2StatusInterruptTXOK++;
      }

      if(CANSTMOB & 0x20)
      {  // RXOK
         //CANCDMOB = 0;           // disable MOb
         CANSTMOB &= 0xdf;       // reset RXOK bit
      }

      if(CANSTMOB & 0x10)
      {  // BERR: Bit Error (The bit value monitored is different from the bit value sent
         CANSTMOB &= 0xef; // reset BERR bit       
         cntCANBitErrorMob1++;
         //BusError = 1;
      }

      if(CANSTMOB & 0x08)
      {  // SERR: Stuff Error
         CANSTMOB &= 0xf7; // reset SERR bit
         cntCANStuffErrorMob1++;
         //BusError = 1;
      }

      if(CANSTMOB & 0x04)
      {  // CERR: CRC Error
         CANSTMOB &= 0xfb; // reset CERR bit
         cntCANCRCErrorMob1++;
         BusError = 1;
      }

      if(CANSTMOB & 0x02)
      {  // FERR: Form Error
         CANSTMOB &= 0xfd; // reset FERR bit
         cntCANFormErrorMob1++;
         BusError = 1;
      }

      if(CANSTMOB & 0x01)
      {  // AERR: Acknowledgment Error
         CANSTMOB &= 0xfe; // reset AERR bit
         cntCANAckErrorMob1++;
         BusError = 1;

         //Retry
         //CANCDMOB |= 0x40; //Enable Transmission
      }
   }

   /******** MOb3 ****************************/
   /* Global CAN address reservation receive     */
   /******************************************/
   if( CANSIT2 & 0x08)
   {   // CANSIT2 MOb3 Status interrupt
      CANPAGE  = 0x30; //(0X03 << 4); set page MOb

      if(CANSTMOB & 0x80)
      {  // DLCW: Data Length Code Warning
      }

      if(CANSTMOB & 0x40)
      {  // TXOK
         CANSTMOB &= 0xbf; // reset TXOK bit
      }

      if(CANSTMOB & 0x20)
      {  // RXOK
         CANSTMOB &= 0xdf;       // reset RXOK bit

         cntReceiveCANControl++;

         CANControlMessageType = (CANIDT4>>3)&0x0F;

         for (cntByte=0; cntByte<8; cntByte++)
         {
            CANControlMessage[cntByte] = CANMSG;
         }

         CANCDMOB |= 0x10; // IDE = 1 CAN rev.2.0B (Indentifier 29bit)
         CANCDMOB |= 0x08; // DLC = 1 Data Length Code
         CANCDMOB |= 0x80; // CONMOB1:0: Configuration of Massage Object = Reception
         
         //LEDGRN = !LEDGRN; 

                 
         ProcessCANControlMessage(CANControlMessageType);
      }

      if(CANSTMOB & 0x10)
      {  // BERR: Bit Error (The bit value monitored is different from the bit value sent
         CANSTMOB &= 0xef; // reset BERR bit
      }

      if(CANSTMOB & 0x08)
      {  // SERR: Stuff Error
         CANSTMOB &= 0xf7; // reset SERR bit
      }

      if(CANSTMOB & 0x04)
      {  // CERR: CRC Error
         CANSTMOB &= 0xfb; // reset CERR bit
      }

      if(CANSTMOB & 0x02)
      {  // FERR: Form Error
         CANSTMOB &= 0xfd; // reset FERR bit
      }

      if(CANSTMOB & 0x01)
      {  // AERR: Acknowledgment Error
         CANSTMOB &= 0xfe; // reset AERR bit
      }
   }

   /******** MOb4 *************************/
   /* Global address reservation transmit */
   /***************************************/
   if( CANSIT2 & 0x10)
   {   // CANSIT2 MOb2 Status interrupt
      CANPAGE  = 0x40; //(0x04 << 4); set page MOb

      if(CANSTMOB & 0x80)
      {  // DLCW: Data Length Code Warning
      }

      if(CANSTMOB & 0x40)
      {  // TXOK
         CANSTMOB &= 0xbf;       // reset TXOK bit

         BusError = 0;

         //PDO = !PDO;

         if (cntCANAddressTransmitTop<CAN_ADDRESS_TRANSMIT_BUFFER_LENGTH)
         {
            CANCDMOB |= 0x10; //IDE = 1
            CANCDMOB |= 0x08; //DLC = 1

            CANMSG = CANAddressTransmit[cntCANAddressTransmitTop++];
            CANMSG = CANAddressTransmit[cntCANAddressTransmitTop++];
            CANMSG = CANAddressTransmit[cntCANAddressTransmitTop++];
            CANMSG = CANAddressTransmit[cntCANAddressTransmitTop++];
            CANMSG = CANAddressTransmit[cntCANAddressTransmitTop++];
            CANMSG = CANAddressTransmit[cntCANAddressTransmitTop++];
            CANMSG = CANAddressTransmit[cntCANAddressTransmitTop++];
            CANMSG = CANAddressTransmit[cntCANAddressTransmitTop++];

            CANCDMOB |= 0x40; //Enable Transmission
         }
         //cntCANMob0StatusInterruptTXOK++;
      }

      if(CANSTMOB & 0x20)
      {  // RXOK
         CANSTMOB &= 0xdf;       // reset RXOK bit
      }

      if(CANSTMOB & 0x10)
      {  // BERR: Bit Error (The bit value monitored is different from the bit value sent
         CANSTMOB &= 0xef; // reset BERR bit
         //BusError = 1;
      }

      if(CANSTMOB & 0x08)
      {  // SERR: Stuff Error
         CANSTMOB &= 0xf7; // reset SERR bit
         //BusError = 1;
      }

      if(CANSTMOB & 0x04)
      {  // CERR: CRC Error
         CANSTMOB &= 0xfb; // reset CERR bit
         BusError = 1;
      }

      if(CANSTMOB & 0x02)
      {  // FERR: Form Error
         CANSTMOB &= 0xfd; // reset FERR bit
         BusError = 1;
      }

      if(CANSTMOB & 0x01)
      {  // AERR: Acknowledgment Error
         CANSTMOB &= 0xfe; // reset AERR bit
         BusError = 1;

         //Retry
         //CANCDMOB |= 0x40; //Enable Transmission
      }
   }

   if( CANGIT & 0x80)
   {  // CANIT: General Interrupt flag
      if( CANGIT & 0x40)
      {   // BOFFIT: Bus Off Interrupt
         cntCANBusOff++;
         CANGIT |= 0x40;

         //BusError = 1;
      }
      if( CANGIT & 0x10)
      {   // BXOK frame buffer receive interrupt
         cntCANFrameBufferReceiveInterrrupt++;
         CANGIT |= 0x10;
      }
      if( CANGIT & 0x08)
      {   // SERG: Stuff Error General
         cntCANStuffErrorGeneral++;
         CANGIT |= 0x08;
         //BusError = 1;

      }
      if( CANGIT & 0x04)
      {   // CERG: CRC Error General
         cntCANCRCErrorGeneral++;
         CANGIT |= 0x04;
         BusError = 1;

      }
      if( CANGIT & 0x02)
      {   // FERG: Form Error General
         cntCANFormErrorGeneral++;
         CANGIT |= 0x02;

         BusError = 1;
     }
      if( CANGIT & 0x01)
      {   // AERG: Acknowledgment Error General
         cntCANAcknowledgementErrorGeneral++;
         CANGIT |= 0x01;
         
         BusError = 1;
      }
   }
   
   if (BusError)
   {
      CanBussError();
          //AddressValidated = 0;
       //timerReservationInfo = 1;
   }
   
   

   cntCANInterrupt++;

   CANPAGE = OldCANPAGE;
//   PDO = 0;
//   PORTF.4 = 0;
//   PORTB.7 = 0;
}

void InitializeCAN()
{
   char cnt;

   // CAN Controller initialization
   // CAN: On
   CANGCON=0x02;
   // CAN Interrupts:
   // Timer Overrun: Off
   // General Errors: Off
   // Frame Buffer: Off
   // MOb Errors: Off
   // Transmit: On
   // Receive: On
   // Bus Off: Off
   // All, except Timer Overrun: On
   CANGIE=0xFE;

   // MOb0: Enabled, MOb1: Enabled, MOb2: Enabled, MOb3: Disabled, MOb4: Disabled, MOb5: Disabled, MOb6: Disabled, MOb7: Disabled
   CANEN2=0x1F;
   // MOb8: Disabled, MOb9: Disabled, MOb10: Disabled, MOb11: Disabled, MOb12: Disabled, MOb13: Disabled, MOb14: Disabled
   CANEN1=0x00;
   // MOb0..7 Interrupts: MOb0: On, MOb1: On, MOb2: On, MOb3: Off, MOb4: Off, MOb5: Off, MOb6: Off, MOb7: Off
   CANIE2=0x1F;
   // MOb8..14 Interrupts: MOb8: Off, MOb9: Off, MOb10: Off, MOb11: Off, MOb12: Off, MOb13: Off, MOb14: Off
   CANIE1=0x00;
   // Highest Interrupt Priority: MOb0
   CANHPMOB=0x00;
   // CAN System Clock: 8000,0 kHz  
//   CANBT1=0x02;//0x00 or 0x02;
   CANBT1=0x00;// 87,5% Sample point
   // Propagation Time Segement: 0,375 us
   // Re-Sync Jump Width: 0,125 us
//   CANBT2=0x04;//0x0C or 0x04;
   CANBT2=0x0E;// 87,5% Sample point
   // Sample Point(s): 3
   // Phase Segment 1: 0,250 us
   // Phase Segment 2: 0,250 us
//   CANBT3=0x13;//0x36 or 0x13;
   CANBT3=0x18;// 87,5% Sample point
   //CANBT3=0x36;//0x01 = SMP, bug -> 3 samplemode off
   // CAN Timer Clock Period: 1,000 us
   CANTCON=0x00;

   //Clear all MObs
   for (cnt = 0; cnt < 15; cnt++)
   {
      CANGIE &= 0x7F;

      CANPAGE  = (cnt << 4);
      CANSTMOB = 0;
      CANCDMOB = 0;
      CANIDT4  = 0;
      CANIDT3  = 0;
      CANIDT2  = 0;
      CANIDT1  = 0;
      CANIDM4  = 0;
      CANIDM3  = 0;
      CANIDM2  = 0;
      CANIDM1  = 0;
      CANMSG = 0;
      CANMSG = 0;
      CANMSG = 0;
      CANMSG = 0;
      CANMSG = 0;
      CANMSG = 0;
      CANMSG = 0;
      CANMSG = 0;

      CANGIE |= 0x80;
   }

   cntCANAddressTransmitTop         = CAN_ADDRESS_TRANSMIT_BUFFER_LENGTH;
   LocalCANAddress                  = 0x00000000;
   ReceivedLocalCANAddress          = 0x00000000;
   ReceivedGatewayCANAddress        = 0x00000000;

   ReceiveSequenceCANAddress        = 0x00000000;
   GlobalReceiveSequenceCANAddress  = 0x00000000;
   TransmitSequenceCANAddress       = 0x00000000;

   //Initialize MOB1 for global receive
   CANGIE &= 0x7F;

   CANPAGE  = 0x10; //(1 << 4);  MO1
   CANSTMOB = 0;
   CANCDMOB = 0;

   GlobalReceiveSequenceCANAddress = BROADCAST_CAN_ADDRESS&0xFFFF0000;
   CANIDT4  = (GlobalReceiveSequenceCANAddress<<3)&0xF8;
   CANIDT3  = (GlobalReceiveSequenceCANAddress>>5)&0xFF;
   CANIDT2  = (GlobalReceiveSequenceCANAddress>>13)&0xFF;
   CANIDT1  = (GlobalReceiveSequenceCANAddress>>21)&0xFF;
   CANIDM4  = 0x07;
   CANIDM3  = 0x00;
   CANIDM2  = 0xF8;
   CANIDM1  = 0xFF;
   CANCDMOB |= 0x10; //IDE = 1
   CANCDMOB |= 0x08; //DLC = 1
   CANCDMOB |= 0x80; //Enable Reception
   CANGIT = 0x7F;

   CANGIE |= 0x80;

   //MOb2 is initialized in the transmit function.

   //Initialize MOB3 for address reservation receive
   CANGIE &= 0x7F;

   CANPAGE  = 0x30; //(1 << 4);  MO1
   CANSTMOB = 0;
   CANCDMOB = 0;


   CANIDT4  = (BROADCAST_ADDRESS_RESERVATION_ADDRESS<<3)&0xF8;
   CANIDT3  = (BROADCAST_ADDRESS_RESERVATION_ADDRESS>>5)&0xFF;
   CANIDT2  = (BROADCAST_ADDRESS_RESERVATION_ADDRESS>>13)&0xFF;
   CANIDT1  = (BROADCAST_ADDRESS_RESERVATION_ADDRESS>>21)&0xFF;
   //CANIDM4  = 0xFF;
   CANIDM4  = 0x87;  //receive all control messages.
   CANIDM3  = 0xFF;
   CANIDM2  = 0xFF;
   CANIDM1  = 0xFF;
   CANCDMOB |= 0x10; //IDE = 1
   CANCDMOB |= 0x08; //DLC = 1
   CANCDMOB |= 0x80; //Enable Reception
   CANGIT = 0x7F;

   //SPY Mob14
   CANPAGE = (0x0E << 4); /* select MOb14 */
   CANSTMOB = 0x00; /* reset MOb14 status */

   CANIDM4  = 0x00;  //receive all control messages.
   CANIDM3  = 0x00;
   CANIDM2  = 0x00;
   CANIDM1  = 0x00;

   CANCDMOB = 0x88; /* reception enable */
                                                         
   CANGIE |= 0x80;

   cntCANBusOff = 0;
   cntCANFrameBufferReceiveInterrrupt = 0;
   cntCANStuffErrorGeneral = 0;
   cntCANCRCErrorGeneral = 0;
   cntCANFormErrorGeneral = 0;
   cntCANAcknowledgementErrorGeneral = 0;
   cntCANTimerOverrun = 0;
   cntCANMob0StatusInterruptRXOK = 0;
   cntCANMob1StatusInterruptRXOK = 0;
   cntCANMob2StatusInterruptTXOK = 0;
   cntCANInterrupt = 0;

   TransmitCANMessageBufferLength = 0;
   cntTransmitCANMessageBuffer = 0;

   cntMambaNetFormatErrorFromCAN = 0;
   cntMambaNetOverrunFromCAN = 0;

   MambaNetEndOfMessageFound = 0;
   GlobalMambaNetEndOfMessageFound = 0;

   AddressValidated = 0;
   timerReservationInfo = 1;
   BusError = 0;

   UARTTransmitBufferTop = 0;
   UARTTransmitBufferBottom = 0;

   RS_CAN = 0;
}


void SendMambaNetMessageToCAN_DedicatedAddress(unsigned long int CANAddress, unsigned char *Data, unsigned char DataLength)
{
   unsigned char cntByte;
   unsigned char MessageLength;
   unsigned char cntBuffer;

   if ((AddressValidated) && (!BusError))
   {
      if ((DataLength <= MAX_MAMBANET_DATA_SIZE) && (LocalCANAddress != 0x00000000))
      {
         while (cntTransmitCANMessageBuffer < TransmitCANMessageBufferLength);

         if (cntTransmitCANMessageBuffer >= TransmitCANMessageBufferLength)
         {            
            for (cntBuffer=0; cntBuffer<DataLength; cntBuffer++)
            {
               TransmitCANMessageBuffer[cntBuffer] = Data[cntBuffer];
            }

            //CAN message size is 'modulo 8'
            MessageLength = DataLength;
            if (MessageLength&0x07)
            {
               MessageLength += 0x08;
            }
            MessageLength &= 0xF8;
            for (cntByte=cntBuffer; cntByte<MAX_MAMBANET_CAN_BUFFER_SIZE; cntByte++)
            {
               TransmitCANMessageBuffer[cntByte] = 0x00;
            }

            //Trigger CAN transmit
            TransmitCANMessageBufferLength = 0;
            cntTransmitCANMessageBuffer = 0;
            TransmitCANMessageBufferLength = MessageLength;

            CANPAGE  = 0x20;  //(Mob2 = 0x02 << 4) + auto increment
            CANSTMOB = 0x00;  //Mob status register
            CANCDMOB = 0x00;  //Mob control and DLC register

            //CANAddress or use broadcast address..
            if (CANAddress != 0x00000000)
            {
               TransmitSequenceCANAddress = (CANAddress<<16)&0xFFFF0000;
            }
            else
            {  //No gateway specified, do broadcast
               TransmitSequenceCANAddress = BROADCAST_CAN_ADDRESS&0xFFFF0000;
            }
            TransmitSequenceCANAddress |= (LocalCANAddress<<4)&0x0000FFF0;


            //TransmitSequenceCANAddress = ToAddress;
            CANIDT4  = (TransmitSequenceCANAddress<<3)&0xF8;
            CANIDT3  = (TransmitSequenceCANAddress>>5)&0xFF;
            CANIDT2  = (TransmitSequenceCANAddress>>13)&0xFF;
            CANIDT1  = (TransmitSequenceCANAddress>>21)&0xFF;

            CANIDM4  = 0xFF;
            CANIDM3  = 0xFF;
            CANIDM2  = 0xFF;
            CANIDM1  = 0xFF;

            CANCDMOB |= 0x10; //IDE = 1
            CANCDMOB |= 0x08; //DLC = 1

            CANMSG = TransmitCANMessageBuffer[cntTransmitCANMessageBuffer++];
            CANMSG = TransmitCANMessageBuffer[cntTransmitCANMessageBuffer++];
            CANMSG = TransmitCANMessageBuffer[cntTransmitCANMessageBuffer++];
            CANMSG = TransmitCANMessageBuffer[cntTransmitCANMessageBuffer++];
            CANMSG = TransmitCANMessageBuffer[cntTransmitCANMessageBuffer++];
            CANMSG = TransmitCANMessageBuffer[cntTransmitCANMessageBuffer++];
            CANMSG = TransmitCANMessageBuffer[cntTransmitCANMessageBuffer++];
            CANMSG = TransmitCANMessageBuffer[cntTransmitCANMessageBuffer++];

            CANCDMOB |= 0x40; //Enable Transmission
         }
      }
   }
}

void SetLocalCANAddress(unsigned long int NewLocalAddress)
{
   //Initialize MOB0 for local receive
   CANGIE &= 0x7F;

   CANPAGE  = 0x00; //(0 << 4);  MOb0
   CANSTMOB = 0;
   CANCDMOB = 0;

   LocalCANAddress = NewLocalAddress;

   ReceiveSequenceCANAddress = (LocalCANAddress<<16)&0xFFFF0000;
   CANIDT4  = (ReceiveSequenceCANAddress<<3)&0xF8;
   CANIDT3  = (ReceiveSequenceCANAddress>>5)&0xFF;
   CANIDT2  = (ReceiveSequenceCANAddress>>13)&0xFF;
   CANIDT1  = (ReceiveSequenceCANAddress>>21)&0xFF;
   CANIDM4  = 0x07;
   CANIDM3  = 0x00;
   CANIDM2  = 0xF8;
   CANIDM1  = 0xFF;
   CANCDMOB |= 0x10; //IDE = 1
   CANCDMOB |= 0x08; //DLC = 1
   CANCDMOB |= 0x80; //Enable Reception
   CANGIT = 0x7F;

//Mob5
   /*CANPAGE  = 0x50; //(5 << 4);  MOb5
   CANSTMOB = 0;
   CANCDMOB = 0;

   ReceiveSequenceCANAddress2 = (LocalCANAddress<<16)&0xFFFF0000;
   CANIDT4  = (ReceiveSequenceCANAddress2<<3)&0xF8;
   CANIDT3  = (ReceiveSequenceCANAddress2>>5)&0xFF;
   CANIDT2  = (ReceiveSequenceCANAddress2>>13)&0xFF;
   CANIDT1  = (ReceiveSequenceCANAddress2>>21)&0xFF;
   CANIDM4  = 0x07;
   CANIDM3  = 0x00;
   CANIDM2  = 0xF8;
   CANIDM1  = 0xFF;
   CANCDMOB |= 0x10; //IDE = 1
   CANCDMOB |= 0x08; //DLC = 1
   CANCDMOB |= 0x80; //Enable Reception
   CANGIT = 0x7F;*/

   CANGIE |= 0x80;
}

void SendCANParentControlMessage(unsigned char *Buffer)
{
   //Trigger CAN transmit
   if (!BusError)
   {
      CANPAGE  = 0x40;  //(Mob2 = 0x02 << 4) + auto increment
      CANSTMOB = 0x00;     //Mob status register
      CANCDMOB = 0x00;     //Mob control and DLC register

      CANIDT4  = (BROADCAST_PARENT_CONTROL_ADDRESS<<3)&0xF8;
      CANIDT3  = (BROADCAST_PARENT_CONTROL_ADDRESS>>5)&0xFF;
      CANIDT2  = (BROADCAST_PARENT_CONTROL_ADDRESS>>13)&0xFF;
      CANIDT1  = (BROADCAST_PARENT_CONTROL_ADDRESS>>21)&0xFF;
      
      CANIDM4  = 0xFF;
      CANIDM3  = 0xFF;
      CANIDM2  = 0xFF;
      CANIDM1  = 0xFF;
   
      CANCDMOB |= 0x10; //IDE = 1
      CANCDMOB |= 0x08; //DLC = 1

      CANMSG = Buffer[0];
      CANMSG = Buffer[1];
      CANMSG = Buffer[2];
      CANMSG = Buffer[3];
      CANMSG = Buffer[4];
      CANMSG = Buffer[5];
      CANMSG = Buffer[6];
      CANMSG = Buffer[7];

      CANCDMOB |= 0x40; //Enable Transmission
   }
}


void SendCANReservationResponse(unsigned int ReceivedManufacturerID, unsigned int ReceivedProductID, unsigned int ReceivedUniqueIDPerProduct, unsigned long int NewCANAddress)
{
   if (!BusError)
   {
      unsigned long int NewGatewayAddress = LocalCANAddress;

      if (cntCANAddressTransmitTop >= CAN_ADDRESS_TRANSMIT_BUFFER_LENGTH)
      {
          //Trigger CAN transmit
          CANPAGE  = 0x40;  //(Mob4 = 0x04 << 4) + auto increment
          CANSTMOB = 0x00;     //Mob status register
          CANCDMOB = 0x00;     //Mob control and DLC register

          CANIDT4  = (BROADCAST_ADDRESS_RESERVATION_ADDRESS<<3)&0xF8;
          CANIDT3  = (BROADCAST_ADDRESS_RESERVATION_ADDRESS>>5)&0xFF;
          CANIDT2  = (BROADCAST_ADDRESS_RESERVATION_ADDRESS>>13)&0xFF;
          CANIDT1  = (BROADCAST_ADDRESS_RESERVATION_ADDRESS>>21)&0xFF;

          CANIDM4  = 0xFF;
          CANIDM3  = 0xFF;
          CANIDM2  = 0xFF;
          CANIDM1  = 0xFF;

          CANCDMOB |= 0x10; //IDE = 1
          CANCDMOB |= 0x08; //DLC = 1

          CANAddressTransmit[0] = (ReceivedManufacturerID>>8)&0xFF;
          CANAddressTransmit[1] = ReceivedManufacturerID&0xFF;
          CANAddressTransmit[2] = (ReceivedProductID>>8)&0xFF;
          CANAddressTransmit[3] = ReceivedProductID&0xFF;
          CANAddressTransmit[4] = (ReceivedUniqueIDPerProduct>>8)&0xFF;
          CANAddressTransmit[5] = ReceivedUniqueIDPerProduct&0xFF;
          CANAddressTransmit[6] = 0x10 | (NewCANAddress>>8)&0x0F;
          CANAddressTransmit[7] =         NewCANAddress    &0xFF;

          CANAddressTransmit[8] = (ReceivedManufacturerID>>8)&0xFF;
          CANAddressTransmit[9] = ReceivedManufacturerID&0xFF;
          CANAddressTransmit[10] = (ReceivedProductID>>8)&0xFF;
          CANAddressTransmit[11] = ReceivedProductID&0xFF;
          CANAddressTransmit[12] = (ReceivedUniqueIDPerProduct>>8)&0xFF;
          CANAddressTransmit[13] = ReceivedUniqueIDPerProduct&0xFF;
          CANAddressTransmit[14] = 0x20 | (NewGatewayAddress>>8)&0x0F;
          CANAddressTransmit[15] =         NewGatewayAddress    &0xFF;

          cntCANAddressTransmitTop = 0;
          CANMSG = CANAddressTransmit[cntCANAddressTransmitTop++];
          CANMSG = CANAddressTransmit[cntCANAddressTransmitTop++];
          CANMSG = CANAddressTransmit[cntCANAddressTransmitTop++];
          CANMSG = CANAddressTransmit[cntCANAddressTransmitTop++];
          CANMSG = CANAddressTransmit[cntCANAddressTransmitTop++];
          CANMSG = CANAddressTransmit[cntCANAddressTransmitTop++];
          CANMSG = CANAddressTransmit[cntCANAddressTransmitTop++];
          CANMSG = CANAddressTransmit[cntCANAddressTransmitTop++];

          CANCDMOB |= 0x40; //Enable Transmission
      }
   }
}

void ProcessCANControlMessage(unsigned char CANControlMessageType)
{
   unsigned int ReceivedManufacturerID;
   unsigned int ReceivedProductID;
   unsigned int ReceivedUniqueIDPerProduct;
   unsigned char ReservationType;
//   unsigned char CANControlData[2];

   switch (CANControlMessageType)
   {
      case 0:
      {  //address reservation
         ReceivedManufacturerID = ((unsigned int)CANControlMessage[0]<<8) | CANControlMessage[1];
         ReceivedProductID = ((unsigned int)CANControlMessage[2]<<8) | CANControlMessage[3];
         ReceivedUniqueIDPerProduct = ((unsigned int)CANControlMessage[4]<<8) | CANControlMessage[5];
         ReservationType = (CANControlMessage[6]>>4)&0x0F;
//         CANControlData[0] = CANControlMessage[6]&0xF;
//         CANControlData[1] = CANControlMessage[7];

/*       if (  (ReceivedManufacturerID == ManufacturerID) &&
               (ReceivedProductID == ProductID) &&
               (ReceivedUniqueIDPerProduct == UniqueIDPerProduct))
         {  //Control Message for my Unique ID.

            switch (ReservationType)
            {
               case 0:
               {  //Reservation request for my unique ID?
               }
               break;
               case 1:
               {  //Reservation response LSB
                  ReceivedLocalCANAddress = 0x00000000;
                  ReceivedLocalCANAddress |= ((unsigned long int)CANControlData[0]<<8)&0x00000F00;
                  ReceivedLocalCANAddress |= ((unsigned long int)CANControlData[1]   )&0x000000FF;

                  SetLocalCANAddress(ReceivedLocalCANAddress);
               }
               break;
               case 2:
               {  //Reservation response MSB
                  ReceivedGatewayCANAddress |= ((unsigned long int)CANControlData[0]<< 8)&0x00000F00;
                  ReceivedGatewayCANAddress |= ((unsigned long int)CANControlData[1]    )&0x000000FF;

                  GatewayCANAddress = ReceivedGatewayCANAddress;
               }
               break;
            }
         }
         else*/
         {
#ifdef CAN_ADDRESS_SERVER
            if ((ReservationType == 0) && (CANServices & 0x01))
            {  //Address request, respond if you are a valid CAN address server.
               unsigned long AddressToAssign;
               unsigned char Found;
               char FreeSlot;
               unsigned long cnt;
               //Check for address
               AddressToAssign = 0x0000002;
               Found = 0;
               FreeSlot = -1;
               for (cnt=0; cnt<CAN_ADDRESS_BUFFER_SIZE; cnt++)
               {
                  if (!Found)
                  {
                     if (  (AddressReservationData[cnt].ManufacturerID == ReceivedManufacturerID) &&
                           (AddressReservationData[cnt].ProductID == ReceivedProductID) &&
                           (AddressReservationData[cnt].UniqueIDPerProduct == ReceivedUniqueIDPerProduct))
                     {
                        if (AddressReservationData[cnt].CANAddress != 0x00000000)
                        {
                           AddressToAssign = AddressReservationData[cnt].CANAddress;
                           Found = 1;
                        }
                     }
                     else if (AddressReservationData[cnt].CANAddress >= AddressToAssign)
                     {
                        AddressToAssign = AddressReservationData[cnt].CANAddress+1;
                     }
                     else if (AddressReservationData[cnt].ManufacturerID == 0)
                     {
                        if (FreeSlot == -1)
                        {
                           FreeSlot = cnt;
                        }
                     }
                  }
               }
               if ((!Found) && (FreeSlot != -1))
               {
                  AddressReservationData[FreeSlot].ManufacturerID = ReceivedManufacturerID;
                  AddressReservationData[FreeSlot].ProductID = ReceivedProductID;
                  AddressReservationData[FreeSlot].UniqueIDPerProduct = ReceivedUniqueIDPerProduct;
                  AddressReservationData[FreeSlot].CANAddress = AddressToAssign;
                  AddressReservationData[FreeSlot].MambaNetAddress = 0x00000000;
               }
               SendCANReservationResponse(ReceivedManufacturerID, ReceivedProductID, ReceivedUniqueIDPerProduct, AddressToAssign);
            }
#endif
         }
      }
      break;
      case 1:
      {
         unsigned char cntByte;
                 
         UARTTransmitBuffer[UARTTransmitBufferTop][0] = 0xE0;
         UARTTransmitBuffer[UARTTransmitBufferTop][1] = 0x40 | ((0xFFF>>7)&0x1F);
         UARTTransmitBuffer[UARTTransmitBufferTop][2] = 0xFFF&0x7F;
         UARTTransmitBuffer[UARTTransmitBufferTop][3] = 0x01&0x0F;
         for (cntByte=0; cntByte<8; cntByte++)
         {
            UARTTransmitBuffer[UARTTransmitBufferTop][4+cntByte] = CANControlMessage[cntByte];
         }
         UARTTransmitBuffer[UARTTransmitBufferTop][12] = 0xE1;

         if ((UARTTransmitBufferTop+1) == UARTTransmitBufferBottom)
         {
            cntMambaNetOverrunFromCAN++;
         }
         else
         {
            UARTTransmitBufferTop++;
            if (UARTTransmitBufferTop>(NR_OF_UART_BUFFERS-1))
            {
               UARTTransmitBufferTop = 0;
            }
         }
      }
      break;
   }
}




#endif


