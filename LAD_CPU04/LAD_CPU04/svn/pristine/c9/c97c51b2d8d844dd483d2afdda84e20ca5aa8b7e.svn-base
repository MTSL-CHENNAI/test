//**********************************************************************************************************************
//
//                                                       DiagDfmAl.c
//
//**********************************************************************************************************************
//
//                                          Copyright (C) 2022 by KNORR-BREMSE,
//                                     Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   IBC
//! @date      2023-12-01
//! @author    C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file
//! @brief Adaption layer for DFM
//!        This file provides interfaces to access device specific resources
//!
//**********************************************************************************************************************
//
// History
// Date          Author         Changes
// 2015-07-20    V.Ingulkar     Start
// 2015-07-29    V.Ingulkar     Removed DFM status
// 2015-10-16    V.Ingulkar     Changes done during integration workshop
//                              @Melksham
// 2015-10-19    V.Ingulkar     Clean up of Rev 1.2
// 2018-01-10    S. Kumbhar     Service OS updated as per Coding guidelines
// 2018-06-08    V.Ingulkar     BC0025-35, BC0025-36:Only one user for poff areas, either APP or APP plus FWK
// 2022-03-09    A. Mauro       TC_004-13662: set DFM_NVM_FWK_AREA_ID when NVM_DEVICE_ID1 is used
// 2023-01-09    J. Lulli       Coding guidelines alignment
// 2023-05-16    C. Brancolini  Lint clean up
// 2023-12-01    C. Brancolini  Lint Plus clean up
//
//**********************************************************************************************************************

//********************************************** Compiler options ( #pragma ) ******************************************

//******************************************* Header / include files ( #include ) **************************************

#include "os.h"
#include "CoErrno.h"
#include "CoCheck.h"
// Inhibit lint errors related to FWK header file
//lint -save -e5469 -e5915 -e4646
#include "DiagDfm.h"
//lint -restore
#include "DiagDfmAl.h"
#include "FwkAlDFMNvMem.h"
#include "nvm_common.h"             // NVM Common definitions
#include "nvm.h"                    // NVM interfaces

//******************************************* Constant / macro definitions ( #define ) *********************************

#define NUM_FOUR            4U
#define WORD_LEN            NUM_FOUR

//*************************************************** Type definitions ( typedef ) *************************************

//***************************************************** Global data definitions ****************************************

//************************************************ Global constant definitions ( const ) *******************************

//************************************************* Modul global data segment ( static ) *******************************

//************************************************ Modul global constants ( static const ) *****************************

//************************************************** Local func/proc prototypes ( static ) *****************************

static inline U16 u16DfmAlCheckValidParamSize( U16 u16Size );
static S16 s16DiagDfmAl_WaitRequestResult( S16 s16AggregatedError, E_NVM_OPERATION_STATUS* peStatus );

// EndOfHeader ***************************************************************

// Function u16DfmAlCheckValidParamSize
//! u16CheckValidParamSize()
//!     This function checks if received size is valid (U32 align) or not.
//!     If not, it will adjust the size.
//! @param[in] u16Size      Received size parameter
//! @param[out] none
//! @return u16RetVal       Valid size
//! @requirement
//*****************************************************************************/
static inline U16 u16DfmAlCheckValidParamSize( U16 u16Size )
{
//************************************************ Function scope data *************************************************
    U16 u16RetVal;                     // Function return variable

//*************************************************** Function code ****************************************************
    // Check if received size is 32 bit aligned or not
    if( ( u16Size % WORD_LEN ) == NUM_ZERO )
    {
        // If Yes, return same size
        u16RetVal = u16Size;
    }
    else
    {
        // If not, make it 32 bit align
        u16RetVal = ( U16 )( u16Size + ( WORD_LEN - ( u16Size % WORD_LEN ) ) );
    }

    // Return input size aligned at U32
    return( u16RetVal );

}
//** EndOfFunction u16DfmAlCheckValidParamSize ******************************************************************************

// Function s16DiagDfmAl_WaitRequestResult
//***************************************************************************************************************************
//! @brief This function waits for the result of the queued request.
//!        It returns KB_RET_OK if the NVM Operation Status is done, error otherwise.
//!
//! @param[in] s16AggregatedError     : KB return value from the caller function
//! @param[in] peStatus               : pointer to NVM Operation Status
//!
//! @return KB Return Value
//! @retval KB_RET_OK                 : Successful execution
//! @retval negative value            : Error
//!
//! @remark The value of the variable referenced by peStatus is changed by NVM Service
//**********************************************************************************************************************
static S16 s16DiagDfmAl_WaitRequestResult(S16 s16AggregatedError, E_NVM_OPERATION_STATUS* peStatus )
{
//************************************************ Function scope data *************************************************
    S16 s16Result;                  // function result

//*************************************************** Function code ****************************************************
    // Initialize function result at s16AggregatedError
    s16Result = s16AggregatedError;
    if( peStatus == KB_NULL_PTR )
    {
        s16Result = KB_RET_ERR_INTERNAL;
    }
    // Evaluate s16AggregatedError parameter coming from the caller function.
    if( s16Result == KB_RET_OK )
    {
        // Wait for the result of the queued request
        while( *peStatus == eNVM_STATUS_OPERATION_BUSY )
        {
            // While status is busy, do nothing.
            // The value of eStatus is changed by another task,
            // so it is possible to exit this while loop
        }
        if( *peStatus == eNVM_STATUS_OPERATION_DONE )
        {
            // Status is operation done, return OK
            s16Result = KB_RET_OK;
        }
        else
        {
            // Status failed, return config error
            s16Result = KB_RET_ERR_CONFIG;
        }
    }
    return s16Result;
}
//** EndOfFunction s16DiagDfmAl_WaitRequestResult **********************************************************************


//**********************************************************************************************************************
// Function s16DiagDfmAl_ReadData
//**********************************************************************************************************************
S16 s16DiagDfmAl_ReadData( U16 u16Offset, U32* pu32Data, U16 u16Length,
                           E_DIAG_DFM_NVMEM_DATA_TYPE eDataType,
                           E_DIAG_DFM_NVMEM_XFER_MODE eNVMemMode )
{
//************************************************ Function scope data *************************************************
    S16 s16AggregatedError = KB_RET_OK;                             // Function return variable
    U16 u16TempLen;                                                 // 32 bit aligned length
    E_NVM_OPERATION_STATUS eStatus = eNVM_STATUS_OPERATION_INIT;    // local variable for operation status

//*************************************************** Function code ****************************************************
    // Check for valid pointer
    if( pu32Data == KB_NULL_PTR )
    {
        s16AggregatedError = KB_RET_ERR_INST_PTR;
    }
    else
    {
        // Size of FRAM transfer should be 32 bit aligned
        u16TempLen = u16DfmAlCheckValidParamSize( u16Length );

        // Check which data we are reading - Markers or Event
        if( eDataType ==  eDFM_NVMEM_MARKER_DATA )
        {
            // Marker data is available in POFF-FRAM
            // Read Marker Data
            s16AggregatedError = s16NVM_ReadData (NVM_DEVICE_ID0,  // Device ID for accessing NVM POFF
                                                  u8DFM_MyPoffUsrArea,
                                                  eNVM_BLOCKING_MODE,
                                                  &eStatus,
                                                  0,
                                                  (U8*) pu32Data,
                                                  (U32) u16TempLen);

            if( s16AggregatedError != KB_RET_OK )
            {
                s16AggregatedError = KB_RET_ERR_INTERNAL;
            }

        }
        else
        {
            // Event data is available in NonPOFF-FRAM
            // Read Event Data
            // Check for mode to read an event
            if( eNVMemMode == eDFM_NVMEM_BLOCK_MODE )
            {
                // Read event data in blocking mode
                // As FRAM queues are not UP before initialization, this mode should be used during initialization only
                // For the data which need to be written or Read during initialization
                s16AggregatedError = s16NVM_ReadData (NVM_DEVICE_ID1,  // Device ID for accessing non poff NVM
                                                      DFM_NVM_FWK_AREA_ID,
                                                      eNVM_BLOCKING_MODE,
                                                      &eStatus,
                                                      u16Offset,
                                                      (U8*) pu32Data,
                                                      (U32) u16TempLen);
            }
            else
            {
                // In queued mode the read request is entered into a free slot in the queue. From there
                // the NVM cyclic operation eventually retrieves and executes it. Depending on the size
                // of the data it may need several passes to finish the request.
                // The result of the operation is written to eStatus.
                // s16DiagDfmAl_ReadData() waits for the result and only exits after receiving it.
                // As the function finishes in a single pass the eStatus may be local. This also allows
                // having multiple instances of the function.
                // There may be multiple read or write requests waiting in the NVM queue at one time.
                // NVM handles them one after the other.
                eStatus = eNVM_STATUS_OPERATION_BUSY;

                // Read DFM data from NV memory - NonPOFF- FRAM
                s16AggregatedError = s16NVM_ReadData (NVM_DEVICE_ID1,  // Device ID for accessing non poff NVM
                                                      DFM_NVM_FWK_AREA_ID,
                                                      eNVM_QUEUE_MODE,
                                                      &eStatus,
                                                      u16Offset,
                                                      (U8*) pu32Data,
                                                      (U32) u16TempLen);

                s16AggregatedError = s16DiagDfmAl_WaitRequestResult( s16AggregatedError, &eStatus );

            }

            // Check intermediate result, set internal error in case of failure
            if( s16AggregatedError != KB_RET_OK )
            {
                s16AggregatedError = KB_RET_ERR_INTERNAL;
            }

        }
    }
    return ( s16AggregatedError );

}
//** EndOfFunction s16DiagDfmAl_ReadData *******************************************************************************

//**********************************************************************************************************************
// Function s16DiagDfmAl_WriteData
//**********************************************************************************************************************
S16 s16DiagDfmAl_WriteData( U16 u16Offset, U32* pu32Data, U16 u16Length,
                            E_DIAG_DFM_NVMEM_DATA_TYPE eDataType,
                            E_DIAG_DFM_NVMEM_XFER_MODE eNVMemMode )
{
//************************************************ Function scope data *************************************************
    S16 s16AggregatedError = KB_RET_OK;                             // Function return variable
    U16 u16TempLen = NUM_ZERO;                                      // 32 bit aligned length
    E_NVM_OPERATION_STATUS eStatus = eNVM_STATUS_OPERATION_INIT;    // local variable for operation status

//*************************************************** Function code ****************************************************
    // Check for valid pointer
    if( pu32Data == KB_NULL_PTR )
    {
        s16AggregatedError = KB_RET_ERR_INST_PTR;
    }
    else
    {
        // Size of FRAM transfer should be 32 bit aligned
        u16TempLen = u16DfmAlCheckValidParamSize( u16Length );
        // Check which data we are storing - Markers or Event
        if( eDataType ==  eDFM_NVMEM_MARKER_DATA )
        {
            // Marker data is available in POFF-FRAM
            // Store Marker Data
            s16AggregatedError = s16NVM_WriteData (NVM_DEVICE_ID0,  // Device ID for accessing NVM POFF
                                                   DFM_POFF_USR_AREA_ID,
                                                   eNVM_BLOCKING_MODE,
                                                   &eStatus,
                                                   0,
                                                   (U8*)(void*)pu32Data,
                                                   (U32) u16TempLen);
            if( s16AggregatedError != KB_RET_OK )
            {
                s16AggregatedError = KB_RET_ERR_INTERNAL;
            }

        }
        else
        {
            // Event data is available in NonPOFF-FRAM
            // Store Event Data
            // Check for mode to store an event
            if( eNVMemMode == eDFM_NVMEM_BLOCK_MODE )
            {
                // Store event data in blocking mode
                // As FRAM queues are not UP before initialization, this mode should be used during initialization only
                // For the data which need to be written or Read during initialization
                s16AggregatedError = s16NVM_WriteData (NVM_DEVICE_ID1,  // Device ID for accessing NVM FRAM
                                                       DFM_NVM_FWK_AREA_ID,
                                                       eNVM_BLOCKING_MODE,
                                                       &eStatus,
                                                       u16Offset,
                                                       (U8*)(void*)pu32Data,
                                                       (U32) u16TempLen);
            }
            else
            {
                // In queued mode the write request is entered into a free slot in the queue. From there
                // the NVM cyclic operation eventually retrieves and executes it. Depending on the size
                // of the data it may need several passes to finish the request.
                // The result of the operation is written to eStatus.
                // s16DiagDfmAl_WriteData() waits for the result and only exits after receiving it.
                // As the function finishes in a single pass the eStatus may be local. This also allows
                // having multiple instances of the function.
                // There may be multiple read or write requests waiting in the NVM queue at one time.
                // NVM handles them one after the other.
                eStatus = eNVM_STATUS_OPERATION_BUSY;
                // Write DFM data into NV memory - NonPOFF- FRAM
                s16AggregatedError = s16NVM_WriteData (NVM_DEVICE_ID1,  // Device ID for accessing NVM FRAM
                                                       DFM_NVM_FWK_AREA_ID,
                                                       eNVM_QUEUE_MODE,
                                                       &eStatus,
                                                       u16Offset,
                                                       (U8*)(void*)pu32Data,
                                                       (U32) u16TempLen);

                s16AggregatedError = s16DiagDfmAl_WaitRequestResult( s16AggregatedError, &eStatus );

            }

            // Check intermediate result, set internal error in case of failure
            if( s16AggregatedError != KB_RET_OK )
            {
                s16AggregatedError = KB_RET_ERR_INTERNAL;
            }

        }
    }

    return ( s16AggregatedError );

}
//** EndOfFunction s16DiagDfmAl_WriteData ******************************************************************************

//**********************************************************************************************************************
// Function s16DiagDfmAl_Init
//**********************************************************************************************************************
S16 s16DiagDfmAl_Init( void )
{
//************************************************ Function scope data *************************************************
    BOOLEAN boReturn = TRUE;      // Intermediate result variable
    S16 s16RetVal;                // Function return variable

//*************************************************** Function code ****************************************************
    // Inhibit lint warning 466 and note 9074 due to a missing void in boOS_ActivateFct declaration
    //lint -save -e466 -e9074

    // This function will check event in PDU queue for every 200 msec
    boReturn &= boOS_ActivateFct( vDiagDfm_Operation, ( U8 ) eOS_SLICE_200MS );

    // This function will be used to decrement event counter after 20 iteration i.e every 10 sec
    boReturn &= boOS_ActivateFct( vDiagDfm_RETDecCntrs, ( U8 ) eOS_SLICE_500MS );

    //lint -restore

    // Check activation results
    if( boReturn == ( BOOLEAN )TRUE )
    {
        // Functions activated with success, return OK
        s16RetVal = KB_RET_OK;
    }
    else
    {
        // Error in functions activation, return internal error
        s16RetVal = KB_RET_ERR_INTERNAL;
    }

    return( s16RetVal );

}
//** EndOfFunction s16DiagDfmAl_Init ***********************************************************************************


// EndOfFile DiagDfmAl.c ***********************************************************************************************
