//****************************************************************************
//
//                              cfg_bcl_mcal.c
//
//****************************************************************************
//
//                    Copyrights(c) 2022 by KNORR-BREMSE,
//               Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   IBC
//! @date      2023-11-02
//! @author    C. Brancolini
//
//****************************************************************************
//
//! @file
//! @brief  Service BCL (MCAL) - Configuration
//
//****************************************************************************
// Date        Author      Changes:
// 2012-03-07  P. Sigl     Initial revision
// 2012-03-29  P. Sigl     Macro PLL_SYSCLK_MHZ introduced
// 2012-09-19  P. Sigl     Adaptation to EB02x
// 2013-01-16  P. Sigl     PLL setup steps acc. Freescale EB698, Rev. 1
// 2012-06-15  P. Sigl     u32MaxIntVectors added.
// 2013-01-18  P. Sigl     u32LoopCtr1ms adjusted. There is still a
//                         problem with different runtimes of the loop,
//                         which has to be analyzed.
// 2013-07-12  P. Sigl     u32LoopCtr1ms adjusted again. Different alignment
//                         together with flash line prefetching caused
//                         different runtimes. Alignment of function
//                         vBCL_MCAL_1ms() to 32byte boundaries solves the
//                         problem.
//                         Config of IRAM, TLB and cache moved from
//                         cfg_bcl_hal.c to here.
// 2019-05-30  K. Gade     Updated 'Loop counter' from 7998 to 7987, for FWR: 1ms function.
// 2023-01-09  J. Lulli    Coding guidelines alignment
// 2023-05-15  C. Brancolini Lint clean up
// 2023-11-02  C. Brancolini Lint Plus clean up
//****************************************************************************

//******************* Compiler options ( #pragma ) ***************************

//******************* Header / include files ( #include ) ********************
#include "bcl_mcal_s.h"
#include "fmpll.h"

//****************************************************************************
//
//! @name       Configuration of system clock (FMPLL)
//
//****************************************************************************
//@{
#define PLL_REFERENCE_FREQ  8U           //!< Reference frequency in MHz
#define PLL_PREDIV          0U           //!< FMPLL_SYNCR: PREDIV value
#define PLL_MFD             6U           //!< FMPLL_SYNCR: MFD value
#define PLL_RFD             0U           //!< FMPLL_SYNCR: RFD value

//! Macro for calculating sys clock.
#define PLL_SYSCLK_MHZ    (((PLL_REFERENCE_FREQ * (PLL_MFD + 4U)) / \
                          (PLL_PREDIV+1U)) /                        \
                          (1U<<(PLL_RFD)))
                                        //! System clock is based on ref.
                                        //! clock, PREDIF, MFD and RFD.
                                        //! 8*(6+4)/1/1 = 80


// PLL setup step 1: 3 Mhz
// Reason: The system clock frequency must be less than one-half of the
//         crystal frequency when changing the predivider or the MFD
//         (which will be done in step 2)
const U32 u32FMPLL_SYNCR_PRE1 = (U32)(FMPLL_PREDIV((U32)0U) +
                                      FMPLL_MFD((U32)2U) +
                                      FMPLL_RFD((U32)4U));

// PLL setup step 2: 10 Mhz
const U32 u32FMPLL_SYNCR_PRE2 = (U32)(FMPLL_PREDIV((U32)PLL_PREDIV) +
                                      FMPLL_MFD((U32)PLL_MFD) +
                                      FMPLL_RFD((U32)3U));

// PLL setup step 3: 20 Mhz
const U32 u32FMPLL_SYNCR_PRE3 = (U32)(FMPLL_PREDIV((U32)PLL_PREDIV) +
                                      FMPLL_MFD((U32)PLL_MFD) +
                                      FMPLL_RFD((U32)2U));

// PLL setup step final: 80 Mhz
const U32 u32FMPLL_SYNCR      = (U32)(FMPLL_PREDIV((U32)PLL_PREDIV) +
                                      FMPLL_MFD((U32)PLL_MFD) +
                                      FMPLL_RFD((U32)PLL_RFD));


// System clock [MHz]
const U32 u32SystemClockMHz   = (U32)PLL_SYSCLK_MHZ;

// System clock [Hz]
const U32 u32SystemClockHz    = (U32)(PLL_SYSCLK_MHZ * 1000000U); // @suppress("No magic numbers")

// Loop counter for vBCL_MCAL_1ms() (used for load measurement purposes)
const U32 u32LoopCtr1ms       = (U32)7987; // @suppress("No magic numbers")
                                        // The value must configured to
                                        // guarantee a runtime of
                                        // 1ms +- 0,1% for vBCL_MCAL_1ms().

//@}
//** End of Configuration of system clock ************************************




//****************************************************************************
//
//! @name       Configuration of interrupt vectors
//
//****************************************************************************
//@{

// Max. number of interrupt vectors
const U32 u32MaxIntVectors   = (U32)212; // @suppress("No magic numbers")

//@}
//** End of Configuration of interrupt vectors *******************************




//****************************************************************************
//
//! @name       Configuration of internal RAM
//
//****************************************************************************
//@{

// Size of IRAM in KBytes
#define IRAM_SIZE_KB  64

// IRAM size in bytes
const U32 u32IRAM_Size = (U32)(IRAM_SIZE_KB * 1024); // @suppress("No magic numbers")

//@}
//** End of Configuration of internal RAM ************************************




//****************************************************************************
//
//! @name       Configuration of TLBs
//
//****************************************************************************
//@{

// Number of TLBs
const U16 u16TLB_Number = 16; // @suppress("No magic numbers")

//@}
//** End of Configuration of TLBs ********************************************




//****************************************************************************
//
//! @name       Configuration of processor cache
//
//****************************************************************************
//@{

// Indicates whether processor cache is available
const BOOLEAN boCacheAvailable = FALSE;

// Indicates whether processor cache shall be enabled.
const BOOLEAN boCacheEnable    = FALSE;

//@}
//** End of Configuration of processor cache *********************************


//** EndOfFile cfg_bcl_mcal.c ************************************************
