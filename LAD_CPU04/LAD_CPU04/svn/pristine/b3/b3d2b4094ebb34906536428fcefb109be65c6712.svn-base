//**************************************************************************************************
//
//                                          cfg_nvm_hal_poff_i.h
//
//**************************************************************************************************
//
//                                Copyrights(c) 2022 by KNORR-BREMSE
//                                  Rail Vehicle Systems, Munich
//
//! @project IBC
//! @date    2023-12-07
//! @author  C. Brancolini
//!
//**************************************************************************************************
//!
//! @file    cfg_nvm_hal_poff_i.h
//! @brief   POFF related configuration dependencies.
//!          Content in this file is configurable and it includes POFF configurable parameters.
//!
//**************************************************************************************************
//
//  History
//  Date        Author         Changes
//  2019-03-06	K. Gade        Start
//  2022-11-21  J. Lulli       Coding guidelines alignment
//  2023-12-07  C. Brancolini  Lint clean up
//**************************************************************************************************
#ifndef CFG_NVM_HAL_POFF_I_H
#define CFG_NVM_HAL_POFF_I_H
//***************************** Header / include files ( #include ) ********************************
#include "kb_types.h"                               // Standard definitions

//************************** Constant / macro definitions ( #define ) ******************************
//! Size of POFF buffer is 8kBytes
#define NVM_HAL_POFF_BUFF_SIZE                  ((U32) 8192)

//! U32 Array size POFF buffer
#define NVM_HAL_POFF_MAX_BUFF_U32               ((U32)((NVM_HAL_POFF_BUFF_SIZE + 3LU) / 4LU))

//! U32 index of CNT2 in POFF buffer
#define NVM_HAL_POFF_BUFF_CNT2IDX_U32           ((U32)(NVM_HAL_POFF_MAX_BUFF_U32 - 1LU))

//! U32 max size for areas in POFF buffer
#define NVM_HAL_POFF_BUFF_AREAS_MAXIDX_U32      ((U32)(NVM_HAL_POFF_BUFF_CNT2IDX_U32 - 1LU))

//! U32 size for areas in POFF buffer
#define NVM_HAL_POFF_BUFF_AREAS_SIZE_U32                                                  \
                                                 ((U32)(NVM_HAL_POFF_BUFF_AREAS_MAXIDX_U32 -  \
                                                        NVM_HAL_POFF_BUFF_AREAS_STARTIDX_U32) + 1U)

//! POFF buffer size reserved for non FWR areas: Words
#define NVM_HAL_POFF_BUFF_AREAS_SIZE_NONFWR_U32        ((U32) 1024)

//! POFF buffer size reserved for FWR areas: Rest
#define NVM_HAL_POFF_BUFF_AREAS_SIZE_FWR_U32           ((U32)(NVM_HAL_POFF_BUFF_AREAS_SIZE_U32 -          \
                                                       NVM_HAL_POFF_BUFF_AREAS_SIZE_NONFWR_U32))

//! POFF buffer start index of NON-FWR areas
#define NVM_HAL_POFF_BUFF_AREAS_STARTIDX_NONFWR_U32    (NVM_HAL_POFF_BUFF_AREAS_STARTIDX_U32 +   \
                                                       NVM_HAL_POFF_BUFF_AREAS_SIZE_FWR_U32)

//******************************** Type definitions ( typedef ) ************************************

//**************************** Global data declarations ( extern ) *********************************

//**************** External parameter / constant declarations ( extern const ) *********************

//******************************* Global func/proc prototypes **************************************

#endif //* CFG_NVM_HAL_POFF_I_H */
//** EndOfFile *************************************************************************************
