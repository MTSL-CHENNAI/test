//****************************************************************************
//
//                               cfgpbridge.c
//
//****************************************************************************
//
//                    Copyrights(c) 2022 by KNORR-BREMSE,
//               Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   ESRA BSW3G55xx
//! @date      2011-06-29
//! @author    P. Sigl
//
//****************************************************************************
//
//! @file
//! @brief  PBRIDGE config
//
//****************************************************************************
// Date        Author      Changes:
// 2011-02-16  P. Sigl     Initial revision
// 2011-06-29  P. Sigl     Comment changed
// 2015-05-15  KH Duemer   cleanup(Lint 9 / MISRA 2012)
// 2018-06-08  A. Mauro    Adatptations for CPU0
// 2023-01-09  J. Lulli    Coding guidelines alignment
//****************************************************************************
//Note: Suppression of "Wrong derived data type", these warnings come from the naming convetion violation of
//      their respective structures
//******************* Compiler options ( #pragma ) ***************************

//******************* Header / include files ( #include ) ********************
#include "55xxpbridge_i.h"              // PBRIDGE internal definitions

//******************* Constant / macro definitions ( #define ) ***************

#define PB_M1     0x1UL                   //!< Masks 1 bit
#define PB_M2     0x3UL                   //!< Masks 2 bits
#define PB_M3     0x7U                    //!< Masks 3 bits

//! Macro for building master access field number x (0..7)
#define PB_MAF(x, mbw, mtr, mtw, mpl)      \
        ((U32)( ((((mbw) & PB_M1) << 3U) |  \
                 (((mtr) & PB_M1) << 2U) |  \
                 (((mtw) & PB_M1) << 1U) |  \
                 (((mpl) & PB_M1)     )) << (28U - (((x) & PB_M3) * 4U)) ))

//! Macro for building peripheral access field x (0..7)
#define PB_PAF(x, bw, sp, wp, tp)      \
        ((U32)( ((((bw) & PB_M1) << 3U) |  \
                 (((sp) & PB_M1) << 2U) |  \
                 (((wp) & PB_M1) << 1U) |  \
                 (((tp) & PB_M1)     )) << (28U - (((x) & PB_M3) * 4U)) ))

//******************* Type definitions ( typedef ) ***************************

//******************* Global scope data definitions **************************

//******************* Global scope read only definitions ( const ) ***********


//****************************************************************************
//!                              PBRIDGE A
//****************************************************************************

#define PB_A_PACR_MAXIDX   0            //!< Max. index x of PACRx registers
                                        //!< of PBRIDGE A used in this
                                        //!< controller derivate.

#define PB_A_OPACR_MAXIDX  2            //!< Max. index x of OPACRx registers
                                        //!< of PBRIDGE A used in this
                                        //!< controller derivate.

//! Number of elements of pcPB_A_PACR_CFG[]
#define PB_A_PACR_MAX      (U8)(PB_A_PACR_MAXIDX + 1)

//! Number of elements of pcPB_A_OPACR_CFG[]
#define PB_A_OPACR_MAX     (U8)(PB_A_OPACR_MAXIDX + 1)


//****************************************************************************
//! PBRIDGE A: MPCR Config
//****************************************************************************
const tcPB_MPCR_CFG cPB_A_MPCR_CFG = // @suppress("Wrong derived data type")
{
    //--------------------------------------------------------------------------
    // boUseCfg        u32PB_MPCR
    //--------------------------------------------------------------------------
    // x    MBWx  MTRx  MTWx  MPLx
    FALSE,          PB_MAF ( 0U,  0UL,  0UL,  0UL,  0UL ) |  // CPU
    PB_MAF ( 1U,  0UL,  0UL,  0UL,  0UL ) |  // Nexus
    PB_MAF ( 2U,  0UL,  0UL,  0UL,  0UL ) |  // eDMA
    PB_MAF ( 3U,  0UL,  0UL,  0UL,  0UL )    // EBI
};

//****************************************************************************
//! PBRIDGE A: PACR Config
//****************************************************************************
const tcPB_xPACR_CFG pcPB_A_PACR_CFG[PB_A_PACR_MAX] = // @suppress("Wrong derived data type")
{
    {
        //------------------------------------------------------------------------
        // PBRIDGE A: PACR 0
        // boUseCfg      u32PB_xPACR
        //--------------------------------------------------------------------------
        // x    BWx  SPx  WPx  TPx
        FALSE,        PB_PAF ( 0U,  0UL, 0UL, 0UL, 0UL )    // PBRIDGE A
    }
};

//****************************************************************************
//! PBRIDGE A: OPACR Config
//****************************************************************************
const tcPB_xPACR_CFG pcPB_A_OPACR_CFG[PB_A_OPACR_MAX] = // @suppress("Wrong derived data type")
{
    {
        //------------------------------------------------------------------------
        // PBRIDGE A: OPACR 0
        // boUseCfg      u32PB_xPACR
        //--------------------------------------------------------------------------
        // x    BWx  SPx  WPx  TPx
        FALSE,        PB_PAF ( 0U,  0UL, 0UL, 0UL, 0UL ) |   // FMPLL
        PB_PAF ( 1U,  0UL, 0UL, 0UL, 0UL ) |   // EBI Ctrl
        PB_PAF ( 2U,  0UL, 0UL, 0UL, 0UL ) |   // Flash Ctrl
        PB_PAF ( 4U,  0UL, 0UL, 0UL, 0UL )     // SIU
    },
    {
        //------------------------------------------------------------------------
        // PBRIDGE A: OPACR 1
        // boUseCfg      u32PB_xPACR
        //--------------------------------------------------------------------------
        // x    BWx  SPx  WPx  TPx
        FALSE,        PB_PAF ( 0U,  0UL, 0UL, 0UL, 0UL )     // eMIOS
    },
    {
        //------------------------------------------------------------------------
        // PBRIDGE A: OPACR 2
        // boUseCfg      u32PB_xPACR
        //--------------------------------------------------------------------------
        // x    BWx  SPx  WPx  TPx
        FALSE,        PB_PAF ( 0U,  0UL, 0UL, 0UL, 0UL ) |   // eTPU
        PB_PAF ( 2U,  0UL, 0UL, 0UL, 0UL ) |   // eTPU PRAM
        PB_PAF ( 3U,  0UL, 0UL, 0UL, 0UL ) |   // eTPU PRAM Mirror
        PB_PAF ( 4U,  0UL, 0UL, 0UL, 0UL )     // eTPU SCM
    }
};

//****************************************************************************
//! Number of elements of cPB_A_PACR_CFG[]
//****************************************************************************
const U8 u8PB_A_PACR_MAX = PB_A_PACR_MAX;

//****************************************************************************
//! Number of elements of cPB_A_OPACR_CFG[]
//****************************************************************************
const U8 u8PB_A_OPACR_MAX = PB_A_OPACR_MAX;




//****************************************************************************
//!                              PBRIDGE B
//****************************************************************************

#define PB_B_PACR_MAXIDX   2            //!< Max. index x of PACRx registers
                                        //!< of PBRIDGE B used in this
                                        //!< controller derivate.

#define PB_B_OPACR_MAXIDX  3            //!< Max. index x of OPACRx registers
                                        //!< of PBRIDGE B used in this
                                        //!< controller derivate.

//! Number of elements of pcPB_B_PACR_CFG[]
#define PB_B_PACR_MAX      (U8)(PB_B_PACR_MAXIDX + 1)

//! Number of elements of pcPB_B_OPACR_CFG[]
#define PB_B_OPACR_MAX     (U8)(PB_B_OPACR_MAXIDX + 1)


//****************************************************************************
//! PBRIDGE B: MPCR Config
//****************************************************************************
const tcPB_MPCR_CFG cPB_B_MPCR_CFG = // @suppress("Wrong derived data type")
{
    //--------------------------------------------------------------------------
    // boUseCfg        u32PB_MPCR
    //--------------------------------------------------------------------------
    // x    MBWx  MTRx  MTWx  MPLx
    FALSE,          PB_MAF ( 0U,  0UL,  0UL,  0UL,  0UL ) |  // CPU
    PB_MAF ( 1U,  0UL,  0UL,  0UL,  0UL ) |  // Nexus
    PB_MAF ( 2U,  0UL,  0UL,  0UL,  0UL ) |  // eDMA
    PB_MAF ( 3U,  0UL,  0UL,  0UL,  0UL )    // EBI
};

//****************************************************************************
//! PBRIDGE B: PACR Config
//****************************************************************************
const tcPB_xPACR_CFG pcPB_B_PACR_CFG[PB_B_PACR_MAX] = // @suppress("Wrong derived data type")
{
    {
        //------------------------------------------------------------------------
        // PBRIDGE B: PACR 0
        // boUseCfg      u32PB_xPACR
        //--------------------------------------------------------------------------
        // x    BWx  SPx  WPx  TPx
        FALSE,        PB_PAF ( 0U,  0UL, 0UL, 0UL, 0UL ) |   // PBRIDGE B
        PB_PAF ( 1U,  0UL, 0UL, 0UL, 0UL )     // XBAR
    },
    {
        //------------------------------------------------------------------------
        // PBRIDGE B: PACR 1
        // boUseCfg      u32PB_xPACR
        //--------------------------------------------------------------------------
        FALSE,        0x00000000   // unused or not available
    },
    {
        //------------------------------------------------------------------------
        // PBRIDGE B: PACR 2
        // boUseCfg      u32PB_xPACR
        //--------------------------------------------------------------------------
        // x    BWx  SPx  WPx  TPx
        FALSE,        PB_PAF ( 0U,  0UL, 0UL, 0UL, 0UL ) |   // ESCM
        PB_PAF ( 1U,  0UL, 0UL, 0UL, 0UL ) |   // eDMA
        PB_PAF ( 2U,  0UL, 0UL, 0UL, 0UL )     // INTC
    }
};

//****************************************************************************
//! PBRIDGE B: OPACR Config
//****************************************************************************
const tcPB_xPACR_CFG pcPB_B_OPACR_CFG[PB_B_OPACR_MAX] = // @suppress("Wrong derived data type")
{
    {
        //------------------------------------------------------------------------
        // PBRIDGE B: OPACR 0
        // boUseCfg      u32PB_xPACR
        //--------------------------------------------------------------------------
        // x    BWx  SPx  WPx  TPx
        FALSE,        PB_PAF ( 0U,  0UL, 0UL, 0UL, 0UL ) |   // eQADC
        PB_PAF ( 4U,  0UL, 0UL, 0UL, 0UL ) |   // DSPI_A
        PB_PAF ( 5U,  0UL, 0UL, 0UL, 0UL ) |   // DSPI_B
        PB_PAF ( 6U,  0UL, 0UL, 0UL, 0UL ) |   // DSPI_C
        PB_PAF ( 7U,  0UL, 0UL, 0UL, 0UL )     // DSPI_D
    },
    {
        //------------------------------------------------------------------------
        // PBRIDGE B: OPACR 1
        // boUseCfg      u32PB_xPACR
        //--------------------------------------------------------------------------
        // x    BWx  SPx  WPx  TPx
        FALSE,        PB_PAF ( 4U,  0UL, 0UL, 0UL, 0UL ) |   // eSCI_A
        PB_PAF ( 5U,  0UL, 0UL, 0UL, 0UL )     // eSCI_B
    },
    {
        //------------------------------------------------------------------------
        // PBRIDGE B: OPACR 2
        // boUseCfg      u32PB_xPACR
        //--------------------------------------------------------------------------
        // x    BWx  SPx  WPx  TPx
        FALSE,        PB_PAF ( 0U,  0UL, 0UL, 0UL, 0UL ) |   // FlexCAN_A
        PB_PAF ( 1U,  0UL, 0UL, 0UL, 0UL ) |   // FlexCAN_B
        PB_PAF ( 2U,  0UL, 0UL, 0UL, 0UL )     // FlexCAN_C
    },
    {
        //------------------------------------------------------------------------
        // PBRIDGE B: OPACR 3
        // boUseCfg      u32PB_xPACR
        //--------------------------------------------------------------------------
        // x    BWx  SPx  WPx  TPx
        FALSE,        PB_PAF ( 7U,  0UL, 0UL, 0UL, 0UL )     // BAM
    }
};

//****************************************************************************
//! Number of elements of pcPB_B_PACR_CFG[]
//****************************************************************************
const U8 u8PB_B_PACR_MAX = PB_B_PACR_MAX;

//****************************************************************************
//! Number of elements of pcPB_B_OPACR_CFG[]
//****************************************************************************
const U8 u8PB_B_OPACR_MAX = PB_B_OPACR_MAX;



//******************* Module scope data segment ( static ) *******************

//******************* Module scope read only variables ( static const ) ******

//******************* Module scope func/proc prototypes ( static )************

//** EndOfHeader *************************************************************

//** EndOfFile cfgpbridge.c **************************************************
