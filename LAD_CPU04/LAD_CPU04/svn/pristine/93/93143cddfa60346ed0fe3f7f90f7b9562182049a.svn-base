//**********************************************************************************************************************
//
//                                               C F G _ I O S  . H
//
//**********************************************************************************************************************
//
//                                       Copyrights(c) 2009 by KNORR-BREMSE,
//                                 Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   ESRA BSW3G55xx
//! @date      2010-04-07
//! @author    A. Tenkeu
//
//**********************************************************************************************************************
//! @file
//! @brief  Configuration Interface for Service IOS.
//
//**********************************************************************************************************************
// Date       Author      Changes:
// 07.04.10   A. Tenkeu   Start
// 01.09.10   C. Baeuml   Redesign input filter.
// 06.09.10   C. Baeuml   All IOS configuration parameters declared here.
// 07.12.12   A. Mauro    Added variables u16IOSCfgFiltBIErrSect and
//                        u16IOSCfgFiltFIErrSect
// 23.01.14   A. Mauro    Added pvIOSCycl20msTriggerIOWatchdog and
//                        pvIOSCycl20msCheck functions declarations
// 05.06.14   A. Mauro    Added IOS_MAX_NV_NUMBER
// 04.12.15   A. Mauro    Jira issues TC_005-53, TC_006-44 and
//                        TC_007-81 solved
// 06.06.17   A. Mauro    BC_002-2005: LINT clean up
// 28.11.22   J. Lulli    Coding guidelines update
//**********************************************************************************************************************


#ifndef CFG_IOS_H
#define CFG_IOS_H

//*********************************** Header / include files ( #include ) **********************************************
#include "std_defs.h"
//#include "iosi_eb.h"

//********************************* Constant / macro definitions ( #define ) *******************************************
#define IOS_MAX_NV_ENTRIES 32
#define IOS_MAX_NV_NUMBER  31


//************************************ Type definitions ( typedef ) ****************************************************

//******************************** Global data declarations ( extern ) *************************************************
//**********************************************************************************************************************

//  Function pvIOSCycl20msTriggerIOWatchdog
//!  @name Output function definitions.
//! @{
//! The following two functios are not used all warnings ignored and suppressed
extern void (*pvIOSCycl20msTriggerIOWatchdog)(void); // @suppress("Descriptive Header")
extern void (*pvIOSCycl20msCheck)(void); // @suppress("Descriptive Header") // @suppress("Use Doxygen Comments")
//! @}


//******************** External parameter / constant declarations ( extern const ) *************************************
//**********************************************************************************************************************
//! @name Parameters for basic Binary Filter Configuration.
//! @{

//! Configuration of number of filtered BIs. Range [0 .. IOS_MAX_NUMBER_BI]
extern const U8  u8IOSCfgFiltNumberOfBI;

//! Configuration of min. number of high states (out of 10 samples) for filter output HIGH. Range [1 .. 10]
extern const U8 u8IOSCfgFiltBINumberOfHighStates;
//! @}



//**********************************************************************************************************************
//! @name Parameters for Diagnosis Configuration inside Binary Filter .
//! @{

//! Configuration of timer for Binary Input diagnosis in [5ms]. Range [100 .. 65534]
//! Use 65535 or 0xffff to switch diagnosis function off.
extern const U16 u16IOSCfgFiltDiagTimer;
extern const U16 u16IOSCfgFiltFiBinDiagTimer;

//! Configuration base error number for BI's.
extern const U16 u16IOSCfgFiltBIErrCode;
extern const U16 u16IOSCfgFiltBIErrSect;

//! Configuration if the sum errors must be used for errors reports of BI's.
//! TRUE:   Sum error. u16IOSCfgFiltBIErrCode used for all channels.
//! FALSE:  Error number will be calculated (u16IOSCfgFiltBIErrCode + u16Channel)
extern const BOOLEAN boIOSCfgFiltBISumErr;

//! Configuration base error number for FIBin's.
extern const U16 u16IOSCfgFiltFIErrCode;
extern const U16 u16IOSCfgFiltFIErrSect;

//! Configuration if the sum errors must be used for errors reports of FIBin's
//! TRUE:   Sum error. u16IOSCfgFiltFIErrCode used for all channels.
//! FALSE:  Error number will be calculated (u16IOSCfgFiltFIErrCode + u16Channel).
extern const BOOLEAN boIOSCfgFiltFISumErr;

//! @}



//**********************************************************************************************************************
//! @name Parameters for Frequency Filter Configuration.
//! @{

//! Configuration of number of filtered FIs. Range [0 .. IOS_MAX_NUMBER_FI]
//! Configuration is used for FIBin filtering, too.
extern const U8  u8IOSCfgFiltNumberOfFI;

//! @brief Configuration of accepted frequency delta between two samples in [cHz]. Range [1000 .. 10000]
extern const U16 u16IOSCfgFiltFrequencyInputTolerance;

//! @brief Configuration of maximal allowed frequency in [cHz]. Range [100000 .. 2000000]
extern const U32 u32IOSCfgFiltMaxAllowedFrequency;

//! @}



#endif
//* EndOfFile CFG_IOS.H ************************************************************************************************

