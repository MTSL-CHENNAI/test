//**********************************************************************************************************************
//
//                                                   NwmMRConfig.c
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
//! @brief
//! This NwmMR private file is a configuration file.
//! It contains the default configuration values for NwmMR.
//! This file has to be provided by the device owner per device type and located
//! in a to be defined folder in the SVN repository under the  device
//! folder (conceptually something like <device>/<FrameworkConfigs>/NwmMR)
//! For more information see the NwmMR private file NwmMRConfigImpl.h
//!
//**********************************************************************************************************************
//
//  History
//  Date        Author      Changes
//  20.07.2015  S. Peter    initial creation
//  2023-01-09  J. Lulli    Coding guidelines alignment
//  2023-05-16  C. Brancolini Lint clean up
//  2023-11-21  C. Brancolini Lint Plus clean up
//
//**********************************************************************************************************************

//****************************************** Compiler options ( #pragma ) **********************************************

//*************************************** Header / include files ( #include ) ******************************************
// Inhibit lint errors related to FWK header file
//lint -save -e5469 -e5915 -e4933
#include "NwmMRConfigImpl.h"
//lint -restore
#include "NwmMRState.h"


//*****************Begin --- Global definitions For Component Testing *******
#ifdef MODULTEST
// static */
#define CONST
const char cRevFwk_NwmMRConfig[] ="$Revision: 401 $";
#else
#define CONST  const
#endif

//***************** End ---Global definitions For Component Testing *********

//************************************** Constant / macro definitions ( #define ) **************************************
#define NWM_MR_TIME_BASE_LIFE_SIGN ((U16)512U) //!< time base for life sign (in ms)
#define NWM_MR_TIMESLICE           ((U16)50U)  //!< time slice in which the component is running (in ms)

//******************************************* Type definitions ( typedef ) *********************************************

//************************************** Global constant definitions ( const ) *****************************************
// Inhibit lint error related to cNwmMRCfg declaration in FWK header file NwmMRConfigImpl.h
//lint -save -e9075
CONST T_NWMMR_CONFIGURATION  cNwmMRCfg =
{
    NWM_MR_TIME_BASE_LIFE_SIGN,
    NWM_MR_TIMESLICE,
    ((U8)eNWM_MR_STATE_DEVREG_NODE_ID_NOT_YET_ASSIGNED),
    ((U8)eNWM_MR_STATE_CONFIG_CHECK_NOT_STARTED),
    ((U8)eNWM_MR_STATE_APP_NOT_STARTED),
    ((U8)0U)                                               //!< reserved value
};
//lint -restore

//************************************** Modul global data segment ( static ) ******************************************

//************************************ Modul global constants ( static const ) *****************************************

//************************************* Local func/proc prototypes ( static ) ******************************************

// EndOfHeader *********************************************************************************************************

// EndOfFile NwmMRConfig.c *********************************************************************************************


