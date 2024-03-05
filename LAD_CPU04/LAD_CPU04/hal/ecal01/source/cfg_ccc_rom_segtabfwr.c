//**********************************************************************************************************************
//
//                               cfg_ccc_rom_segtabfwr.c
//
//**********************************************************************************************************************
//
//                   Copyrights(c) 2022 by KNORR-BREMSE,
//              Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   ESRA BSW3G55xx
//! @date      2020-11-28
//! @author    A.Gatare
//
//**********************************************************************************************************************
//! @file
//! @brief   Contain a board specific ROM segment configuration
//!          table for the ESRA Firmware Layer.
//!
//**********************************************************************************************************************
// Date            Author        Changes:
// 20.04.11        A. Tenkeu     Start.
// 04.05.12        P. Sigl       NUMBER_OF_SEGMENTS_FWR used
// 17.09.20        A. Mauro      Removed one segment (0x00070000)
//                               service CCC and calculated CRC.
// 2020-11-28      A.Gatare      Adapted for GenCA 6.11 Bc0025-271 Service ccc added in GenCA.Modified table
//                               as per service CCC and calculated CRC.
// 2023-01-09      J. Lulli      Coding guidelines alignment
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "cfg_ccc_rom_segtabfwr.h"
#include "ccc_rom.h"
//**************************************** Constant / macro definitions ( #define ) ************************************
#define ROM_SEG1_START_ADDR       ((U32)0x00020000)
#define ROM_SEG2_START_ADDR       ((U32)0x00030000)
#define ROM_SEG3_START_ADDR       ((U32)0x00040000)
#define ROM_SEG4_START_ADDR       ((U32)0x00050000)
#define ROM_SEG5_START_ADDR       ((U32)0x00060000)
#define ROM_SEG6_START_ADDR       ((U32)0x00070000)

#define ROM_SEG1_LENGTH           ((U32)0x00010000)
#define ROM_SEG2_LENGTH           ((U32)0x00010000)
#define ROM_SEG3_LENGTH           ((U32)0x00010000)
#define ROM_SEG4_LENGTH           ((U32)0x00010000)
#define ROM_SEG5_LENGTH           ((U32)0x00010000)
#define ROM_SEG6_LENGTH           ((U32)0x00010000)
//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************
// ROM segment configuration table for the ESRA Firmware
const CCC_ROM_SEGMENT_DEF_TAB( FWR ) cSegmentTablDefFwr =
{
CCC_ROM_SEGMENT_TAB_DEF_ID,
NUMBER_OF_SEGMENTS_FWR,
eCCC_ROM_CRC32,
{
    {
        // Segment #1
        ROM_SEG1_START_ADDR,
        ROM_SEG1_LENGTH
    },
    {
        // Segment #2
        ROM_SEG2_START_ADDR,
        ROM_SEG2_LENGTH
    },
    {
        // Segment #3
        ROM_SEG3_START_ADDR,
        ROM_SEG3_LENGTH
    },
    {
        // Segment #4
        ROM_SEG4_START_ADDR,
        ROM_SEG4_LENGTH
    },
    {
        // Segment #5
        ROM_SEG5_START_ADDR,
        ROM_SEG5_LENGTH
    },
    {
        // Segment #6
        ROM_SEG6_START_ADDR,
        ROM_SEG6_LENGTH
    }

},
//Below CRC needs to be recalculated if there is any change in the table. CRC to be added in Big Endian.
0x3D515A99 // @suppress("No magic numbers")
};

//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************

//** EndOfFile cfg_ccc_rom_segtabfwr.c*********************************************************************************
