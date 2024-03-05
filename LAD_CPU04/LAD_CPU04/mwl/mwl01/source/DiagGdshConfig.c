//**********************************************************************************************************************
//
//                                                DiagGdshConfig.c
//
//**********************************************************************************************************************
//
//                                        Copyrights(c) 2022 by KNORR-BREMSE,
//                                   Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project IBC
//! @date    2023-11-21
//! @author  C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file
//! @brief   This file contains the configuration for GDSH.
//!
//**********************************************************************************************************************
//
//  History
//  Date        Author          Changes
//  2014-02-20  C. Bhor         Start
//  2014-08-13  C. Amrutkar     Added new variable F_EXT_DISTURBANCE in struct
//                              definition
//  2019-02-18  R. Palsule      BC0025-104: File name changed from DsmLadBswDsa
//                              to DiagDsaBswLad.
//  2023-01-09  J. Lulli        Coding guidelines alignment
//  2023-11-21  C. Brancolini   Lint Plus clean up
//
//**********************************************************************************************************************

//****************************************** Compiler options ( #pragma ) **********************************************

//*************************************** Header / include files ( #include ) ******************************************
// Inhibit lint errors related to FWK header file
//lint -save -e5469 -e5915 -e4646
#include "DiagGdshConfig.h"             // Own Header
//lint -restore
#include "DiagDsaBswLad.h"


//******************************************* Type definitions ( typedef ) *********************************************

//************************************** Global constant definitions ( const ) *****************************************
#ifdef MODULTEST
// static */
#define CONST
const char cRevFwk_DiagGdshConfig[] ="$Revision: 397 $";
#else
#define CONST const
#endif

//********************************************* Global data definitions ************************************************
CONST S_DIAGGDSH_CONFIG cDiagGdshConfig = {eGDSH_LAD, F_HW_DEFECT, F_EXT_DISTURBANCE }; // @suppress("Wrong derived data type")
//Note: Suppression of "Wrong derived data type", this warning comes from the naming convention violation of S_DIAGGDSH_CONFIG
//**************************************** Modul global data segment ( static ) ****************************************

//*************************************** Modul global constants ( static const ) **************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

// EndOfHeader *********************************************************************************************************


//* EndOfFile DiagGdshConfig.c *****************************************************************************************
