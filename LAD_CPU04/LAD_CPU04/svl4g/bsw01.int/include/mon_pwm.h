//**********************************************************************************************************************
//
//                                                   mon_pwm.h
//
//**********************************************************************************************************************
//
//                                      Copyrights(c) 2022 by KNORR-BREMSE,
//                                 Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   IBC
//! @date      2023-09-14
//! @author    A. Mauro
//
//**********************************************************************************************************************
//  History
//  Date         Author        Changes
//  09.11.2011   W. Boigk      0.1    Start
//  12.11.2013   H. Shaikh     0.2    Generalization of Commands
//  2023.09.14   A. Mauro      0.3    Alignment with CA: name changed and other
//**********************************************************************************************************************

#ifndef MON_PWM_H
#define MON_PWM_H


//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include    <STD_DEFS.H>

//***************** Constant / macro definitions ( #define ) ***********************************************************

//************************************** Type definitions ( typedef ) **************************************************

//********************************** Global data declarations ( extern ) ***********************************************

//********************** External parameter / constant declarations ( extern const ) ***********************************

//*************************************** Global func/proc prototypes **************************************************

//* Function boMON_WritePWM ********************************************************************************************
//
//!  Set PWM Channel in Testmode
//
//!  @param[in]  u16Channel: FO Channel [#IOS_CHANNEL_1 .. #IOS_CHANNEL_32]
//!  @param[in]  u32DutyCycle: Duty Cycle
//!
//!  @param[out] ---
//!  @returns    Success - TRUE
//!              Fail    - FALSE
//!  @remarks
//**********************************************************************************************************************
extern BOOLEAN boMON_WritePWM(U16 u16Channel, U32 u32DutyCycle);

//** Function vMON_PWMTestHandler **************************************************************************************
//
//!  Get cont. PWM values, because only on request new values are sampled
//
//!  @param[in]  --
//!
//!  @param[out] --
//!  @returns    --
//!  @remarks must allways run in testmode
//**********************************************************************************************************************
extern void vMON_PWMTestHandler (void);

#endif
//* EndOfFile MON_PWM.H ******************************************************
