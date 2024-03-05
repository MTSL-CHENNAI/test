//**********************************************************************************************************************
//
//                                                  cfgsimp.c
//
//**********************************************************************************************************************
//
//                                      Copyrights(c) 2022 by KNORR-BREMSE,
//                                Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @Project  :    IBC
//! @date     :    2023-05-15
//! @author   :    C. Brancolini
//
//**********************************************************************************************************************
// Content : Short decription / summary
//
//**********************************************************************************************************************
// Date       Author        Changes:
// 13.02.2009 M.Belluomini  Start
// 18.02.2009 M.Belluomini  The followings :
//                          oved compiler option CC_SIMULOLDCB12
// 24.02.2008 M.Belluomini  Updated CPLD config
// 25.02.2008 M.Belluomini  Updated release version
// 03.03.2008 M.Belluomini  Updated CPLD config because data in frame are really in reversed in order.
// 2009-03-17 U. Fittler    Adaptions to CPU04
// 2012-10-19 W. Eckerl     Updated section struct with DMA buffer address in IRAM, rework of channel
//                          specific clock settings, support of FRAM device
// 2012-10-24 W. Eckerl     Use slow channel parameters for CPLD/TMP
// 2012-11-22 W. Eckerl     Rework
// 2014-02-13 A. Mauro      Set configuration of CPLD, FRAM, DF and temperature sensor according to HWDD
//                          document PN32711 V. 03 pag 33-36
// 27.08.2014 W. Eckerl     FRAM write access with faster SPI timing (see Jira issue: BC_002-902)
// 12.12.2014 V. Ingulkar   Data Flash channel is configured to access FRAM for nonPoff operations
// 2023-01-09 J. Lulli      Coding guidelines alignment
// 2023-05-15 C. Brancolini Lint clean up
// 2023-05-15 C. Brancolini Lint Plus clean up
//**********************************************************************************************************************
//Note: Suppression of "Wrong derived data type", these warnings come from the naming convention violation
//       of their respective structures
//******************************************* Compiler options ( #pragma ) *********************************************

//*************************************** Header / include files ( #include ) ******************************************

#include "std_defs.h"

#include "55xdma.h"
#include "55xdspi.h"
#include "cfgsimcp.h"
#include "simcpu.h"

//************************************* Constant / macro definitions ( #define ) ***************************************

//! Number of used sections in SIM configuration
#define SIMCPU_CFG_NR_SECTIONS          (1)

//! @name DSPI section definitions DSPI_B
//! @{
//! ID of DSPI managed by SIM CPU
#define SIMCPU_CFG_DSPI_ID              ID_DSPI_B
//! In order to save memory, same Data Block is used by DMA to both transmit & receive

#define SIMCPU_CFG_SECTION_DSPIB_DMATRANSFERS_MAX  \
                         DMA_MAX_NUMBER_ITERATIONS

//! Data Block for DMA to transmit
#define SIMCPU_CFG_DMA_TX               0x40006700
//! Data Block for DMA to receive
#define SIMCPU_CFG_DMA_RX               0x40006700
//! @}

// CHANNELS CONFIGURATION  ============================================= */

//! @name chip select definitions. A faulty CS definition can be used
//! to deactivate a device
//! @{
//! define chip select for CPLD
#define SIMCPU_CFG_CPLD_CS              DSPI55XX_CHIP_SELECT_3
//! define chip select for temperature sensor
#define SIMCPU_CFG_TMP123_CS            DSPI55XX_CHIP_SELECT_5
//! define chip select for FRam
// todo: Is this chip select correct ?!?
#define SIMCPU_CFG_FRAM_CS              DSPI55XX_CHIP_SELECT_0
//! define chip select for Data flash 0
#define SIMCPU_CFG_DF0_CS               DSPI55XX_CHIP_SELECT_2
//! define chip select for Data flash 1
#define SIMCPU_CFG_DF1_CS               DSPI55XX_CHIP_SELECT_4
//! @}

//! @name DSPI-ID definitions
//! @{
//! define DSPI for CPLD
#define SIMCPU_CFG_CPLD_DSPIID          SIMCPU_CFG_DSPI_ID
//! define DSPI for temperature sensor
#define SIMCPU_CFG_TMP123_DSPIID        SIMCPU_CFG_DSPI_ID
//! define DSPI for FRam
#define SIMCPU_CFG_FRAM_DSPIID          SIMCPU_CFG_DSPI_ID
//! define DSPI for Data flash 1
#define SIMCPU_CFG_DF1_DSPIID           SIMCPU_CFG_DSPI_ID
//! define DSPI for Data flash 2
#define SIMCPU_CFG_DF2_DSPIID           SIMCPU_CFG_DSPI_ID
//! @}

//! @name settings for cpld
//! @{
// Data format is :
// | Reg | R/W |    |    |    |    |    |    |    |    |
// |           | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
// |   addr    |    |    |    |    |    |    |    |    |

//! defines the number of adress bits to use
#define SIMCPU_CFG_CPLD_ADRBITS         2
//! defines the buffer length to use
#define SIMCPU_CFG_CPLD_DATA_U32LEN     (1)

//! choose sim mode to use - we work in async. mode
#define SIMCPU_CFG_CPLD_SIM_MODE         SIMCPU_MODE_ASYNC
//! choose buffers to use - buffers for read and write
#define SIMCPU_CFG_CPLD_BUFF             SIMCPU_USE_FIX_BUFF(au32CPLDDataWr,au32CPLDDataRd)
//! Define working clock : 1.66 MHz
#define SIMCPU_CFG_CPLD_CLK              1666667
//! Define delay between CS and SCK : 350 nsec
#define SIMCPU_CFG_CPLD_CS2SCK           350
//! Define delay After SCK: 350 nsec
#define SIMCPU_CFG_CPLD_AFTER_SCK        350
//! Define delay After Transfer: 350 nsec
#define SIMCPU_CFG_CPLD_AFTER_TRANS      350
//! Define Mode 0: Phase LOW
#define SIMCPU_CFG_CPLD_PHASE            PH_LOW
//! Define Mode 0: Clock Polarity LOW
#define SIMCPU_CFG_CPLD_POL              POL_LOW
//! Define transfer is MSB first
#define SIMCPU_CFG_CPLD_BITORDER         MSB_FIRST
//! Define word size one byte + address bits
#define SIMCPU_CFG_CPLD_WORDSIZE         (SIMCPU_CFG_CPLD_ADRBITS+8)
//! Define transfer mode is blocked
#define SIMCPU_CFG_CPLD_TRANSFERMODE     BLOCKER
//! Define inactive state CS is HIGH
#define SIMCPU_CFG_CPLD_CS_INACTIVE      1
//! Define continuous mode between two words in the same transfer
#define SIMCPU_CFG_CPLD_CONTINUOUS       TRUE
//! Define to use DMA
#define SIMCPU_CFG_CPLD_USE_DMA          TRUE
//! @}


//! @name settings for temp sensor
//! @{
//! scale of TMP123 : t[C] = <raw value> / TMP123_KRAWSCALE_TEMP
#define TMP123_KRAWSCALE_TEMP           (0x80)
//! converted temperature scale in centi°C : every unit is 1/100 °C
#define TMP123_K100SCALE_TEMP           (100)
//! Bits D15(msb) - D3 represents temperature value, bits D2 - D0 are not valid ( really are ignored)
#define TMP123_TEMPMASK      (0xFFFFFFF8U)
//! D2 = 0, D1 and D0 are in high impedance state
#define TMP123_D2MASK        (0x00000004)

//! defines the buffer length to use
#define SIMCPU_CFG_TMP123_DATA_U32LEN   (1)

//! choose sim mode to use - we work in sync. mode
#define SIMCPU_CFG_TMP123_SIM_MODE      SIMCPU_MODE_ASYNC
//! choose buffers to use - buffers for read and write
#define SIMCPU_CFG_TMP123_BUFF          SIMCPU_USE_FIX_BUFF(au32TMP123DataWr,au32TMP123DataRd)
//! Define working clock : 3,33 MHz
#define SIMCPU_CFG_TMP123_CLK           3333334
//! Define delay between CS and SCK : 200 nsec
#define SIMCPU_CFG_TMP123_CS2SCK        200
//! Define delay After SCK: 200 nsec
#define SIMCPU_CFG_TMP123_AFTER_SCK     200
//! Define delay After Transfer: 200 nsec
#define SIMCPU_CFG_TMP123_AFTER_TRANS   200
//! Define Mode 3: Phase LOW
#define SIMCPU_CFG_TMP123_PHASE         PH_LOW
//! Define Mode 3: Clock Polarity HIGH
#define SIMCPU_CFG_TMP123_POL           POL_LOW
//! Define transfer is MSB first
#define SIMCPU_CFG_TMP123_BITORDER      MSB_FIRST
//! Define word size two bytes
#define SIMCPU_CFG_TMP123_WORDSIZE      16
//! Define transfer mode is blocked
#define SIMCPU_CFG_TMP123_TRANSFERMODE  BLOCKER
//! Define inactive state CS is HIGH
#define SIMCPU_CFG_TMP123_CS_INACTIVE   1
//! Define continuous mode between two words in the same transfer
#define SIMCPU_CFG_TMP123_CONTINUOUS    TRUE
//! Define to use DMA
#define SIMCPU_CFG_TMP123_USE_DMA       TRUE
//! @}


//! @name settings for fram todo: fill in correct values
//! @{
//! choose sim mode to use - we work in async. mode
#define SIMCPU_CFG_FRAM_SIM_MODE        SIMCPU_MODE_ASYNC
//! choose buffers to use - buffer defined by caller
#define SIMCPU_CFG_FRAM_BUFF            SIMCPU_USE_VAR_BUFF
//! Define working clock for read access : 5.7 MHz
#define SIMCPU_CFG_FRAM_CLK_READ        5714286
//! Define working clock for write access : 10.0 MHz
#define SIMCPU_CFG_FRAM_CLK_WRITE       10000000
//! Define delay between CS and SCK (read access): 125 nsec
#define SIMCPU_CFG_FRAM_CS2SCK_READ     125
//! Define delay between CS and SCK (write access): 75 nsec
#define SIMCPU_CFG_FRAM_CS2SCK_WRITE    75
//! Define delay After SCK (read access): 125 nsec
#define SIMCPU_CFG_FRAM_AFTER_SCK_READ  125
//! Define delay After SCK (write access): 75 nsec
#define SIMCPU_CFG_FRAM_AFTER_SCK_WRITE 75
//! Define delay After Transfer (read access): 125 nsec
#define SIMCPU_CFG_FRAM_AFTER_TRANS_READ 125
//! Define delay After Transfer (write access): 150 nsec
#define SIMCPU_CFG_FRAM_AFTER_TRANS_WRITE 150
//! Define Mode 3: Phase LOW
#define SIMCPU_CFG_FRAM_PHASE           PH_LOW
//! Define Mode 3: Clock Polarity LOW
#define SIMCPU_CFG_FRAM_POL             POL_LOW
//! Define transfer is MSB first
#define SIMCPU_CFG_FRAM_BITORDER        MSB_FIRST
//! Define word size one byte
#define SIMCPU_CFG_FRAM_WORDSIZE        8
//! Define transfer mode is triggered
#define SIMCPU_CFG_FRAM_TRANSFERMODE    TRIGGERED
//! Define inactive state CS is HIGH
#define SIMCPU_CFG_FRAM_CS_INACTIVE     1
//! Define continuous mode between two words in the same transfer
#define SIMCPU_CFG_FRAM_CONTINUOUS      TRUE
//! Define to use DMA
#define SIMCPU_CFG_FRAM_USE_DMA         TRUE
//! @}


//! @name settings for data flashes
//! @{
//! number of data flash devices. Allowed value are from 0 .. 2
#define SIMCPU_CFG_NR_DATA_FLASHES           ((U8)1)

//! choose sim mode to use - we work in sync. mode
#define SIMCPU_CFG_DF_SIM_MODE          SIMCPU_MODE_SYNC
//! choose buffers to use - buffer defined by caller
#define SIMCPU_CFG_DF_BUFF              SIMCPU_USE_VAR_BUFF
//! Define working clock : 8 MHz
#define SIMCPU_CFG_DF_CLK               8000000
//! Define delay between CS and SCK : 100 nsec
#define SIMCPU_CFG_DF_CS2SCK            100
//! Define delay After SCK: 100 nsec
#define SIMCPU_CFG_DF_AFTER_SCK         100
//! Define delay After Transfer: 200 nsec
#define SIMCPU_CFG_DF_AFTER_TRANS       200
//! Define Mode 3: Phase LOW
#define SIMCPU_CFG_DF_PHASE             PH_LOW
//! Define Mode 3: Clock Polarity LOW
#define SIMCPU_CFG_DF_POL               POL_LOW
//! Define transfer is MSB first
#define SIMCPU_CFG_DF_BITORDER          MSB_FIRST
//! Define word size one byte
#define SIMCPU_CFG_DF_WORDSIZE          8
//! Define transfer mode is blocked
#define SIMCPU_CFG_DF_TRANSFERMODE      BLOCKER
//! Define inactive state CS is HIGH
#define SIMCPU_CFG_DF_CS_INACTIVE       1
//! Define continuous mode between two words in the same transfer
#define SIMCPU_CFG_DF_CONTINUOUS        TRUE
//! Define to use DMA
#define SIMCPU_CFG_DF_USE_DMA           TRUE
//! @}

//-------------------------------------------------------------------------
// FROM HERE ON, DO NOT CHANGE ANYTHING. ALL SETTINGS DONE WITH THE DEFINES
// WILL BE PUT TO CORRECT POSITION IN CONFIG STRUCTURES !!!!!!!!!!!!!!!!!!!
//-------------------------------------------------------------------------

///! @name Makros for setting buffers
//! @{
//! macro defines the fixed buffers to be used
#define SIMCPU_USE_FIX_BUFF(Writebuff,Readbuff)                              \
                        (U16)sizeof(Writebuff),Writebuff,(U16)sizeof(Readbuff),Readbuff

//! macro defines that user buffers are used
#define SIMCPU_USE_VAR_BUFF             0,NULL,0,NULL
//! @}

//! Number of used channels in SIM configuration
#define SIMCPU_CFG_NR_CHANNELS          (SIMCPU_CFG_INDEX_DF(1))



//******************************************* Type definitions ( typedef ) *********************************************

//********************************************* Global data definitions ************************************************

//************************************** Global constant definitions ( const ) *****************************************


// SECTIONS CONFIGURATION  ============================================ */

//! @name section configuration DSPI_B
//! @{
//! definitions for DSPI section. DO NOT CHANGE HERE, ONLY THE MACROS !
static const SIMCPUSECTION_CFG cSimcpuSectionBCfg = // @suppress("Wrong derived data type")
{{
    // identifier for the DSPI section
    SIMCPU_CFG_DSPI_ID,

    // size [# transfers] of Data Blocks for DMA (same for both TX and RX)
    //Inhibit lint note 9029 related to a macro of GenMPC55xx.
    //lint -save -e9029
    SIMCPU_CFG_SECTION_DSPIB_DMATRANSFERS_MAX,
    //lint -restore

    //Inhibit lint message caused by address to object pointer conversion needed for memory mapped IO access.
    //lint -save -e9078
    (volatile U32 *)SIMCPU_CFG_DMA_TX, // Data Block for DMA to transmit
    (volatile U32 *)SIMCPU_CFG_DMA_RX  // Data Block for DMA to receive
    //lint -restore
}};

//! definition for runtime data. DO NOT CHANGE HERE, ONLY THE MACROS !
static SIMCPUSECTION_RUNTIME cSimcpuSectionBRunTime; // @suppress("Wrong derived data type")
//! @}


// CHANNELS CONFIGURATION. DO NOT CHANGE HERE, ONLY THE MACROS ! */

//! @name set CPLD registers addresses
//! @{
//! reset event register (read)
const U8 u8SIMCPUCpldReg_RST_EVNT_addr  = 0x0;
//! CF config register (write)
const U8 u8SIMCPUCpldReg_CF_CFG_addr    = 0x1; // @suppress("No magic numbers")
//! HW config register (read)
const U8 u8SIMCPUCpldReg_HWCFG_addr     = 0x2; // @suppress("No magic numbers")
//! control and test register (write)
const U8 u8SIMCPUCpldReg_CTRL_TST_addr  = 0x3; // @suppress("No magic numbers")
//! @}

// Set CPLD number of address bits
//const U8 u8CpldAddrBitLen  = SIMCPU_CFG_CPLD_ADRBITS; //TODO:unused


//! @name CPLD data buffers definitions ( note: array is U32 for safer alignment)
//! @{
// todo: JCB: todo: brauchen wir diese buffer wirklich konfigurierbar ?!?
// Darf es mehrere konkurrierende Zugriffe auf das CPLD geben, oder immer nut einen ?
// Bei nur einem Zugriff reicht jeweils ein U32 (16 Bits transfer size) sicher aus
static U32 au32CPLDDataWr[ SIMCPU_CFG_CPLD_DATA_U32LEN ];
static U32 au32CPLDDataRd[ SIMCPU_CFG_CPLD_DATA_U32LEN ];
//! @}


//! @name channel configuration CPLD
//! @{
static const SIMCPUCHANN_CFG cCpldCfg = // @suppress("Wrong derived data type")
{
    SIMCPU_CFG_INDEX_CPLD, //!< channel index cpld
    SIMCPU_CFG_CPLD_SIM_MODE, //!< set sim mode
    SIMCPU_CFG_CPLD_BUFF, //!<  set the buffers
    {
        SIMCPU_CFG_DSPI_ID, //!< set DSPI identifier
        SIMCPU_CFG_CPLD_CS, //!< set chip select
        SIMCPU_CFG_CPLD_CLK, //!< set working clock
        SIMCPU_CFG_CPLD_CS2SCK, //!< set delay between CS and SCK
        SIMCPU_CFG_CPLD_AFTER_SCK, //!< set delay After SCK
        SIMCPU_CFG_CPLD_AFTER_TRANS, //!< set delay After Transfer
        SIMCPU_CFG_CPLD_PHASE, //!< set phase
        SIMCPU_CFG_CPLD_POL, //!< set polarity
        SIMCPU_CFG_CPLD_BITORDER, //!< set bit order
        SIMCPU_CFG_CPLD_WORDSIZE, //!< set word size
        SIMCPU_CFG_CPLD_TRANSFERMODE, //!< set transfer mode
        SIMCPU_CFG_CPLD_CS_INACTIVE, //!< set inactive state
        SIMCPU_CFG_CPLD_CONTINUOUS, //!< set continuous mode
        SIMCPU_CFG_CPLD_USE_DMA //!< set eDMA
    }
};
//! @}



//! @name data definitions for temperature sensor handling
//! @{
const S32 s32SIMCPUTMP123KrawScaleTemp = (S32)TMP123_KRAWSCALE_TEMP;
const S32 s32SIMCPUTMP123K100ScaleTemp = (S32)TMP123_K100SCALE_TEMP;
const S32 s32SIMCPUTMP123TempMask      = (S32)TMP123_TEMPMASK;
const S32 s32SIMCPUTMP123D2Mask        = (S32)TMP123_D2MASK;
//! @}

//! @name TMP123 data buffers definitions ( note: array is U32 for safer alignment)
//! @{
// todo: JCB: todo: brauchen wir diese buffer wirklich konfigurierbar ?!?
// Oder Wäre es besser, diese im simcpu.c vorzubelegen. Dann müßte sich der Nutzer nicht mehr darum kümmern.
// Nachdem der SIM hier auf einen Temperatursensortypus hart codiert ist, sollte hier immer das Gleiche stehen.
static U32 au32TMP123DataWr[ SIMCPU_CFG_TMP123_DATA_U32LEN ];
static U32 au32TMP123DataRd[ SIMCPU_CFG_TMP123_DATA_U32LEN ];
//! @}

//! @name channel configuration Temp sensor
//! @{
static const SIMCPUCHANN_CFG cTMP123Cfg = // @suppress("Wrong derived data type")
{
    SIMCPU_CFG_INDEX_TMP123, //!< channel index tmp123
    SIMCPU_CFG_TMP123_SIM_MODE, //!< set sim mode
    SIMCPU_CFG_TMP123_BUFF, //!< set the buffers
    {
        SIMCPU_CFG_DSPI_ID, //!< set DSPI identifier
        SIMCPU_CFG_TMP123_CS, //!< set chip select
        SIMCPU_CFG_TMP123_CLK, //!< set working clock
        SIMCPU_CFG_TMP123_CS2SCK, //!< set delay between CS and SCK
        SIMCPU_CFG_TMP123_AFTER_SCK, //!< set delay After SCK
        SIMCPU_CFG_TMP123_AFTER_TRANS, //!< set delay After Transfer
        SIMCPU_CFG_TMP123_PHASE, //!< set phase
        SIMCPU_CFG_TMP123_POL, //!< set polarity
        SIMCPU_CFG_TMP123_BITORDER, //!< set bit order
        SIMCPU_CFG_TMP123_WORDSIZE, //!< set word size
        SIMCPU_CFG_TMP123_TRANSFERMODE, //!< set transfer mode
        SIMCPU_CFG_TMP123_CS_INACTIVE, //!< set inactive state
        SIMCPU_CFG_TMP123_CONTINUOUS, //!< set continuous mode
        SIMCPU_CFG_TMP123_USE_DMA //!< set eDMA
    }
};
//! @}

//! @name channel configuration FRAM (read access)
//! @{
static const SIMCPUCHANN_CFG cMemFRamReadCfg = // @suppress("Wrong derived data type")
{
    SIMCPU_CFG_INDEX_FRAM_READ, //!< channel index FRAM (read access)
    SIMCPU_CFG_FRAM_SIM_MODE, //!< set sim mode
    SIMCPU_CFG_FRAM_BUFF, //!<  set the buffers
    {
        SIMCPU_CFG_DSPI_ID, //!< set DSPI identifier
        SIMCPU_CFG_FRAM_CS, //!< set chip select
        SIMCPU_CFG_FRAM_CLK_READ, //!< set working clock
        SIMCPU_CFG_FRAM_CS2SCK_READ, //!< set delay between CS and SCK
        SIMCPU_CFG_FRAM_AFTER_SCK_READ, //!< set delay After SCK
        SIMCPU_CFG_FRAM_AFTER_TRANS_READ, //!< set delay After Transfer
        SIMCPU_CFG_FRAM_PHASE, //!< set phase
        SIMCPU_CFG_FRAM_POL, //!< set polarity
        SIMCPU_CFG_FRAM_BITORDER, //!< set bit order
        SIMCPU_CFG_FRAM_WORDSIZE, //!< set word size
        SIMCPU_CFG_FRAM_TRANSFERMODE, //!< set transfer mode
        SIMCPU_CFG_FRAM_CS_INACTIVE, //!< set inactive state
        SIMCPU_CFG_FRAM_CONTINUOUS, //!< set continuous mode
        SIMCPU_CFG_FRAM_USE_DMA //!< set eDMA
    }
};
//! @}

//! @name channel configuration FRAM (write access)
//! @{
static const SIMCPUCHANN_CFG cMemFRamWriteCfg = // @suppress("Wrong derived data type")
{
    SIMCPU_CFG_INDEX_FRAM_WRITE, //!< channel index FRAM (write access)
    SIMCPU_CFG_FRAM_SIM_MODE, //!< set sim mode
    SIMCPU_CFG_FRAM_BUFF, //!<  set the buffers
    {
        SIMCPU_CFG_DSPI_ID, //!< set DSPI identifier
        SIMCPU_CFG_FRAM_CS, //!< set chip select
        SIMCPU_CFG_FRAM_CLK_WRITE, //!< set working clock
        SIMCPU_CFG_FRAM_CS2SCK_WRITE, //!< set delay between CS and SCK
        SIMCPU_CFG_FRAM_AFTER_SCK_WRITE, //!< set delay After SCK
        SIMCPU_CFG_FRAM_AFTER_TRANS_WRITE, //!< set delay After Transfer
        SIMCPU_CFG_FRAM_PHASE, //!< set phase
        SIMCPU_CFG_FRAM_POL, //!< set polarity
        SIMCPU_CFG_FRAM_BITORDER, //!< set bit order
        SIMCPU_CFG_FRAM_WORDSIZE, //!< set word size
        SIMCPU_CFG_FRAM_TRANSFERMODE, //!< set transfer mode
        SIMCPU_CFG_FRAM_CS_INACTIVE, //!< set inactive state
        SIMCPU_CFG_FRAM_CONTINUOUS, //!< set continuous mode
        SIMCPU_CFG_FRAM_USE_DMA //!< set eDMA
    }
};
//! @}

//! @name channel configuration data flash 0
//! @{

//! Data flash channel is mapped to FRAM
//! The configuration of the data flash channel in SIM is changes that it accesses the
//! FRAM instead of the data flash that is no more equipped. Then there is no access conflict
//! any more between accessing above 8kBytes and the power fail data writing.

static const SIMCPUCHANN_CFG cMemDataFlash0Cfg = // @suppress("Wrong derived data type")
{
    SIMCPU_CFG_INDEX_DF(0), //!< channel index data flash 1
    SIMCPU_CFG_FRAM_SIM_MODE, //!< set sim mode
    SIMCPU_CFG_FRAM_BUFF, //!<  set the buffers
    {
        SIMCPU_CFG_DSPI_ID, //!< set DSPI identifier
        SIMCPU_CFG_FRAM_CS, //!< set chip select
        SIMCPU_CFG_FRAM_CLK_READ, //!< set working clock
        SIMCPU_CFG_FRAM_CS2SCK_READ, //!< set delay between CS and SCK
        SIMCPU_CFG_FRAM_AFTER_SCK_READ, //!< set delay After SCK
        SIMCPU_CFG_FRAM_AFTER_TRANS_READ, //!< set delay After Transfer
        SIMCPU_CFG_FRAM_PHASE, //!< set phase
        SIMCPU_CFG_FRAM_POL, //!< set polarity
        SIMCPU_CFG_FRAM_BITORDER, //!< set bit order
        SIMCPU_CFG_FRAM_WORDSIZE, //!< set word size
        SIMCPU_CFG_FRAM_TRANSFERMODE, //!< set transfer mode
        SIMCPU_CFG_FRAM_CS_INACTIVE, //!< set inactive state
        SIMCPU_CFG_FRAM_CONTINUOUS, //!< set continuous mode
        SIMCPU_CFG_FRAM_USE_DMA //!< set eDMA
    }
};

//! @}


//! memory allocation for runtime data.
//! Array for runtime data
static SIMCPUCHANN_RUNTIME cRunTime[SIMCPU_CFG_NR_CHANNELS]; // @suppress("Wrong derived data type")

// SIM CONFIGURATION  ================================================= */

const U8 u8SIMCpuNrDataFlashIndex = SIMCPU_CFG_NR_DATA_FLASHES;

// todo: it is a config. why not a const ?!?
SIMCPU_INFO cSimcpuInfo =  // @suppress("Wrong derived data type") // @suppress("Avoid Global Variables")
{
//Note: Suppression of "Avoid Global Variables", the scope of this variable is global and must therefore be declared as
//      such
    SIMCPU_CFG_NR_SECTIONS, // Number of used sections in SIM configuration
    {
        { // Section DSPI_B
            &cSimcpuSectionBCfg,
            &cSimcpuSectionBRunTime
        },
        { // empty section
            NULL,
            NULL
        },
        { // empty section
            NULL,
            NULL
        },
        { // empty section
            NULL,
            NULL
        }
    },
    SIMCPU_CFG_NR_CHANNELS, // Number of channels to manage
    // Note This order MUST be the same as given in simcpu.h
    // if a channel shall not be used, Configuration will be a NULL
    {
        { // SIMCPU_CFG_INDEX_CPLD
            &cCpldCfg,
            &(cRunTime[SIMCPU_CFG_INDEX_CPLD])
        },
        { // SIMCPU_CFG_INDEX_TMP123
            &cTMP123Cfg,
            &(cRunTime[SIMCPU_CFG_INDEX_TMP123])
        },
        { // SIMCPU_CFG_INDEX_FRAM_READ
            &cMemFRamReadCfg,
            &(cRunTime[SIMCPU_CFG_INDEX_FRAM_READ])
        },
        { // SIMCPU_CFG_INDEX_FRAM_WRITE
            &cMemFRamWriteCfg,
            &(cRunTime[SIMCPU_CFG_INDEX_FRAM_WRITE])
        },
        { // SIMCPU_CFG_INDEX_DF(0)
            &cMemDataFlash0Cfg,
            &(cRunTime[SIMCPU_CFG_INDEX_DF(0)])
        },
        { // 05 - nothing
            NULL,
            NULL
        },
        { // 06 - nothing
            NULL,
            NULL
        },
        { // 07 - nothing
            NULL,
            NULL
        },
        { // 08 - nothing
            NULL,
            NULL
        },
        { // 09 - nothing
            NULL,
            NULL
        },
        { // 10 - nothing
            NULL,
            NULL
        },
        { // 11 - nothing
            NULL,
            NULL
        },
        { // 12 - nothing
            NULL,
            NULL
        },
        { // 13 - nothing
            NULL,
            NULL
        },
        { // 14 - nothing
            NULL,
            NULL
        },
        { // 15 - nothing
            NULL,
            NULL
        }
    }
};


//**************************************** Modul global data segment ( static ) ****************************************

//************************************** Modul global constants ( static const ) ***************************************
//*************************************** Local func/proc prototypes ( static ) ****************************************

//** EndOfFile cfgsimcp.c **********************************************************************************************
