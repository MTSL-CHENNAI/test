//*****************************************************************************
//
//                                   ios_hal_cpu04.h
//
//*****************************************************************************
//
//                   Copyrights(c) 2022 by KNORR-BREMSE,
//              Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   IBC
//! @date      2024-02-05
//! @author    C. Brancolini
//
//*****************************************************************************
//! @file
//! @brief  Interface for HAL configuration of service IOS
//!         Standard H- file. Board configuration only in CFG_IOS_HAL.C
//*****************************************************************************
// Date       Author      Changes:
// 07.04.10   A. Tenkeu   Start
// 16.07.10   C. Baeuml   MIN_MAX constants for ios_hal_norm.c
//                        declared here.
// 20.07.10   C. Baeuml   Standard assignment of board voltages
//                        to logical channels.
// 22.07.10   C. Baeuml   Clean up of code and comments;
//                        definitions, typedefs and declarations
//                        sorted according to IOS_HAL_xx modules.
// 28.07.10   C. Baeuml   New H- File name cfg_55xxsiu_eb01.h.
// 23.07.10   A. Tenkeu   New configuration tables types tIOSHALBICfg,
//                        tIOSHALFICfg, tIOSHALROCfg.
//                        New definition of configuration tables.
//                        Renaming the old size of configuration table.
// 16.06.11   A. Raikwar  Logical channels 21-25 added for additional
//                        diagnostic voltages.
// 23.09.11   W. Boigk    New konfiguration table tIOSHALPWD cHALPWD
// 05.07.12   A. Mauro    Merge between EB01x and EB03x module
// 21.01.16   A. Mauro    Jira issue BC_002-1817 solved, removed:
//                        MAX_IOSHAL_GETAIVOLTAGE_CFG_MAX_ENTRIES
//                        MAX_IOSHAL_GETAICURRENT_CFG_MAX_ENTRIES
//                        MAX_IOSHAL_GETAIADCVALUE_CFG_MAX_ENTRIES
//                        u16IOSHALGetAIVoltageCfg
//                        u16IOSHALGetAICurrentCfg
//                        u16IOSHALGetAIADCValue
//                        cSensorMinMaxCurrentData
//                        cSensorMinMaxVoltageData
// 17.11.22  J. Lulli     Coding guidelines update
// 2024-02-05 C. Brancolini   Deleted E_IOS_IO_CHANNEL_BOARD_TYPE
//
//****************************************************************************
//Note: Suppression of "Wrong prefix", these variables cannot be renamed
//      because they are used elsewhere in the code

#ifndef IOS_HAL_CPU04_H
#define IOS_HAL_CPU04_H

//******************* Header / include files ( #include ) ********************
//#include "std_defs.h"
#include "ios_hal.h"
#include "kb_ret.h"

//***************** Constant / macro definitions ( #define ) *****************
#define IOS_HAL_UP_TO_DATE              ((S16) 1)

// ---------------------------------------------------------------------------
//! @name IOS_HAL_CORE.C configuration table length definitions.
//! @{
//! @brief the maximum entries for the configuration of function
//! s16IOS_HAL_InitBoard().
#define MAX_IOSHAL_INITBOARD_CFG_MAX_ENTRIES            32

//! @brief the maximum entries for the configuration of function
//! s16IOS_HAL_SetConfigSignal().
#define MAX_IOSHAL_SETCONFIGSIGNAL_CFG_MAX_ENTRIES      16

//! @brief the maximum entries for the configuration of function
//! s16IOS_HAL_GetBoardVoltage() and s16IOS_HAL_CheckBoardVoltage().
#define MAX_IOSHAL_BOARDVOLTAGE_CFG_MAX_ENTRIES         32

//! @brief the maximun entries for the configuration of function
#define MAX_IOSHAL_SET_EN_SIGNALS                       8

//! @}

// ---------------------------------------------------------------------------
//! @name IOS_HAL_BI.C configuration table length definitions.
//! @{
//! @brief the maximum entries for the configuration of function
//! s16IOS_HAL_InitBI().
#define MAX_IOSHAL_BI_CFG_MAX_ENTRIES                   16
//! @}

// ---------------------------------------------------------------------------
//! @name IOS_HAL_FI.C configuration table length definitions.
//! @{
//! @brief the maximum entries for the configuration of function
//! s16IOS_HAL_InitFI().
#define MAX_IOSHAL_FI_CFG_MAX_ENTRIES                   8

//! @brief the maximun entries for the configuration of function
//! s16IOS_HAL_GetPWDemod().
#define MAX_IOSHAL_PWDCH                                8
//! @}

// ---------------------------------------------------------------------------
//! @name IOS_HAL_FO.C configuration table length definitions.
//! @{
//! @brief the maximum entries for the configuration of function
//! s16IOS_HAL_InitFO().
#define MAX_IOSHAL_FO_CFG_MAX_ENTRIES                   8

// ---------------------------------------------------------------------------
//! @name IOS_HAL_RO.C configuration table length definitions.
//! @{
//! @brief the maximum entries for the configuration of function
//! s16IOS_HAL_InitRO().
#define MAX_IOSHAL_RO_CFG_MAX_ENTRIES                  16

// ---------------------------------------------------------------------------
//!  @name  Logical  channel  definitions
//!  Never  change  this  definitions
//!  @{

#define  IOS_CHANNEL_1                (U16)    0
#define  IOS_CHANNEL_2                (U16)    1
#define  IOS_CHANNEL_3                (U16)    2
#define  IOS_CHANNEL_4                (U16)    3
#define  IOS_CHANNEL_5                (U16)    4
#define  IOS_CHANNEL_6                (U16)    5
#define  IOS_CHANNEL_7                (U16)    6
#define  IOS_CHANNEL_8                (U16)    7
#define  IOS_CHANNEL_9                (U16)    8
#define  IOS_CHANNEL_10              (U16)    9
#define  IOS_CHANNEL_11              (U16)    10
#define  IOS_CHANNEL_12              (U16)    11
#define  IOS_CHANNEL_13              (U16)    12
#define  IOS_CHANNEL_14              (U16)    13
#define  IOS_CHANNEL_15              (U16)    14
#define  IOS_CHANNEL_16              (U16)    15
#define  IOS_CHANNEL_17              (U16)    16
#define  IOS_CHANNEL_18              (U16)    17
#define  IOS_CHANNEL_19              (U16)    18
#define  IOS_CHANNEL_20              (U16)    19
#define  IOS_CHANNEL_21              (U16)    20
#define  IOS_CHANNEL_22              (U16)    21
#define  IOS_CHANNEL_23              (U16)    22
#define  IOS_CHANNEL_24              (U16)    23
#define  IOS_CHANNEL_25              (U16)    24
#define  IOS_CHANNEL_26              (U16)    25
#define  IOS_CHANNEL_27              (U16)    26
#define  IOS_CHANNEL_28              (U16)    27
#define  IOS_CHANNEL_29              (U16)    28
#define  IOS_CHANNEL_30              (U16)    29
#define  IOS_CHANNEL_31              (U16)    30
#define  IOS_CHANNEL_32              (U16)    31

//!  @}

// ---------------------------------------------------------------------------
//! @name IOS_HAL_CORE.C
//!       Standard assignment of board voltages to logical channels
//! @{
#define IOS_CHAN_DIAG_PS_CORE     IOS_CHANNEL_1
#define IOS_CHAN_DIAG_1_5V        IOS_CHANNEL_2
#define IOS_CHAN_DIAG_3_3V        IOS_CHANNEL_3
#define IOS_CHAN_DIAG_5V          IOS_CHANNEL_4
#define IOS_CHAN_DIAG_15V         IOS_CHANNEL_5
#define IOS_CHAN_DIAG_24V         IOS_CHANNEL_6
#define IOS_CHAN_UNUSED_1         IOS_CHANNEL_7
#define IOS_CHAN_UNUSED_2         IOS_CHANNEL_8
#define IOS_CHAN_SUPPLY_INPUTS_1  IOS_CHANNEL_9
#define IOS_CHAN_SUPPLY_INPUTS_2  IOS_CHANNEL_10
#define IOS_CHAN_SUPPLY_INPUTS_3  IOS_CHANNEL_11
#define IOS_CHAN_SUPPLY_INPUTS_4  IOS_CHANNEL_12
#define IOS_CHAN_SUPPLY_OUTPUTS_1 IOS_CHANNEL_13
#define IOS_CHAN_SUPPLY_OUTPUTS_2 IOS_CHANNEL_14
#define IOS_CHAN_SUPPLY_OUTPUTS_3 IOS_CHANNEL_15
#define IOS_CHAN_SUPPLY_OUTPUTS_4 IOS_CHANNEL_16
#define IOS_CHAN_DIAG_CUTOFF_1    IOS_CHANNEL_17
#define IOS_CHAN_DIAG_CUTOFF_2    IOS_CHANNEL_18
#define IOS_CHAN_DIAG_CUTOFF_3    IOS_CHANNEL_19
#define IOS_CHAN_DIAG_CUTOFF_4    IOS_CHANNEL_20
#define IOS_CHAN_DIAG_5V_STBY     IOS_CHANNEL_21
#define IOS_CHAN_DIAG_3_3V_1      IOS_CHANNEL_22
#define IOS_CHAN_DIAG_VPP         IOS_CHANNEL_23
#define IOS_CHAN_DIAG_VADC        IOS_CHANNEL_24
#define IOS_CHAN_DIAG_ADC_REF     IOS_CHANNEL_25
//! @}
// ---------------------------------------------------------------------------

//! @name IOS_HAL_SUPPLY.C configuration table length definitions.
//! @{
//! @brief the maximun entries for the configuration of functions
#define MAX_IOSHAL_SUPPLYSWITCH           8

#define MAX_IOSHAL_SUPPLYSENSE            8

//! @}

#define  HIGHACT    1
#define  LOWACT    0

//*********************** Type definitions ( typedef ) ***********************

// ---------------------------------------------------------------------------
//! @name IOS_HAL_CORE.C typedefs for configuration records
//! @{

//! @brief Configuration structure for the board specific low level
//! driver initialization.
//! Used by the function s16IOS_HAL_InitBoard().
typedef struct {
  //! @brief Pointer to a SIU PCR register index of channels
  //! used as input.
  const U16* pu16GPINr;
  //! @brief Pointer to a SIU PCR register index of channels
  //! used as output.
  const U16* pu16GPONr;
  //! @brief Initial level of binary output signal.
  const BOOLEAN boInitLevel;
}C_IOS_HAL_INIT_BOARD_CFG;

//! @brief Min and Max ADC values used for the board voltage check.
typedef struct {
//! @brief the minimum ADC value in the range.
const U32 u32MinValue;
//! @brief the maximum ADC value in the range.
const U32 u32MaxValue;
} C_IOS_HAL_ADC_MINMAXDATA;

//! @name
//! @{
//! @brief Configuration structure for BO
//! @brief PCR Channel Config Outputs
typedef struct {
  const U16* pu16PCR_CH;
//! @brief Switch High or Low active
  const BOOLEAN bHigh_Low_active; // @suppress("Wrong prefix")
  //Note: Suppression of "Wrong prefix", the number of the struct cannot be renamed
//! @}
}C_IOS_HAL_CONFIG_SIGNALS;

//! @}

// ---------------------------------------------------------------------------
//! @name IOS_HAL_BI.C typedefs for configuration records
//! @{
//! @brief Configuration structure for the initialization of
//! channels for binary input/output.
//! Used by the function s16IOS_HAL_InitBoard().
typedef struct {
  //! @brief Pointer to a SIU PCR register index of channels
  //! used for binary input.
  const U16* pu16BIGPINr;
  //! @brief Pointer to a SIU PCR register index of channels
  //! used for binary test output.
  const U16* pu16BIGPONr;
  //! @brief Status information that indicate if the read input of
  //! channels for relay output diagnose must be invert or not.
  const BOOLEAN boBinInvert;
}C_IOS_HAL_BI_CFG;
//! @}

// ---------------------------------------------------------------------------
//! @name IOS_HAL_FI.C typedefs for configuration records
//! @{
//! @brief Configuration structure for the frequency input diagnose.
//! Used by the function s16IOS_HAL_InitFI().
typedef struct {
  //! @brief Pointer to the SIU PCR register of this FI.
  const U16* pu16FIPCRNr;
  //! @brief Pointer to a SIU PCR register index of channels
  //! used for binary test output.
  const U16* pu16FIBinGPONr;
  //! @brief Status information that indicate if the related input of the
  //! logical channels must be invert or not in Binary Mode.
  const BOOLEAN boFIBinInvert;
  //! @brief Edge Type used for period measurement in FIN Mode.
  const BOOLEAN boEdge;
  //! @brief Spike filter constant in [ns].Values [0, 500, 1000, 2000, 4000].
  const U32 u32MinFilterLength;
}C_IOS_HAL_FI_CFG;

//! @brief Configuration structure for the frequency input in PWD mode.
//! Used by the function s16IOS_HAL_GetPWDemod().

typedef struct {
  //! @brief Pointer to the SIU PCR register
  const U16* pu16PCR;
  //! @brief Sampling window with
  const U16 u16window;
  //! @brief Filter lenth
  const U16 u16filter;
  //! @brief Switch high low active
  const BOOLEAN HLactive; // @suppress("Wrong prefix")
  //Note: Suppression of "Wrong prefix", the number of the struct cannot be renamed
  }C_IOS_HAL_PWD;

//! @}

// ---------------------------------------------------------------------------
//! @name IOS_HAL_RO.C typedefs for configuration records
//! @{
//! @brief Configuration structure for the initialization of logical
//! channels for relay output.
//! Used by the function s16IOS_HAL_InitRO().
typedef struct {
  //! @brief Pointer to a SIU PCR register index of channels
  //! used as input.
  const U16* pu16ROGPINr;
  //! @brief Pointer to a SIU PCR register index of channels
  //! used as output.
  const U16* pu16ROGPONr;
  //! @brief Status information that indicate if the read input of the relay
  //! outputs channels must be invert or not.
  const BOOLEAN boROInvert;
}C_IOS_HAL_RO_CFG;
//! @}


//! @name IOS_HAL_SUPPLY.C typedefs for configuration records
//! @{
//! @brief Configuration structure for the Supply
typedef struct {
  //! @brief Pointer to SIU PCR register
  const U16* pu16PCR;
  //! @brief Switch, High or Low active
  const BOOLEAN HLactive; // @suppress("Wrong prefix")
  //Note: Suppression of "Wrong prefix", the number of the struct cannot be renamed
}C_IOS_HAL_SUPPLY_SENSE;

//! @brief Configuration structure for the Supply
typedef struct {
  //! @brief Pointer to SIU PCR register
  const U16* pu16PCR;
  //! @brief Switch, High or Low active
  const BOOLEAN HLactive; // @suppress("Wrong prefix")
  //Note: Suppression of "Wrong prefix", the number of the struct cannot be renamed
}C_IOS_HAL_SUPPLY_SWITCH;

//! @}

//******************* Global data declarations ( extern ) ********************

//******* External parameter / constant declarations ( extern const ) ********

//! @name IOS_HAL_CORE.C declaration of configuration tables.
//! @{
//! Configuration for the function s16IOS_HAL_TriggerIOWatchdog()
extern const U16* pu16OutputWatchDogTrigger;
//! @}

// ---------------------------------------------------------------------------
//! @name IOS_HAL_CORE.C declaration of configuration tables.
//! @{
//! @brief Configuration table for the function s16IOS_HAL_InitBoard().
extern const C_IOS_HAL_INIT_BOARD_CFG cHALInitBoardCfg[MAX_IOSHAL_INITBOARD_CFG_MAX_ENTRIES]; // @suppress("Wrong prefix")

//! @brief Configuration array for setting of configuration signal.
//! It contain Pointer to  SIU PCR register index of channels
//! for configuration signal.
//! Used by the function  s16IOS_HAL_SetConfigSignal().
extern const C_IOS_HAL_CONFIG_SIGNALS cIOSHALSetConfigSignalCfg[MAX_IOSHAL_SETCONFIGSIGNAL_CFG_MAX_ENTRIES]; // @suppress("Wrong prefix")

//! @brief Configuration array for ADC channels. It contain
//! Pointer to physical ADC channels numbers.
//! Used by the function s16IOS_HAL_GetBoardVoltage() and s16IOS_HAL_CheckBoardVoltage().
extern const U16* u16IOSHALBoardVoltageCfg[MAX_IOSHAL_BOARDVOLTAGE_CFG_MAX_ENTRIES]; // @suppress("Wrong prefix")

//! @brief Min and Max ADC values used for the board voltage check.
extern const C_IOS_HAL_ADC_MINMAXDATA cIOSHALADCMinMaxData[MAX_IOSHAL_BOARDVOLTAGE_CFG_MAX_ENTRIES]; // @suppress("Wrong prefix")

//! @brief Configuration table for the function .
extern const C_IOS_HAL_CONFIG_SIGNALS cHALGetConfSig[MAX_IOSHAL_SET_EN_SIGNALS]; // @suppress("Wrong prefix")

//! @}

//****** External parameter / constant declarations ( extern const ) ********

//! @brief Configuration table for the function .
extern const C_IOS_HAL_CONFIG_SIGNALS cHALSetEnSigConf[MAX_IOSHAL_SET_EN_SIGNALS]; // @suppress("Wrong prefix")
//! @}

// ---------------------------------------------------------------------------
//! @name IOS_HAL_BI.C declaration of configuration tables.
//! @{
//! @brief Configuration table for the function s16IOS_HAL_InitBI().
extern const C_IOS_HAL_BI_CFG cIOSHALBICfg[MAX_IOSHAL_BI_CFG_MAX_ENTRIES]; // @suppress("Wrong prefix")
//! @}

// ---------------------------------------------------------------------------
//! @name IOS_HAL_FI.C declaration of configuration tables.
//! @{
//!@brief  Configuration table for the function s16IOS_HAL_InitFI().
extern const C_IOS_HAL_FI_CFG cIOSHALFICfg[MAX_IOSHAL_FI_CFG_MAX_ENTRIES]; // @suppress("Wrong prefix")
//! @}

//! @brief Configuration table for the function s16IOS_HAL_GetPWDemod().
extern const C_IOS_HAL_PWD cHALPWD[MAX_IOSHAL_PWDCH]; // @suppress("Wrong prefix")
// ---------------------------------------------------------------------------
//! @name IOS_HAL_FO.C declaration of configuration tables.
//! @{
//! @brief Configuration array for frequency output configured as binary
//! inputs.It contain Pointer to SIU PCR register index of
//! channels for frequency output configured as binary input.
//! Used by the function s16IOS_HAL_InitFO().
extern const C_IOS_HAL_CONFIG_SIGNALS u16IOSHALFOCfg[MAX_IOSHAL_FO_CFG_MAX_ENTRIES]; // @suppress("Wrong prefix")
//! @}

// ---------------------------------------------------------------------------
//! @name IOS_HAL_RO.C declaration of configuration tables.
//! @{
//!@brief Configuration table for the function s16IOS_HAL_InitRO().
extern const C_IOS_HAL_RO_CFG cIOSHALROCfg[MAX_IOSHAL_RO_CFG_MAX_ENTRIES]; // @suppress("Wrong prefix")

//! @brief Configuration table for the function s16IOS_HAL_InitRO_B().
extern const C_IOS_HAL_RO_CFG cIOSHALRO_BCfg[MAX_IOSHAL_RO_CFG_MAX_ENTRIES]; // @suppress("Wrong prefix")
//! @}

// ---------------------------------------------------------------------------
//! @name IOS_HAL_SUPPLY.C declaration of configuration tables.
//! @{

//!@brief Configuration table for the function s16IOS_HALGetSupplyStatus
extern const C_IOS_HAL_SUPPLY_SENSE cHALSupplySense[MAX_IOSHAL_SUPPLYSENSE]; // @suppress("Wrong prefix")
//!@brief Configuration table for the function
extern const C_IOS_HAL_SUPPLY_SWITCH cHALSupplySwitch[MAX_IOSHAL_SUPPLYSWITCH]; // @suppress("Wrong prefix")

//! @}

//----------------------------------------------------------------------------
//  Function pvIOSCycl20msTriggerIOWatchdog
//!  @name Output function definitions.
//! @{
//! The following two functios are not used all warnings ignored and suppressed
extern void (*pvIOSCycl20msTriggerIOWatchdog)(void); // @suppress("Descriptive Header")
extern void (*pvIOSCycl20msCheck)(void); // @suppress("Descriptive Header") // @suppress("Use Doxygen Comments")
//! @}

//*******************  Global  data  declarations  (  extern  )  ********************
extern BOOLEAN boIOSHALeMIOS0Initialized;
                                        // EMIO 0 initialized

//******  External  parameter  /  constant  declarations  (  extern  const  )  ********



//  Function s16IOS_HAL_InitCPU04Board  *************************************
//!  This function configures digital status inputs and control outputs of
//!  boards with CPU04
//!  @param[in]    ---
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    Must  be  called  once  during  startup  before  using  IOS.
//*****************************************************************************
extern  S16  s16IOS_HAL_InitCPU04Board  (void);



//  Function s16IOS_HAL_TriggerIOWatchdog  ************************************
//!  Trigger  IO  Watchdog.
//!  @param[in]  ---
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    PWD  Signals  are  initialized  by  s16IOS_HAL_InitBoard().
//*****************************************************************************
extern  S16  s16IOS_HAL_TriggerIOWatchdog  (void);



//  Function s16IOS_HAL_SetConfigSignal  **************************************
//!  Set  Configuration  Signal  Output.
//!  @param[in]  u16Channel:  Config  Signal  Channel
//!                          [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[in]  boOutput:    Output  state  to  be  set.
//!                          TRUE:  Set  signal
//!                          FALSE:  Reset  signal
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    Config  Signals  are  initialized  by  s16IOS_HAL_InitBoard().
//*****************************************************************************
extern  S16  s16IOS_HAL_SetConfigSignal  (U16  u16Channel,  BOOLEAN  boOutput);



//  Function s16IOS_HAL_GetBoardVoltage  **************************************
//!  Read  ADC  Value  of  Board  Voltage.
//!  @param[in]  u16Channel:  Board  Voltage  Channel
//!                            [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[in]  pu16Input:    Reference  to  ADC  value.
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    Drivers  are  initialized  by  s16IOS_HAL_InitBoard().
//!              The  logical  channel  assignment  for  the  Board  Voltages
//!              is  board  specific.
//!              This  function  is  only  for  debugging  and  EMC  Testing.
//*****************************************************************************
extern  S16  s16IOS_HAL_GetBoardVoltage  (U16  u16Channel,  U16* pu16Input);



//  Function s16IOS_HAL_InitBI  ***********************************************
//!  Initialization  of  Binary  Input  channel  and  assigned
//!  BI  Diag  Output,  if  available.
//!  @param[in]  u16Channel:  BI  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    ---
//*****************************************************************************
extern  S16  s16IOS_HAL_InitBI  (U16  u16Channel);



//  Function s16IOS_HAL_GetBI  ************************************************
//!  Read  Binary  Input  channel
//!  @param[in]  u16Channel:  BI  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[in]  pboInput:    Reference  to  input  data.
//!                          TRUE:  Signal  is  high
//!                          FALSE:  Signal  is  low
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    BI  channel  has  to  be  initialized  by  s16IOS_HAL_InitBI().
//*****************************************************************************
extern  S16  s16IOS_HAL_GetBI  (U16  u16Channel,  BOOLEAN* pboInput);



//  Function s16IOS_HAL_SetBIDiag  ********************************************
//!  Set  Diag  Mode  of  selected  BI  channel.
//!  @param[in]  u16Channel:  BI  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[in]  u16Mode:    Test  mode  to  be  set.
//!                          See  enum  #IOS_HAL_TestMode
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    BI  channels  have  to  be  initialised  by  s16IOS_HAL_InitBI().
//*****************************************************************************
extern  S16  s16IOS_HAL_SetBIDiag  (U16  u16Channel,  U16  u16Mode);



//  Function s16IOS_HAL_InitFI  ***********************************************
//!  Initialization  of  Frequency  Input  channel
//!  and  corresponding  FI  diag  outputs,  if  available.
//!  @param[in]  u16Channel:  FI  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    ---
//*****************************************************************************
extern  S16  s16IOS_HAL_InitFI  (U16  u16Channel);



//  Function s16IOS_HAL_GetFI  ************************************************
//!  Read  Frequency  Input.
//!  @param[in]  u16Channel:  FI  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[in]  pu32Input:  Reference  to  frequency  value  in  [0.01  Hz]
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    Channels  have  to  be  initialized  by  s16IOS_HAL_InitFI.
//*****************************************************************************
extern  S16  s16IOS_HAL_GetFI  (U16  u16Channel,  U32* pu32Input);



//  Function s16IOS_HAL_InitFI_Bin  *******************************************
//!  Initialization  of  Frequency  Input  channel
//!  in  BINARY  MODE
//!  and  corresponding  FI  diag  outputs,  if  available.
//!  @param[in]  u16Channel:  FI  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    ---
//*****************************************************************************
extern  S16  s16IOS_HAL_InitFI_Bin  (U16  u16Channel);



//  Function s16IOS_HAL_GetFI_Bin  ********************************************
//!  Read  Frequency  Input  in  BINARY  MODE.
//!  @param[in]  u16Channel:  FI  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[in]  pboInput:    Reference  to  input  data.
//!                          TRUE:  Input  is  high
//!                          FALSE:  Input  is  low
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    Channels  have  to  be  initialized  by  s16IOS_HAL_InitFI_Bin.
//*****************************************************************************
extern  S16  s16IOS_HAL_GetFI_Bin  (U16  u16Channel,  BOOLEAN* pboInput);



//  Function s16IOS_HAL_SetFIDiag  ********************************************
//!  Setting  of  diag  output  of  selected  FI  channel.
//!  @param[in]  u16Channel:  FI  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[in]  u16Mode:      Test  mode  to  be  set.
//!                            See  enum  IOS_HAL_TestMode
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    FI  channels  have  to  be  initialized  by  s16IOS_HAL_InitFI().
//*****************************************************************************
extern  S16  s16IOS_HAL_SetFIDiag  (U16  u16Channel,  U16  u16Mode);



//  Function s16IOS_HAL_InitRO  ***********************************************
//!  Initialisation  of  Relay  Output  channel  and  assigned
//!  RO  Diag  Input,  if  available.
//!  @param[in]  u16Channel:  RO  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    ---
//*****************************************************************************
extern  S16  s16IOS_HAL_InitRO  (U16  u16Channel);



//  Function s16IOS_HAL_SetRO  ************************************************
//!  Set  Relay  Output.
//!  @param[in]  u16Channel:  RO  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[in]  boOutput:    Output  state  to  be  set.
//!                          TRUE:  Close  Relay
//!                          FALSE:  Open  Relay
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    RO  channels  have  to  be  initialized  by  s16IOS_HAL_InitRO().
//*****************************************************************************
extern  S16  s16IOS_HAL_SetRO  (U16  u16Channel,  BOOLEAN  boOutput);



//  Function s16IOS_HAL_GetRODrive  *******************************************
//!  Read  last  driven  setpoint  of  Relay  Output.
//!  @param[in]  u16Channel:  RO  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[in]  pboInput:    Reference  to  driven  setpoint  of  Relay.
//!                          TRUE:  Relay  was  set  to  close
//!                          FALSE:  Relay  was  set  to  open
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    RO  channels  have  to  be  initialized  by  s16IOS_HAL_InitRO.
//*****************************************************************************
extern  S16  s16IOS_HAL_GetRODrive  (U16  u16Channel,  BOOLEAN* pboInput);



//  Function s16IOS_HAL_GetRODiag  ********************************************
//!  Read  Relay  Status.
//!  @param[in]  u16Channel:  RO  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[in]  pboInput:    Reference  to  state  of  Relay.
//!                          TRUE:  Relay  is  closed
//!                          FALSE:  Relay  is  open
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    RO  channels  have  to  be  initialized  by  s16IOS_HAL_InitRO.
//!              After  circuit  time,  depending  on  relay  type,  *pboInput
//!              should  have  the  same  state  as  set  by  boOutput  in
//!              s16IOS_HAL_SetRO.
//*****************************************************************************
extern  S16  s16IOS_HAL_GetRODiag  (U16  u16Channel,  BOOLEAN* pboInput);



//  Function s16IOS_HAL_InitRO_B  *********************************************
//!  Initialisation  of  Backup  or  Safety  Relay  Output  channel  and  assigned
//!  RO  Diag  Input,  if  available.
//!  @param[in]  u16Channel:  RO  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    ---
//*****************************************************************************
extern  S16  s16IOS_HAL_InitRO_B  (U16  u16Channel);



//  Function s16IOS_HAL_SetRO_B  **********************************************
//!  Set  Backup  or  Safety  Relay  Output.
//!  @param[in]  u16Channel:  RO  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[in]  boOutput:    Output  state  to  be  set.
//!                          TRUE:  Close  Relay
//!                          FALSE:  Open  Relay
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    RO  channels  have  to  be  initialized  by  s16IOS_HAL_InitRO_B().
//*****************************************************************************
extern  S16  s16IOS_HAL_SetRO_B  (U16  u16Channel,  BOOLEAN  boOutput);



//  Function s16IOS_HAL_GetRODrive_B  *****************************************
//!  Read  last  driven  setpoint  of  Backup  or  Safety  Relay  Output.
//!  @param[in]  u16Channel:  RO  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[in]  pboInput:    Reference  to  driven  setpoint  of  Relay.
//!                          TRUE:  Relay  was  set  to  close
//!                          FALSE:  Relay  was  set  to  open
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    RO  channels  have  to  be  initialized  by  s16IOS_HAL_InitRO.
//*****************************************************************************
extern  S16  s16IOS_HAL_GetRODrive_B  (U16  u16Channel,  BOOLEAN* pboInput);



//  Function s16IOS_HAL_GetRODiag_B  ******************************************
//!  Read  Relay  Status  of  Backup  or  Safety  Relay.
//!  @param[in]  u16Channel:  RO  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[in]  pboInput:    Reference  to  state  of  Relay.
//!                          TRUE:  Relay  is  closed
//!                          FALSE:  Relay  is  open
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    RO  channels  have  to  be  initialized  by  s16IOS_HAL_InitRO.
//!              After  circuit  time,  depending  on  relay  type,  *pboInput
//!              should  have  the  same  state  as  set  by  boOutput  in
//!              s16IOS_HAL_SetRO_B.
//*****************************************************************************
extern  S16  s16IOS_HAL_GetRODiag_B  (U16  u16Channel,  BOOLEAN* pboInput);



//  Function s16IOS_HAL_InitFO  ***********************************************
//!  Initialization  of  Frequency  Output  channel.
//!
//!  @param[in]  u16Channel:    FO  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[in]  u32Frequency:  Frequency  value  to  be  set    [1  Hz]
//!  @param[in]  u32DutyCycle:  Duty  cycle  value  to  be  set  0..100  [1%]
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    ---
//*****************************************************************************
extern  S16  s16IOS_HAL_InitFO  (U16  u16Channel,  U32  u32Frequency,  U32  u32DutyCycle);



//  Function s16IOS_HAL_SetFO  ************************************************
//!  Set  Frequency  Output.
//!  @param[in]  u16Channel:    FO  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[in]  u32Frequency:  Frequency  value  to  be  set  [1  Hz]
//!  @param[in]  u32DutyCycle:  Duty  cycle  to  be  set  0  ..100[%]
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    Channels  have  to  be  initialized  by  s16IOS_HAL_InitFO.
//*****************************************************************************
extern  S16  s16IOS_HAL_SetFO  (U16  u16Channel,  U32  u32Frequency,  U32  u32DutyCycle);



// Function s16IOS_HAL_InitFO_Bin  *******************************************
//!  Initialization  of  Frequency  Output  channel
//!  in  BINARY  MODE
//!  @param[in]  u16Channel:  FO  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    ---
//*****************************************************************************
extern  S16  s16IOS_HAL_InitFO_Bin  (U16  u16Channel);



// Function s16IOS_HAL_SetFO_Bin  ********************************************
//!  Set  Frequency  Output  in  BINARY  MODE.
//!  @param[in]  u16Channel:  FO  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[in]  boOutput:    Output  state  to  be  set.
//!                          TRUE:  Set  signal  to  High
//!                          FALSE:  Set  signal  to  Low
//!  @param[out]  ---
//!  @returns    #IOS_HAL_return
//!  @remarks    Channels  have  to  be  initialized  by  s16IOS_HAL_InitFO_Bin.
//*****************************************************************************
extern  S16  s16IOS_HAL_SetFO_Bin  (U16  u16Channel,  BOOLEAN  boOutput);



//  Function s16IOS_HAL_PWDemodInit  ***************************************
//!  @brief  init  Puls  Demodulation
//!
//!  @param[in]  u16Channel:  FO  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!
//!  @returns    #IOS_HAL_return
//!
//!
//****************************************************************************
extern S16 s16IOS_HAL_PWDemodInit( U16 u16Channel );


// Function s16IOS_HAL_GetPWDemod  ***************************************
//!  @brief  Get  Puls  Demodulation
//!
//!  @param[in]     u16Channel:  FO  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[in]  pu32FIx:      --  Duty  Cycle
//!  @param[in]    pboIOS_HAL_PWDUpToDate--Up  to  Date  Bit
//!
//!  @returns    #IOS_HAL_return
//!
//!  @remarks    if  the  up  to  dat  bit  is  zero,  the  last  valid  value
//!              is  returned
//****************************************************************************
extern  S16 s16IOS_HAL_GetPWDemod(U16 u16Channel, U32* pu32FIx, BOOLEAN* pboIOS_HAL_PWDUpToDate);



// Function s16IOS_HAL_GetSupplyStatus  ****************************************
//!  @brief  gives  back  the  status  of  supply  at  the  PCR  channel
//!
//!  @param[in]     u16Channel:  FO  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[in]  boStatus:  #ON  (#TRUE)  or  #OFF  (#FALSE).
//!
//!  @returns    #IOS_HAL_return
//!  @remarks    The  channel  status  is  either  ON  (TRUE)  or  OFF(FALSE).
//!              An  Logical  inversion  is
//!              handelt  by  #LOWACT  and  #HIGHACT  in  #tIOSHALSupplySense  .
//!
//!
//****************************************************************************
extern  S16  s16IOS_HAL_GetSupplyStatus(U16  u16Channel,  BOOLEAN* boStatus); // @suppress("Wrong prefix")



// Function s16IOS_HAL_SwitchSupply  ***************************************
//!  @brief  function  for  switching  supply  activation
//!
//!  @param[in]  u16Channel:  FO  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[in]  boStatus--  #ON  (#TRUE)  or  #OFF  (#FALSE).
//!
//!  @returns    #IOS_HAL_return  If  greater  -1  succes.  Otherwise  errror.
//!
//!
//****************************************************************************
extern  S16  s16IOS_HAL_SwitchSupply(U16  u16Channel, BOOLEAN  boStatus);



// Function s16IOS_HAL_SetEnableSignal()  ************************************
//!  @brief  function  to  set  enable  signals,  supply  activation,  driver  activation
//!          etc.
//!
//!  @param[in]  u16Channel:  FO  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[in]  boOutput    :  desired  status  of  pin
//!
//!  @returns    #IOS_HAL_return  If  greater  -1  succes.  Otherwise  errror.
//!
//!
//****************************************************************************
extern  S16  s16IOS_HAL_SetEnableSignal(U16  u16Channel,  BOOLEAN  boOutput);

//  Function s16IOS_HAL_GetConfigSignal()  ***************************************
//!  @brief  function  to  det  binary  config  signals
//!
//!  @param[in]  u16Channel:  FO  Channel  [#IOS_CHANNEL_1  ..  #IOS_CHANNEL_32]
//!  @param[out]  pboStatus  :  status  of  desired  pin
//!
//!
//!  @returns    #IOS_HAL_return  If  greater  -1  succes.  Otherwise  errror.
//!
//!
//****************************************************************************
extern  S16  s16IOS_HAL_GetConfigSignal(U16  u16Channel,  BOOLEAN* pboStatus);


//** Function s16IOSHALCheckAIVoltageValue ************************************
//!   @brief checks if the Analog input value is within the specified values
//!
//!   @param[in] u16Channel, Channel number
//!   @param[in] u16MinThreshold, Minimum threshold value
//!   @param[in] u16MaxThreshold, Maximum threshold value
//!   @param[out] pboResultOkay, the value is within the specified values
//!
//!   @returns : s16HalReturn
//!
//*****************************************************************************
extern S16 s16IOSHALCheckAIVoltageValue ( U16 u16Channel, U16 u16MinThreshold,
                                          U16 u16MaxThreshold, BOOLEAN* pboResult );


//* Function vIOS_HAL_Cycl1ms_GetPWDemod **************************************
//!  @brief Get Puls Demodulation cyclically
//!  @param[in]  --
//!  param[OUT] --
//!  param[OUT] --
//!
//!
//* **************************************************************************
void vIOS_HAL_Cycl1ms_GetPWDemod( void );

#endif
//* EndOfFile ios_hal_cpu04.h **************************************************

