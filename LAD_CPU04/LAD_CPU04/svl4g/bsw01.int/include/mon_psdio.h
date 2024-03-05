//**********************************************************************************************************************
//
//                                             mon_psdio.h
//
//**********************************************************************************************************************
//
//                                      Copyrights(c) 2022 by KNORR-BREMSE,
//                                 Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   IBC
//! @date      2023-12-05
//! @author    C. Brancolini
//
//**********************************************************************************************************************
//!
//! @file
//! @brief Interface definition for accessing I/O PSD ports (via MON service)
//!
//**********************************************************************************************************************
//  History
//  Date         Author        Changes
//  08.03.96  G. Condra        0   Creation.
//  11.04.96  G. Condra        1   Tested by GCC V11.04.96
//  13.06.96  G. Condra        2   Renamed 'E_INPUT' to E_PSD_INPUT--
//                                 -- and 'E_OUTPUT' to E_PSD_OUTPUT.
//  18.03.11  C. Baeuml        3   Porting to MPC55xx.
//  2023.09.14   A. Mauro      4   Alignment with CA: name changed and other
//  2023-12-05   C. Brancolini     Codan clean up
//
//**********************************************************************************************************************

#ifndef MON_PSDIO_H
#define MON_PSDIO_H

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include    <STD_DEFS.H>

//***************** Constant / macro definitions ( #define ) ***********************************************************

//************************************** Type definitions ( typedef ) **************************************************

//  The following typedef enumerates the allowed configurable states for
//  a BOOLEAN channel, namely configured as an INPUT or an OUTPUT.
//
typedef enum    {ePSD_INPUT = 0,                  //!< PSD is an input
                 ePSD_OUTPUT = 1                  //!< PSD is an output
                } E_PSDIO_DIR;

//********************************** Global data declarations ( extern ) ***********************************************

//********************** External parameter / constant declarations ( extern const ) ***********************************

//*************************************** Global func/proc prototypes **************************************************


//* Function boMON_InitPSDIOChannels ***********************************************************************************
//
//!  Function  : This function determines that the desired IO pins
//!              posess the attributes for BINARY input / output
//!              as requested. If they have then
//!              the pins are marked as INITIALISED and the hardware
//!              supporting the pins initialised accordingly.
//!              The 'direction' (input / output) of each pin initialised
//!              is recorded.
//!              Those pins which are initialised as outputs are written
//!              with the boolean value(s) passed in 'U16 wInitState'.
//!              The PORT is implicitly located in the the
//!              Programmable System Device (PSD), typically PSD301.
//! @param[in]  u16PinMask: a U16 containing a bit pattern,
//!                         representing the pins to be configured
//!                         within the PSD port.
//! @param[in]  ePSDIODir: enum indicating whether the pins
//!                        are to be configured as inputs or
//!                        as outputs.
//! @param[in]  u16InitState: U16 containing a bit pattern
//!                           representing the initial states for
//!                           those pins to be configured as outputs
//!                           (only relevant when outputs are
//!                           to be configured).
//! @param[out] ---
//! @returns    boTRUE if GO
//! @returns    boFALSE if noGO -   Pins Not Available - with desired
//!            :                    attributes on this board.
//! @Remarks   :  NOTE:   The port-pin attributes for this board are listed
//!                       in the board specific configuration file.
//!               NOTE:   No changes are registered, either on the
//!                       driver status, on the port configuration
//!                       hardware or on the I/O pins if any of the
//!                       parameters passed are determined incompatible.
//**********************************************************************************************************************
extern  BOOLEAN boMON_InitPSDIOChannels
                    (U16 u16PinMask,
                     E_PSDIO_DIR ePSDIODir,
                     U16 u16InitState
                    );

//  Function boMON_GetPSDIOChannels*******************************************
//
//  Function  : This reads the current state of the PSD port and
//            : returns it together with the current port input / output
//            : configuration.
//            : The PORT is implicitly located in the the
//            : Programmable System Device (PSD), typically PSD301.
//  Param, In : U16 *pu16InputMask - points to where the port
//            :                     input configuration is to
//            :                     be written. A bit returned as a '1'
//            :                     indicates the corresponding pin has
//            :                     been configured as an input.
//            : U16 *pu16CurrentState -  points to where the port pin state
//            :                         read is to be written!
//  Param, Out: Current port I/O configuration,
//            : Current port state.
//  Return    : boTRUE if GO,
//            : boFALSE if noGO -   Never.
//  Data, In  :
//  Data, Out :
//            : NOTE:   No changes are registered, either on the
//            :         driver status, on the port configuration
//            :         hardware or on the I/O pins if any of the
//            :         parameters passed are determined incompatible.
//**********************************************************************************************************************
extern  BOOLEAN boMON_GetPSDIOChannels
                     (U16* pu16InputMask,
                      U16* pu16CurrentState
                     );



#endif
//** EndOfFile MON_PSDIO.H *********************************************************************************************

