//**********************************************************************************************************************
//
//                                          cfg_swd.c
//
//**********************************************************************************************************************
//
//                                  Copyrights(c) by KNORR-BREMSE
//                                  Rail Vehicle Systems, Munich
//
//! @project <CBK>
//! @date    2020-11-26
//! @author  A.Gatare
//!
//**********************************************************************************************************************
//!
//! @file    cfg_swd.c
//! @brief   Configuration for SWD.
//!
//! @details
//!
//**********************************************************************************************************************
//
//  History
//  Date        Author         Changes
// 2018-05-22  N. Joshi       Start
// 2018-10-29  N. Joshi       JIRA BC0025-58 - Applicaiton starts from Sector-8 instea of sector-9
// 2019-01-18  N. Joshi       Updated configuration for MPC5534
// 2019-05-07  N. Joshi       Changes related to SWD module re-structuring
// 2020-11-26  A.Gatare       Adapted for GenCA 6.11.Renamed file from cfg_bcm_fwr_swd to cfg_swd.c.
// 2021-04-13  A. Mauro       Changes for new Flash configuration:
//                            SWD_ADDR_START_0 0x00080000UL->0x00070000UL
//                            SWD_ADDR_SIZE_0 0x00080000UL->0x00090000UL
// 2022-03-25  A. Mauro       Set SWD_SEC_NUM_01 instead of SWD_SEC_NUM_02 in acSWD_SectorEraseTable
// 2023-01-09  J. Lulli       Coding guidelines alignment
//**********************************************************************************************************************

//********************************* Compiler options ( #pragma ) *******************************************************

//**************************************** Header / include files ( #include ) *****************************************

#include "swd_comm_i.h"             // SWD Communication channel internal interface
#include "swd_i.h"                  // SWD internal interface
#include "swd_prog_i.h"             // SWD Programming handler internal interface
#include "swd.h"                    // SWD definitions.
//**************************************** Constant / macro definitions ( #define ) ************************************

//! Sector erase table size
#define SWD_SECTOR_ERASE_TABLE_SIZE                     6U

#define SWD_FLASH_ADDR_TABLE_SIZE               1U

//! Maximum bytes that can be written in a single flash write operation.
#define SWD_MAX_BYTES_IN_A_FLASH_WRITE          16U

//! SWD Flash program address start.
#define SWD_ADDR_START_0             0x00080000UL
//! SWD Flash program size.
#define SWD_ADDR_SIZE_0              0x00080000UL

//! @name SWD Flash sector numbers to be erased.
//! @{
#define SWD_SEC_NUM_00               0U
#define SWD_SEC_NUM_01               1U
#define SWD_SEC_NUM_02               2U
#define SWD_SEC_NUM_03               3U
#define SWD_SEC_NUM_04               4U
#define SWD_SEC_NUM_05               5U
#define SWD_SEC_NUM_06               6U
#define SWD_SEC_NUM_07               7U
#define SWD_SEC_NUM_08               8U
#define SWD_SEC_NUM_09               9U
#define SWD_SEC_NUM_10               10U
#define SWD_SEC_NUM_11               11U
#define SWD_SEC_NUM_12               12U
#define SWD_SEC_NUM_13               13U
#define SWD_SEC_NUM_14               14U
#define SWD_SEC_NUM_15               15U
#define SWD_SEC_NUM_16               16U
#define SWD_SEC_NUM_17               17U
#define SWD_SEC_NUM_18               18U
#define SWD_SEC_NUM_19               19U
#define SWD_SEC_NUM_20               20U
#define SWD_SEC_NUM_21               21U
#define SWD_SEC_NUM_22               22U
#define SWD_SEC_NUM_23               23U
#define SWD_SEC_NUM_24               24U
#define SWD_SEC_NUM_25               25U
#define SWD_SEC_NUM_26               26U
//! @}

//! SWD Flash bank id to be erased.
#define SWD_DATA_FLSH_BANK_0         0U

//! SWD Flash bank id to be erased.
#define SWD_PROG_FLSH_BANK_1         1U

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//! Buffer for holding pending bytes remaining after current flash write operation.
U8 au8SWD_WritePendingBytesBuff[SWD_MAX_BYTES_IN_A_FLASH_WRITE]; // @suppress("Avoid Global Variables")
//Note: Suppression of "Avoid Global Variables", the scope of this variable is global and must therefore be declared as
//      such

//**************************************** Global constant definitions ( const ) ***************************************

//! Table containing Flash areas to be programmed.
const C_SWD_FLASH_ADDR_TABLE acSWD_FlashAddrTable[SWD_FLASH_ADDR_TABLE_SIZE] =
{
     // Flash Application executable Start address and Size
    { SWD_ADDR_START_0, SWD_ADDR_SIZE_0, SWD_DATA_FLSH_BANK_0 }
};


//! Table containing Flash sectors to be erased.
const C_SWD_SECTOR_ERASE_TABLE acSWD_SectorEraseTable[SWD_SECTOR_ERASE_TABLE_SIZE] =
{
    { SWD_DATA_FLSH_BANK_0, SWD_SEC_NUM_01, eFLSH_HAL_TYPE_PFLASH },
    { SWD_DATA_FLSH_BANK_0, SWD_SEC_NUM_08, eFLSH_HAL_TYPE_PFLASH },
    { SWD_DATA_FLSH_BANK_0, SWD_SEC_NUM_09, eFLSH_HAL_TYPE_PFLASH },
    { SWD_DATA_FLSH_BANK_0, SWD_SEC_NUM_10, eFLSH_HAL_TYPE_PFLASH },
    { SWD_DATA_FLSH_BANK_0, SWD_SEC_NUM_11, eFLSH_HAL_TYPE_PFLASH },
    { SWD_DATA_FLSH_BANK_0, SWD_SEC_NUM_12, eFLSH_HAL_TYPE_PFLASH }
};
//! Sector erase table size
const U8 u8SWD_SectorEraseTableSize = SWD_SECTOR_ERASE_TABLE_SIZE;

//! Flash program addresses table size
const U8 u8SWD_FlashAddrTableSize = SWD_FLASH_ADDR_TABLE_SIZE;

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *******************************************************************************************************

//** EndOfFile cfg_swd.c ***********************************************************************************************
