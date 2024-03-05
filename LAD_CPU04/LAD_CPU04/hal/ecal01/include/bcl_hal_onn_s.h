//****************************************************************************
//
//                              bcl_hal_onn_s.h
//
//****************************************************************************
//
//                    Copyrights(c) 2022 by KNORR-BREMSE,
//               Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   ESRA BSW3G55xx
//! @date      2013-11-18
//! @author    P. Sigl
//
//****************************************************************************
//
//! @file
//! @brief  BCL_HAL - BCL_HAL_ONN system interface
//
//****************************************************************************
// Date        Author        Changes:
// 2011-11-07  P. Sigl       Start
// 2013-02-15  C. Baeuml     Extensions for IBC Device Registration.
// 2013-03-14  C. Baeuml     Declaration of function
//                           s16BCL_GNN_GetNN_IBC_Startup
// 2013-04-08  P. Sigl       Function header corrected
// 2013-04-24  P. Sigl       Comments added
// 2013-07-26  P. Sigl       Comments added
// 2013-10-16  P. Sigl       Comments corrected
// 2013-11-18  P. Sigl       Comments added
// 2016-05-10  S. Patapati   Adapted gen55xx w.r.t ESRA Rel 2.21.7
//							 (s16BCL_HAL_ONN_GetSrcFrontCodingDevice added)
// 2022-11-21  J. Lulli      Coding guidelines alignment
//****************************************************************************

#ifndef BCL_HAL_ONN_S_H
#define BCL_HAL_ONN_S_H

//******************* Header / include files ( #include ) ********************
#include "bcl_hal_defs_s.h"    // BCL_HAL common system interface definitions

//***************** Constant / macro definitions ( #define ) *****************

//****************************************************************************
//! @name Node number sources
//****************************************************************************
//@{

#define NN_SRC_IMMEDIATE       0        //!< Fix node number
#define NN_SRC_BACKPLANE       1        //!< Backplane
#define NN_SRC_FRONTCONNECTOR  2        //!< Front connector
#define NN_SRC_FRONTCODINGDEV  3        //!< Front coding device (not yet supported!)
#define NN_SRC_IBC             4        //!< IBC Device Registration.

//@}
//****************************************************************************

#define IBC_INVALID_NODE_NO     0xFF    // IBC Invalid Node Number

//****************************************************************************
//! @name Return value definition for BCL_HAL_ONN functions
//****************************************************************************
//@{
//! Success: Valid node number is returned.
#define BCL_HAL_ONN_OK                   ( (S16)   0 )

//! No success: Parameter error. No node number is returned.
#define BCL_HAL_ONN_ERR_PARAM            ( (S16)  -1 )

//! No success: HAL or driver problem. Default node number is returned.
#define BCL_HAL_ONN_ERR_HAL              ( (S16)  -2 )

//! No success: Parity error. Default node number is returned.
#define BCL_HAL_ONN_ERR_PARITY           ( (S16)  -3 )

//! No success: Range error. Default node number is returned.
#define BCL_HAL_ONN_ERR_RANGE            ( (S16)  -4 )

//! No success: Wrong node number source. Default node number is returned.
#define BCL_HAL_ONN_ERR_SRC              ( (S16)  -5 )
//@}
//****************************************************************************

//*********************** Type definitions ( typedef ) ***********************

//******************* Global data declarations ( extern ) ********************

//******* External parameter / constant declarations ( extern const ) ********

//************************ Global func/proc prototypes ***********************

//** Function s16BCL_GNN_GetNN_IBC_Startup ***********************************
//!  Runs IBC Device Registration Handler during Startup.
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!  @returns     0 : Success
//!                    - #BCL_HAL_ONN_OK
//!
//!  @returns    <0 : No success
//!                    - #BCL_HAL_ONN_ERR_PARAM
//!                    - #BCL_HAL_ONN_ERR_HAL
//!                    - #BCL_HAL_ONN_ERR_PARITY
//!                    - #BCL_HAL_ONN_ERR_RANGE
//!                    - #BCL_HAL_ONN_ERR_SRC
//!
//!  @remark  Configure this function in Init array ppfs16BCL_FWR_InitFcts.
//****************************************************************************
extern S16 s16BCL_GNN_GetNN_IBC_Startup(void);

//** Function s16BCL_HAL_ONN_GetSrcFrontConnector ****************************
//!  Retrieves the node number from the front connector
//!  @param[in]  u8MaxNodeNo  : Maximum allowed node number
//!                             ( 1 ... NODE_NO_DEFAULT )
//!  @param[out] pu8NodeNo    : Node number of the board
//!
//!
//!  @returns     0 : Success
//!                    - #BCL_HAL_ONN_OK
//!
//!  @returns    <0 : No success
//!                    - #BCL_HAL_ONN_ERR_PARAM
//!                    - #BCL_HAL_ONN_ERR_RANGE
//!                    - #BCL_HAL_ONN_ERR_HAL
//!                    - #BCL_HAL_ONN_ERR_PARITY
//!
//!  @remarks    The node number is extracted from the front connector pin
//!              code using mask #NODE_NO_MASK.
//!              The extracted node number must be within range
//!              1 ... u8MaxNodeNo, otherwise BCL_HAL_ONN_ERR_RANGE is
//!              returned.
//!
//!  @remarks    s16BCL_HAL_FC_Get() is called twice for a second look.
//!              In case of pincode mismatch this is repeated up to two times.
//****************************************************************************
S16 s16BCL_HAL_ONN_GetSrcFrontConnector(U8 u8MaxNodeNo, U8* pu8NodeNo);

#endif
//** EndOfFile bcl_hal_onn_s.h ***********************************************
