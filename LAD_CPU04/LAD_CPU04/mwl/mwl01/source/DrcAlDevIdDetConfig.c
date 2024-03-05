//*****************************************************************************
//
//                                DrcAlDevIdDetConfig.c
//
//*****************************************************************************
//
//                   Copyrights(c) 2022 by KNORR-BREMSE,
//              Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @package
//! @library
//! @author  A. Chaudhary
//!
//! $LastChangedDate: 2023-01-27 16:05:51 +0530 (Fri, 27 Jan 2023) $:
//! $LastChangedRevision: 326 $:
//! $LastChangedBy: belsarsa $:
//!
//*****************************************************************************
//!
//! @file
//! @brief This file defines the configuration parameters for device Id determination.
//!
//*****************************************************************************
//
//  History
//  Date        Author          Changes
//  2019-04-01  A. Chaudhary     Start.
//
//*****************************************************************************

//********************** Compiler options ( #pragma ) ************************/

//****************** Header / include files ( #include ) *********************/
#include "DrcAlDevIdDetConfigImpl.h"             // Own Header                       */

//**************** Constant / macro definitions ( #define ) ******************/

//********************** Type definitions ( typedef ) ************************/
//*****************Begin --- Global definitions For Component Testing *******/
#ifdef MODULTEST
#define CONST
const char cRevFwk_DrcAlDevIdDetConfig[] ="$Revision: 326 $";
#else
#define CONST  const
#endif
//***************** End ---Global definitions For Component Testing *********/
//************************ Global data definitions ***************************/

//***************** Global constant definitions ( const ) ********************/
#if 0   //FOR LAD 25*/
CONST S_DRCAL_DEVID_DET_CONFIG cDrcAlDevIdDetConfig =
{
    eDRCAL_DEVID_DET_FIX,
    (U8) 0
};
#else
CONST S_DRCAL_DEVID_DET_CONFIG cDrcAlDevIdDetConfig = // @suppress("Wrong derived data type")
{
    eDRCAL_DEVID_DET_CODINGPLUG,
    (U8) 0
};
//Note: Suppression of "Wrong derived data type", this warning comes from the naming convetion violation of S_DRCAL_DEVID_DET_CONFIG
#endif
//****************** Modul global data segment ( static ) ********************/

//**************** Modul global constants ( static const ) *******************/

//***************** Local func/proc prototypes ( static ) ********************/

//* EndOfFile DrcAlDevIdDetConfig *************************************************/
