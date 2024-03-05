//**********************************************************************************************************************
//
//                                               mon_sdi_pwm.c
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
//!         Module contains function to access PWM driver
//!
//**********************************************************************************************************************
//
// History
// Date            Author              Changes
// 09.11.2011      W. Boigk            0.1  / Start
// 17.11.2011      W. Boigk            0.2  / Splitting into GNRL and specific part
// 07.06.13        H. Shaikh           0.3  / Generalization of Command
// 11.12.13        H. Shaikh           0.4  / Bugfix into s16MONReadPWM
// 28.05.14        H. Shaikh           0.5  / BC_002-814: Command length verification add
// 07.07.15        P. Munoli           0.6  / TC_007-44: Added if else condition in the
//                                          / function s16MONReadPWM
//                                          / TC_007-68: Renamed MON_RANGE_ERROR to
//                                          / MON_CHANNEL_ERROR in function s16MONWritePWM
// 31.03.17        A. Mauro            0.7  / TC_007-98: inverted defined values of
//                                            MON_DUTY_CYCLE_0PERC & MON_DUTY_CYCLE_100PERC
// 20.04.17        A. Mauro            0.8  / TC_007-96: LINT clean up
// 2023.09.14      A. Mauro            0.9   Alignment with CA: name changed and other
// 2023-12-05      C. Brancolini       Lint Plus clean up
//
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************

#include "mon_cpu04_genrl_sdi_i.h"    // MON CPU04 SDI command handler
#include "mon_pwm.h"
#include "mon_cpu04.h"
#include "ios_hal.h"                    // Hardware Abstraction Layer
#include "bcl_s.h"                      // General BCL service definitions
#include "sdi.h"                                            // Error Codes
#include "bcm_strt.h"                                       // BCL system inteface

//**************************************** Constant / macro definitions ( #define ) ************************************
#define MON_NUMBER_FIN_CHNL  (U8)2           //!< Number of FIs
#define MON_NUMBER_FOUT_CHNL (U8)2           //!< Number of FOs
#define MON_FIRST_CH_HANDLE  (U8)0           //!< Start point
#define MON_DUTY_CYCLE_0PERC (U32)1000   //!< Duty Cycle 0%
#define MON_DUTY_CYCLE_100PERC (U32)0    //!< Duty Cycle 100%
#define MON_READPWM_REPLY_POS_UPTODATE      (U8)3   //!< Position up to date flag in Read PWM reply
#define MON_READPWM_REPLY_POS_LOWBYTE      (U8)4   //!< position low-byte in Read PWM reply
#define MON_READPWM_REPLY_POS_HIGHBYTE     (U8)5   //!< position high-byte in Read PWM reply

#define MON_WRITEPWM_CMD_POS_DUTYC_LOWBYTE      (U8)3   //!< position low-byte in Read PWM cmd
#define MON_WRITEPWM_CMD_POS_DUTYC_HIGHBYTE     (U8)4   //!< position high-byte in Read PWM cmd


#define MON_CHANNEL_NUM_POS_VALUE  (U8)1     //!< position of channel in input
#define MON_READPWM_CMD_PARA_LEN     (U8)1   //!< byte length of parameters for each PWM port in Read PWM cmd
#define MON_READPWM_REPLY_PARA_LEN   (U8)3   //!< byte length of parameters for each PWM port in Read PWM reply
#define MON_WRITEPWM_CMD_PARA_LEN    (U8)3   //!< byte length of parameters for each PWM port in Write PWM cmd


//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *******************************************************************************************************

//**********************************************************************************************************************
//
// Function s16MON_ReadPWM
//
//**********************************************************************************************************************
s16SDI_CMD(s16MON_ReadPWM)
{
    //************************************************ Function scope data *********************************************
    S16 s16RetVal = 0;                              // Return value of function
    U8 u8NumberOfInputs = 0;                        // Number of PWM Inputs to be read
    U32 au32PWMInput[MON_NUMBER_FIN_CHNL] = {0, 0 }; // PWM input values
    BOOLEAN aboUpToDateBit[MON_NUMBER_FIN_CHNL] = {0, 0 };
                                                    // Status up to date bit
    U8 u8Cnt;                                       // Counter for loops
    U16 u16SDIRespIndex = MON_SDI_INDEX_1;           // SDI response index
    E_BCM_BOARD_STATE   eBoardState;                // Board state


    //*************************************** Function scope static data declaration ***********************************

    //*************************************************** Function code ************************************************

    (void)u16MaxRespOut; // unused parameter

    // Check Board State:
    eBoardState = eBCM_StrtGetBoardState();

    // Build reply message:
    if (eBoardState == eBCM_BS_TEST)
    {
        // Get Number of PWM Inputs to be read
        u8NumberOfInputs = pu8DataIn[MON_SDI_INDEX_1];

        // Check for range error
        if (u8NumberOfInputs > MON_NUMBER_FIN_CHNL)
        {
            // Number of PWM Inputs to be read is greater than the number of freq ip channels
            // Reply with RANGE_ERROR
            pu8DataOut[u16SDIRespIndex] = MON_SDI_RANGE_ERROR;
            u16SDIRespIndex++;
            s16RetVal = (S16) u16SDIRespIndex;
        }// Check for invalid command
        else if (u16CmdLenIn != (((U16)u8NumberOfInputs * MON_READPWM_CMD_PARA_LEN) + MON_SDI_PAR_OFFSET))
        {   //Command length invalid
            pu8DataOut[u16SDIRespIndex] = MON_SDI_INVALID_COMMAND;
            u16SDIRespIndex++;
            s16RetVal = (S16) u16SDIRespIndex;
        }// Check for channel error
        else if ((pu8DataIn[MON_SDI_INDEX_2] > MON_CHANNEL_NUM_POS_VALUE) ||
                 (pu8DataIn[MON_SDI_INDEX_3] > MON_CHANNEL_NUM_POS_VALUE))
        {
            pu8DataOut[u16SDIRespIndex] = MON_SDI_CHANNEL_ERROR; // set channel error
            u16SDIRespIndex++;
            s16RetVal = (S16) u16SDIRespIndex;
        }
        else
        {
            // No error so far, prepare no error reply

            // loop requested PWM inputs
            for (u8Cnt = 0; u8Cnt < u8NumberOfInputs; u8Cnt++)
            {
                // Read PWM data
                (void) boMON_ReadPWM( pu8DataIn[MON_SDI_PAR_OFFSET + u8Cnt],
                &au32PWMInput[u8Cnt], &aboUpToDateBit[u8Cnt] );

                // Handle up-to-date flag:
                // set to zero in case of duty cycle 0% or duty cycle 100%
                if ( (au32PWMInput[u8Cnt] == MON_DUTY_CYCLE_0PERC) ||
                     (au32PWMInput[u8Cnt] == MON_DUTY_CYCLE_100PERC) )
                {
                    aboUpToDateBit[u8Cnt] = FALSE;
                }

            }
            pu8DataOut[u16SDIRespIndex] = MON_SDI_NO_ERROR;         // reset MON STATUS
            u16SDIRespIndex++;
            pu8DataOut[u16SDIRespIndex] = u8NumberOfInputs;         // Number of Inputs. Only
            // Needed once per call
            u16SDIRespIndex++;
            for (u8Cnt = 0; u8Cnt < u8NumberOfInputs; u8Cnt++) // loop until all PWM In
            { // signals wrote to
                *(pu8DataOut + MON_READPWM_REPLY_POS_UPTODATE + (MON_READPWM_REPLY_PARA_LEN * u8Cnt)) =
                    aboUpToDateBit[u8Cnt];
                *(pu8DataOut + MON_READPWM_REPLY_POS_LOWBYTE + (MON_READPWM_REPLY_PARA_LEN * u8Cnt)) =
                    (U8) au32PWMInput[u8Cnt];
                *(pu8DataOut + MON_READPWM_REPLY_POS_HIGHBYTE + (MON_READPWM_REPLY_PARA_LEN * u8Cnt)) =
                    (U8) (au32PWMInput[u8Cnt] >> MON_SHIFT_VAR_BY_8);
            }
            // length of reply message
            u16SDIRespIndex = (u16SDIRespIndex + (MON_READPWM_REPLY_PARA_LEN * (U16)u8NumberOfInputs));
            s16RetVal = (S16) u16SDIRespIndex;
        }
    }
    else
    {
        // Board not in test mode
        // reply with invalid command
        pu8DataOut[u16SDIRespIndex] = MON_SDI_INVALID_COMMAND;
        u16SDIRespIndex++;
        s16RetVal = (S16) u16SDIRespIndex;
    }
    return (s16RetVal);
}
// EndOfFunction s16MON_ReadPWM ****************************************************************************************


//**********************************************************************************************************************
//
// Function s16MON_WritePWM
//
//**********************************************************************************************************************
s16SDI_CMD(s16MON_WritePWM)
{
    //************************************************ Function scope data *********************************************
    S16 s16RetVal = 0;                               // Return value of function
    U8  u8NumberOfOutputs;                           // Number of Outputs received
    U8  u8OutputCnt;                                 // Internal Counter
    U8  u8OutputNumber;                              // Number of outputs internal used
    U32 u32PWMDutyCycle;                             // duty cycle
    U32 u32PWMTemp;                                  // duty cycle
    U8  u8Offset = 0;                                // offset for getting information
    U8  u8SDIRespIndex = MON_SDI_INDEX_1;                              // SDI command index
    BOOLEAN boReturn;                                // Return value of function
    E_BCM_BOARD_STATE eBoardState;                   // Board state


    //*************************************** Function scope static data declaration ***********************************

    //*************************************************** Function code ************************************************

    (void)u16MaxRespOut; // unused parameter

    // Check Board State:
    eBoardState = eBCM_StrtGetBoardState();

    // Build reply message:
    if (eBoardState == eBCM_BS_TEST)
    {
        // Get number of outputs from cmd message
        u8NumberOfOutputs = pu8DataIn [MON_SDI_INDEX_1];

        if (u8NumberOfOutputs > MON_NUMBER_FOUT_CHNL)    // N > no of freq output channels
        {
            // too big - reply with RANGE_ERROR
            pu8DataOut[u8SDIRespIndex] = MON_SDI_RANGE_ERROR;
            u8SDIRespIndex++;
            return ((S16)u8SDIRespIndex);
        }

        if (u16CmdLenIn != (((U16)u8NumberOfOutputs * MON_WRITEPWM_CMD_PARA_LEN) + MON_SDI_PAR_OFFSET))
        {
            //Command length invalid
            pu8DataOut[u8SDIRespIndex] = MON_SDI_INVALID_COMMAND;
            u8SDIRespIndex++;
        }
        else
        {
            // No error so far, prepare no error reply

            for (u8OutputCnt = 0; u8OutputCnt <= u8NumberOfOutputs; u8OutputCnt++)
            {
                // Get PWM output number
                u8OutputNumber = *(pu8DataIn + MON_NUMBER_FIN_CHNL + u8Offset);

                // Get Channel Duty Cycle: get low-byte, hi-byte and combine them
                u32PWMDutyCycle = (U32)(*(pu8DataIn + MON_WRITEPWM_CMD_POS_DUTYC_LOWBYTE + u8Offset)); // Get value Low Byte
                u32PWMTemp =(U32)(*(pu8DataIn + MON_WRITEPWM_CMD_POS_DUTYC_HIGHBYTE + u8Offset));
                u32PWMDutyCycle |= u32PWMTemp << MON_SHIFT_VAR_BY_8;            // Get value HI  Byte

                // The received PWM value must be inverted
                u32PWMDutyCycle = (U32)(MON_PWM_100PER - u32PWMDutyCycle);

                // Set duty cycle
                boReturn = boMON_WritePWM((U16)u8OutputNumber, u32PWMDutyCycle);
                // Check write result
                if (boReturn != (BOOLEAN)TRUE)
                {
                    // Error in writing, prepare reply message
                    pu8DataOut[u8SDIRespIndex] = MON_SDI_CHANNEL_ERROR;
                    u8SDIRespIndex++;
                    s16RetVal = (S16) u8SDIRespIndex;
                    return (s16RetVal);
                }
                u8Offset += MON_WRITEPWM_CMD_PARA_LEN;      // increase by three
            }
            pu8DataOut[u8SDIRespIndex] = MON_SDI_NO_ERROR;       // No Error
            u8SDIRespIndex++;
        }
    }
    else
    {
        // Board not in test mode
        // reply with invalid command
        pu8DataOut[u8SDIRespIndex] = MON_SDI_INVALID_COMMAND;
        u8SDIRespIndex++;
    }
    s16RetVal = (S16) u8SDIRespIndex;
//lint -e818
    return (s16RetVal);
}

// EndOfFunction s16MON_WritePWM ***************************************************************************************

// EndOfFile mon_sdi_pwm.c *********************************************************************************************
