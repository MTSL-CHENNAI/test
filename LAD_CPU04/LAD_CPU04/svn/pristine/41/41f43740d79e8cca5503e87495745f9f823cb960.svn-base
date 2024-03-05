//**********************************************************************************************************************
//
//                                                    bcm_bs.h
//
//**********************************************************************************************************************
//
//                                        Copyrights(c) 2022 by KNORR-BREMSE
//                                           Rail Vehicle Systems, Munich
//
//! @project IBC
//! @date    2023-12-14
//! @author  C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file    cfg_bcm.h
//! @brief   Header that groups function with no declaration
//!
//**********************************************************************************************************************
//
//  History
//  Date        Author            Changes
//  2022-12-13	ext-lullij        Start
//  2023-11-10  C. Brancolini     Added s16BCM_BS_GenInvGetSWAppData() and "swident.h" include
//  2023-12-14  C. Brancolini     Lint Plus clean up
//
//**********************************************************************************************************************

#ifndef BCM_BS_H
#define BCM_BS_H

//***************************************** Header / include files ( #include ) ****************************************
#include "kb_types.h"
#include "swident.h"

//*************************************** Constant / macro definitions ( #define ) *************************************

//******************************************* Type definitions ( typedef ) *********************************************

//**************************************** Global data declarations ( extern ) *****************************************

//************************************ Global constant declarations ( extern const ) ***********************************

//****************************************************************************
//! @name   Function tables containing SVL call back functions used by FWR
//****************************************************************************
//@{
//----------------------------------------------------------------------------
//! Composite function table required by CCA/NonCCA components
//----------------------------------------------------------------------------
extern const C_FTAB cBCL_FctTab;
extern const C_FTAB cBCM_FctTab;
//@}


//******************************************** Global func/proc prototypes *********************************************

// Function boBCM_AppConfigurationPhase
//**********************************************************************************************************************
//! @brief Call boApp_ConfigurationPhase, get parsed configuration, set pointer to dynamic config...
//!
//!
//! @param[in] u16BCMStartupCode : Startup circumstances (timeout, start command, etc.)
//!
//! @retval TRUE  : Successful execution
//! @retval FALSE : Internal error
//!
//**********************************************************************************************************************
extern BOOLEAN boBCM_AppConfigurationPhase(U16 u16BCMStartupCode);

// Function boApp_ConfigurationPhase
//**********************************************************************************************************************
//! @brief Load configuration from flash and verify
//!
//!
//! @param[in] u16BCMStartupCode : Startup circumstances (timeout, start command, etc.)
//!
//! @retval TRUE  : Successful execution
//! @retval FALSE : Internal error
//!
//**********************************************************************************************************************
//extern BOOLEAN boApp_ConfigurationPhase(U16 u16StartupCode);

// Function s16ESRA_IDLEStartup
//**********************************************************************************************************************
//! @brief Start SCIOPTAos processes
//!
//! @retval KB_RET_OK : Successful execution
//!
//**********************************************************************************************************************
extern S16 s16ESRA_IDLEStartup (void);

// Function s16IBC_Startup
//**********************************************************************************************************************
//! @brief Perform IBC startup
//!
//! @retval KB_RET_OK : Successful execution
//!
//**********************************************************************************************************************
extern S16 s16IBC_Startup (void);

// Function s16BT_Init
//**********************************************************************************************************************
//! @brief Call FWK functions to initialize BTP channels
//!
//!
//! @retval KB_RET_OK : Successful execution
//! @retval CO_ERROR_INTERNAL : Internal error
//! @retval CO_ERROR_ARG : Parameter error
//!
//**********************************************************************************************************************
extern S16 s16BT_Init (void);

// Function s16BCM_PrintStartMsg
//**********************************************************************************************************************
//! @brief Prints start messages on the serial interface
//!
//!
//! @retval KB_RET_OK : Successful execution
//!
//**********************************************************************************************************************
extern S16 s16BCM_PrintStartMsg (void);

// Function s16BCM_BS_GenInvGetSWAppData
//**********************************************************************************************************************
//! @brief  SW (Software) 'application' data for Generic inventory data packet
//!
//! @details       - This function appends Application software related data to
//!                     generic inventory data buffer
//!
//! @param[in]     - u8PageNum     : Requested page number
//!                  u16MaxRespLen : Maximum allowed length of response data
//!                  pu16RspLen    : Actual response data length
//!                  s16ErrStatus  : Error status of calling function
//! @param[in,out] -
//!
//! @param[out]    - pu8DataOut: Generic inventory data buffer
//!
//! @return        - KB_RET_OK              (Success)
//!                - KB_RET_ERR_INST_PTR    (NULL Pointer error)
//!                - KB_RET_ERR_INTERNAL    (Internal error)
//!
//! @remark        -
//
//**********************************************************************************************************************
extern S16 s16BCM_BS_GenInvGetSWAppData (U8* pu8DataOut, U8 u8PageNum, U16 u16MaxRespLen,
        U16* pu16RspLen, S16 s16ErrStatus);


// Function s16BCM_BS_IrqAtomicInterruptInit
//**********************************************************************************************************************
//! @brief Capsule function for s32IrqAtomicInterruptInit
//!
//! @return Error Code
//! @retval KB_RET_OK : Successful execution
//! @retval < 0       : Error
//!
//**********************************************************************************************************************
extern S16 s16BCM_BS_IrqAtomicInterruptInit (void);


#endif
//** EndOfFile *********************************************************************************************************
