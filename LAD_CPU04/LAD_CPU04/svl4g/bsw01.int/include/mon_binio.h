//**********************************************************************************************************************
///
///                                               mon_bionio.h
///
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
//!
//! @file
//! @brief Interface definition for accessing i/o-ports in binary mode (via MON service)
//!
//**********************************************************************************************************************
//  History
//  Date         Author        Changes
//  10.04.95 G.  Condra      0
//  14.09.95 G.  Condra      1   Removed 'CLOSE' fn.
//  04.10.95 G.  Condra      2   Rebuilt - conforms to SB.
//  28.10.95 G.  Condra      3   Corrected text.
//  01.11.95 G.  Condra      4   Tested by GCC V01.11.95.
//  18.12.95 G.  Becker      5   Introduced '#define's --
//                               -- for PORT0, 1, 2, 3, 4, 5, 6.
//  10.01.96 G.  Condra      6   Tested by GCC V10.01.96
//  07.03.96 S.  Widder      7   '#pragma non_banked' added
//  15.03.11 C.  Baeuml      8   Porting to MPC55xx.
//  08.08.11 C.  Baeuml      9   Comments.
//  30.05.13 H.  Shaikh     10   updated for Working Instructions
//  2023.09.14   A. Mauro   11   Alignment with CA: name changed and other
//  2023-12-20   C. Brancolini   Codan clean up
//
//**********************************************************************************************************************

#ifndef MON_BINIO_H
#define MON_BINIO_H

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************

#include    <STD_DEFS.H>

//***************** Constant / macro definitions ( #define ) ***********************************************************

//  The following '#define's cover the allowed BINIO PORT references.
#define PORT0   0                        //!< BinIO Port0
#define PORT1   1                        //!< BinIO Port1
#define PORT2   2                        //!< BinIO Port2
#define PORT3   3                        //!< BinIO Port3
#define PORT4   4                        //!< BinIO Port4
#define PORT5   5                        //!< BinIO Port5
#define PORT6   6                        //!< BinIO Port6

//************************************** Type definitions ( typedef ) **************************************************

//  The following typedef enumerates the allowed configurable states for
//  a BOOLEAN channel, namely configured as an INPUT or an OUTPUT.
//
    typedef enum    {eINPUT = 0,        //!< Board channel is Input
                     eOUTPUT = 1        //!< Board channel is Output
                    } E_BINIO_DIR;

//********************************** Global data declarations ( extern ) ***********************************************

//********************** External parameter / constant declarations ( extern const ) ***********************************

//*************************************** Global func/proc prototypes **************************************************

//* Function boMON_InitBinIoChannels ***********************************************************************************
//
//!  Function  : This function determines that whether the desired IO pins
//!              possess the attributes for BINARY input / output
//!              as requested. If they have then
//!              the pins are marked as INITIALISED and the hardware
//!              supporting the pins initialized accordingly.
//!              The 'direction' (input / output) of each pin initialized
//!              is recorded.
//!              Those pins which are initialized as outputs are written
//!              with the boolean value(s) passed in 'U8 u8InitState'.
//! @param[in] u8HWPortNum:  a U8 containing the HW PORT number.
//! @param[in] u8PinMask: a U8 containing a bit pattern,
//!                       representing the pins to be configured
//!                       within that port.
//! @param[in] eBINIODir: enum indicating whether the pins
//!                       are to be configured as inputs or
//!                       as outputs.
//! @param[in] u8InitState: U8 containing a bit pattern
//!                         representing the initial states for
//!                         those pins to be configured as outputs
//!                         (only relevant when outputs are to be configured).
//! @param[out] ---
//! @returns    boTRUE: if GO
//! @returns    boFALSE: if noG Bad Port Number passed in 'bHWPortNum'.
//!                             Pins Not Available - with desired
//!                             attributes on this board.
//! @remarks NOTE:   The port numbers allowed are defined in the
//!                  board specific configuration file.
//! @remarks NOTE:   The port-pin attributes for this board are listed
//!                  in the board specific configuration file.
//! @remarks NOTE:   No changes are registered, either on the
//!                  driver status, on the port configuration
//!                  hardware or on the I/O pins if any of the
//!                  parameters passed are determined incompatible.
//**********************************************************************************************************************
extern  BOOLEAN boMON_InitBinIoChannels
                    (U8 u8HWPortNum,
                     U8 u8PinMask,
                     E_BINIO_DIR eBINIODir,
                     U8 u8InitState
                    );

//* Function boMON_GetBinIOChannels ************************************************************************************
//
//!  Function  : This reads the current state of the desired port and
//!            : returns it together with the current port input / output
//!            : configuration.
//! @param[in] u8HWPortNum:  a U8 containing the HW PORT number.
//! @param[out] *pu8InputMask: points to where the port
//!                            input configuration is to
//!                            be written. A bit returned as a '1'
//!                            indicates the corresponding pin has
//!                            been configured as an input.
//! @param[out] *pu8CurrentState: points to where the port pin state
//!                               read is to be written!
//! @returns    boTRUE: if GO,
//! @returns    boFALSE: if noGO -   Bad Port Number passed in 'bHWPortNum'.
//! @remarks NOTE:   The port numbers allowed are defined in the
//!                  board specific configuration file.
//! @remarks NOTE:   No changes are registered, either on the
//!                  driver status, on the port configuration
//!                  hardware or on the I/O pins if any of the
//!                  parameters passed are determined incompatible.
//**********************************************************************************************************************
extern  BOOLEAN boMON_GetBinIOChannels
                     (U8  u8HWPortNum,
                      U8* pu8InputMask,
                      U8* pu8CurrentState
                     );

#endif
//* EndOfFile MON_BINIO.H **********************************************************************************************

