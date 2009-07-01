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
#ifndef Axum_UI_CRM_MambaNetH
#define Axum_UI_CRM_MambaNetH

#define MANUFACTERER_ID          0x001    //max 0x3FF
#define PCB_TYPE                 0x0000

#define PCB_MAJOR_VERSION        1
#define PCB_MINOR_VERSION        0

#define FIRMWARE_MAJOR_VERSION   1
#define FIRMWARE_MINOR_VERSION   0

#define MANUFACTURER_ID          1     //D&R
#define PRODUCT_ID               8     //Axum-UI-CRM

#define NR_OF_STATIC_OBJECTS     (1088-1023)
#define NR_OF_OBJECTS            NR_OF_STATIC_OBJECTS

#if (NR_OF_STATIC_OBJECTS > MAX_NR_OF_OBJECTS)
   #error You have defined more objects than can be stored in the EEPROM
#endif

/********************************/
/* global declarations          */
/********************************/
unsigned int ManufacturerID               = MANUFACTURER_ID;
unsigned int ProductID                    = PRODUCT_ID;
eeprom unsigned int UniqueIDPerProduct    = 8;//0x0002;
unsigned char CANServices                 = 0x00;
flash unsigned char NodeServices          = 0x00;

flash unsigned int NumberOfStaticObjects  = NR_OF_STATIC_OBJECTS;

eeprom char NodeName[32] = "Axum-UI-CRMP\0";

unsigned char Parent[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char HardwareMinorRevision = 0x00;
unsigned char FPGAFirmwareMajorRevision = 0;
unsigned char FPGAFirmwareMinorRevision = 0;

flash DEFAULT_NODE_OBJECT_STRUCT DefaultNodeObjects =
{
   "Axum UI CRM Panel\0",                   //Description
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
   // Description             , Services,
   //                         , sensor {type, size, min, max}
   //                         , actuator {type, size, min, max, default}
   { "Switch 1 (SRC)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 2 (EQ HF)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 3 (DYN)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 4 (AUX1)"        , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 5 (GAIN)"        , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 6 (EQ HMF)"      , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 7 (DUCK)"        , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 8 (AUX2)"        , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 9 (PHASE)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 10 (EQ LMF)"     , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 11 (MONO)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 12 (AUX3)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 13 (LC)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 14 (EQ LF)"      , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 15 (PAN)"        , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 16 (AUX4)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 17 (PROG)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 18 (AUX1)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 19 (AUX3)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 20 (SUB)"        , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 21 (AUX2)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 22 (AUX4)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 23 (PROG)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 24 (SUB)"        , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 25 (AUX1)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 26 (AUX2)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 27 (AUX3)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 28 (AUX4)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 29 (CUE)"        , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 30 (COM)"        , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 31 (EXT1)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 32 (EXT2)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 33 (EXT3)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 34 (EXT4)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 35 (DIM CRM)"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 36 (MUTE CRM)"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 37 (PROG)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 38 (SUB)"        , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 39 (AUX1)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 40 (AUX2)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 41 (AUX3)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 42 (AUX4)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 43 (CUE)"        , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 44 (COM)"        , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 45 (EXT1)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 46 (EXT2)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 47 (EXT3)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 48 (EXT4)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 49 (DIM STD)"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 50 (MUTE STD)"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 51 (CUE RESET)"  , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 52 (TB ANN)"     , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 53 (TB GUEST)"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 54 (TB STUDIO)"  , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Encoder 1"              , 0x03
                              , {SIGNED_INTEGER_DATATYPE    ,  1, -128  , 127    }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Encoder 1 Switch"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "LED Bar"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {BIT_STRING_DATATYPE        ,  1, 7     , 7      , 0   }},
   { "Potential Meter 1"      , 0x03
                              , {UNSIGNED_INTEGER_DATATYPE  ,  2, 0     , 1023   }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Potential Meter 2"      , 0x03
                              , {UNSIGNED_INTEGER_DATATYPE  ,  2, 0     , 1023   }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Potential Meter 3"      , 0x03
                              , {UNSIGNED_INTEGER_DATATYPE  ,  2, 0     , 1023   }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Potential Meter 4"      , 0x03
                              , {UNSIGNED_INTEGER_DATATYPE  ,  2, 0     , 1023   }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Jumper"                 , 0x00
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Chipcard switch"        , 0x00
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Chipcard username"      , 0x00
                              , {OCTET_STRING_DATATYPE      ,  32, 0     , 127   }
                              , {OCTET_STRING_DATATYPE      ,  32, 0     , 127   , 0   }},
   { "Chipcard password"      , 0x00
                              , {OCTET_STRING_DATATYPE      ,  16, 0     , 127   }
                              , {OCTET_STRING_DATATYPE      ,  16, 0     , 127   , 0   }}
};
#else
flash OBJECT_VARIABLE_INFORMATION_STRUCT ObjectVariableInformation[1];
#endif

#endif
