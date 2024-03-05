//**********************************************************************************************************************
//
//                                            cfg_ccc_rom_segtabsvl.h
//
//**********************************************************************************************************************
//
//                                       Copyrights(c) 2022 by KNORR-BREMSE,
//                                 Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   CBK
//! @date      2020-11-27
//! @author    A. Gatare
//
//**********************************************************************************************************************
//! @file
//! @brief external reference for:
//! - ROM area table Configuration for ESRA Service. ROM area segment table Configuration for ESRA Service.
//! - Configuration of the executable IDENT for the software component ESRA Service.
//**********************************************************************************************************************
// Date       Author      Changes:
// 20.04.11   A. Tenkeu   Start
// 09.03.12   P. Sigl     FWR separation
// 04.05.12   P. Sigl     NUMBER_OF_AREAS_SVL, NUMBER_OF_SEGMENTS_SVL
//                        introduced.
// 10.04.13   C. Baeuml   EBxxx, NUMBER_OF_SEGMENTS_SVL reduced to 8.
// 09-07-2016  N.Dindugala migarated to gen55xx 2.21.7
// 14.04.17   V.Ingulkar  Updated as per new SWIDENT table for CCA
// 15.06.18   A. Mauro    Adapted to CPU04.
// 17.09.20   A. Mauro    Added one segment.
// 2020-11-27 A.Gatare     Adapted for GenCA 6.11.Bc0025-271 Service ccc added in GenCA.Renamed file from
//                        cfg_ccc_rom_romtabsvl.h to cfg_ccc_rom_segtabsvl.h. Removed configuration for area table.
// 2021-12-15 A. Mauro    BC0025-544: NUMBER_OF_SEGMENTS_SVL changed 8->9
// 2022-11-28 J. Lulli    AS per new coding guidelines adapted template
//**********************************************************************************************************************
#ifndef CFG_CCC_ROM_SEGTABSVL_H
#define CFG_CCC_ROM_SEGTABSVL_H

//**************************************** Header / include files ( #include ) *****************************************
#include "ccc_rom.h"
//**************************************** Constant / macro definitions ( #define ) ************************************
#define NUMBER_OF_SEGMENTS_SVL  9
//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data declarations ( extern ) *****************************************

//**************************************** External parameter / constant declarations ( extern const )  ****************

//**************************************** External parameter / constant declarations ( extern const )  ****************
//! segment table for svl.
TYPEDEF_CCC_ROM_SEGMENT_DEF_TAB( SVL, NUMBER_OF_SEGMENTS_SVL); // @suppress("Wrongly used basic types")

extern const CCC_ROM_SEGMENT_DEF_TAB( SVL ) cSegTablDefSvl;
//**************************************** Global func/proc prototypes *************************************************

//**************************************** Global func/proc prototypes *************************************************
#endif
//** EndOfFile cfg_ccc_rom_segtblsvl.h *********************************************************************************
