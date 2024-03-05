//**********************************************************************************************************************
//
//                                               mon_fout.h
//
//**********************************************************************************************************************
//
//                                      Copyrights(c) 2022 by KNORR-BREMSE,
//                                 Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   IBC
//! @date      2023-12-05
//! @author    C. Brancolini
//
//**********************************************************************************************************************
//!
//! @file
//! @brief Interface definition for accessing output ports in frequency mode (via MON service)
//!
//**********************************************************************************************************************
//  History
//  Date         Author        Changes
//  24.01.96 G.  Condra        0   Creation.
//  31.01.96 G.  Condra        1   Tested by GCC V31.01.96
//  07.03.96 S.  Widder        2   '#pragma non_banked' added
//  21.03.11 C.  Baeuml        3   Porting to MPC55xx.
//  2023.09.14   A. Mauro      4   Alignment with CA: name changed and other
//  2023-12-05   C. Brancolini     Codan clean up
//
//**********************************************************************************************************************

#ifndef MON_FOUT_H
#define MON_FOUT_H

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include    <STD_DEFS.H>

//***************** Constant / macro definitions ( #define ) ***********************************************************

//************************************** Type definitions ( typedef ) **************************************************

//  The following defines the allowed FreqOUT (FOUT) channel numbers.
    typedef enum    {eFREQ_OUT_CHNL_0 = 0,        //!< Frequency output channel 0
                     eFREQ_OUT_CHNL_1 = 1,        //!< Frequency output channel 1
                     eFREQ_OUT_CHNL_2 = 2,        //!< Frequency output channel 2
                     eFREQ_OUT_CHNL_3 = 3         //!< Frequency output channel 3
                    } E_FREQ_OUT_CHNL_NUM;


//********************************** Global data declarations ( extern ) ***********************************************

//********************** External parameter / constant declarations ( extern const ) ***********************************

//*************************************** Global func/proc prototypes **************************************************

//* Function boMON_InitFreqOut *****************************************************************************************
//
//! Function  : This function initializes a given FREQuency output
//!             channel provided the required hardware is available.
//!             If GO then 'u16InitFREQValue' is output.
//! @param[in]  eFREQOutChnlNum:  a WORD with the number of the desired FREQ out
//!                                channel in the LSByte.
//! @param[in]  u16InitFREQValue: Value to be output initially.
//! @param[out] ---
//! @returns    boTRUE if GO,
//! @returns    boFALSE if eFREQOutChnlNum contained an illegal value OR
//!                        Pin Not Available with desired attributes OR
//!                        FREQ Value Out Of Range (from wInitFREQValue).
//! Remarks   : The FREQ value passed will be range tested.
//!             Values passed which are out of range will be modified as
//!             follows:    >maximum will be limited to maximum,
//!                         <minimum will be converted to 0.
//**********************************************************************************************************************
extern  BOOLEAN boMON_InitFreqOut (E_FREQ_OUT_CHNL_NUM eFREQOutChnlNum,
                                 U16 u16InitFREQValue
                                );


#endif
//** EndOfFile MON_FOUT.H **********************************************************************************************
