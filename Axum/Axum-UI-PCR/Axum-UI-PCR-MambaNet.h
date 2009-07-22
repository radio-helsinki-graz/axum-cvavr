/*****************************************************
Project : Axum-UI-PCR
Version :
Date    : 10-july-2007
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
#ifndef Axum_UI_PCR_MambaNetH
#define Axum_UI_PCR_MambaNetH

#define PCB_MAJOR_VERSION        1
#define PCB_MINOR_VERSION        0

#define FIRMWARE_MAJOR_VERSION   1
#define FIRMWARE_MINOR_VERSION   0+TRANSPORTLAYER_MINOR-TRANSPORTLAYER_MINOR_CORRECTION

#define MANUFACTURER_ID          1     //D&R
#define PRODUCT_ID               9     //Axum-UI-PCR

#define NR_OF_STATIC_OBJECTS     (1167-1023)
#define NR_OF_OBJECTS            NR_OF_STATIC_OBJECTS

#if (NR_OF_STATIC_OBJECTS > MAX_NR_OF_OBJECTS)
   #error You have defined more objects than can be stored in the EEPROM
#endif

/********************************/
/* global declarations          */
/********************************/
unsigned int ManufacturerID               = MANUFACTURER_ID;
unsigned int ProductID                    = PRODUCT_ID;
eeprom unsigned int UniqueIDPerProduct    = 1;
unsigned char CANServices                 = 0x00;
flash unsigned char NodeServices          = 0x00;

flash unsigned int NumberOfStaticObjects  = NR_OF_STATIC_OBJECTS;

eeprom char NodeName[32] = "Axum-UI-PCR";

unsigned char Parent[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char HardwareMinorRevision = 0x00;
unsigned char FPGAFirmwareMajorRevision = 0;
unsigned char FPGAFirmwareMinorRevision = 0;

flash DEFAULT_NODE_OBJECT_STRUCT DefaultNodeObjects =
{
   "Axum UI PC-Radio panel",              //Description
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
   { "Switch 1 (Live)"        , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 2 (VceTrk)"      , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 3 (RadixTa)"     , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 4 ()"            , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 5 ()"            , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 6 ()"            , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 7 ()"            , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Encoder 1"              , 0x03
                              , {SIGNED_INTEGER_DATATYPE    ,  1, -128  , 127    }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Encoder 1 Switch"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Encoder 2"              , 0x03
                              , {SIGNED_INTEGER_DATATYPE    ,  1, -128  , 127    }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Encoder 2 Switch"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Switch 8 (A1)"          , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 9 (B1)"          , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 10 (C1)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 11 (D1)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 12 (A2)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 13 (B2)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 14 (C2)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 15 (D2)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 16 (A3)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 17 (B3)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 18 (C3)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 19 (D3)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 20 (A4)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 21 (B4)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 22 (C4)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 23 (D4)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 24 (A5)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 25 (B5)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 26 (C5)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 27 (D5)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 28 (A6)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 29 (B6)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 30 (C6)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 31 (D6)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 32 (A7)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 33 (B7)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 34 (C7)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 35 (D7)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 36 (Stop A)"     , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 37 (Stop B)"     , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 38 (Stop C)"     , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 39 (Stop D)"     , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 40 (Live ass)"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 41 (Jingle)"     , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 42 (VceTrk)"     , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 43 ()"           , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 44 (Play list)"  , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 45 (DB Brwsr)"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 46 (DB Edit)"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 47 (Database)"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 48 (Left)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 49 (Up)"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 50 (Down)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 51 (Right)"      , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Encoder 3"              , 0x03
                              , {SIGNED_INTEGER_DATATYPE    ,  1, -128  , 127    }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Encoder 3 Switch"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Switch 52 (Shift)"      , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 53 (Insert)"     , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 54 (Home)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 55 (Assign)"     , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 56 (Ctrl)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 57 ()"           , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 58 (End)"        , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 59 (Cancel)"     , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 60 (Play)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 61 (Stop)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 62 (Rec)"        , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 1 on color"      , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 2 on color"      , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 3 on color"      , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 8 on color"      , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 9 on color"      , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 10 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 11 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 12 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 13 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 14 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 15 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 16 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 17 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 18 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 19 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 20 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 21 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 22 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 23 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 24 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 25 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 26 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 27 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 28 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 29 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 30 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 31 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 32 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 33 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 34 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 35 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 36 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 37 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 38 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 39 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 60 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 61 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 62 on color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 1 off color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 2 off color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 3 off color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 8 off color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 9 off color"     , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 10 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 11 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 12 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 13 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 14 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 15 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 16 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 17 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 18 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 19 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 20 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 21 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 22 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 23 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 24 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 25 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 26 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 27 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 28 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 29 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 30 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 31 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 32 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 33 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 34 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 35 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 36 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 37 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 38 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 39 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 60 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 61 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Switch 62 off color"    , 0x01
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }}
};
#else
flash OBJECT_VARIABLE_INFORMATION_STRUCT ObjectVariableInformation[1];
#endif

#endif
