//****************************************************************************
//
//                               functabexe.c
//
//****************************************************************************
//
//                    Copyrights(c) 2010 by KNORR-BREMSE,
//               Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project IBC
//! @date    2023-11-14
//! @author  C. Brancolini
//
//****************************************************************************
//
//! @file
//! @brief  Function table for executable entry points
//
//****************************************************************************
// Date        Author      Changes:
// 2012-03-29  P. Sigl     1.0  Initial revision
// 2012-06-11  P. Sigl     1.01 Include bcl_fwr.h
// 2012-08-13  P. Sigl     1.02 Comment added.
// 2013-12-09  P. Sigl     Doxygen comments added.
// 28.06.2016  S.Patapati  1.03 Adapted to CPU05 based LAD
// 2017-04-14  V.Ingulkar  1.04 Updated as per new SWIDENT table for CCA
// 2023-11-14  C. Brancolini    Lint Plus clean up
//
//****************************************************************************

//******************* Compiler options ( #pragma ) ***************************

//******************* Header / include files ( #include ) ********************
#include "functabexe.h"                 // Executable function table interface
#include "bcm_fwr.h"
#include "bcm_bs.h"


//** End of Function tables containing SVL call back functions used by FWR ***

//******************* Constant / macro definitions ( #define ) ***************

//******************* Type definitions ( typedef ) ***************************

//******************* Global scope data definitions **************************

//******************* Global scope read only definitions ( const ) ***********


//----------------------------------------------------------------------------
// Functions required by CCA/NonCCA components
//----------------------------------------------------------------------------
const C_FCT_TAB cFctTabExe =
{
    &cBCM_FctTab,                       // CCA Function Table
    &cBCL_FctTab                        // NonCCA Function Table
};




//******************* Module scope data segment ( static ) *******************

//******************* Module scope read only variables ( static const ) ******

//******************* Module scope func/proc prototypes ( static )************

//** EndOfHeader *************************************************************


//** EndOfFile functabexe.c **************************************************
