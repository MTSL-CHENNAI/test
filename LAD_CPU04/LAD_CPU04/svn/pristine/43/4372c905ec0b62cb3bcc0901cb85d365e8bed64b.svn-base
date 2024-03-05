//**********************************************************************************************************************
//
//                                          mon_sdi_fin.c
//
//**********************************************************************************************************************
//
//                                    Copyrights(c) 2022 by KNORR-BREMSE,
//                                       Rail Vehicle Systems, Munich
//
//! @project IBC
//! @date    2023-12-05
//! @author  C. Brancolini
//
//**********************************************************************************************************************
//!
//! @file
//! @brief  Service Monitor for project ESRA
//!         Module contains function to access freq-in driver
//!
//**********************************************************************************************************************
//
// History
// Date            Author              Changes
// 23.02.96        S. Widder           1.00 / Start, based on sources from
//                                     D. Dunkel and W. Bartel (Fa. MICRONOVA)
// 05.03.96 D.        Dunkel           1.01 / second read of frequency input added
//                                            frequence input: 2 byte
// 05.03.96        T. Moser            1.02 / delay between open and 1. read inserted
// 05.03.96        S. Widder           1.1  / reading FIN several times
// 25.03.96        S. Widder           1.2  / Corrected filenames for include files
// 27.03.96        S. Widder           1.21 / Modified calculation of frequency in Hz
//                                            because of rounding (?)
// 25.04.96        S. Widder           1.22 / added '#pragma codeseg' for banking
//                                            added declaration of non-banked functions
// 15.05.96        S. Widder           1.23 / CR39: Removed pathes in file include
// 30.07.96        S. Widder           1.24 / Increased number of loops for reading
//                                            F-IN; shortened time between successive
//                                            reads
// 21.03.11        C. Baeuml           1.25 / Porting to MPC55xx.
// 06.06.13        H. Shaikh           1.26 / Generalization of Command
// 27.05.14        H. Shaikh           1.27 / BC_002-814 : Command length verification
//                                          / BC_002-821 : Max Freq i/p channels verification
//                                          / Lint: Code cleanup
// 17.03.15        H. Shaikh           1.28 / TC0047-39: Freq. IP channel no. verification
// 27.08.15        P. Munoli           1.29 / Removed compilation warning
// 15.09.15        A. Mauro            1.30 / Changed MON_CHANNEL_ERROR to MON_RANGE_ERROR
//                                            to the function s16MONReadFreq
// 17.02.16        A. Mauro            1.31 / Jira issue TC_007-84 solved
// 30.06.16        A. Mauro            1.32 / Jira issue TC_005-62 solved
// 2023.04.17      A. Mauro            1.33 / TC_007-96: LINT clean up
// 2023.09.14      A. Mauro            1.34   Alignment with CA: name changed and other
// 2023-12-05      C. Brancolini       Lint Plus clean up
//
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include <string.h>                   // Include memcpy
#include "mon_cpu04_genrl_sdi_i.h"    // MON CPU04 SDI command handler
#include "mon_fin.h"                  // MON frequency IO definitions
#include "os.h"
#include "mon_cpu04.h"                // MON CPU04 definitions
#include "mon.h"                      // MON SDI definitions
#include "bcl_s.h"                    // General BCL service definitions
#include "sdi.h"                      // Error Codes
#include "bcm_strt.h"                 // BCL system interface

//**************************************** Constant / macro definitions ( #define ) ************************************

#define DELAY_READ_FIN       ((U32)20)  //! delay for successive reads
                                        //! of frequency inputs: 50 ms
#define NUM_OF_FIN_LOOPS       ((U8)3)  //! Number of loops reading FIN
#define MON_FREQIN_PARA_LEN    ((U8)1)  //!no of parameter for each freq input


#define MON_REPLY_UPDATED_FLAG_LEN     ((U8)1)
#define MON_REPLY_MEASURE_FREQ_LEN     ((U8)2)
#define MON_REPLY_FI_DATA_LEN          (MON_REPLY_UPDATED_FLAG_LEN + MON_REPLY_MEASURE_FREQ_LEN)

#define FREQ_OFFSET 50U
#define FREQ_FACTOR 100U

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *******************************************************************************************************

//**********************************************************************************************************************
//
// Function s16MON_ReadFreq
//**********************************************************************************************************************
s16SDI_CMD(s16MON_ReadFreq)
{
    //************************************************ Function scope data *********************************************
    U32 u32StartTime;                     // start time for generate delay
    U32 u32CurrentTime;                   // start time for generate delay
    U8  u8Cnt;                            // counting variable
    U8  u8RequestedFIs;                   // number of the frequency inputs to be read
    U8  u8LoopCnt;                        // Number of loops to read freq
    U8 u8SDIRespIndex = MON_SDI_INDEX_1;  // SDI response index
    U8 u8SDICmdIndex = MON_SDI_INDEX_1;   // SDI command index
    U16 u16TempFreq ;                     // variable to hold the freq value
    C_FIN_MEASUREMENT_DATA cFIN_DATA;       // struct for frequency inputs
    C_MON_IO_BUFF cMonIoBuff;             // buffer for temp storage of io input u8/u16/u32
    E_BCM_BOARD_STATE   eBoardState;      // Board state
    S16 s16RetVal;                        // Function return value

    //*************************************** Function scope static data declaration ***********************************

    //*************************************************** Function code ************************************************

    (void)u16MaxRespOut; // unused parameter

    // Get Board State
    eBoardState = eBCM_StrtGetBoardState();

    // Check Board State
    if (eBoardState != eBCM_BS_TEST)   //eBoardState is not eBCM_BS_TEST
    {
        // If board is not in Test Mode, command will not be processed.

        // Build reply message "invalid command"
        u8SDIRespIndex = MON_SDI_INDEX_1;
        pu8DataOut[u8SDIRespIndex] = MON_SDI_INVALID_COMMAND;
        u8SDIRespIndex++;

        // Return response length
        return (S16)u8SDIRespIndex;
    }

    // Board is in Test Mode State
    // Build reply message ***************************************************************************

    // Get the number of the frequency inputs to be read
    u8RequestedFIs = pu8DataIn[u8SDICmdIndex];

    // Check reading range
    if ( u8RequestedFIs > u8MON_MaxFreqChnls )  // Frequency channels more than actual
    {
        // Replay with RANGE_ERROR
        pu8DataOut[u8SDIRespIndex] = MON_SDI_CHANNEL_ERROR;
        u8SDIRespIndex++;
        return (S16)u8SDIRespIndex;                         // too big - ack with RANGE_ERROR
    }
    //TC0047-39 -Freq channel no. verification
    //TC_005-62 -From <= to <
    for (u8Cnt = 0; u8Cnt < u8RequestedFIs; u8Cnt++)
    {

        if ((pu8DataIn[(u8SDICmdIndex + u8Cnt + MON_FREQIN_PARA_LEN)] >= u8MON_MaxFreqChnls))       //Freq chan no. more than actual
        { // check reading range
            pu8DataOut[u8SDIRespIndex] = MON_SDI_CHANNEL_ERROR;
            u8SDIRespIndex++;
            return (S16)u8SDIRespIndex;                         // too big - ack with RANGE_ERROR
        }
    }

    //Check command length
    if (u16CmdLenIn != (((U16)u8RequestedFIs * MON_FREQIN_PARA_LEN) + MON_SDI_PAR_OFFSET))
    {
        //Command length invalid
        pu8DataOut[u8SDIRespIndex] = MON_SDI_INVALID_COMMAND;
        u8SDIRespIndex++;
    }
    else
    {
        u8SDICmdIndex++; // point to freq. channel no.
        for (u8Cnt = 0; u8Cnt < u8RequestedFIs; u8Cnt++)
        { // init frequency channels first
            if (boMON_InitFINCaptChannel((E_FIN_CHNL_NUM) pu8DataIn[u8SDICmdIndex + u8Cnt]) == (BOOLEAN)FALSE)
            {
                pu8DataOut[u8SDIRespIndex] = MON_SDI_CHANNEL_ERROR;
                u8SDIRespIndex++;
                return (S16)u8SDIRespIndex;                       // error occurred during channel
                                                                // initialization - no further read
            }
        }

        // Deactivate PWM acquisition if present (TC_007-84)
        if ( pvMON_Cycl1ms_GetPWDemod != KB_NULL_PTR )
        {
            // Inhibit lint error warning 466 and note 9074 due to a missing void in boOS_DeActivateFct declaration
            //lint -save -e466 -e9074
            // Stop PWM cycle readings
            (void)boOS_DeActivateFct(pvMON_Cycl1ms_GetPWDemod,(U8)eOS_SLICE_1MS);
            //lint -restore
        }

        u8LoopCnt = NUM_OF_FIN_LOOPS;
        do
        {
            for (u8Cnt = 0; u8Cnt < u8RequestedFIs; u8Cnt++) // read frequency ports
            {
                (void) boMON_GetFINCaptData((E_FIN_CHNL_NUM) pu8DataIn[u8SDICmdIndex + u8Cnt], &cFIN_DATA);

                cMonIoBuff.acMonFreqBuff[u8Cnt].u16Frequency =
                    (U16)((cFIN_DATA.u32Frequency + FREQ_OFFSET) / FREQ_FACTOR);
                //Conversion to Frequency Value
                cMonIoBuff.acMonFreqBuff[u8Cnt].boFreqUpToDate = cFIN_DATA.boFreqUpToDate;
                // put read bytes into buffer
            }
            u8LoopCnt--;
            if (u8LoopCnt != 0U)
            {
                (void) s16OS_GetTimeMS(&u32StartTime);
                (void) s16OS_GetTimeMS(&u32CurrentTime);

                while ((u32CurrentTime - u32StartTime) < DELAY_READ_FIN)
                {
                    (void) s16OS_GetTimeMS(&u32CurrentTime);
                }
                // delay before reading the second and third time
            }
        } while (u8LoopCnt != 0U);

        for (u8Cnt = 0; u8Cnt < u8RequestedFIs; u8Cnt++) // put read bytes into ack message
        {
            *(pu8DataOut + MON_ACK + (u8Cnt * MON_REPLY_FI_DATA_LEN)) = cMonIoBuff.acMonFreqBuff[u8Cnt].boFreqUpToDate;
            u16TempFreq = cMonIoBuff.acMonFreqBuff[u8Cnt].u16Frequency >> MON_SHIFT_VAR_BY_8;
                                              // used to avoid compiler warning
            u16TempFreq |= cMonIoBuff.acMonFreqBuff[u8Cnt].u16Frequency << MON_SHIFT_VAR_BY_8;
                                              // used to avoid compiler warning
            memcpy((void *)(pu8DataOut + MON_ACK + MON_REPLY_UPDATED_FLAG_LEN + (u8Cnt * MON_REPLY_FI_DATA_LEN)),
                    (const void *)&u16TempFreq, MON_REPLY_MEASURE_FREQ_LEN);
        }
        pu8DataOut[u8SDIRespIndex] = MON_SDI_NO_ERROR; // request is done properly
        u8SDIRespIndex++;
        pu8DataOut[u8SDIRespIndex] = u8RequestedFIs;      // ack with NO_ERROR

        u8SDIRespIndex = MON_ACK + (U8)(u8RequestedFIs * MON_REPLY_FI_DATA_LEN);
    }
    // Re-activate PWM acquisition if present (TC_007-84)
    if ( pvMON_Cycl1ms_GetPWDemod != KB_NULL_PTR )
    {
        // Restart PWM cycle readings
        // Inhibit lint warning 466 and note 9074 due to a missing void in boOS_ActivateFct declaration
        //lint -save -e466 -e9074
        (void)boOS_ActivateFct(pvMON_Cycl1ms_GetPWDemod,(U8)eOS_SLICE_1MS);
        //lint -restore
    }



    // Return response length
    s16RetVal = (S16) u8SDIRespIndex;

    return (s16RetVal);
}
//  EndOfFunction s16MON_ReadFreq **************************************************************************************

//  EndOfFile mon_sdi_fin.c ********************************************************************************************
