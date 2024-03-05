//**********************************************************************************************************************
//
//                                                   cfg1wire.c
//
//**********************************************************************************************************************
//
//                                        Copyrights(c) 2022 by KNORR-BREMSE,
//                                   Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   IBC
//! @date      2023-11-30
//! @author    C. Brancolini
//
//**********************************************************************************************************************
//! @file
//! @brief  Configuration of 1-wire driver
//**********************************************************************************************************************
// Date     Author        Changes
// 16.06.10 A. Tenkeu     Start.
// 01.03.11 A. Tenkeu     New define OWR_VALUE_READ_ZERO for the maximal 1-wire receive value from a read 0.
// 10.03.11 A. Tenkeu     Replace OWR_MAX_NUM_1WIRE_DEVICE_DESCR with OWR_NUM_1WIRE_DEVICE_DESCR
//                        and OWR_MAX_NUM_1WIRE_BUS_DESCR with OWR_NUM_1WIRE_BUS_DESCR.
// 2015-05-15 KH Duemer   Lint cleanup(Lint 9 / MISRA 2012)
// 2023-01-09 J. Lulli    Coding guidelines alignment
// 2023-05-15 C. Brancolini Lint clean up
// 2023-11-30 C. Brancolini Lint Plus clean up
//**********************************************************************************************************************

//***************************************** Compiler options ( #pragma ) ***********************************************

//************************************* Header / include files ( #include ) ********************************************
#include "cfg1wire_hw.h"
//*********************************** Constant / macro definitions ( #define ) *****************************************
#define ONE_WIRE_BUS_ID0      ((U8)0xFE)
//! Number of 1-wire devices descriptors(MIN-value = 1, MAX-value = 255)
//!(this configuration is board specific).
#define OWR_NUM_1WIRE_DEVICE_DESCR  2


//! Number of 1-wire bus descriptors(MIN-value = 1, MAX-value = 255)
//!(this configuration is board specific).
//! Remarks: The number of 1-wire bus descriptor must be equals the
//! the number of configured UART interfaces use for 1-wire communication.
#define OWR_NUM_1WIRE_BUS_DESCR     1
//***************************************** Type definitions ( typedef ) ***********************************************

//******************************************* Global data definitions **************************************************

//************************************ Global constant definitions ( const ) *******************************************
//! Memory allocation for 1-wire devices descriptors and
//! 1-wire bus descriptors.
OWR_ALLOC_MEM( OWR_NUM_1WIRE_BUS_DESCR, OWR_NUM_1WIRE_DEVICE_DESCR )  // @suppress("Wrong derived data type") // @suppress("Avoid Global Variables")

//! Configuration table for asynchronous serial interfaces (UART interfaces)
//! that are used for 1-wire communication.
const OWR_UART_BUS cOWRUARTBUS[] = // @suppress("Wrong derived data type")
//Note: Suppression of "Wrong derived data type", this warning comes from the naming convention violation of OWR_UART_BUS
    {
        // Inhibit lint message 708: union initialization.
        // Used .u32Raw field of .cRamDeviceType union
        //lint -save -e708
        {
            // Inhibit lint message 708: union initialization. Used .u32Raw field of .cRamDeviceType union.
            OWR_UART_INTERFACE_CONFIG(0, OWR_TYPE_ETPU)  //!< configuration for ETPU asynchronous serial interface 0.
        }                                             //!< device type = ETPU, channel number = 0.
        //lint -restore
    };

//! Configuration table for the maximal UART - data value read from
//! 1-wire bus when the 1-wire bit "0" is read.
const U8 u8cOWR_MAX_VALUE[] = // @suppress("Wrong prefix")
{
//Note: Suppression of "Wrong prefix", renaming of this variable is not possible
               ONE_WIRE_BUS_ID0      //!< Configuration for the 1-wire bus ID0.
};

//************************************* Modul global data segment ( static ) *******************************************

//*********************************** Modul global constants ( static const ) ******************************************

//************************************ Local func/proc prototypes ( static ) *******************************************

//* EndOfFile cfg1wire_hw.c ********************************************************************************************
