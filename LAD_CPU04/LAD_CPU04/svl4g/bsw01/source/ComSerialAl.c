//**********************************************************************************************************************
//
//                                ComSerialAl.c
//
//**********************************************************************************************************************
//
//                   Copyrights(c) 2022 by KNORR-BREMSE,
//              Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project IBC
//! @date    2023-11-22
//! @author  C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file  ComSerialAl.c
//! @brief Adaption layer file for accessing the serial communication data required by ComSerial.
//!
//**********************************************************************************************************************
//
// History
// Date        Author         Changes
// 2019-06-21  A. Chaudhary   Start
// 2023-01-09  J. Lulli       Coding guidelines alignment
// 2023-11-22  C. Brancolini  Lint Plus clean up
//
//**********************************************************************************************************************

//********************** Compiler options ( #pragma ) ******************************************************************

//****************** Header / include files ( #include ) ***************************************************************

#include <string.h>                     // memcpy
#include "kb_types.h"
#include "CoErrno.h"
#include "ComSerialAl.h"

//**************************************** Constant / macro definitions ( #define ) ************************************

//**********************************************************************************************************************
//
//! @name   Macros local use
//
//**********************************************************************************************************************
//@{


//@}
//**********************************************************************************************************************

//********************** Type definitions ( typedef ) ******************************************************************


//************************ Global data definitions *********************************************************************

//***************** Global constant definitions ( const ) **************************************************************

//****************** Begin --- Global definitions For Component Testing ************************************************
#ifdef MODULTEST
const char cRevCA_AL_ComSerialAl[] = "$Revision: 422 $";
#endif
//****************** End ---Global definitions For Component Testing ***************************************************

//****************** Module global data segment ( static ) *************************************************************


//**************** Module global constants ( static const ) ************************************************************

//***************** Local func/proc prototypes ( static ) **************************************************************

//* EndOfHeader ********************************************************************************************************

//TODO:
//This file contains empty implemenation of ComSerialAl for eval boards.
//This is just added here to resolve the compilation errors.
//There is no underlying GenCA UART handler service, hence this can not be a part of LAD_CA/code/CA_Al.
//Currently ComSerialAl will be a part of board specific sw.
//
//Also, we can not test the serial communication for UMB broadcast between CID and eval boards!!!
//
//* Function definitions ***********************************************************************************************

// Function s16ComSerialAl_InitSetConfig(const T_COMSERIALAL_UART_MSG_PACKET cStartEndIndication)
S16 s16ComSerialAl_InitSetConfig (const T_COMSERIALAL_UART_MSG_PACKET cStartEndIndication)
{
//************************************************ Function scope data *************************************************
    S16 s16Return = CO_ERROR_NONE;                  // Function return

//*************************************** Function scope static data declaration ***************************************

//*************************************************** Function code ****************************************************

    (void)cStartEndIndication; // unused parameter

    // Return result
    return (s16Return);
}
//** EndOfFunction s16ComSerialAl_InitSetConfig *************************************************************************************

// Function s16ComSerialAl_SendPacket
S16 s16ComSerialAl_SendPacket(const T_COMSERIALAL_UART_MSG_PACKET* const pcPacket)
{
//************************************************ Function scope data *************************************************
    S16 s16Return = CO_ERROR_NONE;                  // Function return

    (void)pcPacket; // unused parameter
//*************************************************** Function code ****************************************************

    // Return result
    return (s16Return);
}
//** EndOfFunction s16ComSerialAl_SendPacket ***************************************************************************

// Function s16ComSerialAl_ReadNextPacket
S16 s16ComSerialAl_ReadNextPacket ( T_COMSERIALAL_UART_MSG_PACKET* const pcPacket )
{
//************************************************ Function scope data *************************************************
    S16 s16Return = CO_ERROR_NONE;                  // Function return

//*************************************** Function scope static data declaration ***************************************

//*************************************************** Function code ****************************************************

    (void)pcPacket; // unused parameter

    // Currently no read message functionality required on LAD.

    // Return Value
    return (s16Return);
}
//** EndOfFunction s16ComSerialAl_ReadNextPacket **************************************************************************

// Function s16ComSerialAl_StopReception
S16 s16ComSerialAl_StopReception ( void ) //lint !e957 Missing void in function prototype (issue related to FWK)
{
//************************************************ Function scope data *************************************************

    S16 s16Return = CO_ERROR_NONE;                      // Function return

//*************************************** Function scope static data declaration ***************************************

//*************************************************** Function code ****************************************************

    // Return Value
    return (s16Return);
}
//** EndOfFunction s16ComSerialAl_StopReception **************************************************************************

//* EndOfFile ComSerialAl.c *******************************************************
