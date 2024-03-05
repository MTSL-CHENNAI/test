//**********************************************************************************************************************
//
//                                                ios_cpu04_i.h
//
//**********************************************************************************************************************
//
//                                        Copyrights(c) by KNORR-BREMSE
//                                        Rail Vehicle Systems, Munich
//
//! @project IBC
//! @date    2023-12-11
//! @author  C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file    ios_board_i.h
//! @brief   IOS board specific internal interface file
//!
//! @details
//!
//**********************************************************************************************************************
//
//  History
//  Date        Author         Changes
//  2018-10-15  R. Palsule     Start
//  2020-02-12  A. Mauro       Lint clean ups
//  2020-04-03  A. Mauro       Renamed boIOS_FinUptodate -> aboIOS_FinUptodate
//  2023-12-11  C. Brancolini  Lint Plus clean up
//
//**********************************************************************************************************************

#ifndef IOS_CPU04_I_H
#define IOS_CPU04_I_H

//***************************************** Header / include files ( #include ) ****************************************
#include "kb_types.h"                   // Standard definitions
#include "ios_i.h"                      // IOS internal definitions

//************************************** Constant / macro definitions ( #define ) **************************************
#define IOS_BI_ERROR_MASK       ((U8)0x01U)                 //!< Mask for binary error
#define IOS_MAX_NUMBER_BI       ((U8)0x10U)                 //!< Max number of filtered BI channels. i.e. 16
#define IOS_MAX_NUMBER_FI       ((U8)0x04U)                 //!< Max number of filtered FI channels.

//******************************************** Type definitions ( typedef ) ********************************************
//! Used to transform U32 <-> U8
typedef union
{
U32 u32Value;                                   //!< U32 value
U8 au8Value[IOS_INDEX_4];                       //!< U8 value
} C_IOS_U32_U8;

//****************************************** Global data declarations ( extern ) ***************************************

//! @name Binary input filter variables
//! @{
//! Filter output for BIs. Global variable containing the evaluated input bits after 10 samples.
//! For bit mapping see logical channel masks #IOS_MASK_CHAN1 etc.
extern U32 u32IOS_FltBiInputs;

//! Filter output for binary configured FIs. Global variable containing the evaluated input bits after 10 samples.
//! For bit mapping see logical channel masks #IOS_MASK_CHAN1 etc.
extern U32 u32IOS_FltFiBinInputs;

//! @}

//! @name Binary input filter variables
//! @{
//! FIN raw data from last driver call. Index is logical channel.
extern C_IOS_U32_U8 acIOS_FinRaw[IOS_MAX_NUMBER_FI];
//! FIN filtered data. Index is logical channel.
extern C_IOS_U32_U8 acIOS_FinFiltered[IOS_MAX_NUMBER_FI];
//! FIN up to date flag. Index is logical channel.
extern BOOLEAN aboIOS_FinUptodate[IOS_MAX_NUMBER_FI];
//! @}


//****************************** External parameter / constant declarations ( extern const ) ***************************

//
// Function boIOS_InitBiFilt
//**********************************************************************************************************************
//!  @brief         Initialize Binary Filter for a BI channel. Initialize needed HAL channel. Activate necessary cyclic
//!                 binary filter functions if not done.
//!
//!  @details       -
//!
//!  @param[in]     u16Channel      :Logical Channel number to be initialized.
//!                                  Max number of channels see #IOS_MAX_NUMBER_BI.
//!
//!  @param[in,out] -
//!
//!  @param[out]    -
//!
//!  @returns       TRUE        Filter and HAL initialization ok.
//!                 FALSE       Channel out of range or driver error.
//!
//!  @remarks       General function.
//**********************************************************************************************************************
extern BOOLEAN boIOS_InitBiFilt (U16 u16Channel);

// Function boIOS_InitFIBinFilt
//**********************************************************************************************************************
//!  @brief         Initialize FI channel as binary and set up filter. Initialize needed HAL channel. Activate
//!                 necessary cyclic binary filter functions if not done.
//!
//!  @details       -
//!
//!  @param[in]     u16Channel      :Logical FI Channel to be initialized
//!                                  Maximum channel number see #IOS_MAX_NUMBER_FI
//!
//!  @param[in,out] -
//!
//!  @param[out]    -
//!
//!  @returns       TRUE        Filter and HAL initialization ok.
//!                 FALSE       Channel out of range or driver error.
//!
//!  @remarks       General function.
//**********************************************************************************************************************
extern BOOLEAN boIOS_InitFIBinFilt (U16 u16Channel);

// Function boIOS_InitFIFilt
//**********************************************************************************************************************
//!  @brief         Initialize FI channel to be filtered. Initialize needed HAL channel. Activate necessary cyclic
//!                 binary filter functions if not done.
//!
//!  @details       -
//!
//!  @param[in]     u16Channel      :Logical FI Channel to be initialized
//!                                  Maximum channel number see #IOS_MAX_NUMBER_FI
//!
//!  @param[in,out] -
//!
//!  @param[out]    -
//!
//!  @returns       TRUE            :Filter successfully activated on channel.
//!                 FALSE           :Channel out of range or driver error or  Filter function could not be activated.
//!
//!  @remarks       General function.
//**********************************************************************************************************************
extern BOOLEAN boIOS_InitFIFilt (U16 u16Channel);

// Function boIOS_GetBiRaw
//**********************************************************************************************************************
//!  @brief         Get raw values of BIs. Make BI diagnosis after configured time. Set/ Reset corresponding errors
//!                 in FMN.
//!
//!  @details       -
//!
//!  @param[in]     pboInputs        :Reference to binary inputs array boInputs[IOS_MAX_NUMBER_BI].Index is logical
//!                                  channel.
//!
//!  @param[in,out] -
//!
//!  @param[out]    -
//!
//!  @returns       TRUE            :if access ok.
//!                 FALSE           :if driver problems.
//!
//!  @remarks       General function.Board specific configuration needed. This function is called every 5ms. Internal
//!                 function of IOS_FILT.C made global for testability.
//**********************************************************************************************************************
extern BOOLEAN boIOS_GetBiRaw (BOOLEAN* pboInputs);

// Function boIOS_GetFIBinRaw
//**********************************************************************************************************************
//!  @brief         Get raw values of binary configured FIs. Make FI (binary) diagnosis after configured time.
//!                 Set/ Reset corresponding errors in FMN.
//!
//!  @details       -
//!
//!  @param[in]     pboInputs        :Reference to binary inputs array boInputs[IOS_MAX_NUMBER_FI]. Index is logical
//!                                  channel.
//!
//!  @param[in,out] -
//!
//!  @param[out]    -
//!
//!  @returns       TRUE            :if access ok.
//!                 FALSE           :if driver problems.
//!
//!  @remarks       General function.Board specific configuration needed. This function is called every 5ms. Internal
//!                 function of IOS_FILT.C made global for testability.
//**********************************************************************************************************************
extern BOOLEAN boIOS_GetFIBinRaw (BOOLEAN* pboInputs);

// Function boIOS_FilterFin
//**********************************************************************************************************************
//!  @brief         It compares the two frequency samples F(i) and F(i-1). The absolute difference of this comparison
//!                 must not exceed  FIN_TOLERANCE (cHz). If three successive comparisons are OK store F(i) to
//!                 pu32FOutput
//!
//!  @details       -
//!
//!  @param[in]     pu32InSamples  :array of samples of a specific Fin channel
//!  @param[in]     pu32FOutput    :output frequency for port
//!
//!  @param[in,out] -
//!
//!  @param[out]    -
//!
//!  @returns       TRUE            :if 3 comparisons were OK
//!                 FALSE           :if no value was found, in this case pu32FOutput = FFFFFF is stored
//!
//!  @remarks       General function.Board specific configuration needed. Internal function of IOS_FILT.C made
//!                 global for testability.
//**********************************************************************************************************************
extern BOOLEAN boIOS_FilterFin (const U32* pu32InSamples, U32* pu32FOutput);

// Function s16IOS_GetBinaryFiltered
//**********************************************************************************************************************
//!  @brief         This Function is used to get binary data of given channel and signal type from filter function
//!
//!  @details       -
//!
//!  @param[in]     eChannelType    : Channel Type
//!  @param[in]     u16Channel      : Channel number
//!
//!  @param[in,out] pboBinaryData   : Pointer to binary data
//!
//!  @param[out]    -
//!
//!  @return        Error Code
//!                 KB_RET_OK               : If reading of channel is successful.
//!                 KB_RET_ERR_INTERNAL     : If reading of channel is unsuccessful.
//!                 KB_RET_ERR_ARG          : If input parameter is not valid.
//!
//!  @remark        This is valid for BI, FI in binary mode
//**********************************************************************************************************************
extern S16 s16IOS_GetBinaryFiltered ( E_IOS_IO_CHANNEL_TYPE eChannelType, U16 u16Channel, BOOLEAN* pboBinaryData);

// Function s16IOS_GetFrequencyFiltered
//**********************************************************************************************************************
//!  @brief         This Function is used to get frequency data of given channel and signal type filtered vaule.
//!
//!  @details       -
//!
//!  @param[in]     eChannelType    : Channel Type
//!  @param[in]     u16Channel      : Channel number
//!
//!  @param[in,out] pu16DutyCycle   : Pointer to duty cycle
//!  @param[in,out] pu32FreqData    : Pointer to Frequency data
//!  @param[in,out] pu8Average      : Pointer to average data
//!  @param[in,out] pboFreqInfo     : Pointer to update bit / direction bit
//!
//!  @param[out]    -
//!
//!  @return        Error Code
//!                 KB_RET_OK               : If reading of channel is successful.
//!                 KB_RET_ERR_INTERNAL     : If reading of channel is unsuccessful.
//!                 KB_RET_ERR_ARG          : If input parameter is not valid.
//!
//!  @remark        This is valid for FI, FSI, MSI only
//**********************************************************************************************************************
extern S16 s16IOS_GetFrequencyFiltered (E_IOS_IO_CHANNEL_TYPE eChannelType, U16 u16Channel,U16* pu16DutyCycle,
                                        U32* pu32FreqData,  U8* pu8Average, BOOLEAN* pboFreqInfo );

#endif //* IOS_CPU04_I_H */
//** EndOfFile *********************************************************************************************************
