//**********************************************************************************************************************
//
//                                                 cfg_swd_cmd_handlr.c
//
//**********************************************************************************************************************
//
//                                     Copyrights(c) 2022 by KNORR-BREMSE,
//                                        Rail Vehicle Systems, Munich
//
//! @project   IBC
//! @date      2023-11-24
//! @author    C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file cfg_bcm_fwr_tch.c
//! @brief SWD command handler Board specific configuration.
//!
//**********************************************************************************************************************
// History
// Date        Author         Changes
// 2019-01-07  N. Joshi       Start
// 2020-02-14  A. Mauro       Lint clean ups
// 2020-11-26  A.Gatare       Adapted as per GenCA 6.11. Renamed file from bcm_fwr_tch.c to cfg_swd_cmd_hndlr.c
// 2023-01-09  J. Lulli       Coding guidelines alignment
// 2023-11-24  C. Brancolini  Lint Plus clean up
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "swd_cmd_handlr_i.h"               // SWD Command Handler interface
#include "swd_comm_i.h"                     // SWD Communication channel internal interface
//**************************************** Constant / macro definitions ( #define ) ************************************

//!< TCH COMM timeout value (in milliseconds).
#define SWD_COMM_TIMEOUT                            60000UL

//! Bulk CAN Message ID.
#define SWD_BULKMSG_ID                              0x03EF8000UL

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************

//! FWR Communication timeout value (in milliseconds).
const U32 u32SWD_COMMTimeout = SWD_COMM_TIMEOUT;

//! Configuration data for TCH COMM transmit mailbox
const C_CAN_MBX_CONF cCAN_FWR_MBxTxCfg =
{
    eCAN_0, eCAN_MBX_TX, 0, eCAN_MBX_EXT, eCAN_DLC_8, CAN_ENABLE_CANID_UPDATE
};

//! Configuration data for TCH COMM receive mailbox
const C_CAN_MBX_CONF cCAN_FWR_MBxRxCfg =
{
    eCAN_0, eCAN_MBX_RX, SWD_BULKMSG_ID, eCAN_MBX_EXT, eCAN_DLC_0, CAN_ACCEPT_ALL_MESSAGES
};

//! Function BCM FWR TCH Command handler.
// inhibit lint message 2705 due to function pointer definition in GenMPC55xx
const S16 (*ps16BCM_FWR_CMDHandler)(U8* pu8DataIn, U16 u16CmdLenIn, U8* pu8DataOut, U16 u16MaxRespOut) = KB_NULL_PTR;  //lint !e2705 // @suppress("Wrongly used data type")
//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *******************************************************************************************************

//** EndOfFile cfg_swd_cmd_handlr.c ************************************************************************************
