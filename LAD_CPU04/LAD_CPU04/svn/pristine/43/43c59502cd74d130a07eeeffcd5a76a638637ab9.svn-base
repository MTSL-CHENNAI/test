//**********************************************************************************************************************
//
//                                         cfg_ccc_rom_segtblfwr.h
//
//**********************************************************************************************************************
//
//                                     Copyrights(c) 2022 by KNORR-BREMSE,
//                                         Rail Vehicle Systems, Munich
//
//! @project CBK
//! @date    2020-11-30
//! @author  A. Gatare
//
//**********************************************************************************************************************
//! @file
//! @brief  external reference for:
//! - Default ROM area table configuration located in the ESRA Firmware.
//! - ROM area segment table configuration for ESRA Firmware.
//! - Executable IDENT table configuration for the software component ESRA Firmware.
//**********************************************************************************************************************
// Date       Author      Changes:
// 20.04.11   A. Tenkeu   Start
// 29.03.12   P. Sigl     NUMBER_OF_AREAS_FWR, NUMBER_OF_SEGMENTS_FWR
//                        introduced.
// 26.06.12   B.Ismagulov Move FWR-DRV from 0x30000 to 0x40000
// 2015-06-11 KH Duemer   Lint cleanup (Lint 9 / MISRA 2012)
// 2017-04-14 V.Ingulkar  Updated as per new SWIDENT table for CCA
// 2017-05-15 V.Ingulkar  BCM_FWR revie rework
// 2020.09.17 A. Mauro    Removed one segment
// 2020-11-30 A.Gatare    Adapted for GenCA 6.11 Bc0025-271 Service ccc added in GenCA.Removed configurations for
//                        ROM area table. Renamed file to cfg_ccc_rom_romtabfwr.h to cfg_ccc_rom_segtblfwr.h
//**********************************************************************************************************************

#ifndef CFG_CCC_ROM_SEGTABFWR_H
#define CFG_CCC_ROM_SEGTABFWR_H

//**************************************** Compiler options ( #pragma ) ************************************************

//**************************************** Header / include files ( #include ) *****************************************
#include "ccc_rom.h"
//**************************************** Constant / macro definitions ( #define ) ************************************
#define NUMBER_OF_SEGMENTS_FWR  6

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data definitions *****************************************************

//**************************************** Global constant definitions ( const ) ***************************************

//! ROM area segment table configuration for firmware
TYPEDEF_CCC_ROM_SEGMENT_DEF_TAB( FWR, NUMBER_OF_SEGMENTS_FWR )

extern const CCC_ROM_SEGMENT_DEF_TAB( FWR ) cSegmentTablDefFwr;
//**************************************** Module global data segment ( static ) ***************************************

//**************************************** Module global constants ( static const ) ************************************

//**************************************** Local func/proc prototypes ( static ) ***************************************
#endif
//** EndOfFile cfg_ccc_rom_segtablfwr.h*********************************************************************************
