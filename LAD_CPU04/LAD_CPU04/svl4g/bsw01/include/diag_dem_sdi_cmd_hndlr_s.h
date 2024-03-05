//**********************************************************************************************************************
//
//                                            diag_dem_sdi_cmd_hndlr_s.h
//
//**********************************************************************************************************************
//
//                                       Copyrights(c) 2022 by KNORR-BREMSE,
//                                        Rail Vehicle Systems, Munich
//
//! @project CBK
//! @date 2019-03-06
//! @author A. Mauro
//!
//**********************************************************************************************************************
//!
//! @file   diag_dem_sdi_cmd_hndlr_s.h
//! @brief  DIAG_DEM Interface functions for SDI commands.
//!
//**********************************************************************************************************************
//
// History
// Date         Author         Changes
// 2019-03-06   A. Mauro       Start
// 2022-11-28   J. Lulli       Coding guidelines alignment
//**********************************************************************************************************************
#ifndef DIAG_DEM_SDI_CMD_HNDLR_S_H
#define DIAG_DEM_SDI_CMD_HNDLR_S_H

//**************************************** Header / include files ( #include ) *****************************************
#include "kb_types.h"                                   // Standard definitions
#include "sdi.h"                                        // SDI configuration structure
//**************************************** Constant / macro definitions ( #define ) ************************************

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data declarations ( extern ) *****************************************

//**************************************** External parameter / constant declarations ( extern const )  ****************
extern const C_SDI_CFG_FCTN_TAB cDIAG_DEM_SDI_CfgFctnTab;         //!< SDI scheduling table for DIAG_DEM Service

//**************************************** Global func/proc prototypes *************************************************

// Function s16SDI_Diag_get_num_entries_lad
//**********************************************************************************************************************
//! @brief          Command handler function to get Diag number entries
//!
//! @details        -
//!
//! @param[in]      pu8RequestBuffer       :   Data input to the command function. (service ID, Fault number)
//! @param[in]      u16RequestSize     :   Length of command.
//! @param[in]      pu8ResponseBuffer   :   Maximum data to write to the output.
//! @param[in]      u16MaxResponseSize
//! @param[in,out]  -
//!
//! @param[out]     pu8DataOut      : Output data passed to the SDI
//!
//! @return         Size of the output data written to pu8DataOut.
//!                 If Success :SDI_DIAG_OK
//!                 If failure :SDI_DIAG_ERROR
//!
//! @remarks        pu8DataIn gives details of expected command input for this command handler.
//!                 pu8DataOut gives details of command response for this command handler
//**********************************************************************************************************************
extern S16 s16SDI_Diag_get_num_entries_lad(U8* pu8RequestBuffer, U16 u16RequestSize,
                                           U8* pu8ResponseBuffer, U16 u16MaxResponseSize);

// Function s16SDI_Diag_get_entries_lad
//**********************************************************************************************************************
//! @brief          Command handler function to get Diag entries
//!
//! @details        -
//!
//! @param[in]      pu8RequestBuffer       :   Data input to the command function. (service ID, Fault number)
//! @param[in]      u16RequestSize     :   Length of command.
//! @param[in]      pu8ResponseBuffer   :   Maximum data to write to the output.
//! @param[in]      u16MaxResponseSize
//! @param[in,out]  -
//!
//! @param[out]     pu8DataOut      : Output data passed to the SDI
//!
//! @return         Size of the output data written to pu8DataOut.
//!                 If Success :SDI_DIAG_OK
//!                 If failure :SDI_DIAG_ERROR
//!
//! @remarks        pu8DataIn gives details of expected command input for this command handler.
//!                 pu8DataOut gives details of command response for this command handler
//**********************************************************************************************************************
extern S16 s16SDI_Diag_get_entries_lad(U8* pu8RequestBuffer, U16 u16RequestSize,
                                       U8* pu8ResponseBuffer, U16 u16MaxResponseSize);

// Function s16SDI_Diag_move_mirror_mark_lad
//**********************************************************************************************************************
//! @brief          Command handler function to clear diagnostic state
//!
//! @details        -
//!
//! @param[in]      pu8RequestBuffer       :   Data input to the command function. (service ID, Fault number)
//! @param[in]      pu8ResponseBuffer     :   Length of command.
//! @param[in]      u16RequestSize   :   Maximum data to write to the output.
//! @param[in]      u16MaxResponseSize
//! @param[in,out]  -
//!
//! @param[out]     pu8DataOut      : Output data passed to the SDI
//!
//! @return         Size of the output data written to pu8DataOut.
//!                 If Success :SDI_DIAG_OK
//!                 If failure :SDI_DIAG_ERROR
//!
//! @remarks        pu8DataIn gives details of expected command input for this command handler.
//!                 pu8DataOut gives details of command response for this command handler
//**********************************************************************************************************************
extern S16 s16SDI_Diag_move_mirror_mark_lad(U8* pu8RequestBuffer, U16 u16RequestSize,
                                            U8* pu8ResponseBuffer, U16 u16MaxResponseSize);


#endif
//** EndOfFile diag_dem_sdi_cmd_hndlr_s.h ******************************************************************************
