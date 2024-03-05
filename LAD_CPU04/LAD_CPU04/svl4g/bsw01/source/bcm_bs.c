//**********************************************************************************************************************
//
//                                              bcm_bdspec.c
//
//**********************************************************************************************************************
//
//                                    Copyrights(c) 2022 by KNORR-BREMSE,
//
//                                       Rail Vehicle Systems, Munich
//
//! @project IBC
//! @date    2023-12-14
//! @author  C. Brancolini
//
//**********************************************************************************************************************
//!
//! @file bcm_bdspec.c
//! @brief BCM - BCM_BDSPEC Implementation
//!
//! Service BCM - Board specific implementation
//!
//**********************************************************************************************************************
//
// History
// Date            Author              Changes
// 2016-11-18      V.Ingulkar          Start
// 2017-04-14      V.Ingulkar          Updated as per new SWIDENT table for CCA
// 2017-06-02      V.Ingulkar          Adapted for BCM_FWR
// 2017-08-16      V.Ingulkar          BC0025-15- Updated to adapt kb_types.h changes
// 2018-01-10      S. Kumbhar          Service OS updated as per Coding guidelines
// 2018-02-09      V.Ingulkar          Updates done to comply code with new coding guidelines and static code analysis
// 2018-05-30      V.Ingulkar          Changes due to common definitions in bcm_common.h
// 2019-01-29      F.Heindl            Added call to s16IbcDebugSetPrintFct()
// 2019-05-06      V.Ingulkar          Updates done as per core asset update v6.0
// 2019-10-18      F.Heindl            Deleted s16IbcDebugSetPrintFct() and corresponding #include
// 2020-02-12      A.Mauro             Lint clean ups
// 2020-11-24      A.Gatare            Adapted for GenCA 6.11
// 2021-04-01      A.Mauro             Added vAPP_ConfigurationPhase() to boBCM_AppConfigurationPhase
// 2021-09-27      N.Jadhav            Genca/GenCA FWK package version information updated.
// 2021-12-17      S.Belsare           Genca/GenCA FWK package version information updated.
// 2022-02-14      S.Belsare           FWK package version information updated.
// 2022-05-20      S.Belsare           Genca/GenCA FWK and FWK package version information updated.
// 2022-11-26      S. Shinde           Adapted for GenCA 7.05
// 2023-01-09      J. Lulli            Coding guidelines alignment
// 2023-03-13      P. Nikam            BC0025-650: Modified STN print in s16BCM_PrintStartMsg()
// 2023-05-29      C. Brancolini       Lint clean up. GENCA_VERSION "V 07.11"
//                                     Added s16LadCfgC_SetUserCfgCheckResult to boBCM_AppConfigurationPhase
// 2023-12-14      C. Brancolini       Lint Plus clean up. Added s16BCM_BS_IrqAtomicInterruptInit().
//
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "bcm_i.h"
#include "bcm_hal.h"
#include "bcm.h"
#include "os_s.h"
#include "bcl_hal_s.h"
#include "FwkCtrlLad.h"
#include "bt.h"
#include "identexesvl.h"                // SVL ident block
#include "os_ca_s.h"                                 // Print messages
#include "ios_board_s.h"
#include "bcm_bs.h"
#include "os_app.h"
#include "LadCfgC.h"
#include "55xxirq.h"
//**************************************** Constant / macro definitions ( #define ) ************************************
//! Generic Code Tag Version
#define GENCA_VERSION_SIZE           13
#define GENCA_VERSION                "V 07.11"
#define FWK_VERSION                  "V05.01.0015"

#define GEN_INV_APP_DATA_OFFSET      (186U)    // Generic inventory - application data offset

#define SIZE_OF_STR_LIMITING_CHAR   1

// offsets of parameters in build date string (YYYY-MM-DD format)
#define DATE_OFFSET_DIG1   8     // Date digit 1
#define DATE_OFFSET_DIG2   9     // Date digit 2
#define MONTH_OFFSET_DIG1  5     // Date digit 1
#define MONTH_OFFSET_DIG2  6     // Date digit 2
#define YEAR_OFFSET_DIG1   0     // Date digit 1
#define YEAR_OFFSET_DIG2   1     // Date digit 2
#define YEAR_OFFSET_DIG3   2     // Date digit 3
#define YEAR_OFFSET_DIG4   3     // Date digit 4

#define GEN_INV_BLD_DATE_SIZE   8    // Size of Software 'Build Date' (DDMMYYYY format)
//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************
//! Generic code Package version
static const U8 au8GenCA_Version[GENCA_VERSION_SIZE] = GENCA_VERSION;
//! Generic fwk code Package version
static const U8 au8FWK_Version[GENCA_VERSION_SIZE] = FWK_VERSION;

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *******************************************************************************************************

//**********************************************************************************************************************
//  Function s16BCM_PrintStartMsg      -
//**********************************************************************************************************************
S16 s16BCM_PrintStartMsg (void)
{
//************************************************ Function scope data *********************************************
    CHAR    achTmp[80];               // Buffer for printing // @suppress("No magic numbers")
    U8      u8Idx;                    // Variable for Loop
    U8      au8OrigVal[4];            // Buffer for CPLD data // @suppress("No magic numbers")
    U8      u8Discard;                // not useful

//*************************************************** Function code ************************************************

    // Print header
    vOS_PrintMsg("\r\r\r**************************************************\r");
    vOS_PrintMsg("*                     CBK                           *\r");
    vOS_PrintMsg("**************************************************\r\r");

    // Print software copyright
    vOS_PrintMsg (cSwIdExe.cSWId.au8Copyright);
    vOS_PrintMsg ("\r");

    // Print software name
    vOS_PrintMsg ("ShortName:   ");
    vOS_PrintMsg (cSwIdExe.cSWId.au8ShortName);
    vOS_PrintMsg ("\r");

    // Print software description
    vOS_PrintMsg ("Description: ");
    vOS_PrintMsg (cSwIdExe.cSWId.au8Description);
    vOS_PrintMsg ("\r");

    // Print software STN
    vOS_PrintMsg ("STN:         ");
    vOS_PrintMsg (cSwIdExe.cSWId.au8STN);
    vOS_PrintMsg ("\r");

    // Print version
    vOS_PrintMsg ("Version:     ");
    vOS_PrintMsg (cSwIdExe.cSWId.au8Version);
    vOS_PrintMsg ("\r");

    // Print build ID1
    vOS_PrintMsg ("Build Date:  ");
    vOS_PrintMsg (cSwIdExe.cSWId.au8Date);
    vOS_PrintMsg ("\r");

    // Print build ID1
    // Inhibit lint message caused by usage of "deprecated" function sprintf (warning 586)
    // function is used just for debug output
    (void)sprintf(achTmp,"Build ID1:   %08lx \r", cSwIdExe.cSWId.u32BuildID1); //lint !e586
    vOS_PrintMsg (achTmp);
    vOS_PrintMsg ("\r");

    // Print package version
    vOS_PrintMsg ("PPC CA/CCA Package Version: ");
    vOS_PrintMsg (au8GenCA_Version);
    vOS_PrintMsg ("\r");

    // Print platform version
    vOS_PrintMsg ("IBC Platform Version: ");
    vOS_PrintMsg (au8FWK_Version);
    vOS_PrintMsg ("\r");


    // get CPLD related information
    for (u8Idx = 0U; u8Idx < 4U; u8Idx++) // @suppress("No magic numbers")
    {
        // get the old value
        (void) s16BCL_HAL_CPLD_RawWrite(u8Idx, (U8) 0, &au8OrigVal[u8Idx]);
        // write the old value back to cpld
        (void) s16BCL_HAL_CPLD_RawWrite(u8Idx, au8OrigVal[u8Idx], &u8Discard);
    }
    // Inhibit lint message caused by usage of "deprecated" function sprintf (warning 586)
    // function is used just for debug output
    // Inhibit lint message 705 related to sprintf arguments 3,4,5,6
    //lint -save -e586 -e705
    (void) sprintf( achTmp,
        "BCL_HAL - CPLD registers : %02x %02x %02x %02x\r",
        au8OrigVal[0],
        au8OrigVal[1], // @suppress("No magic numbers")
        au8OrigVal[2], // @suppress("No magic numbers")
        au8OrigVal[3]); // @suppress("No magic numbers")
    //lint -restore

    // Print CPLD related information
    vOS_PrintMsg(achTmp);

    // Return success
    return (KB_RET_OK);
}
//** EndOfFunction s16BCM_PrintStartMsg ********************************************************************************

// Function s16BT_Init
//**********************************************************************************************************************
S16 s16BT_Init (void)
{
//************************************************ Function scope data *********************************************
    S16 s16Return =  KB_RET_ERR_INTERNAL;  // Function return variable, initialized at internal error
    BOOLEAN boReturn;                      // Intermediate result variable

//*************************************************** Function code ************************************************

    // Initialize BTP
    boReturn = boBTInit();

    // Check BTP initialization result
    if (boReturn == (BOOLEAN)TRUE )
    {
        // No error occurred, return OK
        s16Return = KB_RET_OK;
    }

    // Return result
    return (s16Return);
}
//** EndOfFunction s16BT_Init ******************************************************************************************

// Function boBCM_AppConfigurationPhase
//**********************************************************************************************************************
BOOLEAN boBCM_AppConfigurationPhase (U16 u16BCMStartupCode)
{
//************************************************ Function scope data *********************************************
    CHAR    achTmp[80];               // Buffer for printing // @suppress("No magic numbers")
    BOOLEAN boReturn;                 // Function return variable
    S16 s16ReturnValue;               // Intermediate result variable

//*************************************************** Function code ************************************************

    // Load configuration from flash and verify
    boReturn = boAPP_ConfigurationPhase(u16BCMStartupCode);

    if ( boReturn == (BOOLEAN)TRUE )
    {
        // Configuration successfully loaded
        // Check configuration
        s16ReturnValue = s16LadCfgC_SetUserCfgCheckResult(LADCFGC_USER_APP, LADCFGC_APP_CONFIG_OK);
        if ( s16ReturnValue != KB_RET_OK )
        {
            // check failed, print message on UART and return false
            // Inhibit lint message caused by usage of "deprecated" function sprintf (warning 586)
            // function is used just for debug output
            (void)sprintf(achTmp,"s16LadCfgC_SetUserCfgCheckResult Failed:   %d \r", s16ReturnValue); //lint !e586
            vOS_PrintMsg (achTmp);
            boReturn = FALSE;
        }
    }

    // Run application configuration phase (load the configuration from flash IO Service config)
    vIOS_AppConfigurationPhase();

    if (boReturn == (BOOLEAN)TRUE)
    {
        // No error occurred
        // Finish diagnostic initialization process
        (void) s16FwkCtrlLad_DiagInitFinish();
    }

    // Return result
    return (boReturn);
}
//** EndOfFunction boBCM_AppConfigurationPhase *************************************************************************

// Function s16IBC_Startup
//**********************************************************************************************************************
S16 s16IBC_Startup (void)
{
//************************************************ Function scope data *********************************************
    S16 s16Return = KB_RET_OK;    // Function return variable, initialized at OK

//*************************************************** Function code ************************************************

    // Initialization of APP

    //Create Start up event
    (void) s16FwkCtrlLad_InitFinish();

    // Return result
    return (s16Return);
}
//** EndOfFunction s16IBC_Startup **************************************************************************************

// Function s16ESRA_IDLEStartup
//**********************************************************************************************************************
S16 s16ESRA_IDLEStartup (void)
{
//************************************************ Function scope data *********************************************
    S16 s16Return = KB_RET_OK;    // Function return variable, initialized at OK

//*************************************************** Function code ************************************************

    // Start ESRA IDLE process, if available
    if (u32OS_Pid_SVL_IDLE != OS_PIDINIT)
    {
        (void) s16OS_ProcStart(u32OS_Pid_SVL_IDLE);
    }

    // Return result
    return (s16Return);
}
//** EndOfFunction s16ESRA_IDLEStartup *********************************************************************************

// Function s16BCM_BS_GenInvGetSWAppData
//**********************************************************************************************************************
S16 s16BCM_BS_GenInvGetSWAppData (U8* pu8DataOut, U8 u8PageNum, U16 u16MaxRespLen, U16* pu16RspLen, S16 s16ErrStatus)
{
//************************************************ Function scope data *************************************************
    U32                         u32AppVers = 0;
    S16                         s16Return;
    U16                         u16OFFSET = GEN_INV_APP_DATA_OFFSET;    // Offset for SW Application data
    U8                          u8Index = 0;
    C_BCM_COMMON_SWINF_NAME     cShortName={""};
    C_BCM_COMMON_SWINF_BLD_DATE cBldDate= {{0}};
    C_BCM_COMMON_SWINF_STN      cAppStn= {{0}};
    U8                          au8BldDateReqFormat[GEN_INV_BLD_DATE_SIZE];
//************************* Static data declaration **************************

//*************************************************** Function code ****************************************************
    (void)u16MaxRespLen; // Parameter is unused
    (void)pu16RspLen;    //lint !e920 Parameter is unused

    if (u8PageNum == 0U)   // As Software application data is present on Page 0
    {
        if (s16ErrStatus == KB_RET_OK)  // Perform following operation if calling function status is KB_RET_OK
        {
            // u16OFFSET is decided by referring to the document "PSQ3403_SysIFS_eLAD25_Inventory_Data.xlsm"
            // Software application data is present in Page 0-SW Module 1
            // In the above document, index for SW app. is 188. But as we do not fill first 2 bytes (Cmnd ID, Resp)
            // we have used u16OFFSET = 186 (188 - 2) to fill SW appln data

            pu8DataOut[u16OFFSET] = 0;  // Here '0' signifies 'eSW_APPLICATION'
            u16OFFSET++;

            s16Return = s16BCM_SwInfGetAppShortNameStr(&cShortName);  // Get 'short name'

            if (s16Return == KB_RET_OK)
            {
                // As return value is not relevant, suppressing relative Lint warning
                memcpy((void*) &pu8DataOut[u16OFFSET],
                       (void*) (cShortName.au8ShortName),
                               (SW_ID_SHORTNAME_SIZE - SIZE_OF_STR_LIMITING_CHAR)); //lint !e534
                // We are copying 'SW_ID_SHORTNAME_SIZE-1' characters as we don't need '\0' (last character)

                u16OFFSET = u16OFFSET + (U16)(SW_ID_SHORTNAME_SIZE - SIZE_OF_STR_LIMITING_CHAR); // Update offset

                s16Return = s16BCM_SwInfGetAppStnStr(&cAppStn); // get STN (Part No) string
            }

            if (s16Return == KB_RET_OK)
            {
                // As return value is not relevant, suppressing relative Lint warning
                memcpy((void*)&pu8DataOut[u16OFFSET], (void*)(cAppStn.au8STN), SW_ID_STN_SIZE); //lint !e534

                u16OFFSET = u16OFFSET + (U16)SW_ID_STN_SIZE; // Update offset

                s16Return = s16BCM_SwInfGetAppVers(&u32AppVers); // Get app version
            }

            if (s16Return == KB_RET_OK)
            {
                // Swap data to convert to Big Endian if required
                #if (LOCAL_ENDIANESS == LITTLE_ENDIAN)
                    u32AppVers = BCM_SWAP_W(u32AppVers);
                #endif

                // Update application version
                // As return value is not relevant, suppressing relative Lint warning
                memcpy((void*)&pu8DataOut[u16OFFSET], (void*)(&u32AppVers),  sizeof(U32));  //lint !e534

                u16OFFSET = u16OFFSET + (U16)(sizeof(U32)); // Update offset

                s16Return = s16BCM_SwInfGetAppBldDateStr(&cBldDate);
            }

            if (s16Return == KB_RET_OK)
            {
                // converting build date from YYYY-MM-DD to DDMMYYYY format

                //Copy Date
                au8BldDateReqFormat[u8Index] = cBldDate.au8Date[DATE_OFFSET_DIG1];
                u8Index++;
                au8BldDateReqFormat[u8Index] = cBldDate.au8Date[DATE_OFFSET_DIG2];
                u8Index++;

                //Copy Month
                au8BldDateReqFormat[u8Index] = cBldDate.au8Date[MONTH_OFFSET_DIG1];
                u8Index++;
                au8BldDateReqFormat[u8Index] = cBldDate.au8Date[MONTH_OFFSET_DIG2];
                u8Index++;

                //Copy Year
                au8BldDateReqFormat[u8Index] = cBldDate.au8Date[YEAR_OFFSET_DIG1];
                u8Index++;
                au8BldDateReqFormat[u8Index] = cBldDate.au8Date[YEAR_OFFSET_DIG2];
                u8Index++;
                au8BldDateReqFormat[u8Index] = cBldDate.au8Date[YEAR_OFFSET_DIG3];
                u8Index++;
                au8BldDateReqFormat[u8Index] = cBldDate.au8Date[YEAR_OFFSET_DIG4];


                // copy build version (DDMMYYYY format)
                // As return value is not relevant, suppressing relative Lint warning
                memcpy((void*)&pu8DataOut[u16OFFSET], (void*)(au8BldDateReqFormat),  GEN_INV_BLD_DATE_SIZE); //lint !e534


            }
        }
        else
        {
            s16Return = s16ErrStatus;   // Return the same error status
        }
    }
    else
    {
        s16Return = s16ErrStatus;   // Return the same error status
    }


    // Return result
    return ( s16Return );
}
//** EndOfFunction s16BCM_BS_GenInvGetSWAppData *************************************************************************


// Function s16BCM_BS_IrqAtomicInterruptInit
//**********************************************************************************************************************
extern S16 s16BCM_BS_IrqAtomicInterruptInit (void)
{
//************************************************ Function scope data *********************************************
    S16 s16Return;     // Function return variable

//*************************************************** Function code ************************************************
    // Install atomic interrupt service routine
    s16Return = (S16)s32IrqAtomicInterruptInit();

    return ( s16Return );
}
//** EndOfFunction s16BCM_BS_IrqAtomicInterruptInit  *************************************************************************




//** EndOfFile bcm_bdspec.c ********************************************************************************************

