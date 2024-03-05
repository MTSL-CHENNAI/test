//**********************************************************************************************************************
//
//                                               ios_cpu04_s.h
//
//**********************************************************************************************************************
//
//                                        Copyrights(c) by KNORR-BREMSE
//                                        Rail Vehicle Systems, Munich
//
//! @project IBC
//! @date    2023-09-21
//! @author  C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file    ios_board_s.h
//! @brief   IOS board specific external interface file
//!
//**********************************************************************************************************************
//
//  History
//  Date        Author         Changes
//  2019-06-06  A. Mauro       Start
//  2020-01-29  A. Mauro       Lint clean ups
//  2023-09-21  C. Brancolini  Moved u8IOS_CfgFiltNumberOfBi, u8IOS_CfgFiltBiNumOfHighStates from ios_cpu04_i_.h
//
//**********************************************************************************************************************
#ifndef IOS_CPU04_S_H
#define IOS_CPU04_S_H

//***************************************** Header / include files ( #include ) ****************************************
#include "kb_types.h"                   // Standard definitions
#include "ios_i.h"                      // IOS internal definitions

//************************************** Constant / macro definitions ( #define ) **************************************

//******************************************** Type definitions ( typedef ) ********************************************
typedef void(*FP_IOS_VF)(void); // @suppress("Wrong prefix for complex structures")

//**************************************** Global data declarations ( extern ) *****************************************

//****************************** External parameter / constant declarations ( extern const ) ***************************

//! @name Parameters for basic Binary Filter Configuration.
//! @{
//! Configuration of number of filtered BIs. Range [0 .. IOS_MAX_NUMBER_BI]
extern const U8  u8IOS_CfgFiltNumberOfBi;

//! Configuration of min. number of high states (out of 10 samples)
//! for filter output HIGH. Range [1 .. 10]
extern const U8 u8IOS_CfgFiltBiNumOfHighStates;
//! @}

//! @name Parameters for Diagnosis Configuration inside Binary Filter .
//! @{
//! Configuration of timer for Binary Input diagnosis in[5ms].Range [100..65534]
//! Use 65535 or 0xffff to switch diagnosis function off.
extern const U16 u16IOS_CfgFiltDiagTimer;

//! Configuration base error number for BI's.
extern const U16 u16IOS_CfgFiltBiErrCode;

//! Configuration if the sum errors must be used for errors reports of BI's.
//! TRUE:   Sum error. u16IOS_CfgFiltBiErrCode used for all channels.
//! FALSE:  Error number will be calculated (u16IOS_CfgFiltBiErrCode + u16Channel)
extern const BOOLEAN boIOS_CfgFiltBiSumErr;

//! Configuration of timer for Binary Input diagnosis in [5ms]. Range [100 .. 65534]
//! Use 65535 or 0xffff to switch diagnosis function off.
extern const U16 u16IOS_CfgFiltFiBinDiagTimer;

//! Configuration base error number for FIBin's.
extern const U16 u16IOS_CfgFiltFiErrCode;

//! Configuration if the sum errors must be used for errors reports of FIBin's
//! TRUE:   Sum error. u16IOS_CfgFiltFiErrCode used for all channels.
//! FALSE:  Error number will be calculated (u16IOS_CfgFiltFiErrCode + u16Channel).
extern const BOOLEAN boIOS_CfgFiltFiSumErr;
//! @}

//! @name Parameters for Frequency Filter Configuration.
//! @{
//! Configuration of number of filtered FIs. Range [0 .. IOS_MAX_NUMBER_FI] Configuration is used for FIBin filtering
extern const U8  u8IOS_CfgFiltNumberOfFi;

//! Configuration of accepted frequency delta between two samples in [cHz]. Range [1000 .. 10000]
extern const U16 u16IOS_CfgFiltFreqInputTol;

//! Configuration of maximal allowed frequency in [cHz]. Range [100000 .. 2000000]
extern const U32 u32IOS_CfgFiltMaxAllowedFreq;
//! @}


extern const FP_IOS_VF fpvIOS_Cycl20msTriggerIOWatchdog;               //!< Watchdog function pointer // @suppress("Wrong derived data type")
extern const FP_IOS_VF fpvIOS_Cycl20msCheck;                           //!< Cyclic check function pointer // @suppress("Wrong derived data type")


#endif // IOS_CPU04_S_H
//** EndOfFile *********************************************************************************************************
