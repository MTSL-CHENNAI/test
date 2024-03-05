//**********************************************************************************************************************
//
//                                           mon_sdi_fout.c
//
//**********************************************************************************************************************
//
//                                    Copyrights(c) 2022 by KNORR-BREMSE,
//                                       Rail Vehicle Systems, Munich
//
//! @project IBC
//! @date    2023-12-06
//! @author  C. Brancolini
//
//**********************************************************************************************************************
//!
//! @file
//! @brief  Service Monitor for project ESRA
//!         Module contains function to access freq-out driver
//**********************************************************************************************************************
//
// History
// Date            Author              Changes
// 23.02.96        S. Widder           1.00 / Start, based on sources from
//                                           D. Dunkel and W. Bartel (Fa. MICRONOVA)
// 04.03.96        T. Moser            1.1  / Inserted counter 'bMaxCnt' for number
//                                           of channels
// 25.03.96        S. Widder           1.2  / Corrected filenames for include files
// 25.04.96        S. Widder           1.21 / added '#pragma codeseg' for banking
//                                           added declaration of non-banked functions
// 15.05.96        S. Widder           1.22 / CR39: Removed pathes in file include
// 21.03.11        C. Baeuml           1.23 / Porting to MPC55xx.
// 06.06.13        H. Shaikh           1.24 / Generalization of Command
// 28.05.14        H. Shaikh           1.25 / BC_002-814 : Command length verification
//                                          / Lint: Code cleanup
// 2023.04.17      A. Mauro            1.26 / TC_007-96: LINT clean up
// 2023.09.14      A. Mauro            1.27   Alignment with CA: name changed and other
// 2023-12-06      C. Brancolini       Lint Plus clean up
//
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************

#include "mon_cpu04_genrl_sdi_i.h"    // MON CPU04 SDI command handler
#include "mon_fout.h"                 // MON frequency putputs definitions
#include "mon_cpu04.h"                // MON CPU04 definitions
#include "mon.h"                      // MON SDI definitions
#include "bcl_s.h"                    // General BCL service definitions
#include "sdi.h"                      // Error Codes
#include "bcm_strt.h"                 // BCL system interface

//**************************************** Constant / macro definitions ( #define ) ************************************
#define MON_PARA_FREQOUT_LEN   (U8) 3      // number of parameter for freq output
#define MON_EB_FREQOUT_CHNLS   (U8) 2      // number of freq output channels

#define MON_FREQOUT_NUM   (U8) 0  // internal offset of port number inside parm group in the SDI command write FO
#define MON_FREQOUT_LOW   (U8) 1  // internal offset of low byte freq. value inside parm group in the SDI command write FO
#define MON_FREQOUT_HI    (U8) 2  // internal offset of hi byte freq. value inside parm group in the SDI command write FO


//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *******************************************************************************************************

//**********************************************************************************************************************
//
// Function s16MON_WriteFreq
//
//**********************************************************************************************************************
s16SDI_CMD(s16MON_WriteFreq)
{
    //************************************************ Function scope data *********************************************
    U8 u8Cnt;                             // counting variable
    U8 u8ReqPortsCnt;                     // var to store number of bytes to read
    U8 u8SDIRespIndex = MON_SDI_INDEX_1;  // SDI command indexes
    U8 u8SDICmdIndex = MON_SDI_INDEX_1;   // SDI command index
    E_BCM_BOARD_STATE eBoardState;        // Board state
    S16 s16RetVal;                        // Function return value
    U16 u16FreqOut = 0;                   // Frequency value
    U8* pu8Tmp;                           // Temp pointer

    //*************************************** Function scope static data declaration ***********************************

    //*************************************************** Function code ************************************************
    (void)u16MaxRespOut; // unused parameter

    // Check Board State:
    eBoardState = eBCM_StrtGetBoardState();

    // Build reply message:
    if (eBoardState == eBCM_BS_TEST)
    {
        // get number of ports to read
        u8ReqPortsCnt = pu8DataIn[u8SDICmdIndex];

        // check writing range
        if ( u8ReqPortsCnt > MON_EB_FREQOUT_CHNLS )
        {
            // too big - reply with RANGE_ERROR
            pu8DataOut[u8SDIRespIndex] = MON_SDI_RANGE_ERROR;
            u8SDIRespIndex++;
            return ((S16)u8SDIRespIndex);
        }
        
        // Setup ptr to channel nr
        pu8Tmp = pu8DataIn + MON_SDI_PAR_OFFSET;

        // check command length
        if (u16CmdLenIn != ( ((U16)u8ReqPortsCnt * MON_PARA_FREQOUT_LEN) + MON_SDI_PAR_OFFSET) )
        {
            // Command length invalid
            pu8DataOut[u8SDIRespIndex] = MON_SDI_INVALID_COMMAND;
            u8SDIRespIndex++;
        }
        else
        {
            for (u8Cnt = 0; u8Cnt < u8ReqPortsCnt; u8Cnt++)
            {
                // Get frequency value
                u16FreqOut = (U16)pu8Tmp[MON_FREQOUT_LOW];                        // Get frequency value - Low Byte
                u16FreqOut |= (U16)pu8Tmp[MON_FREQOUT_HI] << MON_SHIFT_VAR_BY_8;  // Get frequency value - High Byte

                // write freq. output
                if (boMON_InitFreqOut((E_FREQ_OUT_CHNL_NUM) pu8Tmp[MON_FREQOUT_NUM], u16FreqOut) == (BOOLEAN)FALSE)
                {
                    // error occurred during channel initialization
                    // reply channel error
                    pu8DataOut[u8SDIRespIndex] = MON_SDI_CHANNEL_ERROR;
                    u8SDIRespIndex++;
                    return ((S16)u8SDIRespIndex);
                }
                // Ptr to next target value
                pu8Tmp = pu8Tmp + MON_PARA_FREQOUT_LEN;
            }

            // no error so far, reply no error
            pu8DataOut[u8SDIRespIndex] = MON_SDI_NO_ERROR;
            u8SDIRespIndex++;
        }
    }
    else
    {
        // Board not in test mode
        // reply with invalid command
        u8SDIRespIndex = MON_SDI_INDEX_1;
        pu8DataOut[u8SDIRespIndex] = MON_SDI_INVALID_COMMAND;
        u8SDIRespIndex++;
    }

    s16RetVal = (S16) u8SDIRespIndex;

    return (s16RetVal);
}
//  EndOfFunction s16MON_WriteFreq *************************************************************************************

//  EndOfFile mon_sdi_fout.c *******************************************************************************************
