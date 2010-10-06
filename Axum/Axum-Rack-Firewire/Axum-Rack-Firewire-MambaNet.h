/*****************************************************
Project : Axum-Rack-FW
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
#ifndef Axum_Rack_FW_MambaNetH
#define Axum_Rack_FW_MambaNetH

#define MANUFACTERER_ID          0x001    //max 0x3FF
#define PCB_TYPE                 0x0000

#define PCB_MAJOR_VERSION        1
#define PCB_MINOR_VERSION        0

#define TRANSPORTLAYER_MINOR_CORRECTION 2
#define FIRMWARE_MAJOR_VERSION   1
#define FIRMWARE_MINOR_VERSION   0+TRANSPORTLAYER_MINOR-TRANSPORTLAYER_MINOR_CORRECTION
//Local FIRMWARE_MINOR_VERSION
//0:  Initial release

#define MANUFACTURER_ID          1     //D&R
#define PRODUCT_ID               30     //Axum-Rack-FW

#define NR_OF_STATIC_OBJECTS    (1379-1023)
#define NR_OF_OBJECTS            NR_OF_STATIC_OBJECTS

#if (NR_OF_STATIC_OBJECTS > MAX_NR_OF_OBJECTS)
   #error You have defined more objects than can be stored in the EEPROM
#endif

/********************************/
/* global declarations          */
/********************************/
unsigned int ManufacturerID               = MANUFACTURER_ID;
unsigned int ProductID                    = PRODUCT_ID;
eeprom unsigned int UniqueIDPerProduct    = 0x0003;
flash unsigned char NodeServices          = 0x00;

flash unsigned int NumberOfStaticObjects  = NR_OF_STATIC_OBJECTS;

eeprom char NodeName[32] = "Rack-FW";

unsigned char Parent[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char HardwareMinorRevision = 0x00;
unsigned char FPGAFirmwareMajorRevision = 0;
unsigned char FPGAFirmwareMinorRevision = 0;


flash DEFAULT_NODE_OBJECT_STRUCT DefaultNodeObjects =
{
   "Rack firewire in/out board",          //Description
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
   { "FW-in-1-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-in-2-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-in-3-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-in-4-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-in-5-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-in-6-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-in-7-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-in-8-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-in-9-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-in-10-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-in-11-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-in-12-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-in-13-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-in-14-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-in-15-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-in-16-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-in-1-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-in-2-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-in-3-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-in-4-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-in-5-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-in-6-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-in-7-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-in-8-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-in-9-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-in-10-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-in-11-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-in-12-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-in-13-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-in-14-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-in-15-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-in-16-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-in-1-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-in-2-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-in-3-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-in-4-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-in-5-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-in-6-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-in-7-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-in-8-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-in-9-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-in-10-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-in-11-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-in-12-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-in-13-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-in-14-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-in-15-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-in-16-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-in-1-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-in-2-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-in-3-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-in-4-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-in-5-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-in-6-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-in-7-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-in-8-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-in-9-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-in-10-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-in-11-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-in-12-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-in-13-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-in-14-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-in-15-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-in-16-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-1-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-out-2-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-out-3-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-out-4-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-out-5-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-out-6-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-out-7-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-out-8-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-out-9-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-out-10-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-out-11-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-out-12-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-out-13-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-out-14-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-out-15-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-out-16-Signal"      , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "FW-out-1-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-out-2-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-out-3-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-out-4-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-out-5-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-out-6-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-out-7-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-out-8-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-out-9-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-out-10-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-out-11-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-out-12-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-out-13-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-out-14-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-out-15-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-out-16-Routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-out-1-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-2-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-3-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-4-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-5-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-6-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-7-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-8-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-9-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-10-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-11-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-12-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-13-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-14-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-15-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-16-Level"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-1-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-2-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-3-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-4-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-5-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-6-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-7-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-8-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-9-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-10-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-11-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-12-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-13-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-14-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-15-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-16-Phase"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-1-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-2-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-3-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-4-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-5-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-6-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-7-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-8-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-9-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-10-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-11-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-12-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-13-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-14-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-15-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-16-Dim"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-1-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-out-2-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-out-3-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-out-4-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-out-5-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-out-6-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-out-7-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-out-8-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-out-9-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-out-10-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-out-11-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-out-12-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-out-13-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-out-14-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-out-15-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-out-16-Dim-level"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "FW-out-1/2-Talkback-1"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-1/2-Talkback-2"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-1/2-Talkback-3"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-1/2-Talkback-4"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-1/2-Talkback-5"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-1/2-Talkback-6"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-1/2-Talkback-7"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-1/2-Talkback-8"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-1/2-Talkback-9"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-1/2-Talkback-10"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-1/2-Talkback-11"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-1/2-Talkback-12"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-1/2-Talkback-13"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-1/2-Talkback-14"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-1/2-Talkback-15"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-1/2-Talkback-16"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-3/4-Talkback-1"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-3/4-Talkback-2"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-3/4-Talkback-3"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-3/4-Talkback-4"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-3/4-Talkback-5"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-3/4-Talkback-6"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-3/4-Talkback-7"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-3/4-Talkback-8"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-3/4-Talkback-9"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-3/4-Talkback-10"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-3/4-Talkback-11"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-3/4-Talkback-12"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-3/4-Talkback-13"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-3/4-Talkback-14"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-3/4-Talkback-15"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-3/4-Talkback-16"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-5/6-Talkback-1"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-5/6-Talkback-2"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-5/6-Talkback-3"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-5/6-Talkback-4"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-5/6-Talkback-5"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-5/6-Talkback-6"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-5/6-Talkback-7"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-5/6-Talkback-8"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-5/6-Talkback-9"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-5/6-Talkback-10"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-5/6-Talkback-11"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-5/6-Talkback-12"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-5/6-Talkback-13"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-5/6-Talkback-14"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-5/6-Talkback-15"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-5/6-Talkback-16"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-7/8-Talkback-1"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-7/8-Talkback-2"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-7/8-Talkback-3"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-7/8-Talkback-4"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-7/8-Talkback-5"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-7/8-Talkback-6"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-7/8-Talkback-7"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-7/8-Talkback-8"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-7/8-Talkback-9"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-7/8-Talkback-10"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-7/8-Talkback-11"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-7/8-Talkback-12"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-7/8-Talkback-13"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-7/8-Talkback-14"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-7/8-Talkback-15"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-7/8-Talkback-16"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-9/10-Talkback-1"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-9/10-Talkback-2"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-9/10-Talkback-3"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-9/10-Talkback-4"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-9/10-Talkback-5"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-9/10-Talkback-6"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-9/10-Talkback-7"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-9/10-Talkback-8"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-9/10-Talkback-9"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-9/10-Talkback-10"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-9/10-Talkback-11"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-9/10-Talkback-12"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-9/10-Talkback-13"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-9/10-Talkback-14"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-9/10-Talkback-15"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-9/10-Talkback-16"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-11/12-Talkback-1"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-11/12-Talkback-2"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-11/12-Talkback-3"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-11/12-Talkback-4"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-11/12-Talkback-5"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-11/12-Talkback-6"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-11/12-Talkback-7"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-11/12-Talkback-8"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-11/12-Talkback-9"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-11/12-Talkback-10"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-11/12-Talkback-11"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-11/12-Talkback-12"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-11/12-Talkback-13"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-11/12-Talkback-14"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-11/12-Talkback-15"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-11/12-Talkback-16"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-13/14-Talkback-1"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-13/14-Talkback-2"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-13/14-Talkback-3"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-13/14-Talkback-4"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-13/14-Talkback-5"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-13/14-Talkback-6"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-13/14-Talkback-7"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-13/14-Talkback-8"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-13/14-Talkback-9"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-13/14-Talkback-10"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-13/14-Talkback-11"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-13/14-Talkback-12"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-13/14-Talkback-13"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-13/14-Talkback-14"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-13/14-Talkback-15"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-13/14-Talkback-16"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-15/16-Talkback-1"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-15/16-Talkback-2"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-15/16-Talkback-3"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-15/16-Talkback-4"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-15/16-Talkback-5"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-15/16-Talkback-6"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-15/16-Talkback-7"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-15/16-Talkback-8"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-15/16-Talkback-9"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-15/16-Talkback-10"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-15/16-Talkback-11"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-15/16-Talkback-12"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-15/16-Talkback-13"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-15/16-Talkback-14"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-15/16-Talkback-15"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-15/16-Talkback-16"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-1-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-out-2-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-out-3-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-out-4-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-out-5-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-out-6-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-out-7-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-out-8-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-out-9-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-out-10-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-out-11-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-out-12-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-out-13-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-out-14-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-out-15-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "FW-out-16-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "FW-out-1-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-2-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-3-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-4-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-5-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-6-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-7-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-8-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-9-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-10-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-11-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-12-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-13-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-14-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-15-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-16-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "FW-out-1-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-2-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-3-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-4-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-5-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-6-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-7-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-8-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-9-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-10-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-11-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-12-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-13-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-14-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-15-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "FW-out-16-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-FW-out-1-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-FW-out-2-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-FW-out-3-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-FW-out-4-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-FW-out-5-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-FW-out-6-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-FW-out-7-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-FW-out-8-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-FW-out-9-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-FW-out-10-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-FW-out-11-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-FW-out-12-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-FW-out-13-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-FW-out-14-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-FW-out-15-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-FW-out-16-Mute"        , 0x00
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
