//**********************************************************************************************************************
//                                                                        
//                               cgftpu.c                                 
//                                                                        
//**********************************************************************************************************************
//                                                                        
//                  Copyrights(c) 2022 by KNORR-BREMSE,                   
//             Systeme fuer Schienenfahrzeuge GmbH, Muenchen              
//                                                                        
//! @project  IBC                                                    
//! @date     2023-11-30                                            
//! @author   C. Brancolini                                          
//                                                                        
//**********************************************************************************************************************
//!
//! @file   cgftpu.c
//! @brief  Configuration table for TPU asynchronous serial interfaces.  
//!                                                                                                                                             
//**********************************************************************************************************************
//
// History
// Date       Author       Changes:                                       
// 09.09.2010 A.Tenkeu     Start                                          
// 08.04.2011 A.Tenkeu     Added channel parameter allocation config     
// 19.04.2011 P. Sigl      Include cfg_55xxsiu_cb12a.h               
// 06.03.2012 P. Sigl      ... renamed: cfg_55xxsiu.h    
// 03.07.2014 K. Chaudha   Pin configuration added   
//                         JIRA Ticket resolved : BC_002-412
// 25.09.2014 K. Chaudha   Modified to implement eTPUB channels for 
//                         for MPC5566. eTPU Number channels      
//                         configured from Board specific     
//                         configuration file.             
//                         JIRA Ticket resolved : BC_002-1221    
// 28.11.2014 G. Badve     JIRA BC_002-1396 resolved:Array                
//                         boFlagPinFuncActivation[] is removed and       
//                         not user configurable.                         
// 2015-05-15 KH Duemer    Lint cleanup(Lint 9 / MISRA 2012)              
// 2018-06-08 A. Mauro     Adaptations for CPU04                          
// 2023-01-09 J. Lulli     Coding guidelines alignment                    
// 2023-11-30 C. Brancolini Lint Plus clean up
//
//**********************************************************************************************************************
//Note: Suppression of "Wrong derived data type", these warnings come from
//      the naming convention violation of their respective structures

//********************** Compiler options ( #pragma ) ******************************************************************

//****************** Header / include files ( #include ) ***************************************************************
#include "std_defs.h"
#include "55xtpu.h"
#include "cfgtpu_cpu04.h"

//**************** Constant / macro definitions ( #define ) ************************************************************

//! Maximum number of UART interfaces.( Max 16 channel)
#define MAX_TPU_UART_INTERFACES ((U8)16)

//! Max eTPU channel number.
#define TPU_MAX_ETPU_CHANNELNUMBER ((U8)32)

//! CPU prescaler
#define TPU_CPU_PRESCALER1     ((U16)8)
#define TPU_CPU_PRESCALER2     ((U8)2)
//********************** Type definitions ( typedef ) ******************************************************************

//************************ Global data definitions *********************************************************************

//***************** Global constant definitions ( const ) **************************************************************

//! Configuration table that contain the PCR index of the
//! TPU asynchronous serial interfaces(UART Rx and Tx channels)
//! use for 1-wire communication.
const tcCFG_PCR_TPU_UART cCFG_PCR_TPU_UART[MAX_TPU_UART_INTERFACES] = // @suppress("Wrong derived data type")
{
    {&u161WIRE_CRM_TX_PCR,    &u161WIRE_CRM_RX_PCR},
    //!< PCR-index for TPU UART-interface 0
    //!< use for 1-wire communication.
    {NULL,                NULL},
    {NULL,                NULL},
    {NULL,                NULL},
    {NULL,                NULL},
    {NULL,                NULL},
    {NULL,                NULL},
    {NULL,                NULL},
    {NULL,                NULL},
    {NULL,                NULL},
    {NULL,                NULL},
    {NULL,                NULL},
    {NULL,                NULL},
    {NULL,                NULL},
    {NULL,                NULL},
    {NULL,                NULL}
};

//! TPU global configuration for CPU03 board
const TPU_CONFIG cTPUConf = { // @suppress("Wrong derived data type")
    80.0f,   //!< CPU board system frequency. // @suppress("No magic numbers")
    //!< CPU03 system frequency = 80.0f MHz
    //!< CPU04 system frequency = 130.0f MHz.
    DIV8,    //!< TPU filter clock.
    TPU_CPU_PRESCALER1,       //!< Timebase 1 prescaler.
    TPU_CPU_PRESCALER2        //!< Timebase 2 prescaler.
};

//! Channel parameter allocation (0: static, 1: dynamic)
const U8 u8TPUConfDynAlloc    = 1; // @suppress("No magic numbers")

//! Number of channel parameters in case of static allocation
const U8 u8TPUConfLengthAlloc = 0;

//UART PIN FUNCTION
const TPU_UART_PIN_FUNCTION cTPU_Uart_Pin_Functions[MAX_TPU_UART_INTERFACES] = // @suppress("Wrong derived data type")
{
    {{PA_ETPUA1_OUT, PA_ETPUA0_IN}},   //!< Pin function for cripto chip device.
    {{PA_ETPUA3_OUT, PA_ETPUA2_IN}},    //!< Pin function for coding device.
    {{0,                0}},
    {{0,                0}},
    {{0,                0}},
    {{0,                0}},
    {{0,                0}},
    {{0,                0}},
    {{0,                0}},
    {{0,                0}},
    {{0,                0}},
    {{0,                0}},
    {{0,                0}},
    {{0,                0}},
    {{0,                0}},
    {{0,                0}}
};
//

//! Max Number of etpu channels
const U8 u8TPUMaxChannelNumber = TPU_MAX_ETPU_CHANNELNUMBER;

const U8 u8TPUMaxUARTChannelNumber = MAX_TPU_UART_INTERFACES;

//****************** Modul global data segment ( static ) **************************************************************

//**************** Modul global constants ( static const ) *************************************************************

//***************** Local func/proc prototypes ( static ) **************************************************************

//** EndOfFile cgftpu.c ************************************************************************************************
