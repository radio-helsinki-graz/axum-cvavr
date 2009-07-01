/*****************************************************
Project : Axum-UI-CRMP
Version :
Date    : 3-10-2007
Author  : Anton Prins
Company : DR Electronica Weesp b.v.
Comments:


Chip type           : AT90CAN32
Program type        : Application
Clock frequency     : 16,000000 MHz
Memory model        : Small
External SRAM size  : 0
Data Stack size     : 512
*****************************************************/
#ifndef Axum_UI_ETXBase_MambaNetH
#define Axum_UI_ETXBase_MambaNetH


#define MANUFACTERER_ID          0x001    //max 0x3FF
#define PCB_TYPE                 0x0000

#define PCB_MAJOR_VERSION        1        
#define PCB_MINOR_VERSION        0

#define FIRMWARE_MAJOR_VERSION   0
#define FIRMWARE_MINOR_VERSION   1
                         
#define MANUFACTURER_ID          1     //D&R
#define PRODUCT_ID               9     //Axum-UI-ETXBase

#define NR_OF_STATIC_OBJECTS     (1023-1023)
#define NR_OF_OBJECTS            NR_OF_STATIC_OBJECTS

#if (NR_OF_STATIC_OBJECTS > MAX_NR_OF_OBJECTS)
   #error You have defined more objects than can be stored in the EEPROM
#endif

/********************************/ 
/* global declarations          */
/********************************/ 
unsigned int ManufacturerID               = MANUFACTURER_ID;   
unsigned int ProductID                    = PRODUCT_ID;   
eeprom unsigned int UniqueIDPerProduct    = 0x0002;   
unsigned char CANServices                 = 0x01;        //Gateway/CAN Address server?
flash unsigned char NodeServices          = 0x00;        

flash unsigned int NumberOfStaticObjects  = NR_OF_STATIC_OBJECTS;

eeprom char NodeName[32] = "Axum-UI-ETXBase\0";

unsigned char Parent[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char HardwareMinorRevision = 0x00;

flash DEFAULT_NODE_OBJECT_STRUCT DefaultNodeObjects =
{
   "Axum UI ETX Base\0",                    //Description
                                          //Name is stored in EEPROM, see above
   MANUFACTURER_ID,                       //ManufacturerID
   PRODUCT_ID,                            //ProductID
//   0,                                     //UniqueMediaAccessID
   PCB_MAJOR_VERSION,                     //HardwareMajorRevision
   PCB_MINOR_VERSION,                     //HardwareMinorRevision
   FIRMWARE_MAJOR_VERSION,                //FirmwareMajorRevision
   FIRMWARE_MINOR_VERSION,                //FirmwareMinorRevision
   PROTOCOL_MAJOR_VERSION,                //ProtocolMajorRevision
   PROTOCOL_MINOR_VERSION,                //ProtocolMinorRevision
   NR_OF_OBJECTS                          //NumberOfObjects
};

#if (NR_OF_STATIC_OBJECTS != 0)
flash OBJECT_VARIABLE_INFORMATION_STRUCT ObjectVariableInformation[NR_OF_STATIC_OBJECTS] =
{
   // Description             , sensor {type, size, min, max}           
   //                         , actuator {type, size, min, max, default} 
   { "Switch 1"               , {STATE_DATATYPE             ,  1, 0     , 1      },
                                {STATE_DATATYPE             ,  1, 0     , 1      , 0   }}    //,

};    
#else
flash OBJECT_VARIABLE_INFORMATION_STRUCT ObjectVariableInformation[1];
#endif


#endif