//**********************************************************************************************************************
//
//                            mon.h
//
//**********************************************************************************************************************
//
//                  Copyrights(c) 1997 by KNORR-BREMSE,
//             Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project IBC
//! @date    2023-12-04
//! @author  C. Brancolini
//
//**********************************************************************************************************************
//!
//! @file
//! @brief Interface definition for corresponding source file ( file-include, constants, macros, types, global data,
//!        functions and their parameters)
//!
//**********************************************************************************************************************
//
// History
// Date:           Author:             Revision / Changes:
// 2023-09-13      A. Mauro            1.00 Start
// 2023-12-04      C. Brancolini       Updated MON_SDI_CHANNEL_ERROR value, added MON_SHIFT_VAR_BY_8
//
//**********************************************************************************************************************

#ifndef MON_H
#define MON_H

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "std_defs.h"


//**************************************** Constant / macro definitions ( #define ) ************************************

//**************************************** Type definitions ( typedef ) ************************************************

//**********************************************************************************************************************
//! @name SDI responses
//**********************************************************************************************************************
//@{

//! Define SDI common responses
#define MON_SDI_NO_ERROR           ((U8)0)    //!< No error
#define MON_SDI_RANGE_ERROR        ((U8)2)    //!< addr range error
#define MON_SDI_CHANNEL_ERROR      ((U8)3)    //!< channel error for comm

#define MON_SDI_INVALID_COMMAND    ((U8)0xFE) //!< invalid TCH command

//@}

#define MON_SHIFT_VAR_BY_8         ((U8)8)    //!< Shift variable by 8 bits

//**************************************** Global data definitions *****************************************************

//**************************************** Global func/proc prototypes *************************************************

#endif
//** EndOfFile MON.H *********************************************************
