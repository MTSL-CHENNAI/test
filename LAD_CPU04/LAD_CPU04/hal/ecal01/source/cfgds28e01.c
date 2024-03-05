//**********************************************************************************************************************
//
//                                                 cfgds28e01.c
//
//**********************************************************************************************************************
//
//                                       Copyrights(c) 2022 by KNORR-BREMSE
//                                          Rail Vehicle Systems, Munich
//
//! @project   IBC
//! @date      2023-11-07
//! @author    C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file
//! @brief Service OWR for 1-Wire device DS28E01-100 1024-Bit 1-Wire EEPROM with SHA-1 Engine Configuration File
//
//**********************************************************************************************************************
//
// History
// Date                Author         Changes
// 2010-07-30          M. Moritz      Start
// 2011-01-13          C. Baeuml      Adaption to CPU04.
// 2011-01-27          C. Baeuml      Speed set to OWR_COM_SPEED_STANDARD.
// 2020-10-26          A. Gatare      Static analysis changes
// 2023-01-09          J. Lulli       Coding guidelines alignment
// 2023-11-07          C. Brancolini  Lint Plus cleanup
//
//**********************************************************************************************************************

//***************************************** Compiler options ( #pragma ) ***********************************************

//************************************* Header / include files ( #include ) ********************************************
#include "ds28e01_hws.h"
#include "ds28e01_hwi.h"
#include "1wire_hws.h"
#include <std_defs.h>     // standard definitions

//*********************************** Constant / macro definitions ( #define ) *****************************************

//! number of DS28E01-100 devices in configuration table
#define DS28E01_NUMBER_OF_DEVICES ((U8)1)
//***************************************** Type definitions ( typedef ) ***********************************************

//******************************************* Global data definitions **************************************************
//! allocate memory for status structure
DS28E01_ALLOC_MEM(DS28E01_NUMBER_OF_DEVICES); // @suppress("Wrong derived data type") // @suppress("Avoid Global Variables")
//Note: Suppression of "Avoid Global Variables", the scope of this variable is global and must therefore be declared as
//      such
//**************************************** Global constant definitions ( const ) ***************************************

//! configuration table for DS28E01-100 devices
static const C_DS28E01_CFG acDS28E01_cfg[DS28E01_NUMBER_OF_DEVICES] =
  {
    {0x00,  OWR_NO_HOTPLUG,      OWR_COM_SPEED_STANDARD}, // config for device #0 on bus #0
//   BusID, Pluggable,           Speed
  };

//! configuration structure for DS28E01-100 devices
const C_DS28E01_CFG_TBL cDS28E01_cfg_tbl =
  {
  DS28E01_NUMBER_OF_DEVICES,
  acDS28E01_cfg
  };
//**************************************** Global data declarations ( extern ) *****************************************
//************************** External parameter / constant declarations ( extern const )  ******************************
//**************************************** Global func/proc prototypes *************************************************

// EndOfHeader *********************************************************************************************************

// EndOfFile cfgds28e01.c **********************************************************************************************
