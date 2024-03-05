//**********************************************************************************************************************
//
//                                                   fram.h
//
//**********************************************************************************************************************
//
//                                      Copyrights(c) 2022 by KNORR-BREMSE,
//                                 Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   IBC
//! @date      2014-12-12
//! @author    ingulkrv
//
//**********************************************************************************************************************
//
//! @file fram.h
//! @brief FRAM SVL interface
//
//**********************************************************************************************************************
//  History
//  Date         Author        Changes
//  12-12-2014   V.Ingulkar    Start
//  20-07-2015   V.Ingulkar    Added s16FramSVLInitData to access FRAM
//                             during initialization
//  28-11.2022   J. Lulli      Coding guidelines and template alignment
//**********************************************************************************************************************
#ifndef FRAM_H
#define FRAM_H

//************************** Header / include files ********************************************************************
#include "std_defs.h"   // Standard definitions
//***************** Constant / macro definitions ( #define ) ***********************************************************
#define FRAM_USER_MAX_AREAS   (U32)256
//! @name FRAM SVL ERROR ID
//! @{
#define FRAM_SVL_NO_ERROR                    (S16)0  //!< no error
#define FRAM_SVL_ERR_NOT_INIT                (S16)-1 //!< not initialised yet
#define FRAM_SVL_ERR_ADR_RANGE               (S16)-2 //!< address range out of bonds
#define FRAM_SVL_ERR_SIM_ERROR               (S16)-3 //!< SIM reports error
#define FRAM_SVL_ERR_AREA_ID                 (S16)-4 //!< area ID out of bonds
#define FRAM_SVL_ERR_PARAM_INVALID           (S16)-5 //!< POFF config error
#define FRAM_SVL_ERR_U32_VIOLATE             (S16)-6 //!< address or length info violated 32 bit
#define FRAM_SVL_ERR_QUEUE_FULL              (S16)-7 //!< Queue full
#define FRAM_SVL_ERR_QUEUE_EMPTY             (S16)-8 //!< Queue Empty
#define FRAM_SVL_ERR_CFG_CALLED              (S16)-9 //!< function s16FramCfgNonSvlAreas() already called
#define FRAM_SVL_ERR_INIT_FAIL               (S16)-10 //!< Initialisation of cyclic function failed
#define FRAM_SVL_ERR_USRAREA_CGF_FAIL        (S16)-11 //!< User Area Configuration Failed

//! @}


#define FRAM_INIT_DATA_READ             (U8)0
#define FRAM_INIT_DATA_WRITE            (U8)1

//************************************** Type definitions ( typedef ) **************************************************

//! FRAM Queue status
typedef enum
{
  FRAM_STATUS_INIT = 0, //!< Entry Free // @suppress("Wrong enum identifier")
  FRAM_STATUS_BUSY, //!< Read/Write operation In Progress // @suppress("Wrong enum identifier")
  FRAM_STATUS_OPERATION_DONE, //!< Read/Write operation completed // @suppress("Wrong enum identifier")
  FRAM_STATUS_OPERATION_FAILED //!< Read/Write operation failed // @suppress("Wrong enum identifier")
} FRAM_STAT; // @suppress("Wrong prefix for complex structures")
// Note: Suppression of "Wrong prefix for complex structures", the enum and its elements should be renamed but, since
//       they are used in FWK, this is not possible so the warnings are suppressed

//********************************** Global data declarations ( extern ) ***********************************************

//********************** External parameter / constant declarations ( extern const ) ***********************************

//*************************************** Global func/proc prototypes **************************************************

//* Function s16FramSVLReadData ****************************************************************************************
//
//! function reads from Fram device. The function will put the transfer to a
//! Queue. The *pcStatus will be set to “busy”.
//! After Transfer has been completed. *pcStatus will be set to “done” or
//! “error”. The user can recognise the transfer status by checking *pcStatus.
//
//! @param[in]  u16AreaId: ID of area to read data from. ID 0 means: first SVL
//!                       area ID
//! @param[in]  u32AreaOffset: offset in area to read from in bytes
//! @param[in]  u32Length: number of bytes to read
//! @param[out] pu8UsersBufferAddress: Address of user buffer
//! @param[out] pcStatus: Address of users transfer status variable
//! @returns    #FRAM_SVL_NO_ERROR, #FRAM_SVL_ERR_NOT_INIT,
//! @returns    #FRAM_SVL_ERR_ADR_RANGE, #FRAM_SVL_ERR_QUEUE_FULL,
//! @returns    #FRAM_SVL_ERR_AREA_ID
//! @remarks    - call s16FramSVLInit() before use !
//! @remarks    - function reserved for SVL areas only
//**********************************************************************************************************************
extern S16 s16FramSVLReadData(U16 u16AreaId, FRAM_STAT* pcStatus,
    U8* pu8UsersBufferAddress, U32 u32AreaOffset, U32 u32Length);

//* Function s16FramSVLWriteData ***************************************************************************************
//
//!function writes to Fram device. The function will put the transfer to a
//! Queue. The *pcStatus will be set to “busy”.
//! After Transfer has been completed. *pcStatus will be set to “done” or
//! “error”. The user can recognize the transfer status by checking *pcStatus.
//! @param[in]  u16AreaId: ID of area to write into. ID 0 means: first SVL
//!                       area ID
//! @param[in]  u32AreaOffset: offset in area to write in bytes
//! @param[in]  u32Length: number of bytes to write
//! @param[in]  pu8UsersBufferAddress: Address of user buffer
//! @param[out] pcStatus: Address of users transfer status variable
//! @returns    #FRAM_SVL_NO_ERROR, #FRAM_SVL_ERR_NOT_INIT,
//! @returns    #FRAM_SVL_ERR_ADR_RANGE, #FRAM_SVL_ERR_QUEUE_FULL,
//! @returns    #FRAM_SVL_ERR_AREA_ID
//! @remarks    - call s16FramSVLInit() before use !
//! @remarks    - function reserved for SVL areas only
//**********************************************************************************************************************
extern S16 s16FramSVLWriteData(U16 u16AreaId, FRAM_STAT* pcStatus,
    U32 u32AreaOffset, U8* pu8UsersBufferAddress, U32 u32Length);




//* Function s16FramSVLInitData ****************************************************************************************
//
//! IMPORTANT - ONLY for init functions
//! This interface is provided to access data from FRAM during initialization.
//! May some modules/functionalities need some data from FRAM while initialization.
//! This interface is provided to fulfill this need
//! Data transfer to or from FRAM is done in blocking mode.
//! Max data transfer during initialization will increase system startup time
//! Strictly do not use this interface other than INIT functions.
//!
//! @param[in]  u16AreaId: ID of area to transfer data to or from. ID 0 means: first SVL
//!                       area ID
//! @param[in]  pu8UsersBufferAddress: Address of user buffer
//! @param[in]  u32AreaOffset: offset in area to transfer data
//! @param[in]  u32Length: number of bytes to transfer
//! @param[in]  u8Flag: FRAM_INIT_DATA_READ or FRAM_INIT_DATA_WRITE
//! @returns    #FRAM_SVL_NO_ERROR, #FRAM_SVL_ERR_NOT_INIT,
//! @returns    #FRAM_SVL_ERR_ADR_RANGE, #FRAM_SVL_ERR_QUEUE_FULL,
//! @returns    #FRAM_SVL_ERR_AREA_ID
//! @remarks    - call s16FramSVLInit() before use !
//! @remarks    - function reserved for SVL areas only
//**********************************************************************************************************************
S16 s16FramSVLInitData(U16 u16AreaId,U8* pu8UsersBufferAddress,
    U32 u32AreaOffset, U32 u32Length, U8 u8Flag);


//* Function s16FramCfgNonSvlAreas *************************************************************************************
//
//! This function configure FRAM NON SVL area.
//
//! @param[in]  pu32AreaDefs: User Configured Area Table
//! @param[in]  u8NumberAreas: Number of Areas
//! @param[out] pu16OffsetAreas: Offset Area Number
//! @returns    #FRAM_SVL_NO_ERROR, #FRAM_SVL_ERR_NOT_INIT
//! @returns    #FRAM_SVL_ERR_CFG_CALLED, #FRAM_SVL_ERR_AREA_ID
//! @returns    #FRAM_SVL_ERR_ADR_RANGE, #FRAM_SVL_ERR_U32_VIOLATE
//**********************************************************************************************************************
extern S16 s16FramCfgNonSvlAreas(const U32* pu32AreaDefs, U8 u8NumberAreas,
    U16* pu16OffsetAreas);


//* Function boFramSVLChkUserAreaMoved *********************************************************************************
//
//! This function checks whether particular area is moved or not
//
//! @param[in]  u8AreadId: Area ID to check
//! @param[out] ---
//! @returns    #TRUE, #FLASE
//**********************************************************************************************************************
extern BOOLEAN boFramSVLChkUserAreaMoved(U8 u8AreadId);

//* Function vFramSVLInitializeMovedUserArea ***************************************************************************
//
//! This function resets area moved flag after initialisation of particular area
//! Once user call s16FramCfgNonSvlAreas to reconfigure USER areas, user has to
//! Initialise all reconfigured area.
//! @param[in]  u8AreadId: Area ID to initialise
//! @param[out] ---
//**********************************************************************************************************************
extern void vFramSVLInitializeMovedUserArea(U8 u8AreadId);

#endif
//** EndOfFile fram.h **************************************************************************************************
