//**********************************************************************************************************************
//
//                                          bcl_hal_bdspec_i.h
//
//**********************************************************************************************************************
//
//                               Copyrights(c) 2022 by KNORR-BREMSE
//                                  Rail Vehicle Systems, Munich
//
//! @project IBC
//! @date    2023-12-07
//! @author  C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file    bcl_hal_bdspec_i.h
//! @brief   Board specific BCL implementation
//!
//! @details -
//!
//**********************************************************************************************************************
//
//  History
//  Date           Author              Changes
//  2018-08-02     V.Ingulkar          Start
//  2023-12-07     C. Brancolini       Added functions: s16BCL_FWR_CtrlCacheEnable, s16BCL_FWR_CtrlCstartup,
//                                     s16BCL_FWR_DSPIInit
//
//**********************************************************************************************************************
#ifndef BCL_HAL_BDSPEC_I_H
#define BCL_HAL_BDSPEC_I_H
//***************************** Header / include files ( #include ) ****************************************************
#include "kb_types.h"
//************************** Constant / macro definitions ( #define ) **************************************************

//******************************** Type definitions ( typedef ) ********************************************************

//**************************** Global data declarations ( extern ) *****************************************************

//**************** External parameter / constant declarations ( extern const ) *****************************************

//******************************* Global func/proc prototypes **********************************************************

// Function s16BCL_BD_HAL_WD_Pin_Init
//! @brief  Returns the total number of configured Board LEDs
//!
//! @details       -
//!
//! @param[in]     -
//!
//! @param[in,out] -
//!
//! @param[out]    -
//!
//! @return     Total number of configured Board LEDs
//!
//! @remark        -
//
//**********************************************************************************************************************
extern S16 s16BCL_BD_HAL_WD_Pin_Init (void);

// Function s16BCL_FWR_CtrlCacheEnable
//! @brief  Capsule function for _fwr_cache_enable
//!
//! @details       -
//!
//! @param[in]     -
//!
//! @param[in,out] -
//!
//! @param[out]    -
//!
//! @return     KB_RET_OK
//!
//! @remark        -
//
//**********************************************************************************************************************
extern S16 s16BCL_FWR_CtrlCacheEnable(void);

// Function s16BCL_FWR_CtrlCstartup
//! @brief  Capsule function for _bcl_fwr_cstartup
//!
//! @details       -
//!
//! @param[in]     -
//!
//! @param[in,out] -
//!
//! @param[out]    -
//!
//! @return     KB_RET_OK
//!
//! @remark        -
//
//**********************************************************************************************************************
extern S16 s16BCL_FWR_CtrlCstartup(void);

// Function s16BCL_FWR_DSPIInit
//! @brief  Capsule function for s32DSPIInit
//!
//! @details       -
//!
//! @param[in]     -
//!
//! @param[in,out] -
//!
//! @param[out]    -
//!
//! @return     0: no error
//! @return     DSPIERR_ALREADYINIT: init function did nothing since it found DSPI module already initialized
//!
//! @remark        -
//
//**********************************************************************************************************************
extern S16 s16BCL_FWR_DSPIInit(void);

#endif //* BCL_HAL_BDSPEC_I_H */
//** EndOfFile *********************************************************************************************************
