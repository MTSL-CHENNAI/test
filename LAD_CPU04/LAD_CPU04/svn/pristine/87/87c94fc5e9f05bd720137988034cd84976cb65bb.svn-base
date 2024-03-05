//**********************************************************************************************************************
//
//                                                  c_nvm.c
//
//**********************************************************************************************************************
//
//                                        Copyrights(c) by KNORR-BREMSE,
//                                         Rail Vehicle Systems, Munich
//
//! @project IBC
//! @date    2023-11-28
//! @author  C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file  c_nvm.c
//! @brief User (Framework, Application etc.) Configuration for areas of Non-volatile memory devices.
//!
//**********************************************************************************************************************
//
// History
// Date         Author      Changes
// 2018-06-11   K. Gade     BC0025-32: Initial Configuration
// 2018-09-10   K. Gade     BC0025-59: Added Device_1 configuration for application area, removed unused header file.
// 2018-10-22   K. Gade     BC0025-66: Updated Device_0 configuration for Framework DataBackup component.
// 2019-01-15   K. Gade     BC0025-81: Generic area id macro added, Restructuring of device specific configuration.
// 2019-01-31   K. Gade     BC0025-102: Updated APP configuration version for device_0.
// 2019-03-01   K. Gade     BC0025-91: New device for POFF data handling is added, POFF configuration is included.
// 2019-07-16   K. Gade     BC0025-202: Updated FRAM configuration for APP and defined SPARE memory area id for
//                          example purpose.
// 2019-11-07   K. Gade     Adapted for slim firmware changes.
// 2021-09-20   N. Jadhav   Adaptation changes for Genca V07.00 porting, c_nvm.c and c_fim.c moved to MWL.
// 2021-10-20   A. Mauro    Modified NVM_USR_AREA_SIZE2_0 due to FWK change: 0x2000->0x4000
// 2022-03-09   A. Mauro    TC_004-13662: Modified NVM_FWK_AREA_SIZE1_2 0x4800->0xA080
// 2023-01-09   J. Lulli    Coding guidelines alignment
// 2023-11-28   C. Brancolini Lint Plus cleanup
//
//**********************************************************************************************************************
//! NOTE: USAGE OF AREA_ID MACRO
//!*********************************************************************************************************************
//! If any Component <Comp_Name> wants to use area of NVM- go through following steps
//!*********************************************************************************************************************
//! STEP-1:: In 'c_nvm.c' file, define area id as follows- consider values of X & Y
//!          #define NVM_USR_AREA_IDX_Y              ((U8)  0x00)    //!!< X-> DeviceID, Y-> AreaID
//!
//!     e.g. AreaID for 'ladc_xxx', will be as follows, [no need to mention name of component in area id]
//!          #define NVM_USR_AREA_ID1_0              ((U8)  0x00)    //!!< Device-1, Area-0
//!*********************************************************************************************************************
//! STEP-2:: In 'c_nvm.c' file, [Note: include "<Comp_Name>.h" to access definition of following macro]
//!          Enter 'NVM_USR_AREA_IDX_Y' in configuration table - acNVM_USR_Device_X [X-> DeviceID]
//!          Define area id 'NVM_USR_AREA_IDX_Y' for it's usage, as follows,
//!          <Comp_Name>_NVM_USR_AREA_ID_SET  ( NVM_USR_AREA_IDX_Y ) *************For NON-POFF // @suppress("Horizonal Lines")
//!          <Comp_Name>_NVM_FWK_AREA_ID_SET  ( NVM_USR_AREA_IDX_Y ) *************For NON-POFF // @suppress("Horizonal Lines")
//!
//!     e.g. In file 'c_nvm.c', [At the End of section- "Global constant definitions"], define following,
//!          Enter 'NVM_USR_AREA_ID1_0' in configuration table - acNVM_USR_Device_1
//!          [Note: include "ladc_flash.h" to access definition of following macro]
//!          For 'ladc_xxx',
//!          LADC_NVM_USR_AREA_ID_SET ( NVM_USR_AREA_ID1_0 )
//!          DABA_NVM_FWK_AREA_ID_SET ( NVM_FWK_AREA_ID1_0 )
//!*********************************************************************************************************************
//! STEP-3:: Below macros needs to be defined in '<Comp_Name>.H'
//!       #define <Comp_Name>_NVM_USR_AREA_ID          u8<Comp_Name>_NonPoffUsrArea
//!       #define <Comp_Name>_NVM_USR_AREA_ID_SET(x)   BCM_COMMON_AREA_ID_SET ( <Comp_Name>_NVM_USR_AREA_ID, x )
//!       BCM_COMMON_AREA_ID_DECL  ( <Comp_Name>_NVM_USR_AREA_ID )

//!     e.g. Define following in 'ladc_flash.h' file (Module header file)
//!          [Note: include "bcm_common.h" to access BCM Macros]
//!          #define LADC_NVM_USR_AREA_ID             u8LADC_NonPoffUsrArea
//!          #define LADC_NVM_USR_AREA_ID_SET(x)      BCM_COMMON_AREA_ID_SET ( LADC_NVM_USR_AREA_ID, x )
//!          BCM_COMMON_AREA_ID_DECL  ( LADC_NVM_USR_AREA_ID )
//!          Similarly,
//!          #define DABA_NVM_FWK_AREA_ID             u8DABA_NonPoffFwkArea
//!          #define DABA_NVM_FWK_AREA_ID_SET(x)      BCM_COMMON_AREA_ID_SET ( DABA_NVM_FWK_AREA_ID, x )
//!          BCM_COMMON_AREA_ID_DECL  ( DABA_NVM_FWK_AREA_ID )
//! STEP-4:: Now, 'LADC_NVM_USR_AREA_ID', and 'DABA_NVM_FWK_AREA_ID' can be used in implementation
//!*********************************************************************************************************************
//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "kb_types.h"                                    // Standard definitions
#include "ct_nvm.h"                                      // CDO table configuration dependencies
#include "c_nvm.h"                                       // NVM device constants and dependencies
#include "nvm_common.h"                                  // NVM Common definitions
#include "FwkAlMamoNvMem.h"                              // MAMO area declarations
#include "FwkAlRtcNvMem.h"                               // RTC area declarations
#include "FwkAlDsmNvMem.h"                               // DSM area declarations
#include "FwkAlDFMNvMem.h"                               // DFM area declarations
#include "FwkAlDataBackup.h"                             // DataBackup area declarations
#include "MaMoAl.h"                                      // MAMO buffer dependencies
#include "ladc_flash.h"                                  // LAD configuration area declarations
#include "FwkAlDrcNvMem.h"
#include "nvm_i.h"

//**************************************** Constant / macro definitions ( #define ) ************************************
//! No.of devices configured in CDO table
#define NVM_USR_NUM_OF_CONFIG_DEVICES   ((U8) 0x03)

//! Configuration version needs to be updated, once there is modification in 'acNVM_USR_Device_x'
#define NVM_USR_CFG_VERS_DEV_0          ((U8) 0x01)      //!< Version of APP's NVM configuration for Device-0
#define NVM_USR_CFG_VERS_DEV_1          ((U8) 0x01)      //!< Version of APP's NVM configuration for Device-1
#define NVM_USR_CFG_VERS_DEV_2          ((U8) 0x01)      //!< Version of APP's NVM configuration for Device-2

//----------------------------------------------------------------------------------------------------------------------
//! APP area definitions of Device_0, i.e. POFF Device
//----------------------------------------------------------------------------------------------------------------------
//! Area identifiers of APP for Device_0
#define NVM_POFF_FWK_AREA_ID_DSM            ((U8) 0x00)   //!< Device-0, Area-0
#define NVM_POFF_FWK_AREA_ID_MAMO           ((U8) 0x01)   //!< Device-0, Area-1
#define NVM_POFF_FWK_AREA_ID_RTC            ((U8) 0x02)   //!< Device-0, Area-2
#define NVM_POFF_FWK_AREA_ID_DFM            ((U8) 0x03)   //!< Device-0, Area-3
#define NVM_POFF_FWK_AREA_ID_DRC            ((U8) 0x04)   //!< Device-0, Area-4

//! Area sizes of APP for Device_0
#define NVM_POFF_FWK_AREA_SIZE_DSM          ((U32) 1024)      //!< Device-0, First area size
#define NVM_POFF_FWK_AREA_SIZE_MAMO         ((U32) C_MAMOAL_DECS_NVMEM_DATA_BUFFER_LENGTH * 4U) //!< Dev-0, Second area
#define NVM_POFF_FWK_AREA_SIZE_RTC          ((U32) 8)
#define NVM_POFF_FWK_AREA_SIZE_DFM          ((U32) 340)
#define NVM_POFF_FWK_AREA_SIZE_DRC          ((U32) 32)

//! Area offset of APP for Device_0
#define NVM_USR_AREA_OFFSET0_0              ((U32) 0x0000)  //!< Device-0, First area offset
#define NVM_USR_AREA_OFFSET0_1              ((U32) (NVM_USR_AREA_OFFSET0_0 + NVM_POFF_FWK_AREA_SIZE_DSM))
#define NVM_USR_AREA_OFFSET0_2              ((U32) (NVM_USR_AREA_OFFSET0_1 + NVM_POFF_FWK_AREA_SIZE_MAMO))
#define NVM_USR_AREA_OFFSET0_3              ((U32) (NVM_USR_AREA_OFFSET0_2 + NVM_POFF_FWK_AREA_SIZE_RTC))
#define NVM_USR_AREA_OFFSET0_4              ((U32) (NVM_USR_AREA_OFFSET0_3 + NVM_POFF_FWK_AREA_SIZE_DFM))
// End of Device_0 Definitions------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
//! APP area definitions of Device_1, i.e. FRAM
//----------------------------------------------------------------------------------------------------------------------
//! Area identifiers of APP for Device_1
#define NVM_USR_AREA_ID1_0                  ((U8) 0x00)     //!< Device-1, Area-0
#define NVM_FWK_AREA_ID1_1                  ((U8) 0x01)     //!< Device-1, Area-1 :  FWK DataBackup
#define NVM_FWK_AREA_ID1_2                  ((U8) 0x02)     //!< Device-1, Area-2 :  FWK DFM NON POFF
#define NVM_USR_AREA_ID1_SPARE              ((U8) 0x03)     //!< Spare or Free space

//! Area sizes of APP for Device_1
#define NVM_USR_AREA_SIZE1_0                ((U32) 0x0020)  //!< Device-1, First area size-32 bytes
#define NVM_FWK_AREA_SIZE1_1                ((U32) 0x0200)  //!< Device-1, FWK area size-512 bytes
#define NVM_FWK_AREA_SIZE1_2                ((U32) 0xA080)  //!< Device-1, DFM area size-41088 bytes
#define NVM_USR_AREA_SIZE1_SPARE            ((U32) 0xC0)    //!< Device-1, Free space

//! Area offset of APP for Device_1
#define NVM_USR_AREA_OFFSET1_0              ((U32) 0x0000)  //!< Device-0, First area offset
#define NVM_FWK_AREA_OFFSET1_1              ((U32) (NVM_USR_AREA_OFFSET1_0 + NVM_USR_AREA_SIZE1_0))
#define NVM_FWK_AREA_OFFSET1_2              ((U32) (NVM_FWK_AREA_OFFSET1_1 + NVM_FWK_AREA_SIZE1_1))
#define NVM_FWK_AREA_OFFSET1_SPARE          ((U32) (NVM_FWK_AREA_OFFSET1_2 + NVM_FWK_AREA_SIZE1_2))

// End of Device_1 Definitions----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
//! APP area definitions of Device_2, i.e. FLASH
//----------------------------------------------------------------------------------------------------------------------
// Erase pattern on flash, i.e. Value after erasing flash memory
#define NVM_FLASH_ERASE_PATTERN             ((U32) 0xFFFFFFFFU)

//! Area identifiers of APP for Device_2
#define NVM_USR_AREA_ID2_0                  ((U8) 0x00)     //!< Device-2, Area-0 : LADC Flash
#define NVM_USR_AREA_ID2_SPARE              ((U8) 0x01)     //!< Device-2, Spare Area

//! Area size of APP for Device_2
#define NVM_USR_AREA_SIZE2_0                ((U32) 0x4000)  //!< Device-2, First area size
#define NVM_USR_AREA_SIZE2_SPARE            ((U32) 0x8000)  //!< Device-2, Spare area size

//! Area offset of APP for Device_2
#define NVM_USR_AREA_OFFSET2_0              ((U32) 0x0000)  //!< Device-2, First area offset
#define NVM_USR_AREA_OFFSET2_SPARE          ((U32) NVM_USR_AREA_OFFSET2_0 + NVM_USR_AREA_SIZE2_0)  //!< Test

// End of Device_2 Configuration----------------------------------------------------------------------------------------

//! Reserved byte for structure alignment in CDO table
#define RES_BYTE                        ((U8) 0x00)

//**************************************** Type definitions ( typedef ) ************************************************
//! Number of elements available in CDO_NVM_USR_CFG_TABLE
TYPEDEF_CDO_NVM_APP_CFG_TABLE (APP, NVM_USR_NUM_OF_CONFIG_DEVICES); // @suppress("Wrong derived data type") // @suppress("Wrong prefix")

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************
//! Note: Configuration provided for Device_0 is example configuration, tested on RAM.
//! Actual FRAM device configuration can be overwritten here, in place of Device_0 configuration
//! APP area configuration for Device_0
//! Note: Please add 'AreaID' in sequential manner like 0,1,2...Don't give random numbers
static const C_NVM_USR_DEVICE_AREAS acNVM_USR_Device_0[] =
{
    // Area ID,                       Area Offset,                  Area Size
    { NVM_POFF_FWK_AREA_ID_DSM,  RES_BYTE, RES_BYTE, RES_BYTE, NVM_USR_AREA_OFFSET0_0, NVM_POFF_FWK_AREA_SIZE_DSM  },
    { NVM_POFF_FWK_AREA_ID_MAMO, RES_BYTE, RES_BYTE, RES_BYTE, NVM_USR_AREA_OFFSET0_1, NVM_POFF_FWK_AREA_SIZE_MAMO },
    { NVM_POFF_FWK_AREA_ID_RTC,  RES_BYTE, RES_BYTE, RES_BYTE, NVM_USR_AREA_OFFSET0_2, NVM_POFF_FWK_AREA_SIZE_RTC  },
    { NVM_POFF_FWK_AREA_ID_DFM,  RES_BYTE, RES_BYTE, RES_BYTE, NVM_USR_AREA_OFFSET0_3, NVM_POFF_FWK_AREA_SIZE_DFM  },
    { NVM_POFF_FWK_AREA_ID_DRC,  RES_BYTE, RES_BYTE, RES_BYTE, NVM_USR_AREA_OFFSET0_4, NVM_POFF_FWK_AREA_SIZE_DRC  }
};

//! APP area configuration for FRAM
static const C_NVM_USR_DEVICE_AREAS acNVM_USR_Device_1[] =
{
    // AreaID,                                                AreaOffset,                 AreaSize
    { NVM_USR_AREA_ID1_0,       RES_BYTE, RES_BYTE, RES_BYTE, NVM_USR_AREA_OFFSET1_0,     NVM_USR_AREA_SIZE1_0     },
    { NVM_FWK_AREA_ID1_1,       RES_BYTE, RES_BYTE, RES_BYTE, NVM_FWK_AREA_OFFSET1_1,     NVM_FWK_AREA_SIZE1_1     },
    { NVM_FWK_AREA_ID1_2,       RES_BYTE, RES_BYTE, RES_BYTE, NVM_FWK_AREA_OFFSET1_2,     NVM_FWK_AREA_SIZE1_2     },
    { NVM_USR_AREA_ID1_SPARE,   RES_BYTE, RES_BYTE, RES_BYTE, NVM_FWK_AREA_OFFSET1_SPARE, NVM_USR_AREA_SIZE1_SPARE }
};

//! APP area configuration for FLASH
static const C_NVM_USR_DEVICE_AREAS acNVM_USR_Device_2[] =
{
    // Area ID,                      Area Offset,                  Area Size
    { NVM_USR_AREA_ID2_0,       RES_BYTE, RES_BYTE, RES_BYTE, NVM_USR_AREA_OFFSET2_0,     NVM_USR_AREA_SIZE2_0      },
    { NVM_USR_AREA_ID2_SPARE,   RES_BYTE, RES_BYTE, RES_BYTE, NVM_USR_AREA_OFFSET2_SPARE, NVM_USR_AREA_SIZE2_SPARE  }
};


//! CDO table stores APP area configuration per device and no.of areas count
static const CDO_NVM_APP_CFG_TABLE(APP) cNVM_USR_CfgTable =
{
    // Initialize Table header
    // Inhibit lint note 9034 due to a GenMPC55xx macro
    //lint  -save -e9034
    INIT_CDO_NVM_APP_CFG_TABLE_HEADER(APP, NVM_CDO_TABLE_INDEX),
    //lint  -restore
    {
        {
            NVM_DEVICE_ID0,
            acNVM_USR_Device_0,
            ((U8) (sizeof(acNVM_USR_Device_0) / sizeof(C_NVM_USR_DEVICE_AREAS))),
            NVM_USR_CFG_VERS_DEV_0
        },
        {
            NVM_DEVICE_ID1,
            acNVM_USR_Device_1,
            ((U8) (sizeof(acNVM_USR_Device_1) / sizeof(C_NVM_USR_DEVICE_AREAS))),
            NVM_USR_CFG_VERS_DEV_1
        },
        {
            NVM_DEVICE_ID2,
            acNVM_USR_Device_2,
            ((U8) (sizeof(acNVM_USR_Device_2) / sizeof(C_NVM_USR_DEVICE_AREAS))),
            NVM_USR_CFG_VERS_DEV_2
        }
    }
};

//! Devices available in configuration
const U8 u8NVM_USR_CfgNumOfDevices = NVM_USR_NUM_OF_CONFIG_DEVICES;

//! Set reference to CDO table
// Inhibit lint note 9075 (external symbol defined without a prior declaration)
// due to a missing declaration in GenMPC55xx
// Inhibit lint note 9005 (cast drops const qualifier)
// due to a GenMPC55xx macro
//lint -save -e9075 -e9005
SET_CONST_REF_CDO_NVM_APP_CFG_TABLE(&cNVM_USR_CfgTable);  // @suppress("Wrong prefix")
//lint -restore

//----------------------------------------------------------------------------------------------------------------------
//! User or Application area definitions
//! Device identifier for USER of NVM, which will be used for READ/WRITE/ERASE Operations
const U8 u8NVM_DeviceIDForUser = NVM_DEVICE_ID2;

//! Erase pattern for Flash device, it is required to verify erase status before write
const U32 u32NVM_FlashErasePattern = NVM_FLASH_ERASE_PATTERN;

//! Set Area ID & AreaOffset of LADCFG for it's usage
LADC_NVM_USR_AREA_ID_SET     ( NVM_USR_AREA_ID2_0 )
LADC_NVM_USR_AREA_OFFSET_SET ( NVM_USR_AREA_OFFSET2_0 )

//----------------------------------------------------------------------------------------------------------------------
//! Framework area id definitions
//! Device identifier for Framework users of NVM, which will be used for READ/WRITE/ERASE Operations
const U8 u8NVM_DeviceIDForFwk = NVM_DEVICE_ID1;

//! Set Area ID for DataBackup
DABA_NVM_FWK_AREA_ID_SET ( NVM_FWK_AREA_ID1_1 )

// FWK area ID for DSM
DSM_POFF_USR_AREA_ID_SET (NVM_POFF_FWK_AREA_ID_DSM)

// FWK area ID for MAMO
MAMO_POFF_USR_AREA_ID_SET (NVM_POFF_FWK_AREA_ID_MAMO)

// FWK area ID for RTC
RTC_POFF_USR_AREA_ID_SET (NVM_POFF_FWK_AREA_ID_RTC)

// FWK area ID for DFM
DFM_POFF_USR_AREA_ID_SET ( NVM_POFF_FWK_AREA_ID_DFM )

// FWK area ID for DRC
DRC_POFF_USR_AREA_ID_SET ( NVM_POFF_FWK_AREA_ID_DRC )

// FWK non-poff area ID for DFM
DFM_NVM_FWK_AREA_ID_SET  ( NVM_FWK_AREA_ID1_2 )
//----------------------------------------------------------------------------------------------------------------------

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

// EndOfHeader *********************************************************************************************************

// EndOfFile c_nvm.c ***************************************************************************************************
