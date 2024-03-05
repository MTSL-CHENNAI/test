//**********************************************************************************************************************
//
//                                                  cfg_nvm.c
//
//**********************************************************************************************************************
//
//                                     Copyrights(c) 20222 by KNORR-BREMSE,
//                                         Rail Vehicle Systems, Munich
//
//! @project IBC
//! @date    2023-11-13
//! @author  C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file  cfg_nvm.c
//! @brief Service layer configuration of Non-volatile memory devices.
//!
//**********************************************************************************************************************
//
// History
// Date         Author      Changes
// 2018-06-11   K. Gade     BC0025-32: Initial Configuration
// 2018-09-18   K. Gade     BC0025-59: Added Device_1 configuration for application area.
// 2018-10-23   K. Gade     BC0025-66: Updated Device_0 configuration for Framework DataBackup component.
// 2018-12-10   K. Gade     BC0025-81: Restructuring of device specific configuration.
// 2019-05-05   K. Gade     BC0025-91: New device for POFF data handling is added, POFF configuration is included.
// 2019-07-05   K. Gade     APP area size increased for FRAM.
// 2019-07-16   K. Gade     BC0025-202: Updated FRAM configuration for HAL,SVL,APP and defined SPARE memory area id for
//                          example purpose.
// 2020-11-24   A. Gatare   Adapted for GenCA 6.11
// 2022-11-26   S.Shinde    Adapted for GenCA 7.05
// 2023-01-09   J. Lulli    Coding guidelines alignment
// 2023-11-13   C. Brancolini  Lint Plus clean up
//
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "kb_types.h"                                   // Standard definitions
#include "nvm_i.h"                                      // Operation Queue dependencies
#include "bcm_lmtd_i.h"                                 // BCM LMTD area size
#include "nvm_common.h"                                 // NVM Common definitions
#include "bcm_como_i.h"                                 // BCM_COMO area size

//**************************************** Constant / macro definitions ( #define ) ************************************
//! No.of devices configured
#define NVM_SVL_NUM_OF_CONFIG_DEVICES       ((U8) 0x03)

//! Following constants needs to be updated, if configuration in 'acNVM_SVL_Device_x' is changed by User
#define NVM_SVL_CFG_VERS_DEV_0              ((U8) 0x03)      //!< Version of SVL's NVM configuration for Device-0
#define NVM_SVL_CFG_VERS_DEV_1              ((U8) 0x05)      //!< Version of SVL's NVM configuration for Device-1
#define NVM_SVL_CFG_VERS_DEV_2              ((U8) 0x07)      //!< Version of SVL's NVM configuration for Device-2

//! This is size of queue, indicates how many operations can be queued in
#define NVM_SVL_CFG_MAX_QUEUE_ENTRIES       ((U8) 0x05)
//----------------------------------------------------------------------------------------------------------------------
//! SVL area definitions of Device_0, i.e. POFF Device
//----------------------------------------------------------------------------------------------------------------------
//!Area identifiers of SVL for Device_0
#define NVM_POFF_SVL_AREA_ID_BD_LMTD        ((U8) 0x00)     //!< Device-0, Area-0
#define NVM_POFF_SVL_AREA_ID_NVM            ((U8) 0x01)     //!< Device-0, Area-1
#define NVM_POFF_SVL_AREA_ID_BCM_COMO       ((U8) 0x02)     //!< Device-0, Area-2

//! Area sizes of SVL for Device_0
#define NVM_POFF_SVL_AREA_SIZE_BD_LMTD      ((U32) BCM_LMTD_POFF_SIZE)    //!< Size of POFF data for BD LMTD
#define NVM_POFF_SVL_AREA_SIZE_NVM          ((U32) NVM_CFG_POFF_SIZE)     //!< Size of POFF data for NVM CFG
#define NVM_POFF_SVL_AREA_SIZE_BCM_COMO     ((U32) sizeof(C_BCM_COMO_NVM_OPCNT))   //!< Size of POFF data for BCM_COMO
#define NVM_SVL_AREA_SIZE0_RES_APP          ((U32) 0x0C00)                //!< 3kB, Reserved APP area size

//! Area offset of SVL for Device_0
#define NVM_SVL_AREA_OFFSET0_0              ((U32) 0x0000)  //!< Device-0, First area offset
#define NVM_SVL_AREA_OFFSET0_1              ((U32) (NVM_SVL_AREA_OFFSET0_0 + NVM_POFF_SVL_AREA_SIZE_BD_LMTD))

#define NVM_SVL_AREA_OFFSET0_2              ((U32) (NVM_SVL_AREA_OFFSET0_1 + NVM_POFF_SVL_AREA_SIZE_NVM))
#define NVM_SVL_AREA_OFFSET0_RES_APP        ((U32) (NVM_SVL_AREA_OFFSET0_2 + NVM_POFF_SVL_AREA_SIZE_BCM_COMO))

// End of Device_0 definitions------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
//! SVL area definitions of Device_1, i.e. FRAM
//----------------------------------------------------------------------------------------------------------------------
//! Area identifiers of SVL for Device_1
// Note: Define area identifiers for Device_1 here
#define NVM_SVL_AREA_ID1_SPARE              ((U8) 0x00)          //!< Device-1, Spare memory for SVL areas

//! Area sizes of SVL for Device_1
// Note: This is spare area size provided as an example, board owner can use this memory area
#define NVM_SVL_AREA_SIZE1_SPARE            ((U32) 0x9800)        //!< Device-1, Spare memory for SVL areas
#define NVM_SVL_AREA_SIZE1_RES_APP          ((U32) 0x14000)       //!< Device-1, Reserved APP area size

//! Area offset of SVL for Device_1
#define NVM_SVL_AREA_OFFSET1_SPARE          ((U32) 0x0000)        //!< Device-1, Reserved APP area offset
#define NVM_HAL_AREA_OFFSET1_RES_APP        ((U32)(NVM_SVL_AREA_OFFSET1_SPARE + NVM_SVL_AREA_SIZE1_SPARE))
                                                                  //!< Device-1, Second area offset

// End of Device_1 definitions------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
//! SVL area definitions of Device_2, i.e. FLASH
//----------------------------------------------------------------------------------------------------------------------
//! Area identifiers of SVL for Device_2
// Note: Define area identifiers for Device_2 here
// There are no SVL areas for this device

//! Area size of SVL for Device_2
#define NVM_SVL_AREA_SIZE2_RES_APP          ((U32) 0xC000)        //!< Device-2, Reserved APP area size

//! Area offset of SVL for Device_2
#define NVM_SVL_AREA_OFFSET2_RES_APP        ((U32) 0x0000)        //!< Device-2, First area offset

// End of Device_2 definitions------------------------------------------------------------------------------------------

// NonFWR area ID for SVL
#define NVM_POFF_NONFWR_AREA_ID_SVL         NVM_POFF_NONFWRAREA_IDX_SVL

// Size of POFF data for SVL
#define NVM_POFF_NONFWR_AREA_SIZE_SVL       ((U32) 1024)

// NonFWR area ID for APP
#define NVM_POFF_NONFWR_AREA_ID_USR         NVM_POFF_NONFWRAREA_IDX_USR

// Size of POFF data for APP
#define NVM_POFF_NONFWR_AREA_SIZE_USR       ((U32) 3072)

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************
//! Operation Queue Handling structure for device 0
C_NVM_SVL_OPERATION_QUEUE acNVM_SVL_OperationQueue_Device0[NVM_SVL_CFG_MAX_QUEUE_ENTRIES]; // @suppress("Avoid Global Variables")

//! Operation Queue Handling structure for device1
C_NVM_SVL_OPERATION_QUEUE acNVM_SVL_OperationQueue_Device1[NVM_SVL_CFG_MAX_QUEUE_ENTRIES]; // @suppress("Avoid Global Variables")

//! Operation Queue Handling structure for device2
C_NVM_SVL_OPERATION_QUEUE acNVM_SVL_OperationQueue_Device2[NVM_SVL_CFG_MAX_QUEUE_ENTRIES]; // @suppress("Avoid Global Variables")

//! Operation Queue Handling structure for device3
C_NVM_SVL_OPERATION_QUEUE acNVM_SVL_OperationQueue_Device3[NVM_SVL_CFG_MAX_QUEUE_ENTRIES]; // @suppress("Avoid Global Variables")

//! Operation Queue Handling structure for device4
C_NVM_SVL_OPERATION_QUEUE acNVM_SVL_OperationQueue_Device4[NVM_SVL_CFG_MAX_QUEUE_ENTRIES]; // @suppress("Avoid Global Variables")

//! Operation Queue Handling structure for device5
C_NVM_SVL_OPERATION_QUEUE acNVM_SVL_OperationQueue_Device5[NVM_SVL_CFG_MAX_QUEUE_ENTRIES]; // @suppress("Avoid Global Variables")

//! Operation Queue Handling structure for device6
C_NVM_SVL_OPERATION_QUEUE acNVM_SVL_OperationQueue_Device6[NVM_SVL_CFG_MAX_QUEUE_ENTRIES]; // @suppress("Avoid Global Variables")

//! Operation Queue Handling structure for device7
C_NVM_SVL_OPERATION_QUEUE acNVM_SVL_OperationQueue_Device7[NVM_SVL_CFG_MAX_QUEUE_ENTRIES]; // @suppress("Avoid Global Variables")


//! POFF data for NVM, used in nvm.c,
// Note: defined here because, No.of devices macro cannot be used in nvm.c
C_NVM_POFF_DATA acNVM_PoffData[NVM_SVL_NUM_OF_CONFIG_DEVICES]; // @suppress("Avoid Global Variables")

//Note: Suppression of "Avoid Global Variables", the scope of these variables is global and must therefore be declared
//      as such
//**************************************** Global constant definitions ( const ) ***************************************
//! Note: Please add 'AreaID' in sequential manner like 0,1,2...Don't give random numbers
//! SVL area configuration for POFF device
static const C_NVM_SVL_DEVICE_AREAS acNVM_SVL_Device_0[] =
{
    // Area ID,                       Area Offset,                  Area Size
    { NVM_POFF_SVL_AREA_ID_BD_LMTD, NVM_SVL_AREA_OFFSET0_0,       NVM_POFF_SVL_AREA_SIZE_BD_LMTD  },
    { NVM_POFF_SVL_AREA_ID_NVM,     NVM_SVL_AREA_OFFSET0_1,       NVM_POFF_SVL_AREA_SIZE_NVM      },
    { NVM_POFF_SVL_AREA_ID_BCM_COMO,  NVM_SVL_AREA_OFFSET0_2,       NVM_POFF_SVL_AREA_SIZE_BCM_COMO },
    { NVM_APP_AREA_ID_RES,          NVM_SVL_AREA_OFFSET0_RES_APP, NVM_SVL_AREA_SIZE0_RES_APP      }
};

//! SVL area configuration for FRAM
static const C_NVM_SVL_DEVICE_AREAS acNVM_SVL_Device_1[] =
{
    // Area ID,                       Area Offset,                  Area Size
    { NVM_SVL_AREA_ID1_SPARE,         NVM_SVL_AREA_OFFSET1_SPARE,   NVM_SVL_AREA_SIZE1_SPARE       },  //!< Reserved
    { NVM_APP_AREA_ID_RES,            NVM_HAL_AREA_OFFSET1_RES_APP, NVM_SVL_AREA_SIZE1_RES_APP     }   //!< Reserved
};

//! SVL area configuration for FLASH
static const C_NVM_SVL_DEVICE_AREAS acNVM_SVL_Device_2[] =
{
    // Area ID,                       Area Offset,                  Area Size
    { NVM_APP_AREA_ID_RES,            NVM_SVL_AREA_OFFSET2_RES_APP, NVM_SVL_AREA_SIZE2_RES_APP     }   //!< Reserved
};

//! This table configures 'Device area configuration' & 'number of areas' per device,
//! Detailed configuration per device shall be part of table-'cNVM_SVL_Device_xx', as per format above
const C_NVM_SVL_DEVICE_INFO_TABLE acNVM_SVL_DeviceTable[] =
{
//! Device Structure, No.of areas per device
    {
        NVM_DEVICE_ID0,                     // NVM Device Id
        acNVM_SVL_Device_0,                 // Area configuration structure
        ((U8) (sizeof(acNVM_SVL_Device_0) / sizeof(C_NVM_SVL_DEVICE_AREAS))),   // No.of configured areas
        NVM_SVL_CFG_VERS_DEV_0              // Configuration version
    },
    {
        NVM_DEVICE_ID1,                     // NVM Device Id
        acNVM_SVL_Device_1,                 // Area configuration structure
        ((U8) (sizeof(acNVM_SVL_Device_1) / sizeof(C_NVM_SVL_DEVICE_AREAS))),   // No.of configured areas
        NVM_SVL_CFG_VERS_DEV_1              // Configuration version
    },
    {
        NVM_DEVICE_ID2,                     // NVM Device Id
        acNVM_SVL_Device_2,                 // Area configuration structure
        ((U8) (sizeof(acNVM_SVL_Device_2) / sizeof(C_NVM_SVL_DEVICE_AREAS))),   // No.of configured areas
        NVM_SVL_CFG_VERS_DEV_2              // Configuration version
    }
};

//! Cyclic operation time slice.
//! Note: User shall update this array, based on configured NVM device
const E_OS_SLICES aeNVM_CyclicOperationTimeSlice[NVM_MAX_CONFIG_DEVICES] =
{   eOS_SLICE_10MS,
    eOS_SLICE_10MS,
    eOS_SLICE_10MS,
    eOS_SLICE_10MS,
    eOS_SLICE_10MS,
    eOS_SLICE_10MS,
    eOS_SLICE_10MS,
    eOS_SLICE_10MS
};
//! Maximum number of entries in operation queue
const U8 u8NVM_SVL_MaxEntriesInQueue = NVM_SVL_CFG_MAX_QUEUE_ENTRIES;

//! First area id of Application area
const U8 u8NVM_SVL_AppFirstAreaID = NVM_APP_AREA_ID_RES;
//----------------------------------------------------------------------------------------------------------------------
//! Unique Area Identifiers
//----------------------------------------------------------------------------------------------------------------------
//! SVL area ID for BD LMTD
BCM_POFF_AREA_ID_LMTD_SET ( NVM_POFF_SVL_AREA_ID_BD_LMTD )

//! SVL area ID for NVM OWN POFF data
NVM_OWN_POFF_AREA_ID_SET ( NVM_POFF_SVL_AREA_ID_NVM )
//! SVL area ID for BCM_COMO POFF data
BCM_NVM_AREA_ID_COMO_SET ( NVM_POFF_SVL_AREA_ID_BCM_COMO )
//----------------------------------------------------------------------------------------------------------------------

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *******************************************************************************************************

//** EndOfFile cfg_nvm.c ***********************************************************************************************
