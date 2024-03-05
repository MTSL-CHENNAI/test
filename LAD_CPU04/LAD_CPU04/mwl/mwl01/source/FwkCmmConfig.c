//**********************************************************************************************************************
//
//                                                  FwkCmmConfig.c
//
//**********************************************************************************************************************
//
//                                        Copyrights(c) 2022 by KNORR-BREMSE,
//                                    Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @package Framework CMM Configuration
//! @library BSW
//! @author  amrutkac
//!
//! $LastChangedDate: 2023-01-27 16:05:51 +0530 (Fri, 27 Jan 2023) $:
//! $LastChangedRevision: 326 $:
//! $LastChangedBy: belsarsa $:
//!
//**********************************************************************************************************************
//!
//! @file
//! @brief Configuration file for the FwkCmm module.
//!
//**********************************************************************************************************************
//
//  History
//  Date        Author         Changes
//  2015-05-22  C. Amrutkar    Start.
//  2018-03-19  R. Dongre      Changed .FWKCMM_MAX_NR_ENTRIES to 20
//  2023-01-09  J. Lulli       Coding guidelines alignment
//**********************************************************************************************************************

//******************************************** Compiler options ( #pragma ) ********************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "Impl/FwkCmmConfig.h"

//************************************** Constant / macro definitions ( #define ) **************************************
#define FWKCMM_DATA_LENGTH_VALUE      ((U16) 10000U)

// Maximum number of FwkCmm Table entries
// DO NOT SET THIS VALUE TO ZERO. VALUE SHOULD BE SET TO MINIMUM ONE */

#define FWKCMM_MAX_NR_ENTRIES         ((U16) 20)

//******************************************** Type definitions ( typedef ) ********************************************
//*************************************** Begin --- Global definitions For Component Testing ***************************
#ifdef MODULTEST
#define CONST
const char cRevFwk_FwkCmmConfig[] ="$Revision: 326 $";
#else
#define CONST  const
#endif
//*************************************** End ---Global definitions For Component Testing ******************************
//********************************************** Global data definitions ***********************************************

//*************************************** Global constant definitions ( const ) ****************************************
CONST S_FWKCMM_CONFIGURATION cFwkCmmConfiguration = // @suppress("Wrong derived data type")
{
//Note: Suppression of "Wrong derived data type", this warning comes from the naming convetion violation of S_FWKCMM_CONFIGURATION
//      FWKCMM_NUM_OF_ENTRIES,
    FWKCMM_DATA_LENGTH_VALUE,
};


FWKCMM_ALLOC_DATA_TABLE(FWKCMM_MAX_NR_ENTRIES); //@suppress("Wrong derived data type") // @suppress("Avoid Global Variables")
//Note: Suppression of "Wrong derived data type", this warning comes from the naming convetion violation of the macro
//Note: Suppression of "Avoid Global Variables", the scope of this variable is global and must therefore be declared as
//      such
//**************************************** Modul global data segment ( static ) ****************************************

//************************************** Modul global constants ( static const ) ***************************************

//*************************************** Local func/proc prototypes ( static ) ****************************************


//* EndOfFile FwkCmmConfig.c *******************************************************************************************
