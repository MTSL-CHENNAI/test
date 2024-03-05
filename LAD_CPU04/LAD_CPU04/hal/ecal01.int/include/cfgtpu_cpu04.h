//**********************************************************************************************************************
//!
//! @details       -
//!
//                                             cfgtpu_cpu04.h
//
//**********************************************************************************************************************
//
//                                       Copyrights(c) by KNORR-BREMSE,
//                                       Rail Vehicle Systems, Munich
//
//! @project  IBC
//! @date     2023-11-30
//! @author   C. Brancolini
//!
//**********************************************************************************************************************
//!
//! @file cfgtpu_cpu04.h
//! @brief Configuration for tpu of cpu04
//!
//
//**********************************************************************************************************************
//
// History
// Date            Author              Changes
// 2023-11-30      C. Brancolini       Start
//
//**********************************************************************************************************************
#ifndef CFGTPU_CPU04_H
#define CFGTPU_CPU04_H
//**************************************** Header / include files ( #include ) *****************************************

//**************************************** Constant / macro definitions ( #define ) ************************************

//**************************************** Type definitions ( typedef ) ************************************************

//**************************************** Global data declarations ( extern ) *****************************************

//**************************************** External parameter / constant declarations ( extern const ) *****************

//! PCR index of RX pin for 1wire interface of CRM device
extern const U16 u161WIRE_CRM_RX_PCR;

//! PCR index of TX pin for 1wire interface of CRM device
extern const U16 u161WIRE_CRM_TX_PCR;

#endif
//* EndOfFile CFGTPU_CPU04.H **************************************************

