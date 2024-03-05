//**********************************************************************************************************************
//
//                                                   DiagDsmNvMem.c
//
//**********************************************************************************************************************
//
//                                        Copyrights(c) 2022 by KNORR-BREMSE,
//                                    Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   IBC
//! @date      2023-11-30
//! @author    C. Brancolini
//!
//!
//**********************************************************************************************************************
//!
//! @file   FwkAlDiagDsmNvMem.c
//! @brief  Diag DSM Adaption Layer source file
//!
//**********************************************************************************************************************
//
// History
// Date          Author       Changes:
// 2014-06-09    S. Kumbhar   Start
// 2014-09-16    S. Kumbhar   Added CRC check in s16DiagDsmAlNvMem_GetNvMemBackupStatus
// 2017-11-20    F. Heindl    Added #include "FwkAlDsmNvMem.h"
// 2017-12-06    F. Heindl    Replaced U32SSECRC32Dir() by u32SSE_Crc32Dir(),
//                            include sse_hal_crc.h instead of sse_crclib.h
// 2018-06-06    V.Ingulkar   BC0025-35, BC0025-36:Only one user for poff areas, either APP or APP plus FWK
//                            CDO based configuration is introduced
// 2018-05-11    S. Peter     cleanup
// 2018-06-18    F. Heindl    removed #include "bcm_s.h"
// 2018-12-17    F. Heindl    TI0001-54 moved this file from FwkAlDiagDsmNvMem.c
//                            to DiagDsmNvMem.c
//  2019-03-30   V.Ingulkar   Changes done as per Jira - BC0025-113
//  2019-04-11   K. Gade      BC0025-91: Replaced BCM_POFF interfaces with NVM interfaces.
//  2020-12-09   A. Gatare    Adapted for GenCA 6.11
// 2023-01-09    J. Lulli     Coding guidelines alignment
// 2023-11-30   C. Brancolini Lint Plus clean up
//
//**********************************************************************************************************************

//********************************************* Compiler options ( #pragma ) *******************************************

//***************************************** Header / include files ( #include ) ****************************************
#include "kb_types.h"
// Inhibit lint errors related to FWK header file
//lint -save -e5469 -e5915 -e4646
#include "DiagDsmTypes.h"
//lint -restore
#include "CoErrno.h"
#include "DiagDsmAlNvMem.h"
#include "FwkAlDsmNvMem.h"
#include "cfg_dsm.h"
#include "sse_crc.h"
#include "bcm.h"
#include <string.h>
#include "nvm.h"                    // NVM interfaces
#include "nvm_common.h"             // NVM Common definitions

//**************************************** Constant / macro definitions ( #define ) ************************************
// DsmNvMemFormatVer and Simple Root cause length for CRC calculation
#define DIAG_DSM_SIMPLE_RC_MEM_FORMAT_VER_LEN   sizeof(cDiagDsmAlData.u32DsmNvMemFormatVer) // @suppress("No upper case suffix for integer constants")
#define DIAG_DSM_SIMPLE_RC_DATA_LEN             sizeof(cDiagDsmAlData.acDiagDsmAlSimpleRCData) // @suppress("No upper case suffix for integer constants")
#define DIAG_DSM_SIMPLE_RC_BUFF_LEN             ( DIAG_DSM_SIMPLE_RC_MEM_FORMAT_VER_LEN + \
                                                  DIAG_DSM_SIMPLE_RC_DATA_LEN )

// Detail Root cause buffer length for CRC calculation
#define DIAG_DSM_DETAIL_RC_BUFF_LEN     ( sizeof(cDiagDsmAlData.au32DsmAlDetailRC) ) // @suppress("No upper case suffix for integer constants")

// NV Memory is 4 byte aligned
#define DIAG_DSM_DETAIL_RC_SIZE_BYTE    ( C_DIAG_DSM_SIZE_DTLD_RC_TABLE_IN_BYTES + \
                                         (C_DIAG_DSM_SIZE_DTLD_RC_TABLE_IN_BYTES % 4) )

#define DIAG_DSM_DETAIL_RC_SIZE_U32     ( DIAG_DSM_DETAIL_RC_SIZE_BYTE / 4 )

//************************************************ Type definitions ( typedef ) ****************************************
//! Structure for FRAM DSM State ID and Simple Root cause
typedef struct
{
  U8 u8SimpleStateValue :1;  //!< Simple State Value
  U8 u8DegradationStateValue :1;  //!< Degradation State Value
  U8 u8SimpleRootCause :5; //!< Simple Root cause
  U8 u8Reserved :1; //!< Reserved bit
} C_DIAG_DSMAL_SIMPLE_RC_DATA;

//! Structure for FRAM DSM data
typedef struct
{
    //!< Diag Dsm NvMemory Format Version
    U32 u32DsmNvMemFormatVer;
    //!< Struct for Simple Root cause data
    C_DIAG_DSMAL_SIMPLE_RC_DATA acDiagDsmAlSimpleRCData[C_DIAG_DSM_MAX_NR_STATEOBJECTS];
    //!< CRC over DsmNvMemFormatVer and Simple Root cause data
    U32 u32DsmAlSimpleRCDataCRC;
    //!< Struct for Detail Root cause data
    U32 au32DsmAlDetailRC[DIAG_DSM_DETAIL_RC_SIZE_U32];
    //!< CRC over Diag DSM Detail Root cause data
    U32 u32DsmAlDetailRCDataCRC;
} C_DIAG_DSMAL_DATA;

//************************************************ Global scope data definitions ***************************************

//**************************************** Global scope read only definitions ( const ) ********************************

//********************************************** Module scope data segment ( static ) **********************************
static U32 u32DiagDsmAlPrevDsmFormatVer = 0; // Prev Diag DMS format version
static C_DIAG_DSMAL_DATA cDiagDsmAlData;     // Diag DSM NV memory data copy


//*************************************** Module scope read only variables ( static const ) ****************************

//****************************************** Module scope func/proc prototypes ( static )*******************************

//** EndOfHeader *******************************************************************************************************

//**********************************************************************************************************************
// Function s16DiagDsmAlNvMem_init
//**********************************************************************************************************************
S16 s16DiagDsmAlNvMem_init(const U32 u32DiagDsmNvMemFormatVersion)
{
//************************************************ Function scope data *************************************************
    S16 s16Ret;                                                     // Function result variable
    E_NVM_OPERATION_STATUS eStatus = eNVM_STATUS_OPERATION_INIT;    // Local variable for operation status

//*************************************************** Function code ****************************************************

    // Get all DSM data in cDiagDsmAlData from NV memory
    s16Ret = s16NVM_ReadData(NVM_DEVICE_ID0,  // Device ID for accessing NVM
        DSM_POFF_USR_AREA_ID,
        eNVM_BLOCKING_MODE,
        &eStatus,
        0,
        (U8*) (void*) &cDiagDsmAlData,
        (U32) sizeof(cDiagDsmAlData));

    // Check result
    if (s16Ret == KB_RET_OK)
    {
        // DSM data read with success
        // Save Previous Diag DMS format version
        u32DiagDsmAlPrevDsmFormatVer = cDiagDsmAlData.u32DsmNvMemFormatVer;
        // Write the version passed as parameter in cDiagDsmAlData struct
        cDiagDsmAlData.u32DsmNvMemFormatVer = u32DiagDsmNvMemFormatVersion;
        s16Ret = CO_ERROR_NONE;
    }
    else
    {
        // Error reading data from NV memory, set internal error
        s16Ret = CO_ERROR_INTERNAL;
    }

    // Return result
    return( s16Ret );
}
//** EndOfFunction s16DiagDsmAlNvMem_init ******************************************************************************


//**********************************************************************************************************************
// Function s16DiagDsmAlNvMem_StartUpdate
//**********************************************************************************************************************
S16 s16DiagDsmAlNvMem_StartUpdate(void)
{
//************************************************ Function scope data *************************************************

//*************************************************** Function code ****************************************************
    return( CO_ERROR_NONE ); // Return ok
}
//** EndOfFunction s16DiagDsmAlNvMem_StartUpdate ***********************************************************************

//**********************************************************************************************************************
// Function s16DiagDsmAlNvMem_FinishUpdate
//**********************************************************************************************************************
S16 s16DiagDsmAlNvMem_FinishUpdate(void)
{
//************************************************ Function scope data *************************************************
    S16 s16Ret;                     // Function return variable
    U32 u32CalculatedCRC;           // Variable for CRC
    U32 u32BuffLength;              // Variable for buffer len
    E_NVM_OPERATION_STATUS eStatus = eNVM_STATUS_OPERATION_INIT;    // Local variable for operation status

//*************************************************** Function code ****************************************************
    // Calculate CRC over Diag DSM DsmNvMemFormatVer and Simple Root cause data
    u32CalculatedCRC = u32SSE_Crc32Dir((U8 *) &cDiagDsmAlData,
        (U32) DIAG_DSM_SIMPLE_RC_BUFF_LEN,
        (U32) 0,
        SSE_CRC32_CCITT_POLY);

    // Update cDiagDsmAlData struct with the CRC
    cDiagDsmAlData.u32DsmAlSimpleRCDataCRC = u32CalculatedCRC;
    u32BuffLength = (U32) (DIAG_DSM_SIMPLE_RC_BUFF_LEN +
        sizeof(cDiagDsmAlData.u32DsmAlSimpleRCDataCRC));

    // Write cDiagDsmAlData struct in Non Volatile Memory
    s16Ret = s16NVM_WriteData(NVM_DEVICE_ID0,  // Device ID for accessing NVM
        DSM_POFF_USR_AREA_ID,
        eNVM_BLOCKING_MODE,
        &eStatus, 0,
        (U8*) (void*) &cDiagDsmAlData,
        (U32) u32BuffLength);

    // Check result
    if (s16Ret == KB_RET_OK)
    {
        // No error
        s16Ret = CO_ERROR_NONE;
    }
    else
    {
        // An error has occurred, set internal error
        s16Ret = CO_ERROR_INTERNAL;
    }

    // Return result
    return( s16Ret );
}
//** EndOfFunction s16DiagDsmAlNvMem_FinishUpdate **********************************************************************


//**********************************************************************************************************************
// Function s16DiagDsmAlNvMem_GetNvMemBackupStatus
//**********************************************************************************************************************
S16 s16DiagDsmAlNvMem_GetNvMemBackupStatus(
    BOOLEAN* const pboBackupAvailable,         //lint !e9072 Parameter violating naming convention in header
    U32* const pu32DiagDsmNvMemFormatVersion)  //lint !e9072 Parameter violating naming convention in header
{
//************************************************ Function scope data *************************************************
    S16 s16Ret;                         // Function return variable
    U32 u32CalculatedSimpleRCCRC;       // Variable for Simple Root Cause CRC
    U32 u32CalculatedDetailRCCRC;       // Variable for Detail Root Cause CRC

//*************************************************** Function code ****************************************************
    // Check the pointers are not null
    if ((pboBackupAvailable != KB_NULL_PTR) && (pu32DiagDsmNvMemFormatVersion != KB_NULL_PTR))
    {
        // Calculate and verify DsmNvMemFormatVer and Simple Root cause CRC
        u32CalculatedSimpleRCCRC = u32SSE_Crc32Dir((U8 *) &cDiagDsmAlData,
            (U32) DIAG_DSM_SIMPLE_RC_BUFF_LEN,
            (U32) 0,
            (U32) SSE_CRC32_CCITT_POLY);

        // Calculate and verify Detail Root cause CRC
        // Inhibit lint warning 545 (taking address of array)
        u32CalculatedDetailRCCRC = u32SSE_Crc32Dir((U8 *) &cDiagDsmAlData.au32DsmAlDetailRC, //lint !e545
            (U32) DIAG_DSM_DETAIL_RC_BUFF_LEN,
            (U32) 0,
            (U32) SSE_CRC32_CCITT_POLY);

        // Verify calculated CRC and NV memory CRC
        if ((u32CalculatedSimpleRCCRC == cDiagDsmAlData.u32DsmAlSimpleRCDataCRC)
            && (u32CalculatedDetailRCCRC == cDiagDsmAlData.u32DsmAlDetailRCDataCRC))
        {
            // CRC values are ok

            // Check Diag DMS Format Version
            if (u32DiagDsmAlPrevDsmFormatVer == cDiagDsmAlData.u32DsmNvMemFormatVer)
            {
                // Diag DMS Format Version is unchanged
                // Backup available
                *pboBackupAvailable = TRUE;
            }
            else
            {
                // No backup available
                *pboBackupAvailable = FALSE;
            }
            // Return ok
            s16Ret = CO_ERROR_NONE;
        }
        else
        {
            // Failure at check of calculated CRC and Non Volatile Memory CRC
            // No backup available
            *pboBackupAvailable = FALSE;
            // Set internal error
            s16Ret = CO_ERROR_INTERNAL;
        }
        // Return Diag DMS Format Version via pu32DiagDsmNvMemFormatVersion
        *pu32DiagDsmNvMemFormatVersion = u32DiagDsmAlPrevDsmFormatVer;
    }
    else
    {
        // Null pointer, set argument error
        s16Ret = CO_ERROR_ARG;
    }

    // Return result
    return( s16Ret );
}
//** EndOfFunction s16DiagDsmAlNvMem_GetNvMemBackupStatus **************************************************************

//**********************************************************************************************************************
// Function s16DiagDsmAlNvMem_UpdateSingleE
//**********************************************************************************************************************
S16 s16DiagDsmAlNvMem_UpdateSingleE(const U16 u16Index,
    const E_DIAG_DSM_SIMPLE_STATE_VALUE eSimpleStateValue,
    const E_DIAG_DSM_DEGRADATION_STATE_VALUE eDegradationStateValue,
    const T_DIAG_DSM_SIMPLE_ROOTCAUSE cSimpleRootCause)
{
//************************************************ Function scope data *************************************************

    S16 s16Ret;    // Function return variable

//*************************************************** Function code ****************************************************
    // Check index range
    if( u16Index < C_DIAG_DSM_MAX_NR_STATEOBJECTS )
    {
        // Update the entry selected by the index with the values passed by function parameters:
        // simple state value, degradation state value and simple root cause
        cDiagDsmAlData.acDiagDsmAlSimpleRCData[u16Index].u8SimpleStateValue = (U8)eSimpleStateValue;
        cDiagDsmAlData.acDiagDsmAlSimpleRCData[u16Index].u8DegradationStateValue = (U8)eDegradationStateValue;
        cDiagDsmAlData.acDiagDsmAlSimpleRCData[u16Index].u8SimpleRootCause = (U8)cSimpleRootCause;
        cDiagDsmAlData.acDiagDsmAlSimpleRCData[u16Index].u8Reserved = 0; // set reserved field at zero
        // Return OK
        s16Ret = CO_ERROR_NONE;
    }
    else
    {
        // The index is out of range, set argument error
        s16Ret = CO_ERROR_ARG;
    }

    // Return result
    return( s16Ret );
}
//** EndOfFunction s16DiagDsmAlNvMem_UpdateSingleE *********************************************************************

//**********************************************************************************************************************
// Function s16DiagDsmAlNvMem_GetSingleE
//**********************************************************************************************************************
S16 s16DiagDsmAlNvMem_GetSingleE(const U16 u16Index, E_DIAG_DSM_SIMPLE_STATE_VALUE* const peSimpleStateValue,
    E_DIAG_DSM_DEGRADATION_STATE_VALUE* const peDegradationStateValue,
    T_DIAG_DSM_SIMPLE_ROOTCAUSE* const pcSimpleRootCause)
{
//************************************************ Function scope data *************************************************
    S16 s16Ret;    // Function return variable

//*************************************************** Function code ****************************************************
    // Check index range and if there is a null pointer parameter
    if( (u16Index < C_DIAG_DSM_MAX_NR_STATEOBJECTS) && (peSimpleStateValue != KB_NULL_PTR)
        && (peDegradationStateValue != KB_NULL_PTR) && (pcSimpleRootCause != KB_NULL_PTR) )
    {
        // Index is in range and pointers are not null
        // Get Simple State, Degradation State and Simple Root Cause of the entry selected by index
        *peSimpleStateValue =
          (E_DIAG_DSM_SIMPLE_STATE_VALUE)cDiagDsmAlData.acDiagDsmAlSimpleRCData[u16Index].u8SimpleStateValue;
        *peDegradationStateValue =
          (E_DIAG_DSM_DEGRADATION_STATE_VALUE)cDiagDsmAlData.acDiagDsmAlSimpleRCData[u16Index].u8DegradationStateValue;
        *pcSimpleRootCause =
          (T_DIAG_DSM_SIMPLE_ROOTCAUSE)cDiagDsmAlData.acDiagDsmAlSimpleRCData[u16Index].u8SimpleRootCause;
        // Return OK
        s16Ret = CO_ERROR_NONE;
    }
    else
    {
        // Index out of range or null pointer parameter
        // Set argument error
        s16Ret = CO_ERROR_ARG;
    }

    // Return result
    return s16Ret;
}
//** EndOfFunction s16DiagDsmAlNvMem_GetSingleE ************************************************************************

//**********************************************************************************************************************
// Function s16DiagDsmAlNvMem_GetDtldRcTbl
//**********************************************************************************************************************
S16 s16DiagDsmAlNvMem_GetDtldRcTbl(T_DIAG_DSM_DTLDRC_NVMEM_DATA_BUFFER* const pcDetailedRootCauseTable)
{
//************************************************ Function scope data *************************************************
    S16 s16Ret;    // Function return variable

//*************************************************** Function code ****************************************************
    // Check if there is a null pointer parameter
    if (pcDetailedRootCauseTable != KB_NULL_PTR)
    {
        //The pointer is not null

        // Copy Detailed Root Cause Table from the copy of the non volatile diag DSM memory data
        //  to the structure pointed by the pcDetailedRootCauseTable parameter
        if( KB_NULL_PTR == memcpy((void *) pcDetailedRootCauseTable, (void *)
            cDiagDsmAlData.au32DsmAlDetailRC, DIAG_DSM_DETAIL_RC_SIZE_BYTE) )
        {
            // An error has occurred coping the Detailed Root Cause Table, set internal error
            s16Ret = CO_ERROR_INTERNAL;
        }
        else
        {
            // Detailed Root Cause Table copied with success, return OK
            s16Ret = CO_ERROR_NONE;
        }
    }
    else
    {
        // Null pointer parameter, set argument error
        s16Ret = CO_ERROR_ARG;
    }

    // Return result
    return( s16Ret );
}
//** EndOfFunction s16DiagDsmAlNvMem_GetDtldRcTbl **********************************************************************

//**********************************************************************************************************************
// Function s16DiagDsmAlNvMem_SetDtldRcTbl
//**********************************************************************************************************************
S16 s16DiagDsmAlNvMem_SetDtldRcTbl(T_DIAG_DSM_DTLDRC_NVMEM_DATA_BUFFER* const pcDetailedRootCauseTable)
{
//************************************************ Function scope data *************************************************
    S16  s16Ret;                  // function return variable
    U32  u32CalculatedCRC = 0;    // local variable for CRC
    U32  u32BuffLength;           // local variable for buffer length in bytes
    U32  u32PoffBuffAddress;      // local variable for offset in area, to write data, in bytes
    U32* pu32DiagDsmDetailRCData = cDiagDsmAlData.au32DsmAlDetailRC; // pointer to detailed root cause structure
    E_NVM_OPERATION_STATUS eStatus = eNVM_STATUS_OPERATION_INIT;     // local variable for operation status

//*************************************************** Function code ****************************************************

    // Check if there is a null pointer parameter
    if( pcDetailedRootCauseTable != KB_NULL_PTR )
    {
        // Copy Detailed Root Cause Table
        if( KB_NULL_PTR == memcpy((void *) cDiagDsmAlData.au32DsmAlDetailRC,
            (void *) pcDetailedRootCauseTable, DIAG_DSM_DETAIL_RC_SIZE_BYTE) )
        {
            // An error has occurred coping the Detailed Root Cause Table, set internal error
            s16Ret = CO_ERROR_INTERNAL;
        }
        else
        {
            // Calculate CRC over Diag DSM DsmNvMemFormatVer and Simple Root cause data
            // Inhibit lint warning 545 (taking address of array)
            u32CalculatedCRC = u32SSE_Crc32Dir((U8 *) &cDiagDsmAlData.au32DsmAlDetailRC, //lint !e545
                (U32)DIAG_DSM_DETAIL_RC_BUFF_LEN,
                (U32) 0,
                SSE_CRC32_CCITT_POLY);

            // Write CRC to cDiagDsmAlData
            cDiagDsmAlData.u32DsmAlDetailRCDataCRC = u32CalculatedCRC;
            // Compute buffer len and offset in area, to write data, in bytes
            // to write detailed root cause CRC in the non volatile memory
            u32BuffLength = DIAG_DSM_DETAIL_RC_BUFF_LEN + sizeof(cDiagDsmAlData.u32DsmAlDetailRCDataCRC);
            u32PoffBuffAddress = (U32)(DIAG_DSM_SIMPLE_RC_BUFF_LEN + sizeof(cDiagDsmAlData.u32DsmAlSimpleRCDataCRC));

            // Write data to the non volatile memory
            s16Ret = s16NVM_WriteData(NVM_DEVICE_ID0,  // Device ID for accessing NVM
                DSM_POFF_USR_AREA_ID,
                eNVM_BLOCKING_MODE,
                &eStatus,
                u32PoffBuffAddress,
                (U8*) (void*) pu32DiagDsmDetailRCData,
                (U32) u32BuffLength);

            // Check result of the write in the non volatile memory
            // and set function return value
            if (s16Ret == KB_RET_OK)
            {
                // data wrote with success, return ok
                s16Ret = CO_ERROR_NONE;
            }
            else
            {
                // an error has occurred, return internal error
                s16Ret = CO_ERROR_INTERNAL;
            }
        }
    }
    else
    {
        // Null pointer parameter, return argument error
        s16Ret = CO_ERROR_ARG;
    }

    return( s16Ret );
}
//** EndOfFunction s16DiagDsmAlNvMem_SetDtldRcTbl **********************************************************************


//** EndOfFile FwkAlDiagDsmNvMem.c *************************************************************************************
