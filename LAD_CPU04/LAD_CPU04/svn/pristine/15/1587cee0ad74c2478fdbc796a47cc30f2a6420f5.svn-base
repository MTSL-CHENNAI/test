//**********************************************************************************************************************
//
//                                                    dsm_bsw.h
//
//**********************************************************************************************************************
//
//                                        Copyrights(c) 2022 by KNORR-BREMSE,
//                                  Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project IBC
//! @date    2023-11-14
//! @author  C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file
//! @brief Header file for BSW DSA Configuration
//!
//**********************************************************************************************************************
//
// History
// Date         Author      Changes
// 13.03.2014   C. Baeuml   Start
// 28.11.2022   J. Lulli    Coding guidelines and template alignment
// 2023-11-14   C. Brancolini   Deleted s32BSWDsa_Init()
//
//**********************************************************************************************************************

#ifndef DSM_BSW_H
#define DSM_BSW_H

//*************************************** Header / include files ( #include ) ******************************************
#include "DiagDsmTypes.h"

//************************************ Constant / macro definitions ( #define ) ****************************************

//******************************************* Type definitions ( typedef ) *********************************************

//*************************************** Global data declarations ( extern ) ******************************************

//****** External parameter / constant declarations ( extern const ) ***************************************************
extern const T_DIAG_DSM_STATE_CONFIG_PER_DSA_TABLE cLadBSWDsaTable;


//*********************** Global func/proc prototypes ******************************************************************


// Function s16BSWDsa_Report *******************************************************************************************
//! Function s16BSWDsa_Report().
//!
//! This function reports the error to DSA.
//!
//! @param[in] cDsaStateId
//!     T_DIAG_DSM_DSA_STATE_ID
//! @param[in] eReport
//!     E_DIAG_DSM_REPORT
//! @return none
//!     CO_ERROR_NONE on Success else CoErrno error
//! @remark
//!     This method function shall be called to report the symptom through BSW.
// *********************************************************************************************************************
extern S16 s16BSWDsa_Report( const T_DIAG_DSM_DSA_STATE_ID cDsaStateId, const E_DIAG_DSM_REPORT eReport);
#endif // bsw_dsa.h
