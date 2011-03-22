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
#ifndef Axum_Rack_MICAD_MambaNetH
#define Axum_Rack_MICAD_MambaNetH

#define MANUFACTERER_ID          0x001    //max 0x3FF
#define PCB_TYPE                 0x0000

#define PCB_MAJOR_VERSION        1
#define PCB_MINOR_VERSION        0

#define FIRMWARE_MAJOR_VERSION   1
#define TRANSPORTLAYER_MINOR_CORRECTION 0
#define FIRMWARE_MINOR_VERSION   2+TRANSPORTLAYER_MINOR-TRANSPORTLAYER_MINOR_CORRECTION
//Local FIRMWARE_MINOR_VERSION
//1.0:  Initial release
//1.1:  Changed name/description with 'Axum' word
//    Acknowlegde only on processed messages
//1.2:  Added function to program UniqueID of is '0'

#define MANUFACTURER_ID          1     //D&R
#define PRODUCT_ID               2     //Axum-Rack-MICAD

#define NR_OF_STATIC_OBJECTS    (1123-1023)
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

eeprom char NodeName[32] = "Rack-MICAD";

unsigned char Parent[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char HardwareMinorRevision = 0x00;
unsigned char FPGAFirmwareMajorRevision = 0;
unsigned char FPGAFirmwareMinorRevision = 0;

flash DEFAULT_NODE_OBJECT_STRUCT DefaultNodeObjects =
{
   "Rack 4x MIC preamp board",            //Description
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
   { "MIC-1-Preamp-clip"      , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "MIC-2-Preamp-clip"      , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "MIC-3-Preamp-clip"      , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "MIC-4-Preamp-clip"      , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADC-1-Overload"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADC-2-Overload"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADC-3-Overload"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADC-4-Overload"         , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADC-1-Signal"           , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADC-2-Signal"           , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADC-3-Signal"           , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADC-4-Signal"           , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "MIC-1-Phantom"          , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "MIC-2-Phantom"          , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "MIC-3-Phantom"          , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "MIC-4-Phantom"          , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "MIC-1-Pad"              , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "MIC-2-Pad"              , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "MIC-3-Pad"              , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "MIC-4-Pad"              , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "MIC-1-Gain"             , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0x4D00, 0x54B0 , 0x4D00 }},
   { "MIC-2-Gain"             , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0x4D00, 0x54B0 , 0x4D00 }},
   { "MIC-3-Gain"             , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0x4D00, 0x54B0 , 0x4D00 }},
   { "MIC-4-Gain"             , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0x4D00, 0x54B0 , 0x4D00 }},
   { "Input-1-Routing"        , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Input-2-Routing"        , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Input-3-Routing"        , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Input-4-Routing"        , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Input-1-Phase"          , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Input-2-Phase"          , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Input-3-Phase"          , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Input-4-Phase"          , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FPGA function"             , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {OCTET_STRING_DATATYPE      ,  3, 0     , 255    , 0   }}
};
#else
flash OBJECT_VARIABLE_INFORMATION_STRUCT ObjectVariableInformation[1];
#endif

#endif
