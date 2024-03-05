//**********************************************************************************************************************
//
//                                                 cfg_can.c
//
//**********************************************************************************************************************
//
//                                     Copyrights(c) 2022 by KNORR-BREMSE,
//                                        Rail Vehicle Systems, Munich
//
//! @project   IBC
//! @date      2023-12-01
//! @author    C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file cfg_can.c
//! @brief Service CAN board specific configuration.
//!
//**********************************************************************************************************************
// History
// Date        Author         Changes
// 2016-06-10  N. Joshi       Start
// 2018-02-12  N. Joshi       Updated as per new coding guidelines
// 2023-01-09  J. Lulli       Coding guidelines alignment
// 2023-12-01  C. Brancolini  Lint Plus clean up
//
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "can_i.h"                      // Service CAN internal interface
//**************************************** Constant / macro definitions ( #define ) ************************************

//! Maximum number of supported Mailboxes.
//! (should match mailboxes specified in cfg_can_hal.c)
#define CAN_MAX_MB_COUNT            ((U16)128)

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

// Inhibit lint message 552 (external variable not accessed) and
// message 729 (external variable not explicitly initialized).
// acCAN_MBxConf is defined in this file and used to get its size,
// its fields are accessed (and initialized) in GenMPC55xx module.
//lint -save -e552 -e729

//! Array to store CAN Mailbox configurations.
C_CAN_MBX_CONF         acCAN_MBxConf[CAN_MAX_MB_COUNT]; // @suppress("Avoid Global Variables")
//! CAN Mailbox access locks.
BOOLEAN                aboCAN_MBxLock[CAN_MAX_MB_COUNT]; // @suppress("Avoid Global Variables")

//Note: Suppression of "Avoid Global Variables", the scope of these variables is global and must therefore be declared
//      as such
//**************************************** Global constant definitions ( const ) ***************************************

//! Max mailbox count
const U16 u16CAN_MaxMbxCount = (U16) sizeof(acCAN_MBxConf)/ sizeof(C_CAN_MBX_CONF);

//lint -restore

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *******************************************************************************************************

//** EndOfFile cfg_can.c ***********************************************************************************************
