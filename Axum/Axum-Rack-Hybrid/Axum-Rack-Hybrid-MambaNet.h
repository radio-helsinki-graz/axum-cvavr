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
#define TRANSPORTLAYER_MINOR_CORRECTION 2
#define FIRMWARE_MINOR_VERSION   0+TRANSPORTLAYER_MINOR-TRANSPORTLAYER_MINOR_CORRECTION
//Local FIRMWARE_MINOR_VERSION
//0 Initial release

#define MANUFACTURER_ID          1     //D&R
#define PRODUCT_ID               29    //Axum-Rack-Hybrid

#define NR_OF_STATIC_OBJECTS    (1147-1023)
#define NR_OF_OBJECTS            NR_OF_STATIC_OBJECTS

#if (NR_OF_STATIC_OBJECTS > MAX_NR_OF_OBJECTS)
   #error You have defined more objects than can be stored in the EEPROM
#endif

/********************************/
/* global declarations          */
/********************************/
unsigned int ManufacturerID               = MANUFACTURER_ID;
unsigned int ProductID                    = PRODUCT_ID;
eeprom unsigned int UniqueIDPerProduct    = 1;//0x0007;
unsigned char CANServices                 = 0x00;
flash unsigned char NodeServices          = 0x00;        

flash unsigned int NumberOfStaticObjects  = NR_OF_STATIC_OBJECTS;

eeprom char NodeName[32] = "Rack-Hybrid";

unsigned char Parent[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char HardwareMinorRevision = 0x00;
unsigned char FPGAFirmwareMajorRevision = 0;
unsigned char FPGAFirmwareMinorRevision = 0;


flash DEFAULT_NODE_OBJECT_STRUCT DefaultNodeObjects =
{
   "4x Hybrid in/out board",              //Description
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
   { "Hybrid-in-1-Signal"     , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Hybrid-in-2-Signal"     , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Hybrid-in-3-Signal"     , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Hybrid-in-4-Signal "    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Hybrid-in-1-Routing"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Hybrid-in-2-Routing"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Hybrid-in-3-Routing"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Hybrid-in-4-Routing"    , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Hybrid-in-1-Level"      , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Hybrid-in-2-Level"      , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Hybrid-in-3-Level"      , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Hybrid-in-4-Level"      , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Hybrid-in-1-Phase"      , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-in-2-Phase"      , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-in-3-Phase"      , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-in-4-Phase"      , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-1-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Hybrid-out-2-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Hybrid-out-3-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Hybrid-out-4-Signal"    , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "Hybrid-out-1-Routing"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Hybrid-out-2-Routing"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Hybrid-out-3-Routing"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Hybrid-out-4-Routing"   , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Hybrid-out-1-Level"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Hybrid-out-2-Level"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Hybrid-out-3-Level"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Hybrid-out-4-Level"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Hybrid-out-1-Phase"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-2-Phase"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-3-Phase"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-4-Phase"     , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-1-Dim"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-2-Dim"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-3-Dim"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-4-Dim"       , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-1-Dim-level" , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "Hybrid-out-2-Dim-level" , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "Hybrid-out-3-Dim-level" , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "Hybrid-out-4-Dim-level" , 0x00
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                              , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xCD00 }},
   { "Hybrid-out-1-Talkback-1"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-1-Talkback-2"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-1-Talkback-3"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-1-Talkback-4"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-1-Talkback-5"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-1-Talkback-6"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-1-Talkback-7"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-1-Talkback-8"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-1-Talkback-9"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-1-Talkback-10"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-1-Talkback-11"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-1-Talkback-12"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-1-Talkback-13"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-1-Talkback-14"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-1-Talkback-15"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-1-Talkback-16"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-2-Talkback-1"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-2-Talkback-2"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-2-Talkback-3"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-2-Talkback-4"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-2-Talkback-5"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-2-Talkback-6"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-2-Talkback-7"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-2-Talkback-8"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-2-Talkback-9"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-2-Talkback-10"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-2-Talkback-11"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-2-Talkback-12"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-2-Talkback-13"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-2-Talkback-14"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-2-Talkback-15"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-2-Talkback-16"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-3-Talkback-1"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-3-Talkback-2"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-3-Talkback-3"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-3-Talkback-4"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-3-Talkback-5"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-3-Talkback-6"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-3-Talkback-7"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-3-Talkback-8"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-3-Talkback-9"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-3-Talkback-10"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-3-Talkback-11"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-3-Talkback-12"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-3-Talkback-13"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-3-Talkback-14"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-3-Talkback-15"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-3-Talkback-16"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-4-Talkback-1"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-4-Talkback-2"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-4-Talkback-3"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-4-Talkback-4"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-4-Talkback-5"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-4-Talkback-6"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-4-Talkback-7"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-4-Talkback-8"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-4-Talkback-9"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-4-Talkback-10"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-4-Talkback-11"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-4-Talkback-12"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-4-Talkback-13"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-4-Talkback-14"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-4-Talkback-15"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-4-Talkback-16"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-1-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Hybrid-out-2-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Hybrid-out-3-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "Hybrid-out-4-Talkback-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "Hybrid-out-1-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Hybrid-out-2-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Hybrid-out-3-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Hybrid-out-4-Talkback-level" , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "Hybrid-out-1-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-2-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-3-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Hybrid-out-4-Talkback-phase" , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-hybrid-out-1-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-hybrid-out-2-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-hybrid-out-3-Mute"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-hybrid-out-4-Mute"        , 0x00
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
