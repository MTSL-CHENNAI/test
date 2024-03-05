//**********************************************************************************************************************
//
//                                               cfg_ccc_rom.c
//
//**********************************************************************************************************************
//
//                                         Copyrights(c) by KNORR-BREMSE,
//                                        Rail Vehicle Systems, Munich
//
//! @project CBK
//! @date    2020-05-15
//! @author  A. Gatare
//!
//**********************************************************************************************************************
//!
//! @file cfg_ccc_rom.c
//! @brief Contain a board specific ROM segment configurations.
//!
//**********************************************************************************************************************
//
// History
// Date         Author            Changes
// 2020-11-27   A. Gatare          Start. Adapted for GenCA 6.11
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "ccc_rom_i.h"
//**************************************** Constant / macro definitions ( #define ) ************************************
//!Start address of ROM memory
#define CCC_ROM_START_ADDRESS_MEMORY  0x00000000UL

//! End address of ROM memory
#define CCC_ROM_END_ADDRESS_MEMORY    0x00100000UL
//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************

//! Memory range configuration table for flash devices available on the ESRA board.
const C_CCC_ROM_CFG_FLASH_MEM_RANGE cCCC_RomCfgMemoryRange =
{
    // Flash memory range configuration flash device
    CCC_ROM_START_ADDRESS_MEMORY,  //!< Base address of flash memory.
    CCC_ROM_END_ADDRESS_MEMORY   //!< End address of intern flash memory.
};
//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfFile cfg_ccc_rom.c*********************************************************************************
