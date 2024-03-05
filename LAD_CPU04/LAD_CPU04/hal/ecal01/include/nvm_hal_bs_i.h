//**********************************************************************************************************************
//
//                                                 nvm_hal_bs_i.h
//
//**********************************************************************************************************************
//
//                                       Copyrights(c) by KNORR-BREMSE,
//                                        Rail Vehicle Systems, Munich
//
//! @project CBK
//! @date 2018-09-07
//! @author K. Gade
//!
//**********************************************************************************************************************
//!
//! @file nvm_hal_bs_i.h
//! @brief NVM HAL - Board specific dependencies.
//!
//**********************************************************************************************************************
//
// History
// Date         Author         Changes
// 2018-09-07   K. Gade        BC0025-59: Start
//
//**********************************************************************************************************************

#ifndef NVM_HAL_BS_I_H
#define NVM_HAL_BS_I_H

//**************************************** Header / include files ( #include ) *****************************************
#include "kb_types.h"                                           // Standard definitions
#include "55xflsh.h"                                            //! Flash erase block

//**************************************** Constant / macro definitions ( #define ) ************************************
//! Device identifiers,
//! Device name can be defined here and used in 'cfg_nvm_hal.c' or it can be used while accessing 'nvm_hal.h' interfaces
#define NVM_HAL_DEVICE_FRAM              ((U8) 0)        //!< FRAM
#define NVM_HAL_DEVICE_FLASH             ((U8) 1)        //!< Flash

//! Flash bank id used for Configuration Data
#define NVM_PFLASH_BANK_0                ((U8) 0)

//! Flash sector numbers to be erased.(referred from '55xflsh.h')
//#define NVM_PFLASH_SECTOR_0              BL2
#define NVM_PFLASH_SECTOR_0              BL1

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data declarations ( extern ) *****************************************

//**************************************** External parameter / constant declarations ( extern const )	****************

//**************************************** Global func/proc prototypes *************************************************

#endif // NVM_HAL_BS_I_H

// EndOfFile nvm_hal_bs_i.h ****************************************************************************************************
