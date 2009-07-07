/*****************************************************
Project : Axum-Rack-Backplane
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
#ifndef Axum_Rack_Backplane_MambaNetH
#define Axum_Rack_Backplane_MambaNetH

#define MANUFACTERER_ID          0x001    //max 0x3FF
#define PCB_TYPE                 0x0000

#define PCB_MAJOR_VERSION        1
#define PCB_MINOR_VERSION        0

#define FIRMWARE_MAJOR_VERSION   1
#define FIRMWARE_MINOR_VERSION   0+TRANSPORTLAYER_MINOR

#define MANUFACTURER_ID          1     //D&R
#define PRODUCT_ID               12    //Axum-Rack-Backplane


#define NR_OF_STATIC_OBJECTS    (1032-1023)
#define NR_OF_OBJECTS            NR_OF_STATIC_OBJECTS+(57*32) // adding the software generated objects


#if (NR_OF_STATIC_OBJECTS > MAX_NR_OF_OBJECTS)
   #error You have defined more objects than can be stored in the EEPROM
#endif

/********************************/
/* global declarations          */
/********************************/
unsigned int ManufacturerID               = MANUFACTURER_ID;
unsigned int ProductID                    = PRODUCT_ID;
eeprom unsigned int UniqueIDPerProduct    = 9;//0x0004;
unsigned char CANServices                 = 0x00;
flash unsigned char NodeServices          = 0x00;

flash unsigned int NumberOfStaticObjects  = NR_OF_STATIC_OBJECTS;

eeprom char NodeName[32] = "Axum-Rack-Backplane\0";

unsigned char Parent[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char HardwareMinorRevision = 0x00;
unsigned char FPGAFirmwareMajorRevision = 0;
unsigned char FPGAFirmwareMinorRevision = 0;


flash DEFAULT_NODE_OBJECT_STRUCT DefaultNodeObjects =
{
   "Axum rack backplane\0",                 //Description
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
   // Description             , Services
   //                         , sensor {type, size, min, max}
   //                         , actuator {type, size, min, max, default}
   { "Clock frequency"        , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 2      , 2   }},
   { "FPGA PLL lock"          , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Enable sum 1 (slot 16)" , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Enable sum 2 (slot 17)" , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Enable sum 3 (slot 18)" , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Enable sum 4 (slot 19)" , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Clock source int/ext"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "PLL Lock"               , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FPGA function"          , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {OCTET_STRING_DATATYPE      ,  4, 0     , 255    , 0   }}
};
#else
flash OBJECT_VARIABLE_INFORMATION_STRUCT ObjectVariableInformation[1];
#endif

#endif
