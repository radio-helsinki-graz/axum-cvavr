/*****************************************************
Project : Axum-Rack-CRMDA
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
#ifndef Axum_Rack_CRMDA_MambaNetH
#define Axum_Rack_CRMDA_MambaNetH

#define MANUFACTERER_ID          0x001    //max 0x3FF
#define PCB_TYPE                 0x0000

#define PCB_MAJOR_VERSION        1
#define PCB_MINOR_VERSION        0

#define FIRMWARE_MAJOR_VERSION   1
#define FIRMWARE_MINOR_VERSION   0+TRANSPORTLAYER_MINOR

#define MANUFACTURER_ID          1     //D&R
#define PRODUCT_ID               4     //Axum-Rack-CRMDA

#define NR_OF_STATIC_OBJECTS    (1235-1023)
#define NR_OF_OBJECTS            NR_OF_STATIC_OBJECTS

#if (NR_OF_STATIC_OBJECTS > MAX_NR_OF_OBJECTS)
   #error You have defined more objects than can be stored in the EEPROM
#endif

/********************************/
/* global declarations          */
/********************************/
unsigned int ManufacturerID               = MANUFACTURER_ID;
unsigned int ProductID                    = PRODUCT_ID;
eeprom unsigned int UniqueIDPerProduct    = 10;//0x0007;
unsigned char CANServices                 = 0x00;
flash unsigned char NodeServices          = 0x00;        

flash unsigned int NumberOfStaticObjects  = NR_OF_STATIC_OBJECTS;

eeprom char NodeName[32] = "Axum-Rack-CRMDA\0";

unsigned char Parent[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char HardwareMinorRevision = 0x00;
unsigned char FPGAFirmwareMajorRevision = 0;
unsigned char FPGAFirmwareMinorRevision = 0;


flash DEFAULT_NODE_OBJECT_STRUCT DefaultNodeObjects =
{
   "Axum rack 4x stereo CRM board\0",       //Description
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
flash OBJECT_VARIABLE_INFORMATION_STRUCT ObjectVariableInformation[NR_OF_OBJECTS] =
{
   // Description             , services, 
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
   { "DAC-1-Signal"           , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "DAC-2-Signal"           , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "DAC-3-Signal"           , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "DAC-4-Signal"           , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "DAC-5-Signal"           , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "DAC-6-Signal"           , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "DAC-7-Signal"           , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "DAC-8-Signal"           , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CRM-1-Left-routing"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CRM-1-Right-routing"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CRM-2-Left-routing"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CRM-2-Right-routing"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CRM-3-Left-routing"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CRM-3-Right-routing"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CRM-4-Left-routing"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CRM-4-Right-routing"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CRM-1-Left-level"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD600, 0x4D80 , 0x0000 }},
   { "CRM-1-Right-level"      , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD600, 0x4D80 , 0x0000 }},
   { "CRM-2-Left-level"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD600, 0x4D80 , 0x0000 }},
   { "CRM-2-Right-level"      , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD600, 0x4D80 , 0x0000 }},
   { "CRM-3-Left-level"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD600, 0x4D80 , 0x0000 }},
   { "CRM-3-Right-level"      , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD600, 0x4D80 , 0x0000 }},
   { "CRM-4-Left-level"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD600, 0x4D80 , 0x0000 }},
   { "CRM-4-Right-level"      , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD600, 0x4D80 , 0x0000 }},
   { "CRM-1-Left-phase"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-1-Right-phase"      , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-2-Left-phase"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-2-Right-phase"      , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-3-Left-phase"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-3-Right-phase"      , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-4-Left-phase"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-4-Right-phase"      , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-1-Left-dim"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-1-Right-dim"        , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-2-Left-dim"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-2-Right-dim"        , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-3-Left-dim"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-3-Right-dim"        , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-4-Left-dim"         , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-4-Right-dim"        , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-1-Left-dim-level"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "CRM-1-Right-dim-level"  , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "CRM-2-Left-dim-level"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "CRM-2-Right-dim-level"  , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "CRM-3-Left-dim-level"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "CRM-3-Right-dim-level"  , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "CRM-4-Left-dim-level"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "CRM-4-Right-dim-level"  , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "CRM-1-Talkback-1"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-1-Talkback-2"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-1-Talkback-3"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-1-Talkback-4"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-1-Talkback-5"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-1-Talkback-6"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-1-Talkback-7"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-1-Talkback-8"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-1-Talkback-9"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-1-Talkback-10"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-1-Talkback-11"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-1-Talkback-12"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-1-Talkback-13"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-1-Talkback-14"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-1-Talkback-15"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-1-Talkback-16"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-2-Talkback-1"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-2-Talkback-2"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-2-Talkback-3"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-2-Talkback-4"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-2-Talkback-5"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-2-Talkback-6"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-2-Talkback-7"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-2-Talkback-8"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-2-Talkback-9"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-2-Talkback-10"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-2-Talkback-11"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-2-Talkback-12"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-2-Talkback-13"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-2-Talkback-14"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-2-Talkback-15"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-2-Talkback-16"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-3-Talkback-1"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-3-Talkback-2"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-3-Talkback-3"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-3-Talkback-4"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-3-Talkback-5"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-3-Talkback-6"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-3-Talkback-7"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-3-Talkback-8"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-3-Talkback-9"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-3-Talkback-10"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-3-Talkback-11"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-3-Talkback-12"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-3-Talkback-13"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-3-Talkback-14"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-3-Talkback-15"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-3-Talkback-16"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-4-Talkback-1"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-4-Talkback-2"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-4-Talkback-3"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-4-Talkback-4"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-4-Talkback-5"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-4-Talkback-6"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-4-Talkback-7"       , 0x00                                                                              
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-4-Talkback-8"       , 0x00                                             
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-4-Talkback-9"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-4-Talkback-10"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-4-Talkback-11"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-4-Talkback-12"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-4-Talkback-13"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-4-Talkback-14"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-4-Talkback-15"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-4-Talkback-16"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-1-Left-talkback-routing"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CRM-1-Right-talkback-routing"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CRM-2-Left-talkback-routing"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CRM-2-Right-talkback-routing"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CRM-3-Left-talkback-routing"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CRM-3-Right-talkback-routing"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CRM-4-Left-talkback-routing"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CRM-4-Right-talkback-routing"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CRM-1-Left-talkback-level"  , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CRM-1-Right-talkback-level" , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CRM-2-Left-talkback-level"  , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CRM-2-Right-talkback-level" , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CRM-3-Left-talkback-level"  , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CRM-3-Right-talkback-level" , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CRM-4-Left-talkback-level"  , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CRM-4-Right-talkback-level" , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CRM-1-Left-talkback-phase"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-1-Right-talkback-phase"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-2-Left-talkback-phase"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-2-Right-talkback-phase"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-3-Left-talkback-phase"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-3-Right-talkback-phase"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-4-Left-talkback-phase"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CRM-4-Right-talkback-phase"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-CRM-1-Left-mute"        , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-CRM-1-Right-mute"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-CRM-2-Left-mute"        , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-CRM-2-Right-mute"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-CRM-3-Left-mute"        , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-CRM-3-Right-mute"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-CRM-4-Left-mute"        , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-CRM-4-Right-mute"       , 0x00
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
