//****************************************************************************
//
//                                 ste_ctrl_cmd_s.h
//
//****************************************************************************
//
//                    Copyrights(c) 2022 by KNORR-BREMSE,
//               Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   ESRA BSW3G55xx
//! @date      2013-05-21
//! @author    Z. Miskatovic
//
//****************************************************************************
//
//! @file
//! @brief  Service STE CTRL
//
//****************************************************************************
// Date        Author          Changes:
// 2013-03-13  Z. Miskatov     Start
// 2013-05-21  Z. Miskatov     comments added
// 2013-07-23  Z. Miskatov     interface reworked
// 2015-03-10  KH Duemer       Lint cleanup (Lint 9 / MISRA 2012)
// 2015-10-30  Z.Miskatov      JIRA ISSUE BC_002-171
// 2022-11-28  J. Lulli        Coding guidelines alignment
//****************************************************************************

#ifndef  STE_CTRL_TCH_S_H
#define  STE_CTRL_TCH_S_H

//******************* Header / include files ( #include ) ********************
#include "std_defs.h"


//***************** Constant / macro definitions ( #define ) *****************



#define STE_CTRL_TCH_SWI_START_AS_MASTER            ((U8)   0xAA)
#define STE_CTRL_TCH_SWI_NO_ACTIVITY                ((U8)   0x00)

#define SYSLOG_STOPPED                              ((U8)   0x01)
#define SYSLOG_STARTED                              ((U8)   0x02)
#define SYSLOG_RUNNING                              ((U8)   0x03)
#define SYSLOG_FINISHED                             ((U8)   0x04)

#define TCHREQ_STOPPED                              ((U8)   0x01)
#define TCHREQ_RUNNING                              ((U8)   0x02)

#define DLGMEAS_STOPPED                             ((U8)   0x01)
#define DLGMEAS_RUNNING                             ((U8)   0x02)
#define DLGMEAS_INTERRUPTED                         ((U8)   0x03)
#define DLGMEAS_FINISHED                            ((U8)   0x04)


#define STE_CTRL_TCH_INIT_OK                         0
#define STE_CTRL_TCH_INIT_ERROR                     -1

#define STE_CTRL_TCH_STARTUP_OK                      0
#define STE_CTRL_TCH_STARTUP_ERROR                  -1

#define STE_CTRL_MIN_ARBITRATION                    ((U8)   0x01)


//*********************** Type definitions ( typedef ) ***********************

//! enumerator to define the STE-TCH activity type
typedef enum
  {
    eSTE_TCH_CTRL_ACTY_UNKNOWN               = 0x00,   //!< unknown
    eSTE_TCH_CTRL_ACTY_ST03_HUMANOPERATOR    = 0x01,   //!< human operator
    eSTE_TCH_CTRL_ACTY_STE_DOWNLOAD          = 0x02,   //!< STE download
    eSTE_TCH_CTRL_ACTY_STE_TCH_REQUEST       = 0x04,   //!< STE TCH request
    eSTE_TCH_CTRL_ACTY_DLG_MEASUREMENT       = 0x10    //!< DLG Measurement
  } E_STE_CTRL_TCH_ACTIVITY_TYPE;

//! enumerator to define the STE-TCH control cycle
typedef enum
  {
    eSTE_TCH_CTRL_CYCLE_20MSEC    = 0,   //!< STE TCH Cycle 20msec
    eSTE_TCH_CTRL_CYCLE_200MSEC   = 1    //!< STE TCH Cycle 200msec
  } E_STE_CTRL_TCH_CYCLE;

//! enumerator to define the STE-TCH states
typedef enum
  {
    eSTE_TCH_SILENT    = 0,            //!< STE TCH state silent
    eSTE_TCH_WAITING   = 1,            //!< STE TCH state waiting
    eSTE_TCH_ACTIVE    = 2,            //!< STE TCH state active
    eSTE_TCH_STATE_MAX   = 3
  } E_STE_CTRL_TCH_STATES;

  //! enumerator to define the CAN TCH states
typedef enum
  {
    eSTE_CAN_TCH_FREE     = 0,            //!< CAN TCH state free
    eSTE_CAN_TCH_BUSY     = 1,            //!< CAN TCH state busy
    eSTE_CAN_TCH_UNKNOWN  = 2,            //!< CAN TCH state unknown
    eSTE_CAN_TCH_STATE_MAX   = 3
  } E_STE_CTRL_CAN_TCH_STATES;

//******************* Global data declarations ( extern ) ********************

extern U8 u8SysLogState;
extern U8 u8DLGMeasState;
extern U8 u8TCHRequestState;
extern U8 u8SWIState;
//************************ Global func/proc prototypes ***********************

//** Function s32STE_CTRL_TCH_Init *******************************************
//
//!  Initialize the STE TCH control  service
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!  @return     Success (0):
//!                      - #STE_CTRL_TCH_INIT_OK
//!
//!  @return     No success (<0):
//!                      - #STE_CTRL_TCH_INIT_ERROR
//!
//!  @remarks    ---
//
//***************************************************************************
extern S32 s32STE_CTRL_TCH_Init( void );


//** Function s32STE_CTRL_TCH_Startup ***************************************
//
//!  start e the STE TCH control  service
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!  @return     Success (0):
//!                      - #STE_CTRL_TCH_STARTUP_OK
//!
//!  @return     No success (<0):
//!                      - #STE_CTRL_TCH_STARTUP_ERROR
//!
//!  @remarks    ---
//
//**************************************************************************
extern S32 s32STE_CTRL_TCH_Startup  ( void );

//** Function vSTE_CTRL_TCH_Cycle *******************************************
//
//!  STE TCH control cyclic function
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!
//!  @remarks  this cyclic function is present in 20msec and 200msec time slices
//
//***************************************************************************
extern void vSTE_CTRL_TCH_Cycle( void );


//** Function vSTE_CTRL_TCH_SetCANTCHState ***********************************
//
//!  set the new CAN TCH state
//
//!  @param[in]  eNewState : new CAN TCH state
//!
//!  @param[out] ---
//!
//!
//!  @remarks    ---
//
//****************************************************************************
extern void vSTE_CTRL_TCH_SetCANTCHState(E_STE_CTRL_TCH_STATES eNewState);

//** Function eSTE_CTRL_TCH_GetCANTCHState ***********************************
//
//!  get the actual CAN TCH state
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!  @return     teSTE_CTRL_CAN_TCH_States
//!                  - #eSTE_CAN_TCH_FREE
//!                  - #eSTE_CAN_TCH_BUSY
//!                  - #eSTE_CAN_TCH_UNKNOWN
//!
//!  @remarks    ---
//
//****************************************************************************
extern E_STE_CTRL_TCH_STATES eSTE_CTRL_TCH_GetCANTCHState(void);

//** Function vSTE_CTRL_TCH_SetSTETCHState ***********************************
//
//!  set the new STE TCH state
//
//!  @param[in]  eNewState : new STE TCH state
//!
//!  @param[out] ---
//!
//!
//!  @remarks    ---
//
//****************************************************************************
extern void vSTE_CTRL_TCH_SetSTETCHState(E_STE_CTRL_TCH_STATES eNewState);

//** Function eSTE_CTRL_TCH_GetSTETCHState ***********************************
//
//!  get the actual STE TCH state
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!  @return     teSTE_CTRL_CAN_TCH_States
//!                  - #eSTE_TCH_SILENT
//!                  - #eSTE_TCH_WAITING
//!                  - #eSTE_TCH_ACTIVE
//!
//!  @remarks    ---
//
//****************************************************************************
extern E_STE_CTRL_TCH_STATES eSTE_CTRL_TCH_GetSTETCHState(void);

//** Function vSTE_CTRL_TCH_StartUpDelayInit *********************************
//
//!  init. the delay time of the STE TCH control service
//!  before arbitration starts
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!
//!  @remarks    ---
//
//****************************************************************************
extern void vSTE_CTRL_TCH_StartUpDelayInit(void);

//** Function vSTE_CTRL_TCH_SetStartUpDelayExpired ***************************
//
//!  set startup delay time as expired
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!
//!  @remarks    ---
//
//****************************************************************************
extern void vSTE_CTRL_TCH_SetStartUpDelayExpired(void);

//** Function vSTELCTRL_TCH_SendOwnAllocMessage ******************************
//
//!  send allocation STE TCH control message
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!
//!  @remarks    ---
//
//****************************************************************************
extern void vSTELCTRL_TCH_SendOwnAllocMessage(void);

//** Function vSTE_CTRL_TCH_OwnPriorityTimeInit ******************************
//
//!  init own priority time
//
//!  @param[in]  boMax :
//!                     - #STE_TCH_CTRL_OWN_PRIO_MAX       maximum time
//!                     - #STE_TCH_CTRL_OWN_PRIO_DEFAULT   standard time
//!
//!  @param[out] ---
//!
//!
//!  @remarks    ---
//
//****************************************************************************
extern void vSTE_CTRL_TCH_OwnPriorityTimeInit(BOOLEAN boMax);

//** Function boSTE_CTRL_TCH_OwnPriorityTimeExpired **************************
//
//!  check if own priority time expired
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!  @return     TRUE: the time is expired
//!
//!  @return     TRUE: the time is not expired
//!
//!  @remarks    ---
//
//****************************************************************************
extern BOOLEAN boSTE_CTRL_TCH_OwnPriorityTimeExpired(void);

//** Function vSTELCTRL_TCH_SendOwnActivityOrFreeMessage *********************
//
//!  send activity/free STE TCH control message
//
//!  @param[in]  u8Type :
//!                   - #STE_TCH_CTRL_ACTIVITY_MSG  - activity message
//!                   - #STE_TCH_CTRL_FREE_MSG      - free message
//!
//!  @param[out] ---
//!
//!
//!  @remarks    ---
//
//****************************************************************************
extern void vSTELCTRL_TCH_SendOwnActivityOrFreeMessage(U8 u8Type);

//** Function vSTELCTRL_TCH_SendStopActivityMessage *************************
//
//!  send activity stop STE TCH control message
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!
//!  @remarks    ---
//
//****************************************************************************
extern void vSTELCTRL_TCH_SendStopActivityMessage(void);

//** Function vSTE_CTRL_ActivityOrFreeMsgReceived ****************************
//
//!  decode the received activity/free message
//
//!  @param[in]  pu8NVRxData: pointer to message buffer
//!
//!  @param[out] ---
//!
//!
//!  @remarks    ---
//
//****************************************************************************
void vSTE_CTRL_ActivityOrFreeMsgReceived(U8* pu8NVRxData);

//** Function vSTE_CTRL_StopActivityMsgReceived ******************************
//
//!  decode the received stop  activity message
//
//!  @param[in]  pu8NVRxData: pointer to message buffer
//!
//!  @param[out] ---
//!
//!
//!  @remarks    ---
//
//****************************************************************************
void vSTE_CTRL_StopActivityMsgReceived(U8* pu8NVRxData);

//** Function boSTE_CTRL_TCH_ActivityCycleExpired ****************************
//
//!  check if activity time expired
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!  @return     TRUE: the time is expired
//!
//!  @return     TRUE: the time is not expired
//!
//!  @remarks    ---
//
//****************************************************************************
extern BOOLEAN boSTE_CTRL_TCH_ActivityCycleExpired(void);

//** Function vSTE_CTRL_TCH_SetActivityCycle *********************************
//
//!  check if activity time expired
//
//!  @param[in]  eNewCycle:
//!                     -#eSTE_TCH_CTRL_Cycle_20msec  - 20msec cycle
//!                     -#eSTE_TCH_CTRL_Cycle_200msec - 200msec cycle
//!
//!  @param[out] ---
//!
//!
//!  @remarks    ---
//
//****************************************************************************
extern void vSTE_CTRL_TCH_SetActivityCycle(E_STE_CTRL_TCH_CYCLE eNewCycle);

//** Function eSTE_CTRL_TCH_GetActivityCycle *********************************
//
//!  get actual activity cycle
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!  @return     eSTE_TCH_CTRL_Cycle_20msec  - 20msec cycle
//!
//!  @return     eSTE_TCH_CTRL_Cycle_200msec - 200msec cycle
//!
//!  @remarks    ---
//
//****************************************************************************
extern E_STE_CTRL_TCH_CYCLE eSTE_CTRL_TCH_GetActivityCycle(void);

//** Function vSTE_CTRL_TCH_ActivityCycleInit ********************************
//
//!  activity cycle init
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!
//!  @remarks    ---
//
//****************************************************************************
extern void vSTE_CTRL_TCH_ActivityCycleInit(void);

//** Function vSTE_CTRL_TCH_ActivityTimeoutReset ******************************
//
//!  reset the activity timeout - monitored time
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!
//!  @remarks    ---
//
//****************************************************************************
extern void vSTE_CTRL_TCH_ActivityTimeoutReset(void);

//** Function boSTE_CTRL_TCH_ActivityTimeoutExpired **************************
//
//!  check if activity timeout expired
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!  @return     TRUE: the time is expired
//!
//!  @return     TRUE: the time is not expired
//!
//!  @remarks    ---
//
//****************************************************************************
extern BOOLEAN boSTE_CTRL_TCH_ActivityTimeoutExpired(void);

//** Function u16TE_CTRL_TCH_GetActivityTimeout *****************************
//
//!  get actual value of the activity timeout time
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!  @return     activity timeout
//!
//!
//!  @remarks    ---
//
//****************************************************************************
extern U16  u16TE_CTRL_TCH_GetActivityTimeout(void);

//** Function vSTE_CTRL_TCH_SetOwnActivityType ******************************
//
//!  set own activity type
//
//!  @param[in]  u8OwnActivity:
//!              eSTE_TCH_CTRL_ACTY_UNKNOWN
//!              eSTE_TCH_CTRL_ACTY_ST03_HUMANOPERATOR
//!              eSTE_TCH_CTRL_ACTY_STE_DOWNLOAD
//!              eSTE_TCH_CTRL_ACTY_STE_TCH_REQUEST
//!              eSTE_TCH_CTRL_ACTY_DLG_MEASUREMENT
//!
//!  @param[out] ---
//!
//!
//!  @remarks    ---
//
//****************************************************************************
extern void vSTE_CTRL_TCH_SetOwnActivityType(U8 u8OwnActivity);

//** Function u8STE_CTRL_TCH_GetOwnActivityType ******************************
//
//!  get actual own activity type
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!  @return     eSTE_TCH_CTRL_ACTY_UNKNOWN
//!              eSTE_TCH_CTRL_ACTY_ST03_HUMANOPERATOR
//!              eSTE_TCH_CTRL_ACTY_STE_DOWNLOAD
//!              eSTE_TCH_CTRL_ACTY_STE_TCH_REQUEST
//!              eSTE_TCH_CTRL_ACTY_DLG_MEASUREMENT
//!
//!  @remarks    ---
//
//****************************************************************************
extern U8 u8STE_CTRL_TCH_GetOwnActivityType(void);

//** Function u8STE_CTRL_TCH_GetExternActivityType ***************************
//
//!  get actual external activity type
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!  @return     eSTE_TCH_CTRL_ACTY_UNKNOWN
//!              eSTE_TCH_CTRL_ACTY_ST03_HUMANOPERATOR
//!              eSTE_TCH_CTRL_ACTY_STE_DOWNLOAD
//!              eSTE_TCH_CTRL_ACTY_STE_TCH_REQUEST
//!              eSTE_TCH_CTRL_ACTY_DLG_MEASUREMENT
//!
//!  @remarks    ---
//
//****************************************************************************
extern U8 u8STE_CTRL_TCH_GetExternActivityType(void);

//** Function u8STE_CTRL_TCH_GetExternActivityNode ***************************
//
//!  get actual external activity node number
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!  @return     node number of external ESRA board
//!
//!  @remarks    ---
//
//****************************************************************************
extern U8 u8STE_CTRL_TCH_GetExternActivityNode(void);

//** Function vSTE_CTRL_TCH_IncreaseArbirtrationNumber ***********************
//
//!  Increase arbitration number
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!
//!  @remarks    ---
//
//****************************************************************************
extern void vSTE_CTRL_TCH_IncreaseArbirtrationNumber(void);

//** Function u8STE_CTRL_TCH_GetArbirtrationNumber ***************************
//
//!  get actual number of tried arbitration
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!  @return     arbitration number since last power on
//!
//!  @remarks    ---
//
//****************************************************************************
extern U8 u8STE_CTRL_TCH_GetArbirtrationNumber(void);

//** Function vSTE_CTRL_StartDLGMeasure **************************************
//
//!  set internal STE TCH control flag -DLG Measure started
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!
//!  @remarks    ---
//
//****************************************************************************
extern void vSTE_CTRL_StartDLGMeasure(void);

//** Function boSTE_CTRL_GetDLGMeasureStarted ********************************
//
//!  check internal STE TCH control flag if DLG Measure was started
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!  @return     TRUE: DLG measure was started
//!
//!  @return     FALSE: DLG was not started
//!
//!  @remarks    ---
//
//****************************************************************************
extern BOOLEAN boSTE_CTRL_GetDLGMeasureStarted(void);

//** Function vSTE_CTRL_StopDLGMeasure **************************************
//
//!  set internal STE TCH control flag -DLG Measure stopped
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!
//!  @remarks    ---
//
//****************************************************************************
extern void vSTE_CTRL_StopDLGMeasure(void);

//** Function vSTE_CTRL_SetSWIState **************************************
//
//!  set internal STE TCH control flag -SWI in to RSM memory
//
//!  @param[in]  u8Type:
//!                 - #STE_CTRL_TCH_SWI_START_AS_MASTER - set flag as master
//!                 - #STE_CTRL_TCH_SWI_NO_ACTIVITY - clear flag
//!
//!  @param[out] ---
//!
//!
//!  @remarks    ---
//
//****************************************************************************
extern void vSTE_CTRL_SetSWIState(U8 u8Type);

//** Function boSTE_CTRL_WasSWIActive **************************************
//
//!  check STE TCH control flag - SWI at RSM memory
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!  @return     FALSE: master Board was not in down-load state
//!
//!  @return     TRUE:  master Board was in down-load state
//!
//!  @remarks    ---
//
//****************************************************************************
extern BOOLEAN boSTE_CTRL_WasSWIActive(void);

//** Function boSTE_CTRL_TCH_RequestActivityExpired ***************************
//
//!  check if STE TCH request activity time expired
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!  @return     TRUE: the time is expired
//!
//!  @return     TRUE: the time is not expired
//!
//!  @remarks    ---
//
//****************************************************************************
extern BOOLEAN boSTE_CTRL_TCH_RequestActivityExpired(void);

//** Function vSTE_CTRL_TCH_RequestActivityReset ******************************
//
//!  reset the STE TCH request activity time
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!
//!  @remarks    ---
//
//****************************************************************************
extern void vSTE_CTRL_TCH_RequestActivityReset(void);

//** Function vSTECTRLDLGProcessing ******************************************
//
//!  call back function - STE control - processing DLG
//
//!  @param[in]  pbTCHData
//!
//!  @param[out] ---
//!
//!
//!  @remarks    ---
//
//***************************************************************************
extern void vSTECTRLDLGProcessing(BYTE* pbTCHData);

//** Function vSTESysconfigCheck *****************************
//
//!  STE control - STE Patch JIRA BC_002-1710
//
//!  @param[in]  bServiceType - TCH Service
//!
//!  @param[in]  u8Command    - TCH Command
//!  @param[out] ---
//!
//!
//!  @remarks    ---
//
//****************************************************************************
extern void vSTESysconfigCheck(BYTE bServiceType, U8 u8Command);

//** Function boSTE_CTRL_TCH_StartUpDelayExpired *****************************
//
//!  STE control - Startup delay processing
//
//!  @param[in]  ---
//!
//!  @param[out] ---
//!
//!  @return     ---
//!
//!  @remarks    ---
//
//****************************************************************************
extern BOOLEAN boSTE_CTRL_TCH_StartUpDelayExpired(void);



#endif
//** EndOfFile ste_ctrl_tch_s.h *****************************************************

