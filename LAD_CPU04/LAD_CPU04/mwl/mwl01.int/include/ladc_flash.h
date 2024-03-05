//*****************************************************************************
//
//                    L A D C _ F L A S H . H
//
//*****************************************************************************
//
//                    Copyrights(c) 2022 by KNORR-BREMSE,
//               Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   IBC
//! @date      2018.12.10
//! @author    K. Gade
//
//*****************************************************************************
//
//! @file
//! @brief  LAD configuration: interface between FLASH related part and Service
//          This file is made to EB01 platform (MPC5534 controller)
//*****************************************************************************
// Date       Author     Changes:
// 2012.11.09 G. Nagy    Start
// 2013.05.27 G. Nagy    Actual Flash usage/functionality added.
// 2014.01.31 P. HegedüsNew eFLASHING_STATE state: eFLASH_COMPARE (C167 only)
// 2015.02.15 A. Demeter Cleanup
// 2017.03.29 S. Kumbhar Added flash configurable parameters
// 2018.09.10 K. Gade    BC0025-59: Cleaned up Flash related constants used
//                       for LAD configuration.
// 2018.12.10 K. Gade    BC0025-81: Adaption of generic area id
// 2022.11.24 J. Lulli   Coding guidelines alignment
//*****************************************************************************
#ifndef LADC_FLASH_H
#define LADC_FLASH_H

//************************** Header / include files ***************************
#include "kb_types.h"                  // Standard definitions
#include "bcm_common.h"

//***************** Constant / macro definitions ( #define ) ******************
// Return values for interface functions
#define FLASH_RET_NO_ERROR                   ((S16)   0)
#define FLASH_RET_IN_PROGRESS                ((S16)   1)
#define FLASH_ERR_NO_CONFIG                  ((S16)  -1)    // No configuration on Flash
#define FLASH_ERR_CFG_SIZE                   ((S16)  -2)    // Invalid raw config size is stored in Flash buffer 1st 4 bytes
#define FLASH_ERR_BUFF_SIZE                  ((S16)  -3)    // The given target buffer is too small for copying the raw configuration.
#define FLASH_ERR_ERASE                      ((S16)  -4)    // Erase failed
#define FLASH_ERR_INPUT                      ((S16)  -5)    // Input parameter is out-of-range
#define FLASH_ERR_PROGRAM                    ((S16)  -6)    // Error in programming flash

// Definition of AreaID, AreaOffset for LAD configuration data
// Use this macro/area id to pass within a function calls of NVM
#define LADC_NVM_USR_AREA_ID             u8LADC_NonPoffUsrArea
#define LADC_NVM_USR_AREA_OFFSET         u8LADC_NonPoffUsrAreaOffset

// Assignment of AreaID, AreaOffset
#define LADC_NVM_USR_AREA_ID_SET(x)      BCM_COMMON_AREA_ID_SET ( LADC_NVM_USR_AREA_ID, x )
#define LADC_NVM_USR_AREA_OFFSET_SET(x)  BCM_COMMON_AREA_ID_SET ( LADC_NVM_USR_AREA_OFFSET, x )

// Declaration of LADC Area ID, AreaOffset
BCM_COMMON_AREA_ID_DECL  ( LADC_NVM_USR_AREA_ID )
BCM_COMMON_AREA_ID_DECL  ( LADC_NVM_USR_AREA_OFFSET )



//*********************** Type definitions ( typedef ) ************************
//******************* Global scope data definitions **************************

//*****************************************************************************

// Function u32LADCGetConfigAddress() ***************************************/
//!                                                                        **/
//! Tells caller on which address the config is stored in FLASH.           **/
//! @param[in] none                                                        **/
//! @return: Address value of the configuration in FLASH                   **/
//!                                                                        **/
//! Note:    This is just the raw address. No check for data there!        **/
//**************************************************************************/
extern U32 u32LADCGetConfigAddress(void);

// Function s16LADCGetRAWConfigFromFLASH() *************************************/
//!                                                                        **/
//! @brief   Get the RAW config from the FLASH memory.                     **/
//!                                                                        **/
//! @param[in,out]   pu8RAMBufferAddress[out]: address of (RAM) buffer,    **/
//!                            where to fill config                        **/
//! @param[in]   u16RAMBuffLength[in]: size of RAM buffer                  **/
//!                                                                        **/
//! @return: #FLASH_RET_NO_ERROR:  Read finished successfully              **/
//!          #FLASH_ERR_NO_CONFIG: no config can be found in FLASH         **/
//!          #FLASH_ERR_BUFF_SIZE: target buffer size is not sufficient    **/
//!          #FLASH_ERR_CFG_SIZE:  raw cfg size indicates invalid content  **/
//**************************************************************************/
extern S16 s16LADCGetRAWConfigFromFLASH(U8* pu8RAMBufferAddress, U16 u16RAMBuffLength);


// Function s16LADCEraseFLASH() ********************************************/
//!                                                                        **/
//! @brief Erases a lock.                                                  **/
//! FLASH segment to be erased is defined internally.                      **/
//! @param[in] none                                                        **/
//! @return: #FLASH_RET_NO_ERROR:    erase finished                        **/
//!          #ERRORS: Return values of u855xxFlsh_ProgramWord changed to   **/
//!                   negative numbers (see 55xflsh.h).                    **/
//!                                                                        **/
//! Timing: Erasing BL2 block takes ~130ms, measured with U32OSGetTimeMS.  **/
//**************************************************************************/
extern S16 s16LADCEraseFLASH(void);


// Function s16LADCFlashParsedCfg() ****************************************/
//                                                                        **/
//! @brief Writes the parsed configuration into FLASH.                     **/
//! FLASH block to be written is defined internally.                       **/
//!                                                                        **/
//! @param[in,out] pu8CfgAddress: Address of configuration to be written   **/
//! @param[in] u16CfgSize   : Size of configuration in bytes               **/
//! @param[in] u16MaxRunTime : maximum allowed runtime in miliseconds      **/
//!                      No check of max runtime, user has to handle       **/
//!                                                                        **/
//! @return: #FLASH_RET_NO_ERROR:    flashing finished                     **/
//!          #FLASH_RET_IN_PROGRESS: flashing is in progress, call again   **/
//!          #FLASH_ERR_INPUT:       u16CfgSize is either 0 or             **/
//!                                  bigger than FLASHBLOCK_SIZE           **/
//!          #Other errors: return values of u855xxFlsh_ProgramWord        **/
//!                         changed to negative numbers (see 55xflsh.h)    **/
//!                                                                        **/
//! Note: Function must be called repeatedly until it returns with         **/
//!       FLASH_RET_IN_PROGRESS.                                           **/
//!       The input parameter CfgSize must be left intact on every call.   **/
//!       pu8CfgAddress is used only at first call.                        **/
//!       Current implementation works with writing huge chunks of source  **/
//!       which is configurable via macros.                                **/
//**************************************************************************/
extern S16 s16LADCFlashParsedCfg(U8* pu8CfgAddress, U16 u16CfgSize, U16 u16MaxRunTime);

#endif
//** EndOfFile ladc_flash.h *********************************************************
