//**********************************************************************************************************************
//
//                                                  cfg_sdi.c
//
//**********************************************************************************************************************
//
//                                        Copyrights(c) by KNORR-BREMSE,
//                                         Rail Vehicle Systems, Munich
//
//! @project IBC
//! @date    2023-11-15
//! @author  C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file   cfg_sdi.c
//! @brief  Configuration for Service Data handler.
//!         New services to be handled with SDI, can be added in the Service function definition table.
//!         i.e. Service Id from 0 to 63.
//!
//**********************************************************************************************************************
//
// History
// Date         Author      Changes
// 2017-11-14   K. Gade      Start
// 2017-11-28   K. Gade      Moved BCM service specific configuration to 'cfg_sdi_bcm.c'
// 2018-03-03   K. Gade      Added 'au8SDI_ServiceMap', for handling of 'apcSDI_SrvFctnPtrTable' for new services.
//                           Renaming of variables.Added SDI_CLIENT_SERIVICES.
// 2018-04-02   R. Palsule   BC0025-33:Changes done FIM command handle implementation
// 2018-04-17   V.Ingulkar   Updated for bcm commands
// 2018-05-03   R. Dongre    Added OS related ID
// 2018-06-14   N. Joshi     Added CAN related ID
// 2019-03-30   V.Ingulkar   Changes done as per Jira - BC0025-119 -  renamed BCM header file
// 2019-04-26   K. Gade      BC0025-155: Removed Service ID Map table, it is added to in service configuration table
//                           BC0025-170: Added Scheduling time-slices list for internal handling of SDI scheduler.
// 2019-04-26   F. Heindl    Added DIAG and DIAG_DEM
// 2019-05-03   F. Heindl    Changed DIAG and DIAG_DEM to the correct 50ms timeslice
// 2019-09-06   K. Gade      BC0025-209: Updated 'apcSDI_SrvFctnPtrTable' for all services. Removed command scheduling
//                           time-slice configuration.
// 2020-02-06   K. Gade      BC0025-209: Added 'Command scheduling table' for individual Services in this file. Command
//                           table will be part of 'Command Handler', this reduces need of files like 'cfg_bcm_sdi',
//                           cfg_can_sdi, cfg_fim_sdi, cfg_os_sdi, cfg_diag_sdi, cfg_diag_dem_sdi etc.
//                           Platform & Application related services are moved to 'cfg_sdi_
// 2020-04-23   D. Jagade    BC0025-272 : Added command scheduling table for service MON
// 2022-03-21   V.Ingulkar   TC_004-13663: For IBC projects, TEST command is handled differently,
//                           Separate command table is created to handle test command differently
// 2023-09-28   A. Mauro     Set MON commands execution to 100ms (cSDI_SchedData100ms)
// 2023-11-15   C. Brancolini  Lint Plus clean up
//
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "kb_types.h"                                   // Standard definitions
#include "cbk_def.h"                                    // Service ID definitions
#include "sdi_i.h"                                      // SDI dependencies
#include "sdi_tasks_s.h"                                // SDI tasks dependencies
#include "sdi_cmd_hndlr_s.h"                            // SDI command handler
#include "mon_sdi_elad_cmd_hndlr_s.h"

//**************************************** Constant / macro definitions ( #define ) ************************************
//! Number of Services which will be used by SDI for Command Execution
#define SDI_BSW_SERVICES                (MAX_ID_BASESERVICES + (U8) 1)

//! Maximum buffer size, this should be same as maximum number of commands allowed
//! Below parameter has to be defined by board owner, based on memory availability
#define SDI_MAX_BUFF_SIZE               ( 30 )

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************
//! Response Message Pool
C_SDI_MSG acSDI_ResponseMsg[SDI_MAX_BUFF_SIZE]; // @suppress("Avoid Global Variables")

//! Command Message Pool
C_SDI_MSG acSDI_CommandMsg[SDI_MAX_BUFF_SIZE]; // @suppress("Avoid Global Variables")


//**************************************** Global constant definitions ( const ) ***************************************
//! Maximum number of commands
const U32 u32SDI_MaxCommands = SDI_MAX_BUFF_SIZE;

//! Number of services, which will be used by SDI for command execution
const U8 u8SDI_NumOfBswServices = SDI_BSW_SERVICES;

//----------------------------------------------------------------------------------------------------------------------
//! Command scheduling table for BCM Service
static const C_SDI_CFG_FCTN_TAB cBCM_SDI_CfgFctnTab =
    {
        (C_SDI_CMD_FCTN_SDI_TABLE*) (void*) &cBCM_SDI_CommandTable2,
        (C_SDI_SDI_SCHED_DATA*) (void*) &cSDI_SchedData20ms,
    };

//! Command scheduling table for CAN Service
static const C_SDI_CFG_FCTN_TAB cCAN_SDI_CfgFctnTab =
    {
        (C_SDI_CMD_FCTN_SDI_TABLE*) (void*) &cCAN_SDI_CommandTable2,
        (C_SDI_SDI_SCHED_DATA*) (void*) &cSDI_SchedData20ms,
    };

//! SDI command scheduling table for OS Service
static const C_SDI_CFG_FCTN_TAB cOS_SDI_CfgFctnTab =
    {
        (C_SDI_CMD_FCTN_SDI_TABLE*) (void*) &cOS_SDI_CommandTable2,
        (C_SDI_SDI_SCHED_DATA*) (void*) &cSDI_SchedData20ms,
    };

//! Command scheduling table for FIM Service
static const C_SDI_CFG_FCTN_TAB cFIM_SDI_CfgFctnTab =
    {
        (C_SDI_CMD_FCTN_SDI_TABLE*) (void*) &cFIM_SDI_CommandTable2,
        (C_SDI_SDI_SCHED_DATA*) (void*) &cSDI_SchedData20ms,
    };

//! Command scheduling table for MON Service
static const C_SDI_CFG_FCTN_TAB cMON_SDI_CfgFctnTab =
    {
        (C_SDI_CMD_FCTN_SDI_TABLE*) (void*) &cMON_SDI_CommandTable_eLAD,
        (C_SDI_SDI_SCHED_DATA*) (void*) &cSDI_SchedData100ms,
    };

//----------------------------------------------------------------------------------------------------------------------
//! This table holds Service function pointers, which will points to Service specific Command table, Scheduling info.
//! Add service specific pointers in the following array, at appropriate location,
const C_SDI_CFG_FCTN_TAB* apcSDI_BSWServiceTable[SDI_BSW_SERVICES] =
{
    &cBCM_SDI_CfgFctnTab,                                                                       // Service ID-0
    NULL,                                                                                       // Service ID-1
    &cCAN_SDI_CfgFctnTab,                                                                       // Service ID-2
    NULL,                                                                                       // Service ID-3
    &cMON_SDI_CfgFctnTab,                                                                       // Service ID-4
    NULL, NULL, NULL, NULL, NULL, NULL,                                                         // Service ID-5 to 10
    NULL, NULL, NULL, NULL, NULL, NULL, NULL,                                                   // Service ID-11 to 17
    &cOS_SDI_CfgFctnTab,                                                                        // Service ID-18
    NULL, NULL, NULL, NULL, NULL, NULL, NULL,                                                   // Service ID-19 to 25
    &cFIM_SDI_CfgFctnTab,                                                                       // Service ID-26
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,                           // Service ID-27 to 37
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,                           // Service ID-38 to 48
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,                           // Service ID-49 to 59
    NULL, NULL, NULL, NULL                                                                      // Service ID-60 to 63
};

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *******************************************************************************************************
//** EndOfFile cfg_sdi.c ***********************************************************************************************
