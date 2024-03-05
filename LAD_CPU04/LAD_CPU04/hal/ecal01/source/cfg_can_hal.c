//**********************************************************************************************************************
//
//                                                 cfg_can_hal.c
//
//**********************************************************************************************************************
//
//                                    Copyrights(c) 2022 by KNORR-BREMSE,
//                                        Rail Vehicle Systems, Munich
//
//! @project  IBC
//! @date     2023-11-30
//! @author   C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file cfg_can_hal.c
//! @brief CAN HW board specific configuration.
//!
//**********************************************************************************************************************
// History
// Date        Author         Changes
// 2016-06-10  N. Joshi       Start
// 2016-10-06  N. Joshi       Changes done as per review comments
// 2017-03-27  N. Joshi       CAN HAL configuration updated.
// 2018-02-21  N. Joshi       Updated as per new coding guidelines
// 2018-06-13  A. Mauro       Adapted to CPU04
// 2019-05-06  V.Ingulkar     Updates done as per core asset update v6.0
// 2020-02-14  A. Mauro       Lint clean ups
// 2023-01-09  J. Lulli       Coding guidelines alignment
// 2023-11-30  C. Brancolini  Lint Plus clean up
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "can_hal_i.h"                  // CAN HAL internal interface
//**************************************** Constant / macro definitions ( #define ) ************************************

//! Maximum number of Mailboxes available on MPC55xx
#define CAN_HAL_MB_MAX                      ((U16)256)
#define CAN_NO_FLEX_MODULES                 ((U32)2)     // Number of can flex modules
#define CAN_MAILBOXES_NUMBER                ((U32)64)    // Number of mailboxes
#define CAN_TESTCASE_NUMBER                 ((U32)2)     // Number of testcase
#define CAN_FLEX_MODULE0_TX                 ((U32)0)     // TX FlexCAN module0
#define CAN_FLEX_MODULE1_TX                 ((U32)1)     // TX FlexCAN module1
#define CAN_FLEX_MODULE0_MAILBX_TX          ((U32)63)    // TX mailbox number
#define CAN_FLEX_MODULE1_MAILBX_TX          ((U32)63)    // TX mailbox number
#define CAN_FLEX_MODULE0_RX                 ((U32)1)     // RX FlexCAN module
#define CAN_FLEX_MODULE1_RX                 ((U32)0)     // RX FlexCAN module
#define CAN_FLEX_MODULE0_MAILBX_RX          ((U32)62)    // RX mailbox number
#define CAN_FLEX_MODULE1_MAILBX_RX          ((U32)62)    // RX mailbox number
#define CAN_FLEX_MODULE0_ID                 ((U32)0x100) // used CAN ID
#define CAN_FLEX_MODULE1_ID                 ((U32)0x101) // used CAN ID
#define CAN_MAILBOXES_COUNT                 ((U32)64)    // Number of mailboxes used in can
//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************
//Note: Suppression of "Avoid Global Variables", the scope of these variables is global and must therefore be declared
//      as such

// Inhibit lint message 552 (external variable not accessed) and
// message 729 (external variable not explicitly initialized).
// acCAN_HAL_MbxCfg is defined in this file and used to get its size,
// its fields are accessed (and initialized) in GenMPC55xx module.
//lint -save -e552 -e729

//! CAN HAL Mailbox configuration array
C_CAN_HAL_MBX_DES acCAN_HAL_MbxCfg[CAN_HAL_MB_MAX]; // @suppress("Avoid Global Variables")
//lint-restore

//! MPC55xx CAN controller HW configuration
tcCFG_CAN55x  cCAN_HAL_HwInit = // @suppress("Wrong derived data type") // @suppress("Avoid Global Variables")
{
    // ==== FlexCAN modules ====================================================
    // Note: Use macro CAN_MODULE_NOT_AVAILABLE for configuration of not
    // available FlexCAN modules.

    CAN_NO_FLEX_MODULES,                                    // Number of FlexCAN modules

    {
      // ---------------- ESRA system bus --------------------------------------
      // FlexCAN 0, max. 64 Mbx, NET 0, optional bits (BOFREC, !LOM_BIT)
      // inhibit lint message (note 923) caused by address to void pointer conversion needed for memory mapped IO access
      { CAN_A_PTR, CAN_MAILBOXES_NUMBER, eCAN_NET_0, eBOFFREC_BIT},  //lint !e923

      // ---------------- IBC bus ----------------------------------------------
      // FlexCAN 1, max. 64 Mbx, NET 1, optional bits (BOFREC, !LOM_BIT)
      { CAN_C_PTR, CAN_MAILBOXES_NUMBER, eCAN_NET_1, eBOFFREC_BIT},  //lint !e923

      // ---------------- not available ----------------------------------------
      CAN_MODULE_NOT_AVAILABLE,   // FlexCAN 1    CAN_MODULE_NOT_AVAILABLE,   // FlexCAN 2
      CAN_MODULE_NOT_AVAILABLE,   // FlexCAN 3
      CAN_MODULE_NOT_AVAILABLE,   // FlexCAN 4
      CAN_MODULE_NOT_AVAILABLE,   // FlexCAN 5
      CAN_MODULE_NOT_AVAILABLE,   // FlexCAN 6
      CAN_MODULE_NOT_AVAILABLE    // FlexCAN 7
    },

    // ==== CAN nets ===========================================================
    // Note: Use macro CAN_NET_NOT_AVAILABLE for configuration of not available
    // CAN nets.
    {
      // ---------------- ESRA system bus --------------------------------------
        eCAN_500kb_80MHz,                   // Bus characteristics CAN NET 0

        // ---------------- IBC bus ----------------------------------------------
        eCAN_500kb_80MHz,                   // Bus characteristics CAN NET 1

      // ---------------- not available ----------------------------------------
      CAN_NET_NOT_AVAILABLE,              // Bus characteristics CAN NET 2
      CAN_NET_NOT_AVAILABLE,              // Bus characteristics CAN NET 3
      CAN_NET_NOT_AVAILABLE,              // Bus characteristics CAN NET 4
      CAN_NET_NOT_AVAILABLE,              // Bus characteristics CAN NET 5
      CAN_NET_NOT_AVAILABLE,              // Bus characteristics CAN NET 6
      CAN_NET_NOT_AVAILABLE               // Bus characteristics CAN NET 7
    },

    // ==== Loop back default test cases =======================================
    // Note: Use macro CAN_LOOPTEST_NOT_AVAILABLE for configuration of not
    // available loop test cases.
    CAN_TESTCASE_NUMBER,                                    // Number of test cases

      {
        // ---------------- ESRA system bus ------------------------------------
        {
             CAN_FLEX_MODULE0_TX, // FlexCAN0-Mbx63 => FlexCAN1-Mbx62 CAN Id 0x100
             CAN_FLEX_MODULE0_MAILBX_TX,
             CAN_FLEX_MODULE0_RX,
             CAN_FLEX_MODULE0_MAILBX_RX,
             CAN_FLEX_MODULE0_ID
        },
        {
            CAN_FLEX_MODULE1_TX, // FlexCAN1-Mbx63 => FlexCAN0-Mbx62 CAN Id 0x101
            CAN_FLEX_MODULE1_MAILBX_TX,
            CAN_FLEX_MODULE1_RX,
            CAN_FLEX_MODULE1_MAILBX_RX,
            CAN_FLEX_MODULE1_ID
        },
        // ---------------- unused ---------------------------------------------
        CAN_LOOPTEST_NOT_AVAILABLE,
        CAN_LOOPTEST_NOT_AVAILABLE,
        CAN_LOOPTEST_NOT_AVAILABLE,
        CAN_LOOPTEST_NOT_AVAILABLE,
        CAN_LOOPTEST_NOT_AVAILABLE,
        CAN_LOOPTEST_NOT_AVAILABLE
      }
};

//**************************************** Global constant definitions ( const ) ***************************************

//**********************************************************************************************************************
//! CAN configuration data
//**********************************************************************************************************************
const C_CAN_HAL_CFG cCAN_HAL_Cfg =
{
    {
        // CAN Network,           Baud rate,   MBx count
        { eCAN_0,        eCAN_500K,       CAN_MAILBOXES_COUNT},
        { eCAN_1,        eCAN_500K,       CAN_MAILBOXES_COUNT},
        { eCAN_UNUSED,   eCAN_125K,                   0UL    },
        { eCAN_UNUSED,   eCAN_125K,                   0UL    },
        { eCAN_UNUSED,   eCAN_125K,                   0UL    },
        { eCAN_UNUSED,   eCAN_125K,                   0UL    },
        { eCAN_UNUSED,   eCAN_125K,                   0UL    },
        { eCAN_UNUSED,   eCAN_125K,                   0UL    },
    },
};

// Inhibit lint message 552 (external variable not accessed) and
// message 729 (external variable not explicitly initialized).
// acCAN_HAL_MbxCfg is defined in this file and used to get its size,
// its fields are accessed (and initialized) in GenMPC55xx module.
//lint -save -e552 -e729
//! Max mailbox count
const U16 u16CAN_HAL_MbxMax = (U16) sizeof(acCAN_HAL_MbxCfg) / sizeof(C_CAN_HAL_MBX_DES);
//lint -restore

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *******************************************************************************************************

//** EndOfFile cfg_can_hal.c *******************************************************************************************
