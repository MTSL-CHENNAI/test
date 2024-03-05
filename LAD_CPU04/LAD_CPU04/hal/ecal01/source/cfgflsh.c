//****************************************************************************
//
//                               cfgflsh.c
//
//****************************************************************************
//
//                    Copyrights(c) 2022 by KNORR-BREMSE,
//               Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   IBC
//! @date      2023-11-28
//! @author    C. Brancolini
//
//****************************************************************************
//
//! @file
//! @brief  FLASH driver config
//
//****************************************************************************
//
// History
// Date        Author      Changes:
// 2011-02-21  P. Sigl     Initial revision
// 2012-03-09  P. Sigl     Flash register init from IRAM
// 2013-07-01  P. Sigl     u32RAMAddr: Linker defined symbol used.
// 2015-05-15  KH Duemer   Lint cleanup(Lint 9 / MISRA 2012)
// 2018-06-08  A. Mauro    Adaptation for CPU04
// 2023-01-09  J. Lulli    Coding guidelines alignment
// 2023-11-28  C. Brancolini Lint Plus cleanup
//
//****************************************************************************

//******************* Compiler options ( #pragma ) ***************************

//******************* Header / include files ( #include ) ********************
#include "55xflsh_i.h"                  // FLASH driver internal definitions

// Inhibit lint message 9093 (the name matches a pattern reserved to the compiler),
// the name is defined by linker script.
// Inhibit lint message 2701 (variable declared outside of header is not defined in the same source file),
// issue related to GenMPC55xx.
extern U32 __FWRSYS_iram_exe_start;     //lint  !e9093 !e2701  // @suppress("Wrong prefix") // @suppress("No extern in source files") // @suppress("Avoid Global Variables")

//******************* Constant / macro definitions ( #define ) ***************

#define FLSH_M1     0x1UL                //!< Masks 1 bit
#define FLSH_M2     0x3UL                //!< Masks 2 bits
#define FLSH_M3     0x7UL                //!< Masks 3 bits

//! Macro for building a FLASH BIUCR register value
#define FLSH_SET_BIUCR(m4pfe, m3pfe, m2pfe, m1pfe, m0pfe,          \
                       apc, wwsc, rwsc, dpfen, ipfen, pflim, bfen) \
        ((U32)( (((m4pfe)  & FLSH_M1) << 20U) |                     \
                (((m3pfe)  & FLSH_M1) << 19U) |                     \
                (((m2pfe)  & FLSH_M1) << 18U) |                     \
                (((m1pfe)  & FLSH_M1) << 17U) |                     \
                (((m0pfe)  & FLSH_M1) << 16U) |                     \
                (((apc)    & FLSH_M3) << 13U) |                     \
                (((wwsc)   & FLSH_M2) << 11U) |                     \
                (((rwsc)   & FLSH_M3) <<  8U) |                     \
                (((dpfen)  & FLSH_M2) <<  6U) |                     \
                (((ipfen)  & FLSH_M2) <<  4U) |                     \
                (((pflim)  & FLSH_M3) <<  1U) |                     \
                (((bfen)   & FLSH_M1)      ) ))


//******************* Type definitions ( typedef ) ***************************

//******************* Global scope data definitions **************************

//******************* Global scope read only definitions ( const ) ***********

//****************************************************************************
//! FLASH Register Initialization Config
//****************************************************************************

const tcFLSH_INIT_CFG cFLSH_INIT_CFG = // @suppress("Wrong derived data type")
{
    //Note: Suppression of "Wrong derived data type", this warning comes
    //from the naming convention violation of tcFLSH_INIT_CFG
    //--------------------------------------------------------------------------
    // boInitFromRAM  u32RAMAddr
    //--------------------------------------------------------------------------

    //Inhibit lint message caused by address to object pointer conversion needed
    // to copy flash register init routine in RAM.
    //lint -save -e9078
    TRUE,          (U32)&__FWRSYS_iram_exe_start
    //lint -restore
};


//****************************************************************************
//! FLASH Bus Interface Unit Control Register Config
//****************************************************************************

const tcFLSH_BIUCR_CFG cFLSH_BIUCR_CFG = // @suppress("Wrong derived data type")
{
    //Note: Suppression of "Wrong derived data type", this warning comes
    //from the naming convention violation of tcFLSH_BIUCR_CFG
    //--------------------------------------------------------------------------
    // boUseCfg     u32FLSH_BIUCR
    //--------------------------------------------------------------------------
    // M4PFE M3PFE M2PFE M1PFE M0PFE
    TRUE,        FLSH_SET_BIUCR (  0UL,    1UL,    1UL,    1UL,    1UL,
        // APC WWSC RWSC DPFEN IPFEN PFLIM BFEN
        2UL,  1UL,   2UL,   1UL,    1UL,    2UL,    1UL   )
};


//******************* Module scope data segment ( static ) *******************

//******************* Module scope read only variables ( static const ) ******

//******************* Module scope func/proc prototypes ( static )************

//** EndOfHeader *************************************************************

//** EndOfFile cfgflsh.c *****************************************************
