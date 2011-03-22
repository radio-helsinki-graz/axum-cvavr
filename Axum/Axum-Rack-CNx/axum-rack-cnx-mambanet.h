/*****************************************************
Project : Axum-Rack-CNx
Version :
Date    : 7-12-2009
Author  : Anton Prins
Company : DR Electronica Weesp b.v.
Comments:


Chip type           : AT90CAN64
Program type        : Application
Clock frequency     : 16,000000 MHz
Memory model        : Small
External SRAM size  : 0
Data Stack size     : 512
*****************************************************/
#ifndef Axum_Rack_CNx_MambaNetH
#define Axum_Rack_CNx_MambaNetH

#define COBRANET_16X16

#define MANUFACTERER_ID          0x001    //max 0x3FF
#define PCB_TYPE                 0x0000

#define PCB_MAJOR_VERSION        1
#define PCB_MINOR_VERSION        0

#define FIRMWARE_MAJOR_VERSION   1
#define TRANSPORTLAYER_MINOR_CORRECTION 2
#define FIRMWARE_MINOR_VERSION   0+TRANSPORTLAYER_MINOR-TRANSPORTLAYER_MINOR_CORRECTION
//Local FIRMWARE_MINOR_VERSION
//0:  Initial release


#define MANUFACTURER_ID          1     //D&R
#ifndef COBRANET_16X16
  #define PRODUCT_ID               27    //Axum-Rack-CN8x8
#else
  #define PRODUCT_ID               28    //Axum-Rack-CN16x16
#endif

#ifndef COBRANET_16X16
  #define NR_OF_STATIC_OBJECTS    (1143-1023)
#else
  #define NR_OF_STATIC_OBJECTS    (1259-1023)
#endif
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

#ifndef COBRANET_16X16
eeprom char NodeName[32] = "Rack-CN8x8";
#else
eeprom char NodeName[32] = "Rack-CN16x16";
#endif

unsigned char Parent[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char HardwareMinorRevision = 0x00;
unsigned char FPGAFirmwareMajorRevision = 0;
unsigned char FPGAFirmwareMinorRevision = 0;


flash DEFAULT_NODE_OBJECT_STRUCT DefaultNodeObjects =
{
#ifndef COBRANET_16X16
   "Rack CobraNet 8x8 in/out board",      //Description
#else
   "Rack CobraNet 16x16 in/out board",    //Description
#endif                                          //Name is stored in EEPROM, see above
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
   { "CobraNet-in-1-Signal"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-in-2-Signal"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-in-3-Signal"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-in-4-Signal"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-in-5-Signal"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-in-6-Signal"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-in-7-Signal"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-in-8-Signal"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
#ifdef COBRANET_16X16
   { "CobraNet-in-9-Signal"   , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-in-10-Signal"  , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-in-11-Signal"  , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-in-12-Signal"  , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-in-13-Signal"  , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-in-14-Signal"  , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-in-15-Signal"  , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-in-16-Signal"  , 0x01
                              , {STATE_DATATYPE             ,  1, 0     , 1      }
                              , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
#endif
   { "CobraNet-in-1-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-in-2-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CobraNet-in-3-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-in-4-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CobraNet-in-5-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-in-6-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CobraNet-in-7-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-in-8-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
#ifdef COBRANET_16X16
   { "CobraNet-in-9-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-in-10-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CobraNet-in-11-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-in-12-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CobraNet-in-13-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-in-14-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CobraNet-in-15-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-in-16-Routing"       , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
#endif
   { "CobraNet-in-1-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-in-2-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-in-3-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-in-4-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-in-5-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-in-6-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-in-7-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-in-8-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
#ifdef COBRANET_16X16
   { "CobraNet-in-9-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-in-10-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-in-11-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-in-12-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-in-13-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-in-14-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-in-15-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-in-16-Level"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
#endif
   { "CobraNet-in-1-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-in-2-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-in-3-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-in-4-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-in-5-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-in-6-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-in-7-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-in-8-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
#ifdef COBRANET_16X16
   { "CobraNet-in-9-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-in-10-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-in-11-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-in-12-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-in-13-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-in-14-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-in-15-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-in-16-Phase"         , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
#endif
   { "CobraNet-out-1-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-out-2-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-out-3-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-out-4-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-out-5-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-out-6-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-out-7-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-out-8-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
#ifdef COBRANET_16X16
   { "CobraNet-out-9-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-out-10-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-out-11-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-out-12-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-out-13-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-out-14-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-out-15-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
   { "CobraNet-out-16-Signal"       , 0x01
                                 , {STATE_DATATYPE             ,  1, 0     , 1      }
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      , 0   }},
#endif
   { "CobraNet-out-1-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-out-2-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CobraNet-out-3-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-out-4-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CobraNet-out-5-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-out-6-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CobraNet-out-7-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-out-8-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
#ifdef COBRANET_16X16
   { "CobraNet-out-9-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-out-10-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CobraNet-out-11-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-out-12-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CobraNet-out-13-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-out-14-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CobraNet-out-15-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-out-16-Routing"      , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
#endif
   { "CobraNet-out-1-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-2-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-3-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-4-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-5-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-6-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-7-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-8-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
#ifdef COBRANET_16X16
   { "CobraNet-out-9-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-10-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-11-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-12-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-13-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-14-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-15-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-16-Level"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
#endif
   { "CobraNet-out-1-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-2-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-3-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-4-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-5-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-6-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-7-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-8-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
#ifdef COBRANET_16X16
   { "CobraNet-out-9-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-10-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-11-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-12-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-13-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-14-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-15-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-16-Phase"        , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
#endif
   { "CobraNet-out-1-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-2-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-3-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-4-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-5-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-6-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-7-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-8-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
#ifdef COBRANET_16X16
   { "CobraNet-out-9-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-10-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-11-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-12-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-13-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-14-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-15-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-16-Dim"          , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
#endif
   { "CobraNet-out-1-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "CobraNet-out-2-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "CobraNet-out-3-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "CobraNet-out-4-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "CobraNet-out-5-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "CobraNet-out-6-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "CobraNet-out-7-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "CobraNet-out-8-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
#ifdef COBRANET_16X16
   { "CobraNet-out-9-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "CobraNet-out-10-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "CobraNet-out-11-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "CobraNet-out-12-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "CobraNet-out-13-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "CobraNet-out-14-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "CobraNet-out-15-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
   { "CobraNet-out-16-Dim-level"    , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0xC900 }},
#endif
   { "CobraNet-out-1/2-Talkback"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 16     , 0   }},
   { "CobraNet-out-3/4-Talkback"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 16     , 0   }},
   { "CobraNet-out-5/6-Talkback"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 16     , 0   }},
   { "CobraNet-out-7/8-Talkback"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 16     , 0   }},
#ifdef COBRANET_16X16
   { "CobraNet-out-9/10-Talkback"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 16     , 0   }},
   { "CobraNet-out-11/12-Talkback"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 16     , 0   }},
   { "CobraNet-out-13/14-Talkback"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 16     , 0   }},
   { "CobraNet-out-15/16-Talkback"   , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 16     , 0   }},
#endif
   { "CobraNet-out-1-TB-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-out-2-TB-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CobraNet-out-3-TB-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-out-4-TB-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CobraNet-out-5-TB-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-out-6-TB-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CobraNet-out-7-TB-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-out-8-TB-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
#ifdef COBRANET_16X16
   { "CobraNet-out-9-TB-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-out-10-TB-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CobraNet-out-11-TB-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-out-12-TB-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CobraNet-out-13-TB-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-out-14-TB-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
   { "CobraNet-out-15-TB-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 1   }},
   { "CobraNet-out-16-TB-routing"     , 0x00
                                 , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                 , {STATE_DATATYPE             ,  1, 0     , 3      , 2   }},
#endif
   { "CobraNet-out-1-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-2-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-3-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-4-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-5-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-6-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-7-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-8-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
#ifdef COBRANET_16X16
   { "CobraNet-out-9-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-10-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-11-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-12-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-13-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-14-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-15-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
   { "CobraNet-out-16-Talkback-level"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {FLOAT_DATATYPE             ,  2, 0xD380, 0x4E00 , 0x0000 }},
#endif
   { "CobraNet-out-1-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-2-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-3-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-4-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-5-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-6-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-7-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-8-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
#ifdef COBRANET_16X16
   { "CobraNet-out-9-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-10-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-11-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-12-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-13-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-14-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-15-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "CobraNet-out-16-Talkback-phase"  , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
#endif
   { "Total-CobraNet-out-1-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-CobraNet-out-2-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-CobraNet-out-3-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-CobraNet-out-4-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-CobraNet-out-5-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-CobraNet-out-6-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-CobraNet-out-7-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-CobraNet-out-8-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }}
#ifdef COBRANET_16X16
,
   { "Total-CobraNet-out-9-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-CobraNet-out-10-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-CobraNet-out-11-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-CobraNet-out-12-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-CobraNet-out-13-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-CobraNet-out-14-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-CobraNet-out-15-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
   { "Total-CobraNet-out-16-Mute"      , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
#endif
   { "Enable word clock"            , 0x00
                                    , {NO_DATA_DATATYPE           ,  0, 0     , 0      }
                                    , {STATE_DATATYPE             ,  1, 0     , 1      , 0   }},
};
#else
flash OBJECT_VARIABLE_INFORMATION_STRUCT ObjectVariableInformation[1];
#endif

#endif
