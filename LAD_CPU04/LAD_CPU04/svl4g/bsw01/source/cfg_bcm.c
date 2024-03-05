//**********************************************************************************************************************
//
//                                              cfg_bcm.c
//
//**********************************************************************************************************************
//
//                                       Copyrights(c) by KNORR-BREMSE,
//
//                                       Rail Vehicle Systems, Munich
//
//! @project   IBC
//! @date      2023-12-01
//! @author    C. Brancolini
//
//**********************************************************************************************************************
//!
//! @file cfg_bcm.c
//! @brief BCM - Configuration
//!
//! CFG_BCM Component provides configuration constants of service BCM.
//!
//**********************************************************************************************************************
//
// History
// Date            Author               Changes
// 2016-11-07      V. Ingulkar          Start
// 2016-01-04      V. Ingulkar          Reworked on BCM_BONO to avoid uses of
//                                      #pragma
// 2017-02-10      R. Palsule           Renamed ioss_eb.h to ioss.h and
//                                      s32IOSInit to s16IOS_Init
// 2017-04-07      R. Dongre            JIRA BC0025-1
//                                      Rework on common startup handler
// 2017-04-13      G. Badve             Added s32IOC_CTRL_init and
//                                      s32IOC_CTRL_startup
// 2017-06-02      V. Ingulkar          Adapted for BCM_FWR
// 2017-06-22      R. Palsule           Added s16FIM_Init call and fim.h in
//                                      Include files
// 2017-06-16      V. Ingulkar          bcm startup handler update
// 2017-09-08      R. Palsule           Added s32IOS_Startup in startup function2
//                                      changed parameter of boBCM_AppConfigurationPhase
// 2017-11-14      K. Gade              Added 's16SDI_Init', 's16SDI_StoreInventoryData'in 'NormalInitFunction' table
// 2017-11-28      K. Gade              Renamed to 's16SDI_BCM_StoreInventoryData' in 'NormalInitFunction' table
// 2018-01-10      S. Kumbhar           Service OS updated as per Coding guidelines
// 2018-02-09      V.Ingulkar           Updates done to comply code with new coding guidelines and static code analysis
// 2018-02-23      K. Gade              Updated 'NormalInitFunction' for function name.
// 2018-04-17      V.Ingulkar           Removed unwanted configuration after implementation bcm_cmd
// 2018-06-08      V.Ingulkar          BC0025-35, BC0025-36:Only one user for poff areas, either APP or APP plus FWK
//                                     CDO based configuration is introduced
// 2018-06-25      K. Gade             Added NVM related POFF area for POFF
// 2018-06-26      R. Palsule          Removed s32IOC_CTRL_Init and related header files
// 2018-09-18      K. Gade             BC0025-59: NVM initialization reordered in 'aps32BCM_CFG_NrmlInitFct'
// 2018-10-04      V.Ingulkar          Changes done for BC0025-63
// 2018-11-26      V.Ingulkar          BC0025-67: Configuration variable added for change device id accept
// 2019-03-19      A. Mauro            Adaptation for LAD01
// 2019-05-06      V.Ingulkar          Updates done as per core asset update v6.0
// 2019-05-08      S. Kumbhar          os_cca_s.h is changed to os_ca_s.h
// 2019-05-09      R. Dongre           DsmLadBswDsa.h changed to DiagDsaBswLad.h
// 2019-07-29      A. Mauro            BC0025-194: added s16FIM_AlInit()
// 2019-10-11      K. Gade             BC0025-143: Added SDI initialization as a part of BCM startup phase 2,
//                                     to be compatible with slim-firmware.
// 2019-11-18      S. Ambre        	   Updated array aps32BCM_CFG_NrmlInitFct[]. Added entry of Init function
//                                     s16FwkCtrlLad_NwmBasicInit ().
//                                     Added entry of DiagDfm startup function s16DiagDfm_Startup () in array
//                                     aps32BCM_CFG_NrmlStartup2Fct[].
// 2020-02-05      A. Mauro            Lint clean ups
// 2020-04-17      V.Ingulkar          BC0025-270 : Changes because of inventory data related updates
// 2020-11-24      A.Gatare            Adapted for GenCA 6.11.
// 2021-06-07      A. Mauro            Added s16SDI_Startup to aps16BCM_CFG_NrmlInitFct
// 2021-07-06      A. Mauro            Removed s16SDI_Startup from aps16BCM_CFG_NrmlInitFct (it cannot be called two times)
// 2021-04-30      N. Jadhav           BC0025-507 : New interface s16SDI_Restart() added. SDI Channel Restart mechanism
//                                                  added.
// 2021-04-09      S.Khadbade          BC0025-505 : For Board specific Prolog/Epilog functions structure array
//                                     aps16BCM_InvGenGetDataPrEpFct is added.
// 2021-05-21      A.Gatare            BC0025-513 Updated to validate temperature range for all configured temperature
//                                     sensors.
// 2022-03-25      A. Mauro            Set u16BCM_CFG_TestRefreshCounter to 5s (was 3s)
// 2022-11-26      S. Shinde           Adapted for GenCA 7.05
// 2023-01-09      J. Lulli            Coding guidelines alignment
// 2023-01-18      J. Lulli            TC_004-14143: moved s16FIM_AdpInit from aps16BCM_CFG_NrmlInitFct
//                                     to aps16BCM_CFG_NrmlStartup2Fct
// 2023-05-16      C. Brancolini       Lint clean up
// 2023-09-28      A. Mauro            Added s16MON_BoardStateTestPRO
// 2023-12-01      C. Brancolini       Lint Plus clean up
//
//**********************************************************************************************************************
//Note: Suppression of "No magic numbers", all magic numbers come with comments so there's necessity to add definitions
//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "bcm_i.h"                            // BCM Internal interface
#include "bcm_s.h"                            // BCM System interface
#include "bcm_hal.h"
#include "ios_s.h"
#include "bcm_fwr.h"
#include "bcm_inv.h"
#include "os_s.h"
#include "os_ca_s.h"
#include "nvm_common.h"
#include "nvm_hal.h"
#include "bcl_i.h"
#include "bcl_s.h"
#include "bcl_fwr_s.h"
#include "bcl_hal_uart_s.h"
#include "mon_s.h"
#include "os_app.h"
#include "bcm_bs.h"
#include "55xxirq.h"
#include "can_s.h"                      // System interface of CAN
#include "ios_s.h"
// Inhibit lint errors related to FWK header file DiagDsmTypes.h
// included by DiagDsaBswLad.h
//lint -save -e5469
#include "DiagDsaBswLad.h"
//lint -restore
#include "FwkCtrlLad.h"
#include "bt.h"
#include "DiagDfm.h"
#include "MaMoAl.h"
#include "ibcsysdefs.h"
#include "RtcAlNvMem.h"
#include "DiagDsmAlNvMem.h"
#include "FwkAlMamoNvMem.h"
#include "FwkAlRtcNvMem.h"
#include "FwkAlDsmNvMem.h"
#include "FwkAlDFMNvMem.h"
#include "fim_s.h"
#include "fim_adp_s.h"
#include "sdi_s.h"                  // Interface for SDI
#include "sdi_adp_i.h"
#include "nvm_s.h"
#include "nvm_i.h"
#include "mon_cpu04_genrl_sdi_i.h"                          //!< CPU04 general MON commands

//**************************************** Constant / macro definitions ( #define ) ************************************

// Macros used for Node Numbers
#define BCM_NODE_NO_0           ((U8) 0)
#define BCM_NODE_NO_1           ((U8) 1)
#define BCM_NODE_NO_29          ((U8) 29)
#define BCM_NODE_NO_30          ((U8) 30)
#define BCM_NODE_NO_DEFAULT     ((U8) 30)

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************

//**********************************************************************************************************************
//
//! @name            BCM_ONN configuration
//
//**********************************************************************************************************************
//@{

//----------------------------------------------------------------------------------------------------------------------
// boBCM_CFG_OnnAcceptNodeNoChange
//
// - TRUE: A change of the node number during runtime is allowed. A change of the node number will trigger a reboot of
//         the board, causing the switch from the current value of own node number to the new node number.
//
// - FALSE: A change of the node number during runtime is not allowed. If the node number read from the source differs
//          from the node number currently used by the board, Board Coding related error is triggered.
//
// Note : This variable is valid only when node number is determined by source such as Front Connector - where it
//        is possible to change node number during runtime. For other sources such as DRC, Fix, default this variable
//        is not valid. And shall always be initialized with FALSE.
//        This variable is used only in vBCM_Cycl100ms_OnnCheck(), if this function is not configured as part of
//        apvBCM_CFG_CyclFct[], this variable will be ignored
//----------------------------------------------------------------------------------------------------------------------
const BOOLEAN boBCM_CFG_OnnAcceptNodeNoChange = FALSE;


// Inhibit lint message 552 (external variable not accessed).
// au8BCM_CFG_OnnAllowedNodeNumbers defined in this file and used to get its size,
// its fields are accessed in GenMPC55xx module.
//lint -save -e552


//----------------------------------------------------------------------------------------------------------------------
// List of allowed node number for particular board
//----------------------------------------------------------------------------------------------------------------------
const U8 au8BCM_CFG_OnnAllowedNodeNumbers[] =
{
//     0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, // @suppress("No magic numbers")
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, // @suppress("No magic numbers")
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, // @suppress("No magic numbers")
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63 // @suppress("No magic numbers")
};
//Note: Suppression of "No magic numbers", adding define statement would not be helpful

//----------------------------------------------------------------------------------------------------------------------
// Number of node numbers configured in List
//----------------------------------------------------------------------------------------------------------------------
const U8 u8BCM_CFG_OnnAllowedNodeNumberCnt = (U8)(sizeof(au8BCM_CFG_OnnAllowedNodeNumbers)/sizeof(U8));

//lint -restore

//----------------------------------------------------------------------------------------------------------------------
// Node Number - Default
//----------------------------------------------------------------------------------------------------------------------
const U8 u8BCM_CFG_OnnDefaultNodeNo = (U8)IBC_NODE_ID_EXCEPTION_DEFAULT;

//----------------------------------------------------------------------------------------------------------------------
// Node number source
//----------------------------------------------------------------------------------------------------------------------
const U8 u8BCM_CFG_OnnSource = BCM_COMMON_SOURCE_DRC;


//@}
//** End of BCM_ONN configuration **************************************************************************************


//**********************************************************************************************************************
//
//! @name            BCM_ID configuration
//
//**********************************************************************************************************************
//@{

//----------------------------------------------------------------------------------------------------------------------
// boBCM_CFG_IdAcceptDeviceIdChange
//
// - TRUE: A change of the device Id during runtime is allowed. A change of the device Id will trigger a reboot of
//         the board, causing the switch from the current value of device Id to the new device Id.
//
// - FALSE: A change of the device Id during runtime is not allowed. If the device Id read from the source differs
//          from the device Id currently used by the board, Board Coding related error is triggered.

// Note : This variable is valid only when device Id is determined by source such as Front Connector - where it
//        is possible to change device Id during runtime.
//        This variable is used only in vBCM_Cycl100ms_IdCheck(), if this function is not configured as part of
//        apvBCM_CFG_CyclFct[], this variable will be ignored
//----------------------------------------------------------------------------------------------------------------------
const BOOLEAN boBCM_CFG_IdAcceptDeviceIdChange = FALSE;

//@}
//** End of BCM_ONN configuration **************************************************************************************

//**********************************************************************************************************************
//
//! @name            BCM_COMO configuration
//
//**********************************************************************************************************************
//@{

//! NVM Device Id used to store the Condition Monitoring related data
const U8 u8BCM_CFG_ComoNvmDevId = NVM_DEVICE_ID0;

//@}
//** End of BCM_COMO configuration *************************************************************************************


//**********************************************************************************************************************
//
//! @name            BCM_WD configuration
//
//**********************************************************************************************************************
//@{

//----------------------------------------------------------------------------------------------------------------------
// Watchdog trigger timeslice
//
// Cyclic Watchdog trigger function - vBCM_Cycl_WdTrigger will be activated for this timeslice
//
// Make sure that vBCM_Cycl_WdTrigger function is available in respective timeslice array in cfg_os.c
// Total trigger window is as per u8BCM_CFG_WdTrigDelay
//----------------------------------------------------------------------------------------------------------------------
const E_OS_SLICES eBCM_CFG_WdTriggerTimeslice = eOS_SLICE_100MS;


//----------------------------------------------------------------------------------------------------------------------
// Watchdog trigger delay.
//
// Number of additional (eBCM_CFG_WdTriggerTimeslice) time slice intervals to be passed before watchdog gets triggered.
//
// Total trigger interval will be (1 + u8BCM_CFG_WdTrigDelay) * eBCM_CFG_WdTriggerTimeslice
//----------------------------------------------------------------------------------------------------------------------
const U8 u8BCM_CFG_WdTrigDelay     = 4; // @suppress("No magic numbers")

//@}
//** End of BCM_WD configuration ***************************************************************************************


//**********************************************************************************************************************
//
//! @name            BCM_PWR configuration
//
//**********************************************************************************************************************
//@{

//----------------------------------------------------------------------------------------------------------------------
// Indicates whether powerline exists for this board.
//----------------------------------------------------------------------------------------------------------------------
const BOOLEAN boBCM_CFG_PwrLineExists = FALSE;

//----------------------------------------------------------------------------------------------------------------------
// Indicates whether power line should be handled during Initialization or not
//
// Normally on ESRA/ESRA_Evo system power line is handled during startup for standby mode
// If handling of the power line during startup is not required, then this should be FALSE
// "TRUE" value for this is only valid when "boBCM_CFG_PwrLineExists" is TRUE
//----------------------------------------------------------------------------------------------------------------------
const BOOLEAN boBCM_CFG_PwrLineInitHandle = FALSE;

//----------------------------------------------------------------------------------------------------------------------
// Delay for switching power line off after startup of the board.
//
// Delay is given in seconds (max. value: 0x1999)
// An application may override switching off.
//----------------------------------------------------------------------------------------------------------------------
const U16 u16BCM_CFG_PwrLineInitDelay = 30; // @suppress("No magic numbers")

//----------------------------------------------------------------------------------------------------------------------
// Time slice for checking power supply FAIL signal.
//
// This defines how fast a power supply FAIL signal can be detected.
//----------------------------------------------------------------------------------------------------------------------
const E_OS_SLICES eBCM_CFG_PwrCheckFailTimeslice = eOS_SLICE_5MS;

//----------------------------------------------------------------------------------------------------------------------
// Interval for checking power supply FAIL signal ON in time slice ticks.
//
// If set to 0, power supply FAIL signal check is disabled.
// If set to n != 0, power supply FAIL signal ON check will be done in every
// n'th cylce of the selected time slice.
//----------------------------------------------------------------------------------------------------------------------
const U16 u16BCM_CFG_PwrFailCheckOnInterval = 1; // @suppress("No magic numbers")

//----------------------------------------------------------------------------------------------------------------------
// Threshold for power supply FAIL signal ON verification.
//
// Defines the number time slice ticks (#eBCM_CFG_PwrCheckFailTimeslice)
// where a stable power fail ON condition gets recognized.
//
// Once power fail ON has been recognized, a threshold counter gets
// incremented (decremented) each time FAIL signal ON (OFF) is detected
// during a time slice tick.
//
// If the counter reaches the configured threshold, the FAIL signal ON
// is considered to be stable and power fail handling gets started.
//
// If the counter reaches 0 while the configured threshold is > 0, then FAIL
// signal ON detection starts from the beginning again.
//
// -> The minimum power fail ON recognition time in ms is:
//    (CheckFailOnThreshold + CheckFailOnInterval) * time slice
//----------------------------------------------------------------------------------------------------------------------
const U16 u16BCM_CFG_PwrFailCheckOnThreshold = 1; // @suppress("No magic numbers")

//----------------------------------------------------------------------------------------------------------------------
// Threshold for power supply FAIL signal OFF verification.
//
// Defines the number time slice ticks (#eBCM_CFG_PwrCheckFailTimeslice)
// where a stable power fail OFF condition gets recognized.
//
// Once power fail handling has been started, a threshold counter gets
// incremented (decremented) each time FAIL signal OFF (ON) is detected
// during a time slice tick.
//
// If the counter reaches the configured threshold, FAIL signal OFF
// is considered to be stable and power fail handling gets finished.
//
// -> The minimal power fail OFF recognition time in ms is:
//    CheckFailOffThreshold * time slice
//----------------------------------------------------------------------------------------------------------------------
const U16 u16BCM_CFG_PwrFailCheckOffThreshold = 2; // @suppress("No magic numbers")

//----------------------------------------------------------------------------------------------------------------------
// Power fail handling finish delay.
//
// Defines the number time slice ticks (#eBCM_CFG_PwrCheckFailTimeslice)
// power fail handling has to continue after a stable FAIL signal OFF has
// been recognized.
//
// Reason for this:
// In case of power fail a board may live longer than the power supply is
// able to hold the FAIL signal. The delay shall be large enough to ensure
// the board is dead after the delay in case of a real power fail.
//----------------------------------------------------------------------------------------------------------------------
const U16 u16BCM_CFG_PwrFailCheckFinishDelay = 200; // @suppress("No magic numbers")

//----------------------------------------------------------------------------------------------------------------------
// Pointer to standard POFF save function
//
// Use s16BCM_HAL_PoffSaveData, if u16BCM_CFG_PwrFailCheckOnInterval
// is set != 0
// Use NULL otherwise.
//----------------------------------------------------------------------------------------------------------------------
const T_BCM_PWR_S16FP_SAVEDATA pfs16BCM_CFG_PwrSaveDataFct = s16NVM_HAL_PoffSaveData;

//@}
//** End of BCM_PWR configuration **************************************************************************************

//**********************************************************************************************************************
//
//! @name            BCM_TEMP configuration
//
//**********************************************************************************************************************
//@{

//----------------------------------------------------------------------------------------------------------------------
// Temperature check interval in 100ms ticks
//
// Current valid temperature value will be checked against configured ranges and FIM error will be set if temperature
// is out of range
//----------------------------------------------------------------------------------------------------------------------
const U32 u32BCM_CFG_TempCheckInverval       = (U32)600; // Check temperature range for every minute // @suppress("No magic numbers")

//----------------------------------------------------------------------------------------------------------------------
// Temperature update interval in 100ms ticks
//
// This variable configures cyclicity for calling of function - vBCM_HAL_Cycl_Temp
// vBCM_HAL_Cycl_Temp function invokes board specific function to get temperature value
//----------------------------------------------------------------------------------------------------------------------
const U32 u32BCM_CFG_TempUpdateInverval       = (U32)5; // Update temperature for every 500 msec // @suppress("No magic numbers")

//----------------------------------------------------------------------------------------------------------------------
// Minimum value of valid temperature range for each temperature sensor (degree celsius)
// FIM error will be set and board specific function will be called if configured, if temperature goes below this limit
// Checking is done as per temperature Check interval - u32BCM_CFG_TempCheckInverval
// At present only 2 temperature sensors are configured hence temeprature is present for 2.
//----------------------------------------------------------------------------------------------------------------------

const S8 as8BCM_CFG_TempAllowedMin[BCM_COMMON_TEMP_MAX_CNT] =
{
  -40, //Minimum value for Temperature sensor 1 // @suppress("No magic numbers")
  -40, //Minimum value for temperature sensor 2 // @suppress("No magic numbers")
   0, //Minimum value for Temperature sensor 3
   0, //Minimum value for temperature sensor 4
   0, //Minimum value for Temperature sensor 5
   0, //Minimum value for temperature sensor 6
   0, //Minimum value for Temperature sensor 7
   0 //Minimum value for temperature sensor 8
};

//----------------------------------------------------------------------------------------------------------------------
// Maximum value of valid temperature range for each temperature sensor (degree celsius)
// FIM error will be set and board specific function will be called if configured, if temperature goes above this limit
// Checking is done as per temperature Check interval - u32BCM_CFG_TempCheckInverval.
// At present only 2 temperature sensors are configured hence temeprature is present for 2.
//----------------------------------------------------------------------------------------------------------------------
const S8 as8BCM_CFG_TempAllowedMax[BCM_COMMON_TEMP_MAX_CNT] =
{
   100, //Maximum value for Temperature sensor 1 // @suppress("No magic numbers")
   100, //Maximum value for temperature sensor 2 // @suppress("No magic numbers")
   0, //Maximum value for Temperature sensor 3
   0, //Maximum value for temperature sensor 4
   0, //Maximum value for Temperature sensor 5
   0, //Maximum value for temperature sensor 6
   0, //Maximum value for Temperature sensor 7
   0 //Maximum value for temperature sensor 8
};

//----------------------------------------------------------------------------------------------------------------------
// Pointer to out of range Temperature handler function
//
// While monitoring temperature, if out of range temperature is detected, this function will be called if configured
// Checking is done as per temperature Check interval - u32BCM_CFG_TempCheckInverval
//----------------------------------------------------------------------------------------------------------------------
const T_BCM_TEMP_VFP_TEMPHNDL pfvBCM_CFG_TempHndlFct = NULL;

//@}
//** End of BCM_TEMP configuration *************************************************************************************

//**********************************************************************************************************************
//
//! @name            BCM_TEST configuration
//
//**********************************************************************************************************************
//@{

//----------------------------------------------------------------------------------------------------------------------
// Refresh counter variable to switch board state "Normal" from board state "Test"
//
// Counter decrements in 100msec interval, so value 1 is equals 100 msec
// If test trigger is not received during this interval Board State Test is exited and board state "Normal" is entered
//----------------------------------------------------------------------------------------------------------------------
const U16 u16BCM_CFG_TestRefreshCounter       = (U16)50; // 5 Second interval // @suppress("No magic numbers")

//@}
//** End of BCM_TEST configuration *************************************************************************************


//**********************************************************************************************************************
//
//! @name            BCM_RSM configuration
//
//**********************************************************************************************************************
//@{

// SVL RSM ID of RSM memory used by SVL runtime (SVLRT)
#define BCM_RSM_SVL_RES_SVLRT           0U
#define BCM_RSM_SVL_RES_SVLRT_SIZE      BCM_RSM_SIZE(sizeof(U32))
#define BCM_RSM_SVL_RES_SVLRT_OFFS      0U

// SVL RSM ID of RSM memory used by Board State
#define BCM_RSM_SVL_RES_BDSTAT          1U
#define BCM_RSM_SVL_RES_BDSTAT_SIZE     BCM_RSM_SIZE(sizeof(C_BCM_RSM_BDSTAT))
#define BCM_RSM_SVL_RES_BDSTAT_OFFS     (BCM_RSM_SVL_RES_SVLRT_OFFS + BCM_RSM_SVL_RES_SVLRT_SIZE )

//Size of RSM used must not exceed size of RSM_SIZE_SVL_RESERVED
#define BCM_RSM_SVL_RES_USED            (BCM_RSM_SVL_RES_BDSTAT_OFFS + BCM_RSM_SVL_RES_BDSTAT_SIZE      )


// Inhibit lint message 552 (external variable not accessed).
// acBCM_CFG_RsmId defined in this file and used to get its size,
// its fields are accessed in GenMPC55xx module.
//lint -save -e552

// RSM Id configuration table
const C_BCM_RSM_ID acBCM_CFG_RsmId[] =
{
    { BCM_RSM_SVL_RES_SVLRT,
      BCM_RSM_SVL_RES_SVLRT_SIZE,
      BCM_RSM_SVL_RES_SVLRT_OFFS },     // RSM ID 0

    { BCM_RSM_SVL_RES_BDSTAT,
      BCM_RSM_SVL_RES_BDSTAT_SIZE,
      BCM_RSM_SVL_RES_BDSTAT_OFFS },    // RSM ID 1
};

// Used reset safe memory size
const U16 u16BCM_CFG_RsmSvlResUsed = BCM_RSM_SVL_RES_USED;

// Total number of configured RSM IDs
const U8 u8BCM_CFG_RsmIdCnt = (U8)(sizeof(acBCM_CFG_RsmId) / sizeof(C_BCM_RSM_ID));

//lint -restore

// RSM area to save board state
BCM_RSM_AREA_ID_BDSTAT_SET(BCM_RSM_SVL_RES_BDSTAT)

// RSM area to save SVL runtime
BCM_RSM_AREA_ID_SVLRT_SET(BCM_RSM_SVL_RES_SVLRT)


//@}
//** End of BCM_RSM configuration **************************************************************************************

//**********************************************************************************************************************
//
//! @name            BCM_STRT configuration
//
//**********************************************************************************************************************
//@{

// Inhibit lint message 552 (external variable not accessed).
// Message related to variables defined in this file and used to get their size,
// their fields are accessed in GenMPC55xx module.
//lint -save -e552

// All startup handler functions
const T_BCM_STRT_BOFP_HDLR apboBCM_CFG_StrtHandlerFct[] =
{
    // Normal startup handler
    boBCM_NrmlStartUpHandler,

    // Limited startup handler
    boBCM_LmtdStartUpHandler
};

// Total number of configured startup handler functions
const U16 u16BCM_CFG_StrtHandlerFctCnt = (U16) (sizeof(apboBCM_CFG_StrtHandlerFct) / sizeof(T_BCM_STRT_BOFP_HDLR));



// All startup PreInit functions
const T_BCM_S16FP aps16BCM_CFG_StrtPreInitFct[] =
{
     s16BCM_BS_IrqAtomicInterruptInit,
     s16BCL_HAL_UART_Open,
     s16BCM_PrintStartMsg,
     s16BCM_CompCheck,
     s16BCM_InitRsmData,
     s16BCM_RsmInit

};

// Total number of configured startup handler functions
const U16 u16BCM_CFG_StrtPreInitFctCnt = (U16) (sizeof(aps16BCM_CFG_StrtPreInitFct) / sizeof(T_BCM_S16FP));

//lint -restore

//@}
//** End of BCM_STRT configuration *************************************************************************************

//**********************************************************************************************************************
//
//! @name      Function tables containing call back functions used by FWR
//
//**********************************************************************************************************************
//@{

//----------------------------------------------------------------------------------------------------------------------
// Functions required by BCM_FWR
//----------------------------------------------------------------------------------------------------------------------
static const C_BCM_FCT_TAB_V1 cBCM_FctTab_V1 =
{
    _start,                             // SCIOPTA start function
    __sp_grow_s,                        // Stack overflow handler
    vOS_EnableTimeSlices,                 // OS scheduling enable function
    vOS_DisableTimeSlices                 // OS scheduling disable function
};

// CCA Function Table - Version 1
const C_FTAB cBCM_FctTab =
{
    FWR_FCT_VERSION_1,              // Function Table version 1
    (const void*) &cBCM_FctTab_V1   // Type of Version 1 function table
};

//@}
//** End of Function tables containing functions used by FWR ***********************************************************


//**********************************************************************************************************************
//
//! @name            BCM_NRML configuration
//
//**********************************************************************************************************************
//@{

// Initial startup state.
const E_BCM_STARTUP_STATE eBCM_CFG_NrmlInitStartupState = eBCM_STARTUP_WAITING;

// Inhibit lint message 552 (external variable not accessed).
// Message related to variables defined in this file and used to get their size,
// their fields are accessed in GenMPC55xx module.
//lint -save -e552

// All init functions for NORMAL board state
const T_BCM_S16FP aps16BCM_CFG_NrmlInitFct[] =
{
        s16FIM_Init,       // Initialize Service FIM
        s16CAN_Init,       // s16CAN_Init must be 2nd in list
        s16NVM_Init,       // NVM initialization
        s16MON_Init,
        s16SDI_Init,       // Service Data Interface
        s16FwkCtrlLad_MemInit,
        s16FwkCtrlLad_Init,
        s16FwkCtrlLad_ComBasicInit,
        s16FwkCtrlLad_CommonBasicInit,
        s16FwkCtrlLad_DvrInit,
        s16FwkCtrlLad_NwmBasicInit,
        s16FwkCtrlLad_SysCfgInit,
        // IBC FMN replacement, must be 1st in list
        s16FwkCtrlLad_DiagBasicInit,
        s16BSWDsa_Init,    // Register BSW DSA
        //Register FWK DSA, FWK DEA, Init SEH & GDSH
        s16FwkCtrlLad_DiagExtendedInit,
        //(T_BCM_S32FP)s16FMNInit,
        s16BCM_Init,// Initialize BCM
        s16BCL_Init,// Initialize BCL
        //***** Section 2 (init function of services are typically placed here)
        s16IOS_Init,
        s16BCL_HAL_VMT_Init,
        //***** Section 3 IBC Init
        s16FwkCtrlLad_MiscInit,
        s16FwkCtrlLad_NwmExtendedInit,
        s16FwkCtrlLad_ComExtendedInit, //COMPDH Init
        s16DiagDfm_Init,          // Initialize Diag DFM
        s16BT_Init,
        s16FwkCtrlLad_LadCfgInit,
//        s16SDI_Startup
};

// Total number of configured init functions for NORMAL board state
const U16 u16BCM_CFG_NrmlInitFctCnt = (U16) (sizeof(aps16BCM_CFG_NrmlInitFct) / sizeof(T_BCM_S16FP));


// All startup stage 1 functions for NORMAL board state
const T_BCM_S16FP aps16BCM_CFG_NrmlStartup1Fct[] =
    {
        s16BCM_Startup,
        s16SDI_Startup            //Start up SDI with old node ID.
    };

// Total number of configured startup stage 1 functions for NORMAL board state
const U16 u16BCM_CFG_NrmlStartup1FctCnt = (U16) (sizeof(aps16BCM_CFG_NrmlStartup1Fct) / sizeof(T_BCM_S16FP));

// All startup stage 2 functions for NORMAL board state
const T_BCM_S16FP aps16BCM_CFG_NrmlStartup2Fct[] =
    {
        s16ESRA_IDLEStartup,
        s16DiagDfm_Startup,
        s16SDI_Restart,
        s16IOS_Startup,
        s16IBC_Startup,
        s16MON_StartUp,
        s16FIM_AdpInit,
    };

// Total number of configured startup stage 2 functions for NORMAL board state
const U16 u16BCM_CFG_NrmlStartup2FctCnt = (U16) (sizeof(aps16BCM_CFG_NrmlStartup2Fct) / sizeof(T_BCM_S16FP));


//@}
//** End of BCM_NRM configuration **************************************************************************************


//**********************************************************************************************************************
//
//! @name            BCM_LMTD configuration
//
//**********************************************************************************************************************
//@{

// All init functions for LIMITED board state
const T_BCM_S16FP aps16BCM_CFG_LmtdInitFct[] =
{
     s16CAN_Init, // s16CAN_Init must be 2nd in list
     s16NVM_Init, // NVM initialization
     s16BCM_Init, // Initialize BCM
     s16FIM_Init, // Initialize Service FIM
     s16SDI_Init, // Service Data Interface
};

// Total number of configured init functions for LIMITED board state
const U16 u16BCM_CFG_LmtdInitFctCnt = (U16) (sizeof(aps16BCM_CFG_LmtdInitFct) / sizeof(T_BCM_S16FP));

// All startup functions for LIMITED board state
const T_BCM_S16FP aps16BCM_CFG_LmtdStartupFct[] =
{
    s16BCM_Startup,
    s16SDI_Startup,
};

// Total number of configured startup functions for LIMITED board state
const U16 u16BCM_CFG_LmtdStartupFctCnt = (U16) (sizeof(aps16BCM_CFG_LmtdStartupFct) / sizeof(T_BCM_S16FP));

//lint -restore

//! NVM Device Id used to store Limited board state errors
const U8 u8BCM_CFG_LmtdNvmDevId = NVM_DEVICE_ID0;
//@}
//** End of BCM_LMTD configuration *************************************************************************************

//**********************************************************************************************************************
//
//! @name            BCM_CYCL configuration
//
//**********************************************************************************************************************
//@{

// Inhibit lint message 552 (external variable not accessed).
// apvBCM_CFG_CyclFct is defined in this file and used to get its size,
// its fields are accessed in GenMPC55xx module.
//lint -save -e552

// All cyclic functions which are need to be run in 100msec timeslice
const T_BCM_CYCL_VFP apvBCM_CFG_CyclFct[] =
{
    // Power Line check function
    vBCM_Cycl100ms_PwrLineCheck,

    // Check Own Device Id function
    vBCM_Cycl100ms_IdCheck,

    // Check if One wire memory devices are connected
    vBCM_Cycl100ms_OwmDeviceCheck,

    // Update SVL Runtime function
    vBCM_Cycl100ms_ComoUpdSvlRuntime,

    // Normal startup request check function
    vBCM_Cycl100ms_NrmlStartupReqCheck,

    // Board State - Test : Check Timeout
    vBCM_Cycl100ms_TestTimeoutCheck,

     // Check connection status of one wire devices
        vBCM_Cycl100ms_OwmDeviceCheck,
    // Update and check temperature values
    vBCM_Cycl100ms_TempHndl

};

// Total number of configured cyclic functions
const U16 u16BCM_CFG_CyclFctCnt = (U16) (sizeof(apvBCM_CFG_CyclFct) / sizeof(T_BCM_CYCL_VFP));

//lint -restore

//@}
//** End of BCM_CYCL configuration *************************************************************************************


//**********************************************************************************************************************
//
//! @name            BCM P configuration
//
//**********************************************************************************************************************
//@{

// Below mentioned function pointers are used in 5 step startup process
// defined in bcm_p component
// startup process varies as per requirements so the values of pointers
// Below mentioned pointers can be initialized with "NULL" if particular
// step is not required for application startup or with Valid function if it
// is required

// Step 1
// Start application processes function pointer
// This function pointer is used to define function which starts Application
// Processes, if application processes are not required it can be initialized
// with NULL
const T_BCM_S16FP_APPSTARTPRCS ps16BCM_CFG_StartAppPrcs = NULL;

// Step 2
// Application configuration phase function pointer
// This function pointer is used to define function which does Application
// Configuration, if application Configuration is not required it can be
// initialized with NULL - it is very unlikely
const T_BCM_BOFP_APPCFGPHASE pboBCM_CFG_AppConfigPhase = boBCM_AppConfigurationPhase;

// Step 3
// Application Startup Init phase function pointer
// This function pointer is used to define function which does Application
// Startup Init, if application Startup Init is not required it can be
// initialized with NULL
const T_BCM_S16FP_APPSTARTUPINIT ps16BCM_CFG_AppStartupInit = s16APP_StartupInit;

// Step 4
// Application Init phase function pointer
// This function pointer is used to define function which does Application
// Init, if application Init is not required it can be
// initialized with NULL - it is very unlikely
const T_BCM_S16FP_APPINIT  ps16BCM_CFG_AppInit = s16APP_Init;

// Step 5
// Start application time slices function pointer
// This function pointer is used to define function which starts Application
// time slices, if application time slices are already initialized, it can be
// initialized with NULL
const T_BCM_S16FP_APPSTARTTS ps16BCM_CFG_StartAppTimeSlices = NULL;

// Configuration variable to define switch of startup handler to state Limited
// in case of Failure
// TRUE : Switch to board state Limited if App configuration or Startup Falis
// FALSE : Dont Switch to board state Limited if App configuration or
// Startup Falis
const BOOLEAN boBCM_CFG_PSwitchToLimited = FALSE;


// Message Handler Functions
const T_BCM_BOFP_MSGHDLR apboBCM_CFG_PMsgHandlerFct[] =
{
    NULL,                // Message handler of BCM_RST
};

// Total number of configured command handler functions
//const U16 u16BCM_CFG_PMsgHandlerFctCnt = (U16) (sizeof(apboBCM_CFG_PMsgHandlerFct) / sizeof(T_BCM_BOFP_MSGHDLR));
const U16 u16BCM_CFG_PMsgHandlerFctCnt = (U16)0;

// BCM Idle process deadline supervision configurable time in seconds (default value 10s)
const U32 u32BCM_CFG_PIdleProcDeadlineTime = (U32)10; // @suppress("No magic numbers")
//@}
//** End of BCM P configuration ****************************************************************************************


//**********************************************************************************************************************
//
//! @name            BCM Prolog/Epilog (PREP) functions
//
//**********************************************************************************************************************
//@{

// vBCM_RstSysRestart : Board specific Prolog/Epilog functions
const T_BCM_S16FP_SYSRESTART_PREP aps16BCM_RstSysRestartPrEpFct[BCM_PRO_EPI_CNT] =
{
    NULL,
    NULL
};

// vBCM_RstGotoFatal : Board specific Prolog/Epilog functions
const T_BCM_S16FP_GOTOFATAL_PREP aps16BCM_RstGotoFatalPrEpFct[BCM_PRO_EPI_CNT] =
{
    NULL,
    NULL
};

// vBCM_RstGotoCritical : Board specific Prolog/Epilog functions
const T_BCM_S16FP_GOTOCRITICAL_PREP aps16BCM_RstGotoCriticalPrEpFct[BCM_PRO_EPI_CNT] =
{
    NULL,
    NULL
};

// vBCM_RstGotoDownload : Board specific Prolog/Epilog functions
const T_BCM_S16FP_GOTODOWNLOAD_PREP aps16BCM_RstGotoDownloadPrEpFct[BCM_PRO_EPI_CNT] =
{
    NULL,
    NULL
};

// vBCM_Cycl50ms_Led : Board specific Prolog/Epilog functions
const T_BCM_LED_S16FP_CYCL50MS_PREP aps16BCM_Cycl50ms_LedPrEpFct[BCM_PRO_EPI_CNT] =
{
    NULL,
    NULL
};

// vBCM_LmtdGotoLimited : Board specific Prolog/Epilog functions
const T_BCM_S16FP_GOTOLIMITED_PREP aps16BCM_GotoLimitedPrEpFct[BCM_PRO_EPI_CNT] =
{
    NULL,
    NULL
};


// vBCM_WdTrigger : Board specific Prolog/Epilog functions
const T_BCM_WD_S16FP_TRIGGER_PREP aps16BCM_WdTriggerPrEpFct[BCM_PRO_EPI_CNT] =
{
    NULL,
    NULL
};

// boBCM_Cycl_PwrFailHandle : Board specific Prolog/Epilog functions
const T_BCM_PWR_S16FP_FAILHANDLE_PREP aps16BCM_PwrFailHandlePrEpFct[BCM_PRO_EPI_CNT] =
{
    NULL,
    NULL
};

// vBCM_TestGotoTest : Board specific Prolog/Epilog functions
const T_BCM_S16FP_GOTOTEST_PREP aps16BCM_RstGotoTestPrEpFct[BCM_PRO_EPI_CNT] =
{
    s16MON_BoardStateTestPRO,
    NULL
};

// s16BCM_OnnGet : Board specific Prolog/Epilog functions
const T_BCM_ONN_S16FP_GET_PREP aps16BCM_OnnGetPrEpFct[BCM_PRO_EPI_CNT] =
{
    NULL,
    NULL
};

// s16BCM_InvGetData : Board specific Prolog/Epilog functions
const T_BCM_INV_S16FP_GETDATA_PREP aps16BCM_InvGetDataPrEpFct[BCM_PRO_EPI_CNT] =
    {
        NULL,
        NULL
    };

// s16BCM_GenInvGetData : Board specific Prolog/Epilog functions
const T_BCM_INV_GEN_S16FP_GETDATA_PREP aps16BCM_InvGenGetDataPrEpFct[BCM_PRO_EPI_CNT] =
    {
        s16BCM_BS_GenInvGetSWAppData,
        NULL
    };

//@}
//** End of BCM Prolog/Epilog (PREP) functions *************************************************************************

//**********************************************************************************************************************
//
//! @name            BCM_UART configuration
//
//**********************************************************************************************************************
//@{

const E_OS_SLICES eBCM_CFG_UartTimeslice = eOS_SLICE_5MS;  //!< time-slice for checking UART

//@}
//** End of BCM_UART configuration **************************************************************************************

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *******************************************************************************************************

//** EndOfFile cfg_bcm.c ***********************************************************************************************
