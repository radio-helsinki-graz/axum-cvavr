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
#ifndef Axum_UI_4FBP_MambaNetH
#define Axum_UI_4FBP_MambaNetH

#define MANUFACTERER_ID          0x001    //max 0x3FF
#define PCB_TYPE                 0x0000

#define PCB_MAJOR_VERSION        1
#define PCB_MINOR_VERSION        0

#define FIRMWARE_MAJOR_VERSION   1
#define FIRMWARE_MINOR_VERSION   0+TRANSPORTLAYER_MINOR-TRANSPORTLAYER_MINOR_CORRECTION

#define MANUFACTURER_ID          1     //D&R
#define PRODUCT_ID               7     //Axum-UI-4FBP

#define NR_OF_STATIC_OBJECTS     (1143-1023)
#define NR_OF_OBJECTS            NR_OF_STATIC_OBJECTS

#if (NR_OF_STATIC_OBJECTS > MAX_NR_OF_OBJECTS)
   #error You have defined more objects than can be stored in the EEPROM
#endif

/********************************/
/* global declarations          */
/********************************/
unsigned int ManufacturerID               = MANUFACTURER_ID;
unsigned int ProductID                    = PRODUCT_ID;
eeprom unsigned int UniqueIDPerProduct    = 24;//0x0005;
unsigned char CANServices                 = 0x00;
flash unsigned char NodeServices          = 0x00;

flash unsigned int NumberOfStaticObjects  = NR_OF_STATIC_OBJECTS;

eeprom char NodeName[32] = "Axum-UI-4FBP\0";

unsigned char Parent[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char HardwareMinorRevision = 0x00;
unsigned char FPGAFirmwareMajorRevision = 0;
unsigned char FPGAFirmwareMinorRevision = 0;

flash DEFAULT_NODE_OBJECT_STRUCT DefaultNodeObjects =
{
   "Axum UI 4 Fader Broadcast Panel\0",     //Description
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
   { "Display 1 Line 1"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {OCTET_STRING_DATATYPE      ,  8, 0     , 127    , 0   }},
   { "Display 2 Line 1"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {OCTET_STRING_DATATYPE      ,  8, 0     , 127    , 0   }},
   { "Display 3 Line 1"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {OCTET_STRING_DATATYPE      ,  8, 0     , 127    , 0   }},
   { "Display 4 Line 1"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {OCTET_STRING_DATATYPE      ,  8, 0     , 127    , 0   }},
   { "Display 1 Line 2"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {OCTET_STRING_DATATYPE      ,  8, 0     , 127    , 0   }},
   { "Display 2 Line 2"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {OCTET_STRING_DATATYPE      ,  8, 0     , 127    , 0   }},
   { "Display 3 Line 2"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {OCTET_STRING_DATATYPE      ,  8, 0     , 127    , 0   }},
   { "Display 4 Line 2"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {OCTET_STRING_DATATYPE      ,  8, 0     , 127    , 0   }},
   { "Encoder 1"              , 0x01
                              , {SIGNED_INTEGER_DATATYPE    ,  1, -128  , 127    }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Encoder 2"              , 0x01
                              , {SIGNED_INTEGER_DATATYPE    ,  1, -128  , 127    }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Encoder 3"              , 0x01
                              , {SIGNED_INTEGER_DATATYPE    ,  1, -128  , 127    }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Encoder 4"              , 0x01
                              , {SIGNED_INTEGER_DATATYPE    ,  1, -128  , 127    }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Encoder 1 Switch"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Encoder 2 Switch"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Encoder 3 Switch"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Encoder 4 Switch"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Switch 1.1 (INPUT A)"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 2.1 (INPUT A)"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 3.1 (INPUT A)"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 4.1 (INPUT A)"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 1.2 (INPUT B)"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 2.2 (INPUT B)"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 3.2 (INPUT B)"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 4.2 (INPUT B)"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 1.3 (PROG)"      , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 2.3 (PROG)"      , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 3.3 (PROG)"      , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 4.3 (PROG)"      , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 1.4 (SUB)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 2.4 (SUB)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 3.4 (SUB)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 4.4 (SUB)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 1.5 (CUE)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 2.5 (CUE)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 3.5 (CUE)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 4.5 (CUE)"       , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 1.6 (ON)"        , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 2.6 (ON)"        , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 3.6 (ON)"        , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 4.6 (ON)"        , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 1.7 (START)"     , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 2.7 (START)"     , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 3.7 (START)"     , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 4.7 (START)"     , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 1.8 (STOP)"      , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 2.8 (STOP)"      , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 3.8 (STOP)"      , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 4.8 (STOP)"      , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 1.1 (Peak)"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 2.1 (Peak)"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 3.1 (Peak)"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 4.1 (Peak)"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 1.2 (Signal)"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 2.2 (Signal)"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 3.2 (Signal)"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 4.2 (Signal)"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 1.3 (EQ)"           , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 2.3 (EQ)"           , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 3.3 (EQ)"           , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 4.3 (EQ)"           , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 1.4 (DYN)"          , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 2.4 (DYN)"          , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 3.4 (DYN)"          , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 4.4 (DYN)"          , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 1.5 (AUX1)"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 2.5 (AUX1)"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 3.5 (AUX1)"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 4.5 (AUX1)"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 1.6 (AUX2)"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 2.6 (AUX2)"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 3.6 (AUX2)"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 4.6 (AUX2)"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 1.7 (AUX3)"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 2.7 (AUX3)"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 3.7 (AUX3)"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 4.7 (AUX3)"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 1.8 (AUX4)"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 2.8 (AUX4)"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 3.8 (AUX4)"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 4.8 (AUX4)"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Fader 1"                , 0x03
                              , {UNSIGNED_INTEGER_DATATYPE  ,  2, 0     , 1023   }
                              , {UNSIGNED_INTEGER_DATATYPE  ,  2, 0     , 1023   , 0   }},
   { "Fader 2"                , 0x03
                              , {UNSIGNED_INTEGER_DATATYPE  ,  2, 0     , 1023   }
                              , {UNSIGNED_INTEGER_DATATYPE  ,  2, 0     , 1023   , 0   }},
   { "Fader 3"                , 0x03
                              , {UNSIGNED_INTEGER_DATATYPE  ,  2, 0     , 1023   }
                              , {UNSIGNED_INTEGER_DATATYPE  ,  2, 0     , 1023   , 0   }},
   { "Fader 4"                , 0x03
                              , {UNSIGNED_INTEGER_DATATYPE  ,  2, 0     , 1023   }
                              , {UNSIGNED_INTEGER_DATATYPE  ,  2, 0     , 1023   , 0   }},
   { "Fader 1 touch"          , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Fader 2 touch"          , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Fader 3 touch"          , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Fader 4 touch"          , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Switch 1.5 on color"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Switch 2.5 on color"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Switch 3.5 on color"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Switch 4.5 on color"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Switch 1.6 on color"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Switch 2.6 on color"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Switch 3.6 on color"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Switch 4.6 on color"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Switch 1.7 on color"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Switch 2.7 on color"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Switch 3.7 on color"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Switch 4.7 on color"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Switch 1.8 on color"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Switch 2.8 on color"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Switch 3.8 on color"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Switch 4.8 on color"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Switch 1.5 off color"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 0   }},
   { "Switch 2.5 off color"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 0   }},
   { "Switch 3.5 off color"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 0   }},
   { "Switch 4.5 off color"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 0   }},
   { "Switch 1.6 off color"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 0   }},
   { "Switch 2.6 off color"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 0   }},
   { "Switch 3.6 off color"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 0   }},
   { "Switch 4.6 off color"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 0   }},
   { "Switch 1.7 off color"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 0   }},
   { "Switch 2.7 off color"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 0   }},
   { "Switch 3.7 off color"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 0   }},
   { "Switch 4.7 off color"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 0   }},
   { "Switch 1.8 off color"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 0   }},
   { "Switch 2.8 off color"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 0   }},
   { "Switch 3.8 off color"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 0   }},
   { "Switch 4.8 off color"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 0   }}
};
#else
flash OBJECT_VARIABLE_INFORMATION_STRUCT ObjectVariableInformation[1];
#endif

#endif
