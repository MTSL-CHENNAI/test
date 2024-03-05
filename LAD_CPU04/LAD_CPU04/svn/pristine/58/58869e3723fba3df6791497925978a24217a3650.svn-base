//****************************************************************************
//
//                               cfgxbar.c
//
//****************************************************************************
//
//                    Copyrights(c) 2022 by KNORR-BREMSE,
//               Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   ESRA BSW3G55xx
//! @date      2014-05-15
//! @author    P. Sigl
//
//****************************************************************************
//
//! @file
//! @brief  XBAR config
//
//****************************************************************************
// Date        Author      Changes:
// 2011-04-07  P. Sigl     Initial revision
// 2014-05-15  P. Sigl     LINT warnings checked.
// 2015-05-15  KH Duemer   Lint cleanup(Lint 9 / MISRA 2012)
// 2018-06-08  A. Mauro    Adaptation for CPU04
// 2023-01-09  J. Lulli    Coding guidelines alignment
//****************************************************************************

//******************* Compiler options ( #pragma ) ***************************

//******************* Header / include files ( #include ) ********************
#include "55xxxbar_i.h"                 // XBAR internal definitions

//******************* Constant / macro definitions ( #define ) ***************

#define XBAR_SP_MAX 8                   //!< Max. number of slave ports.
                                        //!< Only a subset of these ports may
                                        //!< be actually available! See
                                        //!< reference manual.

#define XBAR_SP_REGSPACE  0x100U        //!< Size of register memory area of
                                        //!< one slave port in bytes.

#define XBAR_SP_SCPCROFFS 0x10          //!< Offset of SCPCRn in register
                                        //!< memory area of one slave port in
                                        //!< bytes.

#define XBAR_M1     0x1UL                 //!< Masks 1 bit
#define XBAR_M2     0x3UL                 //!< Masks 2 bits
#define XBAR_M3     0x7UL                 //!< Masks 3 bits

//! Macro for building a XBAR MPR register value
#define XBAR_SET_MPR(mstr3, mstr2, mstr1, mstr0) \
        ((U32)( (((mstr3) & XBAR_M2) << 12U) |  \
                (((mstr2) & XBAR_M2) <<  8U) |  \
                (((mstr1) & XBAR_M2) <<  4U) |  \
                (((mstr0) & XBAR_M2)      ) ))

//! Macro for building a XBAR SGPCR register value
#define XBAR_SET_SGPCR(ro, arb, pctl, park)    \
        ((U32)( (((ro)    & XBAR_M1) << 31U) |  \
                (((arb)   & XBAR_M2) <<  8U) |  \
                (((pctl)  & XBAR_M2) <<  4U) |  \
                (((park)  & XBAR_M3)      ) ))


//****************************************************************************
//! Maximum number of XBAR slave ports
//****************************************************************************
const U8  u8XBAR_SP_MAX        = XBAR_SP_MAX;

//****************************************************************************
//! Size of register memory area of one slave port
//****************************************************************************
const U16 u16XBAR_SP_REGSPACE  = XBAR_SP_REGSPACE;

//****************************************************************************
//! Offset of XBAR_SCPCRn in register memory area of one slave port
//****************************************************************************
const U8  u8XBAR_SP_SCPCROFFS  = XBAR_SP_SCPCROFFS;


//****************************************************************************
//! XBAR Slave Port Configuration
//****************************************************************************
const tcXBAR_MPR_SGPCR_CFG pcXBAR_MPR_SGPCR_CFG[XBAR_SP_MAX] = // @suppress("Wrong derived data type")
  {
      //Note: Suppression of "Wrong derived data type", this warning comes
      //from the naming convention violation of tcXBAR_MPR_SGPCR_CFG
    {
    //------------------------------------------------------------------------
    // Slave Port #0 : Internal FLASH
    //
    // boUseCfg     u32XBAR_MPR
    //              u32XBAR_SGPCR
    //------------------------------------------------------------------------

       FALSE,       0,
                    0
    },
    {
    //------------------------------------------------------------------------
    // Slave Port #1 : EBI
    //
    // boUseCfg     u32XBAR_MPR
    //              u32XBAR_SGPCR
    //------------------------------------------------------------------------

                                 // MSTR3   MSTR2   MSTR1   MSTR0
                                 // (---)   (EBI)   (eDMA)  (Core)
       FALSE,       XBAR_SET_MPR (  3UL,    2UL,    0UL,    1UL   ),

                                   // RO   ARB   PCTL   PARK
                    XBAR_SET_SGPCR (  0UL, 0UL,  0UL ,  1UL    )
    },
    {
    //------------------------------------------------------------------------
    // Slave Port #2 : NOT AVAILABLE!
    //
    // boUseCfg     u32XBAR_MPR
    //              u32XBAR_SGPCR
    //------------------------------------------------------------------------

       FALSE,       0,
                    0
    },
    {
    //------------------------------------------------------------------------
    // Slave Port #3 : Internal SRAM
    //
    // boUseCfg     u32XBAR_MPR
    //              u32XBAR_SGPCR
    //------------------------------------------------------------------------

       FALSE,       0,
                    0
    },
    {
    //------------------------------------------------------------------------
    // Slave Port #4 : NOT AVAILABLE!
    //
    // boUseCfg     u32XBAR_MPR
    //              u32XBAR_SGPCR
    //------------------------------------------------------------------------

       FALSE,       0,
                    0
    },
    {
    //------------------------------------------------------------------------
    // Slave Port #5 : NOT AVAILABLE!
    //
    // boUseCfg     u32XBAR_MPR
    //              u32XBAR_SGPCR
    //------------------------------------------------------------------------

       FALSE,       0,
                    0
    },
    {
    //------------------------------------------------------------------------
    // Slave Port #6 : PBRIDGE_A
    //
    // boUseCfg     u32XBAR_MPR
    //              u32XBAR_SGPCR
    //------------------------------------------------------------------------

       FALSE,       0,
                    0
    },
    {
    //------------------------------------------------------------------------
    // Slave Port #7 : PBRIDGE_B
    //
    // boUseCfg     u32XBAR_MPR
    //              u32XBAR_SGPCR
    //------------------------------------------------------------------------

                                 // MSTR3   MSTR2   MSTR1   MSTR0
                                 // (---)   (EBI)   (eDMA)  (Core)
      FALSE,        XBAR_SET_MPR (  3UL,    2UL ,   0UL,    1UL ),

                                   // RO   ARB   PCTL  PARK
                    XBAR_SET_SGPCR (  0UL, 0UL , 0UL , 1UL    )
    }
  };

//******************* Type definitions ( typedef ) ***************************

//******************* Global scope data definitions **************************

//******************* Global scope read only definitions ( const ) ***********

//******************* Module scope data segment ( static ) *******************

//******************* Module scope read only variables ( static const ) ******

//******************* Module scope func/proc prototypes ( static )************

//** EndOfHeader *************************************************************

//** EndOfFile cfgxbar.c *****************************************************
