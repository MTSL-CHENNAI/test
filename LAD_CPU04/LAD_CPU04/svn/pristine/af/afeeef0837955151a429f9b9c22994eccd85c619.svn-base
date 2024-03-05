//**********************************************************************************************************************
//
//                                                  cfg_peek_sdi.c
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
//! @file   cfg_peek_sdi.c
//! @brief  This file contains configurations for PEEK / POKE commands, which use SDI service.
//!         New commands to be handled by SDI command interface, can be added in the configuration table.
//!
//**********************************************************************************************************************
//
// History
// Date         Author      Changes
// 2019-03-06   A. Mauro    Start
// 2019-09-12   F. Heindl   Changed for Peek/Poke
// 2021-06-24   F. Heindl   Moved cPEEK_SDI_CommandTable and command ID defines to cfg_peek_sdi_hndlr.c
//                          Moved cPEEK_SDI_CfgFctnTab to cfg_sdi_fwk.c
//                          Deleted unused TYPEDEF_SDI_FCTN_TAB
//                          Provide constants to define maximum # of PDs to read or write
// 2023-11-21   C. Brancolini  Deleted unused code
//
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "kb_types.h"                                 // Standard definitions
#include "IbcSysDefs.h"                               // for IBC_PEEK_ID and IBC_PEEK_DEM_ID
#include "peek_sdi_cmd_hndlr_i.h"                     // Service handler interfaces
#include "sdi_tasks_s.h"                                // SDI tasks dependencies

//**************************************** Constant / macro definitions ( #define ) ************************************


//! this is a board specific parameter defining the maximum number of PDs allowed in a read request
#define SDI_PEEK_MAX_READ_PDS_BOARD             ( 0x3CU )
//! this is a board specific parameter defining the maximum number of PDs allowed in a write request
#define SDI_PEEK_MAX_WRITE_PDS_BOARD            ( 0x20U )

#if (SDI_PEEK_MAX_READ_PDS_BOARD > SDI_PEEK_MAX_READ_PDS) || (SDI_PEEK_MAX_WRITE_PDS_BOARD > SDI_PEEK_MAX_WRITE_PDS)
 #error "Please check settings for SDI_PEEK_MAX_READ_PDS_BOARD or SDI_PEEK_MAX_WRITE_PDS_BOARD"
#endif
//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************
const U8 u8PEEK_MaxReadPdsBoard  = SDI_PEEK_MAX_READ_PDS_BOARD;                 //!< max. # of PDs in read request
const U8 u8PEEK_MaxWritePdsBoard = SDI_PEEK_MAX_WRITE_PDS_BOARD;                //!< max. # of PDs in write request

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *******************************************************************************************************

//** EndOfFile cfg_peek_sdi.c *******************************************************************************************
