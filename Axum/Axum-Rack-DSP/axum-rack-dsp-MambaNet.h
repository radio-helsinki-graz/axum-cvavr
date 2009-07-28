/*****************************************************
Project : Axum-Rack-DSP
Version :
Date    : 3-10-2008
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
#ifndef Axum_Rack_DSP_MambaNetH
#define Axum_Rack_DSP_MambaNetH

#define MANUFACTERER_ID          0x001    //max 0x3FF
#define PCB_TYPE                 0x0000

#define PCB_MAJOR_VERSION        1
#define PCB_MINOR_VERSION        0

#define FIRMWARE_MAJOR_VERSION   2
#define FIRMWARE_MINOR_VERSION   0+TRANSPORTLAYER_MINOR-TRANSPORTLAYER_MINOR_CORRECTION

#define MANUFACTURER_ID          1      //D&R
#define PRODUCT_ID               20     //Axum-Rack-DSP

#define NR_OF_STATIC_OBJECTS    (1024-1023)
#define NR_OF_OBJECTS            NR_OF_STATIC_OBJECTS

#if (NR_OF_STATIC_OBJECTS > MAX_NR_OF_OBJECTS)
   #error You have defined more objects than can be stored in the EEPROM
#endif

/********************************/
/* global declarations          */
/********************************/
unsigned int ManufacturerID               = MANUFACTURER_ID;
unsigned int ProductID                    = PRODUCT_ID;
eeprom unsigned int UniqueIDPerProduct    = 9;//0x0007;
unsigned char CANServices                 = 0x00;
flash unsigned char NodeServices          = 0x00;

flash unsigned int NumberOfStaticObjects  = NR_OF_STATIC_OBJECTS;

eeprom char NodeName[32] = "Axum-Rack-DSP\0";

unsigned char Parent[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char HardwareMinorRevision = 0x00;
unsigned char FPGAFirmwareMajorRevision = 0;
unsigned char FPGAFirmwareMinorRevision = 0;

flash DEFAULT_NODE_OBJECT_STRUCT DefaultNodeObjects =
{
   "Axum rack DSP - 4x C6727B\0",         //Description
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

#if (NR_OF_OBJECTS != 0)
flash OBJECT_VARIABLE_INFORMATION_STRUCT ObjectVariableInformation[NR_OF_STATIC_OBJECTS] =
{
   // Description             , Services
   //                         , sensor {type, size, min, max}
   //                         , actuator {type, size, min, max, default}
   { "Slot number"            , 0x00
                              , {UNSIGNED_INTEGER_DATATYPE  ,  1, 0     , 255    }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }}
};
#else
flash OBJECT_VARIABLE_INFORMATION_STRUCT ObjectVariableInformation[1];
#endif

#endif
