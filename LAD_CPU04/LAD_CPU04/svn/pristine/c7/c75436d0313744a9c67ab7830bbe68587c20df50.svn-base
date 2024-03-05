//**********************************************************************************************************************
//
//                                              cfg_bcm_fwr.c
//
//**********************************************************************************************************************
//
//                                       Copyrights(c) by KNORR-BREMSE,
//
//                                       Rail Vehicle Systems, Munich
//
//! @project  IBC
//! @date      2023-11-02
//! @author    C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file cfg_bcm_fwr.c
//! @brief BCM_FWR - Configuration
//!
//! The CFG_BCM_FWR component has all user specific configuration of BCM_FWR
//!
//**********************************************************************************************************************
//
// History
// Date            Author              Changes
// 2017-02-23      V.Ingulkar          Start
// 2017-04-14      V.Ingulkar          Rework and Cleanup
// 2017-05-15      V.Ingulkar          BCM_FWR review rework
// 2017-06-23      V.Ingulkar          Added s16BCM_HAL_IoInit
// 2018-02-09      V.Ingulkar          Updates done to comply code with new coding guidelines and static code analysis
// 2018-05-30      V.Ingulkar          Added s16BCM_HAL_OwmInit
// 2018-07-10      V.Ingulkar          BC0025-53: Cleanup
// 2018-07-15      N.Joshi             Added s16BCM_FWR_SWDMain for handling software download
// 2018-07-31      V.Ingulkar          Added s16BCL_BD_HAL_WD_Pin_Init
// 2019-05-06      V.Ingulkar          Updates done as per core asset update v6.0
// 2019-05-15      V.Ingulkar          Pointer pu8BCM_FWR_CFG_RsmStart is declared as const
// 2019-08-05      V.Ingulkar          Changes done as per Jira - BC0025-183 - removed RSM configured for Feature List
// 2019-10-18      F.Heindl            Deleted s16BCL_GNN_GetNN_IBC_Startup from acBCM_FWR_CFG_CtrlFctsStep4
// 2020-01-30      A.Mauro             Lint cleanups
// 2020-04-17      V.Ingulkar          BC0025-270 : Changes because of inventory data related updates
// 2020-12-04      A.Gatare            Adapted for GenCA 6.11
// 2021-02-05      N.Jadhav            BC0025-435: pu8BCM_FWR_CFG_RsmStart declaration changed due to issue of pointer
//                                     initialization on LS1021 platform.
// 2021-04-06      N.Jadhav            BC0025-435 : Now s16BCM_FWR_CtrlContCheck1ms() configured from cfg_bcm_fwr.c
//                                                  s16BCM_FWR_CbSvlStart() called if platform specific pre SVL
//                                                  function not configured.
// 2021-05-12      S.Khadbade          BC0025-505: Updates are done to support generic inventory data feature
// 2021-11-11      N.Jadhav            BC0025-531: Code changes for const pointer definition for pu8BCM_FWR_CFG_RsmStartd
// 2022-11-26      S. Shinde           Adapted for GenCA 7.05
// 2022-12-13      R. Bhatlawande      Gen. Inventory feature disabled (boBCM_FWR_CFG_InvGenAvail = FALSE) as it is not
//                                     required for LAD01.
// 2023-01-09      J. Lulli            Coding guidelines alignment
// 2023-05-26      A. Mauro            Restored s16BCL_FWR_BD_CheckCrm call
// 2023-11-02      C. Brancolini       Added include "bcm_fwr_adp_bs_i.h", deleted pvBCM_FWR_CFG_CtrlStartCStartup (unused),
//                                     added bcl_fwr_bdspec.h. Used s16BCL_FWR_CtrlCacheEnable and s16BCL_FWR_CtrlCstartup
//                                     in acBCM_FWR_CFG_CtrlFctsStep2. Lint Plus clean up.
//
//**********************************************************************************************************************
//Note: Suppression of "Avoid Global Variables", the scope of these variables is global and must therefore be declared
//      as such

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************

#include "bcm_fwr_i.h"                  // BCM_FWR Internal interface
#include "bcm_fwr_s.h"                  // BCM_FWR System interface
#include "bcm_fwr.h"                    // BCM_FWR User interface
#include "bcm_hal_i.h"                  // BCM_HAL Internal interface
#include "bcm_hal_s.h"                  // BCM_HAL System interface
#include "swident.h"                    // SW ident block

// inhibit lint message caused by incomplete declaration of array. Issue related to GenMPC55xx.
//lint -save -e6028
#include "bcl_fwr_i.h"                  // BCL_FWR Internal interface
//lint -restore

#include "bcl_fwr_s.h"                  // BCL_FWR System interface
#include "cfg_55xxsiu.h"
#include "bcl_hal_s.h"
#include "bcl_hal_i.h"
#include "bcl_hal_bdspec_i.h"

#include "55xtpu.h"
#include "55xcan.h"
#include "55xdma.h"
#include "55xesci.h"
#include "55xdspi.h"
#include "55xxemios.h"
#include "55xxeqadc.h"
#include "simcpu.h"

#include "1wire_hws.h"
#include "MaintFlagH.h"
#include "ibcsysdefs.h"
#include "swd.h"                // BCM FWR SWD user interface

#include "ios_hal.h"
#include "nvm_hal.h"
#include "nvm_common.h"

#include "bcm_fwr_adp_bs_i.h"
#include "bcl_fwr_bdspec.h"

//**************************************** Constant / macro definitions ( #define ) ************************************

// Max. number of fatal error cause strings.
#define BCM_FWR_FAT_IDXMAX   16

// Max. fatal error cause string size including 0-termination.
#define BCM_FWR_FAT_STRSIZE  20

// Firmware board states which are visible on terminal channel
// For all the board states which are visible on Terminal channel are defined in E_BCM_BOARD_STATE (bcm_strt.h)
#define BCM_FWR_BS_DOWNLOAD  0x02
#define BCM_FWR_BS_CRITICAL  0x04


// Below format is as per BANK0 of DS28E01 version 7
// Below format is as per BANK1 of DS28E01 version 6
// Below format is as per BANK2 of DS28E01 version 6

// _BANK is for page / bank index in particular device
// _OFFSET is for offset for data in particular bank
// _SIZE is size of data

#define BOARDS_SN_BANK              0
#define BOARDS_SN_OFFSET           10
#define BOARDS_SN_SIZE              6

#define BOARD_REV_BANK              0
#define BOARDS_REV_OFFSET           7
#define BOARDS_REV_SIZE             3

#define BOARDS_STN_BANK             0
#define BOARDS_STN_OFFSET           1
#define BOARDS_STN_SIZE             3

#define BOARDS_STNPF_STR_BANK       0
#define BOARDS_STNPF_STR_OFFSET    22
#define BOARDS_STNPF_STR_SIZE      10

#define BOARDS_CAT_BANK             2
#define BOARDS_CAT_OFFSET           4
#define BOARDS_CAT_SIZE             2

#define BOARDS_TYP_BANK             2
#define BOARDS_TYP_OFFSET           6
#define BOARDS_TYP_SIZE             2

#define BOARDS_SUBTYP_BANK          2
#define BOARDS_SUBTYP_OFFSET        8
#define BOARDS_SUBTYP_SIZE          2

#define BOARDS_NAME_BANK            2
#define BOARDS_NAME_OFFSET         10
#define BOARDS_NAME_SIZE            8

#define BOARDS_MAC_BANK             0
#define BOARDS_MAC_OFFSET          16
#define BOARDS_MAC_SIZE             6

#define BOARDS_ID_BANK              1
#define BOARDS_ID_OFFSET           16
#define BOARDS_ID_SIZE              6

#define CPU_SN_BANK                 1
#define CPU_SN_OFFSET              10
#define CPU_SN_SIZE                 6

#define CPU_REV_BANK                1
#define CPU_REV_OFFSET              7
#define CPU_REV_SIZE                3

#define CPU_STN_BANK                1
#define CPU_STN_OFFSET              1
#define CPU_STN_SIZE                3

#define CPU_STNPF_STR_BANK          1
#define CPU_STNPF_STR_OFFSET       22
#define CPU_STNPF_STR_SIZE         10

#define BATTERY_INFO_BANK           0
#define BATTERY_INFO_OFFSET         4
#define BATTERY_INFO_MASK        0x00

#define HWPROTO_INFO_BANK           0
#define HWPROTO_INFO_OFFSET         4
#define HWPROTO_INFO_MASK        0x00

#define BCM_WDR_DELTA_TRIG_MIN   ((U16)250)
#define BCM_DWLD_TRIG_TIMEOUT    ((U16)500)
#define BCM_UART_BAUDRATE        ((U32)115200)

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************


//**********************************************************************************************************************
//
//! @name            BCM_FWR_WDR configuration
//
//**********************************************************************************************************************
//@{

// Minimum time in [ms] between two watchdog triggers.
const U16  u16BCM_FWR_CFG_WdrTrigDeltaMinMS   = BCM_WDR_DELTA_TRIG_MIN;

// Flag indicates , if LED should be used to indicate watchdog trigger
const BOOLEAN boBCM_FWR_CFG_WdrUseStateLed        = FALSE;

// Perform watchdog reset test in case of power on (TRUE: yes, FALSE: no)
// Note: This prolongs the board startup time, because of the watchdog reset.
const BOOLEAN boBCM_FWR_CFG_WdrTest              = TRUE;

//@}
//** End of BCM_FWR_WDR configuration **********************************************************************************


//**********************************************************************************************************************
//
//! @name            BCM_FWR_DWLD configuration
//
//**********************************************************************************************************************
//@{

// Trigger timeout for download ( multply of 10 mSec)
// Wait max. 5 seconds for download trigger
const U16  u16BCM_FWR_CFG_DwldTrigTimeout   = BCM_DWLD_TRIG_TIMEOUT;

const T_BCM_FWR_S16FP_STARTDWLD ps16BCM_FWR_CFG_StartDwld = s16SWD_Main;
//const T_BCM_FWR_S16FP_STARTDWLD ps16BCM_FWR_CFG_StartDwld = NULL;

//@}
//** End of BCM_FWR_DWLD configuration *********************************************************************************


//**********************************************************************************************************************
//
//! @name            BCM_FWR_UART configuration
//
//**********************************************************************************************************************
//@{

// UART Baudrate
const U32  u32BCM_FWR_CFG_UartBaudrate   = BCM_UART_BAUDRATE;

// UART ID
const E_BCM_COMMON_UART_IDX eBCM_FWR_CFG_UartId = eBCM_COMMON_UART_ID0;

//@}
//** End of BCM_FWR_UART configuration *********************************************************************************

//**********************************************************************************************************************
//
//! @name            BCM_FWR_LOG configuration
//
//**********************************************************************************************************************
//@{

//! NVM Device Id used to store BCM_FWR_LOG information
const U8 u8BCM_FWR_CFG_LogNvmDevId = NVM_DEVICE_ID0;

//@}
//** End of BCM_FWR_LOG configuration **********************************************************************************


//**********************************************************************************************************************
//
//! @name            BCM_FWR_LOOP configuration
//
//**********************************************************************************************************************
//@{

//----------------------------------------------------------------------------------------------------------------------
// List of configured 10 mSec loop functions
//
// Note:
// - -- //Todo:
//----------------------------------------------------------------------------------------------------------------------

// Inhibit lint message 552 (external variable not accessed).
// acBCM_FWR_CFG_Loop10msFcts is defined in this file and used to get its size,
// its fields are accessed in GenMPC55xx module.
//lint -save -e552
const T_BCM_FWR_LOOP_VFP  acBCM_FWR_CFG_Loop10msFcts[] =
  {
      NULL
  };

// Number of Configured 10 mSec loop functions
const U16 u16BCM_FWR_CFG_Loop10msFctsCnt = (U16)( sizeof(acBCM_FWR_CFG_Loop10msFcts) / sizeof(T_BCM_FWR_LOOP_VFP) );
//lint -restore

//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Board state Conversion from Permanent Internal state to Externally Visible state
//
// Note: This conversion is required, as BCM_FWR handles internal state numbering differently, which is not known to
// user / terminal channel interface.
// This conversion table converts Permanent Internal state to Externally Visible state
//----------------------------------------------------------------------------------------------------------------------
const C_BCM_FWR_LOOP_BS_CONV acBCM_FWR_CFG_LoopConvTable[BCM_FWR_STATE_ES_NUM] =
{
    { BCM_FWR_STATE_PERM_CRITICAL,  BCM_FWR_BS_CRITICAL },
    { BCM_FWR_STATE_DOWNLOAD,       BCM_FWR_BS_DOWNLOAD }
};

//@}
//** End of BCM_FWR_LOOP configuration *********************************************************************************

//**********************************************************************************************************************
//
//! @name            BCM_FWR_RSM configuration (RSM Memory Configuration)
//
//**********************************************************************************************************************

// Total size of reset safe memory
#define RSM_SIZE_TOTAL         ((U32) 0x8000UL)
// Reserve for SVL general use
#define RSM_SIZE_SVL_RESERVED  1024U

#pragma section RSM_data "" ".bss.resetsafe" // @suppress("No #pragma instructions")
#pragma use_section RSM_data au8BCM_FWR_CFG_Rsm // @suppress("No #pragma instructions")

// Reset safe memory buffer
U8 au8BCM_FWR_CFG_Rsm[RSM_SIZE_TOTAL]; // @suppress("Avoid Global Variables")

// Reset Safe memory buffer start address
U8* pu8BCM_FWR_CFG_RsmStart = NULL; // @suppress("Avoid Global Variables")

// Reset safe memory size
const U32 u32BCM_FWR_CFG_RsmSize = RSM_SIZE_TOTAL;

// Note : It is compulsory to configure required RSM memory for components -
// BoardState (BDSTAT), CriticalState (CRIT), Debugger, WarmState (WS),
// and SVL. RSM Ids can be user specific

// RSM ID of RSM memory used by Board State
#define BCM_FWR_RSM_ID_BDSTAT         0U
#define BCM_FWR_RSM_ID_BDSTAT_SIZE    BCM_FWR_RSM_SIZE(sizeof(C_BCM_FWR_RSM_BDSTAT))
#define BCM_FWR_RSM_ID_BDSTAT_OFFS    0U

// RSM ID of RSM memory used by Critical State
#define BCM_FWR_RSM_ID_CRIT           1U
#define BCM_FWR_RSM_ID_CRIT_SIZE      BCM_FWR_RSM_SIZE(sizeof(C_BCM_FWR_RSM_CRIT))
#define BCM_FWR_RSM_ID_CRIT_OFFS      (BCM_FWR_RSM_ID_BDSTAT_OFFS + BCM_FWR_RSM_ID_BDSTAT_SIZE)

// RSM ID of RSM memory used for Debugger state
#define BCM_FWR_RSM_ID_DEBUGGER       2U
#define BCM_FWR_RSM_ID_DEBUGGER_SIZE  BCM_FWR_RSM_SIZE(sizeof(C_BCM_FWR_RSM_DEBUGGER))
#define BCM_FWR_RSM_ID_DEBUGGER_OFFS  (BCM_FWR_RSM_ID_CRIT_OFFS + BCM_FWR_RSM_ID_CRIT_SIZE)

// RSM ID of RSM memory used for SVL Warm Start indication
#define BCM_FWR_RSM_ID_WS             3U
#define BCM_FWR_RSM_ID_WS_SIZE        BCM_FWR_RSM_SIZE(sizeof(C_BCM_FWR_RSM_WS))
#define BCM_FWR_RSM_ID_WS_OFFS        (BCM_FWR_RSM_ID_DEBUGGER_OFFS + BCM_FWR_RSM_ID_DEBUGGER_SIZE)

// RSM ID of RSM memory used by SVL only
#define BCM_FWR_RSM_ID_SVL            4U
#define BCM_FWR_RSM_ID_SVL_SIZE       BCM_FWR_RSM_SIZE(RSM_SIZE_SVL_RESERVED)
#define BCM_FWR_RSM_ID_SVL_OFFS       (BCM_FWR_RSM_ID_WS_OFFS + BCM_FWR_RSM_ID_WS_SIZE)

// RSM ID of RSM memory used for Poff Data Save
#define BCM_FWR_RSM_ID_PDS            5U
#define BCM_FWR_RSM_ID_PDS_SIZE       BCM_FWR_RSM_SIZE(sizeof(C_BCM_FWR_RSM_PDS))
#define BCM_FWR_RSM_ID_PDS_OFFS       (BCM_FWR_RSM_ID_SVL_OFFS + BCM_FWR_RSM_ID_SVL_SIZE)

// RSM ID of RSM memory used for Application Version
#define BCM_FWR_RSM_ID_APPVERS        6U
#define BCM_FWR_RSM_ID_APPVERS_SIZE   BCM_FWR_RSM_SIZE( sizeof(C_BCM_FWR_RSM_APPVERS) )
#define BCM_FWR_RSM_ID_APPVERS_OFFS   (BCM_FWR_RSM_ID_PDS_OFFS + BCM_FWR_RSM_ID_PDS_SIZE)

#define BCM_FWR_RSM_USED              ( BCM_FWR_RSM_ID_APPVERS_OFFS + BCM_FWR_RSM_ID_APPVERS_SIZE )

// Used reset safe memory size
const U32 u32BCM_FWR_CFG_RsmUsed = BCM_FWR_RSM_USED;


// Inhibit lint message 552 (external variable not accessed).
// acBCM_FWR_CFG_RsmId is defined in this file and used to get its size,
// its fields are accessed in GenMPC55xx module.
//lint -save -e552

// RSM Id configuration table
const C_BCM_FWR_RSM_ID acBCM_FWR_CFG_RsmId[] =
{
    { BCM_FWR_RSM_ID_BDSTAT,
      BCM_FWR_RSM_ID_BDSTAT_SIZE,
      BCM_FWR_RSM_ID_BDSTAT_OFFS },     // RSM ID 0

    { BCM_FWR_RSM_ID_CRIT,
      BCM_FWR_RSM_ID_CRIT_SIZE,
      BCM_FWR_RSM_ID_CRIT_OFFS },
                                        // RSM ID 1

    { BCM_FWR_RSM_ID_DEBUGGER,
      BCM_FWR_RSM_ID_DEBUGGER_SIZE,
      BCM_FWR_RSM_ID_DEBUGGER_OFFS },
                                        // RSM ID 2

    { BCM_FWR_RSM_ID_WS,
      BCM_FWR_RSM_ID_WS_SIZE,
      BCM_FWR_RSM_ID_WS_OFFS },
                                        // RSM ID 3

    { BCM_FWR_RSM_ID_SVL,
      BCM_FWR_RSM_ID_SVL_SIZE,
      BCM_FWR_RSM_ID_SVL_OFFS },
                                        // RSM ID 4

    { BCM_FWR_RSM_ID_PDS,
      BCM_FWR_RSM_ID_PDS_SIZE,
      BCM_FWR_RSM_ID_PDS_OFFS },
                                        // RSM ID 5
    {
      BCM_FWR_RSM_ID_APPVERS,
      BCM_FWR_RSM_ID_APPVERS_SIZE,
      BCM_FWR_RSM_ID_APPVERS_OFFS}      // RSM ID 6
};

// Total number of configured RSM IDs
const U8 u8BCM_FWR_CFG_RsmIdCnt = (U8) (sizeof(acBCM_FWR_CFG_RsmId) / sizeof(C_BCM_FWR_RSM_ID));
//lint -restore

// RSM area for SVL use
BCM_FWR_RSM_AREA_ID_SVL_SET(BCM_FWR_RSM_ID_SVL)

// RSM area to save board state
BCM_FWR_RSM_AREA_ID_BDSTAT_SET(BCM_FWR_RSM_ID_BDSTAT)

// RSM area to save critical state data
BCM_FWR_RSM_AREA_ID_CRITICAL_SET(BCM_FWR_RSM_ID_CRIT)

// RSM area to save debugger info
BCM_FWR_RSM_AREA_ID_DEBUGGER_SET(BCM_FWR_RSM_ID_DEBUGGER)

// RSM area to save Warm Start indication info
BCM_FWR_RSM_AREA_ID_WS_SET(BCM_FWR_RSM_ID_WS)

// RSM area to save Power off Data Save info
BCM_FWR_RSM_AREA_ID_PDS_SET(BCM_FWR_RSM_ID_PDS)

// RSM area to save Application Version
BCM_FWR_RSM_AREA_ID_APPVERS_SET ( BCM_FWR_RSM_ID_APPVERS )

//** End of BCM_FWR_RSM configuration **********************************************************************************



//**********************************************************************************************************************
//
//! @name           FWR CTRL step function lists configuration
//
//**********************************************************************************************************************
//@{




//----------------------------------------------------------------------------------------------------------------------
// List of configured step 1 functions.
//
// Note: Testing of CPU, GPIO and initialization of External interfaces
// is done in step1
// UART is not available also C environment is not setup
// Failure of these functions result into board state FATAL
//----------------------------------------------------------------------------------------------------------------------

// Inhibit lint message 552 (external variable not accessed).
// acBCM_FWR_CFG_CtrlFctsStep1 is defined in this file and used to get its size,
// its fields are accessed in GenMPC55xx module.
//lint -save -e552
const C_BCM_FWR_CTRL_STEP_FCTS  acBCM_FWR_CFG_CtrlFctsStep1[] =
{
    //***** Very basic init or test functions are placed here ****************
    { s16BCL_FWR_CTRL_Start_TestCpu,      "TestCpu" },
    { s16BCL_FWR_CTRL_Start_TestGpio,     "TestGpio" },
    { s16BCL_FWR_CTRL_Start_InitExtIf,    "InitExtIf" },
    { s16BCL_FWR_CTRL_Start_ExtRamInit,   "InitExtRam" },
    { s16BCL_FWR_CTRL_InitRsmBuffer,      "RsmBufferInit" }
};

const U16 u16BCM_FWR_CFG_CtrlFctsStep1Cnt = (U16)(sizeof(acBCM_FWR_CFG_CtrlFctsStep1) /
    sizeof(C_BCM_FWR_CTRL_STEP_FCTS));
//lint -restore

//----------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------
// List of configured step 2 functions.
//
// Note: Initialization and testing of FWR resources done in Step2
// Checking of board state
// UART is available at this step
// It is expected that C environment will be available at the end of step 2
// Failure of these functions result into board state FATAL
//----------------------------------------------------------------------------------------------------------------------

// Inhibit lint message 552 (external variable not accessed).
// acBCM_FWR_CFG_CtrlFctsStep2 is defined in this file and used to get its size,
// its fields are accessed in GenMPC55xx module.
//lint -save -e552
const C_BCM_FWR_CTRL_STEP_FCTS  acBCM_FWR_CFG_CtrlFctsStep2[] =
{
    //***** BCM_FWR start functions (Normally not to be changed!) ******************************************************
    { s16BCM_FWR_CtrlInitAndTriggerFwrWd,      "InitAndTriggerFwrWd" },
    { s16BCM_FWR_CtrlStartCheckRsm,            "CheckRSM"},
    { s16BCM_FWR_CtrlStartHandlePowerOnReset,  "HandlePowerOnReset" },
    { s16BCM_FWR_CtrlStartCleanUpTgtBdState,   "CleanUpTgtBdState" },
    { s16BCM_FWR_CtrlStartCheckDebugger,       "CheckDebugger" },
    { s16BCM_FWR_CtrlStartCheckFatal,          "CheckFatal" },
    { s16BCL_FWR_CTRL_Start_TestRam,           "TestRam" },

    //***** Functions called after BCM_FWR functions *******************************************************************
    { s16BCL_FWR_CtrlCacheEnable,              "cache_enable" },
    { s16BCL_FWR_CtrlCstartup,                 "cStartup" },
    //  { s16BCM_FWR_UartInit,                     "BcmFwrUartInit" },  //!< Needs again initialization
};

const U16 u16BCM_FWR_CFG_CtrlFctsStep2Cnt = (U16)(sizeof(acBCM_FWR_CFG_CtrlFctsStep2) /
    sizeof(C_BCM_FWR_CTRL_STEP_FCTS));
//lint -restore
//----------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------
// List of configured step 3 functions.
//
// Note: C Environment is available for Step 3
// Initialization of all required Software module / drivers is done in Step3
// Failure of these functions result into board state FATAL / CRITICAL
//----------------------------------------------------------------------------------------------------------------------

// Inhibit lint message 552 (external variable not accessed).
// acBCM_FWR_CFG_CtrlFctsStep3 is defined in this file and used to get its size,
// its fields are accessed in GenMPC55xx module.
//lint -save -e552
const C_BCM_FWR_CTRL_STEP_FCTS  acBCM_FWR_CFG_CtrlFctsStep3[] =
{
    { s16BCM_FWR_UartInit,                "BcmFwrUartInit" },   //Needs again initialization
    //***** Callback and watchdog init (Normally not to be changed!) ***************************************************
    { s16BCM_FWR_CbDeInstall,                "CBDeinstall" },
    { s16BCM_FWR_CtrlContReInitFwrWd,        "ReInitFwrWd" },

    //***** ReInit RSM memory after cStartup ***************************************************************************
    { s16BCL_FWR_CTRL_InitRsmBuffer,         "ReInitRsmBuffer" },
    { s16BCM_FWR_RsmInit,                    "ReInitRSM" },

    //***** other ******************************************************************************************************
    { s16BCL_FWR_CTRL_Cont_SetEhReady,       "SetEhReady" },
    { s16BCM_FWR_CtrlTestFwrRom,             "TestFwrRom" },
    { s16BCL_FWR_CTRL_Cont_GetResetEvent,    "GetResetEvent"},
    { s16BCM_FWR_CtrlContCheckSavePoffData,  "CheckSavePoffData"},
    { s16SIU_BD_Startup,                     "SiuBdStartup"},
    { s16BCL_HAL_Init,                       "InitBclHal"},
    { s16BCM_HAL_IoInit,                     "InitBcmIo"},
    { s16BCL_BD_HAL_WD_Pin_Init,             "InitWDIoPin"},
    { s16BCM_HAL_TimInit,                    "InitBcmHalTim" },
    { s16CANHwDefaultInit,                   "InitCanHw" },
    { s16TPUStdInit,                         "InitTPU" },
    { s16OWRInit,                            "InitOneWire"},
    { s16BCM_HAL_OwmInit,                    "InitBcmOwm"},
    { s16BCL_FWR_BD_CheckCrm,                "CheckCrm" },
    { s16BCL_FWR_CTRL_Cont_CheckBdHrc,       "CheckBdHrc" },
    { s16EDMAInitGeneralDMA,                 "InitEdma" },
    { s16BCL_FWR_DSPIInit,                   "InitDSPI" },
    { s16SIMCPUInit,                         "InitSimCPU" },
    { s16BCL_HAL_BD_IOInit,                  "InitIO" },
    { s16NVM_HAL_Init,                       "InitNvmHal" },
    { s16BCM_FWR_CtrlSavePoffData,           "SavePoffData"},
    { s16BCM_FWR_CtrlContPrintPoffInfo,      "PrintPoffInfo"},
    //***** Init NonPoff FRAM handling *********************************************************************************
    { s16MaintFlagH_Init,                    "InitMaintFlag" }
};

const U16 u16BCM_FWR_CFG_CtrlFctsStep3Cnt = (U16)(sizeof(acBCM_FWR_CFG_CtrlFctsStep3) /
    sizeof(C_BCM_FWR_CTRL_STEP_FCTS));
//lint -restore
//----------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------
// List of configured step 4 functions.
//
// Note:
// Initialization of required Software module / drivers is done in Step4
// Failure of these functions result into board state FATAL / CRITICAL
//----------------------------------------------------------------------------------------------------------------------

// Inhibit lint message 552 (external variable not accessed).
// acBCM_FWR_CFG_CtrlFctsStep4 is defined in this file and used to get its size,
// its fields are accessed in GenMPC55xx module.
//lint -save -e552
const C_BCM_FWR_CTRL_STEP_FCTS  acBCM_FWR_CFG_CtrlFctsStep4[] =
{
    //***** Tests and additional driver inits **************************************************************************
    { s16BCL_FWR_CTRL_Cont_TestMmu,          "TestMmu" },
    { s16BCL_FWR_CTRL_Cont_TestDma,          "TestDma" },
    { s16EMIOSInit,                          "InitEMIOS" },
    { s16QADCInit,                           "InitQadc" },
    { s16BCL_HAL_ADC_Init,                   "InitBclHalADC" },
    { s16BCL_HAL_HWSD_Init,                  "InitBclHalHWSD" },
    { s16BCL_HAL_VMT_Init,                   "InitBclHalVMT" },
//    { s16BCL_GNN_GetNN_IBC_Startup,          "GetNodeNo" },
    { s16BCM_HAL_TempInit,                   "InitBcmHalTemp" },
    { s16BCL_FWR_CTRL_Cont_Vmt,              "Vmt"},
    { s16BCL_FWR_CTRL_Cont_Hwsd,             "Hwsd"},
    { s16IOS_HAL_InitBoard,                  "InitIOS" }
};

const U16 u16BCM_FWR_CFG_CtrlFctsStep4Cnt = (U16)(sizeof(acBCM_FWR_CFG_CtrlFctsStep4) /
    sizeof(C_BCM_FWR_CTRL_STEP_FCTS));
//lint -restore
//**********************************************************************************************************************-


//----------------------------------------------------------------------------------------------------------------------
// List of configured step 5 functions.
//
// Note: Functions related to searching of SVL, callback Install and
// compatibility checking are called in Step5, after successful execution of
// step 5, software jumps to SVL (if valid entry is available)
//----------------------------------------------------------------------------------------------------------------------
//**********************************************************************************************************************

// Inhibit lint message 552 (external variable not accessed).
// acBCM_FWR_CFG_CtrlFctsStep5 is defined in this file and used to get its size,
// its fields are accessed in GenMPC55xx module.
//lint -save -e552
const C_BCM_FWR_CTRL_STEP_FCTS  acBCM_FWR_CFG_CtrlFctsStep5[] =
{
    //***** Search, check and start SVL (Normally not to be changed!) **************************************************
                  { s16BCM_FWR_CtrlContSearchSvl,          "SearchSvl"      },
                  { s16BCM_FWR_CtrlTestSvlRom,             "TestSvlRom"     },
                  { s16BCL_HAL_SetFctTabExePtr,            "NonCcaCbInstall"},
                  { s16BCM_FWR_CtrlContInitSvlWd,          "InitSvlWd"      },
                  { s16BCL_FWR_BD_SetStackOvfHndlr,        "StackOvfHndlr"  }
};

const U16 u16BCM_FWR_CFG_CtrlFctsStep5Cnt = (U16)(sizeof(acBCM_FWR_CFG_CtrlFctsStep5) /
    sizeof(C_BCM_FWR_CTRL_STEP_FCTS));
//lint -restore
//----------------------------------------------------------------------------------------------------------------------


// Ident block identifier of SVL executable
const U8  au8BCM_FWR_CFG_CtrlSvlIdentifier[32] = "!!!!!!!EXE_IDENTIFICATION!!!!!!"; // @suppress("No magic numbers")

// SW type of SVL executable
// Todo: Sw Type ??? Need to define enum ?
const U16 u16BCM_FWR_CFG_CtrlSvlSWType  = 1; // @suppress("No magic numbers")

// Min. address of area where to search for SVL executable
const U32 u32BCM_FWR_CFG_CtrlSvlMinAddr = 0x080000; // @suppress("No magic numbers")

// Max. address of area where to search for SVL executable
const U32 u32BCM_FWR_CFG_CtrlSvlMaxAddr = 0x0E0000; // @suppress("No magic numbers")

// Address steps used to search for SVL executable
const U32 u32BCM_FWR_CFG_CtrlSvlSearchSteps = 0x1000; // @suppress("No magic numbers")

// Firmware infinite Loop valid for this board - SHOULD BE ALWAYS "TRUE"
// This variabke is used to enable infinite for(;;) loop at the end of firmware startup
// On SCIOPTA based projects such as LAD01/02/03, LAD25 and CCB (MPC and Aurix based) this loop should be enabled
// as before program control reach to end of firmware, SVL should be started or other board state
// It is not expected that control reaches to end, this loop is added for force Watchdog reset
// On PikeOS based projects such as LAD15 (Layerscape based) this should be disabled, as in this case firmware
// partition and application partitions are active ate same time and infinite loop can cause problem
const BOOLEAN boBCM_FWR_CFG_CtrlFwrInfiniteLoop = TRUE;

// Node number to be used, when no valid node number is available
const U8 u8BCM_FWR_CFG_DefaultNodeNumber = IBC_NODE_ID_DEFAULT;

// Board state in case of SVL ROM error (TRUE: DOWNLOAD. FALSE:FATAL)
const BOOLEAN  boBCM_FWR_CFG_SvlRomErrorCausesDownload = TRUE;
//@}
//** End of BCM_FWR_CTRL configuration *********************************************************************************


//**********************************************************************************************************************
//
//! @name            BCM_FWR_CB configuration
//
//**********************************************************************************************************************
//@{

// Pre SVL start function pointer
const T_BCM_VFP_PRESVLSTRT pvBCM_FWR_CFG_CtrlPreSvlStartFct = NULL;
//**********************************************************************************************************************
//
//! @name            BCM_FWR_INV configuration
//
//**********************************************************************************************************************
//@{

// Size of inventory data for interface version 0x05 - excluding status byte - status byte is handled by SDI
#define  BCM_FWR_INV_SIZE_MAX   64

//----------------------------------------------------------------------------------------------------------------------
//! Boards inventory data expected version format
//
//! Below are valid values
//! - 0x0005 - Only IBC inventory data
//! - 0x0006 - IBC inventory data plus board specific inventory data
//! - 0x000x - IBC inventory data plus board specific inventory data
//! - 0x0000 – When complete inventory data is different and basic format of version 0x0005
//!            is not followed. Rare case, but just to handle this case for future.
//----------------------------------------------------------------------------------------------------------------------
const U16 u16BCM_FWR_CFG_InvFmtVers = BCM_FWR_INV_IFID_V05;

//! Inventory data buffer
U8 au8BCM_FWR_InvDataBuffer[BCM_FWR_INV_SIZE_MAX]; // @suppress("Avoid Global Variables")

//! Size of Inventory data buffer
const U16 u16BCM_FWR_CFG_InvBufSize = BCM_FWR_INV_SIZE_MAX;

//@}
//** End of BCM_FWR_COMP configuration *********************************************************************************

//**********************************************************************************************************************
//
//! @name            BCM_FWR_INV_GEN configuration
//
//**********************************************************************************************************************
//@{

// Explanation For boBCM_FWR_CFG_InvGenAvail flag
//----------------------------------------------------------------------------------------------------------------------
//! User Can decide either he want to use generic inventory Data feature or NOT by  setting
// boBCM_FWR_CFG_InvGenAvail flag.
//!
//!boBCM_FWR_CFG_InvGenAvail = TRUE--> By sending Command ID 0x51, User Can retrieve Generic inventory data
//!if this true bs implementation generic inventory needed and below configuration
//! boBCM_FWR_CFG_InvGenAvail = False --> Generic Inventory Feature is Unavailable, If user send 0x51 Command then
//! it result into Command Failure. if dummy config needed for compilation
//!
//----------------------------------------------------------------------------------------------------------------------

BOOLEAN boBCM_FWR_CFG_InvGenAvail = FALSE; // @suppress("Avoid Global Variables")

// Max page size for Generic Inventory data
#define  MAX_PAGE_SIZE                         (480U)

// Total number of pages available in Generic inventory
#define  TOTAL_PAGE_COUNT       (2U)

//Max Page size for generic inventory data
const U16  u16BCM_FWR_CFG_InvGenMaxPageSize  = MAX_PAGE_SIZE;

//Total Page count for generic inventory data
const U8  u8BCM_FWR_CFG_InvGenPageCount  = TOTAL_PAGE_COUNT;

//! Generic Inventory data buffer
U8 au8BCM_FWR_InvGenDataBuffer[(TOTAL_PAGE_COUNT)*(MAX_PAGE_SIZE)]; // @suppress("Avoid Global Variables")

//! Generic Inventory Buffer to store page size
U16 au16BCM_FWR_InvGenPageSizeBuffer[TOTAL_PAGE_COUNT]; // @suppress("Avoid Global Variables")


// Generic Page Summary info
const C_BCM_FWR_INV_GEN_PAGE_INFO acBCM_FWR_CFG_InvGenPageInfo[TOTAL_PAGE_COUNT]=
{    //No Of HW module     //No of SW module   //GS1 modules  //Custom modules    // PAGE Name
    {   1,                   2,                 0,              0,                  "LAD25"},//@suppress("No magic numbers")
    {   3,                   2,                 0,              0,              "LAD25_EXT"}//@suppress("No magic numbers")
};


//** End of BCM_FWR_GEN configuration *********************************************************************************

//**********************************************************************************************************************
//
//! @name            BCM_FWR_COMP configuration
//
//**********************************************************************************************************************
//@{

//----------------------------------------------------------------------------------------------------------------------
// Array of compatible FWR descriptors.
//
// Note: Constant acBCM_FWR_CFG_Comp is not needed if it contains no entry.
// Maximum 5 entries are supported
//----------------------------------------------------------------------------------------------------------------------
static const C_BCM_FWR_COMP  acBCM_FWR_CFG_Comp[] =
{
    // Just an example:  STN ccccc/ddddd, version 3.05.0000
    { "34599/FW1",  CREATE_CA_VERSION_DESCRIPTOR (3, 5, 0) },
};

//----------------------------------------------------------------------------------------------------------------------
// List of compatible FWR descriptors
//
// This list describes to which alternative STN and version descriptor the
// current FWR is also compatible.
//
// - List empty    : This means, that acBCM_FWR_CFG_Comp[] contains no valid
//                   entry or is not defined at all.
//                   cBCM_FWR_CFG_CompList = { 0, NULL }
//
// - List not empty: This means, that acBCM_FWR_CFG_Comp[] is defined and
//                   contains at least one entry.
//----------------------------------------------------------------------------------------------------------------------
const C_BCM_FWR_COMP_LIST cBCM_FWR_CFG_CompList =
                   { (U8)(sizeof(acBCM_FWR_CFG_Comp)/sizeof(C_BCM_FWR_COMP)), acBCM_FWR_CFG_Comp };

//@}
//** End of BCM_FWR_COMP configuration *********************************************************************************

//**********************************************************************************************************************
//
//! @name                   BCM_FWR_HWINF configuration
//
//**********************************************************************************************************************
//@{

//! Id of one wire memory device which is used to store inventory data
const U8 u8BCM_FWR_CFG_HwInfOwmDevId = 0;

//! Offset of version byte in each bank, it is assumed that same offset is used for all banks to store version
const U8 u8BCM_FWR_CFG_HwInfVersionOffset = 0;

// One wire memory device, bank and offset configuration for inventory data,
// lengths for these are fixed and are defined in bcm_hal_hwinf_i.h
const C_BCM_FWR_HWINF_DATA_POS_INFO cBCM_FWR_CFG_HwInfDataPosInfo =
{
    CPU_SN_BANK,            CPU_SN_OFFSET,              CPU_SN_SIZE,
    CPU_REV_BANK,           CPU_REV_OFFSET,             CPU_REV_SIZE,
    CPU_STN_BANK,           CPU_STN_OFFSET,             CPU_STN_SIZE,
    CPU_STNPF_STR_BANK,     CPU_STNPF_STR_OFFSET,       CPU_STNPF_STR_SIZE,
    BOARDS_SN_BANK,         BOARDS_SN_OFFSET,           BOARDS_SN_SIZE,
    BOARD_REV_BANK,         BOARDS_REV_OFFSET,          BOARDS_REV_SIZE,
    BOARDS_STN_BANK,        BOARDS_STN_OFFSET,          BOARDS_STN_SIZE,
    BOARDS_STNPF_STR_BANK,  BOARDS_STNPF_STR_OFFSET,    BOARDS_STNPF_STR_SIZE,
    BOARDS_CAT_BANK,        BOARDS_CAT_OFFSET,          BOARDS_CAT_SIZE,
    BOARDS_TYP_BANK,        BOARDS_TYP_OFFSET,          BOARDS_TYP_SIZE,
    BOARDS_SUBTYP_BANK,     BOARDS_SUBTYP_OFFSET,       BOARDS_SUBTYP_SIZE,
    BOARDS_NAME_BANK,       BOARDS_NAME_OFFSET,         BOARDS_NAME_SIZE,
    BOARDS_MAC_BANK,        BOARDS_MAC_OFFSET,          BOARDS_MAC_SIZE,
    BOARDS_ID_BANK,         BOARDS_ID_OFFSET,           BOARDS_ID_SIZE,
    BATTERY_INFO_BANK,      BATTERY_INFO_OFFSET,        BATTERY_INFO_MASK,
    HWPROTO_INFO_BANK,      HWPROTO_INFO_OFFSET,        HWPROTO_INFO_MASK
};

//@}
//** End of BCM_FWR_HWINF configuration ********************************************************************************

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *******************************************************************************************************


// EndOfFile cfg_bcm_fwr.c *********************************************************************************************
