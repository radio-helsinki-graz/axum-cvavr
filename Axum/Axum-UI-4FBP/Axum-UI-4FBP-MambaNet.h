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

#define FIRMWARE_MAJOR_VERSION   2

#define TRANSPORTLAYER_MINOR_CORRECTION 2
#define FIRMWARE_MINOR_VERSION   2+TRANSPORTLAYER_MINOR-TRANSPORTLAYER_MINOR_CORRECTION
//Local FIRMWARE_MINOR_VERSION
//1.1: On/Off color set direct
//1.2: Optimized setting of LEDs
//1.3: Changed name/description with 'Axum' word
//    Acknowlegde only on processed messages
//2.0: node names changed
//2.1: Faders working without touch
//2.2:  Added function to program UniqueID of is '0'

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
eeprom unsigned int UniqueIDPerProduct    = 0;
flash unsigned char NodeServices          = 0x00;

flash unsigned int NumberOfStaticObjects  = NR_OF_STATIC_OBJECTS;

eeprom char NodeName[32] = "UI-4FBP";

unsigned char Parent[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char HardwareMinorRevision = 0x00;
unsigned char FPGAFirmwareMajorRevision = 0;
unsigned char FPGAFirmwareMinorRevision = 0;

flash DEFAULT_NODE_OBJECT_STRUCT DefaultNodeObjects =
{
   "UI 4 Fader Broadcast Panel",          //Description
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
   { "Switch 1.1"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 2.1"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 3.1"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 4.1"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 1.2"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 2.2"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 3.2"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 4.2"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 1.3"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 2.3"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 3.3"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 4.3"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 1.4"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 2.4"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 3.4"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 4.4"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 1.5"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 2.5"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 3.5"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 4.5"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 1.6"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 2.6"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 3.6"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 4.6"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 1.7"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 2.7"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 3.7"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 4.7"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 1.8"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 2.8"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 3.8"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 4.8"             , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 1.1"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 2.1"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 3.1"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 4.1"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 1.2"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 2.2"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 3.2"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 4.2"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 1.3"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 2.3"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 3.3"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 4.3"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 1.4"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 2.4"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 3.4"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 4.4"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 1.5"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 2.5"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 3.5"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 4.5"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 1.6"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 2.6"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 3.6"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 4.6"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 1.7"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 2.7"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 3.7"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 4.7"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 1.8"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 2.8"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 3.8"                , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "LED 4.8"                , 0x00
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
