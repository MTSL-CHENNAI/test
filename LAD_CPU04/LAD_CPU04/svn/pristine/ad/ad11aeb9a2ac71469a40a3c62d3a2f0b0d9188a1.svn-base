//****************************************************************************
//
//                             R T C S . H
//
//****************************************************************************
//
//                  Copyrights(c) 2022 by KNORR-BREMSE,
//             Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   ESRA BSW3G55xx
//! @date      2014-07-17
//! @author    C. Brancolini
//
//****************************************************************************
//
//! @file   rtcs.h
//! @brief  RTC service external interface definition (for other services
//!         in the same memory space).
//!         It includes RTC.H automatically (without RTCWP.H).
//
//****************************************************************************
// Date       Author           Changes:
// 22.09.00   Breidenstein     Split RTC.H to RTC.H and RTCS.H
//                             changed includes from  to "xx"
// 10.11.00   Breidenstein     New arrangement of Headerfiles for ser-
//                             vice RTC
// 30.01.01   Breidenstein     Alle Config-Pointer nun shuge
// 03.04.01   Breidenstein     changes after code review
//                             added comments
//                             shuge to SHUGE
// 07.06.12   Gambacciani      Adapted for BSW3G
// 2012-07-30 F. Stefani       Upd prototypes u16/bo-->s16
// 2012-08-01 F. Stefani       Restored SetCDO... functions and returnvalues
// 2012-10-05 GambaccM         Upd doxygen comments
// 2012-10-17 C. Brancolin     Changes due to BCL :
//                             deleted s16RTCStartup
//                             added s32RTCStartup
//                             added defines for s32RTCStartUp
//                             renamed s16RTCInit->s32RTCInit
// 2013-08-08 GambaccM         Del RTC_STARTUP_RTC_ACT_ERROR
// 2013-08-29 GambaccM         Upd doxygen comments
// 2014-07-17 C.Brancolini     Added errors defines for s16RTCProcessTCHCmd.
//                             Updated s16RTCProcessTCHCmd comment
//****************************************************************************

#ifndef RTCS_H
#define RTCS_H

//************************ Compiler options (pragma) *************************
//******************* Header / include files ( include ) *********************
#include "rtc.h"

//***************** Constant / macro definitions ( #define ) *****************
//! @name ReturnValuesOf_wRTCSetCfgCdoRtcTable
//!        Return values of wRTCSetCfgCdoRtcTable */
//! @{ */
#define RTC_CDO_SET_OK              ((S16)  0) //!< Set CDO table O.K.
#define RTC_CDO_SET_ERROR           ((S16) -1) //!< Set CDO table not in configuration phase
#define RTC_CDO_TYPE_ERROR          ((S16) -2) //!< CDO Type error
#define RTC_CDO_SIZE_ERROR          ((S16) -3) //!< CDO Size error
//! @}

//! @name ReturnValuesOf_wRTCSetCfgCdoRtcNvTable
//!     Return values of wRTCSetCfgCdoRtcNvTable */
//! @{ */
#define RTC_CDO_NV_SET_OK           ((S16)  0) //!< Set CDO NV table O.K.
#define RTC_CDO_NV_SET_ERROR        ((S16) -1) //!< Set CDO NV table not in configuration phase
#define RTC_CDO_NV_TYPE_ERROR       ((S16) -2) //!< CDO NV Type error
#define RTC_CDO_NV_SIZE_ERROR       ((S16) -3) //!< CDO NV Size error
//! @} */

//! @name ReturnValuesOf_s32RTCStartUp
//!       Return values of s32RTCStartUp */
//! @{ */
#define RTC_STARTUP_OK                   ((S32)  0) //!< no error
#define RTC_STARTUP_P_RTC_ACT_ERROR      ((S32) -1) //!< P_RTC process activation error
#define RTC_STARTUP_DRIVER_ACT_ERROR     ((S32) -2) //!< Driver RTC activation error
//! @} */


//! @name ReturnValuesOf_s16RTCProcessTCHCmd
//!        Specific errors of s16RTCProcessTCHCmd */
//! @{ */
#define RTC_PROCESS_TCH__ERR_CMD_SIZE   ((S16) -1) //!< Wrong command size
#define RTC_PROCESS_TCH__ERR_RSP_SIZE   ((S16) -2) //!< Wrong reply size
//! @} */

//*********************** Type definitions ( typedef ) ***********************
//******************* Global data declarations ( extern ) ********************
//******* External parameter / constant declarations ( extern const ) ********
//********************* Constant / macro definitions *************************
//************************ Global func/proc prototypes ***********************


//!Function s16RTCProcessTCHCmd *********************************************/
//! @brief      Processes TCH commands provided by service STE. */
//! @param[in]  pu8TCHCmd       - Pointer to buffer of the TCH command
//!                               (starting with command identifier) */
//! @param[in]  u16TCHCmdLen    - Length of command */
//! @param[in]  u16TCHRspLenMax - Max. allowed length of response */
//! @param[out] pu8TCHRsp       - Pointer to buffer of the TCH response
//!                               (starting with command identifier) */
//! @return     In case of success (>= 0): \n
//!                     - Length of response\n
//!             In case of error (< 0):\n
//!                     - #RTC_NULL_POINTER_CALL: null pointer parameter \n
//!                     - #RTC_PROCESS_TCH__ERR_CMD_SIZE: u16TCHCmdLen is 0 \n
//!                     - #RTC_PROCESS_TCH__ERR_RSP_SIZE: reply message bigger
//!                       than u16TCHRspLenMax */
//! @remarks    If length of response is 0, then there is no response to
//!             the TCH command defined or required. */
S16 s16RTCProcessTCHCmd(U8* pu8TCHCmd, U16 u16TCHCmdLen, U8* pu8TCHRsp,U16 u16TCHRspLenMax );
//***************************************************************************/


//!Function vRTCCycl200ms ***************************************************/
//! @brief      This function checks if Broadcast is enabled and in case
//!             System time is transmitted. */
//! @param[in]  - */
//! @param[out] - */

//! @remarks    To be called by OS every 200 ms. */
extern void vRTCCycl200ms( void );
//***************************************************************************/


//!Function vRTCCycl500ms ***************************************************/
//! This function calls main function if start up is successfully activated. */
//! @param[in]  - */
//! @param[out] - */
//! @remarks    To be called by OS every 500 ms. */
extern void vRTCCycl500ms( void );
//***************************************************************************/


//!Function s32RTCStartUp ***************************************************/
//! @brief      Starts process P_RTC, driver RTC and service RTC. */
//! @param[in]  - */
//! @param[out] - */
//! @return     #RTC_STARTUP_OK;\n
//!             #RTC_STARTUP_P_RTC_ACT_ERROR;\n
//!             #RTC_STARTUP_DRIVER_ACT_ERROR */
//! @remarks    Call after s32RTCInit() if it returns no error. */
extern S32 s32RTCStartUp( void );
//***************************************************************************/


//!Function s32RTCInit ******************************************************/
//! @brief      Prepares service for ConfigPrepared. */
//! @param[in]  - */
//! @param[out] - */
//! @return     0 - configuration prepared successfully;\n
//!             -1 - configuration not correctly prepared */
//! @remarks    To be called once before config prepared. */
extern S32 s32RTCInit( void );
//***************************************************************************/


//!Function s16RTCSetCfgCdoRtcTable *****************************************/
//! @brief      Configures a CDO_RTC_TABLE towards RTC */
//! @param[in]  pcCdo - pointer to the CDO_RTC_TABLE to be checked and assigned */
//! @param[out] - */
//! @return     #RTC_CDO_SET_OK:  All right;\n
//!             #RTC_CDO_SET_ERROR:  Call not in config prepared;\n
//!             #RTC_CDO_TYPE_ERROR:  TTC of CDO_RTC_TABLE faulty;\n
//!             #RTC_CDO_SIZE_ERROR:  Size of cdo in CDO_RTC_TABLE faulty */
//! @remarks    May only be called in ConfigPrepared */
extern S16 s16RTCSetCfgCdoRtcTable( void SHUGE *pcCdo );
//**************************************************************************/


//!Function s16RTCSetCfgCdoRtcNvTable ***************************************/
//! @brief      Configures a CDO_RTC_NV_TABLE towards RTC */
//! @param[in]  pcCdo - pointer to the CDO_RTC_NV_TABLE to be checked and assigned */
//! @param[out] - */
//! @return     #RTC_CDO_NV_SET_OK:  All right;\n
//!             #RTC_CDO_NV_SET_ERROR:  Call not in config prepared;\n
//!             #RTC_CDO_NV_TYPE_ERROR:  TTC of CDO_RTC_NV_TABLE faulty;\n
//!             #RTC_CDO_NV_SIZE_ERROR:  Size of cdo in CDO_RTC_NV_TABLE faulty */
//! @remarks    May only be called in ConfigPrepared */
extern S16 s16RTCSetCfgCdoRtcNvTable( void SHUGE *pcCdo );
//***************************************************************************/

#endif
//** EndOfFile RTCS.H ********************************************************/
