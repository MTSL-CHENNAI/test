//**********************************************************************************************************************
//
//                                   identexefwr.c
//**********************************************************************************************************************
//
//                   Copyrights(c) 2022 by KNORR-BREMSE,
//              Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project  IBC
//! @date     2023-11-20
//! @author   C. Brancolini
//
//**********************************************************************************************************************
//!
//! @file
//! @brief  Administration identification of software component ESRA Firmware  
//!  
//**********************************************************************************************************************
//
// History
// Date       Author          Changes
// 27.06.2011 A. Tenkeu       Initial revision
// 14.04.2017 V.Ingulkar      Updated as per new SWIDENT table for CCA
// 2017-05-15 V.Ingulkar      BCM_FWR review rework
// 2021-01-13 A.Gatare        Adapted for GenCA 6.11
// 2023-01-09 J. Lulli        Coding guidelines alignment
// 2023-11-20 C. Brancolini   Lint Plus clean up
//
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "identexefwr.h"                       // FWR Ident table
#include "cfg_ccc_rom_segtabfwr.h"             // extern data definitions for config table.
//**************************************** Constant / macro definitions ( #define ) ************************************

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************

const C_SW_COMP_IDENT cIdExeFwr =
  {
    {
    // Identifier (31+1=32 byte) ------------------
    "!!!!!!!EXE_IDENTIFICATION!!!!!!",

    // Version info of ident struct (4 byte) ------
    (U32)1,                 // u32VersionIdentStruct // @suppress("No magic numbers")

    // Copyright String (31+1=32 byte) ------------
    "Copyright (c) by Knorr Bremse  ",

    // Short Name ( 8 + 1 = 9 byte) ---------------
    "LADxx   ",

    // Description (31+1=32 byte) -----------------
    ///firmware
    //library
    //application
    "CBK Executable-FWR02          ",

    //Type of SW module (2 byte) -----------------
    (U16)1,  //u16SWType (Application, ESRA, COTS) // @suppress("No magic numbers")

    //STN number of SW module (15+1=16 byte) -----
    "STN 00000/00000",

    //Version number (12+1=13 byte) --------------
    "V xx.xx.xxxx",

    //Date of generation (10+1=11 byte) ----------
    "yyyy-mm-dd",

    //BuildID: Checksum without serial. (4+1=5 byte)--
    0x00000000,

    //Dummy build ID. (4 Byte)---
    0x00000000,

    //Reference to the segment table definition -
    ( const U32 *)(const void*)&cSegmentTablDefFwr
    },

  // FWR has not function table
  NULL,

  // FWR has no compatibility table
  NULL
  };

//******************* Modul global data segment ( static ) *************************************************************

//***************** Modul global constants ( static const ) ************************************************************

//****************** Local func/proc prototypes ( static ) *************************************************************

//** EndOfFile IDENTEXEFWR.C *******************************************************************************************
