//
//                                 MDR_Supported_Roles.c
//
//******************************************************************************
//
//                         Copyrights(c) 2022 by KNORR-BREMSE,
//                   Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @package IBC General
//! @library <Library name>
//! @author <Author>
//!
//! $LastChangedDate: 2023-01-27 16:05:51 +0530 (Fri, 27 Jan 2023) $
//! $LastChangedRevision: 326 $
//! $LastChangedBy: belsarsa $
//!
//******************************************************************************
//!
//! @file
//! @brief This file contains the Supported Device Roles data.
//!
//******************************************************************************
//
//  History
//  Date        Author           Changes
//  2017-04-27  A. Chaudhary     Start.
//  2018-07-09  D. Gaur          Added in China trial CCA with LA role only
//  2023-01-09  J. Lulli         Coding guidelines alignment
//******************************************************************************

//********************** Compiler options ( #pragma ) ***********************//

//****************** Header / include files ( #include ) ********************/

#include "DvrMgrAl.h"

//********************** Type definitions ( typedef ) ***********************/

//************************ Global data definitions **************************/

//***************** Global constant definitions ( const ) *******************/

// Hard coded variable providing the supported device roles data for the device.
// This data is provided by the deive owner. */
#if 0 //LA+UM*/
const T_IBCDVR_SET_OF_DEVICE_ROLES cDvrMgr_SupportDeviceRoles = 0x06;
#else //LA*/
const T_IBCDVR_SET_OF_DEVICE_ROLES cDvrMgr_SupportDeviceRoles = 0x04; // @suppress("No magic numbers")
#endif
//****************** Modul global data segment ( static ) *******************/

//**************** Modul global constants ( static const ) ******************/

//***************** Local func/proc prototypes ( static ) *******************/

//* EndOfHeader *************************************************************/

//* Function definitions *******************************************************/
//* EndOfFile MDR_Supported_Roles.c ***************************************************/
