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

#ifdef __GNUG__
  #include <avr/interrupt.h>
  #include <avr/pgmspace.h>
  #define FLASHMEM PROGMEM
  #define EEPROMMEM __attribute__((section(".eeprom")))
#endif

#define PROTOCOL_MAJOR_VERSION   1
#define PROTOCOL_MINOR_VERSION   0

#define TRANSPORTLAYER_MINOR     1

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

#ifdef __GNUG__
unsigned long int LocalMambaNetAddress EEPROMMEM = 0x00000000;
unsigned long int DefaultEngineMambaNetAddress EEPROMMEM = 0x00000000;
extern unsigned int UniqueIDPerProduct EEPROMMEM;

extern unsigned char NodeServices FLASHMEM;
extern unsigned int NumberOfStaticObjects FLASHMEM;
#else
eeprom unsigned long int LocalMambaNetAddress = 0x00000000;
eeprom unsigned long int DefaultEngineMambaNetAddress = 0x00000000;
extern eeprom unsigned int UniqueIDPerProduct;
extern flash unsigned char NodeServices;
extern flash unsigned int NumberOfStaticObjects;
#endif

extern unsigned int ManufacturerID;
extern unsigned int ProductID;
extern unsigned char CANServices;

unsigned char AddressValidated;
unsigned char BusError;

//Debug Anton
unsigned long int ObjectNrInformationCount;
unsigned long int LastObjectInformationRequested;


extern void (*ProcessMambaNetMessage7BitsDataFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength);
extern void (*ProcessMambaNetMessageFromCAN)(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength);
extern void CanBussError();

#define BROADCAST_CAN_ADDRESS                   0x10000000  //0x1000zzz0   z = from address
#define BROADCAST_ADDRESS_RESERVATION_ADDRESS   0x0FFF0000  //0x1FFFzzz0   z = from address
#define BROADCAST_PARENT_CONTROL_ADDRESS        0x0FFF0001  //0x1FFFzzz0   z = from address

unsigned long int LocalCANAddress;
unsigned long int GatewayCANAddress;
unsigned long int ReceivedLocalCANAddress;
unsigned long int ReceivedGatewayCANAddress;

unsigned char ReceiveSequenceNumber;
unsigned char GlobalReceiveSequenceNumber;
unsigned int ReceiveCANAddress;
unsigned int GlobalReceiveCANAddress;

//unsigned long int ReceiveSequenceCANAddress;
//unsigned long int GlobalReceiveSequenceCANAddress;

unsigned long int TransmitSequenceCANAddress;

unsigned char CANControlMessage[8];

#define CAN_ADDRESS_TRANSMIT_BUFFER_LENGTH      16
unsigned char CANAddressTransmit[CAN_ADDRESS_TRANSMIT_BUFFER_LENGTH];
unsigned char cntCANAddressTransmitTop;

#ifdef __GNUG__
typedef struct
#else
typedef eeprom struct
#endif
{
   unsigned long int CANAddress;
   unsigned int ManufacturerID;
   unsigned int ProductID;
   unsigned int UniqueIDPerProduct;
   unsigned long int MambaNetAddress;
} ADDRESS_RESERVATION_DATA_STRUCT;

#ifdef __GNUG__
typedef struct
#else
typedef eeprom struct
#endif
{
   unsigned long int UpdateFrequency:3;
   unsigned long int EngineMambaNetAddress:29;
} OBJECT_WRITABLE_INFORMATION_STRUCT;

#ifdef __GNUG__
  #ifdef __AVR_AT90CAN32__
    #define _CHIP_AT90CAN32_
  #endif
  #ifdef __AVR_AT90CAN64__
    #define _CHIP_AT90CAN64_
  #endif
  #ifdef __AVR_AT90CAN128__
    #define _CHIP_AT90CAN128_
  #endif
#endif

//defines for eeprom usage
#ifndef CAN_ADDRESS_SERVER
   #ifdef _CHIP_AT90CAN32_
      #define MAX_NR_OF_OBJECTS 245     //CAN 32
   #endif
   #ifdef _CHIP_AT90CAN64_
      #define MAX_NR_OF_OBJECTS 501     //CAN 64
   #endif
   #ifdef _CHIP_AT90CAN128_
      #define MAX_NR_OF_OBJECTS 1013    //CAN 128
   #endif
#else
   #ifdef _CHIP_AT90CAN32_
      #define MAX_NR_OF_OBJECTS 77      //CAN 32
   #endif
   #ifdef _CHIP_AT90CAN64_
      #define MAX_NR_OF_OBJECTS 333     //CAN 64
   #endif
   #ifdef _CHIP_AT90CAN128_
      #define MAX_NR_OF_OBJECTS 845     //CAN 128
   #endif
#endif

#ifdef CAN_ADDRESS_SERVER

#define CAN_ADDRESS_BUFFER_SIZE  48   //Depends on EEPROM Size

#ifdef __GNUG__
ADDRESS_RESERVATION_DATA_STRUCT AddressReservationData[CAN_ADDRESS_BUFFER_SIZE] EEPROMMEM =
#else
eeprom ADDRESS_RESERVATION_DATA_STRUCT AddressReservationData[CAN_ADDRESS_BUFFER_SIZE] =
#endif
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

#ifdef __GNUG__
OBJECT_WRITABLE_INFORMATION_STRUCT ObjectWritableInformation[MAX_NR_OF_OBJECTS] EEPROMMEM =
#else
eeprom OBJECT_WRITABLE_INFORMATION_STRUCT ObjectWritableInformation[MAX_NR_OF_OBJECTS] =
#endif
{
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}
#if (MAX_NR_OF_OBJECTS>77)
                                                                                      , {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000},
   {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}, {1, 0x00000000}
#endif
};

#ifdef __GNUG__
extern char NodeName[32] EEPROMMEM;
#else
extern eeprom char NodeName[32];
#endif
extern unsigned char Parent[6];
extern unsigned char HardwareMinorRevision;
extern unsigned char FPGAFirmwareMajorRevision;
extern unsigned char FPGAFirmwareMinorRevision;

#ifdef __GNUG__
typedef struct
#else
typedef flash struct
#endif
{
   unsigned char  Description[64];
//   unsigned char  Name[32]; // Stored in EEPROM
   unsigned int   ManufacturerID;
   unsigned int   ProductID;
//   unsigned int   UniqueMediaAccessID; // Stored in EEPROM
   unsigned char  HardwareMajorRevision;
   unsigned char  HardwareMinorRevision;
   unsigned char  FirmwareMajorRevision;
   unsigned char  FirmwareMinorRevision;
//   unsigned char  FPGAFirmwareMajorRevision;  // Stored in FPGA
//   unsigned char  FPGAFirmwareMinorRevision;  // Stored in FPGA
   unsigned char  ProtocolMajorRevision;
   unsigned char  ProtocolMinorRevision;
   unsigned int   NumberOfObjects;
} DEFAULT_NODE_OBJECT_STRUCT;

#ifdef __GNUG__
typedef struct
#else
typedef flash struct
#endif
{
   unsigned char DataType;
   unsigned char DataSize;
   unsigned long int DataMinimal;   // is max 32 bits in AVR but could be 64 bits in the protocol
   unsigned long int DataMaximal;   // is max 32 bits in AVR but could be 64 bits in the protocol
} SENSOR_DATA_STRUCT;

#ifdef __GNUG__
typedef struct
#else
typedef flash struct
#endif
{
   unsigned char DataType;
   unsigned char DataSize;
   unsigned long int DataMinimal;   // is max 32 bits in AVR but could be 64 bits in the protocol
   unsigned long int DataMaximal;   // is max 32 bits in AVR but could be 64 bits in the protocol
   unsigned long int DefaultData;   // is max 32 bits in AVR but could be 64 bits in the protocol
} ACTUATOR_DATA_STRUCT;

#ifdef __GNUG__
typedef struct
#else
typedef flash struct
#endif
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

unsigned char ReceivedCANMessageBuffer[CAN_RECEIVE_BUFFER_SIZE];
unsigned char PtrReceivedCANMessageBufferTop;
unsigned char PtrReceivedCANMessageBufferBottom;

unsigned char ReceivedGlobalCANMessageBuffer[GLOBAL_CAN_RECEIVE_BUFFER_SIZE];
unsigned char PtrReceivedGlobalCANMessageBufferTop;
unsigned char PtrReceivedGlobalCANMessageBufferBottom;

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

unsigned int cntCANMessageReceived = 0;
unsigned int cntGlobalCANMessageReceived = 0;
unsigned int cntCANMessageTransmitted = 0;

unsigned char timerReservationInfo = 1;

#ifdef __GNUG__
extern DEFAULT_NODE_OBJECT_STRUCT DefaultNodeObjects FLASHMEM;
extern OBJECT_VARIABLE_INFORMATION_STRUCT ObjectVariableInformation[] FLASHMEM;
#else
extern flash DEFAULT_NODE_OBJECT_STRUCT DefaultNodeObjects;
extern flash OBJECT_VARIABLE_INFORMATION_STRUCT ObjectVariableInformation[];
#endif

void SendMambaNetReservationInfo();
void DecodeRawMambaNetMessageFromCAN(unsigned char *Buffer, unsigned char BufferPosition, unsigned char MessageLength);
void SendMambaNetMessage7BitsDataToCAN(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength);
void SendMambaNetMessage7BitsDataToCAN_DedicatedAddress(unsigned long int CANAddress, unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength);

inline unsigned char Encode8to7bits(unsigned char *Buffer, unsigned char BufferLength, unsigned char *Buffer7Bit, unsigned char Buffer7BitPosition);
inline unsigned char Decode7to8bits(unsigned char *Buffer, unsigned char BufferPosition, unsigned char DecodeLength, unsigned char *Buffer8Bit);

void SetLocalCANAddress(unsigned long int NewLocalAddress);
void SendCANReservationRequest();
void SendCANParentControlMessage();
void SendCANReservationResponse(unsigned int ManufacturerID, unsigned int ProductID, unsigned int UniqueIDPerProduct, unsigned long int NewCANAddress);
void ProcessCANControlMessage(unsigned char CANControlMessageType);


unsigned char PreProcessMambaNetMessageFromCAN(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength);

// CAN Timer Overrun interrupt service routine
#ifdef __GNUG__
ISR(OVRIT_vect)
#else
interrupt [CTIM_OVF] void can_timer_isr(void)
#endif
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
#ifdef __GNUG__
ISR(CANIT_vect)
#else
interrupt [CAN_IT] void can_isr(void)
#endif
{
   unsigned char cntByte;
   unsigned char ReceivedByte;
   unsigned char SequenceNumber;
   unsigned int FromCANAddress;
   unsigned char OldCANPAGE;
   unsigned char MessageComplete;
   unsigned char CANControlMessageType;

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


         MessageComplete = 0;
         SequenceNumber = (CANIDT4>>3)&0xF;
         
         if (SequenceNumber == ReceiveSequenceNumber)
         {
            unsigned char ProcessData = 0;
            FromCANAddress  = (CANIDT4>>7)&0x001;
            FromCANAddress |= (((unsigned int)CANIDT3)<<1)&0x1FE;
            FromCANAddress |= (((unsigned int)CANIDT2)<<9)&0xE00;
            
            if (SequenceNumber == 0)
            {
               ReceiveCANAddress = FromCANAddress;
               ProcessData = 1;
            }
            else if (ReceiveCANAddress == FromCANAddress)            
            {
               ProcessData = 1;
            }
            
            if (ProcessData)
            {                   
               for (cntByte=0; cntByte<8; cntByte++)
               {
                  ReceivedByte = CANMSG;
   
                  if (!MessageComplete)
                  {
                     if ((ReceivedByte & 0xC0) == 0x80)
                     {  //StartOfMessage
                     }
                     ReceivedCANMessageBuffer[PtrReceivedCANMessageBufferTop] = ReceivedByte;
                     if (((unsigned char)(PtrReceivedCANMessageBufferTop+1)) == PtrReceivedCANMessageBufferBottom)
                     {
                        cntMambaNetOverrunFromCAN++;
                     }
                     else
                     {
                        PtrReceivedCANMessageBufferTop++;
                     }


                     if (ReceivedByte == 0xFF)
                     {  //EndOfMessage
                        MessageComplete = 1;
                        MambaNetEndOfMessageFound = 1;
                     }
                  }
               }
            
               if (MessageComplete)
               {
                  ReceiveSequenceNumber = 0;
               }
               else
               {
                  ReceiveSequenceNumber++;
               }
            }
         }
         CANCDMOB |= 0x80; // CONMOB1:0: Configuration of Message Object = Reception

         cntCANMob0StatusInterruptRXOK++;
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

         MessageComplete = 0;
         SequenceNumber = (CANIDT4>>3)&0xF;
         
         if (SequenceNumber == GlobalReceiveSequenceNumber)
         { 
            unsigned char ProcessData = 0;

            FromCANAddress  = (CANIDT4>>7)&0x001;
            FromCANAddress |= (((unsigned int)CANIDT3)<<1)&0x1FE;
            FromCANAddress |= (((unsigned int)CANIDT2)<<9)&0xE00;

            if (SequenceNumber == 0)
            {
               GlobalReceiveCANAddress = FromCANAddress;
               ProcessData = 1;
            }
            else if (GlobalReceiveCANAddress == FromCANAddress)
            {
               ProcessData = 1;
            }
            
            if (ProcessData)
            {       
               for (cntByte=0; cntByte<8; cntByte++)
               {
                  ReceivedByte = CANMSG;

                  if (!MessageComplete)
                  {
                     if ((ReceivedByte & 0xC0) == 0x80)
                     {  //StartOfMessage
                     }
                     ReceivedGlobalCANMessageBuffer[PtrReceivedGlobalCANMessageBufferTop] = ReceivedByte;
                     if (((unsigned char)(PtrReceivedGlobalCANMessageBufferTop+1)) == PtrReceivedGlobalCANMessageBufferBottom)
                     {
                        cntMambaNetOverrunFromCAN++;
                     }
                     else
                     {
                        PtrReceivedGlobalCANMessageBufferTop++;
                     }

                     if (ReceivedByte == 0xFF)
                     {  //EndOfMessage
                        MessageComplete = 1;
                        GlobalMambaNetEndOfMessageFound = 1;
                     }
                  }
               }

               if (MessageComplete)
               {
                  GlobalReceiveSequenceNumber = 0;
               }
               else
               {
                  GlobalReceiveSequenceNumber++;
               }
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
//PDO = 0;
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
   //CANBT1=0x02;//0x00 or 0x02;
   CANBT1=0x00;// 87,5% Sample point
   // Propagation Time Segement: 0,375 us
   // Re-Sync Jump Width: 0,125 us
   //CANBT2=0x04;//0x0C or 0x04;
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
   
   ObjectNrInformationCount = 0;
   LastObjectInformationRequested = 0;


   cntCANAddressTransmitTop         = CAN_ADDRESS_TRANSMIT_BUFFER_LENGTH;
   LocalCANAddress                  = 0x00000000;
   ReceivedLocalCANAddress          = 0x00000000;
   ReceivedGatewayCANAddress        = 0x00000000;
   
   ReceiveSequenceNumber            = 0;
   GlobalReceiveSequenceNumber      = 0;
   ReceiveCANAddress                = 0x000;
   GlobalReceiveCANAddress          = 0x000;
   TransmitSequenceCANAddress       = 0x00000000;

   //Initialize MOB1 for global receive
   CANGIE &= 0x7F;

   CANPAGE  = 0x10; //(1 << 4);  MO1
   CANSTMOB = 0;
   CANCDMOB = 0;

   CANIDT4  = ((BROADCAST_CAN_ADDRESS&0xFFFF0000)<<3)&0xF8;
   CANIDT3  = ((BROADCAST_CAN_ADDRESS&0xFFFF0000)>>5)&0xFF;
   CANIDT2  = ((BROADCAST_CAN_ADDRESS&0xFFFF0000)>>13)&0xFF;
   CANIDT1  = ((BROADCAST_CAN_ADDRESS&0xFFFF0000)>>21)&0xFF;
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

   PtrReceivedCANMessageBufferTop = 0;
   PtrReceivedCANMessageBufferBottom = 0;
   PtrReceivedGlobalCANMessageBufferTop = 0;
   PtrReceivedGlobalCANMessageBufferBottom = 0;

   cntMambaNetFormatErrorFromCAN = 0;
   cntMambaNetOverrunFromCAN = 0;

   MambaNetEndOfMessageFound = 0;
   GlobalMambaNetEndOfMessageFound = 0;

   AddressValidated = 0;
   timerReservationInfo = 1;
   BusError = 0;

#ifdef __GNUG__
   PORTD &= ~(_BV(PD7));
#else
   RS_CAN = 0;
#endif

}

void SendMambaNetReservationInfo()
{
   unsigned char Data[16];
   unsigned char Buffer7Bit[MAX_MAMBANET_CAN_BUFFER_SIZE];
   unsigned char Buffer7BitLength;
   
   if(--timerReservationInfo != 0)
   {
      return;
   }

   Data[0] = 0x00;   //Type is reservation
   Data[1] = (ManufacturerID>>8)&0xFF;
   Data[2] = ManufacturerID&0xFF;
   Data[3] = (ProductID>>8)&0xFF;
   Data[4] = ProductID&0xFF;
   Data[5] = (UniqueIDPerProduct>>8)&0xFF;
   Data[6] = UniqueIDPerProduct&0xFF;
   Data[7] = (LocalMambaNetAddress>>24)&0xFF;
   Data[8] = (LocalMambaNetAddress>>16)&0xFF;
   Data[9] = (LocalMambaNetAddress>> 8)&0xFF;
   Data[10] = (LocalMambaNetAddress    )&0xFF;
   Data[11] = (DefaultEngineMambaNetAddress>>24)&0xFF;
   Data[12] = (DefaultEngineMambaNetAddress>>16)&0xFF;
   Data[13] = (DefaultEngineMambaNetAddress>> 8)&0xFF;
   Data[14] = (DefaultEngineMambaNetAddress    )&0xFF;
   Data[15] = NodeServices;
   if (AddressValidated)
   {
      Data[15] |= 0x80;
   }
   
   timerReservationInfo = AddressValidated ? 30 : 1;

   Buffer7BitLength = Encode8to7bits(Data, 16, Buffer7Bit, 0);

   SendMambaNetMessage7BitsDataToCAN(0x10000000, LocalMambaNetAddress, 0, 0, 0, Buffer7Bit, 0, Buffer7BitLength);
}

void DecodeRawMambaNetMessageFromCAN(unsigned char *Buffer, unsigned char BufferPosition, unsigned char MessageLength)
{
   if (MessageLength>PROTOCOL_OVERHEAD)
   {
      unsigned long int ToAddress;
      unsigned long int FromAddress;
      unsigned char Ack;
      unsigned int MessageID;
      unsigned int MessageType;
      unsigned char cntBuffer;
      unsigned char cnt;
         
      cntBuffer = BufferPosition;

      Ack = 0;
      if (Buffer[cntBuffer] == 0x82)
      {
         Ack = 1;
      }

      ToAddress = Buffer[cntBuffer++] & 0x01;
      for (cnt=0; cnt<4; cnt++)
      {
         ToAddress <<= 7;
         ToAddress |= Buffer[cntBuffer++] & 0x7F;
      }

      FromAddress = 0;
      for (cnt=0; cnt<4; cnt++)
      {
         FromAddress <<= 7;
         FromAddress |= Buffer[cntBuffer++]&0x7F;
      }

      //MessageID
      MessageID = 0;
      for (cnt=0; cnt<3; cnt++)
      {
         MessageID <<= 7;
         MessageID |= Buffer[cntBuffer++]&0x7F;
      }
      
      MessageType  = ((unsigned int)Buffer[cntBuffer++]<<7)&0x3F80;
      MessageType |= ((unsigned int)Buffer[cntBuffer++]   )&0x007F;

      //((unsigned int)Buffer[cntBuffer++]   )&0x007F; <-length of message
      cntBuffer++;

      if (ProcessMambaNetMessage7BitsDataFromCAN != NULL)
      {
         ProcessMambaNetMessage7BitsDataFromCAN(ToAddress, FromAddress, Ack, MessageID, MessageType, Buffer, cntBuffer, MessageLength-PROTOCOL_OVERHEAD);
      }

      if ((ToAddress == 0x10000000) || (ToAddress == LocalMambaNetAddress))
      {
         unsigned char Buffer8Bits[MAX_MAMBANET_DATA_SIZE];
         unsigned char Buffer8BitsLength;
         unsigned char MessageProcessed;

         Buffer8BitsLength = Decode7to8bits(Buffer, cntBuffer, MessageLength-PROTOCOL_OVERHEAD, Buffer8Bits);

         MessageProcessed = PreProcessMambaNetMessageFromCAN(ToAddress, FromAddress, Ack, MessageID, MessageType, Buffer8Bits, Buffer8BitsLength);

         if (ProcessMambaNetMessageFromCAN != NULL)
         {
            if ((!MessageProcessed) && (AddressValidated))
            {
               ProcessMambaNetMessageFromCAN(ToAddress, FromAddress, Ack, MessageID, MessageType, Buffer8Bits, Buffer8BitsLength);
            }
         }
      }
   }
   else
   {
      cntMambaNetFormatErrorFromCAN++;
   }
}

void SendMambaNetMessage7BitsDataToCAN(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength)
{
   unsigned char cntByte;
   unsigned char MessageLength;
   unsigned char cntBuffer;
   unsigned char cntData;

   if (((AddressValidated) || (MessageType == 0)) && (!BusError))
   {
      if ((DataLength <= MAX_MAMBANET_DATA_SIZE) && (LocalCANAddress != 0x00000000))
      {
         while (cntTransmitCANMessageBuffer < TransmitCANMessageBufferLength)
         {
         }
                  
         if (cntTransmitCANMessageBuffer >= TransmitCANMessageBufferLength)
         {
   //#asm("cli");
            cntBuffer = 0;
            //StartOfMessage
            if ((MessageID) && (!((ToAddress>>28)&0x01)) && ((ToAddress&0x0FFFFFFF) != 0x00000000) && (Ack))
            {  //ackknowledge is never broadcast
               TransmitCANMessageBuffer[cntBuffer++] = 0x82;
            }
            else
            {
               TransmitCANMessageBuffer[cntBuffer++] = 0x80 | ((ToAddress>>28)&0x01);
            }
            
            //ToAddress
            TransmitCANMessageBuffer[cntBuffer++] = (ToAddress>>21)&0x7F;   //7 bits
            TransmitCANMessageBuffer[cntBuffer++] = (ToAddress>>14)&0x7F;   //7 bits
            TransmitCANMessageBuffer[cntBuffer++] = (ToAddress>> 7)&0x7F;   //7 bits
            TransmitCANMessageBuffer[cntBuffer++] =  ToAddress     &0x7F;   //7 bits

            //FromAddress
            TransmitCANMessageBuffer[cntBuffer++] = (FromAddress>>21)&0x7F;   //7 bits
            TransmitCANMessageBuffer[cntBuffer++] = (FromAddress>>14)&0x7F;   //7 bits
            TransmitCANMessageBuffer[cntBuffer++] = (FromAddress>> 7)&0x7F;   //7 bits
            TransmitCANMessageBuffer[cntBuffer++] =  FromAddress     &0x7F;   //7 bits

            //MessageID
            TransmitCANMessageBuffer[cntBuffer++] = (MessageID>>14)&0x7F;   //7 bits
            TransmitCANMessageBuffer[cntBuffer++] = (MessageID>> 7)&0x7F;   //7 bits
            TransmitCANMessageBuffer[cntBuffer++] =  MessageID     &0x7F;   //7 bits

            //MessageType
            TransmitCANMessageBuffer[cntBuffer++] = (MessageType>>7)&0x7F;   //7 bits
            TransmitCANMessageBuffer[cntBuffer++] = (MessageType   )&0x7F;   //7 bits
            //MessageLength
            TransmitCANMessageBuffer[cntBuffer++] = DataLength;

            cntData = DataPosition;
            for (cntByte=0; cntByte<DataLength; cntByte++)
            {
               TransmitCANMessageBuffer[cntBuffer++] = Data[cntData++];
            }
            //EndOfMessage
            TransmitCANMessageBuffer[cntBuffer++] = 0xFF;

            //CAN message size is 'modulo 8'
            MessageLength = DataLength+PROTOCOL_OVERHEAD;
            if (MessageLength&0x07)
            {
               MessageLength += 0x08;
            }
            MessageLength &= 0xF8;
            for (cntByte=cntBuffer; cntByte<MAX_MAMBANET_CAN_BUFFER_SIZE; cntByte++)
            {
               TransmitCANMessageBuffer[cntByte] = 0x00;
            }
   //#asm("sei");

            //Trigger CAN transmit
            TransmitCANMessageBufferLength = 0;
            cntTransmitCANMessageBuffer = 0;
            TransmitCANMessageBufferLength = MessageLength;

            CANPAGE  = 0x20;  //(Mob2 = 0x02 << 4) + auto increment
            CANSTMOB = 0x00;     //Mob status register
            CANCDMOB = 0x00;     //Mob control and DLC register

            //GatewayCANAddress or use TO Address...
            if ((GatewayCANAddress != 0x00000000) && (ToAddress != 0x10000000))
            {
               TransmitSequenceCANAddress = (GatewayCANAddress<<16)&0xFFFF0000;
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

void SendMambaNetMessage7BitsDataToCAN_DedicatedAddress(unsigned long int CANAddress, unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataPosition, unsigned char DataLength)
{
   unsigned char cntByte;
   unsigned char MessageLength;
   unsigned char cntBuffer;
   unsigned char cntData;

   if (((AddressValidated) || (MessageType == 0)) && (!BusError))
   {
      if ((DataLength <= MAX_MAMBANET_DATA_SIZE) && (LocalCANAddress != 0x00000000))
      {
         while (cntTransmitCANMessageBuffer < TransmitCANMessageBufferLength)
         {
         }

         if (cntTransmitCANMessageBuffer >= TransmitCANMessageBufferLength)
         {            

   //#asm("cli");
            cntBuffer = 0;
            //StartOfMessage
            if ((MessageID) && (!((ToAddress>>28)&0x01)) && ((ToAddress&0x0FFFFFFF) != 0x00000000) && (Ack))
            {  //acknowledge is never broadcast
               TransmitCANMessageBuffer[cntBuffer++] = 0x82;
            }
            else
            {
               TransmitCANMessageBuffer[cntBuffer++] = 0x80 | ((ToAddress>>28)&0x01);
            }
            //ToAddress
            TransmitCANMessageBuffer[cntBuffer++] = (ToAddress>>21)&0x7F;   //7 bits
            TransmitCANMessageBuffer[cntBuffer++] = (ToAddress>>14)&0x7F;   //7 bits
            TransmitCANMessageBuffer[cntBuffer++] = (ToAddress>> 7)&0x7F;   //7 bits
            TransmitCANMessageBuffer[cntBuffer++] =  ToAddress     &0x7F;   //7 bits

            //FromAddress
            TransmitCANMessageBuffer[cntBuffer++] = (FromAddress>>21)&0x7F;   //7 bits
            TransmitCANMessageBuffer[cntBuffer++] = (FromAddress>>14)&0x7F;   //7 bits
            TransmitCANMessageBuffer[cntBuffer++] = (FromAddress>> 7)&0x7F;   //7 bits
            TransmitCANMessageBuffer[cntBuffer++] =  FromAddress     &0x7F;   //7 bits

            //MessageID
            TransmitCANMessageBuffer[cntBuffer++] = (MessageID>>14)&0x7F;   //7 bits
            TransmitCANMessageBuffer[cntBuffer++] = (MessageID>> 7)&0x7F;   //7 bits
            TransmitCANMessageBuffer[cntBuffer++] =  MessageID     &0x7F;   //7 bits

            //MessageType
            TransmitCANMessageBuffer[cntBuffer++] = (MessageType>>7)&0x7F;   //7 bits
            TransmitCANMessageBuffer[cntBuffer++] = (MessageType   )&0x7F;   //7 bits
            //MessageLength
            TransmitCANMessageBuffer[cntBuffer++] = DataLength;

            cntData = DataPosition;
            for (cntByte=0; cntByte<DataLength; cntByte++)
            {
               TransmitCANMessageBuffer[cntBuffer++] = Data[cntData++];
            }

            //EndOfMessage
            TransmitCANMessageBuffer[cntBuffer++] = 0xFF;

            //CAN message size is 'modulo 8'
            MessageLength = DataLength+PROTOCOL_OVERHEAD;
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
            CANSTMOB = 0x00;     //Mob status register
            CANCDMOB = 0x00;     //Mob control and DLC register

            //CANAddress or use broadcast address..
            if ((CANAddress != 0x00000000) && (ToAddress != 0x10000000))
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

//Encode 8-to-7 bits in a 256 byte Circular Buffer
inline unsigned char Encode8to7bits(unsigned char *Buffer, unsigned char BufferLength, unsigned char *Buffer7Bit, unsigned char Buffer7BitPosition)
{
   unsigned char cntByte;
   unsigned char cntBuffer7Bit;
   unsigned char Mask1;
   unsigned char Mask2;
   unsigned char BitShift;

   Mask1=0x7F;
   Mask2=0x80;

   cntBuffer7Bit = Buffer7BitPosition;
   Buffer7Bit[cntBuffer7Bit] = 0;
   for (cntByte=0; cntByte<BufferLength; cntByte++)
   {
      BitShift = cntByte%7;
      Mask1 = 0x7F>>BitShift;
      Mask2 = Mask1^0xFF;

      Buffer7Bit[cntBuffer7Bit++] |= (Buffer[cntByte]&Mask1)<<BitShift;
      Buffer7Bit[cntBuffer7Bit  ]  = (Buffer[cntByte]&Mask2)>>(7-BitShift);
      if (Mask2 == 0xFE)
      {
         cntBuffer7Bit++;
         Buffer7Bit[cntBuffer7Bit] = 0x00;
      }
   }
   if ((cntByte%7) != 0)
   {
      cntBuffer7Bit++;
   }

   return (cntBuffer7Bit-Buffer7BitPosition);
}


//Decode 7-to-8 bits
inline unsigned char Decode7to8bits(unsigned char *Buffer, unsigned char BufferPosition, unsigned char DecodeLength, unsigned char *Buffer8Bit)
{
   unsigned char cntByte;
   unsigned char cntBuffer8Bit;
   unsigned char Mask1;
   unsigned char Mask2;

   cntBuffer8Bit = 0;
   Buffer8Bit[cntBuffer8Bit] = Buffer[BufferPosition]&0x7F;
   for (cntByte=1; cntByte<DecodeLength; cntByte++)
   {
      Mask1 = (0x7F>>(cntByte&0x07))<<(cntByte&0x07);
      Mask2 = Mask1^0x7F;

      if (Mask2 != 0x00)
      {
         Buffer8Bit[cntBuffer8Bit++] |= (unsigned char)((Buffer[BufferPosition+cntByte]&Mask2)<<(8-(cntByte&0x07)));
      }
      Buffer8Bit[cntBuffer8Bit] = (unsigned char)((Buffer[BufferPosition+cntByte]&Mask1)>>(cntByte&0x07));
   }
   return cntBuffer8Bit;
}

void SetLocalCANAddress(unsigned long int NewLocalAddress)
{
   unsigned long int ReceiveSequenceCANAddress;
   
   //Initialize MOB0 for local receive
   CANGIE &= 0x7F;

   CANPAGE  = 0x00; //(0 << 4);  MOb0
   CANSTMOB = 0;
   CANCDMOB = 0;

   LocalCANAddress = NewLocalAddress;

   ReceiveSequenceCANAddress = ((LocalCANAddress<<16)&0xFFFF0000);
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

   CANGIE |= 0x80;
}

void SendCANReservationRequest()
{
   if ((LocalCANAddress == 0x0000000) && (!BusError))
   {
      //Trigger CAN transmit
      CANPAGE  = 0x40;  //(Mob2 = 0x04 << 4) + auto increment
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

      CANMSG = (ManufacturerID>>8)&0xFF;
      CANMSG = ManufacturerID&0xFF;
      CANMSG = (ProductID>>8)&0xFF;
      CANMSG = ProductID&0xFF;
      CANMSG = (UniqueIDPerProduct>>8)&0xFF;
      CANMSG = UniqueIDPerProduct&0xFF;
      CANMSG = 0x00;
      CANMSG = 0x00;

      CANCDMOB |= 0x40; //Enable Transmission
   }
}

void SendCANParentControlMessage()
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

      CANMSG = (ManufacturerID>>8)&0xFF;
      CANMSG = ManufacturerID&0xFF;
      CANMSG = (ProductID>>8)&0xFF;
      CANMSG = ProductID&0xFF;
      CANMSG = (UniqueIDPerProduct>>8)&0xFF;
      CANMSG = UniqueIDPerProduct&0xFF;
      CANMSG = 0x00;
      CANMSG = 0x00;

      CANCDMOB |= 0x40; //Enable Transmission
   }
}

void SendCANReservationResponse(unsigned int ManufacturerID, unsigned int ProductID, unsigned int UniqueIDPerProduct, unsigned long int NewCANAddress)
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

          CANAddressTransmit[0] = (ManufacturerID>>8)&0xFF;
          CANAddressTransmit[1] = ManufacturerID&0xFF;
          CANAddressTransmit[2] = (ProductID>>8)&0xFF;
          CANAddressTransmit[3] = ProductID&0xFF;
          CANAddressTransmit[4] = (UniqueIDPerProduct>>8)&0xFF;
          CANAddressTransmit[5] = UniqueIDPerProduct&0xFF;
          CANAddressTransmit[6] = 0x10 | ((NewCANAddress>>8)&0x0F);
          CANAddressTransmit[7] =         NewCANAddress    &0xFF;

          CANAddressTransmit[8] = (ManufacturerID>>8)&0xFF;
          CANAddressTransmit[9] = ManufacturerID&0xFF;
          CANAddressTransmit[10] = (ProductID>>8)&0xFF;
          CANAddressTransmit[11] = ProductID&0xFF;
          CANAddressTransmit[12] = (UniqueIDPerProduct>>8)&0xFF;
          CANAddressTransmit[13] = UniqueIDPerProduct&0xFF;
          CANAddressTransmit[14] = 0x20 | ((NewGatewayAddress>>8)&0x0F);
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
   unsigned char CANControlData[2];

   switch (CANControlMessageType)
   {
      case 0:
      {  //address reservation
         ReceivedManufacturerID = ((unsigned int)CANControlMessage[0]<<8) | CANControlMessage[1];
         ReceivedProductID = ((unsigned int)CANControlMessage[2]<<8) | CANControlMessage[3];
         ReceivedUniqueIDPerProduct = ((unsigned int)CANControlMessage[4]<<8) | CANControlMessage[5];
         ReservationType = (CANControlMessage[6]>>4)&0x0F;
         CANControlData[0] = CANControlMessage[6]&0xF;
         CANControlData[1] = CANControlMessage[7];

         if (  (ReceivedManufacturerID == ManufacturerID) &&
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
         else
         {
#ifdef CAN_ADDRESS_SERVER
            if ((ReservationType == 0) && (CANServices & 0x01))
            {  //Address request, respond if you are a valid CAN address server.
               unsigned long AddressToAssign;
               unsigned char Found;
               char FreeSlot;
               unsigned long cnt;
               //Check for address
               AddressToAssign = 0x0000001;
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
      {  //parent control
         Parent[0] = CANControlMessage[0];
         Parent[1] = CANControlMessage[1];
         Parent[2] = CANControlMessage[2];
         Parent[3] = CANControlMessage[3];
         Parent[4] = CANControlMessage[4];
         Parent[5] = CANControlMessage[5];
      }
      break;
   }
}

void ProcessCAN()
{
   if (MambaNetEndOfMessageFound)
   {
      MambaNetEndOfMessageFound = 0;
      if (((unsigned char)PtrReceivedCANMessageBufferTop-PtrReceivedCANMessageBufferBottom)>PROTOCOL_OVERHEAD)
      {
         unsigned char cntCheck;
         unsigned char StartPointer = 0;
         unsigned char ReceivedByte;

         cntCheck = PtrReceivedCANMessageBufferBottom;
         while (cntCheck != PtrReceivedCANMessageBufferTop)
         {
            if ((ReceivedByte = ReceivedCANMessageBuffer[cntCheck++]) & 0x80)
            {
//               PDO=1;
               switch (ReceivedByte&0xC0)
               {
                  case 0x80: //0x80, 0x81, 0x82
                  {  //MambaNet SOM found.
                     StartPointer = cntCheck-1;
                  }
                  break;
                  case 0xC0:
                  {  //MambaNet EOM found.
                     if (ReceivedByte == 0xFF)
                     {
                        DecodeRawMambaNetMessageFromCAN(ReceivedCANMessageBuffer, StartPointer, cntCheck-StartPointer);
                        PtrReceivedCANMessageBufferBottom = cntCheck;
                        cntCANMessageReceived++;
                     }
                  }
                  break;
               }
//               PDO=1;
            }
         }
      }
   }

   if (GlobalMambaNetEndOfMessageFound)
   {
      GlobalMambaNetEndOfMessageFound = 0;
      if (((unsigned char)PtrReceivedGlobalCANMessageBufferTop-PtrReceivedGlobalCANMessageBufferBottom)>PROTOCOL_OVERHEAD)
      {
         unsigned char cntCheck;
         unsigned char StartPointer = 0;
         unsigned char ReceivedByte;

         cntCheck = PtrReceivedGlobalCANMessageBufferBottom;
         while (cntCheck != PtrReceivedGlobalCANMessageBufferTop)
         {
            if ((ReceivedByte = ReceivedGlobalCANMessageBuffer[cntCheck++]) & 0x80)
            {
               switch (ReceivedByte&0xC0)
               {
                  case 0x80:  //0x80, 0x81, 0x82
                  {  //MambaNet SOM found.
                     StartPointer = cntCheck-1;
                  }
                  break;
                  case 0xC0:
                  {  //MambaNet EOM found.
                     if (ReceivedByte == 0xFF)
                     {
                        DecodeRawMambaNetMessageFromCAN(ReceivedGlobalCANMessageBuffer, StartPointer, cntCheck-StartPointer);
                        PtrReceivedGlobalCANMessageBufferBottom = cntCheck;
                        cntGlobalCANMessageReceived++;
                     }
                  }
                  break;
               }
            }
         }
      }
   }
}

void SendMambaNetMessageToCAN(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength)
{
   unsigned char Buffer7Bit[MAX_MAMBANET_CAN_BUFFER_SIZE];
   unsigned char Buffer7BitLength;

   Buffer7BitLength = Encode8to7bits(Data, DataLength, Buffer7Bit, 0);

   SendMambaNetMessage7BitsDataToCAN(ToAddress, FromAddress, Ack, MessageID, MessageType, Buffer7Bit, 0, Buffer7BitLength);
}

void SendSensorChangeToMambaNet(unsigned int ObjectNr, unsigned char DataType, unsigned char DataSize, unsigned char *Data)
{
   if (ObjectWritableInformation[ObjectNr-1024].UpdateFrequency)
   {
      unsigned char TransmitBuffer[MAX_MAMBANET_DATA_SIZE];
      unsigned char cntByte;
      unsigned long int EngineMambaNetAddress;

      TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
      TransmitBuffer[1] = ObjectNr&0xFF;
      TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_CHANGED;
      TransmitBuffer[3] = DataType;
      TransmitBuffer[4] = DataSize;
      for (cntByte=0; cntByte<DataSize; cntByte++)
      {
         TransmitBuffer[(unsigned char)(5+cntByte)] = Data[cntByte];
      }
   
      EngineMambaNetAddress = 0x10000000;
      if (DefaultEngineMambaNetAddress)
      {
         EngineMambaNetAddress = DefaultEngineMambaNetAddress;
      }
      if (ObjectWritableInformation[ObjectNr-1024].EngineMambaNetAddress)
      {
         EngineMambaNetAddress = ObjectWritableInformation[ObjectNr-1024].EngineMambaNetAddress;
      }

      SendMambaNetMessageToCAN(EngineMambaNetAddress, LocalMambaNetAddress, 0, 0, 1, TransmitBuffer, 5+DataSize);
   }
}

unsigned char PreProcessMambaNetMessageFromCAN(unsigned long int ToAddress, unsigned long int FromAddress, unsigned char Ack, unsigned long int MessageID, unsigned int MessageType, unsigned char *Data, unsigned char DataLength)
{
   unsigned char MessageProcessed;
   
   if (MessageID)
   {
      Ack = 1;
   }

   MessageProcessed = 0;

   switch (MessageType)
   {
      case 0:
      {  //Address Reservation
         unsigned char AddressReservationType;
         unsigned int ReceivedManufacturerID;
         unsigned int ReceivedProductID;
         unsigned int ReceivedUniqueIDPerProduct;
         unsigned long int ReceivedMambaNetAddress;
         unsigned long int ReceivedDefaultEngineMambaNetAddress;

         AddressReservationType        = Data[0];
         ReceivedManufacturerID        = ((unsigned int)Data[1])<<8;
         ReceivedManufacturerID        |=               Data[2];
         ReceivedProductID             = ((unsigned int)Data[3])<<8;
         ReceivedProductID             |=               Data[4];
         ReceivedUniqueIDPerProduct    = ((unsigned int)Data[5])<<8;
         ReceivedUniqueIDPerProduct    |=               Data[6];
         ReceivedMambaNetAddress        = (((unsigned long int)Data[ 7])<<24)&0xFF000000;
         ReceivedMambaNetAddress       |= (((unsigned long int)Data[ 8])<<16)&0x00FF0000;
         ReceivedMambaNetAddress       |= (((unsigned long int)Data[ 9])<< 8)&0x0000FF00;
         ReceivedMambaNetAddress       |= (((unsigned long int)Data[10])    )&0x000000FF;
         ReceivedDefaultEngineMambaNetAddress        = (((unsigned long int)Data[11])<<24)&0xFF000000;
         ReceivedDefaultEngineMambaNetAddress       |= (((unsigned long int)Data[12])<<16)&0x00FF0000;
         ReceivedDefaultEngineMambaNetAddress       |= (((unsigned long int)Data[13])<< 8)&0x0000FF00;
         ReceivedDefaultEngineMambaNetAddress       |= (((unsigned long int)Data[14])    )&0x000000FF;

         if (  (ReceivedManufacturerID       == ManufacturerID) &&
               (ReceivedProductID            == ProductID) &&
               (ReceivedUniqueIDPerProduct   == UniqueIDPerProduct))
         {  //Reservation message for my Unique ID.
            if (AddressReservationType == MAMBANET_ADDRESS_RESERVATION_TYPE_RESPONSE)
            {  //Response to a request.
               LocalMambaNetAddress = ReceivedMambaNetAddress;
               DefaultEngineMambaNetAddress = ReceivedDefaultEngineMambaNetAddress;

               if (LocalMambaNetAddress == 0x00000000)
               {
                  AddressValidated = 0;
               }
               else
               {
                  if (Data[15]&0x80)
                  {
                     AddressValidated = 1;
                  }
                  else
                  {
                     AddressValidated = 0;
                  } 
               }
               BusError = 0;
            }
         }
         if ((AddressReservationType == MAMBANET_ADDRESS_RESERVATION_TYPE_PING) || (AddressReservationType == MAMBANET_ADDRESS_RESERVATION_TYPE_RESPONSE))
         {
            timerReservationInfo = 1;
            SendMambaNetReservationInfo();
         }
         MessageProcessed = 1;
      }
      break;
   }

   if (AddressValidated)
   {
      switch (MessageType)
      {
         case 1:
         {  //Object message
            unsigned int ObjectNr;
            unsigned char ObjectMessageAction;

            ObjectNr = ((unsigned int)Data[0]<<8) | Data[1];
            ObjectMessageAction = Data[2];

            switch (ObjectMessageAction)
            {
               case  MAMBANET_OBJECT_ACTION_GET_INFORMATION:
               {
                 if ((ObjectNr>=1024) && (ObjectNr<(1024+NumberOfStaticObjects)))
                 {  //Only for the non-standard objects                      
                      unsigned char TransmitBuffer[96];
                      char cntSize;
                      int TableNr;
                      char DataSize;
                      unsigned long int TempData;
                      unsigned char cntChar;

                      ObjectNrInformationCount++;
                      LastObjectInformationRequested = ObjectNr;
                      TableNr = ObjectNr-1024;

                      cntSize=0;
                      TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                      TransmitBuffer[1] = ObjectNr&0xFF;
                      TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_INFORMATION_RESPONSE;
                      TransmitBuffer[3] = OBJECT_INFORMATION_DATATYPE;
                      TransmitBuffer[4] = cntSize;
                      for (cntChar=0; cntChar<32; cntChar++)
                      {
                          TransmitBuffer[(unsigned char)(5+cntSize++)] = ObjectVariableInformation[TableNr].Description[cntChar];
                      }
                      TransmitBuffer[(unsigned char)(5+cntSize++)] = ObjectVariableInformation[TableNr].Services;
                      //Sensor
                      TransmitBuffer[(unsigned char)(5+cntSize++)] = ObjectVariableInformation[TableNr].Sensor.DataType;
                      DataSize = ObjectVariableInformation[TableNr].Sensor.DataSize;
                      TransmitBuffer[(unsigned char)(5+cntSize++)] = DataSize;
                      if ((ObjectVariableInformation[TableNr].Sensor.DataType == OCTET_STRING_DATATYPE) || (ObjectVariableInformation[TableNr].Sensor.DataType == BIT_STRING_DATATYPE))
                      {
                        DataSize = 1;
                      }
                      TempData = ObjectVariableInformation[TableNr].Sensor.DataMinimal;
                      for (cntChar=0; cntChar<DataSize; cntChar++)
                      {
                        TransmitBuffer[(unsigned char)(5+cntSize++)] = (unsigned char)((TempData>>(((DataSize-cntChar)-1)<<3))&0xFF);
                      }
                      TempData = ObjectVariableInformation[TableNr].Sensor.DataMaximal;
                      for (cntChar=0; cntChar<DataSize; cntChar++)
                      {
                        TransmitBuffer[(unsigned char)(5+cntSize++)] = (unsigned char)((TempData>>(((DataSize-cntChar)-1)<<3))&0xFF);
                      }
                     //Actuator
                      TransmitBuffer[(unsigned char)(5+cntSize++)] = ObjectVariableInformation[TableNr].Actuator.DataType;
                      DataSize = ObjectVariableInformation[TableNr].Actuator.DataSize;
                      TransmitBuffer[(unsigned char)(5+cntSize++)] = DataSize;
                      if ((ObjectVariableInformation[TableNr].Actuator.DataType == OCTET_STRING_DATATYPE) || (ObjectVariableInformation[TableNr].Actuator.DataType == BIT_STRING_DATATYPE))
                      {
                        DataSize = 1;
                      }

                      TempData = ObjectVariableInformation[TableNr].Actuator.DataMinimal;
                      for (cntChar=0; cntChar<DataSize; cntChar++)
                      {
                        TransmitBuffer[(unsigned char)(5+cntSize++)] = (unsigned char)((TempData>>(((DataSize-cntChar)-1)<<3))&0xFF);
                      }
                      TempData = ObjectVariableInformation[TableNr].Actuator.DataMaximal;
                      for (cntChar=0; cntChar<DataSize; cntChar++)
                      {
                        TransmitBuffer[(unsigned char)(5+cntSize++)] = (unsigned char)((TempData>>(((DataSize-cntChar)-1)<<3))&0xFF);
                      }
                      TempData = ObjectVariableInformation[TableNr].Actuator.DefaultData;
                      for (cntChar=0; cntChar<DataSize; cntChar++)
                      {
                        TransmitBuffer[(unsigned char)(5+cntSize++)] = (unsigned char)((TempData>>(((DataSize-cntChar)-1)<<3))&0xFF);
                      }
                      //Adjust the size
                      TransmitBuffer[4] = cntSize;

                      SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, cntSize+5);
                      MessageProcessed = 1;
                 }
                 else if ((ObjectNr>=(1024+NumberOfStaticObjects)) && (ObjectNr<(1024+DefaultNodeObjects.NumberOfObjects)))
                 {   //dynamic generated objects, so not processed
                      MessageProcessed = 0;
                 }
                 else
                 {
                      unsigned char TransmitBuffer[20];

                      TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                      TransmitBuffer[1] = ObjectNr&0xFF;
                      TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_INFORMATION_RESPONSE;
                      TransmitBuffer[3] = ERROR_DATATYPE;
                      TransmitBuffer[4] = 15;
                      sprintf((char *)&TransmitBuffer[5], "Not implemented");

                      SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 20);
                      MessageProcessed = 1;
                 }
               }
               break;
               case MAMBANET_OBJECT_ACTION_INFORMATION_RESPONSE:
               {       //Not implemented
               }
               break;
               case MAMBANET_OBJECT_ACTION_GET_ENGINE_ADDRESS:
               {
                 if ((ObjectNr>=1024) && (ObjectNr<(1024+NumberOfStaticObjects)))
                 {  //Only for the non-standard objects
                      unsigned char TransmitBuffer[9];
                      unsigned long int EngineMambaNetAddress;

                      EngineMambaNetAddress = ObjectWritableInformation[ObjectNr-1024].EngineMambaNetAddress;

                      TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                      TransmitBuffer[1] = ObjectNr&0xFF;
                      TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ENGINE_ADDRESS_RESPONSE;
                      TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                      TransmitBuffer[4] = 4;
                      TransmitBuffer[5] = (EngineMambaNetAddress>>24)&0xFF;
                      TransmitBuffer[6] = (EngineMambaNetAddress>>16)&0xFF;
                      TransmitBuffer[7] = (EngineMambaNetAddress>> 8)&0xFF;
                      TransmitBuffer[8] =  EngineMambaNetAddress     &0xFF;

                      SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 9);
                      MessageProcessed = 1;
                 }
                 else if ((ObjectNr>=(1024+NumberOfStaticObjects)) && (ObjectNr<(1024+DefaultNodeObjects.NumberOfObjects)))
                 {   //dynamic generated objects, so not processed
                     MessageProcessed = 0;
                 }
                 else
                 {
                      unsigned char TransmitBuffer[20];

                      TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                      TransmitBuffer[1] = ObjectNr&0xFF;
                      TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ENGINE_ADDRESS_RESPONSE;
                      TransmitBuffer[3] = ERROR_DATATYPE;
                      TransmitBuffer[4] = 15;
                      sprintf((char *)&TransmitBuffer[5], "Not implemented");

                      SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 20);
                      MessageProcessed = 1;
                 }
               }
               break;
               case MAMBANET_OBJECT_ACTION_ENGINE_ADDRESS_RESPONSE:
               {  //Not implemented
               }
               break;
               case MAMBANET_OBJECT_ACTION_SET_ENGINE_ADDRESS:
               {
                 if ((ObjectNr>=1024) && (ObjectNr<(1024+NumberOfStaticObjects)))
                 {  //Only for the non-standard objects
                     unsigned char DataType;
                     unsigned char DataSize;

                     DataType = Data[3];
                     DataSize = Data[4];

                     if (DataType == UNSIGNED_INTEGER_DATATYPE)
                     {
                        if (DataSize == 4)
                        {
                           unsigned long int EngineMambaNetAddress;


                           EngineMambaNetAddress = Data[5];
                           EngineMambaNetAddress <<= 8;
                           EngineMambaNetAddress |= Data[6];
                           EngineMambaNetAddress <<= 8;
                           EngineMambaNetAddress |= Data[7];
                           EngineMambaNetAddress <<= 8;
                           EngineMambaNetAddress |= Data[8];

                           ObjectWritableInformation[ObjectNr-1024].EngineMambaNetAddress = EngineMambaNetAddress;

                           if (MessageID)
                           {
                              unsigned char TransmitBuffer[16];
                           
                              TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                              TransmitBuffer[1] = ObjectNr&0xFF;
                              TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ENGINE_ADDRESS_RESPONSE;
                              TransmitBuffer[3] = NO_DATA_DATATYPE;
      
                              SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 4);
                           }                 

                           MessageProcessed = 1;
                        }
                     }
                     
                  }
                  else if ((ObjectNr>=(1024+NumberOfStaticObjects)) && (ObjectNr<(1024+DefaultNodeObjects.NumberOfObjects)))
                  {   //dynamic generated objects, so not processed
                     MessageProcessed = 0;
                  }
                  else
                  {
                      unsigned char TransmitBuffer[20];

                      TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                      TransmitBuffer[1] = ObjectNr&0xFF;
                      TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ENGINE_ADDRESS_RESPONSE;
                      TransmitBuffer[3] = ERROR_DATATYPE;
                      TransmitBuffer[4] = 15;
                      sprintf((char *)&TransmitBuffer[5], "Not implemented");

                      SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 20);
                      MessageProcessed = 1;
                  }
                  
               }
               break;
               case  MAMBANET_OBJECT_ACTION_GET_OBJECT_FREQUENCY:
               {
                 if ((ObjectNr>=1024) && (ObjectNr<(1024+NumberOfStaticObjects)))
                 {  //Only for the non-standard objects
                      if (ObjectVariableInformation[ObjectNr].Services != 0x00)
                      {
                         unsigned char TransmitBuffer[6];
                         unsigned char ObjectFrequency;

                         ObjectFrequency = ObjectWritableInformation[ObjectNr-1024].UpdateFrequency;

                         TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                         TransmitBuffer[1] = ObjectNr&0xFF;
                         TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_OBJECT_FREQUENCY_RESPONSE;
                         TransmitBuffer[3] = STATE_DATATYPE;
                         TransmitBuffer[4] = 1;
                         TransmitBuffer[5] = ObjectFrequency&0xFF;

                         SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);
                         MessageProcessed = 1;
                     }
                 }
                 else if ((ObjectNr>=(1024+NumberOfStaticObjects)) && (ObjectNr<(1024+DefaultNodeObjects.NumberOfObjects)))
                 {   //dynamic generated objects, so not processed
                     MessageProcessed = 0;
                 }
                 else
                 {
                      unsigned char TransmitBuffer[20];

                      TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                      TransmitBuffer[1] = ObjectNr&0xFF;
                      TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_OBJECT_FREQUENCY_RESPONSE;
                      TransmitBuffer[3] = ERROR_DATATYPE;
                      TransmitBuffer[4] = 15;
                      sprintf((char *)&TransmitBuffer[5], "Not implemented");

                      SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 20);
                      MessageProcessed = 1;
                 }
               }
               break;
               case  MAMBANET_OBJECT_ACTION_OBJECT_FREQUENCY_RESPONSE:
               {  //No implementation required.
               }
               break;
               case  MAMBANET_OBJECT_ACTION_SET_OBJECT_FREQUENCY:
               {
                 if ((ObjectNr>=1024) && (ObjectNr<(1024+NumberOfStaticObjects)))
                 {  //Only for the non-standard objects
                     unsigned char DataType;
                     unsigned char DataSize;

                     DataType = Data[3];
                     DataSize = Data[4];

                     if (DataType == STATE_DATATYPE)
                     {
                        if (DataSize == 1)
                        {
                           unsigned char ObjectFrequency;

                           ObjectFrequency = Data[5]&0x0F;
                           ObjectWritableInformation[ObjectNr-1024].UpdateFrequency = ObjectFrequency;

                           MessageProcessed = 1;

                           if (MessageID)
                           {
                              unsigned char TransmitBuffer[16];
                           
                              TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                              TransmitBuffer[1] = ObjectNr&0xFF;
                              TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_OBJECT_FREQUENCY_RESPONSE;
                              TransmitBuffer[3] = NO_DATA_DATATYPE;
   
                              SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 4);
                           }                                           
                        }
                     }
                  }
                  else if ((ObjectNr>=(1024+NumberOfStaticObjects)) && (ObjectNr<(1024+DefaultNodeObjects.NumberOfObjects)))
                  {   //dynamic generated objects, so not processed
                     MessageProcessed = 0;
                  }
                  else
                  {
                      unsigned char TransmitBuffer[20];

                      TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                      TransmitBuffer[1] = ObjectNr&0xFF;
                      TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_OBJECT_FREQUENCY_RESPONSE;
                      TransmitBuffer[3] = ERROR_DATATYPE;
                      TransmitBuffer[4] = 15;
                      sprintf((char *)&TransmitBuffer[5], "Not implemented");

                      SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 20);
                      MessageProcessed = 1;
                  }
               }
               break;
               case  MAMBANET_OBJECT_ACTION_GET_SENSOR_DATA:
               {
                 if (ObjectNr<1024)
                 {  //Only for the standard obects.
                     unsigned char TransmitBuffer[69];
                     unsigned char cntByte;

                     switch (ObjectNr)
                     {
                        case 0:
                        {  //Description
                           TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                           TransmitBuffer[1] = ObjectNr&0xFF;
                           TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                           TransmitBuffer[3] = OCTET_STRING_DATATYPE;
                           TransmitBuffer[4] = 64;
                           for (cntByte=0; cntByte<64; cntByte++)
                           {
                              TransmitBuffer[(unsigned char)(5+cntByte)] = DefaultNodeObjects.Description[cntByte];
                           }

                           SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 69);
                        }
                        break;
   //                     case 1: Name is an actuator
                        case 2:
                        {  //ManufacturerID
                           TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                           TransmitBuffer[1] = ObjectNr&0xFF;
                           TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                           TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                           TransmitBuffer[4] = 2;
                           TransmitBuffer[5] = (DefaultNodeObjects.ManufacturerID>>8)&0xFF;
                           TransmitBuffer[6] = DefaultNodeObjects.ManufacturerID&0xFF;

                           SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 7);
                        }
                        break;
                        case 3:
                        {  //ProductID
                           TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                           TransmitBuffer[1] = ObjectNr&0xFF;
                           TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                           TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                           TransmitBuffer[4] = 2;
                           TransmitBuffer[5] = (DefaultNodeObjects.ProductID>>8)&0xFF;
                           TransmitBuffer[6] = DefaultNodeObjects.ProductID&0xFF;

                           SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 7);
                        }
                        break;
                        case 4:
                        {  //UniqueID
                           TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                           TransmitBuffer[1] = ObjectNr&0xFF;
                           TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                           TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                           TransmitBuffer[4] = 2;                           
                           TransmitBuffer[5] = (UniqueIDPerProduct>>8)&0xFF;
                           TransmitBuffer[6] = UniqueIDPerProduct&0xFF;
                           //TransmitBuffer[5] = (DefaultNodeObjects.UniqueMediaAccessID>>8)&0xFF;
                           //TransmitBuffer[6] = DefaultNodeObjects.UniqueMediaAccessID&0xFF;

                           SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 7);
                        }
                        break;
                        case 5:
                        {  //HardwareMajorRevision
                           TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                           TransmitBuffer[1] = ObjectNr&0xFF;
                           TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                           TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                           TransmitBuffer[4] = 1;
                           TransmitBuffer[5] = DefaultNodeObjects.HardwareMajorRevision;

                           SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);
                        }
                        break;
                        case 6:
                        {  //HarwareMinorRevision
                           TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                           TransmitBuffer[1] = ObjectNr&0xFF;
                           TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                           TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                           TransmitBuffer[4] = 1;
                           TransmitBuffer[5] = (DefaultNodeObjects.HardwareMinorRevision&0xF0) | (HardwareMinorRevision&0x0F);

                           SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);
                        }
                        break;
                        case 7:
                        {  //FirmwareMajorRevision
                           TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                           TransmitBuffer[1] = ObjectNr&0xFF;
                           TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                           TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                           TransmitBuffer[4] = 1;
                           TransmitBuffer[5] = DefaultNodeObjects.FirmwareMajorRevision;

                           SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);
                        }
                        break;
                        case 8:
                        {  //FirmwareMinorRevision
                           TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                           TransmitBuffer[1] = ObjectNr&0xFF;
                           TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                           TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                           TransmitBuffer[4] = 1;
                           TransmitBuffer[5] = DefaultNodeObjects.FirmwareMinorRevision;

                           SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);
                        }
                        break;
                        case 9:
                        {  //FPGAFirmwareMajorRevision
                           TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                           TransmitBuffer[1] = ObjectNr&0xFF;
                           TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                           TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                           TransmitBuffer[4] = 1;
                           TransmitBuffer[5] = FPGAFirmwareMajorRevision;

                           SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);
                        }
                        break;
                        case 10:
                        {  //FPGAFirmwareMinorRevision
                           TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                           TransmitBuffer[1] = ObjectNr&0xFF;
                           TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                           TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                           TransmitBuffer[4] = 1;
                           TransmitBuffer[5] = FPGAFirmwareMinorRevision;

                           SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);
                        }
                        break;
                        case 11:
                        {  //ProtocolMajorRevision
                           TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                           TransmitBuffer[1] = ObjectNr&0xFF;
                           TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                           TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                           TransmitBuffer[4] = 1;
                           TransmitBuffer[5] = DefaultNodeObjects.ProtocolMajorRevision;

                           SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);
                        }
                        break;
                        case 12:
                        {  //ProtocolMinorRevision
                           TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                           TransmitBuffer[1] = ObjectNr&0xFF;
                           TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                           TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                           TransmitBuffer[4] = 1;
                           TransmitBuffer[5] = DefaultNodeObjects.ProtocolMinorRevision;

                           SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);
                        }
                        break;
                        case 13:
                        {  //Number of Objects
                           TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                           TransmitBuffer[1] = ObjectNr&0xFF;
                           TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                           TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                           TransmitBuffer[4] = 2;
                           TransmitBuffer[5] = (DefaultNodeObjects.NumberOfObjects>>8)&0xFF;
                           TransmitBuffer[6] = DefaultNodeObjects.NumberOfObjects&0xFF;

                           SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 7);
                        }
                        break;
   //                     case 14: Default engine address is an actuator
                        case 15:
                        { //Hardware parent
                           TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                           TransmitBuffer[1] = ObjectNr&0xFF;
                           TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                           TransmitBuffer[3] = OCTET_STRING_DATATYPE;
                           TransmitBuffer[4] = 6;
                           TransmitBuffer[5] = Parent[0];
                           TransmitBuffer[6] = Parent[1];
                           TransmitBuffer[7] = Parent[2];
                           TransmitBuffer[8] = Parent[3];
                           TransmitBuffer[9] = Parent[4];
                           TransmitBuffer[10] = Parent[5];

                           SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 11);
                        }
                        break;
                        case 16:
                        { //Service requested
                           TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                           TransmitBuffer[1] = ObjectNr&0xFF;
                           TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                           TransmitBuffer[3] = STATE_DATATYPE;
                           TransmitBuffer[4] = 1;
                           TransmitBuffer[5] = 0;

                           SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 6);
                        }
                        break;
                        default:
                        {
                            TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                            TransmitBuffer[1] = ObjectNr&0xFF;
                            TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE;
                            TransmitBuffer[3] = ERROR_DATATYPE;
                            TransmitBuffer[4] = 15;
                            sprintf((char *)&TransmitBuffer[5], "Not implemented");

                            SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 20);
                            MessageProcessed = 1;
                        }
                        break;
                     }
                     MessageProcessed = 1;
                 }
               }
               break;
               case  MAMBANET_OBJECT_ACTION_SENSOR_DATA_RESPONSE:
               {       //Not implemented
               }
               break;
               case  MAMBANET_OBJECT_ACTION_GET_ACTUATOR_DATA:
               {
                 if (ObjectNr<1024)
                 {  //Only for the standard obects.
                     unsigned char TransmitBuffer[37];
                     unsigned char cntByte;

                     switch (ObjectNr)
                     {
                        case 1:
                        {  //Name
                           TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                           TransmitBuffer[1] = ObjectNr&0xFF;
                           TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE;
                           TransmitBuffer[3] = OCTET_STRING_DATATYPE;
                           TransmitBuffer[4] = 32;
                           for (cntByte=0; cntByte<32; cntByte++)
                           {
                              TransmitBuffer[(unsigned char)(5+cntByte)] = NodeName[cntByte];
                           }

                           SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 37);
                        }
                        break;
                        case 14:
                        {  //Default engine address
                           TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                           TransmitBuffer[1] = ObjectNr&0xFF;
                           TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE;
                           TransmitBuffer[3] = UNSIGNED_INTEGER_DATATYPE;
                           TransmitBuffer[4] = 4;
                           TransmitBuffer[5] = (DefaultEngineMambaNetAddress>>24)&0xFF;
                           TransmitBuffer[6] = (DefaultEngineMambaNetAddress>>16)&0xFF;
                           TransmitBuffer[7] = (DefaultEngineMambaNetAddress>>8 )&0xFF;
                           TransmitBuffer[8] =  DefaultEngineMambaNetAddress     &0xFF;

                           SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 9);
                        }
                        break;
                        default:
                        {
                            TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                            TransmitBuffer[1] = ObjectNr&0xFF;
                            TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE;
                            TransmitBuffer[3] = ERROR_DATATYPE;
                            TransmitBuffer[4] = 15;
                            sprintf((char *)&TransmitBuffer[5], "Not implemented");

                            SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 20);
                        }
                        break;
                     }
                     MessageProcessed = 1;
                  }
               }
               break;
               case  MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE:
               {       //Not implemented
               }
               break;
               case  MAMBANET_OBJECT_ACTION_SET_ACTUATOR_DATA:
               {
                  if (ObjectNr<1024)
                  {
                     unsigned char DataType;
                     unsigned char DataSize;

                     DataType = Data[3];
                     DataSize = Data[4];

                     switch (ObjectNr)
                     {
                        case 1:
                        {  //Name
                           if (DataType == OCTET_STRING_DATATYPE)
                           {
                              if (DataSize <= 32)
                              {
                                 unsigned char cntChar;
                                 char TextString[33];

                                 for (cntChar=0; cntChar<DataSize; cntChar++)
                                 {
                                    NodeName[cntChar] = Data[(unsigned char)(5+cntChar)];
                                 }
                                 for (cntChar=DataSize; cntChar<32; cntChar++)
                                 {
                                    TextString[cntChar] = ' ';
                                 }
                              }
                           }
                        }
                        break;
                        case 12:
                        {  //engine address
                           if (DataType == UNSIGNED_INTEGER_DATATYPE)
                           {
                              if (DataSize == 4)
                              {
                                 unsigned long int EngineMambaNetAddress;

                                 EngineMambaNetAddress = Data[5];
                                 EngineMambaNetAddress <<= 8;
                                 EngineMambaNetAddress |= Data[6];
                                 EngineMambaNetAddress <<= 8;
                                 EngineMambaNetAddress |= Data[7];
                                 EngineMambaNetAddress <<= 8;
                                 EngineMambaNetAddress |= Data[8];

                                 DefaultEngineMambaNetAddress = EngineMambaNetAddress;
                              }
                           }
                        }
                        break;
                        default:
                        {
                            unsigned char TransmitBuffer[20];

                            TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                            TransmitBuffer[1] = ObjectNr&0xFF;
                            TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE;
                            TransmitBuffer[3] = ERROR_DATATYPE;
                            TransmitBuffer[4] = 15;
                            sprintf((char *)&TransmitBuffer[5], "Not implemented");

                            SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 20);
                            MessageProcessed = 1;
                        }
                        break;
                     }
                     MessageProcessed = 1;
                  }
                  else
                  {
                     unsigned long int EngineMambaNetAddress;

                     if (ObjectNr<(1024+NumberOfStaticObjects))
                     {
                        EngineMambaNetAddress = ObjectWritableInformation[ObjectNr-1024].EngineMambaNetAddress;

                        //if engine address is empty or set to broadcast message, we must be processed in the application
                        if ((EngineMambaNetAddress != 0x00000000) && (EngineMambaNetAddress != 0x10000000))
                        {
                           //if engine address set but not equal to transmitter, we must NOT process the message in the application.
                           if (FromAddress != EngineMambaNetAddress)
                           {
                              MessageProcessed = 1;
                           }
                        }
                     }
                  }
                  
                  if (MessageProcessed)
                  {
                     if (MessageID)
                     {
                        unsigned char TransmitBuffer[16];
                        
                        Ack = 1;
                  
                        TransmitBuffer[0] = (ObjectNr>>8)&0xFF;
                        TransmitBuffer[1] = ObjectNr&0xFF;
                        TransmitBuffer[2] = MAMBANET_OBJECT_ACTION_ACTUATOR_DATA_RESPONSE;
                        TransmitBuffer[3] = NO_DATA_DATATYPE;
   
                        SendMambaNetMessageToCAN(FromAddress, LocalMambaNetAddress, Ack, MessageID, 1, TransmitBuffer, 4);
                     }                 
                  }
               }
               break;
            }
         }
         break;
      }
   }
   return MessageProcessed;
   ToAddress = 0;
   DataLength = 0;
}

//make a 32 float representation.
//8 bit  = seee mmmm
//16 bit = seee eemm mmmm mmmm
//32 bit = seee eeee emmm mmmm mmmm mmmm mmmm mmmm
unsigned char VariableFloat2Float(unsigned char *VariableFloatBuffer, unsigned char VariableFloatBufferSize, float *ReturnFloatValue)
{
   unsigned long TemporyForCast;
   int exponent;
   unsigned long mantessa;
   char signbit;
   unsigned char ReturnStatus;
   unsigned char cntSize;
   char NonZero;

   ReturnStatus = 0;

   NonZero=0;
   for (cntSize=0; cntSize<VariableFloatBufferSize; cntSize++)
   {
      if (VariableFloatBuffer[cntSize] != 0x00)
      {
         NonZero = 1;
      }
   }

   if (NonZero)
   {
      switch (VariableFloatBufferSize)
      {
         case 1:
         {
            signbit = (VariableFloatBuffer[0]>>7)&0x01;
            exponent = (VariableFloatBuffer[0]>>4)&0x07;
            mantessa = (VariableFloatBuffer[0]   )&0x0F;
            if (exponent == 0)
            {  //denormalized
               exponent = -127;
            }
            else if (exponent == 7)
            {  //+/-INF or NaN, depends on sign
               exponent = 128;
            }
            else
            {
               exponent -= 3;
            }

            TemporyForCast = signbit;
            TemporyForCast <<= 8;
            TemporyForCast |= (((long)exponent+127)&0xFF);
            TemporyForCast <<= 4;
            TemporyForCast |= mantessa&0x0F;
            TemporyForCast <<= 8;
            TemporyForCast <<= 8;
            TemporyForCast <<= 3;

            *ReturnFloatValue = *((float *)&TemporyForCast);
         }
         break;
         case 2:
         {
            signbit = (VariableFloatBuffer[0]>>7)&0x01;
            exponent = (VariableFloatBuffer[0]>>2)&0x1F;
            mantessa = (VariableFloatBuffer[0]   )&0x03;
            mantessa <<= 8;
            mantessa |= (VariableFloatBuffer[1]   )&0xFF;
            if (exponent == 0)
            {  //denormalized
               exponent = -127;
            }
            else if (exponent == 31)
            {  //+/-INF, NaN, depends on sign
               exponent = 128;
            }
            else
            {
               exponent -= 15;
            }

            TemporyForCast = signbit;
            TemporyForCast <<= 8;
            TemporyForCast |= ((long)exponent+127)&0xFF;
            TemporyForCast <<= 2;
            TemporyForCast |= (mantessa>>8)&0x03;
            TemporyForCast <<= 8;
            TemporyForCast |= (mantessa   )&0xFF;
            TemporyForCast <<= 8;
            TemporyForCast <<= 5;

            *ReturnFloatValue = *((float *)&TemporyForCast);
         }
         break;
         case 4:
         {
            TemporyForCast = VariableFloatBuffer[0];
            TemporyForCast <<= 8;
            TemporyForCast |= VariableFloatBuffer[1];
            TemporyForCast <<= 8;
            TemporyForCast |= VariableFloatBuffer[2];
            TemporyForCast <<= 8;
            TemporyForCast |= VariableFloatBuffer[3];

            *ReturnFloatValue = *((float *)&TemporyForCast);
         }
         break;
         default:
         {
            ReturnStatus = 1;
         }
         break;
      }
   }
   else
   { //NonZero = 0;
      TemporyForCast = 0x00000000;
      *ReturnFloatValue = *((float *)&TemporyForCast);
   }

   return ReturnStatus;
}

//make a 32 float representation.
//8 bit  = seee mmmm
//16 bit = seee eemm mmmm mmmm
//32 bit = seee eeee emmm mmmm mmm mmmmm mmmm mmmm
unsigned char Float2VariableFloat(float InputFloat, unsigned char VariableFloatBufferSize, unsigned char *FloatBuffer)
{
   unsigned long TemporyCastedFloat;
   int exponent;
   unsigned long mantessa;
   char signbit;
   unsigned char ReturnStatus;

   ReturnStatus = 1;

   TemporyCastedFloat = *((unsigned long *)&InputFloat);

   mantessa = TemporyCastedFloat&0x007FFFFF;

   exponent = (TemporyCastedFloat>>23)&0xFF;
   exponent -= 127;

   signbit = (TemporyCastedFloat>>(23+8))&0x01;

   if (TemporyCastedFloat == 0x00000000)
   {
      unsigned char cntSize;

      for (cntSize=0; cntSize<VariableFloatBufferSize; cntSize++)
      {
         FloatBuffer[cntSize] = 0x00;
      }
      ReturnStatus = 0;
   }
   else
   {
      switch (VariableFloatBufferSize)
      {
         case 1:
         {
            exponent += 3;
            if (exponent<7)
            {
               if (exponent<0)
               {
                  exponent = 0;
               }
               FloatBuffer[0] = signbit;
               FloatBuffer[0] <<= 3;
               FloatBuffer[0] |= (exponent&0x7);
               FloatBuffer[0] <<= 4;
               FloatBuffer[0] |= (mantessa>>19)&0x0F;

               ReturnStatus = 0;
            }
            else if (exponent > 6)
            {  //+/-INF (or NaN)
               exponent = 7;
               mantessa = 0;

               FloatBuffer[0] = signbit;
               FloatBuffer[0] <<= 3;
               FloatBuffer[0] |= (exponent&0x7);
               FloatBuffer[0] <<= 4;
               FloatBuffer[0] |= (mantessa>>19)&0x0F;

               ReturnStatus = 0;
            }
         }
         break;
         case 2:
         {
            exponent += 15;
            if (exponent<31)
            {
               if (exponent<0)
               {
                  exponent = 0;
               }
               FloatBuffer[0] = signbit;
               FloatBuffer[0] <<= 5;
               FloatBuffer[0] |= (exponent&0x1F);
               FloatBuffer[0] <<= 2;
               FloatBuffer[0] |= (mantessa>>21)&0x03;
               FloatBuffer[1]  = (mantessa>>13)&0xFF;

               ReturnStatus = 0;
            }
            else if (exponent > 30)
            {  //+/-INF (or NaN)
               exponent = 31;
               mantessa = 0;

               FloatBuffer[0] = signbit;
               FloatBuffer[0] <<= 3;
               FloatBuffer[0] |= (exponent&0x1F);
               FloatBuffer[0] <<= 4;
               FloatBuffer[0] |= (mantessa>>19)&0x0F;

               ReturnStatus = 0;
            }
         }
         break;
         case 4:
         {
            FloatBuffer[0] = (TemporyCastedFloat>>24)&0xFF;
            FloatBuffer[1] = (TemporyCastedFloat>>16)&0xFF;
            FloatBuffer[2] = (TemporyCastedFloat>> 8)&0xFF;
            FloatBuffer[3] = (TemporyCastedFloat    )&0xFF;

            ReturnStatus = 0;
         }
         break;
      }
   }

   return ReturnStatus;
}


#endif


