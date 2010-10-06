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
#ifndef Axum_Rack_ADAT_MambaNetH
#define Axum_Rack_ADAT_MambaNetH

#define MANUFACTERER_ID          0x001    //max 0x3FF
#define PCB_TYPE                 0x0000

#define PCB_MAJOR_VERSION        1
#define PCB_MINOR_VERSION        0

#define FIRMWARE_MAJOR_VERSION   1
#define FIRMWARE_MINOR_VERSION   0+TRANSPORTLAYER_MINOR-TRANSPORTLAYER_MINOR_CORRECTION
//Local FIRMWARE_MINOR_VERSION
//0:  Initial release

#define MANUFACTURER_ID          1     //D&R
#define PRODUCT_ID               5     //Axum-Rack-ADAT

#define NR_OF_STATIC_OBJECTS    (1270-1023)
#define NR_OF_OBJECTS            NR_OF_STATIC_OBJECTS

#if (NR_OF_STATIC_OBJECTS > MAX_NR_OF_OBJECTS)
   #error You have defined more objects than can be stored in the EEPROM
#endif

/********************************/
/* global declarations          */
/********************************/
unsigned int ManufacturerID               = MANUFACTURER_ID;
unsigned int ProductID                    = PRODUCT_ID;
eeprom unsigned int UniqueIDPerProduct    = 0x0001;
flash unsigned char NodeServices          = 0x00;

flash unsigned int NumberOfStaticObjects  = NR_OF_STATIC_OBJECTS;

eeprom char NodeName[32] = "Rack-ADAT";

unsigned char Parent[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char HardwareMinorRevision = 0x00;
unsigned char FPGAFirmwareMajorRevision = 0;
unsigned char FPGAFirmwareMinorRevision = 0;


flash DEFAULT_NODE_OBJECT_STRUCT DefaultNodeObjects =
{
   "Rack 2x ADAT in/out board\0",         //Description
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
   { "FPGA major revision"    , 0x00
                              , {UNSIGNED_INTEGER_DATATYPE  ,  1, 0     , 255    }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FPGA minor revision"    , 0x00
                              , {UNSIGNED_INTEGER_DATATYPE  ,  1, 0     , 255    }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-1-in-LED-red/green"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-in-LED-red/green"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-LED-red/green"  , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-LED-red/green"  , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-in-LED-red/green-mode" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 4      , 0   }},
   { "ADAT-2-in-LED-red/green-mode" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 4      , 0   }},
   { "ADAT-1-out-LED-red/green-mode", 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 4      , 0   }},
   { "ADAT-2-out-LED-red/green-mode", 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 4      , 0   }},
   { "ADAT-1-input-status"       , 0x00
                                 , {BIT_STRING_DATATYPE        ,  1, 0     , 2      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-2-input-status"       , 0x00
                                 , {BIT_STRING_DATATYPE        ,  1, 0     , 2      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-1-in-1-Signal"        , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-1-in-2-Signal"        , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-1-in-3-Signal"        , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-1-in-4-Signal"        , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-1-in-5-Signal"        , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-1-in-6-Signal"        , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-1-in-7-Signal"        , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-1-in-8-Signal"        , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-2-in-1-Signal"        , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-2-in-2-Signal"        , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-2-in-3-Signal"        , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-2-in-4-Signal"        , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-2-in-5-Signal"        , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-2-in-6-Signal"        , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-2-in-7-Signal"        , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-2-in-8-Signal"        , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-1-in-1-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-1-in-2-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-1-in-3-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-1-in-4-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-1-in-5-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-1-in-6-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-1-in-7-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-1-in-8-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-2-in-1-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-2-in-2-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-2-in-3-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-2-in-4-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-2-in-5-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-2-in-6-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-2-in-7-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-2-in-8-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-1-in-1-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-in-2-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-in-3-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-in-4-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-in-5-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-in-6-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-in-7-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-in-8-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-in-1-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-in-2-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-in-3-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-in-4-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-in-5-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-in-6-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-in-7-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-in-8-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-in-1-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-in-2-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-in-3-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-in-4-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-in-5-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-in-6-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-in-7-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-in-8-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-in-1-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-in-2-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-in-3-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-in-4-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-in-5-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-in-6-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-in-7-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-in-8-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-1-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-1-out-2-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-1-out-3-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-1-out-4-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-1-out-5-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-1-out-6-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-1-out-7-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-1-out-8-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-2-out-1-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-2-out-2-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-2-out-3-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-2-out-4-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-2-out-5-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-2-out-6-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-2-out-7-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-2-out-8-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "ADAT-1-out-1-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-1-out-2-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-1-out-3-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-1-out-4-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-1-out-5-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-1-out-6-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-1-out-7-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-1-out-8-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-2-out-1-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-2-out-2-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-2-out-3-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-2-out-4-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-2-out-5-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-2-out-6-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-2-out-7-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-2-out-8-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-1-out-1-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-out-2-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-out-3-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-out-4-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-out-5-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-out-6-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-out-7-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-out-8-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-out-1-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-out-2-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-out-3-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-out-4-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-out-5-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-out-6-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-out-7-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-out-1-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-2-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-3-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-4-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-5-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-6-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-7-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-8-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-1-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-2-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-3-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-4-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-5-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-6-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-7-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-8-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-1-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-2-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-3-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-4-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-5-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-6-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-7-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-8-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-1-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-2-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-3-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-4-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-5-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-6-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-7-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-8-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-1-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "ADAT-1-out-2-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "ADAT-1-out-3-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "ADAT-1-out-4-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "ADAT-1-out-5-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "ADAT-1-out-6-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "ADAT-1-out-7-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "ADAT-1-out-8-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "ADAT-2-out-1-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "ADAT-2-out-2-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "ADAT-2-out-3-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "ADAT-2-out-4-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "ADAT-2-out-5-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "ADAT-2-out-6-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "ADAT-2-out-7-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "ADAT-2-out-8-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "ADAT-1-out-1/2-Talkback"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 16     , 0   }},
   { "ADAT-1-out-3/4-Talkback"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 16     , 0   }},
   { "ADAT-1-out-5/6-Talkback"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 16     , 0   }},
   { "ADAT-1-out-7/8-Talkback"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 16     , 0   }},
   { "ADAT-2-out-1/2-Talkback"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 16     , 0   }},
   { "ADAT-2-out-3/4-Talkback"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 16     , 0   }},
   { "ADAT-2-out-5/6-Talkback"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 16     , 0   }},
   { "ADAT-2-out-7/8-Talkback"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 16     , 0   }},
   { "ADAT-1-out-1-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-1-out-2-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-1-out-3-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-1-out-4-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-1-out-5-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-1-out-6-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-1-out-7-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-1-out-8-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-2-out-1-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-2-out-2-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-2-out-3-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-2-out-4-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-2-out-5-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-2-out-6-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-2-out-7-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "ADAT-2-out-8-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "ADAT-1-out-1-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-out-2-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-out-3-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-out-4-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-out-5-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-out-6-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-out-7-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-out-8-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-out-1-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-out-2-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-out-3-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-out-4-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-out-5-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-out-6-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-out-7-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-2-out-8-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "ADAT-1-out-1-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-2-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-3-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-4-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-5-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-6-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-7-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-1-out-8-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-1-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-2-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-3-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-4-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-5-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-6-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-7-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "ADAT-2-out-8-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-ADAT-1-out-1-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-ADAT-1-out-2-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-ADAT-1-out-3-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-ADAT-1-out-4-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-ADAT-1-out-5-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-ADAT-1-out-6-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-ADAT-1-out-7-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-ADAT-1-out-8-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-ADAT-2-out-1-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-ADAT-2-out-2-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-ADAT-2-out-3-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-ADAT-2-out-4-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-ADAT-2-out-5-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-ADAT-2-out-6-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-ADAT-2-out-7-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-ADAT-2-out-8-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FPGA function"                , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {OCTET_STRING_DATATYPE      ,  3, 0     , 255    , 0   }}
};
#else
flash OBJECT_VARIABLE_INFORMATION_STRUCT ObjectVariableInformation[1];
#endif

#endif
