//**********************************************************************************************************************
//
//                                            cfg_ccc_ram.c
//
//**********************************************************************************************************************
//
//                   Copyrights(c) 2022 by KNORR-BREMSE,
//              Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   IBC
//! @date      2023-11-30
//! @author    C. Brancolini
//
//**********************************************************************************************************************
//!
//! @file
//! @brief  Board specific configuration for RAM-Devices
//!         - Configuration table for RAM devices descriptors.
//!         - Configuration table for AddOn functions descriptors.
//!
//**********************************************************************************************************************
//
// History
// Date        Author        Changes:
// 20.04.11    A. Tenkeu     Start.
// 16.01.12    A. Tenkeu     Adaption to EB01.
// 24.01.12    C. Baeuml     Modification RAM test areas.
// 08.01.13    W. Hilbk      Adress areas adapted
// 25.07.14    A. Mauro      Changed configuration
// 2023-01-09  J. Lulli      Coding guidelines alignment
// 2023-05-15  C. Brancolini Lint clean up
// 2023-11-30  C. Brancolini Lint Plus clean up
//
//**********************************************************************************************************************

//************************************** Compiler options ( #pragma ) **************************************************

//*********************************** Header / include files ( #include ) **********************************************
#include "ccchws.h"                  // Interface to firmware layer
#include "std_defs.h"

//********************************* Constant / macro definitions ( #define ) *******************************************
#define RAM_MAX_CONSEC_TEST         ((U32)2)          // Number of maximum consecutive RAM test allowed
#define RAM_TESTED_BYTES_TILL_WD    ((U32)65535)      // Number of bytes to be tested until watchdog trigger
#define RAM_NO_OF_DEVICE            ((U32)4)          // Number of RAM device

#define RAM_BOOT_START_ADDR         ((U32)0x40000000) // RAM boot segment start
#define RAM_BOOT_SEG_LENGTH         ((U32)0x00010000) // RAM boot segment length

#define RAM_CRITICAL_START_ADDR     ((U32)0x20000000) // RAM critical segment start
#define RAM_CRITICAL_SEG_LENGTH     ((U32)0x00010000) // RAM critical segment length

#define RAM_EXTDEV0_START_ADDR      ((U32)0x20000000) // RAM ext dev 0 segment start
#define RAM_EXTDEV0_SEG_LENGTH      ((U32)0x00000000) // RAM ext dev 0 segment length

#define RAM_EXTDEV1_START_ADDR      ((U32)0x20010000) // RAM ext dev 1 segment start
#define RAM_EXTDEV1_SEG_LENGTH      ((U32)0x001F0000) // RAM ext dev 1 segment length

//*************************************** Type definitions ( typedef ) *************************************************

//****************************************** Global data definitions ***************************************************

//************************************* Global constant definitions ( const ) ******************************************

//! Number of RAM test repetitions allowed
// inhibit lint message (note 9075) caused by external symbol defined without a prior declaration
// in GenMPC55xx
const U32 u32CfgNumberOfRamTestRepeatAllowed = RAM_MAX_CONSEC_TEST;  //lint !e9075

//! Number of bytes to be tested until watchdog trigger
// inhibit lint message (note 9075) caused by external symbol defined without a prior declaration
// in GenMPC55xx
const U32 u32CfgBytesToTestUntilWDog = RAM_TESTED_BYTES_TILL_WD;  //lint !e9075

//! Definition of RAM devices descriptors table
TYPEDEF_CCC_RAM_DEV_TAB( CFG, 4) // @suppress("Wrong derived data type") // @suppress("Wrong prefix for complex structures")
static const CCC_RAM_DEV_TAB( CFG ) cRamDevDescriptors = // @suppress("Wrong derived data type")
{
    RAM_NO_OF_DEVICE,        // Number of RAM Devices (field .u32NumberOfRamDev)
    //********************************************************************************/
    // Array of RAM Devices (field .cRamDevice)
    {
        {
        // RAM DEVICE: BOOT - RAM  (internal RAM)
        //***********************************************************************/
            // RAM device type (field .cRamDeviceType)
            // Inhibit lint message 708: union initialization.
            // Used .u32Raw field of .cRamDeviceType union
            //lint -save -e708
            {
                 CCC_RAM_DEV_TYPE_CONFIG( CCC_RAM_BOOT_RAM_SEG,
                                                    CCC_RAM_32BIT_RAM,
                                                    CCC_RAM_SRAM,
                                                    CCC_RAM_ECC )
            },
            //lint -restore
            RAM_BOOT_START_ADDR,   // RAM device start (field .u32RamDevStartAddress)
            RAM_BOOT_SEG_LENGTH,   // RAM device length in BYTES (field .u32RamDevLength)
        },
        {
        // RAM DEVICE: PSRAM - Critical Area  (reset safe memory)
        //***********************************************************************/
            // RAM device type (field .cRamDeviceType)
            // Inhibit lint message 708: union initialization.
            // Used .u32Raw field of .cRamDeviceType union
            //lint -save -e708
            {
                 CCC_RAM_DEV_TYPE_CONFIG( CCC_RAM_CRITICAL_RAM_SEG,
                                                    CCC_RAM_16BIT_RAM,
                                                    CCC_RAM_SRAM,
                                                    CCC_RAM_NON_ECC)
            },
            //lint -restore
            RAM_CRITICAL_START_ADDR,       // RAM device. start.
            RAM_CRITICAL_SEG_LENGTH,       // RAM device. length in BYTES.
        },
        {
        // RAM DEVICE: PSRAM  (before critical area)
        //***********************************************************************/
            // RAM device type (field .cRamDeviceType)
            // Inhibit lint message 708: union initialization.
            // Used .u32Raw field of .cRamDeviceType union
            //lint -save -e708
            {
                 CCC_RAM_DEV_TYPE_CONFIG( CCC_RAM_EXT_RAM_DEV,
                                                    CCC_RAM_16BIT_RAM,
                                                    CCC_RAM_SRAM,
                                                    CCC_RAM_NON_ECC )
            },
            //lint -restore
            RAM_EXTDEV0_START_ADDR,        // RAM device. start.
            RAM_EXTDEV0_SEG_LENGTH,        // RAM device. length in BYTES.
        },
        {
        // RAM DEVICE: PSRAM  (after critical area)
        //***********************************************************************/
            // RAM device type (field .cRamDeviceType)
            // Inhibit lint message 708: union initialization.
            // Used .u32Raw field of .cRamDeviceType union
            //lint -save -e708
            {
                 CCC_RAM_DEV_TYPE_CONFIG( CCC_RAM_EXT_RAM_DEV,
                           CCC_RAM_16BIT_RAM,
                           CCC_RAM_SRAM,
                           CCC_RAM_NON_ECC )
            },//lint -restore
            RAM_EXTDEV1_START_ADDR,         // RAM device. start.
            RAM_EXTDEV1_SEG_LENGTH          // RAM device. length in BYTES.
        }
    }
};

//! Definition of configuration table for AddOn functions descriptors
// Inhibit lint message 708: union initialization. Used .u32Raw field of .cRamDeviceType union.
//lint -save -e708
TYPEDEF_CCC_RAM_DEV_ADDON_FUNC_TAB( CFG, 1 ) // @suppress("Wrong derived data type") // @suppress("Wrong prefix for complex structures")
static const CCC_RAM_DEV_ADDON_FUNC_TAB( CFG ) cRamDevAddOnFuncDescriptors = // @suppress("Wrong derived data type")
{
    1,     // Number of AddOn functions (field .u32NrAddOnFunc) // @suppress("No magic numbers")
           // List of AddOn functions descriptor (field .cAddOnFunc)
    {
        {
            { CCC_RAM_DEF_TYPE },    // Default RAM device type (field .cRamDeviceType)
            s16CCCRAMTestDefAddOn    // Default AddOn function (field .s16CCCRAMTestAddOn)
        }
    }
};
//lint -restore

// Get the start address of the RAM devices descriptor table
// Inhibit lint message (note 9075) caused by external symbol defined without a prior declaration
// in GenMPC55xx
// Inhibit lint message (note 9005) "cast drops const qualifier" due to GenMPC55xx macro
// Inhibit lint message (note 9087) cast between pointer of different types due to GenMPC55xx macro
SET_CCC_RAM_DEV_DEF(&cRamDevDescriptors);  //lint !e9075 !e9005 !e9087  // @suppress("Wrong derived data type")

// Get the start address of the AddOn functions descriptors table
// Inhibit lint message (note 9075) caused by external symbol defined without a prior declaration
// in GenMPC55xx
// Inhibit lint message (note 9005) "cast drops const qualifier" due to GenMPC55xx macro
// Inhibit lint message (note 9087) cast between pointer of different types due to GenMPC55xx macro
SET_CCC_RAM_DEV_ADDON_FUNC_DEF(&cRamDevAddOnFuncDescriptors);  //lint !e9075 !e9005 !e9087 // @suppress("Wrong derived data type")

//************************************** Modul global data segment ( static ) ******************************************

//************************************ Modul global constants ( static const ) *****************************************

//************************************* Local func/proc prototypes ( static ) ******************************************

// EndOfFile cfg_ccc_ram.c *********************************************************************************************
