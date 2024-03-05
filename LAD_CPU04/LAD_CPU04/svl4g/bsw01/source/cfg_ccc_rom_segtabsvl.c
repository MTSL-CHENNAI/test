//**********************************************************************************************************************
//
//                                        cfg_ccc_rom_segtblsvl.c
//
//**********************************************************************************************************************
//
//                                  Copyrights(c) 2022 by KNORR-BREMSE,
//                             Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project IBC
//! @date    2023-11-09
//! @author  C. Brancolini
//
//**********************************************************************************************************************
//! @file
//! @brief     Contain a board specific ROM segment configuration table for the ESRA Service Layer.
//!
//**********************************************************************************************************************
//
// History
// Date        Author        Changes
// 2011-04-20  A. Tenkeu     Start.
// 2012-03-09  P. Sigl       Adaptation to CB12A. Currently MM tool supports only 16 of the required 26 segments
// 2012-04-10  C. Baeuml     Adaption to EBxxx SVL starts at 0x00080000.
// 2020.09.17  A. Mauro      Added one segment: SVL starts at 0x00070000
// 2020-12-02  A.Gatare      Adapted for GenCA 6.11 Bc0025-271 Service ccc added in GenCA.Modified table as per
//                           service CCC and calculated CRC.
// 2023-01-09  J. Lulli      Coding guidelines alignment
// 2023-11-09  C. Brancolini Lint Plus clean up
//
//**********************************************************************************************************************

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "cfg_ccc_rom_segtabsvl.h"
#include "swident.h"
#include "ccc_rom.h"
//**************************************** Constant / macro definitions ( #define ) ************************************
#define ROM_SE
//**************************************** ROM Sectors Start Address ****************************************************
#define ROM_SEG2_START_ADDR           ((U32)0x00080000) // Start address of memory segment 2
#define ROM_SEG3_START_ADDR           ((U32)0x00090000) // Start address of memory segment 3
#define ROM_SEG4_START_ADDR           ((U32)0x00094000) // Start address of memory segment 4
#define ROM_SEG5_START_ADDR           ((U32)0x000A0000) // Start address of memory segment 5
#define ROM_SEG6_START_ADDR           ((U32)0x000B0000) // Start address of memory segment 6
#define ROM_SEG7_START_ADDR           ((U32)0x000C0000) // Start address of memory segment 7
#define ROM_SEG8_START_ADDR           ((U32)0x000D0000) // Start address of memory segment 8
#define ROM_SEG9_START_ADDR           ((U32)0x000E0000) // Start address of memory segment 9
#define ROM_SEG10_START_ADDR          ((U32)0x000F0000) // Start address of memory segment 10
//**************************************** ROM Sectors Length **********************************************************
#define ROM_SEG2_LENGTH               ((U32)0x00010000) // Length of memory segment 2
#define ROM_SEG3_LENGTH               ((U32)0x00004000) // Length of memory segment 3
#define ROM_SEG4_LENGTH               ((U32)0x0000C000) // Length of memory segment 4
#define ROM_SEG5_LENGTH               ((U32)0x00010000) // Length of memory segment 5
#define ROM_SEG6_LENGTH               ((U32)0x00010000) // Length of memory segment 6
#define ROM_SEG7_LENGTH               ((U32)0x00010000) // Length of memory segment 7
#define ROM_SEG8_LENGTH               ((U32)0x00010000) // Length of memory segment 8
#define ROM_SEG9_LENGTH               ((U32)0x00010000) // Length of memory segment 9
#define ROM_SEG10_LENGTH              ((U32)0x00010000) // Length of memory segment 10

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************

// ROM segment configuration table for the ESRA Service Layer
const CCC_ROM_SEGMENT_DEF_TAB( SVL ) cSegTablDefSvl =
{
    CCC_ROM_SEGMENT_TAB_DEF_ID,
    NUMBER_OF_SEGMENTS_SVL,
    eCCC_ROM_CRC32,
    {
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
        },
        {
            // Segment #7
            ROM_SEG7_START_ADDR,
            ROM_SEG7_LENGTH
        },
        {
            // Segment #8
            ROM_SEG8_START_ADDR,
            ROM_SEG8_LENGTH
        },
        {
            // Segment #9
            ROM_SEG9_START_ADDR,
            ROM_SEG9_LENGTH
        },
        {
            // Segment #10
            ROM_SEG10_START_ADDR,
            ROM_SEG10_LENGTH
        },
    },

    //Below CRC needs to be recalculated if there is change in the table. CRC to be kept in Big endian order.
    0xF19C2922U // @suppress("No magic numbers")
};
//******************* Modul global data segment ( static ) *************************************************************

//***************** Modul global constants ( static const ) ************************************************************

//****************** Local func/proc prototypes ( static ) *************************************************************

//** EndOfFile cfg_ccc_rom_segtblsvl.c *********************************************************************************
