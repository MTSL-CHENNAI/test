//**********************************************************************************************************************
//
//                                                    RtcCConfig.c
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
//! @brief
//! This RtcC private file is a configuration file.
//! It contains the default configuration values for RtcC.
//! This file has to be provided by the device owner per device type and located
//! in a to be defined folder in the SVN repository under the  device
//! folder (conceptually something like <device>/<FrameworkConfigs>/RtcC)
//! For more information see the RtcC private file RtcCConfigImpl.h
//!
//**********************************************************************************************************************
//
//  History
//  Date        Author     Changes
//  03.06.2015  S. Peter   initial creation
//  2023-01-09  J. Lulli   Coding guidelines alignment
//  2023-05-16  C. Brancolini  Lint clean up
//  2023-11-21  C. Brancolini Lint Plus clean up
//
//**********************************************************************************************************************

//****************************************** Compiler options ( #pragma ) **********************************************

//*************************************** Header / include files ( #include ) ******************************************
// Inhibit lint errors related to FWK header file
//lint -save -e5469 -e5915 -e4933
#include "impl/RtcCConfigImpl.h"
//lint -restore

//*****************Begin --- Global definitions For Component Testing *******
#ifdef MODULTEST
// static */
#define CONST
const char cRevFwk_RtcCConfig[] ="$Revision: 400 $";
#else
#define CONST  const
#endif

//***************** End ---Global definitions For Component Testing *********

//************************************** Constant / macro definitions ( #define ) **************************************
#define NWM_RTC_TIME_BASE_LIFE_SIGN ((U16)512U)   //!< time base for life sign (in ms)
#define NWM_RTC_TIMESLICE           ((U16)500U)   //!< time slice in which RTCC is running (in ms)
#define NWM_RTC_STANDALONE_SET      ((U32)86400U) //!< time in seconds after which the state "Stand alone" will be set
#define NWM_RTC_TIMESTAMP_PERIOD    ((U16)10U)    //!< time in seconds of period to write new time stamp to NvMem

//******************************************* Type definitions ( typedef ) *********************************************

//************************************** Global constant definitions ( const ) *****************************************

// Inhibit lint note 9075: cRTCCConfiguration is declared in a FWK header
// but lint plus doesn't recognize it because of a comment before the symbol
//lint -save -e9075
CONST T_RTCC_CONFIGURATION  cRTCCConfiguration =
{
    NWM_RTC_TIME_BASE_LIFE_SIGN,
    NWM_RTC_TIMESLICE,
    NWM_RTC_STANDALONE_SET,
    NWM_RTC_TIMESTAMP_PERIOD
};
//lint -restore

//************************************** Modul global data segment ( static ) ******************************************

//************************************ Modul global constants ( static const ) *****************************************

//************************************* Local func/proc prototypes ( static ) ******************************************

// EndOfHeader *********************************************************************************************************

// EndOfFile RtcCConfig.c **********************************************************************************************


