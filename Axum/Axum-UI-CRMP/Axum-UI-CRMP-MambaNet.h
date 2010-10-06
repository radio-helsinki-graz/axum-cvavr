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

#define FIRMWARE_MAJOR_VERSION   2
#define TRANSPORTLAYER_MINOR_CORRECTION 2
#define FIRMWARE_MINOR_VERSION   0+TRANSPORTLAYER_MINOR-TRANSPORTLAYER_MINOR_CORRECTION
//Local FIRMWARE_MINOR_VERSION
//0:  Initial release
//1:  Changed name/description with 'Axum' word
//    Acknowlegde only on processed messages

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
flash unsigned char NodeServices          = 0x00;

flash unsigned int NumberOfStaticObjects  = NR_OF_STATIC_OBJECTS;

eeprom char NodeName[32] = "UI-CRMP";

unsigned char Parent[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char HardwareMinorRevision = 0x00;
unsigned char FPGAFirmwareMajorRevision = 0;
unsigned char FPGAFirmwareMinorRevision = 0;

flash DEFAULT_NODE_OBJECT_STRUCT DefaultNodeObjects =
{
   "UI CRM Panel",                        //Description
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
   { "Switch 1"               , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 2"               , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 3"               , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 4"               , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 5"               , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 6"               , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 7"               , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 8"               , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 9"               , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 10"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 11"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 12"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 13"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 14"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 15"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 16"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 17"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 18"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 19"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 20"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 21"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 22"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 23"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 24"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 25"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 26"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 27"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 28"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 29"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 30"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 31"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 32"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 33"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 34"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 35"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 36"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 37"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 38"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 39"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 40"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 41"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 42"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 43"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 44"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 45"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 46"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 47"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 48"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 49"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 50"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 51"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 52"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 53"              , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Switch 54"              , 0x01
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
