//**********************************************************************************************************************
//
//                                                 mon_cpu04_genrl_sdi_i.h
//
//**********************************************************************************************************************
//
//                                       Copyrights(c) by KNORR-BREMSE,
//                                        Rail Vehicle Systems, Munich
//
//! @project   IBC
//! @date      2023-12-04
//! @author    C. Brancolini
//!
//**********************************************************************************************************************
//! @file
//! @brief  General MON TCH internal definitions and types
//!
//**********************************************************************************************************************
// History
// Date           Author:       Changes:
// 21.05.2013     H. Shaikh     0.1  Start
// 29.05.2014     H. Shaikh     0.2  BC_002-814 added command length for PSDIO
// 2023.09.28     A. Mauro      0.3    Alignment with CA: name changed and other
// 2023-12-04     C. Brancolini Changed __MON_CPU04_GENRL_SDI_I_H__ in MON_CPU04_GENRL_SDI_I_H
//
//**********************************************************************************************************************

#ifndef MON_CPU04_GENRL_SDI_I_H
#define MON_CPU04_GENRL_SDI_I_H
//**************************************** Header / include files ( #include ) *****************************************
#include "std_defs.h"
#include "sdi.h"                            // SDI definitions
#include "mon.h"
//**************************************** Constant / macro definitions ( #define ) ************************************

//**********************************************************************************************************************
//! @name Define General SDI commands
//**********************************************************************************************************************
#define MON_SDI_READ_DIGIO_BYTE            12
#define MON_SDI_WRITE_DIGIO_BYTE           13
#define MON_SDI_READ_ANALOG                14
#define MON_SDI_READ_FREQ                  15
#define MON_SDI_WRITE_FREQ                 16
#define MON_SDI_WRITE_PWM                  17
#define MON_SDI_READ_PSDIO                 18
#define MON_SDI_WRITE_PSDIO                19
#define MON_SDI_WRITE_ANALOG               20
#define MON_SDI_READ_PWM                   21


//**********************************************************************************************************************
//! @name Define General TCH commands length
//**********************************************************************************************************************
#define MON_SDI_READ_PSDIO_LEN             3
#define MON_SDI_WRITE_PSDIO_LEN            5

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data declarations ( extern ) *****************************************

//**************************************** External parameter / constant declarations ( extern const )  ****************

//**************************************** Global func/proc prototypes *************************************************

//* Function s16MON_WriteDigioByte ********************************************
//*
//!  This function processes the terminal command MON_SDI_WRITE_DIGIO_BYTE
//
//!  @param[in]  pu8DataIn : Pointer of Terminal channel input
//!  @param[in]  u16CmdLenIn : length of command
//!  @param[out] pu8DataOut : Pointer on TCH Message for output
//!  @param[out] u16MaxRespOut : Max data to write to output
//!  @returns    >= 0 : Size of response to terminal (data byte in pu8DataOut)\n
//!              <0 : not used
//!  @remarks    Only to be called by s16MONProcessTCHMessage
//**********************************************************************************************************************
extern s16SDI_CMD(s16MON_WriteDigioByte);

//* Function s16MON_ReadDigioByte **************************************************************************************
//*
//!  This function processes the terminal command MON_SDI_READ_DIGIO_BYTE
//
//!  @param[in]  pu8DataIn : Pointer of Terminal channel input
//!  @param[in]  u16CmdLenIn : length of command
//!  @param[out] pu8DataOut : Pointer on TCH Message for output
//!  @param[out] u16MaxRespOut : Max data to write to output
//!  @returns    >= 0 : Size of response to terminal (data byte in pu8DataOut)\n
//!              <0 : not used
//!  @remarks    Only to be called by s16MONProcessTCHMessage
//**********************************************************************************************************************
extern s16SDI_CMD(s16MON_ReadDigioByte);

//* Function s16MON_WritePWM *******************************************************************************************
//*
//!  This function processes the terminal command MON_SDI_WRITE_PWM
//
//!  @param[in]  pu8DataIn : Pointer of Terminal channel input
//!  @param[in]  u16CmdLenIn : length of command
//!  @param[out] pu8DataOut : Pointer on TCH Message for output
//!  @param[out] u16MaxRespOut : Max data to write to output
//!  @returns    >= 0 : Size of response to terminal (data byte in pu8DataOut)\n
//!              <0 : not used
//!  @remarks    Only to be called by s16MONProcessTCHMessage
//**********************************************************************************************************************
extern s16SDI_CMD(s16MON_WritePWM);

//* Function s16MON_ReadPWM ********************************************************************************************
//*
//!  This function processes the terminal command MON_SDI_READ_PWM
//
//!  @param[in]  pu8DataIn : Pointer of Terminal channel input
//!  @param[in]  u16CmdLenIn : length of command
//!  @param[out] pu8DataOut : Pointer on TCH Message for output
//!  @param[out] u16MaxRespOut : Max data to write to output
//!  @returns    >= 0 : Size of response to terminal (data byte in pu8DataOut)\n
//!              <0 : not used
//!  @remarks    Only to be called by s16MONProcessTCHMessage
//**********************************************************************************************************************
extern s16SDI_CMD(s16MON_ReadPWM);

//* Function s16MON_WriteFreq ******************************************************************************************
//*
//!  This function processes the terminal command MON_SDI_WRITE_FREQ
//
//!  @param[in]  pu8DataIn : Pointer of Terminal channel input
//!  @param[in]  u16CmdLenIn : length of command
//!  @param[out] pu8DataOut : Pointer on TCH Message for output
//!  @param[out] u16MaxRespOut : Max data to write to output
//!  @returns    >= 0 : Size of response to terminal (data byte in pu8DataOut)\n
//!              <0 : not used
//!  @remarks    Only to be called by s16MONProcessTCHMessage
//**********************************************************************************************************************
extern s16SDI_CMD(s16MON_WriteFreq);

//* Function s16MON_ReadFreq *******************************************************************************************
//*
//!  This function processes the terminal command MON_SDI_READ_FREQ
//
//!  @param[in]  pu8DataIn : Pointer of Terminal channel input
//!  @param[in]  u16CmdLenIn : length of command
//!  @param[out] pu8DataOut : Pointer on TCH Message for output
//!  @param[out] u16MaxRespOut : Max data to write to output
//!  @returns    >= 0 : Size of response to terminal (data byte in pu8DataOut)\n
//!              <0 : not used
//!  @remarks    Only to be called by s16MONProcessTCHMessage
//**********************************************************************************************************************
extern s16SDI_CMD(s16MON_ReadFreq);

//* Function s16MON_WritePSDIO *****************************************************************************************
//*
//!  This function processes the terminal command MON_SDI_WRITE_PSDIO
//
//!  @param[in]  pu8DataIn : Pointer of Terminal channel input
//!  @param[in]  u16CmdLenIn : length of command
//!  @param[out] pu8DataOut : Pointer on TCH Message for output
//!  @param[out] u16MaxRespOut : Max data to write to output
//!  @returns    >= 0 : Size of response to terminal (data byte in pu8DataOut)\n
//!              <0 : not used
//!  @remarks    Only to be called by s16MONProcessTCHMessage
//**********************************************************************************************************************
extern s16SDI_CMD(s16MON_WritePSDIO);

//* Function s16MON_ReadPSDIO ******************************************************************************************
//*
//!  This function processes the terminal command MON_SDI_READ_PSDIO
//
//!  @param[in]  pu8DataIn : Pointer of Terminal channel input
//!  @param[in]  u16CmdLenIn : length of command
//!  @param[out] pu8DataOut : Pointer on TCH Message for output
//!  @param[out] u16MaxRespOut : Max data to write to output
//!  @returns    >= 0 : Size of response to terminal (data byte in pu8DataOut)\n
//!              <0 : not used
//!  @remarks    Only to be called by s16MONProcessTCHMessage
//**********************************************************************************************************************
extern s16SDI_CMD(s16MON_ReadPSDIO);

//* Function s16MON_BoardStateTestPRO **********************************************************************************
//*
//!  This function realize the MON test entering steps
//
//!  @param[in]  --
//!  @param[out] --
//!  @returns    KB_RET_OK if everything ok
//!
//!  @remarks    Has to be called when board enter TEST
//**********************************************************************************************************************
extern S16 s16MON_BoardStateTestPRO( void);

#endif
//* EndOfFile mon_cpu04_genrl_sdi_i.h **********************************************************************************
