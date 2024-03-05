//**********************************************************************************************************************
//
//                                                  cfg_sdi_fwk.c
//
//**********************************************************************************************************************
//
//                                        Copyrights(c) by KNORR-BREMSE
//                                         Rail Vehicle Systems, Munich
//
//! @project   IBC
//! @date      2023-11-21
//! @author    C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file      cfg_sdi_fwk.c
//! @brief     This file allows Framework users to configure services, which will use SDI for command execution.
//!            i.e. Service Id from 64 to 127.
//!
//**********************************************************************************************************************
//
// History
// Date            Author              Changes
// 2020-02-03      K. Gade             Start
// 2021-01-11      A.Gatare            Adapted for GenCA6.11
// 2021-10-29      A. Mauro            Added AOD and PEEK service command handling
// 2023-11-21      C. Brancolini       Lint Plus cleanup
//
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma )	************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "kb_types.h"                                   // Standard definitions
#include "cbk_def.h"                                    // Service ID definitions
#include "sdi_i.h"                                      // SDI dependencies
#include "sdi_tasks_s.h"                                // SDI tasks dependencies
#include "diag_sdi_cmd_hndlr_s.h"                       // DIAG Service Command Table
#include "diag_dem_sdi_cmd_hndlr_s.h"                   // DIAG_DEM Service Command Table
#include "aod_sdi_cmd_hndlr_s.h"                        // AOD Service Command Table
#include "peek_sdi_cmd_hndlr_s.h"                       // PEEK Service Command Table

//**************************************** Constant / macro definitions ( #define ) ************************************
//! Number of Framework Services which will be used by SDI for Command Execution
#define SDI_PLATFORM_SERVICES         ((U8)(MAX_ID_BASESERVICES + (U8) 1))

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************
//! Number of Framework services, which will be used by SDI for command execution
const U8 u8SDI_NumOfPlatformServices = SDI_PLATFORM_SERVICES;

//! Command scheduling table for DIAG Service
const C_SDI_CFG_FCTN_TAB cDIAG_SDI_CfgFctnTab =
    {
        (C_SDI_CMD_FCTN_SDI_TABLE*) (void*) &cDIAG_SDI_CommandTable,
        (C_SDI_SDI_SCHED_DATA*)(void*) &cSDI_SchedData50ms
    };

// Inhibit lint message 9005 related to C_SDI_CFG_FCTN_TAB in GenMPC55xx

//! Command scheduling table for DIAG DEM Service
const C_SDI_CFG_FCTN_TAB cDIAG_DEM_SDI_CfgFctnTab =
    {
        (C_SDI_CMD_FCTN_SDI_TABLE* )(void* )&cDIAG_DEM_SDI_CommandTable, //lint !e9005
        (C_SDI_SDI_SCHED_DATA*) (void*)&cSDI_SchedData100ms
    };

//! Command scheduling table for PEEK Service
const C_SDI_CFG_FCTN_TAB cPEEK_SDI_CfgFctnTab =
    {
        (C_SDI_CMD_FCTN_SDI_TABLE*)(void*) &cPEEK_SDI_CommandTable, //lint !e9005
        (C_SDI_SDI_SCHED_DATA*) (void*)&cSDI_SchedData100ms
    };

//! Command scheduling table for AOD Service
const C_SDI_CFG_FCTN_TAB cAOD_SDI_CfgFctnTab =
    {
        (C_SDI_CMD_FCTN_SDI_TABLE*)(void*) &cAOD_SDI_CommandTable, //lint !e9005
        (C_SDI_SDI_SCHED_DATA*) (void*)&cSDI_SchedData100ms
    };

//----------------------------------------------------------------------------------------------------------------------
//! This table holds Service function pointers, which will points to Service specific Command table, Scheduling info.
//! Add service specific pointers in the following array, at appropriate location,
//! As we know from 0 to 63, we have 'Base Software' services, so in implementation we will find out 'Service ID'
//! by considering 'Offset - 64'.
const C_SDI_CFG_FCTN_TAB* apcSDI_PLFServiceTable[SDI_PLATFORM_SERVICES] =
{
    &cDIAG_SDI_CfgFctnTab,                                                                          // Service ID-64
    &cDIAG_DEM_SDI_CfgFctnTab,                                                                      // Service ID-65
    &cPEEK_SDI_CfgFctnTab,                                                                          // Service ID-66
	NULL, NULL, NULL,                                                                               // SerID-67 to 69
	&cAOD_SDI_CfgFctnTab,                                                                           // Service ID-70
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,                               // SerID-71 to 81
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, // SerID-82 to 97
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, // SerID-98 to 113
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,                   // SerID-114 to 126
    NULL                                                                                            // Service ID-127
};

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *******************************************************************************************************

//** EndOfFile cfg_sdi_fwk.c ********************************************************************************************
