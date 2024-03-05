//**********************************************************************************************************************
//
//                                                  cfg_aod_sdi.c
//
//**********************************************************************************************************************
//
//                                        Copyrights(c) by KNORR-BREMSE,
//                                         Rail Vehicle Systems, Munich
//
//! @project IBC
//! @date    2023-11-21
//! @author  C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file   cfg_aod_sdi.c
//! @brief  This file contains configurations for AOD commands, which uses SDI service.
//!         New commands to be handled by SDI command interface, can be added in the configuration table.
//!
//**********************************************************************************************************************
//
// History
// Date         Author      Changes
// 2020-03-25   F. Heindl   Copied from cfg_diag_dem_sdi.c
// 2021-06-24   F. Heindl   Moved cAOD_SDI_CommandTable to cfg_aod_sdi_hndlr.c
//                          Moved cAOD_SDI_CfgFctnTab to cfg_sdi_fwk.c
//                          Now u8AOD_ActionIdsMaxBoard defines how many Action IDs are supported on this board
//                          Deleted unused TYPEDEF_SDI_FCTN_TAB
// 2023-11-21   C. Brancolini  Deleted unused constant u8AOD_InterfaceVersion
//
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "kb_types.h"                               // Standard definitions
#include "IbcSysDefs.h"                             // for IBC_DIAG_ID and IBC_DIAG_DEM_ID
#include "aod_sdi_cmd_hndlr_i.h"                    // Service handler interfaces
#include "sdi_tasks_s.h"                                // SDI tasks dependencies

//**************************************** Constant / macro definitions ( #define ) ************************************

//**************************************** Type definitions ( typedef ) ************************************************
// maximum number of action IDs supported (the limit is set by ACTION_IDS_MAX)
#define ACTION_IDS_MAX_BOARD                        ( 10U )

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************
const U8 u8AOD_ActionIdsMaxBoard = ACTION_IDS_MAX_BOARD;                //!< max. supported number of Action IDs

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *******************************************************************************************************

//** EndOfFile cfg_aod_sdi.c *******************************************************************************************
