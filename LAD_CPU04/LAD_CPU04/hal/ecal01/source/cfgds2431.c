//**********************************************************************************************************************
//
//                                                   cfgds2431.c
//
//**********************************************************************************************************************
//
//                                       Copyright (C) 2022 by KNORR-BREMSE,
//                                  Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   IBC
//! @date      2023-11-07
//! @author    C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file
//! @brief DS2431 configuration file
//
//**********************************************************************************************************************
//
// History
// Date         Author            Changes
// 2018-07-02   V.Ingulkar        Dummy configuration
// 2023-01-09   J. Lulli          Coding guidelines alignment
// 2023-11-07   C. Brancolini     Lint Plus cleanup
//
//**********************************************************************************************************************

//***************************************** Compiler options ( #pragma ) ***********************************************

//************************************* Header / include files ( #include ) ********************************************
#include "ds2431_hws.h"
#include "ds2431_hwi.h"
#include "1wire_hws.h"
#include <std_defs.h>     // standard definitions

//*********************************** Constant / macro definitions ( #define ) *****************************************
//! number of DS28E01-100 devices in configuration table
#define DS2431_NUMBER_OF_DEVICES ((U8)1)
//***************************************** Type definitions ( typedef ) ***********************************************

//******************************************* Global data definitions **************************************************

//! allocate memory for status structure
DS2431_ALLOC_MEM(DS2431_NUMBER_OF_DEVICES); // @suppress("Wrong derived data type") // @suppress("Avoid Global Variables")
//Note: Suppression of "Avoid Global Variables", the scope of this variable is global and must therefore be declared as
//      such
//************************************ Global constant definitions ( const ) *******************************************
//! configuration table for DS28E01-100 devices
static const DS2431_CFG cDS2431_cfg[DS2431_NUMBER_OF_DEVICES] = // @suppress("Wrong derived data type")
{
    { 0x00, OWR_NO_HOTPLUG, OWR_COM_SPEED_STANDARD }, // config for device #0 on bus #0
    //   BusID, Pluggable,           Speed                                      */
//Note: Suppression of "Wrong derived data type", this warning comes from the naming convention violation of DS2431_CFG
};

//! configuration structure for DS28E01-100 devices
const DS2431_CFG_TBL cDS2431_cfg_tbl = // @suppress("Wrong derived data type")
{
    DS2431_NUMBER_OF_DEVICES,
    cDS2431_cfg
//Note: Suppression of "Wrong derived data type", this warning comes from the naming convention violation of DS2431_CFG_TBL
};
//************************************* Modul global data segment ( static ) *******************************************
//*********************************** Modul global constants ( static const ) ******************************************
//************************************ Local func/proc prototypes ( static ) *******************************************
// EndOfFile cfgds2431.c ***********************************************************************************************
