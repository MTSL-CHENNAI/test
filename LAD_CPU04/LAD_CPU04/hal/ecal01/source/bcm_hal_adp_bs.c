//**********************************************************************************************************************
//
//                                              bcm_hal_adp_bs.c
//
//**********************************************************************************************************************
//
//                                    Copyrights(c) 2022 by KNORR-BREMSE,
//
//                                       Rail Vehicle Systems, Munich
//
//! @project  IBC
//! @date     2023-10-25
//! @author   C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file bcm_hal_adp_bs.c
//! @brief BCM_HAL - BCM_HAL_ADP Adapter Module - Board specific Implementation
//!
//! BCM_HAL_ADP is a adapter module of BCM_HAL. It implements interfaces to all BCM_HAL components access device
//! specific Software/Hardware resources
//!
//**********************************************************************************************************************
//
// History
// Date            Author              Changes
// 2018-07-10      V.Ingulkar          BC0025-53:bcm_hal_adp_i.h implementation is divided into
//                                     platform specific (bcm_hal_adp_ps.c) and board specific (bcm_hal_adp_bs.c)
//                                     bcm_hal_adp.c is obsolete
// 2018-08-30      R. Dongre           BC0025-57: SSE includes renamed
// 2018-10-23      K. Gade             BC0025-66: Updated 'BCM_HAL_FRAM_BLOCK_ADDR_SIZE' for big-FRAM (128kB). Updated
//                                     s16BCM_HAL_AdpNvMemWrite, s16BCM_HAL_AdpNvMemRead interfaces for addressing.
// 2019-05-06      V.Ingulkar          Updates done as per core asset update v6.0
// 2019-05-15      V.Ingulkar          Added adapter function - s16BCM_HAL_AdpWdrTrigger for raw watchdog trigger
// 2019-08-05      V.Ingulkar          Cleaned up deactivated code
// 2020-10-29      A. Mauro            Lint clean ups
// 2021-01-13      A.Gatare            Adapted for GenCA 6.11
// 2023-01-09      J. Lulli            Coding guidelines alignment
// 2023-10-25      C. Brancolini       Lint Plus cleanup
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "bcl_hal_adc_s.h"              // BCM_HAL_ADC System interface
#include "simcpuwp.h"                   // For cpu temp sensor access
#include "bcl_hal_temp_i.h"             // Board specific temp functionality
#include "simcpu.h"                     // For FRAM access
#include "1wire_hws.h"                  // 1 wire system interface
#include "ds28e01_hws.h"                // CRM chip hardware
#include "sse_crc.h"
#include "bcl_hal_io_i.h"
#include "bcl_hal_io_s.h"
#include "bcl_hal_onn.h"
#include "bcl_mcal_s.h"
#include "55xxsiu_gpio.h"
#include "mpc5554.h"
#include "bcm_hal_onn.h"
#include "IbcSysDefs.h"
#include "bcm_hal_adp_i.h"
//**************************************** Constant / macro definitions ( #define ) ************************************

//! Invalid Node ID
#define BCM_HAL_INVALID_NODE_NO           0xFF
#define BCM_HAL_INVALID_DEVICE_ID         15                    //!< Maximum device ID for IBC

//**************************************** Type definitions ( typedef ) ************************************************

//! States for CPU Temperature sensor
typedef enum
{
    eREAD_TEMP_START = 0,
    eREAD_TEMP_GETVAL,
    eREAD_TEMP_NOINIT
} E_BCM_HAL_CPU_TEMP_STATE;

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

//! Current state of cpu temperature sensor
static E_BCM_HAL_CPU_TEMP_STATE eCpuTempState = eREAD_TEMP_NOINIT;

//** EndOfHeader *******************************************************************************************************

//**********************************************************************************************************************
//
//! @name            BCM_HAL_TEMP Implementation
//
//**********************************************************************************************************************
//@{

//**********************************************************************************************************************
// Function s16BCM_HAL_AdpTempInit
//**********************************************************************************************************************
S16 s16BCM_HAL_AdpTempInit ( U8 u8TempSensor )
{
//******************************** Function scope data *************************************
    S16 s16Return = KB_RET_OK;  // Function return value, initialized at OK

//*********************************** Function code ****************************************
    // Initialize temperature sensor selected by u8TempSensor parameter

    // Check sensor number
    switch (u8TempSensor)
    {
        case 0:
        {
            // Sensor number 0
            // Initialize the temperature sensor setting
            // its current state at Start.
            eCpuTempState = eREAD_TEMP_START;
            break;
        }

        default :
        {
            // Unexpected sensor number, set resource error
            s16Return = KB_RET_ERR_RESOURCE;
            break;
        }
    }

    // Return result
    return (s16Return);
}
//** EndOfFunction s16BCM_HAL_AdpTempInit ***************************************************************************


//**********************************************************************************************************************
// Function s16BCM_HAL_AdpTempGetDegCels
//**********************************************************************************************************************
S16 s16BCM_HAL_AdpTempGetDegCels (U8 u8TempSensor, S8* ps8TempDegCels)
{
//************************************************ Function scope data *************************************************
    S16 s16Return = KB_RET_ERR_INTERNAL; // function result, initialized at internal error
    S32 s32Response;                     // intermediate result
    S16 s16TempRaw;                      // variable to read "raw" temperature ([1/100 °C] unit)
    #define CONV_RAW_TO_DEGCELS   100    // conversion factor from raw temperature to °C temperature

//*************************************** Function scope static data declaration ***************************************

//*************************************************** Function code ****************************************************
    // Check sensor number

    if(u8TempSensor == 0U)
    {
        // Sensor number 0

        *ps8TempDegCels = 0; // default return value

        // Check current state of CPU temperature sensor
        switch (eCpuTempState)
        {
            case eREAD_TEMP_NOINIT :
            {
                // Do Nothing
                // Not started yet, send driver error
                s16Return = KB_RET_ERR_DRIVER;
                break;
            }

            case eREAD_TEMP_START :
            {
                // Start reading temperature
                s32Response = s32SIMCPUW_TMP123StartRdTemp();
                // Check result
                if (s32Response >= (S32) 0)
                {
                    // State change
                    eCpuTempState = eREAD_TEMP_GETVAL;
                    // Temperature value is not yet
                    // return error
                    s16Return = KB_RET_ERR_INTERNAL;
                }
                else
                {
                    // Couldnt start temp sensors, return driver error
                    s16Return = KB_RET_ERR_DRIVER;
                }
                break;
            }

            case eREAD_TEMP_GETVAL :
            {
                // Read temperature
                s32Response = s32SIMCPUW_TMP123GetTemper(&s16TempRaw);
                // Check result
                if (s32Response > (S32) 0)
                {
                    // Temperature read
                    // Return degree celsius value.
                    *ps8TempDegCels = (S8) (s16TempRaw / CONV_RAW_TO_DEGCELS);
                    // Change state
                    eCpuTempState = eREAD_TEMP_START;
                    // return success
                    s16Return = KB_RET_OK;
                }
                break;
            }

            default:
            {
                // return error
                s16Return = KB_RET_ERR_INTERNAL;
                break;
            }

        }

    }else{
        // Unexpected sensor number
        *ps8TempDegCels = 0; // default return value
        // Set resource error
        s16Return = KB_RET_ERR_RESOURCE;
    }


    // Return result
    return(s16Return);
}
//** EndOfFunction s16BCM_HAL_AdpTempGetDegCels ************************************************************************
//@}
//** End of BCM_HAL_TEMP Implementation ********************************************************************************


//**********************************************************************************************************************
//
//! @name            BCM_HAL_ONN Implementation
//
//**********************************************************************************************************************
//@{

//**********************************************************************************************************************
// Function s16BCM_HAL_AdpOnnGet
//**********************************************************************************************************************
S16 s16BCM_HAL_AdpOnnGet ( U8* pu8NodeNoSrc, U8* pu8NodeNo )
{
//************************************************ Function scope data *************************************************
    S16                 s16Return = KB_RET_OK;  // Function return
    S16                 s16Response;            // Return value of called intermediate function
    C_BCM_HAL_ONN_DATA  cNodeNoData;            // Node number data

//*************************************** Function scope static data declaration ***************************************

//*************************************************** Function code ****************************************************

    // Check if valid node number is available in nonvolatile memory.
    s16Response = s16BCM_HAL_OnnReadBackup(&cNodeNoData);
    if( s16Response == KB_RET_OK)
    {
        // Valid node number information is available
        // Return last valid node number and source
        *pu8NodeNo = u8VAV_GET(cNodeNoData.u8vavNodeNumber);
        *pu8NodeNoSrc = u8VAV_GET(cNodeNoData.u8vavNodeNumberSrc);
    }
    else
    {
        // No valid node number information
        // Return default node number
        *pu8NodeNo = IBC_NODE_ID_EXCEPTION_DEFAULT;
        *pu8NodeNoSrc = BCM_COMMON_SOURCE_DEFAULT;
    }

    // Return result - Always return success
    return( s16Return );

}
//** EndOfFunction s16BCM_HAL_AdpOnnGet ********************************************************************************
//@}
//** End of BCM_HAL_ONN Implementation *********************************************************************************

//**********************************************************************************************************************
//
//! @name            BCM_HAL_ID Implementation
//
//**********************************************************************************************************************
//@{

//**********************************************************************************************************************
// Function s16BCM_HAL_AdpIdGet
//**********************************************************************************************************************
S16 s16BCM_HAL_AdpIdGet (U8* pu8DeviceId, U8* pu8DeviceIdSrc)
{
//************************************************ Function scope data *************************************************
    S16 s16Return;
    S16 s16Response = 0; //TODO: initialize with negative value?

//*************************************** Function scope static data declaration ***************************************

//*************************************************** Function code ****************************************************

    if (pu8DeviceId != KB_NULL_PTR)
    {
        // Pointer pu8DeviceId is defined
        // Get the device Id from front connector (value returned via pu8DeviceId)
        s16Response = s16BCL_HAL_ONN_GetSrcFrontConnector(BCM_HAL_INVALID_DEVICE_ID, pu8DeviceId);

        if ((pu8DeviceIdSrc != KB_NULL_PTR) && (s16Response == BCL_HAL_ONN_OK ))
        {
            // Pointer pu8DeviceIdSrc is defined and the device Id has been return with success
            // Update pu8DeviceIdSrc with source information: Front Panel
            *pu8DeviceIdSrc = BCM_COMMON_SOURCE_FP;
        }
    }

    // Check response: 0 in case of success, < 0 otherwise
    if (s16Response < 0)
    {
        // negative response
        // return driver error
        s16Return = KB_RET_ERR_DRIVER;
    }
    else
    {
        // return success
        s16Return = KB_RET_OK;
    }

    // Return result
    return ( s16Return);
}
//** EndOfFunction s16BCM_HAL_AdpIdGet *********************************************************************************

//@}
//** End of BCM_HAL_ID Implementation **********************************************************************************


//**********************************************************************************************************************
//
//! @name            BCM_HAL_OWM Implementation
//
//**********************************************************************************************************************
//@{

//**********************************************************************************************************************
// Function s16BCM_HAL_AdpOwmInit
//**********************************************************************************************************************
S16 s16BCM_HAL_AdpOwmInit (U8 u8DevId, C_BCM_COMMON_OWM_ROMID* pcRomId)
{
//************************************************ Function scope data *************************************************
    S16 s16Return = KB_RET_OK;
    S16 s16Response;

    //Note: Suppression of "Wrong derived data type", this warning comes from
    //      the naming convention violation of OWR_DEV_ROM_NUMBER
    OWR_DEV_ROM_NUMBER cRomID; // @suppress("Wrong derived data type")

//*************************************** Function scope static data declaration ***************************************

//*************************************************** Function code ****************************************************

    if ( u8DevId == 0U )
    {
        // Initialize DS28E01 device
        s16Response = s16DS28E01Init();
        // Check if device is initialized successfully
        if( s16Response == OWR_OK )
        {
            // Device initialized successfully
            // Now get ROM Id of the device identified by u8DevId
            s16Response = s16DS28E01GetROMID( u8DevId, &cRomID);
            if( s16Response == OWR_OK )
            {
                //return ROM id via pcRomId parameter
                pcRomId->u64RomId = cRomID.u64Raw;
            }
            else
            {
                // Failed to get Device Id, return error
                s16Return = KB_RET_ERR_DRIVER;
            }
        }
        else
        {
            // Failed to initialize device, return error
            s16Return = KB_RET_ERR_DRIVER;
        }
    }
    else
    {
        // Currently, only one device is configured, return error
        s16Return = KB_RET_ERR_ARG;
    }

    // Return result
    return (s16Return);
}
//** EndOfFunction s16BCM_HAL_AdpOwmInit *******************************************************************************


//**********************************************************************************************************************
// Function boBCM_HAL_AdpOwmIsDeviceConnected
//**********************************************************************************************************************
BOOLEAN boBCM_HAL_AdpOwmIsDeviceConnected (U8 u8DevId )
{
//************************************************ Function scope data *************************************************
    BOOLEAN boReturn = TRUE;                // Default return is true

//*************************************** Function scope static data declaration ***************************************

//*************************************************** Function code ****************************************************

    // just to avoid waring for now, must be updated board specific
    (void)u8DevId;

    // Return result
    return (boReturn);
}
//** EndOfFunction boBCM_HAL_AdpOwmIsDeviceConnected *******************************************************************


//**********************************************************************************************************************
// Function s16BCM_HAL_AdpOwmReadPage
//**********************************************************************************************************************
S16 s16BCM_HAL_AdpOwmReadPage ( U8 u8DevId, U8 u8PageNo, U16 u16Offset, U16 u16Length, U8* pu8Buffer )
{
//************************************************ Function scope data *************************************************
    S16 s16Return;                  // Function return
    S16 s16Response;                // Response of called function
//*************************************** Function scope static data declaration ***************************************

//*************************************************** Function code ****************************************************

    if ( u8DevId == 0U )
    {
        // Call DS28E01 function to read page
        s16Response = s16DS28E01ReadMemoryPage( u8DevId, u8PageNo, u16Offset, u16Length, (void*)pu8Buffer);
        // Check for response
        // This function returns count of read bytes, which is always u16Length in successful cases
        if( s16Response < OWR_OK )
        {
            // Failed to read data - return error
            s16Return = KB_RET_ERR_DRIVER;
        }
        else
        {
            // Data read successfully
            s16Return = KB_RET_OK;
        }
    }
    else
    {
        // Currently, only one device is configured, return error
        s16Return = KB_RET_ERR_ARG;
    }
    // Return Value
    return (s16Return);
}
//** EndOfFunction s16BCM_HAL_AdpOwmReadPage ***************************************************************************


//**********************************************************************************************************************
// Function s16BCM_HAL_AdpOwmWritePage
//**********************************************************************************************************************
S16 s16BCM_HAL_AdpOwmWritePage ( U8 u8DevId, U8 u8PageNo, U16 u16Offset, U16 u16Length, U8* pu8Buffer )
{
//************************************************ Function scope data *************************************************
    S16 s16Return;                  // Function return
    S16 s16Response;                // Response of called function

//*************************************** Function scope static data declaration ***************************************

//*************************************************** Function code ****************************************************

    if ( u8DevId == 0U )
    {
        // Call DS28E01 function to write page

        // first write required buffer
        s16Response = s16DS28E01WriteMemoryBuffer( u8DevId, u8PageNo, u16Offset, u16Length, (void*)pu8Buffer);
        // Check for response
        // This function returns count of read bytes, which is always u16Length in successful cases
        if( s16Response < OWR_OK )
        {
            // Failed to write data - return error
            s16Return = KB_RET_ERR_DRIVER;
        }
        else
        {
            // Data written successfully to buffer
            // Now write buffered data to requested page
            s16Response = s16DS28E01WriteMemoryPage( u8DevId, u8PageNo );
            if( s16Response < OWR_OK )
            {
                // Failed to write data - return error
                s16Return = KB_RET_ERR_DRIVER;
            }
            else
            {
                // Return success
                s16Return = KB_RET_OK;
            }
        }
    }
    else
    {
        // Currently, only one device is configured, return error
        s16Return = KB_RET_ERR_ARG;
    }

    // Return Value
    return (s16Return);
}
//** EndOfFunction s16BCM_HAL_AdpOwmWritePage **************************************************************************

//@}
//** End of BCM_HAL_OWM Implementation *********************************************************************************

//**********************************************************************************************************************
// Function s16BCM_HAL_AdpWdTrigger
//**********************************************************************************************************************
S16 s16BCM_HAL_AdpWdTrigger ( void )
{
//************************************************ Function scope data *************************************************
    S16     s16Return;            // function result
    S16     s16Response;          // intermediate result
    U16     u16Pcr;               // PCR number of watchdog pin
    BOOLEAN boStatus;             // watchdog pin current status
    BOOLEAN boStatusNew;          // watchdog pin next status

//*************************************************** Function code ****************************************************

    // Get the reference of watchdog pin
    s16Response = s16BCL_HAL_GetBinOutPcr( BCL_HAL_IO_IDX_BO_WD, &u16Pcr);

    // Check if pin information retrieved successfully
    if (s16Response == BCL_HAL_NO_ERR)
    {
        // Get current signal level
        s16Response = s16SIUGPOStatus(u16Pcr, &boStatus);

        // Check Result
        if (s16Response < 0)
        {
            // return driver error
            s16Return = KB_RET_ERR_DRIVER;
        }
        else
        {
            // Toggle current level and set it
            boStatusNew = boStatus ^ (BOOLEAN)TRUE;  //@suppress("Not using boolean macros")
            s16Response = s16SIUGPOSet(u16Pcr, boStatusNew);
            // Check Result
            if (s16Response < 0)
            {
                // return driver error
                s16Return = KB_RET_ERR_DRIVER;
            }
            else
            {
                // return success
                s16Return = KB_RET_OK;
            }
        }
    }
    else
    {
        // Failed to read watchdog pin,
        // return resource error
        s16Return = KB_RET_ERR_RESOURCE;
    }

    // Return result
    return (s16Return);
}
//** EndOfFunction s16BCM_HAL_AdpWdTrigger *****************************************************************************

//**********************************************************************************************************************
// Function s16BCM_HAL_AdpWdrTrigger
//**********************************************************************************************************************
S16 s16BCM_HAL_AdpWdrTrigger ( void )
{
//************************************************ Function scope data *************************************************
    S16     s16Return;
    S16     s16Response;
    U16     u16Pcr;
    BOOLEAN boStatus;
    BOOLEAN boStatusNew;

//*************************************** Function scope static data declaration ***************************************

//*************************************************** Function code ****************************************************

    // Get the reference of watchdog pin
    s16Response = s16BCL_HAL_GetBinOutPcr( BCL_HAL_IO_IDX_BO_WD, &u16Pcr);

    // Check if pin information retrieved successfully
    if (s16Response == BCL_HAL_NO_ERR)
    {
        // inhibit lint message related to GenMPC55xx.
        //lint -save -e9048 -e9078
        boStatus = SIU.GPDO[u16Pcr].B.PDO; //@suppress("Not using boolean macros")
        //lint -restore
        boStatusNew = boStatus^(BOOLEAN)TRUE; //@suppress("Not using boolean macros")
        //lint -save -e9048 -e9078
        SIU.GPDO[u16Pcr].B.PDO = boStatusNew; //@suppress("Not using boolean macros")
        //lint -restore
        s16Return = KB_RET_OK;
    }
    else
    {
        // return error
        s16Return = KB_RET_ERR_RESOURCE;
    }

    // Return result
    return (s16Return);
}
//** EndOfFunction s16BCM_HAL_AdpWdrTrigger *****************************************************************************


//** EndOfFile bcm_hal_adp_bs.c ****************************************************************************************
