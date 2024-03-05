//**********************************************************************************************************************
//
//                                                  FwkCtrlConfig.c
//
//**********************************************************************************************************************
//
//                                        Copyrights(c) 2022 by KNORR-BREMSE,
//                                     Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project IBC
//! @date    2023-11-21
//! @author  C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file
//! @brief   Framework Control Configuration
//!
//! This is MPC specific configuration for FwkCtrl
//!
//**********************************************************************************************************************
//
//  History
//  Date        Author          Changes
//  23.05.2014   C. Bhor        Start
//  04.01.2017   S. Kumbhar     Added 2ms amd 1000ms time slice
//  2018-01-10   S. Kumbhar     Service OS updated as per Coding guidelines
//  2023-01-09   J. Lulli       Coding guidelines alignment
//  2023-05-16   C. Brancolini  Lint clean up
//  2023-11-21  C. Brancolini   Lint Plus clean up
//
//**********************************************************************************************************************

//****************************************** Compiler options ( #pragma ) **********************************************

//*************************************** Header / include files ( #include ) ******************************************
#include "FwkCtrlConfig.h"
#include "os_s.h"

//******************************************* Type definitions ( typedef ) *********************************************

//************************************** Global constant definitions ( const ) *****************************************
const S_FWKCTRL_CONFIG cFwkCtrlConfig = // @suppress("Wrong derived data type")
{
    //Note: Suppression of "Wrong derived data type", this warning comes from the naming convetion violation of S_FWKCTRL_CONFIG
    (U8)eOS_SLICE_1MS,
    (U8)eOS_SLICE_2MS,
    (U8)eOS_SLICE_5MS,
    (U8)eOS_SLICE_10MS,
    (U8)eOS_SLICE_20MS,
    (U8)eOS_SLICE_50MS,
    (U8)eOS_SLICE_100MS,
    (U8)eOS_SLICE_200MS,
    (U8)eOS_SLICE_500MS,
    (U8)eOS_SLICE_1000MS,
    (U8)eOS_SLICE_USER,
    TRUE,
    boOS_ActivateFct //lint !e9074 Missing void in the first parameter of boOS_ActivateFct
};

//************************************** Modul global data segment ( static ) ******************************************

//************************************ Modul global constants ( static const ) *****************************************

//************************************* Local func/proc prototypes ( static ) ******************************************

//* EndOfHeader ********************************************************************************************************

//* Function definitions ***********************************************************************************************

//* EndOfFile FwkCtrlConfig.c ******************************************************************************************
