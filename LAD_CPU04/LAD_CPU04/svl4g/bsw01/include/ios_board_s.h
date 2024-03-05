//**********************************************************************************************************************
//
//                                               ios_board_s.h
//
//**********************************************************************************************************************
//
//                                        Copyrights(c) by KNORR-BREMSE
//                                         Rail Vehicle Systems, Munich
//
//! @project IBC
//! @date    2023-11-13
//! @author  C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file    ios_board_s.h
//! @brief   IOS board specific internal interface file
//!
//**********************************************************************************************************************
//
//  History
//  Date        Author         Changes
//  2018-10-15  R. Palsule     Start
//  2021-07-06  A. Mauro       Added vIOS_AppConfigurationPhase
//  2022-11-28  J. Lulli       Descriptors of functions aligned with new guidelines
//  2023-11-13  C. Brancolini  Lint Plus clean up
//
//**********************************************************************************************************************

#ifndef IOS_BOARD_S_H
#define IOS_BOARD_S_H

//***************************************** Header / include files ( #include ) *****************************************
#include "kb_types.h"                   // Standard definitions
#include "ios_i.h"                      // IOS internal definitions

//************************************** Constant / macro definitions ( #define ) **************************************

//******************************************** Type definitions ( typedef ) ********************************************

//****************************************** Global data declarations ( extern ) ***************************************

//****************************** External parameter / constant declarations ( extern const ) ***************************

//******************************************** Global func/proc prototypes *********************************************

// Function vIOS_Cycl20msCheck
//**********************************************************************************************************************
//!  @brief         Board specific check function for supply voltages, relays and other IOs.
//!
//!  @details       -
//!
//!  @param[in]     -
//!
//!  @param[in,out] -
//!
//!  @param[out]    -
//!
//!
//!  @remark        Board specific function. must be called once at startup and cyclically every 20 ms. used in
//!                 diagnosis file i.e. ios_diag.c
//****************************************************************************************************************
extern void vIOS_Cycl20msCheck (void);

// Function vIOS_Cycl5msBinFilter
//**********************************************************************************************************************
//!  @brief         This function should be called in 5ms-slice. It reads each configured binary input and adds it up.
//!
//!  @details       -
//!
//!  @param[in]     -
//!
//!  @param[in,out] -
//!
//!  @param[out]    -
//!
//!
//!  @remark        Board specific configuration needed.It is supposed that each sum remains below 255 !
//!                 The function  IOSfilter50ms() must be called periodically in the 50ms-slice where each sum is
//!                 reset to zero.
//**********************************************************************************************************************
extern void vIOS_Cycl5msBinFilter (void);

// Function vIOS_Cycl50msBinFilter
//**********************************************************************************************************************
//!  @brief         This function decides if each configured binary input was high or low during the last 50 samples.
//!                 It evaluates the sum built from IOSCycl5msBinFilter() for each input : If the sum of high states
//!                 of a particular input is higher then a certain value (10...40), this input is treated  as high for
//!                 the next time (of 50ms).
//!
//!  @details       -
//!
//!  @param[in]     -
//!
//!  @param[in,out] -
//!
//!  @param[out]    -
//!
//!
//!  @remark        General function. Board specific configuration needed. This function must run in the 50ms-slice,
//!                 because it is supposed that IOSCycl5msBinFilter() was called 50 times after the last reset of each
//!                 sum.
//**********************************************************************************************************************
extern void vIOS_Cycl50msBinFilter(void);

// Function vIOS_Cycl10msFinFilter
//**********************************************************************************************************************
//!  @brief         With each call a new frequency value for Fin1 and Fin2 will be stored in an array. It contains the
//!                 X latest successive stored Fin values. Those values will be evaluated in function
//!                 vIOS_Cycl50msFinFilter which should run in the 50ms slice.
//!
//!  @details       -
//!
//!  @param[in]     -
//!
//!  @param[in,out] -
//!
//!  @param[out]    -
//!
//!
//!  @remark        Return values of Fin-driver will not be handled ! The Fin-driver will never cause ERR_DRV_IO_ACCESS.
//!                 This function should run in the 10ms slice.
//**********************************************************************************************************************
extern void vIOS_Cycl10msFinFilter (void);

// Function vIOS_Cycl50msFinFilter
//**********************************************************************************************************************
//!  @brief         Evaluates samples stored for each configured frequency channel. Filter algorithm for FIN1, FIN2 :
//!                 If three successive comparisons are good, that sample is selected which was compared last, it is
//!                 stored in FinXValue.lword. To get a good comparison, the difference of the two compared samples
//!                 must not exceed the defined tolerance and three successive comparisons must be successful.
//!
//!  @details       -
//!
//!  @param[in]     -
//!
//!  @param[in,out] -
//!
//!  @param[out]    -
//!
//!
//!  @remark        General function. Board specific configuration needed. Should run in the 50ms slice. The whole
//!                 filter algorithm is implemented in static func boIOSFilterFin(). Func IOSCycl50msFinFilter()
//!                 only passes parameter to this function if PORT-configuration is correct.
//**********************************************************************************************************************
extern void vIOS_Cycl50msFinFilter (void);

// Function vIOS_Cycl20msTriggerIOWatchdog
//**********************************************************************************************************************
//!  @brief         This function should be called in the 20ms-slice. Cyclic triggering of IO watch dog, if available
//!                 on board.
//!
//!  @details       -
//!
//!  @param[in]     -
//!
//!  @param[in,out] -
//!
//!  @param[out]    -
//!
//!
//!  @remark        General function. Activation before vIOS_Cycl20msCheck().
//**********************************************************************************************************************
extern void vIOS_Cycl20msTriggerIOWatchdog(void);

//** Function vIOS_Cycl5msRelayMonitoring ************************************
//
//!  This function should be called in the 5ms-slice.
//!  It reads driven state and actual state of each relay and memorizes
//!  differences in an array of counters.
//!
//!  @param[in]  ---
//!  @param[out] ---
//!
//!  @remarks    Board specific function.
//!              Diagnosis, based on counter array and reset counters to zero
//!              is done by IOSCycl20msCheck().
//****************************************************************************
extern void vIOS_Cycl5msRelayMonitoring (void);

//** Function vIOS_Cycl200msRelayDiagnosis ************************************
//!
//!   @brief Perform the relay diagnosis.
//!
//!
//!   @param[in]  ---
//!
//!   @param[out] ---
//!
//!
//!
//!
//!
//!   @remarks
//****************************************************************************
extern void vIOS_Cycl200msRelayDiagnosis(void);

// Function vIOS_AppConfigurationPhase
//**********************************************************************************************************************
//! @brief  IOS dynamic configuration 
//!
//! @details       -
//!
//! @param[in]     -
//!
//! @param[in,out] -
//!
//! @param[out]    -
//!
//!
//! @remark        -
//
//**********************************************************************************************************************
extern void vIOS_AppConfigurationPhase (void);


#endif
//** EndOfFile *************************************************************************************
