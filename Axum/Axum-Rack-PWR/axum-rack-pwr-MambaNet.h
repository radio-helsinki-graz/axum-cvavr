/*****************************************************
Project : Axum-Rack-AD
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
#ifndef Axum_Rack_PWR_MambaNetH
#define Axum_Rack_PWR_MambaNetH

#define MANUFACTERER_ID          0x001    //max 0x3FF
#define PCB_TYPE                 0x0000

#define PCB_MAJOR_VERSION        1
#define PCB_MINOR_VERSION        0

#define FIRMWARE_MAJOR_VERSION   2
//Major version 1: initial release
//Major version 2: corrected min-max bug on object 1027 (-15V)
#define FIRMWARE_MINOR_VERSION   0+TRANSPORTLAYER_MINOR

#define MANUFACTURER_ID          1      //D&R
#define PRODUCT_ID               22     //Axum-Rack-PWR

#define NR_OF_STATIC_OBJECTS    (1029-1023)
#define NR_OF_OBJECTS            NR_OF_STATIC_OBJECTS

#if (NR_OF_STATIC_OBJECTS > MAX_NR_OF_OBJECTS)
   #error You have defined more objects than can be stored in the EEPROM
#endif

/********************************/
/* global declarations          */
/********************************/
unsigned int ManufacturerID               = MANUFACTURER_ID;
unsigned int ProductID                    = PRODUCT_ID;
eeprom unsigned int UniqueIDPerProduct    = 10;//0x0009;
unsigned char CANServices                 = 0x00;
flash unsigned char NodeServices          = 0x00;

flash unsigned int NumberOfStaticObjects  = NR_OF_STATIC_OBJECTS;

eeprom char NodeName[32] = "Axum-Rack-PWR\0";

unsigned char Parent[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char HardwareMinorRevision;
unsigned char FPGAFirmwareMajorRevision;
unsigned char FPGAFirmwareMinorRevision;

flash DEFAULT_NODE_OBJECT_STRUCT DefaultNodeObjects =
{
   "Axum rack power\0",                   //Description
                                          //Name is stored in EEPROM, see above
   MANUFACTURER_ID,                       //ManufacturerID
   PRODUCT_ID,                            //ProductID
//   0,                                     //UniqueMediaAccessID   (0=proto, 1)
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
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "+5V (pre)"              , 0x03
                              , {FLOAT_DATATYPE             ,  2, 0x0000, 0x4900 }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "+15V (pre)"             , 0x03
                              , {FLOAT_DATATYPE             ,  2, 0x0000, 0x4D00 }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "-15V (pre)"             , 0x03
                              , {FLOAT_DATATYPE             ,  2, 0xCD00, 0x0000 }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Fan speed"              , 0x03
                              , {UNSIGNED_INTEGER_DATATYPE  ,  2, 0     , 4000   }
                              , {UNSIGNED_INTEGER_DATATYPE  ,  2, 0     , 1023   , 1023}},
   { "Temperature"            , 0x03
                              , {FLOAT_DATATYPE             ,  2, 0xD100, 0x57D0 }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }}
};
#else
flash OBJECT_VARIABLE_INFORMATION_STRUCT ObjectVariableInformation[1];
#endif

#endif
