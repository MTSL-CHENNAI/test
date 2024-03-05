//**********************************************************************************************************************
//
//                                                  cfg_nvm_hal_poff.c
//
//**********************************************************************************************************************
//
//                                        Copyrights(c) by KNORR-BREMSE
//                                         Rail Vehicle Systems, Munich
//
//! @project   IBC
//! @date      2023-11-02
//! @author    C.Brancolini
//!
//**********************************************************************************************************************
//!
//! @file      cfg_nvm_hal_poff.c
//! @brief     This file includes Power Fail related configuration parameters.
//!
//!
//**********************************************************************************************************************
//
// History
// Date            Author              Changes
// 2019-03-20      K. Gade             Start
// 2019-07-16      K. Gade             BC0025-202: Code cleanup.
// 2023-01-09      J. Lulli            Coding guidelines alignment
// 2023-11-02      C.Brancolini        Lint Plus cleanup
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma )	************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "kb_types.h"                               // Standard definitions
#include "nvm_hal_i.h"                              // NVM device configuration dependencies
#include "nvm_common.h"                             // NVM Common definitions
#include "cfg_nvm_hal_poff_i.h"                     // POFF related definitions

//**************************************** Constant / macro definitions ( #define ) ************************************
//----------------------------------------------------------------------------------------------------------------------

// Configuration of POFF buffer blocks for writing to NVM
//----------------------------------------------------------------------------------------------------------------------
//! Number of Blocks to transfer POFF data to NVMem
#define NVM_HAL_POFF_MAX_BLOCKS         15LU

//! Macro determine maximum size of a block in U32 units
#define NVM_HAL_POFF_MAX_BLOCK_SIZE_U32  ((U32)(((NVM_HAL_POFF_BUFF_SIZE / NVM_HAL_POFF_MAX_BLOCKS)+3LU) / 4LU))

//! Macro determine size of a block in U32 units
#define NVM_HAL_POFF_SIZE_BLOCK_U32(x)                                       \
        ((x>=(NVM_HAL_POFF_MAX_BLOCKS-1LU)) ?                                \
         (NVM_HAL_POFF_MAX_BUFF_U32 - (NVM_HAL_POFF_MAX_BLOCK_SIZE_U32*x)) : \
         NVM_HAL_POFF_MAX_BLOCK_SIZE_U32)

//! Macro determine start index of a block in U32 units
#define NVM_HAL_POFF_START_BLOCK_U32(x) (NVM_HAL_POFF_MAX_BLOCK_SIZE_U32 * x)

//! macro determine max index of a block in U32 units
#define NVM_HAL_POFF_MAX_BLOCK_U32(x)   (NVM_HAL_POFF_START_BLOCK_U32(x) + NVM_HAL_POFF_SIZE_BLOCK_U32(x))

//! Block definitions for writing to NVM
#define NVM_HAL_POFF_BLOCK_DEF(x)           \
    {                                       \
      NVM_HAL_POFF_MAX_BLOCK_U32(x),        \
      NVM_HAL_POFF_SIZE_BLOCK_U32(x),       \
      NVM_HAL_POFF_START_BLOCK_U32(x)       \
    }

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************
//! Buffer for power fail data
//! note: after reset it must not be initialized.
#pragma section POFF_HW_DATA ".poffhwinits" ".poffhwuinits" // @suppress("No #pragma instructions")
#pragma use_section POFF_HW_DATA au32NVM_HAL_PoffHwBuffer // @suppress("No #pragma instructions")

//! RAM buffer for storage of POFF data
U32 au32NVM_HAL_PoffHwBuffer[NVM_HAL_POFF_BUFF_SIZE / NVM_FACTOR_FOR_U8_TO_U32]; // @suppress("Avoid Global Variables")
//Note: Suppression of "Avoid Global Variables", the scope of this variable is global and must therefore be declared as
//      such
//**************************************** Global constant definitions ( const ) ***************************************
// Start index in POFF buffer for non FWR areas
const U32 u32NVM_HAL_PoffNFwrAreaStrtIdx = NVM_HAL_POFF_BUFF_AREAS_STARTIDX_NONFWR_U32;

//! U32 index of CNT2 in POFF buffer
const U32 u32NVM_HAL_CFG_PoffCnt2Idx = NVM_HAL_POFF_BUFF_CNT2IDX_U32;

//! Max U32 index for areas in POFF buffer
const U32 u32NVM_HAL_CFG_PoffMaxAreasIdx = NVM_HAL_POFF_BUFF_AREAS_MAXIDX_U32;

//! Block definitions for writing to NVMem
const C_NVM_HAL_POFF_BLOCK_DEFS acNVM_HAL_CFG_PoffBlockDef[NVM_HAL_POFF_MAX_BLOCKS] =
{
    NVM_HAL_POFF_BLOCK_DEF(0U),
    NVM_HAL_POFF_BLOCK_DEF(1U),
    NVM_HAL_POFF_BLOCK_DEF(2U),
    NVM_HAL_POFF_BLOCK_DEF(3U),
    NVM_HAL_POFF_BLOCK_DEF(4U),
    NVM_HAL_POFF_BLOCK_DEF(5U),
    NVM_HAL_POFF_BLOCK_DEF(6U),
    NVM_HAL_POFF_BLOCK_DEF(7U),
    NVM_HAL_POFF_BLOCK_DEF(8U),
    NVM_HAL_POFF_BLOCK_DEF(9U),
    NVM_HAL_POFF_BLOCK_DEF(10U),
    NVM_HAL_POFF_BLOCK_DEF(11U),
    NVM_HAL_POFF_BLOCK_DEF(12U),
    NVM_HAL_POFF_BLOCK_DEF(13U),
    NVM_HAL_POFF_BLOCK_DEF(14U)
};

const U8 u8NVM_HAL_CFG_PoffMaxBlocks = (U8) NVM_HAL_POFF_MAX_BLOCKS;

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *******************************************************************************************************

//** EndOfFile cfg_nvm_hal_poff.c **************************************************************************************
