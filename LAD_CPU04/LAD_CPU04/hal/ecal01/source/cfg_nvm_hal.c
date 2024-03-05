//**********************************************************************************************************************
//
//                                                  cfg_nvm_hal.c
//
//**********************************************************************************************************************
//
//                                        Copyrights(c) by KNORR-BREMSE,
//                                         Rail Vehicle Systems, Munich
//
//! @project  IBC
//! @date     2023-11-02
//! @author   C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file cfg_nvm_hal.c
//! @brief HAL configuration of Non-volatile memory devices.
//!
//**********************************************************************************************************************
//
// History
// Date         Author      Changes
// 2018-06-11   K. Gade     BC0025-32: Start
// 2018-09-18   K. Gade     BC0025-59: Added Program Flash Configuration.
// 2018-10-23   K. Gade     BC0025-66: Updated FRAM-1Mbit Configuration for Non-POFF data handling.
// 2019-01-18   N. Joshi    Updated max flash transfer size for MPC5534
// 2019-05-07   K. Gade     BC0025-91: New device for POFF data handling is added, HAL areas added for POFF.
// 2019-07-16   K. Gade     BC0025-202: FRAM device configuration is updated. Spare area id created for free space.
//                          Memory allocated for HAL, SVL, APP.
// 2019-10-18   F. Heindl   Changed DRC_POFF_FWR_AREA_ID_SET to DRC_POFF_USR_AREA_ID_SET
// 2020-12-04   A. Gatare   Adapted for GenCA 6.11
// 2021-09-14   N. Jadhav   GenCA V07.00 adaptation changes.
// 2022-11-26   S. Shinde   Adapted for GenCA 7.05
// 2023-11-02   C. Brancolini Lint Plus cleanup
//
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "kb_types.h"                               // Standard definitions
#include "bcm_hal_onn.h"                            // BCM_HAL_ONN structure dependencies
#include "bcm_hal_onn_s.h"                          // BCM ONN dependencies
#include "bcm_fwr_cfgbcmhal_s.h"                    // BCM area size dependencies
#include "MaintFlagH_i.h"                           // Maint_FlagH area id for POFF
#include "nvm_hal_i.h"                              // NVM device configuration dependencies
#include "nvm_hal.h"                                // NVM device configuration dependencies
#include "nvm_hal_bs_i.h"                           // NVM_HAL board specific dependencies
#include "nvm_common.h"                             // NVM Common definitions
#include "cfg_nvm_hal_poff_i.h"                     // POFF related definitions, configurable parameters of POFF
#include "55xflsh.h"                                // For max transfer size of flash

//**************************************** Constant / macro definitions ( #define ) ************************************
//! Number of available devices
#define NVM_HAL_NUM_OF_DEVICES              ((U8) 0x03)

//! Default value present on memory locations or values after Erase
//! Note: Board owner shall update these macros, based of configured NVM device
#define NVM_DEFAULT_VAL_DEV_0           ((U8)(0x00))
#define NVM_DEFAULT_VAL_DEV_1           ((U8)(0x00))
#define NVM_DEFAULT_VAL_DEV_2           ((U8)(0xFF))

//----------------------------------------------------------------------------------------------------------------------
//! Definitions of Device_0, i.e. POFF Device
//----------------------------------------------------------------------------------------------------------------------
//! POFF Device configuration
#define NVM_DEV_0_START_ADDR                ((U32) 0x00)                //!< Start address for POFF
#define NVM_DEV_0_MX_TXFER_SIZE             NVM_HAL_POFF_BUFF_SIZE      //!< Transfer Size of POFF block
#define NVM_DEV_0_SIZE                      NVM_HAL_POFF_BUFF_SIZE      //!< Size of complete POFF block

//! Area identifiers of HAL for Device_0
#define NVM_HAL_POFF_AREA_ID_FATAL          ((U8) 0x00)                     //!< Device-0, Area-0
#define NVM_HAL_POFF_AREA_ID_CRITICAL       ((U8) 0x01)                     //!< Device-0, Area-1
#define NVM_HAL_POFF_AREA_ID_ONN            ((U8) 0x02)                     //!< Device-0, Area-2
#define NVM_HAL_POFF_AREA_ID_MAINTFLAG      ((U8) 0x03)                     //!< Device-0, Area-3
//---New area id can be added before 'SPARE'
#define NVM_HAL_POFF_AREA_ID_SPARE          ((U8) 0x04)                     //!< Device-0, Area-4

//! POFF buffer size reserved for non FWR areas: 4KBytes
#define NVM_HAL_POFF_BUFF_AREAS_SIZE_NONFWR ((U32) 4096)

//! Area sizes of HAL for Device_0
#define NVM_HAL_POFF_AREA_SIZE_FATAL        BCM_FWR_LOG_MAX_SIZE_FATAL            //!< Device-0, First area size
#define NVM_HAL_POFF_AREA_SIZE_CRITICAL     (BCM_FWR_LOG_MAX_SIZE_CRITICAL + 2U)  //!< Device-0, Second area size
#define NVM_HAL_POFF_AREA_SIZE_ONN          ((U32)sizeof(C_BCM_HAL_ONN_DATA))
#define NVM_HAL_POFF_AREA_SIZE_MAINTFLAG    ((U32) 8)
//--Area size of new area id shall be subtracted from SPARE size
//! Device-0, available FWR memory
#define NVM_HAL_POFF_AREA_SIZE_SPARE                                                                   \
                                            ((U32)(((((NVM_HAL_POFF_BUFF_AREAS_SIZE_FWR_U32 * 4U)  -   \
                                                       NVM_HAL_POFF_AREA_SIZE_FATAL)               -   \
                                                       NVM_HAL_POFF_AREA_SIZE_CRITICAL)            -   \
                                                       NVM_HAL_POFF_AREA_SIZE_ONN)                 -   \
                                                       NVM_HAL_POFF_AREA_SIZE_MAINTFLAG))

//! Area offset of HAL for Device_0
#define NVM_HAL_AREA_OFFSET0_0              ((U32) 0x0000)  //!< Device-0, First area offset
#define NVM_HAL_AREA_OFFSET0_1              ((U32) (NVM_HAL_AREA_OFFSET0_0 + NVM_HAL_POFF_AREA_SIZE_FATAL))
#define NVM_HAL_AREA_OFFSET0_2              ((U32) (NVM_HAL_AREA_OFFSET0_1 + NVM_HAL_POFF_AREA_SIZE_CRITICAL))
#define NVM_HAL_AREA_OFFSET0_3              ((U32) (NVM_HAL_AREA_OFFSET0_2 + NVM_HAL_POFF_AREA_SIZE_ONN))
#define NVM_HAL_AREA_OFFSET0_SPARE          ((U32) (NVM_HAL_AREA_OFFSET0_3 + NVM_HAL_POFF_AREA_SIZE_MAINTFLAG))
//--Offset of new area shall be calculated by considering 'AreaOffsets' before 'SPARE' area
#define NVM_HAL_AREA_OFFSET0_RES            ((U32) (NVM_HAL_AREA_OFFSET0_SPARE + NVM_HAL_POFF_AREA_SIZE_SPARE))

// End of Device_0 definitions------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
//! Definitions of Device_1, i.e. FRAM
//----------------------------------------------------------------------------------------------------------------------
//! FRAM-FM25V10 configuration
#define NVM_DEV_1_START_ADDR                (NVM_HAL_POFF_BUFF_SIZE)    //!< FRAM start address for Non-POFF
#define NVM_DEV_1_MX_TXFER_SIZE             ((U32) 0x100)      //!< Value will be overwritten in Device info interface
#define NVM_DEV_1_TOTAL_SIZE                ((U32) 131072)     //!< Size of FRAM - 128 kBytes
#define NVM_DEV_1_SIZE                      (NVM_DEV_1_TOTAL_SIZE - NVM_HAL_POFF_BUFF_SIZE)//!< Size considering POFF

//! Area identifiers of HAL for Device_1
// Note: This is spare area id provided as an example, board owner can add multiple areas in place of this area id
#define NVM_HAL_AREA_ID1_SPARE              ((U8) 0x00)          //!< Device-1, Spare memory for HAL areas


//! Area sizes of HAL for Device_1
// Note: This is spare area size provided as an example, board owner can use this memory area
#define NVM_HAL_AREA_SIZE1_SPARE            ((U32) 0x800)          //!< Device-1, Spare memory for HAL areas
#define NVM_HAL_AREA_SIZE1_RES_SVL_APP      ((U32) 0x1D800)        //!< Device-1, Reserved [SVL+ APP] area size


//! Area offset of HAL for Device_1
#define NVM_HAL_AREA_OFFSET1_SPARE          ((U32) 0x0000)        //!< Device-1, First area offset
#define NVM_HAL_AREA_OFFSET1_RES_SVL_APP    ((U32)(NVM_HAL_AREA_OFFSET1_SPARE + NVM_HAL_AREA_SIZE1_SPARE))
                                                                  //!< Device-1, Second area offset
// End of Device_1 definitions------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
//! Definitions of Device_2, i.e. FLASH
//----------------------------------------------------------------------------------------------------------------------
//! Flash information is retrieved from '55xflsh'
//#define NVM_DEV_2_START_ADDR                ((U32) 0x00010000)    //!< FLASH start address
#define NVM_DEV_2_START_ADDR                ((U32) 0x00004000)    //!< FLASH start address
#define NVM_DEV_2_MX_TXFER_SIZE             ((U32) 0x10)        //!< Value will be overwritten in Device info interface
#define NVM_DEV_2_SIZE                      ((U32) 0xC000)        //!< FLASH block size in Bytes

//! Area identifiers of HAL for Device_2
// Note: Define area identifiers for Device_2 here
// There are no HAL areas for this device

//! Area size of HAL for Device_2
#define NVM_HAL_AREA_SIZE2_RES_SVL_APP      ((U32) 0xC000)        //!< Device-2, Reserved [SVL+ APP] area size

//! Area offset of HAL for Device_2
#define NVM_HAL_AREA_OFFSET2_RES            ((U32) 0x0000)        //!< Device-2, First area offset

// End of Device_2 definitions------------------------------------------------------------------------------------------

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************
//! HAL area configuration for POFF
static const C_NVM_HAL_DEVICE_AREAS acNVM_HAL_Device_0[] =
{
    // Area ID,                       Area Offset,                  Area Size
    { NVM_HAL_POFF_AREA_ID_FATAL,     NVM_HAL_AREA_OFFSET0_0,      NVM_HAL_POFF_AREA_SIZE_FATAL        },
    { NVM_HAL_POFF_AREA_ID_CRITICAL,  NVM_HAL_AREA_OFFSET0_1,      NVM_HAL_POFF_AREA_SIZE_CRITICAL     },
    { NVM_HAL_POFF_AREA_ID_ONN,       NVM_HAL_AREA_OFFSET0_2,      NVM_HAL_POFF_AREA_SIZE_ONN          },
    { NVM_HAL_POFF_AREA_ID_MAINTFLAG, NVM_HAL_AREA_OFFSET0_3,      NVM_HAL_POFF_AREA_SIZE_MAINTFLAG    },
    { NVM_HAL_POFF_AREA_ID_SPARE,     NVM_HAL_AREA_OFFSET0_SPARE,  NVM_HAL_POFF_AREA_SIZE_SPARE        },
    { NVM_SVL_AREA_ID_RES,            NVM_HAL_AREA_OFFSET0_RES,    NVM_HAL_POFF_BUFF_AREAS_SIZE_NONFWR }
};

//! HAL area configuration for FRAM
static const C_NVM_HAL_DEVICE_AREAS acNVM_HAL_Device_1[] =
{
    // Area ID,                       Area Offset,                  Area Size
    { NVM_HAL_AREA_ID1_SPARE,  NVM_HAL_AREA_OFFSET1_SPARE,          NVM_HAL_AREA_SIZE1_SPARE          }, // Free Space
    { NVM_SVL_AREA_ID_RES,     NVM_HAL_AREA_OFFSET1_RES_SVL_APP,    NVM_HAL_AREA_SIZE1_RES_SVL_APP    }
};

//! HAL area configuration for FLASH
static const C_NVM_HAL_DEVICE_AREAS acNVM_HAL_Device_2[] =
{
    // Area ID,                       Area Offset,                  Area Size
    { NVM_SVL_AREA_ID_RES,            NVM_HAL_AREA_OFFSET2_RES,     NVM_HAL_AREA_SIZE2_RES_SVL_APP    }
};

//! NVM devices configuration
const C_NVM_HAL_DEV_INFO acNVM_HAL_DeviceCfgInfo[NVM_HAL_NUM_OF_DEVICES] =
{
    {
        NVM_DEVICE_ID0,           // NVM DevID
        "POFF",                   // DeviceName
        ((U8) (sizeof(acNVM_HAL_Device_0) / sizeof(C_NVM_HAL_DEVICE_AREAS))), // No.of configured areas in this device
        NVM_DEFAULT_VAL_DEV_0, // Default initial value
        TRUE,                      // Device is memory mapped
        NVM_DEV_0_START_ADDR,     // StartAddr
        NVM_DEV_0_SIZE,           // DevSize
        NVM_DEV_0_MX_TXFER_SIZE,  // MaxTransfrSize
        acNVM_HAL_Device_0,       // Pointer to HAL area Configuration
    },
    {
        NVM_DEVICE_ID1,          // NVM DevID
        "FRAM",                  // DeviceName
        ((U8) (sizeof(acNVM_HAL_Device_1) / sizeof(C_NVM_HAL_DEVICE_AREAS))), // No.of configured areas in this device
        NVM_DEFAULT_VAL_DEV_1, // Default initial value
        FALSE,                      // Device is memory mapped
        NVM_DEV_1_START_ADDR,    // StartAddr
        NVM_DEV_1_SIZE,          // DevSize
        NVM_DEV_1_MX_TXFER_SIZE, // MaxTransfrSize
        acNVM_HAL_Device_1,      // Pointer to HAL area Configuration
    },
    {
        NVM_DEVICE_ID2,
        "FLASH",
        ((U8) (sizeof(acNVM_HAL_Device_2) / sizeof(C_NVM_HAL_DEVICE_AREAS))),
        NVM_DEFAULT_VAL_DEV_2, // Default initial value
        TRUE,                      // Device is memory mapped
        NVM_DEV_2_START_ADDR,
        NVM_DEV_2_SIZE,
        NVM_DEV_2_MX_TXFER_SIZE,
        acNVM_HAL_Device_2,
    }
};

//! Number of devices configured
const U8 u8NVM_HAL_NoOfDevicesConfigured = NVM_HAL_NUM_OF_DEVICES;

//! First area id of SVL area
const U8 u8NVM_HAL_SvlFirstAreaID = NVM_SVL_AREA_ID_RES;



//----------------------------------------------------------------------------------------------------------------------
//! Area Identifiers Definitions
//----------------------------------------------------------------------------------------------------------------------
//! FWR area ID for FATAL errors
BCM_FWR_LOG_POFF_AREA_ID_FATAL_SET(NVM_HAL_POFF_AREA_ID_FATAL)

//! FWR area ID for CRITICAL errors
BCM_FWR_LOG_POFF_AREA_ID_CRITICAL_SET(NVM_HAL_POFF_AREA_ID_CRITICAL)

//! FWR area ID for Node number bckup
BCM_HAL_ONN_POFF_AREA_ID_SET(NVM_HAL_POFF_AREA_ID_ONN)

//! FWR area ID for MaintFlag
MAINTFLAG_POFF_AREA_ID_SET(NVM_HAL_POFF_AREA_ID_MAINTFLAG)

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

// EndOfHeader *********************************************************************************************************

// EndOfFile cfg_nvm_hal.c *********************************************************************************************
