//****************************************************************************
//
//                              bcl_hal_onn.c
//
//****************************************************************************
//
//                    Copyrights(c) 2022 by KNORR-BREMSE,
//               Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project  IBC
//! @date     2023-10-25
//! @author   C.Brancolini
//
//****************************************************************************
//
//! @file
//! @brief  BCL_HAL - Handling of the boards own node number
//
//****************************************************************************
// Date        Author      Changes:
// 2012-11-07  P. Sigl     Start
// 2013-02-15  C. Baeuml   IBC extensions.
// 2013-03-15  C. Baeuml   Additional function
//                         s16BCL_GNN_GetNN_IBC_Startup.
// 2013-04-08  P. Sigl     Redundant function headers removed
// 2013-07-15  S. Kumbhar  Changes as per new DRC framework
// 2013-07-26  P. Sigl     Parameter checks added.
// 2013-10-16  P. Sigl     Allow node number 30.
// 2013-10-31  C. Baeuml   Code Review, see TODO comments;
//                         Avoidance of Warnings.
// 2013-11-07  S. Kumbhar  Updated as per code review comments
// 2013-11-18  P. Sigl     2nd look for SC and FC added.
//                         NODE_NO_0 not allowed.
//                         s16BCL_HAL_ONN_Get(): Obsolete parameter check
//                         removed.
// 2014-05-14  C. Baeuml   Adaptation for IBC Device ID.
// 2014-05-27  C. Baeuml   Handling of IBC_INVALID_NODE_NO.
// 2014-06-04  S. Kumbhar  Added function return value in debug message.
// 2014-12-12  C. Baeuml   TC_004-4132 case NN_SRC_FRONTCONNECTOR
//                         removed.
// 2015-01-20  C. Baeuml   Usage of IBC_NODE_ID_DEFAULT.
// 2015-02-13  A. Benko    boBCLHwCanMode() implemented.
// 2015-03-15  C. Baeuml   TC_004-4705 LAD 32 bit:
//                         add IBI to serial output on startup.
// 31.03.2015  A. Sem      rename to s16IbcInvData_GetIbcBoardId
// 2016-05-10  S. Patapati Adapted gen55xx w.r.t ESRA Rel 2.21.7
//                         (s16BCL_HAL_ONN_GetSrcFrontCodingDevice added)
// 2017-06-02  V.Ingulkar  Adapted for BCM_FWR
// 2017-06-23  V.Ingulkar  Removed unwanted code after addition of
//                         BCM_HAL_ID component
// 2017-08-22  V.Ingulkar  BC0025-15- Updated to adapt kb_types.h changes
// 2017-10-06  S.Kumbhar   Disabled CAN interrupt after DRC
// 2018-01-17  F.Heindl    Added s16FwkCtrlDvrFwr_Operation and
//                          s16FwkCtrlDvrFwr_Init,
//                          fixed debug output of runtime and node
// 2018-07-10  V.Ingulkar  BC0025-53: Cleanup
// 2019-10-18  F. Heindl   Commented: s16BCL_GNN_GetNN_IBC_Startup()
// 2019-12-30  R. Dongre   Removed esra_def.h includes
// 2020-01-30  A. Mauro    Lint clean ups
// 2022-01-10  A. Mauro    TC_004-13671: temporary change because s16BCL_HAL_FC_Get()
//                                       does not return BCL_HAL_INTEGRITY_ERR.
//                                       Delete s16BCL_HAL_ONN_GetSrcFrontConnector() and use 
//                                       s16BCL_HAL_ONN_GetSrcFrontConnector_old removing "_old"
//                                       from function name when s16BCL_HAL_FC_Get() is fixed
// 2023-01-09  J. Lulli    Coding guidelines alignment
// 2023-04-18  A.Gatare    BT0003-2:Removed s16BCL_HAL_ONN_GetSrcFrontConnector_old as bcl_hal_fc.c updated for
//                         return parameter.
// 2023-10-25  C.Brancolini Lint Plus cleanup
//
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "std_defs.h"                   // Standard definitions
#include "bcl_hal_i.h"                  // BCL_HAL internal interface
#include "bcl_hal_s.h"                  // BCL_HAL system interface
#include "bcl_mcal_s.h"                 // BCL_MCAL system interface
#include "bcm_hal_tim.h"                // BCM_HAL_TIM system interface

#include "DeviceTime.h"
#include "NwmDrc.h"
#include "bcl_hal_onn.h"
#include "IbcSysDefs.h"                 // IBC_Device_ID_MAX
#include "IbcInvData.h"                 // IBI
#include "bcm_hal.h"

//**************************************** Constant / macro definitions ( #define ) ************************************
#define BCL_HAL_ONN_SC_RDMAX        ((U8)   3)
#define BCL_HAL_ONN_FC_RDMAX        ((U8)   3)
#define BCL_HAL_ONN_DELAY_2NDLOOK   ((U32)  5) // micro seconds

#define IBC_DEVICE_ID_MASK      ( (U16) 0x000F )// IBC DeviceID mask (4 bits)
#define IBC_DUALCAN_MASK        ( (U16) 0x0010 )// IBC Dual CAN enabled mask (1 bit)

// Macro for waiting at least x micro seconds
#define BCL_HAL_ONN_WAITUS(x)                                               \
               {                                                            \
               U32 u32TsUS;                                                 \
               u32TsUS = u32BCM_HAL_TimGetDeltaUS (0UL);                    \
               while ( u32BCM_HAL_TimGetDeltaUS(u32TsUS) < (x) ) {;}        \
               }


//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************

//**************************************** Module global data segment ( static ) ***************************************

static S16 s16BCL_HAL_ONN_ReadFrontConnectorCode(BOOLEAN* pboPinCodeAvailable, U8* pu8NodeNo);

//**************************************** Module global constants ( static const ) ************************************
//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *******************************************************************************************************


//**********************************************************************************************************************
// Function s16BCL_HAL_ONN_GetSrcFrontConnector
//**********************************************************************************************************************
S16 s16BCL_HAL_ONN_GetSrcFrontConnector(U8 u8MaxNodeNo, U8* pu8NodeNo)
{
//************************************************ Function scope data *************************************************
    S16 s16PartialResult;
    S16 s16Ret;
    U8 u8NodeNo;
    BOOLEAN boPinCodeAvailable = FALSE;

//*************************************************** Function code ****************************************************
    // Parameter check
    // Adaptation for IBC Device ID
    if (u8MaxNodeNo > IBC_DEVICE_ID_MAX)
    {
        s16Ret = BCL_HAL_ONN_ERR_PARAM;
    }
    else
    {

        // Read front connector code
        s16PartialResult = s16BCL_HAL_ONN_ReadFrontConnectorCode(&boPinCodeAvailable, &u8NodeNo);

        // Check if front connector code is available
        if ((boPinCodeAvailable == (U8) TRUE) && (s16PartialResult == BCL_HAL_NO_ERR))
        {
            // Front connector successfully read.
            // No parity error.

            // Check if node number is within valid range
            if (u8NodeNo <= u8MaxNodeNo) // IBC: 0 is allowed!
            {
                // Node number valid
                *pu8NodeNo = u8NodeNo;
                s16Ret = BCL_HAL_ONN_OK;
            }
            else
            {
                // Node number not in valid range
                s16Ret = BCL_HAL_ONN_ERR_RANGE;
            }
        }
        else
        {
            // Front connector read error
            if ((boPinCodeAvailable == (U8) TRUE) && (s16PartialResult == BCL_HAL_INTEGRITY_ERR))
            {
                // Front connector successfully read.
                // Parity error.
                s16Ret = BCL_HAL_ONN_ERR_PARITY;
            }
            else
            {
                // Front connector not successfully read.
                s16Ret = BCL_HAL_ONN_ERR_HAL;
            }
        }
    }
    return (s16Ret); // Return result

}
//** EndOfFunction s16BCL_HAL_ONN_GetSrcFrontConnector *****************************************************************

// Function s16BCL_HAL_ONN_ReadFrontConnectorCode
//**********************************************************************************************************************
//! @brief          Reads front connector code
//!
//!
//! @param[in,out]      pboPinCodeAvailable            : pointer to  pin code available flag
//! @param[in,out]      pu8NodeNo                      : pointer to  node number
//!
//! @return         Return Code
//!                  - BCL_HAL_NO_ERR : Successful execution
//!                  - negative number : Error.
//!
//! @remarks        -
//**********************************************************************************************************************
static S16 s16BCL_HAL_ONN_ReadFrontConnectorCode (BOOLEAN* pboPinCodeAvailable, U8* pu8NodeNo)
{
//************************************************ Function scope data *************************************************
    U16 u16PinCode;               // variable for pin code, first read result
    U16 u16PinCode2nd = 0;        // variable for pin code, second read result
    U16 u16PinNo;                 // variable for pin number, first read result
    U16 u16PinNo2nd;              // variable for pin number, second read result
    U8 u8Cnt = 0;                 // local counter
    S16 s16Res = BCL_HAL_ONN_ERR_PARAM;   // function result

//*************************************************** Function code ****************************************************
    // Check for null pointer error
    if ((pboPinCodeAvailable == KB_NULL_PTR) || (pu8NodeNo == KB_NULL_PTR))
    {
        return s16Res;
    }

    // init code available at FALSE
    *pboPinCodeAvailable = FALSE;

    // Read front connector code (at max 3 times)
    do
    {
        // Read front connector code
        s16Res = s16BCL_HAL_FC_Get(&u16PinCode, &u16PinNo);
        if ((s16Res == BCL_HAL_NO_ERR) || (s16Res == BCL_HAL_INTEGRITY_ERR))
        {
            // Wait a little before 2nd look
            BCL_HAL_ONN_WAITUS(BCL_HAL_ONN_DELAY_2NDLOOK);

            // Read front connector code (2nd look)
            s16Res = s16BCL_HAL_FC_Get(&u16PinCode2nd, &u16PinNo2nd);
        }

        // Check read slotcodes
        if ((s16Res == BCL_HAL_NO_ERR) || (s16Res == BCL_HAL_INTEGRITY_ERR))
        {
            // Front connector code is available if both read pin codes are equal.
            *pboPinCodeAvailable = (u16PinCode == u16PinCode2nd) ? (U8) TRUE : (U8) FALSE;
        }

        // Increment loop counter
        u8Cnt++;
    } while (((s16Res == BCL_HAL_NO_ERR) || (s16Res == BCL_HAL_INTEGRITY_ERR)) && (*pboPinCodeAvailable == (U8) FALSE)
        && (u8Cnt < BCL_HAL_ONN_FC_RDMAX));

    *pu8NodeNo = (U8) (u16PinCode & IBC_DEVICE_ID_MASK);

    return (s16Res); // Return result
}
//** EndOfFunction s16BCL_HAL_ONN_ReadFrontConnectorCode  **************************************************************

//** EndOfFile bcl_hal_onn.c *******************************************************************************************
