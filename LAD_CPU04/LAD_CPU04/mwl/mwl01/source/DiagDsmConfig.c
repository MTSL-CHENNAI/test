//**********************************************************************************************************************
//
//                                                  DiagDsmConfig.c
//
//**********************************************************************************************************************
//
//                                        Copyrights(c) 2022 by KNORR-BREMSE,
//                                    Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   IBC
//! @date      2023-11-30
//! @author    C. Brancolini
//!
//!
//**********************************************************************************************************************
//!
//! @file
//! @brief DSM Configuration
//!
//**********************************************************************************************************************
//
// History
// Date         Author      Changes
// 02.12.2013   C. Bhor     Start
// 17.03.2014   C. Baeuml   Module renamed.
// 19.03.2014   C. Baeuml   Increase of max STATEOBJECTS and DSAOWNERS.
// 25.03.2014   C. Baeuml   Better allignmetn to config example DiagDsmConfig.c; File renamed.
// 2015-11-10   S. Shinde   Changed Diagnostic State object simulation time-out period from 3000 milliseconds to
//                          180 seconds in cDSMConfiguration structure.
// 2023-01-09   J. Lulli    Coding guidelines alignment
// 2023-11-30   C. Brancolini  Lint Plus clean up
//
//**********************************************************************************************************************

//******************************************** Compiler options ( #pragma ) ********************************************

//**************************************** Header / include files ( #include ) *****************************************
// Inhibit lint errors related to FWK header file
//lint -save -e5469 -e5915 -e4646 -e4933
#include "DiagDsmConfigImpl.h"
//lint -restore

// Inhibit lint errors related to FWK header file DiagDsmTypes.h included by cfg_dsm.h
//lint -save -e5469 -e5915 -e4646
#include "cfg_dsm.h"
//lint -restore

//*************************************** Begin --- Global definitions For Component Testing ***************************
#ifdef MODULTEST
// static */
#define STATIC
#define CONST
const char cRevFwk_NwmMapH[] ="$Revision: 395 $";
#else
#define STATIC static
#define CONST const
#endif
//*************************************** End ---Global definitions For Component Testing ******************************

//******************************************** Type definitions ( typedef ) ********************************************
#define DIAG_DSM_OPERATION_CYC      ((U16)200) // DSM operation cycle in ms
#define DIAG_DSM_TIMEOUT            ((U16)180) // DSM time-out (in Seconds) for simulation
#define DIAG_DSM_FDS_PERIOD         ((U16)200) // lsPeriodForFDSAndSDSInMs
#define DIAG_DSM_CDS_PERIOD         ((U16)500) // lsPeriodForCDSInMs
//********************************************** Global data definitions ***********************************************
// Inhibit lint errors related to FWK header file DiagDsmConfigImpl.h
//lint -save -e9075 -e5915 -e4933
CONST T_DSM_CONFIGURATION   cDSMConfiguration =
{
    DIAG_DSM_OPERATION_CYC,
    DIAG_DSM_TIMEOUT,
    DIAG_DSM_FDS_PERIOD,
    DIAG_DSM_CDS_PERIOD
};
//lint -restore

// Inhibit lint errors related to FWK header file DiagDsmConfigImpl.h
//lint -save -e5915 -e4933
//! !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//! !!!!!!!!!! CAVEAT: DO NOT TOUCH THE FOLLOWING LINES !!!!!!!!!!!!!!!!!!!!!!
//! !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
DIAG_DSM_ALLOC_INTERNAL_STATE_TABLES(C_DIAG_DSM_MAX_NR_STATEOBJECTS);  // @suppress("Wrong prefix") // @suppress("Avoid Global Variables")
DIAG_DSM_ALLOC_INTERNAL_DSA_TABLE(C_DIAG_DSM_MAX_NR_DSAOWNERS); // @suppress("Wrong prefix") // @suppress("Avoid Global Variables")
//Note: Suppression of "Avoid Global Variables", the scope of these variables is global and must therefore be declared
//      as such
//lint -restore
//*************************************** Global constant definitions ( const ) ****************************************

//**************************************** Modul global data segment ( static ) ****************************************

//************************************** Modul global constants ( static const ) ***************************************

//*************************************** Local func/proc prototypes ( static ) ****************************************

//* Function definitions ***********************************************************************************************

//* EndOfFile DiagDsmConfig.c ******************************************************************************************
