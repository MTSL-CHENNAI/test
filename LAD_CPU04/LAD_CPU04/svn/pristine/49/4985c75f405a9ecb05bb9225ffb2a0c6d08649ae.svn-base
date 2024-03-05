//**********************************************************************************************************************
//
//                                              ios_cpu04.c
//
//**********************************************************************************************************************
//
//                                       Copyrights(c) by KNORR-BREMSE,
//
//                                       Rail Vehicle Systems, Munich
//
//! @project  IBC
//! @date     2023-11-30
//! @author   C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file ios_bs.c
//! @brief IOS - IOS_BS Implementation
//!
//! Service IOS - Board specific implementation
//!
//**********************************************************************************************************************
//
// History
// Date            Author              Changes
// 2021-07-06      A.Mauro             Start
// 2022-11-26      S.Shinde            Adapted for GenCA 7.05
// 2023-01-09      J. Lulli            Coding guidelines alignment
// 2023-05-29      C. Brancolini       Lint clean up
//                                     Moved s16LadCfgC_SetAppConfigCheck to boBCM_AppConfigurationPhase
// 2023-11-30      C. Brancolini       Lint Plus clean up
//
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "ios_board_s.h"
#include "LadCfgC.h"
#include "ct_ios_channel.h"             // Tools for using CDO_IOS_CHANNEL
#include "c_ios_channel.h"

//**************************************** Constant / macro definitions ( #define ) ************************************
//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *******************************************************************************************************


// Function vIOS_AppConfigurationPhase
//**********************************************************************************************************************
void vIOS_AppConfigurationPhase (void)
{
//************************************************ Function scope data *********************************************

    static S16 s16RetVal;
    static CDO_IOS_CHANNEL_TABLE(TEST) cIoConfig; // @suppress("Wrong derived data type")
    static CDO_IOS_CHANNEL_TABLE(TEST)*  pcIoConfig = &cIoConfig; // @suppress("Wrong derived data type")
    static CDO_IOS_CHANNEL_TABLE(TEST)** const ppcIoConfig = &pcIoConfig; // @suppress("Wrong derived data type")

//*************************************************** Function code ************************************************
    //Load the configuration from flash IO Service config
    // Inhibit lint message (note 9087) cast between pointer of different types
    s16RetVal = s16LadCfgC_GetParsedUserStruct(LADCFGC_USER_BSW_IOSERVICE, (U32**)ppcIoConfig); //lint !e9087
    if (KB_RET_NO_ERROR(s16RetVal)==(BOOLEAN)TRUE)
    {
        // Get dynamic IOS configuration
        (void)SET_DYNAMIC_REF_CDO_IOS_CHANNEL_TABLE(*ppcIoConfig);
    }

}
//** EndOfFunction vIOS_AppConfigurationPhase *************************************************************************

//** EndOfFile ios_cpu04.c ********************************************************************************************
