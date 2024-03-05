// *********************************************************************************************************************
//
//                                                   cfgesci.c
//
// *********************************************************************************************************************
//
//                                        Copyrights(c) 2022 by KNORR-BREMSE,
//                                   Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   IBC
//! @date      2023-11-28
//! @author    C. Brancolini
//
// *********************************************************************************************************************
//!
//! @file
//! @brief Configuration tables for ESCI driver
//!
// *********************************************************************************************************************
//
//  History
//  Date        Author       Changes:
//  07.10.2008  A.Raspanti   Start
//  03.11.2008  M.Belluomini Continue
//  28.11.2008  A.Raspanti   File name changed from c55xesci to cfgesci
//  17.12.2008  A.Raspanti   Updated release version
//  16.03.2010  Z.Miskatovic eSCI and buffer declaration removed here buffer size allocate adapted for new buffer layout
//  02.12.2011  W.Eckerl     enhanced DMA handling with channel linking and scatter/gather implemented
//  27.02.2012  P. Sigl      FWR Separation: Use of function table provided by service layer
//  29.04.2013  K.Chaudhari  Updated for PC Lint Errors and warning.
//  2015-05-15  KH Duemer    cleanup(Lint 9 / MISRA 2012)
//  2017-04-14  V.Ingulkar   ed as per new SWIDENT table for CCA
//  2017-05-15  V.Ingulkar   WR revie rework
//  2018-06-08  A. Mauro     Adatptations for CPU04
//  2020-10-15  A. Mauro     Lint clean ups
//  2020-12-03  A.Gatare     Adapted for GenCA 6.11
//  2023-01-09  J. Lulli     Coding guidelines alignment
//  2023-11-28  C. Brancolini Lint Plus cleanup
//
// *********************************************************************************************************************

// ***************************************** Compiler options ( #pragma ) **********************************************

// ************************************* Header / include files ( #include ) *******************************************
#include "std_defs.h"
#include "MPC5554.h"
#include "55xdma.h"
#include "cfgesci.h"
#include "cfgesci_def.h"
#include "functabexe.h"
#include "bcl_hal_s.h"
#include "kb_ret.h"

// *********************************** Constant / macro definitions ( #define ) ****************************************
#define ESCI_TX_RX_QUEUE_SIZE ( ( ( GET_MAX_CFG_UART((U32)ID_UART_ESCIA) * (U16)MAXLEN_BUF_55XXESCI ) * (U8)2 ) + \
                                  (U16)MAXLEN_BUF_55XXESCI )
// ***************************************** Type definitions ( typedef ) **********************************************

// ******************************************* Global data definitions *************************************************

// ************************************ Global constant definitions ( const ) ******************************************

const ESCIDEVICES acEsciDevices[]= // @suppress("Wrong derived data type")
{
    //Inhibit lint messages caused by address to object pointer conversion needed for memory mapped IO access
    //lint -save -e9048 -e9078
    {ID_UART_ESCIA, DMADEV_SERVICE(DMA_ESCI, DMA_ESCI_A, DMA_DIRTX),
        DMADEV_SERVICE(DMA_ESCI, DMA_ESCI_A, DMA_DIRRX), &(ESCI_A)},
    //lint -restore
    {MAX_UART, 0, 0, ( struct ESCI_tag *)0}
};

//Inhibit lint messages 9029 caused by GET_MAX_CFG_UART macro defined in GenMPC55xx.
//lint -save -e9029
const U32   u32MaxCfgUart        = GET_MAX_CFG_UART((U32)ID_UART_ESCIA);
const U32   u32eSCITxRxQueueSize = ESCI_TX_RX_QUEUE_SIZE;
//lint -restore
const U16   u16eSCIBuffLength    = MAXLEN_BUF_55XXESCI;

// **************************************** Module global data segment ( static ) **************************************
//Inhibit lint messages 9029 caused by GET_MAX_CFG_UART macro defined in GenMPC55xx.
//lint -save -e9029
                                    // Array for UART descriptor
static U8 au8DescrUart[GET_MAX_CFG_UART((U32)ID_UART_ESCIA)*sizeof(UARTCH)];
                                   // Buffer for transmit and receive
static U8 au8ESCI_TXRXQUEUE[ ESCI_TX_RX_QUEUE_SIZE ];
//lint -restore

// ************************************* Module global constants ( static const ) **************************************

// ************************************** Local func/proc prototypes ( static ) ****************************************

//**********************************************************************************************************************
// Function s32ExtCardTestResourceExtIrq
// *********************************************************************************************************************
S32 s32ExtCardTestResourceExtIrq(  UARTID eIdUart, U32 u32NrIrq )
{
//******************************** Function scope data *****************************************************************
    const C_FTAB* pcFctTab;
    const C_BCL_FCT_TAB_V1* pcFctTabExe;
    const tcFctTab_55XESCI* pcFctTab_55XESCI; // @suppress("Wrong derived data type")
    //Note: Suppression of "Wrong derived data type", this warning comes
    //from the naming convention violation of tcFctTab_55XESCI

    //******************************** Function code ********************************************************************

    // Check if pointer to call back functions is available.
    pcFctTab = pcBCL_HAL_GetFctTabExePtr();
    if ( pcFctTab == KB_NULL_PTR )
    {
        // Error: Pointer to function table is not set
        return (KB_RET_ERR_START_GENERIC);
    }

    //Inhibit lint messages 9079 caused by C_FTAB and C_BCL_FCT_TAB_V1 defined in GenMPC55xx.
    //lint -save -e9079
    pcFctTabExe = pcFctTab->pvFctTab;
    pcFctTab_55XESCI = pcFctTabExe->pvFctTab_55XESCI;
    //lint -restore

    // Wrap function with board custom code
    return ( (*pcFctTab_55XESCI->ps32fctTestResIrq)(eIdUart ,u32NrIrq) );
}
//**  EndOfFunction s32ExtCardSetResourceExtIrq ************************************************************************

//**********************************************************************************************************************
//  Function s32ExtCardSetResourceExtIrq
//**********************************************************************************************************************
S32 s32ExtCardSetResourceExtIrq(  UARTID eIdUart )
{
//******************************** Function scope data *****************************************************************
    const C_FTAB* pcFctTab;
    const C_BCL_FCT_TAB_V1* pcFctTabExe;
    const tcFctTab_55XESCI* pcFctTab_55XESCI; // @suppress("Wrong derived data type")
    //Note: Suppression of "Wrong derived data type", this warning comes
    //from the naming convention violation of tcFctTab_55XESCI

//*********************************** Function code ********************************************************************

    // Check if pointer to call back functions is available.
    pcFctTab = pcBCL_HAL_GetFctTabExePtr();
    if ( pcFctTab == KB_NULL_PTR )
    {
        // Error: Pointer to function table is not set
        return (KB_RET_ERR_START_GENERIC);
    }

    //Inhibit lint messages 9079 caused by C_FTAB and C_BCL_FCT_TAB_V1 defined in GenMPC55xx.
    //lint -save -e9079
    pcFctTabExe = pcFctTab->pvFctTab;
    pcFctTab_55XESCI = pcFctTabExe->pvFctTab_55XESCI;
    //lint -restore

    // Wrap function with board custom code
    return ( (*pcFctTab_55XESCI->ps32fctSetResIrq)(eIdUart) );
}
//** EndOfFunction s32ExtCardSetResourceExtIrq *************************************************************************

//**********************************************************************************************************************
//  Function ppu8GeteSCITXRXBufferAddress
//**********************************************************************************************************************
U8** ppu8GeteSCITXRXBufferAddress( void )
{
//******************************** Function scope data *****************************************************************

//*********************************** Function code ********************************************************************
    // Inhibit lint message 545 "taking address of array".
    // Inhibit lint message 728 "static variable not explicitly initialized":
    // BSS segment is initialized to 0 at startup.
    return ((U8 **)(void*)(&au8ESCI_TXRXQUEUE)); //lint !e545 !e728
}
//** EndOfFunction u8GeteSCITXRXBufferAddress  *************************************************************************

//**********************************************************************************************************************
//  Function ppu8GeteSCIbDescrUartBufferAddress
//**********************************************************************************************************************
U8** ppu8GeteSCIbDescrUartBufferAddress( void )
{
//******************************** Function scope data *****************************************************************

//*********************************** Function code ********************************************************************
    // Inhibit lint message 545 "taking address of array"
    // Inhibit lint message 728 "static variable not explicitly initialized":
    // BSS segment is initialized to 0 at startup.
    return ((U8 **)(void*)(&au8DescrUart)); //lint !e545 !e728
}
//** EndOfFunction u8GeteSCIbDescrUartBufferAddress  *******************************************************************


//** EndOfFile cgfesci.c ***********************************************************************************************
