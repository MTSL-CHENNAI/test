//**********************************************************************************************************************
//
//                                           mon_sdi_psdio.c
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
//!         Module contains functions to access i/o-ports in binary mode
//!
//**********************************************************************************************************************
//
// History
// Date            Author              Changes
// 23.02.96        S. Widder           1.00 / Start, based on sources for BINIO
// 25.04.96        S. Widder           1.01 / added '#pragma codeseg' for banking
//                                            added declaration of non-banked functions
// 15.05.96        S. Widder           1.10 / CR39: Removed pathes in file include
// 13.06.96        S. Widder           1.11 / Changed names for E_INPUT/E_OUTPUT to
//                                            E_PSD_INPUT/E_PSD_OUTPUT
// 18.03.11        C. Baeuml           1.20 / Porting to MPC55xx.
// 12.05.11        C. Baeuml           1.21 / New function ReadPSDIO().
// 06.06.13        H. Shaikh           1.22 / Generalization of Command
// 23.05.14        H. Shaikh           1.23 / BC_002-814: Command length verification add
// 27.08.15        P. Munoli           1.29 / Removed compilation warning
// 15.09.15        A. Mauro            1.30 / Bug fix: u16State.u16Data = u16TempData
//                                            reassignment missing into s16MONReadPSDIO
// 14.09.16        A. Mauro            1.31 / TC_005-66: updated s16MONReadPSDIO
// 20.04.17        A. Mauro            1.33 / TC_007-96: LINT clean up
// 2023.09.14      A. Mauro            1.34   Alignment with CA: name changed and other
// 2023-12-06      C. Brancolini       Lint Plus clean up
//
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "mon_cpu04_genrl_sdi_i.h"    // MON CPU04 SDI command handler
#include "mon_psdio.h"                // MON PSDIO definitions
#include "mon_cpu04.h"                // MON CPU04 definitions
#include "mon.h"                      // MON SDI definitions
#include "bcl_s.h"                    // General BCL service definitions
#include "sdi.h"                      // Error Codes
#include "bcm_strt.h"                 // BCL system interface

//**************************************** Constant / macro definitions ( #define ) ************************************
#define DUMMY_OUT_VAL (U16)    0x0        // Dummy val for init psd io
//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *******************************************************************************************************

//**********************************************************************************************************************
//
// Function s16MON_ReadPSDIO
//
//**********************************************************************************************************************
s16SDI_CMD(s16MON_ReadPSDIO)
{
//************************************************ Function scope data *************************************************

    U8 u8SDIIndex = MON_SDI_INDEX_1;                    // SDI command indexes
    U16 u16Mask;
    C_WORD_BYTE cState;
    E_BCM_BOARD_STATE   eBoardState;      // Board state
    S16 s16RetVal;                        // Function return value
    U16 u16TempData;

//*************************************************** Function code ****************************************************
    (void)u16MaxRespOut; // unused parameter

    // Check Board State:
    eBoardState = eBCM_StrtGetBoardState();

    // Build reply message:
    if (eBoardState == eBCM_BS_TEST)
    {
        cState.u16Data = 0;
        if (u16CmdLenIn != (U16) MON_SDI_READ_PSDIO_LEN)
        { //Command length invalid
            pu8DataOut[u8SDIIndex] = MON_SDI_INVALID_COMMAND;
            u8SDIIndex++;
        }
        else
        {
        //lint -e725
            // Get mask value
            u16Mask = (U16)(*(pu8DataIn + MON_SDI_INDEX_1));
                                              // Get value Low Byte
            u16Mask |= (U16)(*(pu8DataIn + MON_SDI_INDEX_2)) << MON_SHIFT_VAR_BY_8;
                                              // Get value High Byte

            // Mask for reading
            u16TempData = cState.u16Data; // used to avoid compiler warning
            if ( boMON_InitPSDIOChannels(u16Mask, ePSD_INPUT, DUMMY_OUT_VAL) == (BOOLEAN)FALSE )
            {
                pu8DataOut[u8SDIIndex] = MON_SDI_CHANNEL_ERROR;
                u8SDIIndex++;
                return ((S16)u8SDIIndex); // an error occurred on init
            }
            if ( boMON_GetPSDIOChannels(&u16Mask, &u16TempData) == (BOOLEAN)FALSE )
            {
                pu8DataOut[u8SDIIndex] = MON_SDI_CHANNEL_ERROR;
                u8SDIIndex++;
                return ((S16)u8SDIIndex); // an error occurred on init
            }
            cState.u16Data = u16TempData; // used to avoid compiler warning
//lint -e725
            cState.u16Data = (U16)(cState.u16Data & u16Mask); // Get relevant bits
            pu8DataOut[u8SDIIndex] = MON_SDI_NO_ERROR; // request is done properly,
// ack with NO_ERROR
            u8SDIIndex++;
            // TC_005-66: inverted returned values
            pu8DataOut[u8SDIIndex] = cState.au8Data[1]; // @suppress("No magic numbers")
            u8SDIIndex++;
            pu8DataOut[u8SDIIndex] = cState.au8Data[0]; // put result in ack msg
            u8SDIIndex++;
        }
    }
    else
    {
        u8SDIIndex = MON_SDI_INDEX_1;
        pu8DataOut[u8SDIIndex] = MON_SDI_INVALID_COMMAND;
        u8SDIIndex++;
    }
    s16RetVal = (S16) u8SDIIndex;

//lint -e818
    return (s16RetVal); // return reply len
}
//  EndOfFunction s16MON_ReadPSDIO *************************************************************************************

//**********************************************************************************************************************
//
// Function s16MON_WritePSDIO
//
//**********************************************************************************************************************
s16SDI_CMD(s16MON_WritePSDIO)
{
    //lint -e818
//************************************************ Function scope data *************************************************
    U8 u8SDIRespIndex = MON_SDI_INDEX_1;  // SDI response index
    U8 u8SDICmdIndex;                     // SDI command index
    U16 u16Mask;                          // Mask and state for reading psd
    U16 u16Val;                           // psd value
    E_BCM_BOARD_STATE   eBoardState;      // Board state
    S16 s16RetVal;                        // Function return value

//*************************************************** Function code ****************************************************
    (void)u16MaxRespOut; // unused parameter

    // Check Board State:
    eBoardState = eBCM_StrtGetBoardState();

    // Build reply message:
    if (eBoardState == eBCM_BS_TEST)
    {
        if (u16CmdLenIn != (U16) MON_SDI_WRITE_PSDIO_LEN)
        { //Command length invalid
            pu8DataOut[u8SDIRespIndex] = MON_SDI_INVALID_COMMAND;
            u8SDIRespIndex++;
        }
        else
        {
            // Get mask value
            u8SDICmdIndex = MON_SDI_INDEX_1; // 1 : Desired value for PSD I/O port A
            // Get value Low Byte
            u16Val = (U16)pu8DataIn[u8SDICmdIndex];
            u8SDICmdIndex++;                 // 2 : Desired value for PSD I/O port B
            // Get value High Byte
            u16Val |= ((U16)pu8DataIn[u8SDICmdIndex]) << MON_SHIFT_VAR_BY_8;
            u8SDICmdIndex++;                 // 3 : Bit mask for port A
            // Get mask Low Byte
            u16Mask = ((U16)pu8DataIn[u8SDICmdIndex]);
            u8SDICmdIndex++;                 // 4 : Bit mask for port B
            // Get mask High Byte
            u16Mask |= ((U16)pu8DataIn[u8SDICmdIndex]) << MON_SHIFT_VAR_BY_8;

            // Init  PSD IO channels with received mask and value
            if ( boMON_InitPSDIOChannels(u16Mask, ePSD_OUTPUT, u16Val) == (BOOLEAN)FALSE )
            {
                pu8DataOut[u8SDIRespIndex] = MON_SDI_CHANNEL_ERROR;
                u8SDIRespIndex++;
            }
            else
            {
                // No error so far, prepare reply
                pu8DataOut[u8SDIRespIndex] = MON_SDI_NO_ERROR;
                u8SDIRespIndex++;
            }
        }
    }
    else
    {
        u8SDIRespIndex = MON_SDI_INDEX_1;
        pu8DataOut[u8SDIRespIndex] = MON_SDI_INVALID_COMMAND;
        u8SDIRespIndex++;
    }
    s16RetVal = (S16) u8SDIRespIndex;

    return (s16RetVal); // return reply len
}
//  EndOfFunction s16MON_WritePSDIO ************************************************************************************

//  EndOfFile mon_sdi_psdio.c ******************************************************************************************
