//**********************************************************************************************************************
//
//                                    C F G _ C C C _ R O M _ T A B S V L . H
//
//**********************************************************************************************************************
//
//                                       Copyrights(c) 2022 by KNORR-BREMSE,
//                                  Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   ESRA BSW3G55xx
//! @date      2011-04-20
//! @author    A. Tenkeu
//
//**********************************************************************************************************************
//! @file
//! @brief external reference for:
//! - ROM area table Configuration for ESRA Service.
//! - ROM area segment table Configuration for ESRA Service.
//! - Configuration of the executable IDENT for the software component ESRA Service.
//**********************************************************************************************************************
// Date       Author      Changes:
// 20.04.11   A. Tenkeu   Start
// 09.03.12   P. Sigl     FWR separation
// 04.05.12   P. Sigl     NUMBER_OF_AREAS_SVL, NUMBER_OF_SEGMENTS_SVL
//                        introduced.
// 10.04.13   C. Baeuml   EBxxx, NUMBER_OF_SEGMENTS_SVL reduced to 8.
// 09.07.16   N.Dindugala migarated to gen55xx 2.21.7
// 14.04.17   V.Ingulkar  Updated as per new SWIDENT table for CCA
// 15.06.18   A. Mauro    Adapted to CPU04.
// 17.09.20   A. Mauro    Added one segment.
// 28.11.22   J. Lulli    Coding guidelines alignment
//**********************************************************************************************************************
#ifndef CFG_CCC_ROM_ROMTABSVL_H
#define CFG_CCC_ROM_ROMTABSVL_H

//************************************* Header / include files ( #include ) ********************************************
#include "swident.h"                              // typedef of EXE_IDENT
#include "ccchw.h"                                // Interface to service layer
//*********************************** Constant / macro definitions ( #define ) *****************************************

//*************************************** Type definitions ( typedef ) *************************************************

#define NUMBER_OF_AREAS_SVL     2
#define NUMBER_OF_SEGMENTS_SVL  9

//************************************ Global data declarations ( extern ) *********************************************

//************************  External parameter / constant declarations ( extern const ) ********************************
//! ROM area segment table configuration for ESRA Service Layer located in RAM.
TYPEDEF_CCC_ROM_DEF_TAB( SVL, NUMBER_OF_AREAS_SVL ); // @suppress("Wrong derived data type") // @suppress("Wrong prefix for complex structures") // @suppress("Wrongly used basic types")
extern const CCC_ROM_DEF_TAB( SVL )RomAreaTabDefSvl; // @suppress("Wrong derived data type")
//! ROM area segment table configuration for ESRA Service Layer.
TYPEDEF_CCC_SEGMENT_DEF_TAB( SVL, NUMBER_OF_SEGMENTS_SVL); // @suppress("Wrong prefix for complex structures") // @suppress("Wrong derived data type") // @suppress("Wrongly used basic types")
extern const CCC_SEGMENT_DEF_TAB( SVL ) cSegTabDefSvl; // @suppress("Wrong derived data type")
// Note: All warnings suppressed because these macros are defined elesewhere in the code
//! Executable IDENT configuration for the software component ESRA Service.
extern const C_SW_COMP_IDENT cIdExeSvl;

//*************************************** Global func/proc prototypes **************************************************
#endif
//* EndOfFile cfg_ccc_rom_romtabsvl.h **********************************************************************************
