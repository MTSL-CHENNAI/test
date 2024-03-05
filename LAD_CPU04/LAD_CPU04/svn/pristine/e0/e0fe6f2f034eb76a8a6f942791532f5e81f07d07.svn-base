//**********************************************************************************************************************
//
//                                            diag_sdi_cmd_hndlr_s.h
//
//**********************************************************************************************************************
//
//                                      Copyrights(c) 2022 by KNORR-BREMSE,
//                                        Rail Vehicle Systems, Munich
//
//! @project CBK
//! @date 2019-03-06
//! @author A. Mauro
//!
//**********************************************************************************************************************
//!
//! @file   diag_sdi_cmd_hndlr_s.h
//! @brief  DIAG Interface functions for SDI commands.
//!
//**********************************************************************************************************************
//
// History
// Date         Author         Changes
// 2019-03-06   A. Mauro       Start
// 2022-11-28   J. Lulli       Coding guidelines alignment
//**********************************************************************************************************************
#ifndef DIAG_SDI_CMD_HNDLR_S_H
#define DIAG_SDI_CMD_HNDLR_S_H

//**************************************** Header / include files ( #include ) *****************************************
#include "kb_types.h"                                   // Standard definitions
#include "sdi.h"                                        // SDI configuration structure
//**************************************** Constant / macro definitions ( #define ) ************************************

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data declarations ( extern ) *****************************************

//**************************************** External parameter / constant declarations ( extern const )  ****************
extern const C_SDI_CFG_FCTN_TAB cDIAG_SDI_CfgFctnTab;             //!< SDI scheduling table for DIAG Service

//**************************************** Global func/proc prototypes *************************************************

// Function s16SDI_Diag_get_DS
//**********************************************************************************************************************
//! @brief          Command handler function to get the diagnostics status
//!
//! @details        -
//!
//! @param[in]      pu8RequestBuffer
//! @param[in]      u16RequestSize
//! @param[in]      pu8ResponseBuffer
//! @param[in]      u16MaxResponseSize
//! @param[in,out]  -
//!
//!
//! @return         Size of the output data written to pu8DataOut.
//!                 If Success :SDI_DIAG_OK
//!                 If failure :SDI_DIAG_ERROR
//!
//! @remarks        pu8DataIn gives details of expected command input for this command handler.
//!                 pu8DataOut gives details of command response for this command handler
//**********************************************************************************************************************
extern S16 s16SDI_Diag_get_DS(U8* pu8RequestBuffer, U16 u16RequestSize, U8* pu8ResponseBuffer, U16 u16MaxResponseSize);

// Function s16SDI_Diag_get_F
//**********************************************************************************************************************
//! @brief          Command handler function to get fault
//!
//! @details        -
//!
//! @param[in]      pu8RequestBuffer
//! @param[in]      u16RequestSize
//! @param[in]      pu8ResponseBuffer
//! @param[in]      u16MaxResponseSize
//!
//!
//! @return         Size of the output data written to pu8DataOut.
//!                 If Success :SDI_DIAG_OK
//!                 If failure :SDI_DIAG_ERROR
//!
//! @remarks        pu8DataIn gives details of expected command input for this command handler.
//!                 pu8DataOut gives details of command response for this command handler
//**********************************************************************************************************************
extern S16 s16SDI_Diag_get_F(U8* pu8RequestBuffer, U16 u16RequestSize, U8* pu8ResponseBuffer, U16 u16MaxResponseSize);

// Function s16SDI_Diag_get_Deg
//**********************************************************************************************************************
//! @brief          Command handler function to get degraded
//!
//! @details        -
//!
//! @param[in]      pu8RequestBuffer
//! @param[in]      u16RequestSize
//! @param[in]      pu8ResponseBuffer
//! @param[in]      u16MaxResponseSize
//!
//! @return         Size of the output data written to pu8DataOut.
//!                 If Success :SDI_DIAG_OK
//!                 If failure :SDI_DIAG_ERROR
//!
//! @remarks        pu8DataIn gives details of expected command input for this command handler.
//!                 pu8DataOut gives details of command response for this command handler
//**********************************************************************************************************************
extern S16 s16SDI_Diag_get_Deg(U8* pu8RequestBuffer, U16 u16RequestSize, U8* pu8ResponseBuffer, U16 u16MaxResponseSize);

// Function s16SDI_Diag_get_RC
//**********************************************************************************************************************
//! @brief          Command handler function to get Diag root cause
//!
//! @details        -
//!
//! @param[in]      pu8RequestBuffer
//! @param[in]      u16RequestSize
//! @param[in]      pu8ResponseBuffer
//! @param[in]      u16MaxResponseSize
//!
//! @return         Size of the output data written to pu8DataOut.
//!                 If Success :SDI_DIAG_OK
//!                 If failure :SDI_DIAG_ERROR
//!
//! @remarks        pu8DataIn gives details of expected command input for this command handler.
//!                 pu8DataOut gives details of command response for this command handler
//**********************************************************************************************************************
extern S16 s16SDI_Diag_get_RC(U8* pu8RequestBuffer, U16 u16RequestSize, U8* pu8ResponseBuffer, U16 u16MaxResponseSize);

// Function s16SDI_Diag_clear_DS
//**********************************************************************************************************************
//! @brief          Command handler function to clear diagnostic state
//!
//! @details        -
//!
//! @param[in]      pu8RequestBuffer
//! @param[in]      u16RequestSize
//! @param[in]      pu8ResponseBuffer
//! @param[in]      u16MaxResponseSize
//!
//! @return         Size of the output data written to pu8DataOut.
//!                 If Success :SDI_DIAG_OK
//!                 If failure :SDI_DIAG_ERROR
//!
//! @remarks        pu8DataIn gives details of expected command input for this command handler.
//!                 pu8DataOut gives details of command response for this command handler
//**********************************************************************************************************************
extern S16 s16SDI_Diag_clear_DS(U8* pu8RequestBuffer, U16 u16RequestSize,
                                U8* pu8ResponseBuffer, U16 u16MaxResponseSize);

// Function s16SDI_Diag_sim_DS
//**********************************************************************************************************************
//! @brief          Command handler function to simulate a diagnostic state
//!
//! @details        -
//!
//! @param[in]      pu8RequestBuffer
//! @param[in]      u16RequestSize
//! @param[in]      pu8ResponseBuffer
//! @param[in]      u16MaxResponseSize
//!
//! @return         Size of the output data written to pu8DataOut.
//!                 If Success :SDI_DIAG_OK
//!                 If failure :SDI_DIAG_ERROR
//!
//! @remarks        pu8DataIn gives details of expected command input for this command handler.
//!                 pu8DataOut gives details of command response for this command handler
//**********************************************************************************************************************
extern S16 s16SDI_Diag_sim_DS(U8* pu8RequestBuffer, U16 u16RequestSize, U8* pu8ResponseBuffer, U16 u16MaxResponseSize);

// Function s16SDI_Diag_stop_restart
//**********************************************************************************************************************
//! @brief          Command handler function to stop\restart diagnostic
//!
//! @details        -
//!
//! @param[in]      pu8RequestBuffer
//! @param[in]      u16RequestSize
//! @param[in]      pu8ResponseBuffer
//! @param[in]      u16MaxResponseSize
//!
//! @return         Size of the output data written to pu8DataOut.
//!                 If Success :SDI_DIAG_OK
//!                 If failure :SDI_DIAG_ERROR
//!
//! @remarks        pu8DataIn gives details of expected command input for this command handler.
//!                 pu8DataOut gives details of command response for this command handler
//**********************************************************************************************************************
extern S16 s16SDI_Diag_stop_restart(U8* pu8RequestBuffer, U16 u16RequestSize,
                                    U8* pu8ResponseBuffer, U16 u16MaxResponseSize);

// Function s16SDI_Diag_freeze_unfreeze
//**********************************************************************************************************************
//! @brief          Command handler function to freeze\un-freeze diagnostic
//!
//! @details        -
//!
//! @param[in]      pu8RequestBuffer
//! @param[in]      u16RequestSize
//! @param[in]      pu8ResponseBuffer
//! @param[in]      u16MaxResponseSize
//!
//! @return         Size of the output data written to pu8DataOut.
//!                 If Success :SDI_DIAG_OK
//!                 If failure :SDI_DIAG_ERROR
//!
//! @remarks        pu8DataIn gives details of expected command input for this command handler.
//!                 pu8DataOut gives details of command response for this command handler
//**********************************************************************************************************************
extern S16 s16SDI_Diag_freeze_unfreeze(U8* pu8RequestBuffer, U16 u16RequestSize,
                                       U8* pu8ResponseBuffer, U16 u16MaxResponseSize);

// Function s16SDI_Diag_MasterClear
//**********************************************************************************************************************
//! @brief          Command handler function to Master Clear command
//!
//! @details        -
//!
//! @param[in]      pu8RequestBuffer
//! @param[in]      u16RequestSize
//! @param[in]      pu8ResponseBuffer
//! @param[in]      u16MaxResponseSize
//!
//! @return         Size of the output data written to pu8DataOut.
//!                 If Success :SDI_DIAG_OK
//!                 If failure :SDI_DIAG_ERROR
//!
//! @remarks        pu8DataIn gives details of expected command input for this command handler.
//!                 pu8DataOut gives details of command response for this command handler
//**********************************************************************************************************************
extern S16 s16SDI_Diag_MasterClear(U8* pu8RequestBuffer, U16 u16RequestSize,
                                   U8* pu8ResponseBuffer, U16 u16MaxResponseSize);

#endif
//** EndOfFile diag_sdi_cmd_hndlr_s.h **********************************************************************************
