//**********************************************************************************************************************
//
//                                                    cfgqeadc.c
//
//**********************************************************************************************************************
//
//                                        Copyright (C) 2022 by KNORR-BREMSE,
//                                   Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project IBC
//! @date 2023-11-02
//! @author C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file
//! @brief configuration for eQADC for DMA mode implementation
//!
//!
//
//**********************************************************************************************************************
//
// History
// Date       Author         Changes
// 2013-02-04 K. Chaudha     Start
// 2014-01-24 K. Chaudha     Hint Added in QADC_CHANNEL_COMMAND_QUEUE for Number of channels configured
//							 permanently for scanning of channels (According to JIRA issue BC_002-829)
// 2015-05-15  KH Duemer     Lint cleanup(Lint 9 / MISRA 2012)
// 2015-08-28  KH Duemer     JIRA BC_002-1685: configure EQADC to QADC_ADC_BLOCKING_MODE
// 2018-06-08  A. Mauro      Adapted for CPU04 board
// 2023-01-09  J. Lulli      Coding guidelines alignment
// 2023-11-02  C. Brancolini Lint Plus cleanup
//**********************************************************************************************************************

//****************************************** Compiler options ( #pragma ) **********************************************

//************************************** Header / include files ( #include ) *******************************************
#include <std_defs.h>     // standard definitions
#include "MPC5554.h"
#include "55xxeqadc.h"
#include "cfgeqadc.h"
#include "55xdma.h"
//************************************ Constant / macro definitions ( #define ) ****************************************
//! @name #define for Configurations
//! @{
//! Actual Number of channel to scan
#define QADC_NUMBER_OF_CHANNEL_TO_SCAN             ((U8)42)           // First 40 Channels are Normal ADC channels,
                                                                      // Channel No: 41 and 42 are Reference channels for calibration
//! MAX AVERAGE COUNT
#define QADC_AVERAGE_COUNT                         ((U8)5)
//! QADC Desired Operating clock frequency
#define QADC_CLOCK_FREQ_IN_MHZ                     ((U32)3000000)
//! QADC not used channel
#define QADC_CHANNEL_NOT_USED                          ((QADC_CHANNEL_NR)0xFF)
#define QADC_CAL_NOT_USED                              ((QADC_CAL_CONFIG)0xFF)
#define QADC_CLK_NOT_USED                              ((QADC_LST_CLOCK)0xFF)
#define QADC_FMT_NOT_USED                              ((QADC_FMT_CONFIG)0xFF)
//! @}

//! @name memory Allocation calculation
//! @{
//! Top offset for EQADC iRam Location
//#define QADC_TOP_IRAM_LOC                          ((U32)(0x4000D000U))
#define QADC_TOP_IRAM_LOC                          ((U32)(0x40008000U))
//! Buffer for Command Queue
#define QADC_COMMAND_QUEUE_BUFFER                  ((U16)(QADC_NUMBER_OF_CHANNEL_TO_SCAN * QADC_AVERAGE_COUNT * 4U))
//! Buffer for Result Queue
#define QADC_RESULT_QUEUE_BUFFER                   ((U16)(QADC_NUMBER_OF_CHANNEL_TO_SCAN * QADC_AVERAGE_COUNT * 2U))
//! Total buffer for Command & Result Queue
#define QADC_TOTAL_QUEUE_BUFFER                    ((U16)(QADC_COMMAND_QUEUE_BUFFER + QADC_RESULT_QUEUE_BUFFER ))
//! START for command queue memory location
#define QADC_COMMAND_QUEUE_MEM_LOC                 ((U32)(QADC_TOP_IRAM_LOC - QADC_COMMAND_QUEUE_BUFFER))
//! START for result queue memory location
#define QADC_RESULT_QUEUE_MEM_LOC                  ((U32)(QADC_COMMAND_QUEUE_MEM_LOC - QADC_RESULT_QUEUE_BUFFER))
//! @}

//****************************************** Type definitions ( typedef ) **********************************************
//******************************************** Global data definitions *************************************************

//************************************* Global constant definitions ( const ) ******************************************

const QADCDEVICES cQadcDevices[]= // @suppress("Wrong derived data type")
{
    //Note: Suppression of "Wrong derived data type", this warning come from the naming convention violation
    //      of QADCDEVICES

    // inhibit lint messages caused by address to object pointer conversion needed for memory mapped IO access
    // and unsigned integer literal without a 'U' suffix. Issues related to GenMPC55xx.
    //lint -save -e9048 -e9078
    {QADC_ADC_NR0,DMADEV_SERVICE(DMA_EQADC, DMA_EQADC_1, DMA_DIRTX),
            DMADEV_SERVICE(DMA_EQADC, DMA_EQADC_1, DMA_DIRRX),&(EQADC)},
    {(QADC_ADC_NR)QADCID_ENDVALUE,  0, 0, ( struct EQADC_tag *)0}
    //lint -restore
};

//! configuration table for Channel conversion command preparation
//! 42 channels are configured permanently(Number of channel to scan are fixed).
//! First 40 Normal ADC channels and  Channel No: 41 and 42 are Reference channels for calibration

// Inhibit lint note 9075 (external symbol defined without a prior declaration)
// due to a missing declaration in GenMPC55xx
const QADC_CHANNEL_COMMAND_QUEUE cQADC_CHANNEL_COMMAND_QUEUE = //lint !e9075 // @suppress("Wrong derived data type")
{
    //Note: Suppression of "Wrong derived data type", this warning come from the naming convention violation
    //      of QADC_CHANNEL_COMMAND_QUEUE
    //ADC Working Mode Selection
        QADC_ADC_BLOCKING_MODE,
    // Number if channels to be scan
         QADC_NUMBER_OF_CHANNEL_TO_SCAN,
    // Configure the count for Averaging the Channel Scan data read
        QADC_AVERAGE_COUNT,
    {  // Channel To SCAN     calibrated result    LST value               Result Format
        {QADC_CHANNEL_NUMBER0,  QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER1,  QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER2,  QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER3,  QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER4,  QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER5,  QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER6,  QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER7,  QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER8,  QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER9,  QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER10, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER11, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER12, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER13, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER14, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER15, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER16, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER17, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER18, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER19, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER20, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER21, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER22, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER23, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER24, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER25, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER26, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER27, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER28, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER29, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER30, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER31, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER32, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER33, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER34, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER35, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER36, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER37, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER38, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER39, QADC_CAL,          QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER43, QADC_NO_CAL,       QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NUMBER44, QADC_NO_CAL,       QADC_LST_CLK_CYCLE8, QADC_FMT_UNSIGNED },
        {QADC_CHANNEL_NOT_USED, QADC_CAL_NOT_USED, QADC_CLK_NOT_USED,   QADC_FMT_NOT_USED },
        {QADC_CHANNEL_NOT_USED, QADC_CAL_NOT_USED, QADC_CLK_NOT_USED,   QADC_FMT_NOT_USED },
    },
    // inhibit lint message caused by address to object pointer conversion needed for memory mapped IO access
    //lint -save -e9078
    (volatile U32 *)QADC_COMMAND_QUEUE_MEM_LOC,         // Data Block for DMA to transmit(Command Queue),
    (volatile U16 *)QADC_RESULT_QUEUE_MEM_LOC,          // Data Block for DMA to receive (Result Queue),
    //lint -restore
    QADC_CLOCK_FREQ_IN_MHZ,
};

//************************************** Modul global data segment ( static ) ******************************************
//************************************ Modul global constants ( static const ) *****************************************
//************************************* Local func/proc prototypes ( static ) ******************************************
// EndOfHeader *********************************************************************************************************

// EndOfFile CFGeqadc.c ************************************************************************************************
