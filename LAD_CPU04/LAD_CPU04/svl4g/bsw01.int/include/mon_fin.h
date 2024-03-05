//**********************************************************************************************************************
//
//                                               mon_fin.h
//
//**********************************************************************************************************************
//
//                                      Copyrights(c) 2022 by KNORR-BREMSE,
//                                 Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   IBC
//! @date      2023-12-04
//! @author    C. Brancolini
//
//**********************************************************************************************************************
//!
//! @file
//! @brief Interface definition for accessing input ports in frequency mode (via MON service)
//!
//**********************************************************************************************************************
//  History
//  Date         Author        Changes
//  24.03.95 G.  Condra        0
//  14.09.95 G.  Condra        1   Removed 'CLOSE'.
//  13.10.95 G.  Condra        2   SB conform.
//  29.11.95 G.  Condra        3   Changed - ref CRequest #6.
//                                 Removed 'boFValueInvalid' flag.
//                                 Extended freq. to 32 bits.
//  08.12.95 G.  Condra        4   Tested by GCC V08.12.95
//  20.12.95 G.  Condra        5   Removed type ref. 'FIN_MEASUREMENT_DATA',
//                                 corrected number of last revision
//                                 entry (was '15' now '4').
//                                 according to CR9 (20/12/95).
//  20.12.95 G.  Condra        6   Tested by GCC V-----------
//  07.03.96 S.  Widder        7   '#pragma non_banked' added
//  21.03.11 C.  Baeuml        9   Porting to MPC55xx.
//  08.08.11 C.  Baeuml        10  Comments.
//  30.04.13 H.  Shaikh        11  Updated as per working instructions
//  2023.09.14   A. Mauro      12  Alignment with CA: name changed and other
//  2023-12-04   C. Brancolini     Codan clean up
//
//**********************************************************************************************************************

#ifndef MON_FIN_H
#define MON_FIN_H

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include    <STD_DEFS.H>

//***************** Constant / macro definitions ( #define ) ***********************************************************

//************************************** Type definitions ( typedef ) **************************************************

//  The following defines the allowed FreqIN (FIN) channel numbers.
    typedef enum {
        eFIN_CHNL_0 = 0,
        eFIN_CHNL_1 = 1,
        eFIN_CHNL_2 = 2,
        eFIN_CHNL_3 = 3
    } E_FIN_CHNL_NUM;


//  The structure 'FIN_MEASUREMENT_DATA *pcFINMeasurementData' consists
//  of two components:
//      The 'LWORD lwFrequency' contains the current frequency this channel.
//      The 'BOOLEAN boFreqUpToDate' indicates that the value
//      returned in (LWORD lwFrequency) has been calculated during this
//      current call to the function 'boFnGetFINCaptData'.
//      If 'BOOLEAN boFreqUpToDate' is returned = FALSE then the
//      value returned in (LWORD lwFrequency) has not been calculated during
//      this call to the function 'boFnGetFINCaptData', ergo not UP-TO-DATE.
//      This does not mean that the value returned in in (LWORD lwFrequency)
//      is not CURRENT. It simply means that there was not enough
//      new FINdata to enable a re-calculation of (LWORD lwFrequency).
//      When 'LWORD lwFrequency' is returned = 0FFFF,FFFFHex this indicates
//      that the selected FIN channel is operating such that the number of
//      frequency input events can not be assimilated (i.e. the current
//      frequency at the FIN hardware pin is so high that the driver is
//      not able to cope with it, at the rate at which the driver function
//      'boFnGetFINCaptData' is currently being called).
//      Should the function 'boFnGetFINCaptData' be called too infrequently
//      such that the freq. in events at the FIN hardware pin cause the
//      FIN event counting mechanism to 'overflow', then it is
//      unable to calculate a meaningful value for (LWORD lwFrequency).
//      NOTE:   The driver will self-correct as soon as the cause of
//             overload has been removed.
//              The cause of overload may be removed by:
//                 Calling the function 'boFnGetFINCaptData' more
//                      frequently - OR -
//                 Reducing the frequency of events at the FIN channel pin.
//      NOTE:   The FIN driver uses the '196 'PTS' mechanism. If more
//              than 255 events are recorded by the 'PTS' mechanism before
//              it (the 'PTS') is (flushed and re-armed) by calling
//              the function 'boFnGetFINCaptData', then the 'PTS' registers
//              an 'overflow'. If the function 'boFnGetFINCaptData'
//              detects such an 'overflow', it restarts the 'PTS' and
//              returns 'LWORD lwFrequency' = 0FFFF,FFFFHex.
//              Thus it can be seen that the more frequently the
//              function 'boFnGetFINCaptData' is called the greater
//              frequency range (bandwidth) the
//              function 'boFnGetFINCaptData' can cover.

typedef struct  {U32      u32Frequency;
                 BOOLEAN    boFreqUpToDate;
                } C_FIN_MEASUREMENT_DATA;


//********************************** Global data declarations ( extern ) ***********************************************

//********************** External parameter / constant declarations ( extern const ) ***********************************

//*************************************** Global func/proc prototypes **************************************************

//* Function boMON_InitFINCaptChannel **********************************************************************************
//
//!  Function  : This function initializes a freq. (speed) capture channel.
//!   @param[in]  eFINChnlNum -  a token representing the desired FIN channel.
//!   @param[out] ---
//! @returns    boTRUE if GO,
//! @returns    boFALSE if: 'eFINChnlNum' contained an illegal value OR
//!            :             Pin Not Available with desired attributes.
//! @remarks   ---
//**********************************************************************************************************************
extern  BOOLEAN boMON_InitFINCaptChannel (E_FIN_CHNL_NUM eFINChnlNum);

//* Function boMON_GetFINCaptData **************************************************************************************
//
//!  Function  : This function reads the captured events and time info.
//!              from a frequency input channel and converts the captured
//!              data (together with state information derived from
//!              previous executions of this function) to a frequency
//!              value and conversion status. The frequency and status are
//!              returned to the caller.
//! @param[in]  eFINChnlNum: -  a token representing the
//!                             desired FIN channel.
//!             FIN_MEASUREMENT_DATA *pcFINMeasurementData - a pointer to
//!             a structure where the results are to be returned.
//! @param[out] pcFINMeasurementData: Frequency input value read
//! @returns    boTRUE if GO - channel initialised.
//! @returns    boFALSE if: 'eFINChnlNum' contained an illegal value OR
//!                         FIN channel not initialised.
//! @remarks   : The FIN channel may not be able to deliver a result
//!             that is UP-TO-DATE every time the
//!             function 'boMON_GetFINCaptData' is called. This is true
//!             above all when the period of the input frequency
//!             is shorter than the elapsed time between successive
//!             calls to this function ('boMON_GetFINCaptData').
//!             That an UP-TO-DATE value can not be delivered does
//!             not mean that a current value can not be delivered.
//!             In those cases where an UP-TO-DATE value could not
//!             be delivered (due to lack of new channel input events)
//!             then the last determined value for the frequency input
//!             for the channel is delivered.
//!             The flag 'boFreqUpToDate' = FALSE indicates that the
//!             value delivered in 'lwFrequency' has not been calculated
//!             during this call to 'boMON_GetFINCaptData' as there
//!             is no 'new' data available with which to calculate.
//!
//!             NOTE:   An FIN channel will 'overflow' when:
//!                         The PTS readout mechanism (this function) is
//!                         called too infrequently
//!                         OR
//!                         the input frequency is too high.
//!                     This function can not distinguish the former case
//!                     from the latter case. It bundles and covers both
//!                     by returning 'LWORD lwFrequency' = 0FFFF,FFFFHex.
//**********************************************************************************************************************
extern  BOOLEAN boMON_GetFINCaptData
                    (E_FIN_CHNL_NUM eFINChnlNum,
                     C_FIN_MEASUREMENT_DATA* pcFINMeasurementData
                    );

#endif
//* EndOfFile MON_FIN.H ************************************************************************************************
