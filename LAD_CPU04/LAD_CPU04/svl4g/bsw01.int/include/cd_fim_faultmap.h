//**********************************************************************************************************************
//
//                                                 cd_fim_faultmap.h
//
//**********************************************************************************************************************
//
//                                       Copyrights(c) by KNORR-BREMSE,
//                                        Rail Vehicle Systems, Munich
//
//! @project CBK
//! @date 2021-09-14
//! @author N.Jadhav
//!
//**********************************************************************************************************************
//!
//! @file cd_fim_faultmap.h
//! @brief CDO-definition
//!
//**********************************************************************************************************************
//
// History
// Date         Author         Changes
// 2017-07-27   R. Palsule     Start
// 2017-12-18   R. Palsule     Changed file name and related comments
// 2018-12-14   R. Palsule     TI0001-82: Changes done internal error parameter in CDO_FIM_DSM_AL
// 2021-09-14   N. Jadhav      GenCA V07.00 adaptation changes.
//**********************************************************************************************************************

#ifndef CD_FIM_FAULTMAP_H
#define CD_FIM_FAULTMAP_H

//**************************************** Header / include files ( #include ) *****************************************
#include "cbk_def.h"                    // CBK Standard Definitions
#include "kb_types.h"                   // KB Types
#include "cdo.h"                        // Generic definition of CDO
//**************************************** Constant / macro definitions ( #define ) ************************************
//! Definition of the table type code minor number
#define TTC_MINOR_CDO_FIM_DSM_AL       0U
//**************************************** Type definitions ( typedef ) ************************************************
//! FIM-DSM fault mapping structure
typedef struct
  {
  U8  u8ServiceErrorNumber;             //!< Service error number
  U8  u8ServiceID;                      //!< Service ID
  U8  u8Section;                        //!< Section number
  U8  u8ErrorCategory;                  //!< Error Category
  U16 u16DSMActualFaultID;              //!< DSM Actual Fault ID
  U16 u16DSMDependentFault;             //!< DSM Dependent fault
  U16 u16DSMCDSID;                      //!< DSM CDS ID
  U16 u16DSMFDSID;                      //!< DSM FDS ID
  BOOLEAN boInternalError;              //!< Internal error number TRUE: Internal error FALSE: Normal error
  } C_CDO_FIM_DSM_AL;
//**************************************** Global data declarations ( extern ) *****************************************

//**************************************** External parameter / constant declarations ( extern const )	****************

//**************************************** Global func/proc prototypes *************************************************

#endif

//** EndOfFile cd_fim_faultmap.h ***************************************************************************************
