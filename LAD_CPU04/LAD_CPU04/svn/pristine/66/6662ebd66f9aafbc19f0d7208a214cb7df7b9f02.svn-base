//**********************************************************************************************************************
//
//                                                 cfg_mon.c
//
//**********************************************************************************************************************
//
//                                     Copyrights(c) 2022 by KNORR-BREMSE,
//                                        Rail Vehicle Systems, Munich
//
//! @project  IBC
//! @date     2023-11-30
//! @author   C. Brancolini
//
//**********************************************************************************************************************
//!
//! @file cfg_mon.c
//! @brief  Service MON - Measurement data Address Range Configuration
//!
//**********************************************************************************************************************
// History
//  Date       Author       Changes:
// ----.--.--   ---         Start, based on B2G
// 2013-07-10   H. Shaikh   adapted for B3G
// 2014-02-14   A. Mauro    adapted for EBxxx
// 2014-05-29   H. Shaikh   Changed MEM_SEG_DESCRIPTORS to MON_MEM_SEG_DESCRIPTORS
// 2015-12-10   P. Munoli   For jira issue: BC_002-987,changed number of
//                          memory segments value from 9 to 5.
// 2016-01-17   A. Mauro    Jira issue TC_007-84 solved
// 2018-09-07   A. Mauro    TC_004-4962: Configured for IBC measurements
// 2019-12-30   R. Dongre   Removed esra_def.h includes
// 2020-02-12   A. Mauro    Lint clean ups
// 2020-11-26   A. Gatare   Adapated for GenCA 6.11.Adapted as per implemented service MON in GenCA.
// 2023-01-09   J. Lulli    Coding guidelines alignment
// 2023-05-16   C. Brancolini  Lint clean up
// 2023-11-30 C. Brancolini Lint Plus clean up
//
//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "mon_i.h"                      // Interface to MON
#include "mon_cpu04.h"

//**************************************** Constant / macro definitions ( #define ) ************************************
#define MEM_SEG_COUNT                    5U               //No of memory segment count
//**************************************** Starting address of mem segments ********************************************
#define MEM_RSM_START_ADDR        ((U8*)0x20000000)  // Memory segment 1 start address, 64KB valid (RSM)
#define MEM_DRV_START_ADDR        ((U8*)0x20010000)  // Memory segment 2 start address, 192KB valid (DRV)
#define MEM_SYS_START_ADDR        ((U8*)0x20040000)  // Memory segment 3 start address, 64KB valid (system)
#define MEM_SPARE_START_ADDR      ((U8*)0x20050000)  // Memory segment 4 start address, 700KB valid (Spare)
#define MEM_SVL_START_ADDR        ((U8*)0x20100000)  // Memory segment 5 start address, 1MB valid (SVL)
//**************************************** Length of memory segments ***************************************************
#define MEM_RSM_SEG_LENGTH         ((U32)0x010000)   // Memory segment 1 length
#define MEM_DRV_SEG_LENGTH         ((U32)0x030000)   // Memory segment 2 length
#define MEM_SYS_SEG_LENGTH         ((U32)0x010000)   // Memory segment 3 length
#define MEM_SPARE_SEG_LENGTH       ((U32)0x0B0000)   // Memory segment 4 length
#define MEM_SVL_SEG_LENGTH         ((U32)0x100000)   // Memory segment 5 length
//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************
// PWM acquisition definition
void (*pvMON_Cycl1ms_GetPWDemod)(void) = KB_NULL_PTR; // @suppress("Wrongly used data type")
//void (*pvMON_Cycl1ms_GetPWDemod)(void) = vIOS_HAL_Cycl1ms_GetPWDemod;


//**************************************** Global constant definitions ( const ) ***************************************

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**********************************************************************************************************************
// Address ranges {32 bit base address, number of bytes} where read of memory via MON is allowed.
//****************************************************************************

// inhibit lint message 9078 caused by address to object pointer conversion needed for memory access

//No. of Segments Limited by macro MAX_NOF_MEMORY_SEGS
const C_MON_MEM_SEGMENT    cMON_Mem_Read_Normal =
{
    MEM_SEG_COUNT, // No. of memory segments
    //      Start Address, Size
    {
        {MEM_RSM_START_ADDR,   MEM_RSM_SEG_LENGTH  },  //lint !e9078
        {MEM_DRV_START_ADDR,   MEM_DRV_SEG_LENGTH  },  //lint !e9078
        {MEM_SYS_START_ADDR,   MEM_SYS_SEG_LENGTH  },  //lint !e9078
        {MEM_SPARE_START_ADDR, MEM_SPARE_SEG_LENGTH},  //lint !e9078
        {MEM_SVL_START_ADDR,   MEM_SVL_SEG_LENGTH  },  //lint !e9078
        {(U8  *)0,0UL},               //free
        {(U8  *)0,0UL},               //free
        {(U8  *)0,0UL},               //free
        {(U8  *)0,0UL},               //free
        {(U8  *)0,0UL},               //free
        {(U8  *)0,0UL},               //free
        {(U8  *)0,0UL},               //free
        {(U8  *)0,0UL},               //free
        {(U8  *)0,0UL},               //free
        {(U8  *)0,0UL},               //free
    }
};                            // NORMAL: READ MEMORY

const C_MON_MEM_SEGMENT    cMON_Mem_Read_Test =
{
    MEM_SEG_COUNT, // No. of memory segments
    {
        //      Start Address, Size
        {MEM_RSM_START_ADDR,   MEM_RSM_SEG_LENGTH  },  //lint !e9078
        {MEM_DRV_START_ADDR,   MEM_DRV_SEG_LENGTH  },  //lint !e9078
        {MEM_SYS_START_ADDR,   MEM_SYS_SEG_LENGTH  },  //lint !e9078
        {MEM_SPARE_START_ADDR, MEM_SPARE_SEG_LENGTH},  //lint !e9078
        {MEM_SVL_START_ADDR,   MEM_SVL_SEG_LENGTH  },  //lint !e9078
        {(U8  *)0,0UL},               //free
        {(U8  *)0,0UL},               //free
        {(U8  *)0,0UL},               //free
        {(U8  *)0,0UL},               //free
        {(U8  *)0,0UL},               //free
        {(U8  *)0,0UL},               //free
        {(U8  *)0,0UL},               //free
        {(U8  *)0,0UL},               //free
        {(U8  *)0,0UL},               //free
        {(U8  *)0,0UL},               //free
    }
};                        // TEST: READ MEMORY


//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *******************************************************************************************************

//** EndOfFile cfg_mon.c ***********************************************************************************************
