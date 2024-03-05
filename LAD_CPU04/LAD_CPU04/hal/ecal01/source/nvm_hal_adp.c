//**********************************************************************************************************************
//
//                                                  nvm_hal_adp.c
//
//**********************************************************************************************************************
//
//                                        Copyrights(c) by KNORR-BREMSE
//                                         Rail Vehicle Systems, Munich
//
//! @project   IBC
//! @date      2023-12-06
//! @author    C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file      nvm_hal_adp.c
//! @brief     This file contains board specific implementation of NVM interfaces, which will be in control of
//!            board responsible user.
//!
//!
//**********************************************************************************************************************
//
// History
// Date            Author              Changes
// 2019-04-03      K. Gade             BC0025-91: Start
// 2019-07-15      K. Gade             BC0025-202: Updated code related to Get Device information.
// 2020-10-30      A. Mauro            Lint clean ups.
// 2020-12-02      A. Gatare           Adapted for GenCA 6.11
// 2021-03-04      N. Jadhav           FRAM issue chnages done as per GenCA V06.11
// 2021-09-20      N. Jadhav           GenCA V07.00 adaptation changes.
// 2021-09-22      N. Jadhav           BC0025-529: Workaround changes for area ID offset configuration issue.
// 2021-12-15      N. Jadhav           BC0025-529: Workaround changes removed with integration of CA 07.01.
// 2023-12-06      C. Brancolini       Lint Plus clean up
//
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma )	************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "string.h"                                             // String related interfaces
#include "kb_types.h"                                           // Standard definitions
#include "kb_ret.h"                                             // Global Knorr-Bremse return value definitions
#include "nvm_common.h"                                         // NVM general definitions like DeviceID
#include "nvm_hal.h"                                            // NVM-HAL device information structure dependencies
#include "nvm_hal_adp_i.h"                                      // NVM-HAL board specific interfaces
#include "nvm_hal_bs_i.h"                                       // NVM-HAL device specific definitions
#include "nvm_hal_s.h"                                          // NVM-HAL Poff interfaces
#include "flsh_hal.h"                                           // Flash HAL interfaces
#include "bcm_fwr_rst_s.h"                                      // BCM FWR Reset interfaces
#include "nvm_hal_i.h"                                          // NVM_HAL internal interfaces
#include "cfg_nvm_hal_poff_i.h"                                 // CFG NVM HAL POFF interfaces
#include "fram_hal.h"
#include "bcl_mcal_s.h"                                         // for Cache block flush interface

//**************************************** Constant / macro definitions ( #define ) ************************************

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************

//**************************************** Module global data segment ( static ) ***************************************
static S16 s16NVM_HAL_AdpDeriveAbsoluteMemoryAddress (U8 u8NvmID,
                                                      U32 u32LocalAreaOffset,
                                                      U32* pu32DeviceAddress);

static S16 s16NVM_HAL_AdpReadDeviceID1 (U8 u8NvmID, U8* pu8UsrBuffer,
                                        U32 u32LocalAreaOffset, U32 u32Length);

static S16 s16NVM_HAL_AdpWriteDeviceID1 (U8 u8NvmID, U8* pu8UsrBuffer, U32 u32LocalAreaOffset, U32 u32Length);

//**************************************** Module global constants ( static const ) ************************************

//! Operation status for Device ID 1.
static E_NVM_HAL_DEVICE_STATUS eDeviceOperationStatus = eNVM_HAL_DEVICE_STATUS_FREE;

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *******************************************************************************************************

//**********************************************************************************************************************
// Function s16NVM_HAL_AdpInit
//**********************************************************************************************************************
S16 s16NVM_HAL_AdpInit (U8 u8NvmID)
{
//************************************************ Function scope data *************************************************
    S16 s16Return;                                          // Function Return value

//*************************************************** Function code ****************************************************
    // Execution based upon device type.
    switch (u8NvmID)
    {
        case NVM_DEVICE_ID0 :
        {
            // Device ID 0
            // Clear POFF buffer in case of cold reset
            if (boBCM_FWR_RstIsColdStart() == (BOOLEAN)TRUE)
            {
                // Clear POFF buffer
                memset((void*)au32NVM_HAL_PoffHwBuffer, 0, (size_t)NVM_HAL_POFF_BUFF_SIZE);
            }

            //Need to be called from here first Fram_hal init and then poff_hal init.
            // Otherwise NVM does not initialize and board goes to state Fatal.
            s16Return = s16FRAM_HAL_Init();

            if (s16Return == KB_RET_OK)
            {
                // Initialize POFF HAL for NVM operations
                s16Return = s16NVM_HAL_PoffInit();
            }

            break;
        }

        case NVM_DEVICE_ID1 :
        {
            // Device ID 1
            // FRAM HAL initialization is already done in Device ID 0
            s16Return = KB_RET_OK;
            break;
        }

        case NVM_DEVICE_ID2 :
        {
            // Device ID 2
            // Initialize Flash HAL
            s16Return = s16FLSH_HAL_Init();
            break;
        }

        default:
        {
            // invalid device argument received
            // Note: This condition may not come as nvmID already checked in caller.
            // Return driver error
            s16Return = KB_RET_ERR_DRIVER;
            break;
        }
    }

    // Check, If there is error received in driver initialization
    if (s16Return < KB_RET_OK)
    {
        // An error has occurred
        // It seems like driver is not initialized
        // Return driver error
        s16Return = KB_RET_ERR_DRIVER;
    }

    // Return result
    return (s16Return);
}
//** EndOfFunction s16NVM_HAL_AdpInit***********************************************************************************

//**********************************************************************************************************************
// Function s16NVM_HAL_AdpRead
//**********************************************************************************************************************
S16 s16NVM_HAL_AdpRead (U8 u8NvmID, U8 u8AreaID, U32 u32Offset, U8* pu8UsrBuffer, U32 u32LocalAreaOffset, U32 u32Length)
{
//************************************************ Function scope data *************************************************
    S16 s16Return;                                          // Function Return value
    U32 u32DeviceAddress;                                   // Device address on NVM device

//*************************************************** Function code ****************************************************
    // Note:
    // Exception is made for max allowed nesting (MaxND), this function has nesting 7, max allowed is 5
    // Separating code will reduce understandability and readability

    // Execution based upon device type
    switch (u8NvmID)
    {
        case NVM_DEVICE_ID0 :
        {
            // Device ID 0
            // Pass the READ request to HAL POFF interface
            // Offset handling is part of POFF interface, so received offset is passed
            // Note: 'Offset' for POFF and Non-POFF data handling is kept separate
            s16Return = s16NVM_HAL_PoffReadData(u8AreaID, u32Offset, u32Length, (U32*) (void*) pu8UsrBuffer);
            break;
        }
        case NVM_DEVICE_ID1 :
        {
            // Device ID 1
            s16Return = s16NVM_HAL_AdpReadDeviceID1( u8NvmID, pu8UsrBuffer, u32LocalAreaOffset, u32Length);
            break;
        }
        case NVM_DEVICE_ID2 :
        {
            // Device ID 2
            // Calculation of absolute address
            s16Return = s16NVM_HAL_AdpDeriveAbsoluteMemoryAddress(u8NvmID,
                                                                  u32LocalAreaOffset,
                                                                  &u32DeviceAddress);

            // Pass the READ request to Flash HAL interface
            if (s16Return >= KB_RET_OK)
            {
                // Call Flash interface for Read
                // Data Flash is used for writing Configuration data
                s16Return = s16FLSH_HAL_Read(eFLSH_HAL_TYPE_PFLASH, u32DeviceAddress, pu8UsrBuffer, u32Length);
            }
            break;
        }
        default:
        {
            // DeviceID is not available in configuration, set driver error
            // Note: This condition may not come as nvmID already checked in caller.
            s16Return = KB_RET_ERR_DRIVER;
            break;
        }
    }

    // Check whether Read operation is successful or not
    if (s16Return < KB_RET_OK)
    {
        // Failed to read data
        s16Return = KB_RET_ERR_DRIVER;
    }
    else
    {
        // Read successful
        s16Return = KB_RET_OK;
    }

    // Return result
    return (s16Return);
}
//** EndOfFunction s16NVM_HAL_AdpRead***********************************************************************************

//**********************************************************************************************************************
// Function s16NVM_HAL_AdpWrite
//**********************************************************************************************************************
S16 s16NVM_HAL_AdpWrite (U8 u8NvmID,
                         U8 u8AreaID,
                         U32 u32Offset,
                         U8* pu8UsrBuffer,
                         U32 u32LocalAreaOffset,
                         U32 u32Length)
{
//************************************************ Function scope data *************************************************
    S16 s16Return;                                          // Function Return value
    U32 u32DeviceAddress;                                   // Device address on NVM device

//*************************************************** Function code ****************************************************
    // Note:
    // Exception is made for max allowed nesting (MaxND), this function has nesting 7, max allowed is 5
    // Separating code will reduce understandability and readability.

    // Execution based upon device type
    switch (u8NvmID)
    {
        case NVM_DEVICE_ID0 :
        {
            // Device ID 0
            // Pass the WRITE request to POFF interface
            // Offset handling is part of POFF interface, so received offset is passed
            s16Return = s16NVM_HAL_PoffWriteData(u8AreaID, u32Offset, u32Length, (U32*) (void*)pu8UsrBuffer);
            break;
        }

        case NVM_DEVICE_ID1 :
        {
            // Device ID 1
            s16Return = s16NVM_HAL_AdpWriteDeviceID1 ( u8NvmID, pu8UsrBuffer, u32LocalAreaOffset, u32Length);
            break;
        }

        case NVM_DEVICE_ID2 :
        {
            // Device ID 2
            // Calculation of absolute address
            s16Return = s16NVM_HAL_AdpDeriveAbsoluteMemoryAddress(u8NvmID,
                                                                  u32LocalAreaOffset,
                                                                  &u32DeviceAddress);

            // Data Flash is used for writing configuration data
            // Pass the write request to Flash HAL interface
            // Blocking mode feature is available as a part of Flash Hal
            // Pass the write request to Flash HAL interface
            // Blocking mode feature is available as a part of Flash Hal
            if (s16Return >= KB_RET_OK)
            {
                // Call Flash interface for Writing 'u32Length' on Data Flash
                // Device address is calculated based upon 'Base Address' from configuration
                // if there is any error, it will be returned to the caller
                s16Return = s16FLSH_HAL_Write(eFLSH_HAL_TYPE_PFLASH, u32DeviceAddress,pu8UsrBuffer,u32Length,+ TRUE);
            }

            break;
        }

        default:
        {
            // DeviceID is not available in configuration, set driver error
            // Note: This condition may not come as nvmID already checked in caller.
            s16Return = KB_RET_ERR_DRIVER;
            break;
        }
    }

    // Check whether Write operation is successful or not
    if (s16Return < KB_RET_OK)
    {
        // Failed to write data
        s16Return = KB_RET_ERR_DRIVER;
    }
    else
    {
        // Write data successful
        s16Return = KB_RET_OK;
    }

    // Return result
    return (s16Return);
}
//** EndOfFunction s16NVM_HAL_AdpWrite**********************************************************************************

//**********************************************************************************************************************
// Function s16NVM_HAL_AdpErase
//**********************************************************************************************************************
S16 s16NVM_HAL_AdpErase (U8 u8NvmID, U32 u32Offset, U32 u32Length)
{
//************************************************ Function scope data *************************************************
    S16 s16Return;                                 // Function Return value

//*************************************************** Function code ****************************************************
    // To remove warnings
    (void) u32Length; // unused parameter
    (void) u32Offset; // unused parameter

    // Execution based upon device type
    switch (u8NvmID)
    {
        case NVM_DEVICE_ID0 :
        {
            // Device ID 0
            // There is no Erase interface available in FRAM
            s16Return = KB_RET_OK;

            break;
        }

        case NVM_DEVICE_ID1 :
        {
            // Device ID 1
            // There is no Erase interface available in FRAM
            s16Return = KB_RET_OK;
            break;
        }
        case NVM_DEVICE_ID2 :
        {
            // Device ID 2
            // Flash area identified based upon BankID, SectorNumber
            // Erase operation will be done based on sectors.
            // Complete sector will be erased.
            // Flash sector allocated for LAD CFG will be erased.
            s16Return = s16FLSH_HAL_Erase(eFLSH_HAL_TYPE_PFLASH, NVM_PFLASH_BANK_0, (U8)NVM_PFLASH_SECTOR_0, TRUE);

            // Check whether ERASE operation is successful or not
            if (s16Return < KB_RET_OK)
            {
                // Failed to erase data
                // Error in driver erase functionality.
                s16Return = KB_RET_ERR_DRIVER;
            }
            else
            {
                // Erase successful
                s16Return = KB_RET_OK;
            }
            break;
        }
        default:
        {
            // DeviceID is not available in configuration, set argument error
            s16Return = KB_RET_ERR_ARG;
            break;
        }
    }

    // Check whether Erase operation is successful or not
    if (s16Return < KB_RET_OK)
    {
        // Failed to erase data
        s16Return = KB_RET_ERR_DRIVER;
    }
    else
    {
        // Erase data successful
        s16Return = KB_RET_OK;
    }

    // Return result
    return (s16Return);
}
//** EndOfFunction s16NVM_HAL_AdpErase**********************************************************************************

//**********************************************************************************************************************
// Function s16NVM_HAL_AdpGetDeviceOpernStatus
//**********************************************************************************************************************
S16 s16NVM_HAL_AdpGetDeviceOpernStatus (U8 u8NvmID, E_NVM_HAL_DEVICE_STATUS* peDeviceStatus)
{
//************************************************ Function scope data *************************************************
    S16 s16Return;                                          // Function Return value

//*************************************************** Function code ****************************************************
    // Execution based upon device type
    switch (u8NvmID)
    {
        case NVM_DEVICE_ID0 :
        {
            // Device ID 0
            // we have returned device is 'FREE'
            // there is no need to check, operation status for POFF device.
            s16Return = KB_RET_OK;
            *peDeviceStatus = eNVM_HAL_DEVICE_STATUS_FREE;
            break;
        }

        case NVM_DEVICE_ID1 :
        {
            // Device ID 1
            // Return device status for previous operation.
            // FRAM device works in non-blocking mode.
            // Read operation status is checked after particular command is triggered.
            // Local variable used to update the read operation status.
            s16Return = KB_RET_OK;
            *peDeviceStatus = eDeviceOperationStatus;
            break;
        }

        case NVM_DEVICE_ID2 :
        {
            // Device ID 2
            // Flash device supports 'Blocking Mode' only, so it will always return device status as 'FREE'
            s16Return = KB_RET_OK;
            *peDeviceStatus = eNVM_HAL_DEVICE_STATUS_FREE;
            break;
        }

        default:
        {
            // invalid device argument received, set argument error
            s16Return = KB_RET_ERR_ARG;
            break;
        }
    }

    // Check whether read operation status check is successful or not
    if (s16Return < KB_RET_OK)
    {
        // Failed to update read operation status
        s16Return = KB_RET_ERR_DRIVER;
    }
    else
    {
        // Read operation status check successful
        s16Return = KB_RET_OK;
    }

    // Return result
    return (s16Return);
}
//** EndOfFunction s16NVM_HAL_AdpGetDeviceOpernStatus*********************************************************************

//**********************************************************************************************************************
// Function s16NVM_HAL_AdpPoffWrite
//**********************************************************************************************************************
S16 s16NVM_HAL_AdpPoffWrite (U32 u32DstOffset, U8* pu8SrcAddr, U32 u32Length)
{
//************************************************ Function scope data *************************************************
    S16 s16Return;                                          // Function Return value

//*************************************************** Function code ****************************************************
    // Flush cache of the block
    vBCL_MCAL_CacheFlush(pu8SrcAddr, u32Length);

    // Pass the WRITE request to driver interface
    s16Return = s16FRAM_HAL_Write(u32DstOffset, pu8SrcAddr, u32Length);

    // Check return
    if (s16Return < 0)
    {
        // return error
        s16Return = KB_RET_ERR_DRIVER;
    }
    else
    {
        // Check FRAM status for read command
        while (s16FRAM_HAL_ChkWriteStatus() != KB_RET_OK)
        {
            ; // do nothing
        }
    }

    // Return result
    return (s16Return);
}
//** EndOfFunction s16NVM_HAL_AdpPoffWrite *****************************************************************************

//**********************************************************************************************************************
// Function s16NVM_HAL_AdpPoffRead
//**********************************************************************************************************************
S16 s16NVM_HAL_AdpPoffRead (U32 u32SrcOffset, U8* pu8DstAddr, U32 u32Length)
{
//************************************************ Function scope data *************************************************
    S16 s16Return;                              // Function Return value

//*************************************************** Function code ****************************************************
    // Pass the READ request to driver interface
    s16Return = s16FRAM_HAL_Read(pu8DstAddr, u32SrcOffset, u32Length);

    // Check return
    if (s16Return < 0)
    {
        // return error
        s16Return = KB_RET_ERR_DRIVER;
    }
    else
    {
        // Check FRAM status for read command
        while (s16FRAM_HAL_ChkReadStatus() != KB_RET_OK)
        {
            ; // do nothing
        }
    }

    // Return result
    return (s16Return);
}
//** EndOfFunction s16NVM_HAL_AdpPoffRead ******************************************************************************

//**********************************************************************************************************************
// Function s16NVM_HAL_AdpPoffStart
//**********************************************************************************************************************
S16 s16NVM_HAL_AdpPoffStart (void)
{
//************************************************ Function scope data *************************************************
    S16 s16Return = KB_RET_OK;                     // Function Return value

//*************************************************** Function code ****************************************************

    // Return result
    return (s16Return);
}
//** EndOfFunction s16NVM_HAL_AdpPoffStart ******************************************************************************

//**********************************************************************************************************************
// Function s16NVM_HAL_AdpPoffStop
//**********************************************************************************************************************
S16 s16NVM_HAL_AdpPoffStop (void)
{
//************************************************ Function scope data *************************************************
    S16 s16Return = KB_RET_OK;                    // Function Return value

//*************************************************** Function code ****************************************************

    // Return result
    return (s16Return);
}
//** EndOfFunction s16NVM_HAL_AdpPoffStop ******************************************************************************

// Function s16NVM_HAL_AdpDeriveAbsoluteMemoryAddress
//**********************************************************************************************************************
//! @brief          NVM_HAL-> Get Absolute Address
//!
//! @details        This function calculates absolute address based upon start address available in the configuration
//!                 and offset received from request.
//!
//! @param[in]      u8NvmID            : Device identifier
//! @param[in]      u32LocalAreaOffset : Offset in area
//!
//! @param[in,out]  -
//!
//! @param[out]     pu32DeviceAddress  : Absolute Address retrieved from physical device
//!
//! @return         Return Code
//!                  - KB_RET_OK : Successful execution
//!                  - KB_RET_ERR_INST_PTR : If received pointer is NULL.
//!
//! @remarks        -
//**********************************************************************************************************************
static S16 s16NVM_HAL_AdpDeriveAbsoluteMemoryAddress (U8 u8NvmID,
                                                      U32 u32LocalAreaOffset,
                                                      U32* pu32DeviceAddress)
{
//************************************************ Function scope data *************************************************
    S16 s16Return = KB_RET_OK;                              // Function return value

//*************************************************** Function code ****************************************************
    // Derive memory base address to execute particular command
    if (pu32DeviceAddress != KB_NULL_PTR)
    {
        // Calculation of absolute address; Start Address will be available in HAL configuration
        *pu32DeviceAddress = (U32) (u32LocalAreaOffset + acNVM_HAL_DeviceCfgInfo[u8NvmID].u32StartAddress);
    }
    else
    {
        // null pointer, return error
        s16Return = KB_RET_ERR_INST_PTR;
    }

    // Return Value
    return (s16Return);
}
//** EndOfFunction s16NVM_HAL_AdpDeriveAbsoluteMemoryAddress ***********************************************************


// Function s16NVM_HAL_AdpReadDeviceID1
//**********************************************************************************************************************
//! @brief          This function reads Device ID1
//!
//!
//! @param[in]      u8NvmID            : Device identifier
//!
//! @param[in,out]  pu8UsrBuffer       : Pointing to the user buffer, in which data will be copied from memory location.
//!
//! @param[in]      u32LocalAreaOffset : Memory offset in device ID1 to read data.
//!
//! @param[in]      u32Length          : Number of bytes to read
//!
//!
//! @return         Return Code
//!                  - KB_RET_OK : Successful execution
//!                  - negative value : In case of error.
//!
//! @remarks        -
//**********************************************************************************************************************
static S16 s16NVM_HAL_AdpReadDeviceID1 (U8 u8NvmID,  U8* pu8UsrBuffer, U32 u32LocalAreaOffset, U32 u32Length)
{
//************************************************ Function scope data *************************************************
    S16 s16Return = KB_RET_OK;                              // Function Return value
    U32 u32DeviceAddress;                                   // Device address on NVM device

//*************************************************** Function code ****************************************************
    // Calculation of absolute address, the address is written in u32DeviceAddress variable.
    // Note: s16Return is initialized at 0 (KB_RET_OK) and then updated with the sum of prev. value
    // and the function return value to avoid lint complains
    s16Return += s16NVM_HAL_AdpDeriveAbsoluteMemoryAddress(u8NvmID,
                                                          u32LocalAreaOffset,
                                                          &u32DeviceAddress);

    // If there is no error, then call FRAM interface
    if (s16Return == KB_RET_OK)
    {
        // Pass the READ request to the driver interface. Data is returned via pu8UsrBuffer.
        s16Return = s16FRAM_HAL_Read(pu8UsrBuffer, u32DeviceAddress, u32Length);

        // If no error, proceed for read operation status check.
        if (s16Return == KB_RET_OK)
        {
            // Check FRAM status for read command.
            // Call check read status function until it returns either positive result or driver error
            do
            {
                s16Return = s16FRAM_HAL_ChkReadStatus();

                // Check whether driver error or not.
                // Update device read operation status.
                if (s16Return == KB_RET_ERR_DRIVER)
                {
                    // Driver error, mark device status as ERROR and exit the loop.
                    eDeviceOperationStatus = eNVM_HAL_DEVICE_STATUS_ERROR;
                    break;
                }
                else if (s16Return == KB_RET_OK)
                {
                    // Read operation successful, mark device status as FREE.
                    eDeviceOperationStatus = eNVM_HAL_DEVICE_STATUS_FREE;
                }
                else
                {
                    // Read operation is in progress, mark device status as BUSY.
                    eDeviceOperationStatus = eNVM_HAL_DEVICE_STATUS_BUSY;
                }
            } while (s16Return != KB_RET_OK);
        }
    }
    // Return result
    return s16Return;
}
//** EndOfFunction s16NVM_HAL_AdpReadDeviceID1 **************************************************************************

// Function s16NVM_HAL_AdpWriteDeviceID1
//**********************************************************************************************************************
//! @brief          This function writes Device ID1
//!
//!
//! @param[in]      u8NvmID            : Device identifier
//!
//! @param[in]      pu8UsrBuffer       : Pointing to the user buffer, which contains data to be written into memory device.
//!
//! @param[in]      u32LocalAreaOffset : Offset in area
//!
//! @param[in]      u32Length          : Number of bytes to write
//!
//!
//! @return         Return Code
//!                  - KB_RET_OK : Successful execution
//!                  - negative value : In case of error.
//!
//! @remarks        -
//**********************************************************************************************************************
static S16 s16NVM_HAL_AdpWriteDeviceID1 (U8 u8NvmID, U8* pu8UsrBuffer, U32 u32LocalAreaOffset, U32 u32Length)
{
//************************************************ Function scope data *************************************************
    S16 s16Return = KB_RET_OK;                              // Function Return value
    U32 u32DeviceAddress;                                   // Device address on NVM device

//*************************************************** Function code ****************************************************
    // Calculation of absolute address, the address is written in u32DeviceAddress variable.
    // Note: s16Return is initialized at 0 (KB_RET_OK) and then updated with the sum of prev. value
    // and the function return value to avoid lint complains
    s16Return += s16NVM_HAL_AdpDeriveAbsoluteMemoryAddress(u8NvmID,
                                                          u32LocalAreaOffset,
                                                          &u32DeviceAddress);

    // Pass the WRITE request to driver interface
    // DeviceAddress will be updated based upon 'Base Address' & 'u32LocalAreaOffset' value
    if (s16Return == KB_RET_OK)
    {
        // Call Fram Drive interface for writing 'u32Length' bytes
        s16Return = s16FRAM_HAL_Write(u32DeviceAddress, pu8UsrBuffer, u32Length);

        // If no error, proceed with write operation status.
        if (s16Return == KB_RET_OK)
        {
            // Check FRAM status for write command
            // Call check write status function until it returns either positive result or driver error
            do
            {
                s16Return = s16FRAM_HAL_ChkWriteStatus();

                // Check whether driver error or not.
                if (s16Return == KB_RET_ERR_DRIVER)
                {
                    // Driver error, mark device status as ERROR and exit the loop.
                    eDeviceOperationStatus = eNVM_HAL_DEVICE_STATUS_ERROR;
                    break;
                }
                else if (s16Return == KB_RET_OK)
                {
                    // Write operation successful, mark device status as FREE.
                    eDeviceOperationStatus = eNVM_HAL_DEVICE_STATUS_FREE;
                }
                else
                {
                    // Write operation is in progress, mark device status as BUSY.
                    eDeviceOperationStatus = eNVM_HAL_DEVICE_STATUS_BUSY;
                }
            } while (s16Return != KB_RET_OK);
        }
    }
    return s16Return;
}
//** EndOfFunction s16NVM_HAL_AdpWriteDevID1 ***************************************************************************

//** EndOfFile nvm_hal_adp.c *******************************************************************************************
