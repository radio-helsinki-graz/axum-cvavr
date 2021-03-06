/*****************************************************
Project : Axum-Rack-DD
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
#ifndef Axum_Rack_DD_SRC_MambaNetH
#define Axum_Rack_DD_SRC_MambaNetH

#define MANUFACTERER_ID          0x001    //max 0x3FF
#define PCB_TYPE                 0x0000

#define PCB_MAJOR_VERSION        1
#define PCB_MINOR_VERSION        0

#define FIRMWARE_MAJOR_VERSION   1
#define TRANSPORTLAYER_MINOR_CORRECTION 0
#define FIRMWARE_MINOR_VERSION   3+TRANSPORTLAYER_MINOR-TRANSPORTLAYER_MINOR_CORRECTION
//Local FIRMWARE_MINOR_VERSION
//1.0: Initial release
//1.1: Correct bug in Acknowlege of custom messages
//1.2: Changed name/description with 'Axum' word
//     Acknowlegde only on processed messages
//1.3: Added function to program UniqueID of is '0'

#define MANUFACTURER_ID          1     //D&R
#define PRODUCT_ID               23     //Axum-Rack-DD-SRC

#define NR_OF_STATIC_OBJECTS    (1275-1023)
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

eeprom char NodeName[32] = "Rack-DD-SRC";

unsigned char Parent[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char HardwareMinorRevision = 0x00;
unsigned char FPGAFirmwareMajorRevision = 0;
unsigned char FPGAFirmwareMinorRevision = 0;


flash DEFAULT_NODE_OBJECT_STRUCT DefaultNodeObjects =
{
   "Rack 4x stereo AES3 SRC in/out board", //Description
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
   { "Slot number"            , 0x00
                              , {UNSIGNED_INTEGER_DATATYPE  ,  1, 0     , 255    }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Input channel count"    , 0x00
                              , {UNSIGNED_INTEGER_DATATYPE  ,  1, 0     , 255    }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Output channel count"   , 0x00
                              , {UNSIGNED_INTEGER_DATATYPE  ,  1, 0     , 255    }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "GPI-1"                  , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "GPI-2"                  , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "GPI-3"                  , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "GPI-4"                  , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "GPI-5"                  , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "GPI-6"                  , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "GPI-7"                  , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "GPI-8"                  , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "GPI-1-Active-state"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 1   }},
   { "GPI-2-Active-state"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 1   }},
   { "GPI-3-Active-state"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 1   }},
   { "GPI-4-Active-state"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 1   }},
   { "GPI-5-Active-state"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 1   }},
   { "GPI-6-Active-state"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 1   }},
   { "GPI-7-Active-state"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 1   }},
   { "GPI-8-Active-state"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 1   }},
   { "GPIO-1-Mode"            , 0x00
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "GPIO-2-Mode"            , 0x00
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "GPIO-3-Mode"            , 0x00
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "GPIO-4-Mode"            , 0x00
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "GPIO-5-Mode"            , 0x00
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "GPIO-6-Mode"            , 0x00
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "GPIO-7-Mode"            , 0x00
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "GPIO-8-Mode"            , 0x00
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "GPO-1"                  , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "GPO-2"                  , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "GPO-3"                  , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "GPO-4"                  , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "GPO-5"                  , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "GPO-6"                  , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "GPO-7"                  , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "GPO-8"                  , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "GPO-1-Time"             , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {UNSIGNED_INTEGER_DATATYPE  ,  1, 0     , 255    , 50  }},
   { "GPO-2-Time"             , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {UNSIGNED_INTEGER_DATATYPE  ,  1, 0     , 255    , 50  }},
   { "GPO-3-Time"             , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {UNSIGNED_INTEGER_DATATYPE  ,  1, 0     , 255    , 50  }},
   { "GPO-4-Time"             , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {UNSIGNED_INTEGER_DATATYPE  ,  1, 0     , 255    , 50  }},
   { "GPO-5-Time"             , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {UNSIGNED_INTEGER_DATATYPE  ,  1, 0     , 255    , 50  }},
   { "GPO-6-Time"             , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {UNSIGNED_INTEGER_DATATYPE  ,  1, 0     , 255    , 50  }},
   { "GPO-7-Time"             , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {UNSIGNED_INTEGER_DATATYPE  ,  1, 0     , 255    , 50  }},
   { "GPO-8-Time"             , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {UNSIGNED_INTEGER_DATATYPE  ,  1, 0     , 255    , 50  }},
   { "GPO-1-Active-state"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 1   }},
   { "GPO-2-Active-state"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 1   }},
   { "GPO-3-Active-state"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 1   }},
   { "GPO-4-Active-state"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 1   }},
   { "GPO-5-Active-state"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 1   }},
   { "GPO-6-Active-state"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 1   }},
   { "GPO-7-Active-state"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 1   }},
   { "GPO-8-Active-state"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 1   }},
   { "IO1-LED-Orange"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "IO1-LED-Green"          , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "IO2-LED-Orange"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "IO2-LED-Green"          , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "IO3-LED-Orange"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "IO3-LED-Green"          , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "IO4-LED-Orange"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "IO4-LED-Green"          , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "IO1-LED-Orange-mode"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "IO1-LED-Green-mode"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "IO2-LED-Orange-mode"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "IO2-LED-Green-mode"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "IO3-LED-Orange-mode"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "IO3-LED-Green-mode"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "IO4-LED-Orange-mode"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "IO4-LED-Green-mode"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-in-1-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Digital-in-2-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Digital-in-3-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Digital-in-4-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Digital-in-5-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Digital-in-6-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Digital-in-7-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Digital-in-8-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Digital-in-1-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Digital-in-2-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Digital-in-3-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Digital-in-4-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Digital-in-5-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Digital-in-6-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Digital-in-7-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Digital-in-8-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Digital-in-1-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-in-2-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-in-3-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-in-4-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-in-5-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-in-6-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-in-7-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-in-8-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-in-1-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-in-2-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-in-3-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-in-4-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-in-5-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-in-6-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-in-7-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-in-8-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-1-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Digital-out-2-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Digital-out-3-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Digital-out-4-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Digital-out-5-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Digital-out-6-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Digital-out-7-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Digital-out-8-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Digital-out-1-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Digital-out-2-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Digital-out-3-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Digital-out-4-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Digital-out-5-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Digital-out-6-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Digital-out-7-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Digital-out-8-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Digital-out-1-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-out-2-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-out-3-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-out-4-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-out-5-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-out-6-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-out-7-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-out-8-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-out-1-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-2-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-3-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-4-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-5-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-6-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-7-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-8-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-1-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-2-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-3-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-4-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-5-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-6-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-7-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-8-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-1-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "Digital-out-2-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "Digital-out-3-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "Digital-out-4-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "Digital-out-5-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "Digital-out-6-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "Digital-out-7-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "Digital-out-8-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "Digital-out-1/2-Talkback-1"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-1/2-Talkback-2"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-1/2-Talkback-3"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-1/2-Talkback-4"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-1/2-Talkback-5"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-1/2-Talkback-6"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-1/2-Talkback-7"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-1/2-Talkback-8"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-1/2-Talkback-9"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-1/2-Talkback-10"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-1/2-Talkback-11"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-1/2-Talkback-12"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-1/2-Talkback-13"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-1/2-Talkback-14"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-1/2-Talkback-15"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-1/2-Talkback-16"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-3/4-Talkback-1"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-3/4-Talkback-2"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-3/4-Talkback-3"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-3/4-Talkback-4"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-3/4-Talkback-5"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-3/4-Talkback-6"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-3/4-Talkback-7"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-3/4-Talkback-8"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-3/4-Talkback-9"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-3/4-Talkback-10"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-3/4-Talkback-11"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-3/4-Talkback-12"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-3/4-Talkback-13"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-3/4-Talkback-14"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-3/4-Talkback-15"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-3/4-Talkback-16"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-5/6-Talkback-1"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-5/6-Talkback-2"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-5/6-Talkback-3"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-5/6-Talkback-4"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-5/6-Talkback-5"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-5/6-Talkback-6"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-5/6-Talkback-7"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-5/6-Talkback-8"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-5/6-Talkback-9"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-5/6-Talkback-10"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-5/6-Talkback-11"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-5/6-Talkback-12"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-5/6-Talkback-13"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-5/6-Talkback-14"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-5/6-Talkback-15"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-5/6-Talkback-16"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-7/8-Talkback-1"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-7/8-Talkback-2"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-7/8-Talkback-3"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-7/8-Talkback-4"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-7/8-Talkback-5"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-7/8-Talkback-6"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-7/8-Talkback-7"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-7/8-Talkback-8"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-7/8-Talkback-9"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-7/8-Talkback-10"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-7/8-Talkback-11"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-7/8-Talkback-12"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-7/8-Talkback-13"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-7/8-Talkback-14"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-7/8-Talkback-15"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-7/8-Talkback-16"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-1-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Digital-out-2-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Digital-out-3-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Digital-out-4-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Digital-out-5-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Digital-out-6-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Digital-out-7-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Digital-out-8-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Digital-out-1-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-out-2-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-out-3-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-out-4-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-out-5-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-out-6-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-out-7-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-out-8-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Digital-out-1-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-2-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-3-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-4-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-5-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-6-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-7-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Digital-out-8-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-digital-out-1-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-digital-out-2-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-digital-out-3-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-digital-out-4-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-digital-out-5-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-digital-out-6-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-digital-out-7-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-digital-out-8-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Receiver-1-Status-register"   , 0x00
                                    , {BIT_STRING_DATATYPE        ,  3, 24    , 24     }
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Receiver-2-Status-register"   , 0x00
                                    , {BIT_STRING_DATATYPE        ,  3, 24    , 24     }
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Receiver-3-Status-register"   , 0x00
                                    , {BIT_STRING_DATATYPE        ,  3, 24    , 24     }
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Receiver-4-Status-register"   , 0x00
                                    , {BIT_STRING_DATATYPE        ,  3, 24    , 24     }
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Transmitter-1-Control-register"  , 0x00
                                       , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                       , {BIT_STRING_DATATYPE        ,  3, 24    , 24     , 0   }},
   { "Transmitter-2-Control-register"  , 0x00
                                       , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                       , {BIT_STRING_DATATYPE        ,  3, 24    , 24     , 0   }},
   { "Transmitter-3-Control-register"  , 0x00
                                       , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                       , {BIT_STRING_DATATYPE        ,  3, 24    , 24     , 0   }},
   { "Transmitter-4-Control-register"  , 0x00
                                       , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                       , {BIT_STRING_DATATYPE        ,  3, 24    , 24     , 0   }},
   { "FPGA function"             , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {OCTET_STRING_DATATYPE      ,  3, 0     , 255    , 0   }}
};
#else
flash OBJECT_VARIABLE_INFORMATION_STRUCT ObjectVariableInformation[1];
#endif

#endif
