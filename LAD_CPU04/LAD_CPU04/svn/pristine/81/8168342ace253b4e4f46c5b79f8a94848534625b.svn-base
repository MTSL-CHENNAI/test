//**********************************************************************************************************************
//
//                                          mon_sdi_binio.c
//
//**********************************************************************************************************************
//
//                                    Copyrights(c) 2022 by KNORR-BREMSE,
//                                       Rail Vehicle Systems, Munich
//
//! @project IBC
//! @date    2023-12-15
//! @author  C. Brancolini
//
//**********************************************************************************************************************
//!
//! @file
//! @brief   Service Monitor for project IBC
//!          Module contains functions to access i/o-ports in binary mode
//!
//**********************************************************************************************************************
//
// History
// Date            Author              Changes
// 23.02.96        S. Widder           1.00 / Start, based on sources from
//                                     D. Dunkel and W. Bartel (Fa. MICRONOVA)
// 07.03.96        S. Widder           1.10 / Modified read digio because of error
// 10.03.96        D. Dunkel           1.10 / write digio: init bMaxCnt with value of
//                                            the terminal command read digio:  extended terminal command
//                                            (io-channel mask
// 13.03.96        S. Widder           1.20 / Removed mask in read digio response to
//                                            terminal
// 25.03.96        S. Widder           1.21 / Corrected bug putting read ports to buff
// 25.03.96        S. Widder           1.22 / Corrected filenames for include files
// 25.04.96        S. Widder           1.23 / added '#pragma codeseg' for banking
//                                            added declaration of non-banked functions
// 08.05.96        S. Widder           1.3  / shortend 'ReadDigIO'
// 15.05.96        S. Widder           1.31 / CR39: Removed pathes in file include
// 15.03.11        C. Baeuml           1.4  / Porting to MPC55xx.
// 24.03.11        C. Baeuml           1.4  / H- File names.
// 06.06.13        H. Shaikh           1.5  / Generalization of Command
// 29.05.14        H. Shaikh           1.6  / BC_002-814: Command length verification add
//                                            Lint:Code Claenup
// 20.04.17        A. Mauro            1.7    TC_007-96: LINT clean up
// 2023.09.13      A. Mauro            1.8    Alignment with CA: name changed and other
// 2023-12-15      C. Brancolini       Lint Plus cleanup
//
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include <string.h>                   // Include memcpy

#include "mon_cpu04_genrl_sdi_i.h"    // MON CPU04 SDI command handler
#include "mon_binio.h"                // MON binary IO definitions
#include "mon_cpu04.h"                // MON CPU04 definitions
#include "mon.h"                      // MON SDI definitions
#include "bcl_s.h"                    // General BCL service definitions
#include "sdi.h"                      // Error Codes
#include "bcm_strt.h"                 // BCL system interface

//**************************************** Constant / macro definitions ( #define ) ************************************
#define MON_DUMMY_OUTPUT_VAL (U8) 0x00     // Dummy val for init bin io
#define MON_OUTPORT_PARA_LEN (U8) 3        // no. of parameter for each port in the SDI command
#define MON_INPORT_PARA_LEN  (U8) 2        // no. of parameter for each port in the SDI command

#define MON_OUTPUT_PORT_NUM   (U8) 0  // internal offset of port number inside parm group in the SDI command write DGIO
#define MON_OUTPUT_PORT_VALUE (U8) 1  // internal offset of port value inside parm group in the SDI command write DGIO
#define MON_OUTPUT_PORT_MASK  (U8) 2  // internal offset of port mask inside parm group in the SDI command write DGIO

#define MON_INPUT_PORT_NUM   (U8) 0  // internal offset of port number inside parm group in the SDI command read DGIO
#define MON_INPUT_PORT_MASK  (U8) 1  // internal offset of port mask inside parm group in the SDI command read DGIO

#define MON_MAXINPORT_NO ((MON_MSGMAXLEN - 3U) / 2U) //todo: not clear

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *******************************************************************************************************

//**********************************************************************************************************************
//
// Function s16MON_ReadDigioByte
//**********************************************************************************************************************
s16SDI_CMD(s16MON_ReadDigioByte)
{
    //************************************************ Function scope data *********************************************
    U8 u8Cnt;                             // counting variable
    U8 u8ReqPortsCnt;                     // var to store number of ports to read
    U8 u8Mask;                            // temp var for DigIO mask
    U8 u8State;                           // temp var for DigIO state
    C_MON_IO_BUFF cMonIOBuff;             // buffer for temp storage of io input bytes/words/lwords
    U8* pu8IOByteBuffer = KB_NULL_PTR;    // ptr to buffer
    U8 u8SDIRespIndex = MON_SDI_INDEX_1;  // SDI response index
    E_BCM_BOARD_STATE eBoardState;        // Board state
    S16 s16RetVal;                        // Function return value
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
        u8ReqPortsCnt = pu8DataIn [MON_SDI_INDEX_1];

        // check reading range
        if (u8ReqPortsCnt > MON_MAXINPORT_NO)
        {
            // too big - reply with RANGE_ERROR
            pu8DataOut[u8SDIRespIndex] = MON_SDI_RANGE_ERROR;
            u8SDIRespIndex++;
            return ((S16)u8SDIRespIndex);
        }

        if( u16CmdLenIn != (((U16)u8ReqPortsCnt * MON_INPORT_PARA_LEN) + MON_SDI_PAR_OFFSET) )
        {
            // Command length invalid
            pu8DataOut[u8SDIRespIndex] = MON_SDI_INVALID_COMMAND;
            u8SDIRespIndex++;
        }
        else
        {
            // Command length valid
            pu8Tmp = pu8DataIn + MON_SDI_PAR_OFFSET;    // setup ptr to port numbers
            pu8IOByteBuffer = &(cMonIOBuff.au8Data[0]); // setup ptr to result buffer

            for (u8Cnt = 0; u8Cnt < u8ReqPortsCnt; u8Cnt++)
            {
                // Try to init IO channel for reading
                if( boMON_InitBinIoChannels(
                     pu8Tmp[MON_INPUT_PORT_NUM],      // IO channel port number
                     pu8Tmp[MON_INPUT_PORT_MASK],     // IO channel pin mask
                     eINPUT,                                 // input mode for read
                     MON_DUMMY_OUTPUT_VAL) == (BOOLEAN)FALSE)
                {
                    // channel error
                    pu8DataOut[u8SDIRespIndex] = MON_SDI_CHANNEL_ERROR;
                    u8SDIRespIndex++;
                    return ((S16)u8SDIRespIndex);
                }
                (void) boMON_GetBinIOChannels( pu8Tmp[MON_INPUT_PORT_NUM], &u8Mask, &u8State );
                // read bin io channels
                *pu8IOByteBuffer = u8State & pu8Tmp[MON_INPUT_PORT_MASK];
                pu8IOByteBuffer++;
                // put read bytes into buffer
                // switch to next port number
                pu8Tmp = pu8Tmp + MON_INPORT_PARA_LEN;
            }

            // No error so far, prepare reply message
            pu8DataOut[u8SDIRespIndex] = MON_SDI_NO_ERROR; // no error
            u8SDIRespIndex++;

            pu8DataOut[u8SDIRespIndex] = u8ReqPortsCnt;
            u8SDIRespIndex++;

            // copy buffer to reply message
            memcpy((void *) (pu8DataOut + u8SDIRespIndex),
                   (const void *) cMonIOBuff.au8Data, u8ReqPortsCnt);
            u8SDIRespIndex = (u8SDIRespIndex + u8ReqPortsCnt); // reply message length
        }
    }
    else
    {
        // Board not in test mode:
        // reply invalid command
        u8SDIRespIndex = MON_SDI_INDEX_1;
        pu8DataOut[u8SDIRespIndex] = MON_SDI_INVALID_COMMAND;
        u8SDIRespIndex++;
    }
    s16RetVal = (S16) (u8SDIRespIndex );
    // return reply message length
    return (s16RetVal);

}
//  EndOfFunction s16MON_ReadDigioByte *********************************************************************************

//**********************************************************************************************************************
//
// Function s16MON_WriteDigioByte
//**********************************************************************************************************************
s16SDI_CMD(s16MON_WriteDigioByte)
{
//************************************************ Function scope data *********************************************
    U8 u8Cnt;                             // counting variable
    U8 u8PortsCnt;                        // variable to store number of ports to write
    U8 u8SDIRespIndex = MON_SDI_INDEX_1;  // SDI reply index
    U8 u8SDICmdIndex = MON_SDI_INDEX_1;   // SDI command index
    E_BCM_BOARD_STATE eBoardState;        // Board state
    S16 s16RetVal;                        // Function return value
    U8* pu8Tmp;                           // Temporary pointer

//*************************************************** Function code ************************************************
    (void)u16MaxRespOut; // unused parameter

    // Get Board State
    eBoardState = eBCM_StrtGetBoardState();

    // Check Board State
    if (eBoardState == eBCM_BS_TEST)
    {
        // The board is in test mode

        // get number of ports to write
        u8PortsCnt = pu8DataIn[u8SDICmdIndex];

        // check writing range
        if (u8PortsCnt > MON_MAXOUTPORT_NO)
        {
            // too big - reply with RANGE_ERROR
            pu8DataOut[u8SDIRespIndex] = MON_SDI_RANGE_ERROR;
            u8SDIRespIndex++;
            // return reply message length
            return ((S16)u8SDIRespIndex);
        }

        // Check command length
        if( u16CmdLenIn != (((U16)u8PortsCnt * MON_OUTPORT_PARA_LEN) + MON_SDI_PAR_OFFSET) )
        {
            //Command length invalid - reply with INVALID_COMMAND
            pu8DataOut[u8SDIRespIndex] = MON_SDI_INVALID_COMMAND;
            u8SDIRespIndex++;
        }
        else
        {
            // no error so far

            // setup pu8Tmp to port numbers
            pu8Tmp = pu8DataIn + MON_SDI_PAR_OFFSET;

            // write i/o ports
            for (u8Cnt = 0; u8Cnt < u8PortsCnt; u8Cnt++)
            {
                // write to i/o ports
                if( boMON_InitBinIoChannels( pu8Tmp[MON_OUTPUT_PORT_NUM],       // i/o-channel port number
                    pu8Tmp[MON_OUTPUT_PORT_MASK],                               // i/o-channel pin mask
                    eOUTPUT,                                                         // output mode
                    pu8Tmp[MON_OUTPUT_PORT_VALUE] ) == (BOOLEAN)FALSE )         // i/o-channel value
                {
                    // failed to initialize the channel - reply with CHANNEL_ERROR
                    pu8DataOut[u8SDIRespIndex] = MON_SDI_CHANNEL_ERROR;
                    u8SDIRespIndex++;
                    // return reply message length
                    return ((S16)u8SDIRespIndex);
                }
                // switch to next port number
                pu8Tmp = pu8Tmp + MON_OUTPORT_PARA_LEN;
            }

            // request is done properly - reply with NO_ERROR
            pu8DataOut[u8SDIRespIndex] = MON_SDI_NO_ERROR;
            u8SDIRespIndex++;
        }
    }
    else
    {
        // The board is not in test mode - reply with INVALID_COMMAND
        u8SDIRespIndex = MON_SDI_INDEX_1;
        pu8DataOut[u8SDIRespIndex] = MON_SDI_INVALID_COMMAND;
        u8SDIRespIndex++;
    }
    s16RetVal = (S16) u8SDIRespIndex;
    // Return the length of the reply message
    return (s16RetVal);
}
//  EndOfFunction s16MON_WriteDigioByte ********************************************************************************

//  EndOfFile MON_SDI_BINIO.C ******************************************************************************************
