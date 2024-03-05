//**********************************************************************************************************************
//
//                                              bcm_fwr_adp_bs.c
//
//**********************************************************************************************************************
//
//                                       Copyrights(c) by KNORR-BREMSE,
//
//                                       Rail Vehicle Systems, Munich
//
//! @project  IBC
//! @date     2023-10-25
//! @author   C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file bcm_fwr_adp_bs.c
//! @brief BCM_FWR - BCM_FWR_ADP Adapter Module - Board specific Implementation
//!
//! BCM_FWR_ADP is a adapter module of BCM_FWR. It implements interfaces to all BCM_FWR components access device
//! specific Software/Hardware resources
//!
//**********************************************************************************************************************
//
// History
// Date            Author              Changes
// 2018-07-10      V.Ingulkar          BC0025-53:bcm_fwr_adp_i.h implementation is divided into
//                                     platform specific (bcm_fwr_adp_ps.c) and board specific (bcm_fwr_adp_bs.c)
//                                     bcm_fwr_adp.c is obsolete
// 2019-05-06      V.Ingulkar          Updates done as per core asset update v6.0
// 2019-04-13      N.Joshi             BC0025-52: Added terminal channel processing
// 2020-01-30      A. Mauro            Lint clean ups
// 2020-04-17      V.Ingulkar          BC0025-270 : Changes because of inventory data related updates
// 2020-10-29      A. Mauro            Lint clean ups
// 2020-12-04      A.Gatare            Adapted for GenCA 6.11.BC0025-210 : Function renamed from boSWD_CMDInit to
//                                     boSWD_CmdInit.Include files name chanaged from bcm_fwr_comm_i.h to swd_comm_i.h
// 2021-05-12      S.Khadbade          BC0025-505 : File is updated for new interfaces s16BCM_FWR_AdpGenInvGetHwData
//                                     and s16BCM_FWR_AdpGenInvGetSwData.
// 2022-11-26  S. Shinde    Adapted for GenCA 7.05
// 2023-05-18      C. Brancolini       Lint clean up
// 2023-10-25      C. Brancolini       Lint Plus cleanup. Added s16BCL_FWR_CtrlCacheEnable, s16BCL_FWR_CtrlCstartup
//                                     and s16BCL_FWR_DSPIInit.
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "string.h"                   // String related interfaces
#include "bcm_fwr.h"
#include "bcm_fwr_i.h"
#include "bcm_hal.h"                  // BCM_HAL Internal interface
#include "cfg_55xxsiu.h"
#include "swd_cmd_handlr_i.h"         // swd cmd handler internal interface
#include "swd_comm_i.h"               // swd common internal interface
#include "swd.h"

// inhibit lint message caused by incomplete declaration of array. Issue related to GenMPC55xx.
//lint -save -e6028
#include "bcl_fwr_i.h"
//lint -restore

#include "bcl_hal_bdspec_i.h"
#include "55xdspi.h"

//**************************************** Constant / macro definitions ( #define ) ************************************

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************


//**************************************** Local func/proc prototypes ( static ) ***************************************


//** EndOfHeader *******************************************************************************************************
//**********************************************************************************************************************
// Function s16BCL_FWR_CtrlCacheEnable
//**********************************************************************************************************************
S16 s16BCL_FWR_CtrlCacheEnable(void)
{
//************************************************ Function scope data *************************************************
//*************************************************** Function code ****************************************************
    // call assembly function to enable the controller cache
    _fwr_cache_enable();
    // return always "no error"
    return KB_RET_OK;
}
//** EndOfFunction s16BCL_FWR_CtrlCacheEnable **************************************************************************


//**********************************************************************************************************************
// Function s16BCL_FWR_CtrlCstartup
//**********************************************************************************************************************
S16 s16BCL_FWR_CtrlCstartup(void)
{
//************************************************ Function scope data *************************************************
//*************************************************** Function code ****************************************************
    // call assembly function to setup C environment
    _bcl_fwr_cstartup();
    // return always "no error"
    return KB_RET_OK;
}
//** EndOfFunction s16BCL_FWR_CtrlCstartup *****************************************************************************

//**********************************************************************************************************************
// Function s16BCL_FWR_DSPIInit
//**********************************************************************************************************************

S16 s16BCL_FWR_DSPIInit(void)
{
//************************************************ Function scope data *************************************************
//*************************************************** Function code ****************************************************
    // Init Module to use DSPI devices
    // return 0 Ok, < 0 in case of error
    return (S16) s32DSPIInit();
}
//** EndOfFunction s16BCL_FWR_DSPIInit *****************************************************************************

//**********************************************************************************************************************
// Function vBCM_FWR_AdpLoopStartCmdProcessing
//**********************************************************************************************************************
void vBCM_FWR_AdpLoopStartCmdProcessing ( U8 u8BoardState, U8 u8NodeNumber )
{
//************************************************ Function scope data *************************************************

//*************************************** Function scope static data declaration ***************************************

//*************************************************** Function code ****************************************************
    (void)boSWD_CommInit();                 // Initialise communication channel interface
    (void)boSWD_CmdInit (u8BoardState, u8NodeNumber);
                                                // Initialise terminal channel interface
    vBCM_FWR_UartPrint("SWD CMD: Processing started . . . \n");
}
//** EndOfFunction vBCM_FWR_AdpLoopStartCmdProcessing ******************************************************************

//**********************************************************************************************************************
// Function vBCM_FWR_AdpLoopStopCmdProcessing
//**********************************************************************************************************************
void vBCM_FWR_AdpLoopStopCmdProcessing ( void )
{
//************************************************ Function scope data *************************************************

//*************************************** Function scope static data declaration ***************************************

//*************************************************** Function code ****************************************************
    (void)boSWD_CommDeInit();               // De-initialise communication channel interface
}
//** EndOfFunction vBCM_FWR_AdpLoopStopCmdProcessing *******************************************************************

//**********************************************************************************************************************
// Function vBCM_FWR_AdpLoopCmdProcess
//**********************************************************************************************************************
void vBCM_FWR_AdpLoopCmdProcess ( void )
{
//************************************************ Function scope data *************************************************
    BOOLEAN boTemp;            // Temporary data store
    U16 u16Temp;               // Temporary data store
//*************************************** Function scope static data declaration ***************************************

//*************************************************** Function code ****************************************************
    (void)pu8SWD_CommReadDataPkt(&u16Temp, &boTemp);
                                                // Process any data received on TCH channel.

    vSWD_CommResetTimer(u32SWD_COMMTimeout);
                                                // Reset timeout
}
//** EndOfFunction vBCM_FWR_AdpLoopCmdProcess **************************************************************************

//**********************************************************************************************************************
// Function s16BCM_FWR_AdpInvGetPartNumStr
//**********************************************************************************************************************
S16 s16BCM_FWR_AdpInvGetPartNumStr (U8*  pu8DataOut, U16  u16MaxRespLen, U16* pu16RspLen, U8 u8HwModule)
{
//************************************************ Function scope data *************************************************
    S16     s16Return = KB_RET_ERR_DRIVER;                  // Function return variable
    S16     s16Response;                                    // Response of called function
    C_BCM_COMMON_HWINF_STN    cStnNr =  {{0}};              // Structure to get STN string


//*************************************** Function scope static data declaration ***************************************

//*************************************************** Function code ****************************************************
    (void) u16MaxRespLen; // unused parameter

    // Check for which hardware module, part number should be retrieved
    switch(u8HwModule)
    {
        // CPU module
        case BCM_COMMON_HW_MODULE_CPU:
        {
            // Get the CPU STN string
            s16Response = s16BCM_FWR_HwInfGetCpuStnStr(&cStnNr);
            break;
        }
        // Board / Device module
        case BCM_COMMON_HW_MODULE_DEV:
        {
            // Get the Device STN string
            s16Response = s16BCM_FWR_HwInfGetDevStnStr(&cStnNr);
            break;
        }

        default:
        {
            // Unexpected module, return error
            s16Return = KB_RET_ERR_ARG;
            s16Response = KB_RET_ERR_ARG;
            break;
        }
    }

    // Check if data retrieved successfully
    if( s16Response == KB_RET_OK )
    {
        // Return STN via pu8DataOut parameter
        memcpy( (void*)pu8DataOut, (void*)cStnNr.au8STN, BCM_COMMON_INVDATA_HW_STN_SIZE);
        // Return response length via pu16RspLen parameter
        *pu16RspLen = BCM_COMMON_INVDATA_HW_STN_SIZE;
        // Return success
        s16Return = KB_RET_OK;
    }

    return ( s16Return );
}
//** EndOfFunction s16BCM_FWR_AdpInvGetPartNumStr **********************************************************************


//**********************************************************************************************************************
// Function s16BCM_FWR_AdpInvGetAddData
//**********************************************************************************************************************
S16 s16BCM_FWR_AdpInvGetAddData (U8*  pu8DataOut, U16  u16MaxRespLen, U16* pu16RspLen)
{
//************************************************ Function scope data *************************************************

//*************************************************** Function code ****************************************************
    // No need to implement for inventory version format - 0x05
    (void)pu8DataOut;       // unused parameter
    (void)u16MaxRespLen;    // unused parameter
    (void)pu16RspLen;       // unused parameter
    return ( KB_RET_ERR_INTERNAL );  // Return internal error
}
//** EndOfFunction s16BCM_FWR_AdpInvGetAddData *************************************************************************


//**********************************************************************************************************************
// Function s16BCM_FWR_AdpInvGetFullData
//**********************************************************************************************************************
S16 s16BCM_FWR_AdpInvGetFullData (U8*  pu8DataOut, U16  u16MaxRespLen, U16* pu16RspLen)
{
//************************************************ Function scope data *************************************************

//*************************************************** Function code ****************************************************
    // No need to implement
    (void)pu8DataOut;       // unused parameter
    (void)u16MaxRespLen;    // unused parameter
    (void)pu16RspLen;       // unused parameter
    return ( KB_RET_ERR_INTERNAL );  // Return internal error
}
//** EndOfFunction s16BCM_FWR_AdpInvGetFullData ************************************************************************

//**********************************************************************************************************************
// Function s16BCM_FWR_AdpInvGenGetSwData
//**********************************************************************************************************************
S16 s16BCM_FWR_AdpInvGenGetSwData(C_BCM_FWR_INV_GEN_SW_COMP* const pcSw_Comp, U8 u8Page_num, U8 u8Sw_module_count)
{
//************************************************ Function scope data *************************************************

//*************************************************** Function code ****************************************************
 // No need to implement
    (void)pcSw_Comp;           // unused parameter
    (void)u8Page_num;          // unused parameter
    (void)u8Sw_module_count;   // unused parameter
    return ( KB_RET_ERR_INTERNAL );  // Return internal error


}

//** EndOfFunction s16BCM_FWR_AdpInvGenGetSwData ************************************************************************

//**********************************************************************************************************************
// Function s16BCM_FWR_AdpInvGenGetHwData
//**********************************************************************************************************************
S16 s16BCM_FWR_AdpInvGenGetHwData(C_BCM_FWR_INV_GEN_HW_COMP* const pcHw_Comp, U8 u8Page_num, U8 u8Hw_module_count)
{
//************************************************ Function scope data *************************************************

//*************************************************** Function code ****************************************************
    // No need to implement
    (void)pcHw_Comp;            // unused parameter
    (void)u8Page_num;           // unused parameter
    (void)u8Hw_module_count;    // unused parameter
    return ( KB_RET_ERR_INTERNAL );  // Return internal error

}
//** EndOfFunction s16BCM_FWR_AdpInvGenGetHwData ************************************************************************

//**********************************************************************************************************************
// Function s16BCM_FWR_AdpInvGenGetGS1Data
//**********************************************************************************************************************
S16 s16BCM_FWR_AdpInvGenGetGS1Data(C_BCM_FWR_INV_GEN_GS1_COMP* const pcGs1Comp,
                                    U8                               u8PageNum,
                                    U8                               u8Gs1ModuleCount)
{
//************************************************ Function scope data *************************************************

//*************************************************** Function code ****************************************************
 (void)pcGs1Comp;        // not used
 (void)u8PageNum;        // not used, remove warning Info 715
 (void)u8Gs1ModuleCount; // not used, remove warning Info 715
 return ( KB_RET_OK );
}
//** EndOfFunction s16BCM_FWR_AdpInvGenGetGS1Data ************************************************************************

//**********************************************************************************************************************
// Function s16BCM_FWR_AdpInvGenGetCustomData
//**********************************************************************************************************************
S16 s16BCM_FWR_AdpInvGenGetCustomData(C_BCM_FWR_INV_GEN_CUST_COMP* const pcCustComp,
                                      U8                                 u8PageNum,
                                      U8                                 u8CustModuleCount)
{
//************************************************ Function scope data *************************************************

//*************************************** Function scope static data declaration ***************************************

//*************************************************** Function code ****************************************************
 (void)pcCustComp;        // not used
 (void)u8PageNum;         // not used, remove warning Info 715
 (void)u8CustModuleCount; // not used, remove warning Info 715
 return ( KB_RET_OK );
}
//** EndOfFunction s16BCM_FWR_AdpInvGenGetCustomData ************************************************************************


//** EndOfFile bcm_fwr_adp_bs.c ****************************************************************************************
