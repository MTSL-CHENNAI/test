//**********************************************************************************************************************
//
//                                                  ios_filt.c
//
//**********************************************************************************************************************
//
//                                        Copyrights(c) by KNORR-BREMSE,
//                                         Rail Vehicle Systems, Munich
//
//! @project   IBC
//! @date      2023-12-13
//! @author    C. Brancolini
//
//**********************************************************************************************************************
//! @file   ios_filt.c
//! @brief General implementation of filter functions for Service IOS.
//
//**********************************************************************************************************************
//
// History
// Date         Author        Changes
// 2010-05-07   A. Tenkeu     Start.
// 2010-07-16   C. Baeuml     Update of functions boIOSGetBIRaw() and boIOSGetFIBinRaw()
// 2010-07-30   C. Baeuml     Code review; comments.
// 2010-08-04   C. Baeuml     Comment.
// 2010-08-19   A. Tenkeu     generalization of the filter functions boIOSGetBIRaw(),boIOSGetFIBinRaw() IOSFinSample()
//                            and IOSFilterFin50().
// 2010-08-23   A. Tenkeu     Rename IOSFilterFin50()with IOSFilterFin50ms(). Rename IOSFinSample() with
//                            IOSFinSample10ms().
// 2010-08-30   C. Baeuml     Redesign FIN filter.
// 2010-09-06   C. Baeuml     Rename functions due to Naming conventions in working instructions  AA 4-142.
// 2011-03-31   C. Baeuml     Optimization of FI filter due to EMC results.
// 2011-04-05   C. Baeuml     Handlig of boIOSFinUptodate[] in IOSCycl50msFinFilter(); 0 Hz detection.
// 2011-05-16   C. Baeuml     Rework for slowing down diagnosis for binary inputs. Only one channel per test cycle.
//                            Error counter introduced.
// 2011-06-29   C. Baeuml     New global data boIOSBIErrStatus[], u32IOSFIBinInputs[].
// 2011-07-26   C. Baeuml     Global data changed to u16IOSBIErrStatus, u16IOSFIBinInputs.
// 2011-09-13   C. Baeuml     Correction in boIOSGetFIBinRaw().
// 2011-09-16   C. Baeuml     Mapping of new variables u32IOSRawBIInputs, u32IOSRawFIBinInputs.
// 2012-03-04   A. Mauro      Changed setting of groupped BI-FIbin errors
// 2012-12-07   A. Mauro      Added variables u16IOSCfgFiltBIErrSect and u16IOSCfgFiltFIErrSect
// 2014-01-20   A. Mauro      Corrected bug in BI diagnostic (TC_005-26)
// 2014-05-12   A. Mauro      Corrected bug in BI diagnostic (TC_005-32 & TC_005-33)
// 2014-05-29   A. Mauro      Corrected bug boIOSGetBIRaw() and  boIOSGetFIBinRaw() in test mode
// 2016-07-12   R. Palsule    LAD01_BSW_V02.62 is taken for reference renamed include files:ios_i.h, ios_s.h
//                            edited boIOSFinUptodate update part in function IOSCycl10msFinFilter,
//                            removed FMN related part.
// 2017-07-06   R. Palsule    Updated as per new coding guidelines
// 2017-11-01   R. Palsule    Replaced Updated variable names
// 2018-01-10   S. Kumbhar    Service OS parameters updated code as per Coding guidelines
// 2018-02-09   R. Palsule    BC0025-28: Removed old ios_hal.h dependency
// 2018-09-21   R. Palsule    BC0025-61: Adapted to kb_ret.h
// 2019-05-10   R. Dongre     cIOS_FinFiltered[] renamed to acIOS_FinFiltered[]
// 2019-12-13   A. Mauro      Corrected bug in boIOS_GetBiRaw for BI diagnostic (set to unknown when BI = LOW)
// 2020-02-12   A. Mauro      Lint clean ups
// 2020-04-03   A. Mauro      Renamed boIOS_FinUptodate -> aboIOS_FinUptodate
// 2021-09-14   N. Jadhav     GenCA V07.00 adaptation changes.
// 2023-01-09   J. Lulli      Coding guidelines alignment
// 2023-03-13   P. Nikam      GenCA V07.06 adaptation changes.
// 2023-12-13   C. Brancolini Lint Plus clean up
//
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "os.h"                           // Contains boOS_ActivateFct
#include "ios_i.h"                        // Internal interface IOS.
#include "ios_s.h"                        // System interface IOS.
#include "ios_hal_cpu04.h"
#include "ios_cpu04_i.h"
#include "ios_board_s.h"
#include "fim.h"
#include "ios_cpu04_s.h"
//**************************************** Constant / macro definitions ( #define ) ************************************

//! @name Definitions for Frequency input filter
//! @{
#define IOS_FI_BUFFER_SIZE            ((U8)0x08U)                 //!< Number of Samples to be stored.
#define IOS_BAD_FREQUENCY             ((U32)0x00FFFFFFUL)         //!< Value to mark bad sample.
#define IOS_ERR_SUSPECT_MAX           ((U8)0x0AU)                 //!< Maximum value for err counter to set error.
#define IOS_BI_DIAG_TIMER_INIT        ((U8)0x0AU)                 //!< Advance of time slices for counter.
#define IOS_FILT_BITMASK16            ((U16)1)
#define IOS_FILT_BITMASK32            ((U32)1)
#define IOS_FI_FILTER_LENGTH          ((U8)3)                     //!< Filter length for frequency in
//! @}
//**************************************** Type definitions ( typedef ) ************************************************
//! Type definition for the states of the IOS binary sampling state machines.
typedef enum
{
    eIOS_BI_SAMPLE_NORMAL,                                       //!< Normal sampling of the binary signals
    eIOS_BI_SAMPLE_TEST                                          //!< Set the BI test signals
} E_IOS_BI_SAMPLE_STATES;

//**************************************** Global data definitions *****************************************************
//! @name Binary input filter variables
//! @{
//! Filter output for BIs. Global variable containing the evaluated input bits after 10 samples. For bit mapping see
//!  logical channel masks #IOS_MASK_CHAN1 etc.

// Inhibit lint message 552. The variable is accessed by eLad0x module
//lint -save -e552
U32 u32IOS_FltBiInputs = 0; // @suppress("Avoid Global Variables")
//lint -restore

//! Filter output for binary configured FIs. Global variable containing the evaluated input bits after 10 samples.
//! For bit mapping see logical channel masks #IOS_MASK_CHAN1 etc.

// Inhibit lint message 552. The variable is accessed by eLad0x module
//lint -save -e552
U32 u32IOS_FltFiBinInputs = 0; // @suppress("Avoid Global Variables")
//lint -restore

//! @}

//! @name Frequency input filter variables
//! @{
//! FIN raw data from last driver call. Index is logical channel.
static C_IOS_U32_U8  cIOS_FinRaw[IOS_MAX_NUMBER_FI];  // @suppress("Wrong prefix") @suppress("Avoid Global Variables")

//! FIN filtered data. Index is logical channel.
C_IOS_U32_U8  acIOS_FinFiltered[IOS_MAX_NUMBER_FI]; // @suppress("Avoid Global Variables")

//! FIN up to date flag. Index is logical channel.
BOOLEAN aboIOS_FinUptodate[IOS_MAX_NUMBER_FI]; // @suppress("Avoid Global Variables")
//! @}

//**************************************** Global constant definitions ( const ) ***************************************

//**************************************** Module global data segment ( static ) ***************************************
static U32 u32IOS_BiErrorSet = 0;                               //!< Binary Input error set
static U32 u32IOS_FiBinErrorSet = 0;                            //!< Frequency (binary) Input error set

static BOOLEAN boIOS_BiSetUnknownError = TRUE;                  //!< Binary Input set UNKOWN
static BOOLEAN boIOS_FiBinSetUnknownError = TRUE;               //!< Frequency (binary) Input set UNKOWN

//! @name Binary input filter variables
//! @{
static BOOLEAN boIOS_CyclBinFiltFuncActivated = FALSE;          //!< Flag for activated cyclic filter functions.
static BOOLEAN aboIOS_BiFilterActivated[IOS_MAX_NUMBER_BI];      //!< Flags for channel activation of BI filter.
static BOOLEAN aboIOS_FiBinFilterActivated[IOS_MAX_NUMBER_FI];   //!< Flags for channel activation of FIbin filter.
static BOOLEAN aboIOS_BiInputs[IOS_MAX_NUMBER_BI];               //!< Raw values of BIs.
static BOOLEAN aboIOS_FiBinInputs[IOS_MAX_NUMBER_FI];            //!< Raw values of binary FIs.

//! Each element contains the sum of high states of corresponding BI channel.
static U8 au8IOS_BiCounter[IOS_MAX_NUMBER_BI];

//! Each element contains the sum of high states of corresponding FIbin channel.
static U8 au8IOS_FiBinCounter[IOS_MAX_NUMBER_FI];

//! Mask for test execute at list once on BI channel.
static U16 u16IOS_BiTestExecutedMask = 0;

//! Mask for test execute at list once on FIbin channel.
static U16 u16IOS_FiBinTestExecutedMask = 0;
//! @}

//! @name Frequency input filter variables
//! @{
static BOOLEAN aboIOS_FinFilterActivated[IOS_MAX_NUMBER_FI];         //!< Flags for channel activation of BI filter.
static U32 au32IOS_FinBuffer[IOS_MAX_NUMBER_FI][IOS_FI_BUFFER_SIZE]; //!< Buffer for FIN raw data for all channels.

//! Index to write next sample into Buffer u32IOSFinData[][]. Index used for all channels.
static U8 u8IOS_FinSampleIndex = 0;



static void vIOSBIFMNInit ( U16 u16Channel );
static void vIOSFIBinFMNInit ( U16 u16Channel );
// FMN part is removed for now
//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfHeader *********************************************************************************************************


// Function boIOS_InitBiFilt
//**********************************************************************************************************************
BOOLEAN boIOS_InitBiFilt ( U16 u16Channel )
{
//************************************************ Function scope data *************************************************
    BOOLEAN boReturn; // Return value of function.

//*************************************** Function scope static data declaration ***************************************

//*************************************************** Function code ****************************************************
    // Check if BI channel is available
    if (u16Channel < u8IOS_CfgFiltNumberOfBi)
    {
        // Init FMN error
        vIOSBIFMNInit( u16Channel );
        aboIOS_BiFilterActivated[u16Channel] = TRUE;
        // Check If Cyclic filter function is activated before
        if (boIOS_CyclBinFiltFuncActivated == (BOOLEAN)TRUE)
        {
            boReturn = TRUE;
        }
        //Activate Cyclic filter function
        else
        {
            // Inhibit lint warning 466 and note 9074 due to a missing void in boOS_ActivateFct declaration
            //lint -save -e466 -e9074
            boReturn = boOS_ActivateFct( vIOS_Cycl50msBinFilter, (U8)eOS_SLICE_50MS );
            boReturn &= boOS_ActivateFct( vIOS_Cycl5msBinFilter, (U8)eOS_SLICE_5MS );
            //lint -restore

            boIOS_CyclBinFiltFuncActivated = boReturn;
        }
    }
    // Error: if Channel not available.
    else
    {
        boReturn = FALSE;
    }

    return (boReturn);
}
//** EndOfFunction boIOS_InitBiFilt*************************************************************************************

// Function boIOS_InitFIBinFilt
//**********************************************************************************************************************
BOOLEAN boIOS_InitFIBinFilt ( U16 u16Channel )
{
//************************************************ Function scope data *************************************************
    BOOLEAN boReturn; // Return value of function.

//*************************************** Function scope static data declaration ***************************************

//*************************************************** Function code ****************************************************
    // Check if FI channel is available
    if (u16Channel < u8IOS_CfgFiltNumberOfFi)
    {
        // Init FMN error
        vIOSFIBinFMNInit ( u16Channel );
        aboIOS_FiBinFilterActivated[u16Channel] = TRUE;
        // Check If Cyclic filter function is activated before
        if (boIOS_CyclBinFiltFuncActivated == (BOOLEAN)TRUE)
        {
            boReturn = TRUE;
        }
        //Activate Cyclic filter function
        else
        {
            // Inhibit lint warning 466 and note 9074 due to a missing void in boOS_ActivateFct declaration
            //lint -save -e466 -e9074
            boReturn = boOS_ActivateFct( vIOS_Cycl50msBinFilter,(U8)eOS_SLICE_50MS );
            boReturn &= boOS_ActivateFct( vIOS_Cycl5msBinFilter, (U8)eOS_SLICE_5MS );
            //lint -restore

            boIOS_CyclBinFiltFuncActivated = boReturn;
        }
    }
    // Error: if Channel not available.
    else
    {
        boReturn = FALSE;
    }

    return (boReturn);
}
//** EndOfFunction boIOS_InitFIBinFilt**********************************************************************************

// Function boIOS_InitFIFilt
//**********************************************************************************************************************
BOOLEAN boIOS_InitFIFilt ( U16 u16Channel )
{
//************************************************ Function scope data *************************************************
    BOOLEAN boReturn; // Return value of function.

//*************************************** Function scope static data declaration ***************************************
    static BOOLEAN boCyclicFunctionsActivated = FALSE; // Static variable to check if cyclic filter function
                                                       // has been activated, initialized at false.
//*************************************************** Function code ****************************************************
    // Check if FI channel is available
    if (u16Channel < u8IOS_CfgFiltNumberOfFi)
    {
        aboIOS_FinFilterActivated[u16Channel] = TRUE;
        // Check If Cyclic filter function is activated before
        if (boCyclicFunctionsActivated == (BOOLEAN)TRUE)
        {
            boReturn = TRUE;
        }
        //Activate Cyclic filter function
        else
        {
            // Inhibit lint warning 466 and note 9074 due to a missing void in boOS_ActivateFct declaration
            //lint -save -e466 -e9074
            boReturn = boOS_ActivateFct( vIOS_Cycl50msFinFilter, (U8)eOS_SLICE_50MS );
            boReturn &= boOS_ActivateFct( vIOS_Cycl10msFinFilter, (U8)eOS_SLICE_10MS );
            //lint -restore

            boCyclicFunctionsActivated = boReturn;
        }
    }
    // Error: if Channel not available.
    else
    {
        boReturn = FALSE;
    }

    return (boReturn);
}
//** EndOfFunction boIOS_InitFIFilt*************************************************************************************

// Function boIOS_GetBiRaw
//**********************************************************************************************************************
BOOLEAN boIOS_GetBiRaw( BOOLEAN* pboInputs )
{
    //************************************************ Function scope data *********************************************
    BOOLEAN boReturn = TRUE;                // Return value of function.
    BOOLEAN boInput = FALSE;                // Input value of current channel.
    E_IOS_INPUT_STATUS eStatus;             // Input status.
    S16 s16HALReturn;                       // Return value of HAL.
    U16 u16Channel;                         // Logical channel number
    //*************************************** Function scope static data declaration ***********************************
    static E_IOS_BI_SAMPLE_STATES eSample_State = eIOS_BI_SAMPLE_NORMAL;
    static U8  au8ErrSuspect[IOS_MAX_NUMBER_BI] = { 0 };      // Err suspect counter.
    static U32 u32SkipTest = 0;                             // Skip test of BI
    static U32 u32SumErrorMask = 0;                         // Mask for sum error
    static U16 u16SliceCounter = IOS_BI_DIAG_TIMER_INIT;    // Gives time delay between BI and FI bin test.
    static U16 u16TestChannel = 0;              // Logical channel number.
    //*************************************************** Function code ************************************************
    // Note:
    // Exception is made for code complexity (V(G)), this function has complexity 27, max allowed is 15.
    // Exception is made for max allowed nesting (MaxND), this function has nesting 8, max allowed is 5.
    // Exception is made for max number of program lines, this function has 152, max allowed is 150.
    // Separating code will reduce understandability and readability.
    // Sample all configured BI channels.
    for (u16Channel = 0 ; u16Channel < u8IOS_CfgFiltNumberOfBi; u16Channel++)
    {
        // Check if the filter is active for the current channel
        if ( aboIOS_BiFilterActivated[u16Channel] == (BOOLEAN)TRUE )
        {
            // Filter is active, get the BI
            s16HALReturn = s16IOS_HAL_GetBinary( eIOS_BI, u16Channel, &boInput, &eStatus );
            if( s16HALReturn == (S16) KB_RET_OK )
            {
                boReturn &= (BOOLEAN)TRUE;
            }
            // Return BI value via pboInputs pointer
            pboInputs[u16Channel] = boInput; // @suppress("Not using boolean macros")
        }
    }
    // State machine for sampling and test.
    switch (eSample_State)
    {
        case eIOS_BI_SAMPLE_NORMAL :
        {
            if (++u16SliceCounter > u16IOS_CfgFiltDiagTimer)
            {
                u16SliceCounter = 0;
                // Set test channel to test mode.
                if ( aboIOS_BiFilterActivated[u16TestChannel] == (BOOLEAN)TRUE )
                {
                    // In input to be tested is active
                    if (pboInputs[u16TestChannel] == (BOOLEAN)TRUE)
                    {
                        u32SkipTest &= ~((U32) IOS_BI_ERROR_MASK << u16TestChannel);
                        //eIOS_BI_DIAG
                        s16HALReturn = s16IOS_HAL_SetBIDiag ( u16TestChannel, TRUE );
                        if (s16HALReturn == (S16) KB_RET_OK)
                        {
                            boReturn &= (BOOLEAN) TRUE;
                        }
                        // Switch to test state for next cycle.
                        eSample_State = eIOS_BI_SAMPLE_TEST;
                    }
                    else
                    {
                        u32SkipTest |= (IOS_FILT_BITMASK32 << u16TestChannel);
                        // Switch to test state for next cycle.
                        eSample_State = eIOS_BI_SAMPLE_TEST;
                    }
                }
            }
            break;
        }
        case eIOS_BI_SAMPLE_TEST :
        {
            // If test must be executed (Input was  High)
            if ((u32SkipTest & (IOS_FILT_BITMASK32 << u16TestChannel)) == 0U)
            {
                // Sample BI channel to test for diagnosis.
                if ( aboIOS_BiFilterActivated[u16TestChannel] == (BOOLEAN)TRUE )
                { // Channel activated. Sample input for test.
                    // Set test execute on channel x
                    u16IOS_BiTestExecutedMask |= (U16)(IOS_FILT_BITMASK16 << u16TestChannel);//lint !e701 correct bit mask
                    boInput = pboInputs[u16TestChannel]; // @suppress("Not using boolean macros")
                    // Set normal mode for signal, because sampling for diagnosis already made.
                    //eIOS_BI_DIAG
                    s16HALReturn = s16IOS_HAL_SetBIDiag ( u16TestChannel, FALSE );
                    if (s16HALReturn == (S16) KB_RET_OK)
                    {
                        boReturn &= (BOOLEAN) TRUE;
                    }
                    // In TEST_MODE input signal should be low.
                    if ( boInput == (BOOLEAN)TRUE )
                    { // Error: Stuck at high level. -----------------------------------
                        if (au8ErrSuspect[u16TestChannel] >= IOS_ERR_SUSPECT_MAX)
                        {
                            if ( boIOS_CfgFiltBiSumErr == (BOOLEAN)TRUE )
                            { // Sum Error Mode configured.
                                u32IOS_BiErrorSet |= (U32)IOS_BI_ERROR_MASK << u16TestChannel;
                            }
                            else
                            { // Channel Error Mode configured.
                                (void) s16FIM_SetFault( (U8) ( u16IOS_CfgFiltBiErrCode + u16TestChannel ), IOS_ID);
                            }
                        }
                        else
                        { // Mark channel as suspicious.
                            au8ErrSuspect[u16TestChannel]++;
                        }
                    }
                    else
                    { // Signal ok, reset error. ---------------------------------------
                        au8ErrSuspect[u16TestChannel] = 0; // Suspicion cleared for channel.
                        u32IOS_BiErrorSet &= ~( (U32)IOS_BI_ERROR_MASK << u16TestChannel);

                        if ( boIOS_CfgFiltBiSumErr == (BOOLEAN)FALSE )
                        { // Channel Error Mode configured.
                            (void) s16FIM_ResetFault( (U8) ( u16IOS_CfgFiltBiErrCode + u16TestChannel ), IOS_ID);
                        }
                    }
                }
                // Force status of signal under test to TRUE
                pboInputs[u16TestChannel] = TRUE;
            }
            else
            {
                if ( boIOS_CfgFiltBiSumErr == (BOOLEAN)FALSE )
                {
                    // Set error UNKOWN
                    (void) s16FIM_SetToUnknownFault( (U8) ( u16IOS_CfgFiltBiErrCode + u16TestChannel ), IOS_ID);
                }
            }
            // Handling of channel number, flags and Sum Error Mode ------------------
            if ( u16TestChannel < ( (U16)u8IOS_CfgFiltNumberOfBi - 1U) ) // @suppress("No magic numbers")
            {
                u32SumErrorMask = (U32)( u32SumErrorMask | (IOS_FILT_BITMASK16 << u16TestChannel) );
                // Switch channel for next test.
                u16TestChannel++;
            }
            else
            {

                u32SumErrorMask = (U32)( u32SumErrorMask | (IOS_FILT_BITMASK16 << u16TestChannel) );
                // Begin with first channel for next test.
                u16TestChannel = 0;
                // Fault management for Sum Error Mode. --------------------------------
                if ( ( boIOS_CfgFiltBiSumErr == (BOOLEAN)TRUE ) && (u16IOS_BiTestExecutedMask != 0U))
                {
                    // If test must be executed (Input was  High)
                    if (u32SkipTest != u32SumErrorMask)
                    {
                        // Reset Unknwon error flag for BI
                        boIOS_BiSetUnknownError = FALSE;
                        if ( u32IOS_BiErrorSet != 0U )
                        {
                            (void) s16FIM_SetFault( (U8) u16IOS_CfgFiltBiErrCode, IOS_ID);
                        }
                        else
                        {
                            // If no FI input error or error BI-FI to be set is different
                            if( (u32IOS_FiBinErrorSet == 0U) || (u16IOS_CfgFiltBiErrCode != u16IOS_CfgFiltFiErrCode) )
                            {
                                (void) s16FIM_ResetFault( (U8) u16IOS_CfgFiltBiErrCode, IOS_ID);
                            }
                        }
                    }
                    else
                    {
                        // Set Unknwon error flag for BI
                        boIOS_BiSetUnknownError = TRUE;
                        // If BI want to set unknown or if error to be set are different
                        if ((boIOS_FiBinSetUnknownError == (BOOLEAN)TRUE) ||
                                (u16IOS_CfgFiltBiErrCode != u16IOS_CfgFiltFiErrCode))
                        {
                            // Set error UNKOWN
                            (void) s16FIM_SetToUnknownFault( (U8) u16IOS_CfgFiltBiErrCode, IOS_ID);
                        }
                    }
                }
            }
            // Switch back to normal sampling in next slice
            eSample_State = eIOS_BI_SAMPLE_NORMAL;
            break;
        }
        default:
        {
            boReturn = FALSE;
            break;
        }
    }

    return (boReturn);
}
//** EndOfFunction boIOS_GetBiRaw***************************************************************************************

// Function boIOS_GetFIBinRaw
//**********************************************************************************************************************
BOOLEAN boIOS_GetFIBinRaw( BOOLEAN* pboInputs )
{
//************************************************ Function scope data *************************************************
    BOOLEAN boReturn = TRUE;                // Return value of function.
    BOOLEAN boInput = FALSE;                // Input value of current channel.
    E_IOS_INPUT_STATUS eStatus;             // Input status.
    S16 s16HALReturn;                       // Return value of HAL.
    U16 u16Channel;                         // Logical channel number.
//*************************************** Function scope static data declaration ***************************************
    static E_IOS_BI_SAMPLE_STATES eSample_State = eIOS_BI_SAMPLE_NORMAL;
    static U8  au8ErrSuspect[IOS_MAX_NUMBER_FI] = { 0 } ;   // Err suspect counter.
    static U32 u32SkipTest = 0;                           // Skip test of BI
    static U32 u32SumErrorMask = 0;                       // Mask for sum error
    static U16 u16SliceCounter = 0;
    static U16 u16TestChannel = 0;                        // Logical channel number.

//*************************************************** Function code ****************************************************
    // Note:
    // Exception is made for code complexity (V(G)), this function has complexity 27, max allowed is 15.
    // Exception is made for max allowed nesting (MaxND), this function has nesting 8, max allowed is 5.
    // Exception is made for max number of program lines, this function has 153, max allowed is 150.
    // Separating code will reduce understandability and readability.

    // Sample all configured FIbin channels.
    for (u16Channel = 0 ; u16Channel < u8IOS_CfgFiltNumberOfFi; u16Channel++)
    {
        // Check if the filter for the current channel is active
        if ( aboIOS_FiBinFilterActivated[u16Channel] == (BOOLEAN)TRUE )
        {
            // Get FI
            s16HALReturn = s16IOS_HAL_GetBinary( eIOS_FI, u16Channel, &boInput, &eStatus );
            if ( s16HALReturn == (S16) KB_RET_OK )
            {
                boReturn &= (BOOLEAN) TRUE;
            }
            // Return the FI value via pboInputs pointer
            pboInputs[u16Channel] = boInput; // @suppress("Not using boolean macros")
        }
    }

    // State machine for sampling and test
    switch (eSample_State)
    {
        case eIOS_BI_SAMPLE_NORMAL :
        {
            if (++u16SliceCounter > u16IOS_CfgFiltFiBinDiagTimer)
            {
                u16SliceCounter = 0;
                // Set test channel to test mode.
                if ( aboIOS_FiBinFilterActivated[u16TestChannel] == (BOOLEAN)TRUE )
                {
                    // In input to be tested is active
                    if (pboInputs[u16TestChannel] == (BOOLEAN)TRUE)
                    {
                        u32SkipTest &= ~((U32) IOS_BI_ERROR_MASK << u16TestChannel);
                        //eIOS_FI_DIAG
                        s16HALReturn = s16IOS_HAL_SetFIDiag ( u16TestChannel, TRUE );
                        if (s16HALReturn == (S16) KB_RET_OK)
                        {
                            boReturn &= (BOOLEAN) TRUE;
                        }
                        eSample_State = eIOS_BI_SAMPLE_TEST; // Switch to test state for next cycle.
                    }
                    else
                    {
                        u32SkipTest = (U32)( u32SkipTest | (IOS_FILT_BITMASK16 << u16TestChannel) );//lint !e701 correct bit mask
                        eSample_State = eIOS_BI_SAMPLE_TEST; // Switch to test state for next cycle.
                    }
                }
            }
            break;
        }
        case eIOS_BI_SAMPLE_TEST :
        {
            // If test must be executed (Input was  High)
            if ( (U32)( u32SkipTest & ( IOS_FILT_BITMASK16 << u16TestChannel ) ) == 0U)//lint !e701 correct bit mask
            {
                // Sample all configured FIbin channels for diagnosis.
                if ( aboIOS_FiBinFilterActivated[u16TestChannel] == (BOOLEAN)TRUE )
                { // Channel activated. Sample input for test.
                  // Set test execute on channel x
                    u16IOS_FiBinTestExecutedMask |= (U16)(IOS_FILT_BITMASK16 << u16TestChannel);//lint !e701 correct bit mask
                    boInput = pboInputs[u16TestChannel]; // @suppress("Not using boolean macros")
                    // Set normal mode for signal, because sampling for diagnosis already made.
                    //eIOS_FI_DIAG
                    s16HALReturn = s16IOS_HAL_SetFIDiag ( u16TestChannel, FALSE );
                    if (s16HALReturn == (S16) KB_RET_OK)
                    {
                        boReturn &= (BOOLEAN) TRUE;
                    }

                    // In TEST_MODE input signal should be low.
                    if ( boInput == (BOOLEAN)TRUE )
                    { // Error: Stuck at high level. -----------------------------------
                        if (au8ErrSuspect[u16TestChannel] >= IOS_ERR_SUSPECT_MAX)
                        {
                            if ( boIOS_CfgFiltFiSumErr == (BOOLEAN)TRUE )
                            { // Sum Error Mode configured.
                                u32IOS_FiBinErrorSet =
                                        (U32)( u32IOS_FiBinErrorSet | (IOS_BI_ERROR_MASK << u16TestChannel) );//lint !e701 correct bit mask
                            }
                            else
                            { // Channel Error Mode configured.
                                (void) s16FIM_SetFault( (U8) ( u16IOS_CfgFiltFiErrCode + u16TestChannel ), IOS_ID);
                            }
                        }
                        else
                        { // Mark channel as suspicious.
                            au8ErrSuspect[u16TestChannel]++;
                        }
                    }
                    else
                    { // Signal ok, reset error. ---------------------------------------
                        au8ErrSuspect[u16TestChannel] = 0; // Suspicion cleared for channel.
                        u32IOS_FiBinErrorSet &= ~((U32) IOS_BI_ERROR_MASK << u16TestChannel);

                        if ( boIOS_CfgFiltFiSumErr == (BOOLEAN)FALSE )
                        { // Channel Error Mode configured.
                          (void) s16FIM_ResetFault( (U8) ( u16IOS_CfgFiltFiErrCode + u16TestChannel ), IOS_ID);
                        }
                    }
                }
                // Force status of signal under test to TRUE
                pboInputs[u16TestChannel] = TRUE;
            }
            else
            {
                if ( boIOS_CfgFiltFiSumErr == (BOOLEAN)FALSE )
                {
                    // Set error UNKOWN
                    (void) s16FIM_SetToUnknownFault( (U8) ( u16IOS_CfgFiltFiErrCode + u16TestChannel ), IOS_ID);
                }
            }

            // Handling of channel number, flags and Sum Error Mode ------------------
            if ( u16TestChannel < ( (U16)u8IOS_CfgFiltNumberOfFi - 1U) ) // @suppress("No magic numbers")
            {
                u32SumErrorMask |= (IOS_FILT_BITMASK32 << u16TestChannel);
                // Switch channel for next test.
                u16TestChannel++;
            }
            else
            {
                u32SumErrorMask |= (IOS_FILT_BITMASK32 << u16TestChannel);
                // Begin with first channel for next test.
                u16TestChannel = 0;
                // Fault management for Sum Error Mode. --------------------------------
                if ( ( boIOS_CfgFiltFiSumErr == (BOOLEAN)TRUE ) && (u16IOS_FiBinTestExecutedMask != 0U))
                {
                    // If test must be executed (Input was  High)
                    if (u32SkipTest != u32SumErrorMask)
                    {
                        // Reset Unknwon error flag for FiBIN
                        boIOS_FiBinSetUnknownError = FALSE;
                        if ( u32IOS_FiBinErrorSet != 0U )
                        {
                            (void) s16FIM_SetFault( (U8) u16IOS_CfgFiltFiErrCode, IOS_ID);
                        }
                        else
                        {
                            // If no BI input error or error BI-FI to be set is different
                            if ( ( u32IOS_BiErrorSet == 0U ) || ( u16IOS_CfgFiltBiErrCode != u16IOS_CfgFiltFiErrCode ) )
                            {
                                (void) s16FIM_ResetFault( (U8) u16IOS_CfgFiltFiErrCode, IOS_ID);
                            }
                        }
                    }
                    else
                    {
                        // Set Unknwon error flag for FiBIN
                        boIOS_FiBinSetUnknownError = TRUE;
                        // If BI want to set unkown or if error to be set are different
                        if ((boIOS_BiSetUnknownError == (BOOLEAN)TRUE) ||
                                (u16IOS_CfgFiltBiErrCode != u16IOS_CfgFiltFiErrCode))
                        {
                            // Set error UNKOWN
                            (void) s16FIM_SetToUnknownFault( (U8) u16IOS_CfgFiltFiErrCode, IOS_ID);
                        }
                    }
                }
                u32SumErrorMask = 0;
            }
            // Switch back to normal sampling in next slice.
            eSample_State = eIOS_BI_SAMPLE_NORMAL;
            break;
        }
        default:
        {
            boReturn = FALSE;
            break;
        }
    }

    return (boReturn);
}
//** EndOfFunction boIOS_GetFIBinRaw************************************************************************************

// Function vIOS_Cycl5msBinFilter
//**********************************************************************************************************************
void vIOS_Cycl5msBinFilter (void)
{
//************************************************ Function scope data *************************************************
    U16 u16Channel;                     // Logical channel number.
//*************************************** Function scope static data declaration ***************************************

//*************************************************** Function code ****************************************************
    (void)boIOS_GetBiRaw(aboIOS_BiInputs);             //Read raw values of BIs

    (void)boIOS_GetFIBinRaw(aboIOS_FiBinInputs);       //Read raw values of binary configured FIs

    // Fill arrays according to sampled values
    for (u16Channel = 0; u16Channel < u8IOS_CfgFiltNumberOfBi; u16Channel++)
    {
        //Each byte contains the sum of high states of corresponding inp.
        au8IOS_BiCounter[u16Channel] += aboIOS_BiInputs[u16Channel];
    }
    // Increment each byte in the array if input state is high.
    for (u16Channel = 0; u16Channel < u8IOS_CfgFiltNumberOfFi; u16Channel++)
    {
        // Each byte contains the sum of high states of corresponding inp.
        au8IOS_FiBinCounter[u16Channel] += aboIOS_FiBinInputs[u16Channel];
    }
    // Increment each byte in the array if input state is high.
}
//** EndOfFunction vIOS_Cycl5msBinFilter********************************************************************************

// Function vIOS_Cycl50msBinFilter
//**********************************************************************************************************************
void vIOS_Cycl50msBinFilter(void)
{
//************************************************ Function scope data *************************************************
    U16 u16Channel;                     // Logical channel.
    U32 u32ChannelMask;                // Logical channel mask.
//*************************************** Function scope static data declaration ***************************************

//*************************************************** Function code ****************************************************

    u32ChannelMask = IOS_FILT_BITMASK32;
    for (u16Channel = 0 ; u16Channel < u8IOS_CfgFiltNumberOfBi; u16Channel++)
    {
        // If the number of high states is bigger than 35(7) during 50(10) samples, set this bit, otherwise reset it.
        if ( au8IOS_BiCounter[u16Channel] > u8IOS_CfgFiltBiNumOfHighStates )
        {
            // Set input status
            u32IOS_FltBiInputs |= u32ChannelMask; //lint !e552 u32IOS_FltBiInputs accessed by eLad0x module
        }
        else
        {
            // Reset input status
            u32IOS_FltBiInputs &= ~u32ChannelMask; //lint !e552 u32IOS_FltBiInputs accessed by eLad0x module
        }

        // Prepare mask with raw values.
        au8IOS_BiCounter[u16Channel] = 0;
        // Reset bit sum for next sampling
        u32ChannelMask <<= 1; // @suppress("No magic numbers")
    }
    // Switch to next channel.

    u32ChannelMask = IOS_FILT_BITMASK32;
    for (u16Channel = 0 ; u16Channel < u8IOS_CfgFiltNumberOfFi; u16Channel++)
    {
        // If the number of high states is bigger than configured limit. during 50(10) samples, set this bit,
        // otherwise reset it.
        if ( au8IOS_FiBinCounter[ u16Channel ] > u8IOS_CfgFiltBiNumOfHighStates )
        {
            // Set input status
            u32IOS_FltFiBinInputs |= u32ChannelMask; //lint !e552 u32IOS_FltFiBinInputs accessed by eLad0x module
        }
        else
        {
            // Reset input status
            u32IOS_FltFiBinInputs &= ~u32ChannelMask; ///lint !e552  u32IOS_FltFiBinInputs accessed by eLad0x module
        }

        // Prepare mask with raw values.
        au8IOS_FiBinCounter[u16Channel] = 0;
        // Reset bit sum for next sampling
        u32ChannelMask <<= 1; // @suppress("No magic numbers")
    }
    // Switch to next channel.
}
//** EndOfFunction vIOS_Cycl50msBinFilter*******************************************************************************

// Function vIOS_Cycl10msFinFilter
//**********************************************************************************************************************
void vIOS_Cycl10msFinFilter (void)
{
//************************************************ Function scope data *********************************************
    S16 s16HALReturn;                       // Return value of HAL
    U16 u16Channel;                         // Logical channel number
    U16 u16FIDutyCycle;                     // Duty cycle of the frequency sensor input
    U8 u8Average;
    E_IOS_FREQ_DIR eFreqInfo;               // Frequency sensor input direction
    E_IOS_INPUT_STATUS eStatus;             // Input status

//*************************************************** Function code ************************************************

    // For each filtered Frequency Input
    for (u16Channel = 0 ; u16Channel < u8IOS_CfgFiltNumberOfFi; u16Channel++)
    {
        // Check if frequency input filter is activated
        if ( aboIOS_FinFilterActivated[u16Channel] == (BOOLEAN)TRUE )
        {
            // Get frequency data
            // Inhibit lint message 728 "static variable not explicitly initialized":
            // BSS segment is initialized to 0 at startup.
            //lint -save -e728
            s16HALReturn = s16IOS_HAL_GetFrequency ( eIOS_FI, u16Channel, &u16FIDutyCycle,
                &cIOS_FinRaw[u16Channel].u32Value,  &u8Average, &eFreqInfo, &eStatus );
            //lint -restore
            // Check return value
            if (s16HALReturn >= (S16)KB_RET_OK)
            {
                // No error. Write to buffer.
                au32IOS_FinBuffer[u16Channel][u8IOS_FinSampleIndex] = cIOS_FinRaw[u16Channel].u32Value;
                if ( s16HALReturn == (S16) IOS_HAL_UP_TO_DATE )
                { // Set update flag. Will be reset after value was used.
                    aboIOS_FinUptodate[u16Channel] = TRUE;
                }
            }
            else
            {
                // Error. Mark bad sample.
                au32IOS_FinBuffer[u16Channel][u8IOS_FinSampleIndex] = IOS_BAD_FREQUENCY;
                aboIOS_FinUptodate[u16Channel] = FALSE;
            }
        }
    }
    // Prepare for next call
    u8IOS_FinSampleIndex++;
    if (u8IOS_FinSampleIndex >= IOS_FI_BUFFER_SIZE)
    {
        u8IOS_FinSampleIndex = 0;
    }
    // Only the last IOS_FI_BUFFER_SIZE values will be stored (0...x)

}
//** EndOfFunction vIOS_Cycl50msBinFilter*******************************************************************************

// Function vIOS_Cycl50msFinFilter
//**********************************************************************************************************************
void vIOS_Cycl50msFinFilter (void)
{
//************************************************ Function scope data *********************************************
    U16 u16Channel;    // Logical channel number

//*************************************************** Function code ************************************************

    // For each filtered Frequency Input
    for (u16Channel = 0 ; u16Channel < u8IOS_CfgFiltNumberOfFi; u16Channel++)
    {
        // Check if frequency input filter is activated
        if ( aboIOS_FinFilterActivated[u16Channel] == (BOOLEAN)TRUE )
        {
            // Check if frequency input filter is updated
            if ( aboIOS_FinUptodate[u16Channel] == (BOOLEAN)TRUE )
            {
                // Edges detected during last 50 ms
                // Run filter and update FIN filtered data array (acIOS_FinFiltered) with the result.
                (void)boIOS_FilterFin(&au32IOS_FinBuffer[u16Channel][0], &acIOS_FinFiltered[u16Channel].u32Value);
            }
            else
            {
                // No edges detected during last 50 ms
                // Assume 0 Hz and update FIN filtered data array (acIOS_FinFiltered).
                acIOS_FinFiltered[u16Channel].u32Value = (U32) 0;
            }
        }
    }

}
//** EndOfFunction vIOS_Cycl50msBinFilter*******************************************************************************

// Function boIOS_FilterFin
//**********************************************************************************************************************
BOOLEAN boIOS_FilterFin(const U32* pu32InSamples, U32* pu32FOutput)
{
    //************************************************ Function scope data *********************************************
    BOOLEAN boReturn;
    U8 u8Index;
    U8 u8CycleBufferIndex;
    U8 u8HitCount = 0;                             // counts successful comparisons.
    U8 u8CompCount = 0;                            // counts total number of compare.
    U32 u32Sample1;
    U32 u32Sample2;
    U32 u32SampleSum = 0;                          // Sum for average calculation.
    U32 au32FinSamples[IOS_FI_BUFFER_SIZE];        // Buffer to arrange samples for one FIN channel.
    //*************************************** Function scope static data declaration ***********************************


    //*************************************************** Function code ************************************************
    boReturn = FALSE;
    // if no sample could be found !!!
    *pu32FOutput = IOS_BAD_FREQUENCY;

    u8CycleBufferIndex = u8IOS_FinSampleIndex;
    for (u8Index = 0; u8Index < IOS_FI_BUFFER_SIZE; u8Index++)
    {
        au32FinSamples[ u8Index ] = pu32InSamples[ u8CycleBufferIndex ];
        u8CycleBufferIndex++;
        if (u8CycleBufferIndex >= IOS_FI_BUFFER_SIZE)
        {
            u8CycleBufferIndex = 0; // Copy all values in the right
        }
    }

    // start with newest sample
    u8Index = IOS_FI_BUFFER_SIZE - 1U; // @suppress("No magic numbers")
    while (u8CompCount < ( IOS_FI_BUFFER_SIZE + 2U ) ) // @suppress("No magic numbers")
    {
        // compare F(i) with F(i-1)
        u32Sample1 = au32FinSamples[u8Index];

        if (u8Index == 0U)
        {
            u32Sample2 = au32FinSamples[IOS_FI_BUFFER_SIZE - 1U]; // @suppress("No magic numbers")
            u8Index = IOS_FI_BUFFER_SIZE - 1U; // compare sample0 with sample7 // @suppress("No magic numbers")
        }
        else
        {
            u8Index--;
            u32Sample2 = au32FinSamples[u8Index];
        }
        // compare F(i) with F(i-1)
        if ((u32Sample1 < (u32Sample2 + u16IOS_CfgFiltFreqInputTol))
            && (u32Sample2 < (u32Sample1 + u16IOS_CfgFiltFreqInputTol))
            && (u32Sample1 <= u32IOS_CfgFiltMaxAllowedFreq))
        {
            //limitation: F(i) <= Fmax !!!
            u8HitCount++;
            u32SampleSum += u32Sample1;
            // Sum up hit samples for average
            // calculation.
            if (u8HitCount == IOS_FI_FILTER_LENGTH) // if OK increment hit counter
            { // success if 3 compares are OK
                *pu32FOutput = (u32SampleSum / u8HitCount);
                // Return average of hit samples.
                boReturn =  TRUE; // abort loop, return with success
                break;
            }
        }
        else
        {
            u8HitCount = 0; // reset hit counter
            u32SampleSum = 0; // reset sum for average
        }
        u8CompCount++; // next compare
    }
    return boReturn;
}
//** EndOfFunction vIOS_Cycl50msBinFilter*******************************************************************************

// Function vIOSBIFMNInit
//**********************************************************************************************************************
//!  @brief         initializes the related BI FMN error to UNKNOWN
//!
//!  @param[in]     u16Channel    : channel number
//!  @param[in,out] -
//!  @param[out]    -
//!
//!
//!  @remark        -
//**********************************************************************************************************************
//FMN part is removed for now
static void vIOSBIFMNInit ( U16 u16Channel )
{
//************************************************ Function scope data *********************************************

//*************************************************** Function code ************************************************

    // Initialize BI FMN error to UNKNOWN
    // Check configuration flag boIOS_CfgFiltBiSumErr
    if ( boIOS_CfgFiltBiSumErr == (BOOLEAN)TRUE )
    {
        // Configuration flag at TRUE,
        // use u16IOS_CfgFiltBiErrCode for all channels
        (void) s16FIM_SetToUnknownFault( (U8) u16IOS_CfgFiltBiErrCode, IOS_ID);
    }
    else
    {    // Configuration flag at FALSE,
         // calculate error number for single channel (u16IOS_CfgFiltBiErrCode + u16Channel)
        (void) s16FIM_SetToUnknownFault( (U8)(u16IOS_CfgFiltBiErrCode + u16Channel), IOS_ID);
    }

}

//** EndOfFunction vIOSBIFMNInit****************************************************************************************

// Function vIOSFIBinFMNInit
//**********************************************************************************************************************
//!  @brief         initializes the related BI in binary mode FMN error to UNKNOWN
//!
//!  @param[in]     u16Channel    : channel number
//!  @param[in,out] -
//!  @param[out]    -
//!
//!
//!  @remark        -
//**********************************************************************************************************************
//FMN part is removed for now
static void vIOSFIBinFMNInit ( U16 u16Channel )
{
//************************************************ Function scope data *********************************************

//*************************************************** Function code ************************************************

    // Initialize FI in binary mode FMN error to UNKNOWN
    // Check configuration flag boIOS_CfgFiltFiSumErr
    if ( boIOS_CfgFiltFiSumErr == (BOOLEAN)TRUE )
    {
        // Configuration flag at TRUE,
        // use boIOS_CfgFiltFiSumErr for all channels
        (void) s16FIM_SetToUnknownFault( (U8) u16IOS_CfgFiltFiErrCode, IOS_ID);
    }
    else
    {
        // Configuration flag at FALSE,
        // calculate error number for single channel (u16IOS_CfgFiltFiErrCode + u16Channel)
        (void) s16FIM_SetToUnknownFault( (U8)(u16IOS_CfgFiltFiErrCode + u16Channel), IOS_ID);
    }

}

//** EndOfFunction vIOSFIBinFMNInit*************************************************************************************

//** EndOfFile ios_filt.c **********************************************************************************************
