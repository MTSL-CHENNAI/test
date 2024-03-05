//**********************************************************************************************************************
//
//                                               identexesvl.c
//**********************************************************************************************************************
//
//                                     Copyrights(c) 2022 by KNORR-BREMSE,
//                                Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project  IBC
//! @date     2023-11-30
//! @author   C. Brancolini
//
//**********************************************************************************************************************
//!
//! @file
//! @brief  Administration identification of software component
//!
//**********************************************************************************************************************
//
// History
// Date       Author      Changes:
// 03.09.2009 W. Hilbk    Initial revision (identexe.c)
// 09.03.2012 P. Sigl     Pointer to function table and segment
//                        table added.
// 09.12.2013 P. Sigl     Comment changed
// 28.06.2016 S.Patapati  Adapted to CPU05 based LAD
// 2017-04-14 V.Ingulkar  Reworked module for CCA
// 2020-02-13 A. Mauro    Lint clean ups
// 2021-01-12 A.Gatare    Adpated as per GenCA6.11
// 2023-01-09 J. Lulli    Coding guidelines alignment
// 2023-11-30 C. Brancolini Lint Plus clean up
//
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "cfg_ccc_rom_segtabsvl.h"      // extern data definitions for
#include "STD_DEFS.H"                   // Standard definitions
#include "swident.h"                    // typedef of SWCOMP_IDENT
#include "functabexe.h"                 // Executable function table interface
#include "bcm_fwr.h"
#include "identexesvl.h"
#include "identexesvl_cpu04.h"

//**************************************** Constant / macro definitions ( #define ) ************************************

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************



const C_SW_COMP_IDENT cSwIdExe =
  {
    {
    // Identifier (31+1=32 byte) ------------------*/
    "!!!!!!!EXE_IDENTIFICATION!!!!!!",

    // Version info of ident struct (4 byte) ------*/
    (U32)1,                 // u32VersionIdentStruct // @suppress("No magic numbers")

    // Copyright String (31+1=32 byte) ------------*/
    "Copyright (c) by Knorr Bremse  ",

    // Short Name ( 8 + 1 = 9 byte) ---------------
    "LADxx   ",

    // Description (31+1=32 byte) -----------------
    // firmware
    // library
    // application
    "CBK Executable-APP02          ",

    //* Type of SW module (2 byte) -----------------
    (U16)1,  //* u16SWType (Application, ESRA, COTS) // @suppress("No magic numbers")

    //* STN number of SW module (15+1=16 byte) -----
    "STN 00000/00000",

    //* Version number (12+1=13 byte) --------------
    "V xx.xx.xxxx",

    //* Date of generation (10+1=11 byte) ----------
    "yyyy-mm-dd",

    //* BuildID1: Checksum without serial. (4+1=5 byte)--
    0x00000000,
    //* Dummy build ID. (4 Byte)---*/
    0x00000000,

    // Reference to the segment table definition -
    ( const U32* )( const void* )&cSegTablDefSvl
    },

    &cFctTabExe,                       // Pointer to CCA/nonCCA func table

    &cCompTabExe                        // Pointer to compatibility table
};


//******************* Modul global data segment ( static ) *************************************************************

//***************** Modul global constants ( static const ) ************************************************************

//****************** Local func/proc prototypes ( static ) *************************************************************

//** EndOfFile identexesvl.c ******************************************************************************************
