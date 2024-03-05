//****************************************************************************
//
//                                  cfgcan.c
//
//****************************************************************************
//
//                    Copyrights(c) 2022 by KNORR-BREMSE,
//               Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project  IBC
//! @date     2023-11-14
//! @author   C. Brancolini
//
//****************************************************************************
//
//! @file
//! @brief  MPC55xx FlexCAN Driver - Configuration (board specific)
//
//****************************************************************************
// Date        Author      Changes:
// 2009-03-20  P. Sigl     Initial revision
// 2009-08-05  P. Sigl     Pad attributes added
// 2009-09-28  P. Sigl     Prepared for Doxygen
// 2010-08-27  P. Sigl     CB12A specific version
// 2011-05-31  P. Sigl     Pad attributes based on 55xxsiu.h
// 2011-10-21  P. Sigl     Allow pad configuration to be done by SIU
//                         manager alternatively.
// 2012-10-29  P. Sigl     Doxygen comment corrected
// 2014-05-14  P. Sigl     warnings checked and (most of them) removed.
// 2015-05-12  KH Duemer   cleanup(Lint 9 / MISRA 2012)
// 2015-10-20  P. Sigl     FlexCAN configuration added.
// 2016-05-10  S.Patapati  Adapted for CPU05 board
// 2018-06-08  A. Mauro    Adapted for CPU04 board
// 2019-05-06  V.Ingulkar  Updates done as per core asset update v6.0
// 2020-02-14  A. Mauro    Lint clean ups
// 2020-10-29  A. Mauro    Lint clean ups
// 2023-01-09  J. Lulli    Coding guidelines alignment
// 2023-12-14  C. Brancolini Lint Plus clean up
//****************************************************************************

//******************* Compiler options ( #pragma ) ***************************

//******************* Header / include files ( #include ) ********************

#include "55xxsiu.h"                    // for pad configuration

#include "55xcan.h"                     // CAN device driver interface
#include "can_common.h"
//******************* Macro defines / fixed constants ( #define ) ************
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
//******************* Constant / parameter ( #define ) ***********************

//******************* Type definitions ( typedef ) ***************************

//******************* Global scope data definitions **************************

//******************* Global scope read only definitions ( const ) ***********

//****************************************************************************
//! Default FlexCAN configuration data for LADxxx
//****************************************************************************
const tcCFG_CAN55x cCFG_CAN55x = // @suppress("Wrong derived data type")

{
// ==== FlexCAN modules ====================================================
// Note: Use macro CAN_MODULE_NOT_AVAILABLE for configuration of not
// available FlexCAN modules.

CAN_NO_FLEX_MODULES,// Number of FlexCAN modules

{
    // ---------------- ESRA system bus --------------------------------------
    // FlexCAN 0, max. 64 Mbx, NET 0, optional bits (BOFREC, !LOM_BIT)
    // inhibit lint message (note 923) caused by address to void pointer conversion needed for memory mapped IO access
    { CAN_A_PTR, CAN_MAILBOXES_NUMBER, eCAN_NET_0, eBOFFREC_BIT }, //lint !e923

    // ---------------- IBC bus ----------------------------------------------
    // FlexCAN 1, max. 64 Mbx, NET 1, optional bits (BOFREC, !LOM_BIT)
    { CAN_C_PTR, CAN_MAILBOXES_NUMBER, eCAN_NET_1, eBOFFREC_BIT }, //lint !e923

    // ---------------- not available ----------------------------------------
    CAN_MODULE_NOT_AVAILABLE,   // FlexCAN 2
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
CAN_TESTCASE_NUMBER,// Number of test cases

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


//****************************************************************************
//! @name Test FlexCAN configuration data for LADxx
//****************************************************************************
//@{

//----------------------------------------------------------------------------
// FlexCAN configuration for production test
//
// If a production test configuration is required, which is different to the
// default configuration (cCFG_CAN55x), provide it by cCFG_CAN55x_Test.
// Note: The configuration for production test must at least contain a
//       configuration of the FlexCAN modules used in default configuration.
//       It may contain a configuration of additional FlexCAN modules, which
//       are not used in default configuration, though.
//----------------------------------------------------------------------------
// const tcCFG_CAN55x cCFG_CAN55x_Test = { test config  };

//----------------------------------------------------------------------------
// Pointer to FlexCAN configuration for production test
//
// Use &cCFG_CAN55x_Test, if a production test configuration is provided,
// which differs from the default configuration (cCFG_CAN55x).
// Use NULL otherwise.
//----------------------------------------------------------------------------
const tcCFG_CAN55x* pcCFG_CAN55x_Test = NULL; // @suppress("Wrong derived data type")
//Note: Suppression of "Wrong derived data type", this warning comes from the naming convention violation oftcCFG_CAN55x

//@}
//****************************************************************************


//****************************************************************************
//!                       Pad configuration
//****************************************************************************
const BOOLEAN boCANHwConfPad = TRUE;    //!< - TRUE: Driver will do pad
                                        //!<   configuration according to
                                        //!<   configured values (FlexCAN SIU
                                        //!<   PCR, Pad attributes).
                                        //!< - FALSE: External SW will do pad
                                        //!<   configuration (e.g. SIU manager)


//****************************************************************************
//! @name FlexCAN SIU PCR
//
//! Valid values are only required for FlexCAN controllers configured in
//! #cCFG_CAN55x.
//****************************************************************************
//@{

const U16 u16CAN_A_TX_PCR = 83U;        // FlexCAN A TX pin // @suppress("No magic numbers")
const U16 u16CAN_A_RX_PCR = 84U;        // FlexCAN A RX pin // @suppress("No magic numbers")

const U16 u16CAN_B_TX_PCR = 85U;         // FlexCAN B TX pin // @suppress("No magic numbers")
const U16 u16CAN_B_RX_PCR = 86U;         // FlexCAN B RX pin // @suppress("No magic numbers")

const U16 u16CAN_C_TX_PCR = 87U;         // FlexCAN C TX pin // @suppress("No magic numbers")
const U16 u16CAN_C_RX_PCR = 88U;         // FlexCAN C RX pin // @suppress("No magic numbers")

const U16 u16CAN_D_TX_PCR = 193U;        // FlexCAN D TX pin // @suppress("No magic numbers")
const U16 u16CAN_D_RX_PCR = 194U;        // FlexCAN D RX pin // @suppress("No magic numbers")

const U16 u16CAN_E_TX_PCR = 201U;        // FlexCAN E TX pin // @suppress("No magic numbers")
const U16 u16CAN_E_RX_PCR = 202U;        // FlexCAN E RX pin // @suppress("No magic numbers")

//Note: Suppression of "No magic numbers", adding define for all of these GPIO would not be useful

//@}
//****************************************************************************


//****************************************************************************
//! @name Pad attributes
//
//! Valid values are only required for FlexCAN controllers configured in
//! #cCFG_CAN55x.
//****************************************************************************
//@{

const U16 u16CAN_A_TX_pad_attr =
                   SIU_PCR_PA_PRIMARY_FUNCTION  |
                   SIU_OUTPUT_BUFFER_DISABLE    |
                   SIU_INPUT_BUFFER_DISABLE     |
                   SIU_INPUT_HYSTERESIS_DISABLE |
                   SIU_MINIMUM_SLEW_RATE        |
                   SIU_WEAK_PULL_ENABLE         |
                   SIU_WEAK_PULL_UP;

const U16 u16CAN_A_RX_pad_attr =
                   SIU_PCR_PA_PRIMARY_FUNCTION  |
                   SIU_OUTPUT_BUFFER_DISABLE    |
                   SIU_INPUT_BUFFER_DISABLE     |
                   SIU_INPUT_HYSTERESIS_DISABLE |
                   SIU_MINIMUM_SLEW_RATE        |
                   SIU_WEAK_PULL_ENABLE         |
                   SIU_WEAK_PULL_UP;

const U16 u16CAN_B_TX_pad_attr =
                   SIU_PCR_PA_PRIMARY_FUNCTION  |
                   SIU_OUTPUT_BUFFER_DISABLE    |
                   SIU_INPUT_BUFFER_DISABLE     |
                   SIU_INPUT_HYSTERESIS_DISABLE |
                   SIU_MINIMUM_SLEW_RATE        |
                   SIU_WEAK_PULL_ENABLE         |
                   SIU_WEAK_PULL_UP;

const U16 u16CAN_B_RX_pad_attr =
                   SIU_PCR_PA_PRIMARY_FUNCTION  |
                   SIU_OUTPUT_BUFFER_DISABLE    |
                   SIU_INPUT_BUFFER_DISABLE     |
                   SIU_INPUT_HYSTERESIS_DISABLE |
                   SIU_MINIMUM_SLEW_RATE        |
                   SIU_WEAK_PULL_ENABLE         |
                   SIU_WEAK_PULL_UP;

const U16 u16CAN_C_TX_pad_attr =
                   SIU_PCR_PA_PRIMARY_FUNCTION  |
                   SIU_OUTPUT_BUFFER_DISABLE    |
                   SIU_INPUT_BUFFER_DISABLE     |
                   SIU_INPUT_HYSTERESIS_DISABLE |
                   SIU_MINIMUM_SLEW_RATE        |
                   SIU_WEAK_PULL_ENABLE         |
                   SIU_WEAK_PULL_UP;

const U16 u16CAN_C_RX_pad_attr =
                   SIU_PCR_PA_PRIMARY_FUNCTION  |
                   SIU_OUTPUT_BUFFER_DISABLE    |
                   SIU_INPUT_BUFFER_DISABLE     |
                   SIU_INPUT_HYSTERESIS_DISABLE |
                   SIU_MINIMUM_SLEW_RATE        |
                   SIU_WEAK_PULL_ENABLE         |
                   SIU_WEAK_PULL_UP;

const U16 u16CAN_D_TX_pad_attr =
                   SIU_PCR_PA_PRIMARY_FUNCTION  |
                   SIU_OUTPUT_BUFFER_DISABLE    |
                   SIU_INPUT_BUFFER_DISABLE     |
                   SIU_INPUT_HYSTERESIS_DISABLE |
                   SIU_MINIMUM_SLEW_RATE        |
                   SIU_WEAK_PULL_ENABLE         |
                   SIU_WEAK_PULL_UP;

const U16 u16CAN_D_RX_pad_attr =
                   SIU_PCR_PA_PRIMARY_FUNCTION  |
                   SIU_OUTPUT_BUFFER_DISABLE    |
                   SIU_INPUT_BUFFER_DISABLE     |
                   SIU_INPUT_HYSTERESIS_DISABLE |
                   SIU_MINIMUM_SLEW_RATE        |
                   SIU_WEAK_PULL_ENABLE         |
                   SIU_WEAK_PULL_UP;

const U16 u16CAN_E_TX_pad_attr =
                   SIU_PCR_PA_PRIMARY_FUNCTION  |
                   SIU_OUTPUT_BUFFER_DISABLE    |
                   SIU_INPUT_BUFFER_DISABLE     |
                   SIU_INPUT_HYSTERESIS_DISABLE |
                   SIU_MINIMUM_SLEW_RATE        |
                   SIU_WEAK_PULL_ENABLE         |
                   SIU_WEAK_PULL_UP;

const U16 u16CAN_E_RX_pad_attr =
                   SIU_PCR_PA_PRIMARY_FUNCTION  |
                   SIU_OUTPUT_BUFFER_DISABLE    |
                   SIU_INPUT_BUFFER_DISABLE     |
                   SIU_INPUT_HYSTERESIS_DISABLE |
                   SIU_MINIMUM_SLEW_RATE        |
                   SIU_WEAK_PULL_ENABLE         |
                   SIU_WEAK_PULL_UP;

//@}
//****************************************************************************


//******************* Module scope data segment ( static ) *******************

//******************* Module scope read only variables ( static const ) ******

//******************* Module scope func/proc prototypes ( static ) ***********

//** EndOfHeader *************************************************************

//** EndOfFile cfgcan.c ******************************************************
