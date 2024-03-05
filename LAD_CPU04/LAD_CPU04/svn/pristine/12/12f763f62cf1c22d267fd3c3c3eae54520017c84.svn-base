//*****************************************************************************
//
//                  L A D C _ S R V . H
//
//*****************************************************************************
//
//                    Copyrights(c) 2022 by KNORR-BREMSE,
//               Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   IBC
//! @date      2012-10-31
//! @author    J. Breidenstein, R/BCE13
//
//*****************************************************************************
//
//! @file
//! @brief  Definition of interface LAD configuration
//
//*****************************************************************************
// Date       Author           Changes:
// 2012-10-23 J. Breidenstein  Start
// 2012-10-25 J. Breidenstein  -Error correction in parameters of function
//                             s16LADCSrvGetFlashConfig().
//                             - added s16LADCSrvGetHWTypeAndVersion()
// 2012-10-31 J. Breidenstein  - added comments about the endianess
//                             - adapted s16LADCSrvGetDynCfgPart(): frame
//                               work has to tell LADC the length of the
//                               copied data.
// 2013.05.27. G. Nagy          s16LADCSrvGetFlashConfig prototype change
//                              Removed the declarations of Framework functions
// 2022.11.24  J. Lulli        Coding guidelines alignment
//*****************************************************************************
#ifndef LADC_SRV_H
#define LADC_SRV_H

//************************** Header / include files ***************************
#include "kb_types.h"                  // Standard definitions
#include "ladc.h"                      // common ladc definitions

//***************** Constant / macro definitions ( #define ) ******************

//*********************** Type definitions ( typedef ) ************************

//*****************************************************************************

//* Function s16LADCSrvGetFlashConfig *****************************************
//
//! This function tells caller, where flash configuration is saved.
//
//! @param[in]  ppu32StartConfig : Address, where to store address of raw
//!                                configuration.
//! @param[out]
//! @return     #LADC_RET_NO_ERROR, or error
//! @remarks    This is just the raw address. No check for data there!
//*****************************************************************************
extern S16 s16LADCSrvGetFlashConfig(U32** ppu32StartConfig);


//* Function s16LADCSrvGetSerialNumber ****************************************
//
//! This function gets the serial number of the LAD.
//
//! @param[in]
//! @param[out] pu32SerialNumber: Address where to write serial number.
//!             Note: This is address of lower U32. Upper value will be saved
//!             at *(pu32SerialNumber+1)
//!             Write data in local endianess !
//! @return     #LADC_RET_NO_ERROR, or error
//! @remarks    This is a standard interface function. It will call others to
//!             get the serial number (which depends on the platform)
//*****************************************************************************
extern S16 s16LADCSrvGetSerialNumber(U32* pu32SerialNumber);


//* Function s16LADCSrvGetLadTypeAndVersion ***********************************
//
//!  function for getting LAD type (APP SW-ID) and version (APP SW-Version)
//
//! @param[in]
//! @param[out] pchLadType: Address where to write LAD type (<= 16 chars)
//! @param[out] pchLadVersion: Address where to write LAD version(<= 12 chars)
//! @return     #LADC_RET_NO_ERROR, or error
//! @remarks    This is a standard interface function. It will call others to
//!             get the LAD type and version (which depends on the platform)
//*****************************************************************************
extern S16 s16LADCSrvGetLadTypeAndVersion(char* pchLadType, char* pchLadVersion);

//* Function s16LADCSrvGetHWTypeAndVersion ************************************
//
//!  function for getting HW type (FWR SW-ID) and version (FWR SW-Version)
//
//! @param[in]
//! @param[out] pchHWType: Address where to write LAD type (<= 16 chars)
//! @param[out] pchHWVersion: Address where to write LAD version(<= 12 chars)
//! @return     #LADC_RET_NO_ERROR, or error
//! @remarks    This is a standard interface function. It will call others to
//!             get the LAD type and version (which depends on the platform)
//*****************************************************************************
extern S16 s16LADCSrvGetHWTypeAndVersion(char* pchHWType, char* pchHWVersion);

#endif
//** EndOfFile ladc_srv.h *****************************************************
