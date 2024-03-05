//**********************************************************************************************************************
//
//                                           mon_cpu04.h
//
//**********************************************************************************************************************
//
//                                      Copyrights(c) 2022 by KNORR-BREMSE,
//                                 Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   IBC
//! @date      2023-12-20
//! @author    C. Brancolini
//
//**********************************************************************************************************************
//!  Content: constants: max number of meas data bytes
//!                      data sizes
//!                    : max number of bytes for read and write memory
//!                      accesses
//!                      max timeout value for measurement trigger
//!           typedefs:  meas data configuration structure
//!                      meas data transmit structure
//!                      CAN-Bus communication structure for request and
//!                      acknowledge
//!           externals:
//!           variables: segment descriptor for meas data validity
//!                      meas data configuration structure (RAM and ROM)
//!                      CAN-Bus handles
//!                      segment descriptors and other used within the
//!                      terminal control monitor
//!           functions: used within measurement data control monitor
//!                      (init, cyclic access, check of config data)
//!                      used within terminal control monitor
//!                      (memory access, i/o access, meas data config.,
//!                      meas trigger, project info)
//
//**********************************************************************************************************************
//  History
//  Date         Author        Changes
//  31.10.95     D. Dunkel     1.00 / Start
//  03.03.96     D. Dunkel     1.01 / command ids for service terminal changed
//  10.03.96     D. Dunkel     1.02 / MON_IO_BUFF: MAX_READ_ADDR -> MSGMAXLEN
//                                    MAX_READ_ADDR, MAX_WRITE_ADDR deleted
//  18.03.96     T. Moser      1.03 / typ-specifier corrected
//  19.03.96     T. Moser      1.04 / ConfigMeas without bSize-parameter
//  25.03.96     T. Moser      1.05 / mon_int.h renamed moni.h
//  28.03.96     S. Widder     1.06 / Changed timeout for measuredata
//  13.04.96     S. Widder     1.07 / Added prototypes for read /write PSD
//  15.04.96     S. Widder     1.08 / Rearanged command id's for monitor
//  25.04.96     S. Widder     1.1  / Declared all internal functions as
//                                    'non_banked'
//  08.05.96     S. Widder     1.08 / Rearanged command id's for monitor
//  15.05.96     S. Widder     1.1  / CR39: Removed pathes in file include
//  23.05.96     S. Widder     1.2  / Removed include of 'ESRA_DEF.H',
//  13.08.96     S. Widder     1.21 / CR68: Renamed 'CheckMeasTrigger'
//                                    to 'CyclCheckMeasdatMode'
//                                    Added defines for measdata config
//  19.08.96     S. Widder     1.22 / CR68: Redefined some constants for
//                                for measdat configuration
//  09.09.97     M. Meindl	   1.23 / CR?? Some Command ID's for terminal
//                                channel added (compatibility 80167)
//                                New: all  _32 accesses,
//                                     READ and WRITE_DIGIO_WORD
//                                     READ_ANALOG_VOLTAGE
//                                     READ_ANALOG_CURRENT
//  13.02.98     G. Becker     1.24 / only comment changed
//  19.11.98     G. Becker     1.25 / CAN_DEFAULT and UART_DEFAULT were
//                                    defined in MON.H
//  16.03.11     C. Baeuml     1.3  / Reduction for MPC55xx usage.
//  28.03.11     C. Baeuml     1.4  / Pragma pack little endian
//                                for communication buffer.
//  12.05.11     C. Baeuml     1.5  / New function ReadPSDIO().
//  09.11.11     W. Boigk      1.6  / Modified ReadPWM and add WritePWM
//  15.04.13     H. Shaikh     1.7  / Updates as per Working Instructions.
//  29.10.14     H. Shaikh     1.8  / Added  MON_MAXOUTPORT_NO
//  17.02.16     A. Mauro      1.9  / Jira issue TC_007-84 solved
//  20.04.17     A. Mauro      2.0  / TC_007-96: LINT clean up
//  2023.09.14   A. Mauro      2.1    Alignment with CA: name changed and other
//  2023-12-20   C. Brancolini        Lint Plus clean up
//
//**********************************************************************************************************************

#ifndef MON_CPU04_H
#define MON_CPU04_H

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include    <STD_DEFS.H>

//***************** Constant / macro definitions ( #define ) ***********************************************************
#define   MON_MSGMAXLEN          64U           // size of buffer terminal channel
#define   MON_MAXOUTPORT_NO       2U           // no of parameter for each output

// error codes for service terminal commands -------------------------------

#define MON_ERR_PWM_WRITE    1
// Others ------------------------------------------------------------------
#define MON_DAT            1U            // offset for request data
#define MON_ACK            3U            // offset for acknowledge data

#define MON_PWM_100PER      (U32)1000    // max value of PWM
#define MON_SDI_PAR_OFFSET      (U8)2    // offset of parameters in request message

#define MON_SDI_INDEX_1 1U
#define MON_SDI_INDEX_2 2U
#define MON_SDI_INDEX_3 3U

// Macros ------------------------------------------------------------------
#define GET_ADR_FROM_TERMPTR(x) (BYTE *) (*(x) +((*(x+1))<<8U))
// Get byte ptr from term msg ptr
// *(ptr+0) = ADR_LOWBYTE
// *(ptr+1) = ADR_HIGHBYTE

#define GET_WORD_FROM_TERMPTR(x) (*(x) + ((*(x+1))<<8UL))
// Get word from term msg ptr
// *(ptr+0) = WORD_LOWBYTE
// *(ptr+1) = WORD_HIGHBYTE
//************************************** Type definitions ( typedef ) **************************************************

#pragma pack (1,1,1)                    // "Little endian" // @suppress("No #pragma instructions")
typedef struct                          // structure for frequency input transmit
{
    U16 u16Frequency;
    BOOLEAN boFreqUpToDate;
} C_FIN_MEASUREMENT_DATA_WORD;
#pragma pack(0)                         // Set to default packing // @suppress("No #pragma instructions")

#pragma pack (1,1,1)                    // "Little endian" // @suppress("No #pragma instructions")
typedef union
{
    U8 au8Data[MON_MSGMAXLEN];
    U16 au16Data[MON_MSGMAXLEN / 2];
    C_FIN_MEASUREMENT_DATA_WORD acMonFreqBuff[MON_MSGMAXLEN / 5];
} C_MON_IO_BUFF;
#pragma pack(0)                         // Set to default packing // @suppress("No #pragma instructions")

#pragma pack (1,1,1)                    // "Little endian" // @suppress("No #pragma instructions")
// typedef for conversion word
typedef union
{
    U8 au8Data[2];
    U16 u16Data;
    U8* pu8Addr;
} C_WORD_BYTE;
#pragma pack(0)                         // Set to default packing // @suppress("No #pragma instructions")

//********************************** Global data declarations ( extern ) ***********************************************

//********************** External parameter / constant declarations ( extern const ) ***********************************

// PWM acquisition definition (TC_007-84)
extern void (*pvMON_Cycl1ms_GetPWDemod)(void);

extern U8 u8MON_MaxFreqChnls;           // No. of freq chnls applicable for EB0xx


//*************************************** Global func/proc prototypes **************************************************

//* Function boMON_ReadPWM *********************************************************************************************
//
//!  Function  : Read PWM value in eLAD03
//! @param[in] u8Channel: FI Channel [2 or 3]
//! @param[out] *pu32DutyCycle: duty cycle value read
//! @param[out] *pboUPToDateBit: Up to date bit
//! @returns    boReturn: TRUE if OK
//! @remarks ---
//**********************************************************************************************************************
extern BOOLEAN boMON_ReadPWM(U8 u8Channel, U32* pu32DutyCycle, BOOLEAN* pboUPToDateBit);

#endif

//  EndOfFile mon_cpu04.h **********************************************************************************************
