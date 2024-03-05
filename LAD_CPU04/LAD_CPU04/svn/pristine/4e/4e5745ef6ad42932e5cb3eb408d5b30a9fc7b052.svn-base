//****************************************************************************
//
//                                  can_nv.h
//
//****************************************************************************
//
//                    Copyrights(c) 2022 by KNORR-BREMSE,
//               Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project   IBC
//! @date      2023-12-05
//! @author    C. Brancolini
//
//****************************************************************************
//
//! @file
//! @brief  Service CAN - User interface of Standard Net Variables
//
//****************************************************************************
//
// History
// Date        Author      Changes:
// 2009-02-16  P. Sigl     Start
// 2009-03-09  P. Sigl     Type 0xFE reserved
// 2009-03-10  P. Sigl     Some parameters changed
// 2009-03-13  P. Sigl     NV_MAXSIZE_U8 corrected
// 2009-03-18  P. Sigl     Obsolete macros removed. Headers updated.
// 2009-03-27  P. Sigl     Cleanup
// 2009-05-14  P. Sigl     Update of base cycles
// 2009-07-21  P. Sigl     Debugging support added
// 2009-08-05  P. Sigl     tcCAN_NV_DATA changed to "little endian"
// 2009-08-13  P. Sigl     typedefs.h not included anymore
// 2009-09-28  P. Sigl     Prepared for Doxygen
// 2009-10-14  P. Sigl     tcCAN_NV_HI changed.
// 2009-10-20  P. Sigl     Doxygen member groups added.
// 2009-10-28  P. Sigl     pu16CAN_NV_IdleCnt added.
// 2009-12-14  P. Sigl     Comment in header of boCAN_NV_Read() corrected
//                         Changes based on review SWMDS.
// 2010-01-29  P. Sigl     Obsolete IEs removed.
// 2010-02-10  P. Sigl     Comment added.
// 2010-02-15  P. Sigl     boCAN_NV_InitDone introduced.
// 2010-07-01  P. Sigl     Additional return values for ...NV_Read().
// 2010-12-14  P. Sigl     CAN_NV_READ_ERR_RXBUF added.
// 2011-04-19  P. Sigl     Some comments corrected.
// 2013-10-15  P. Sigl     CAN_TX_1000MS introduced
// 2013-12-04  KH Duemer   use pragma pack only for Windriver Compiler
// 2014-05-14  P. Sigl     LINT warnings checked and (most of them) removed.
// 2014-10-28  GambaccM    New Safety Layer implementation.
// 2015-04-10  GambaccM    New CAN_NV_READ_ERR_SAFE.
// 2015-04-22  KH Duemer   Lint cleanup ( (Lint 9 / MISRA 2012):
//                         handling BOOLEAN + Note 9027
// 2015-09-22  GambaccM    Del u16CAN_NV_OpenSafe() (Jira BC_002-1696).
// 2016-11-23  R. Palsule  Adapted as per CBK header files.
// 2022-11-25  J. Lulli    Coding guidelines update
// 2023-12-05  C. Brancolini Codan clean up
//
//****************************************************************************

#ifndef CAN_NV_H
#define CAN_NV_H


//******************* Header / include files ( #include ) ********************
#include "kb_types.h"

//***************** Constant / macro definitions ( #define ) *****************

//! @file
//! @verbatim
//****************************************************************************
//**                 Transmission Mode for TX Net Variables                 **
//**                                                                        **
//**                                                                        **
//**          <----- Base Cycle -----> | <---- Cycle Count ---->            **
//**          7      6      5      4   |  3      2      1      0            **
//**                                   |                                    **
//**            0: No base cycle       |  n = 0 ... 13                      **
//**            1: 5ms time slice      |                                    **
//**            2: 50ms time slice     |  Sending is done at (n+1)'th       **
//**                                   |  occurrence of Base Cycle          **
//**                                   |                                    **
//**            other base cycles      |  n = 14: Sending is done at the    **
//**            under investigation    |          20th occurrence of        **
//**                                   |          Base Cycle                **
//**                                   |                                    **
//**                                   |  n = 15: reserved                  **
//****************************************************************************
//! @endverbatim

//****************************************************************************
//! @name Masks for Base Cycle and Cycle Count
//****************************************************************************
//@{

//! Base cycle Mask.
#define CAN_TX_BASE_CYCLE_MASK   ((U8) 0xF0)

//! Cycle Count Mask
#define CAN_TX_CYCLE_COUNT_MASK  ((U8) 0x0F)

//! Cycle Count n = 14 (meaning 20th occurrence of Base Cycle)
#define CAN_TX_CYCLE_COUNT_14       ((U8)(14))

//! Offset to be added for Cycle Count n = 14 in order to get 20 Base Cycles
#define CAN_TX_CYCLE_COUNT_14_OFFS  ((U8)(5))


//@}
//****************************************************************************


//****************************************************************************
//! @name TX Base Cycles
//****************************************************************************
//@{

//! No base cycle.
#define CAN_NO_TX_BASE_CYCLE     ((U8) 0x00)

//! Base cycle 5ms.
#define CAN_5MS_TX_BASE_CYCLE    ((U8) 0x10)

//! Base cycle 50ms.
#define CAN_50MS_TX_BASE_CYCLE   ((U8) 0x20)

//! Base cycle 1ms. Not intended to be used by applications!
#define CAN_1MS_TX_BASE_CYCLE    ((U8) 0x30)

//@}
//****************************************************************************


//****************************************************************************
//! @name Standard transmission modes known from BSW2G
//****************************************************************************
//@{

//! TX mode: Send immediately
#define CAN_TX_IMMEDIATE         CAN_NO_TX_BASE_CYCLE

//! TX mode: Send synchronous to next 50ms time slice.
#define CAN_TX_50MS              ((U8)(CAN_50MS_TX_BASE_CYCLE | (U8)0x00))

//! TX mode: Send synchronous to 2nd occurance of 50ms time slice.
#define CAN_TX_100MS             ((U8)(CAN_50MS_TX_BASE_CYCLE | (U8)0x01))

//! TX mode: Send synchronous to 4th occurance of 50ms time slice.
#define CAN_TX_200MS             ((U8)(CAN_50MS_TX_BASE_CYCLE | (U8)0x03))

//! TX mode: Send synchronous to 10th occurance of 50ms time slice.
#define CAN_TX_500MS             ((U8)(CAN_50MS_TX_BASE_CYCLE | (U8)0x09))

//! TX mode: Send synchronous to 20th occurance of 50ms time slice.
//
//! Note: Special handling of cycle count n = 14.
#define CAN_TX_1000MS            ((U8)(CAN_50MS_TX_BASE_CYCLE | \
                                       CAN_TX_CYCLE_COUNT_14))

//@}
//****************************************************************************


//****************************************************************************
//! @name Additional transmission modes BSW3G
//****************************************************************************
//@{

//! TX mode: Send synchronous to next 5ms time slice.
#define CAN_TX_5MS               ((U8)(CAN_5MS_TX_BASE_CYCLE  | (U8)0x00))

//! TX mode: Send synchronous to 2nd occurance of 5ms time slice.
#define CAN_TX_10MS              ((U8)(CAN_5MS_TX_BASE_CYCLE  | (U8)0x01))

//! TX mode: Send synchronous to 4th occurance of 5ms time slice.
#define CAN_TX_20MS              ((U8)(CAN_5MS_TX_BASE_CYCLE  | (U8)0x03))

//@}
//****************************************************************************


//****************************************************************************
//! @name Special purpose transmission modes BSW3G (not for applications!)
//****************************************************************************
//@{

//! TX mode: Send synchronous to next occurance of 1ms time slice.
#define CAN_TX_1MS               ((U8)CAN_1MS_TX_BASE_CYCLE  | (U8)0x0)
                                        //!< Not intended to be used by
                                        //!< applications!

//! TX mode: Send synchronous to 2nd occurance of 1ms time slice.
#define CAN_TX_2MS               ((U8)CAN_1MS_TX_BASE_CYCLE  | (U8)0x1)
                                        //!< Not intended to be used by
                                        //!< applications!
//@}
//****************************************************************************


//! @file
//! @verbatim
//****************************************************************************
//**                             Net Variable Type                          **
//**                                                                        **
//**                            Type       |                                **
//**                     <-- Extension --> | <---- Type ---->               **
//**                     7    6    5    4  | 3    2    1    0               **
//** (reserved) 0 -------+----+    |    |  |                                **
//**                               |    |  |    READ, WRITE,                **
//**           REL ----------------+    |  |    BROAD, ...                  **
//**           1: Relative node number  |  |                                **
//**           0: Absolute node number  |  |                                **
//**                                    |  |                                **
//**           INT ---------------------+  |                                **
//**           1: Internal NV              |                                **
//**           0: External NV              |                                **
//**                                                                        **
//** Note: NV types 0xFF, 0xFE and 0xB0 are reserved!                       **
//****************************************************************************
//! @endverbatim

//****************************************************************************
//! @name Net Variable type masks
//****************************************************************************
//@{

//! Mask for NV-Type.
#define NV_TYPE           ((U8) 0x0F)

//! Mask for NV-Type Extension.
#define NV_TYPE_EXT       ((U8) 0xF0)

//! Mask for NV-type extension INT (internal).
#define NV_TYPE_EXT_INT   ((U8) 0x10)

//! Mask for NV-type extension REL (relative).
#define NV_TYPE_EXT_REL   ((U8) 0x20)

//@}
//****************************************************************************


//****************************************************************************
//! @name Net Variable types
// Note: Additional types of net variables are defined in can_nvs.h
//****************************************************************************
//@{

//! Net Variable Type: NV for RX.
#define READ             ((U8) 0x00)

//! Net Variable Type: NV for TX.
#define WRITE            ((U8) 0x01)

//! Net Variable Type: NV for broadcast.
#define BROAD            ((U8) 0x02)    //!< Node is always own node.

//! Net Variable Type: READ / WRITE / BROAD don't care.
#define RWB_DONT_CARE    ((U8) 0x04)

//! Net Variable Type: NV for RX, only board internal.
#define READ_INT         ((U8)(READ  | NV_TYPE_EXT_INT))

//! Net Variable Type: NV for TX, only board internal.
#define WRITE_INT        ((U8)(WRITE | NV_TYPE_EXT_INT))

//! Net Variable Type: NV for RX, Node is relative to own node number.
#define READ_REL         ((U8)(READ  | NV_TYPE_EXT_REL))

//! Net Variable Type: NV for TX, Node is relative to own node number.
#define WRITE_REL        ((U8)(WRITE | NV_TYPE_EXT_REL))

//@}
//****************************************************************************


//****************************************************************************
//! @name Scope of Netvariables
//****************************************************************************
//@{

//! NV scope: local.
#define LOCAL_NV         ((U8)  0)      //!< Visibility of the NV may be
                                        //!< limited to this rack.

//! NV scope: global.
#define GLOBAL_NV        ((U8)  1)      //!< NV is globally visible.
//@}
//****************************************************************************


//****************************************************************************
//! @name Limits for CAN communication interface
//****************************************************************************
//@{

//! Maximum size of a NV in U64 chunks.
#define NV_MAXSIZE_U64   ((U8) 1)

//! Maximum size of a NV in U32 chunks.
#define NV_MAXSIZE_U32   (2*NV_MAXSIZE_U64)

//! Maximum size of a NV in U16 chunks.
#define NV_MAXSIZE_U16   (2*NV_MAXSIZE_U32)

//! Maximum size of a NV in U8 chunks.
#define NV_MAXSIZE_U8    (2*NV_MAXSIZE_U16)

//! Highest possible NodeNo.
#define NV_NODEMAX       NODE_NO_31

//! Highest possible NV ID.
#define NV_IDMAX         NV_ID_31

//! Unvalid NV handle.
#define NV_VOID_HANDLE   ((U16) 0xFFFFU)

//@}
//****************************************************************************


//****************************************************************************
//! @name Return value definition for s16CAN_NV_Change()
//****************************************************************************
//@{

//! Success
#define CAN_NV_CHANGE_OK           ((S16)  0)

//! No success: Handle not within range or not opened
#define CAN_NV_CHANGE_ERR_HANDLE   ((S16) -1)

//! No success: NV configuration is wrong
#define CAN_NV_CHANGE_ERR_CONFIG   ((S16) -2)

//! No success: Install Mailbox failed
#define CAN_NV_CHANGE_ERR_IMBX     ((S16) -3)

//! No success: CAN_NV not yer initialized
#define CAN_NV_CHANGE_ERR_INIT     ((S16) -4)

//@}
//****************************************************************************


//****************************************************************************
//! @name Return value definition for s16CAN_NV_Close()
//****************************************************************************
//@{

//! Success
#define CAN_NV_CLOSE_OK           ((S16)  0)

//! No success: Handle not within range or not opened
#define CAN_NV_CLOSE_ERR_HANDLE   ((S16) -1)

//! No success: Deinstall Mailbox failed
#define CAN_NV_CLOSE_ERR_DIMBX    ((S16) -2)

//! No success: CAN_NV not yet initialized
#define CAN_NV_CLOSE_ERR_INIT     ((S16) -3)

//@}
//****************************************************************************


//****************************************************************************
//! @name Return value definition for s16CAN_NV_Read()
//****************************************************************************
//@{

//! Success
#define CAN_NV_READ_OK            ((S16)  0)

//! No success: Handle not within range or not opened
#define CAN_NV_READ_ERR_HANDLE    ((S16) -1)

//! No success: Wrong size received
#define CAN_NV_READ_ERR_SIZE      ((S16) -2)

//! No success: CAN_NV not yet initialized
#define CAN_NV_READ_ERR_INIT      ((S16) -3)

//! No success: Wrong NV type
#define CAN_NV_READ_ERR_NVTYPE    ((S16) -4)

//! No success: CAN driver reported problem (Nothing received or param. wrong)
#define CAN_NV_READ_ERR_MBX       ((S16) -5)

//! No success: Receive buffer not valid
#define CAN_NV_READ_ERR_RXBUF     ((S16) -6)

//! No success: Receive buffer not valid due to the safe communication
#define CAN_NV_READ_ERR_SAFE      ((S16) -7)


//@}
//****************************************************************************


//****************************************************************************
//! @name Return value definition for s16CAN_NV_Write()
//****************************************************************************
//@{

//! Success
#define CAN_NV_WRITE_OK            ((S16)  0)

//! No success: Handle not within range or not opened
#define CAN_NV_WRITE_ERR_HANDLE    ((S16) -1)

//! No success: Wrong NV type
#define CAN_NV_WRITE_ERR_NVTYPE    ((S16) -2)

//! No success: Write buffer missing
#define CAN_NV_WRITE_ERR_BUFFER    ((S16) -3)

//! No success: Write mailbox failed (e.g. CAN controller is busy)
#define CAN_NV_WRITE_ERR_WRMBX     ((S16) -4)

//! No success: CAN_NV not yet initialized
#define CAN_NV_WRITE_ERR_INIT      ((S16) -5)

//@}
//****************************************************************************


//****************************************************************************
//! @name Return value definition for s16CAN_NV_GetInfo()
//****************************************************************************
//@{

//! Success
#define CAN_NV_GETINFO_OK           ((S16)  0)

//! No success: Handle not within range or not opened
#define CAN_NV_GETINFO_ERR_HANDLE   ((S16) -1)

//! No success: Pointer is NULL
#define CAN_NV_GETINFO_ERR_PTR      ((S16) -2)

//! No success: Mailbox info not available
#define CAN_NV_GETINFO_ERR_MBX      ((S16) -3)

//! No success: CAN_NV not yet initialized
#define CAN_NV_GETINFO_ERR_INIT     ((S16) -4)

//@}
//****************************************************************************


//*********************** Type definitions ( typedef ) ***********************

//****************************************************************************
//! Type of Net Variable configuration parameters
//****************************************************************************
typedef struct
{
        U8   u8NVType;                        //!< Net Variable Type

        U8   u8NVTxMode;                      //!< Transmission Mode

        U8   u8NVId;                          //!< ID of NV
        //!< (Part of CAN ID)

        U8   u8NVSize;                        //!< Length of NV in bytes

        U8   u8NVScope;                       //!< Scope of NV
        //!< (Part of CAN ID)

        S8   s8NodeNo;                        //!< Node number or node offset
        //!< (Part of CAN ID)
}C_CAN_NV_CONF;



//****************************************************************************
//! Type of Net Variable data
//
//! Byte order is "little endian" on CAN bus because of compatibility
//! to older ESRA boards.
//****************************************************************************
#ifdef _DIAB_TOOL
#pragma pack (1,4,1)                    // "Little endian"
#endif
typedef union
{
        U8   au8Data [NV_MAXSIZE_U8];          //!< U8  array: 8 elements

        U16  au16Data[NV_MAXSIZE_U16];         //!< U16 array: 4 elements

        U32  au32Data[NV_MAXSIZE_U32];         //!< U32 array: 2 elements

        U64  u64Data;                         //!< U64: 1 element
}C_CAN_NV_DATA;

#ifdef _DIAB_TOOL
#pragma pack(0)                         // Set to default packing
#endif

//****************************************************************************
//! CAN Net on which a certain NV shall be received or transmitted
//****************************************************************************
typedef enum
{
    eCAN_NV_NET_0   = 0,                  //!< CAN net 0 is the internal ESRA
    //!< system bus.

    // Additional CAN nets.
    // Availability depends on board specific configuration.
    eCAN_NV_NET_1   = 1,                  //!< CAN net 1
    //!< (board specific)

    eCAN_NV_NET_2   = 2,                  //!< CAN net 2
    //!< (board specific)

    eCAN_NV_NET_3   = 3,                  //!< CAN net 3
    //!< (board specific)

    eCAN_NV_NET_4   = 4,                  //!< CAN net 4
    //!< (board specific)

    eCAN_NV_NET_5   = 5,                  //!< CAN net 5
    //!< (board specific)

    eCAN_NV_NET_6   = 6,                  //!< CAN net 6
    //!< (board specific)

    eCAN_NV_NET_7   = 7,                  //!< CAN net 7
    //!< (board specific)


    eCAN_NV_NET_MAX = 8                   //!< Max. number of CAN nets.
    //!< Used for range check.
}E_CAN_NV_NET;



//****************************************************************************
//!CAN NV handle info (for debugging purpose)
//****************************************************************************
typedef struct
{
        // NV information
        U16    u16MbxHandle;                //!< NV info: Mailbox handle

        U8     u8NVType;                    //!< NV info: NV type

        U8     u8TXBaseCycle;               //!< NV info: Base cycle

        U8     u8TXCycleCount;              //!< NV info: Cycle count

        U8     u8NVSize;                    //!< NV info: NV size


        // Mailbox information
        U8     u8NetIdx;                    //!< Mbx info: CAN net

        U8     u8FlexCAN;                   //!< Mbx info: CAN module

        U8     u8Mbx;                       //!< Mbx info: CAN mailbox


        U8     u8Dir;                       //!< Mbx info: CAN mailbox mode
        //!< RX:0, TX:1

        U16    u16ID;                       //!< Mbx info: CAN identifer
}C_CAN_NV_HI;



//******************* Global data declarations ( extern ) ********************

extern U16 pu16CAN_NV_ClosedCnt[eCAN_NV_NET_MAX]; // @suppress("Wrong prefix")
                                        //!< Closed NVs per CAN net

//************************ Global func/proc prototypes ***********************

//******* External parameter / constant declarations ( extern const ) ********


//** Function u16CAN_NV_Open *************************************************
//
//!  Opens a NV on a certain CAN net.
//
//!  @param[in]  pcNVConf - NV configuration
//!  @param[in]  eCANNet  - CAN net on which the NV shall be opened.
//!                         "eCAN_NV_NET_0" is the internal ESRA system bus
//!
//!  @param[out] ---
//!
//!  @return     In case of success:    valid NV handle
//!  @return     In case of no success: #NV_VOID_HANDLE
//!
//!  @remarks    Reentrant. Disables / enables time slice scheduling!
//!
//!  @remarks    Cause of return value #NV_VOID_HANDLE:
//!              - Invalid parameters
//!              - CAN_NV internal problem (not expected to occur)
//
//****************************************************************************
extern U16 u16CAN_NV_Open ( C_CAN_NV_CONF* pcNVConf, E_CAN_NV_NET  eCANNet );

//** Function s16CAN_NV_Change ***********************************************
//
//!  Changes the configuration of an already opened NV.
//
//!  @param[in]  u16NV_Handle : NV handle
//!  @param[in]  pcNVConf     : NV configuration
//!
//!  @param[out] ---
//!
//!  @return     Success (0):
//!                      - #CAN_NV_CHANGE_OK
//!
//!  @return     No success (<0):
//!                      - #CAN_NV_CHANGE_ERR_HANDLE
//!                      - #CAN_NV_CHANGE_ERR_CONFIG
//!                      - #CAN_NV_CHANGE_ERR_IMBX
//!                      - #CAN_NV_CHANGE_ERR_INIT
//!
//!  @remarks    Reentrant. Disables / enables time slice scheduling!
//
//****************************************************************************
extern S16 s16CAN_NV_Change ( U16 u16NV_Handle, C_CAN_NV_CONF* pcNVConf );


//-----------------------------------------------------------
//! boCAN_NV_Change() is deprecated! Use s16CAN_NV_Change()!
//-----------------------------------------------------------
#define BOCAN_NV_CHANGE(p1,p2)                        \
        ( (s16CAN_NV_Change((U16)           (p1),     \
                            (C_CAN_NV_CONF*)(p2))     \
          < 0) ? FALSE : TRUE )


//** Function s16CAN_NV_Close ************************************************
//
//!  Closes a NV.
//
//!  @param[in]  u16NV_Handle : NV handle
//!
//!  @param[out] ---
//!
//!  @return     Success (0):
//!                      - #CAN_NV_CLOSE_OK
//!
//!  @return     No success (<0):
//!                      - #CAN_NV_CLOSE_ERR_HANDLE
//!                      - #CAN_NV_CLOSE_ERR_DIMBX
//!                      - #CAN_NV_CLOSE_ERR_INIT
//!
//!  @remarks    Reentrant. Disables / enables time slice scheduling!
//
//****************************************************************************
extern S16 s16CAN_NV_Close ( U16 u16NV_Handle );

//---------------------------------------------------------
//! boCAN_NV_Close() is deprecated! Use s16CAN_NV_Close()!
//---------------------------------------------------------
#define BOCAN_NV_CLOSE(p1)  ( (s16CAN_NV_Close((p1)) < 0) ? FALSE : TRUE ) // @suppress("No upper case suffix for integer constants")


//** Function s16CAN_NV_Read *************************************************
//
//!  Reads a NV.
//
//!  @param[in]  u16NV_Handle : NV handle
//!  @param[in]  pcNVData     : Pointer to receive buffer
//!  @param[in]  pu8DataLen   : Pointer to buffer for returning the number
//!                             of read bytes.
//!                             In case of NULL, no data length will be
//!                             returned.
//!
//!  @param[out] ---
//!
//!  @return     Success (0): Data and number of read bytes are copied to
//!                           the buffers.
//!                           - #CAN_NV_READ_OK
//!
//!  @return     No success (<0): Content of receive buffer is undetermined.
//!                               Content of buffer for read bytes remains
//!                               unchanged.
//!                               - #CAN_NV_READ_ERR_HANDLE
//!                               - #CAN_NV_READ_ERR_SIZE
//!                               - #CAN_NV_READ_ERR_INIT
//!                               - #CAN_NV_READ_ERR_NVTYPE
//!                               - #CAN_NV_READ_ERR_MBX
//!                               - #CAN_NV_READ_ERR_RXBUF
//!
//!  @remarks    Reentrant. Disables / enables time slice scheduling!
//
//****************************************************************************
extern S16 s16CAN_NV_Read ( U16 u16NV_Handle,C_CAN_NV_DATA* pcNVData,U8* pu8DataLen);

//-------------------------------------------------------
//! boCAN_NV_Read() is deprecated! Use s16CAN_NV_Read()!
//-------------------------------------------------------
#define BOCAN_NV_READ(p1,p2,p3)                     \
        ( (s16CAN_NV_Read((U16)           (p1),     \
                          (C_CAN_NV_DATA*)(p2),     \
                          (U8*)           (p3))     \
          < 0) ? FALSE : TRUE )


//** Function s16CAN_NV_Write ************************************************
//
//!  Writes a NV.
//
//!  @param[in]  u16NV_Handle   : NV handle
//!  @param[in]  pcNVData       : Pointer to send buffer
//!
//!  @param[out] ---
//!
//!  @return     Success (0):
//!                      - #CAN_NV_WRITE_OK
//!
//!  @return     No success (<0):
//!                      - #CAN_NV_WRITE_ERR_HANDLE
//!                      - #CAN_NV_WRITE_ERR_NVTYPE
//!                      - #CAN_NV_WRITE_ERR_BUFFER
//!                      - #CAN_NV_WRITE_ERR_WRMBX
//!                      - #CAN_NV_WRITE_ERR_INIT
//!
//!  @remarks    Reentrant. Disables / enables time slice scheduling!
//
//****************************************************************************
extern S16 s16CAN_NV_Write ( U16 u16NV_Handle,C_CAN_NV_DATA* pcNVData );


//---------------------------------------------------------
//! boCAN_NV_Write() is deprecated! Use s16CAN_NV_Write()!
//---------------------------------------------------------
#define BOCAN_NV_WRITE(p1,p2)                     \
        ( (s16CAN_NV_Write((p1),                  \
                           (p2))                  \
          < 0) ? FALSE : TRUE )


//** Function s16CAN_NV_GetInfo **********************************************
//
//!  Retrieves information about the given NV handle.
//
//!  @param[in]  u16NV_Handle : NV handle
//!
//!  @param[out] pcNV_Info   : Information about the given NV handle
//!
//!  @return     Success (0):
//!                      - #CAN_NV_GETINFO_OK
//!
//!  @return     No success (<0):
//!                      - #CAN_NV_GETINFO_ERR_HANDLE
//!                      - #CAN_NV_GETINFO_ERR_PTR
//!                      - #CAN_NV_GETINFO_ERR_MBX
//!                      - #CAN_NV_GETINFO_ERR_INIT
//!
//!  @remarks    For debugging purpose.
//
//****************************************************************************
extern S16 s16CAN_NV_GetInfo ( U16 u16NV_Handle, C_CAN_NV_HI* pcNV_Info );


//-------------------------------------------------------------
//! boCAN_NV_GetInfo() is deprecated! Use s16CAN_NV_GetInfo()!
//-------------------------------------------------------------
#define BOCAN_NV_GET_INFO(p1,p2)                   \
        ( (s16CAN_NV_GetInfo((U16)         (p1),  \
                             (C_CAN_NV_HI*)(p2))  \
          < 0) ? FALSE : TRUE )


#endif
//** EndOfFile can_nv.h ******************************************************

