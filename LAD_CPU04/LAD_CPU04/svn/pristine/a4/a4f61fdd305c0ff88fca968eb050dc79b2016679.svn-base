//**********************************************************************************************************************
//
//                                            ct_fim_faultmap.h
//
//**********************************************************************************************************************
//
//                                       Copyrights(c) by KNORR-BREMSE,
//                                        Rail Vehicle Systems, Munich
//
//! @project   IBC
//! @date      2023-12-05
//! @author    C. Brancolini
//
//!
//**********************************************************************************************************************
//!
//! @file ct_fim_faultmap.h
//! @brief Tools for Fim CDO table
//!
//**********************************************************************************************************************
//
// History
// Date         Author          Changes
// 2017-07-27   R. Palsule      Start
// 2017-08-22   R. Palsule      BC0025-15- Updated to adapt kb_types.h changes
// 2017-12-18   R. Palsule      Changed file name and related comments
// 2018-04-02   R. Palsule      Coding guideline update
// 2021-09-20   N. Jadhav       Adaptation changes for GenCA V07.00 porting.
// 2023-12-05   C. Brancolini   Codan clean up
//
//**********************************************************************************************************************

#ifndef CT_FIM_FAULTMAP_H
#define CT_FIM_FAULTMAP_H

//**************************************** Header / include files ( #include ) *****************************************
#include "cbk_def.h"                    // CBK Standard Definitions
#include "kb_types.h"                   // KB Types
#include "cd_fim_faultmap.h"            // CDO definition
//**************************************** Constant / macro definitions ( #define ) ************************************

//! definition of the table type code
#define TTC_MAJOR_CDO_FIM_DSM_AL     (U16)0x40U
#define TTC_CDO_FIM_DSM_AL_TABLE     ((TTC_MAJOR_CDO_FIM_DSM_AL * (U16)64) + TTC_MINOR_CDO_FIM_DSM_AL)

//! Macro definitions for CDO_FIM_DSM_AL_TABLE
#define TYPEDEF_CDO_FIM_DSM_AL_TABLE(name, size)  \
        TYPEDEF_CDO_TABLE(C_CDO_FIM_DSM_AL, name, size)

//! Macro definitions for Header
#define INIT_CDO_FIM_DSM_AL_TABLE_HEADER(name, handler)       \
        INIT_CDO_TABLE_HEADER(TTC_CDO_FIM_DSM_AL_TABLE,         \
                              handler,                    \
                              (sizeof(CDO_FIM_DSM_AL_TABLE(name)) - \
                              sizeof(CDO_TABLE_HEADER)) /       \
                              sizeof(C_CDO_FIM_DSM_AL),                  \
                              C_CDO_FIM_DSM_AL)

//! Type-Macro for usage in C
#define CDO_FIM_DSM_AL_TABLE(name)    \
        CDO_TABLE(C_CDO_FIM_DSM_AL, name)

//! Macro for definition of ROM-Pointer
#define SET_CONST_REF_CDO_FIM_DSM_AL_TABLE(reference) \
        SET_CONST_REF_CDO_TABLE(C_CDO_FIM_DSM_AL, BSW, reference)

//! Macro for using CONST-REF
#define CONST_REF_CDO_FIM_DSM_AL_TABLE    \
        CONST_REF_CDO_TABLE(C_CDO_FIM_DSM_AL, BSW)

//! Macro for setting dynamic configuration
#define SET_DYNAMIC_REF_CDO_FIM_DSM_AL_TABLE(reference)   boSetCfgCdoFimDsmAlTable((VOID SHUGE*) reference) // @suppress("No upper case suffix for integer constants")
//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data declarations ( extern ) *****************************************

//**************************************** External parameter / constant declarations ( extern const )	****************

//**************************************** Global func/proc prototypes *************************************************

#endif

//** EndOfFile ct_fim_faultmap.h ***************************************************************************************
