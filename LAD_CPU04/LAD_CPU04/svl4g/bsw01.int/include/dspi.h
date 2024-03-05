//**********************************************************************************************************************
//
//                                                   dspi.h
//
//**********************************************************************************************************************
//
//                                     Copyrights(c) 20222 by KNORR-BREMSE,
//                                Systeme fuer Schienenfahrzeuge GmbH, Muenchen
//
//! @project IBC
//! @date    2023-11-13
//! @author  C. Brancolini
//!
//**********************************************************************************************************************
//
//! @file    dspi.h
//! @brief   Constant declaration for accessing MPC5534 DSPI Register
//!
//! @details the DSPI Config register settings are put in using position mask of the configuration bits.
//!          The real access to the register is done by the DSPI driver.
//!          The informations in this file, are only used to generate the config data given to the driver.
//
//**********************************************************************************************************************
// Date          Author      Changes:
// 27.07.11      R. Hafner   Start
// 31.07.11      R. Hafner   ctar
// 20.10.11      W. Boigk    removed DSPI struct constants and macros are
//                           used in cfg_sim.c
// 28.11.22      J. Lulli    Coding guidelines update
// 2023-11-13    C. Brancolini  Lint Plus clean up
//
//**********************************************************************************************************************

//*************************************** Compiler options ( #pragma ) *************************************************

//*********************************** Header / include files ( #include ) **********************************************
// 
#include <std_defs.h>
#include <esra_def.h>

#ifndef DSPI_H
#define DSPI_H


// basic definitions for DSPI operation  setup
// all informations here are positions of Bits inside the DSPI Config Registers
// Documentation in Chapter Memory Map and Register Definition for DSPI
// in Rev. 2 this is Chapter 19.3

#define DSPI_MCR_MSTR                   (0x80000000UL) 
//!< 1 DSPI Master / 0 DSPI Slave
#define DSPI_MCR_CSCK                   (0x40000000UL) 
//!< 1 SCK runs continously, 0 SCK only on transfer active

// Module configuration
#define DSPI_MCR_DCONF(x)               (((x)&0x03UL)<<28)
//!< Position of Config of Operation Modes
#define DSPI_MCR_FRZ                    (0x08000000UL)
//!< Position of Freeze of serial transfer
#define DSPI_MCR_MTFE                   (0x04000000UL)
//!< Position of Modify time Format
#define DSPI_MCR_PCSSE                  (0x02000000UL)
//!< Position of Strope Enable
#define DSPI_MCR_ROOE                   (0x01000000UL)
//!< Position of Receive overflow enable
#define DSPI_MCR_CSIS7                  (0x00800000UL)
//!< Position of CS7 inactive state config
#define DSPI_MCR_CSIS6                  (0x00400000UL)
//!< Position of CS6 inactive state config
#define DSPI_MCR_CSIS5                  (0x00200000UL)
//!< Position of CS5 inactive state config
#define DSPI_MCR_CSIS4                  (0x00100000UL)
//!< Position of CS4 inactive state config
#define DSPI_MCR_CSIS3                  (0x00080000UL)
//!< Position of CS3 inactive state config
#define DSPI_MCR_CSIS2                  (0x00040000UL)
//!< Position of CS2 inactive state config
#define DSPI_MCR_CSIS1                  (0x00020000UL)
//!< Position of CS1 inactive state config
#define DSPI_MCR_CSIS0                  (0x00010000UL)
//!< Position of CS0 inactive state config
#define DSPI_MCR_MDIS                   (0x00004000UL)
//!< Position of module dissable
#define DSPI_MCR_DTXF                   (0x00002000UL)
//!< Position of Disable Transmit FIFO
#define DSPI_MCR_DRXF                   (0x00001000UL)
//!< Position of Disable receive FIFO
#define DSPI_MCR_CTXF                   (0x00000800UL)
//!< Position of clear TX FIFO
#define DSPI_MCR_CRXF                   (0x00000400UL)
//!< Position of clear RX FIFO
#define DSPI_MCR_SMPL_PT(x)             (((x)&0x03UL)<<8)
//!< Position of modify sample points
#define DSPI_MCR_HALT                   (0x00000001UL)
//!< Position of MCR HALT

 // Status
#define DSPI_SR_TCF                     (0x80000000UL)
//!< Position of Transfer complete flag
#define DSPI_SR_TXRXS                   (0x40000000UL)
//!< Position of TX RX Mode
#define DSPI_SR_EOQF                    (0x10000000UL)
//!< Position of End of Que flag
#define DSPI_SR_TFUF                    (0x08000000UL)
//!< Position of Transmit FIFO underflow flag
#define DSPI_SR_TFFF                    (0x02000000UL)
//!< Position of Transmit FIFO fill flag
#define DSPI_SR_RFOF                    (0x00080000UL)
//!< Position of Receive FIFO overflow flag
#define DSPI_SR_RFDF                    (0x00020000UL)
//!< Position of Receive FIFO drain flag
#define DSPI_SR_TXCTR(x)                (((x)&0x0FUL)<<12)
//!< Position of TX FIFO counter
#define DSPI_SR_TXPTR(x)                (((x)&0x0FUL)<<8)
//!< Position of Transmit next Pointer flag
#define DSPI_SR_RXCTR(x)                (((x)&0x0FUL)<<4)
//!< Position of Pop next pointer flag
#define DSPI_SR_RXPTR(x)                (((x)&0x0FUL))


// Clock and transfer attributes
#define DSPI_CTAR_DBR                   (0x80000000UL)
//!< Position of double baud rate
#define DSPI_CTAR_TRSZ(x)               ((((x)-1UL)&0x0FUL)<<27)
//!< Position of number of bits per frame
#define DSPI_CTAR_CPOL                  (0x04000000UL)
//!< Position of clock polarity
#define DSPI_CTAR_CPHA                  (0x02000000UL)
//!< Position of Clock phase
#define DSPI_CTAR_LSBFE                 (0x01000000UL)
//!< Position of LSB first enable
#define DSPI_CTAR_PCSSCK(x)             (((x)&0x03UL)<<22)
//!< Position of PCS to SCK delay prescaler
#define DSPI_CTAR_PCSSCK_7CLK           (0x00A00000UL)
//!< Position of PCS to SCK delay prescaler
#define DSPI_CTAR_PCSSCK_5CLK           (0x00800000UL)
//!< Position of PCS to SCK delay prescaler
#define DSPI_CTAR_PCSSCK_3CLK           (0x00400000UL)
//!< Position of PCS to SCK delay prescaler
#define DSPI_CTAR_PCSSCK_1CLK           (0x00000000UL)
//!< Position of after SCK delay prescaler
#define DSPI_CTAR_PASC(x)               (((x)&0x03UL)<<20)
//!< Position of after SCK delay prescaler
#define DSPI_CTAR_PASC_7CLK             (0x00300000UL)
//!< Position of after SCK delay prescaler
#define DSPI_CTAR_PASC_5CLK             (0x00200000UL)
//!< Position of after SCK delay prescaler
#define DSPI_CTAR_PASC_3CLK             (0x00100000UL)
//!< Position of after SCK delay prescaler
#define DSPI_CTAR_PASC_1CLK             (0x00000000UL)
//!< Position of after SCK delay prescaler
#define DSPI_CTAR_PDT(x)                (((x)&0x03UL)<<18)
//!< Position of delay after transfer prescaler
#define DSPI_CTAR_PDT_7CLK              (0x000A0000UL)
//!< Position of delay after transfer prescaler
#define DSPI_CTAR_PDT_5CLK              (0x00080000UL)
//!< Position of delay after transfer prescaler
#define DSPI_CTAR_PDT_3CLK              (0x00040000UL)
//!< Position of delay after transfer prescaler
#define DSPI_CTAR_PDT_1CLK              (0x00000000UL)
//!< Position of delay after transfer prescaler
#define DSPI_CTAR_PBR(x)                (((x)&0x03UL)<<16)
//!< Position of baud rate prescaler
#define DSPI_CTAR_PBR_7CLK              (0x00030000UL)
//!< Position of baud rate prescaler
#define DSPI_CTAR_PBR_5CLK              (0x00020000UL)
//!< Position of baud rate prescaler
#define DSPI_CTAR_PBR_3CLK              (0x00010000UL)
//!< Position of baud rate prescaler
#define DSPI_CTAR_PBR_1CLK              (0x00000000UL)
//!< Position of baud rate prescaler
#define DSPI_CTAR_CSSCK(x)              (((x)&0x0FUL)<<12)
//!< Position of PCS to SCK delay scaler
#define DSPI_CTAR_ASC(x)                (((x)&0x0FUL)<<8)
//!< Position of after SCK delay scaler
#define DSPI_CTAR_DT(x)                 (((x)&0x0FUL)<<4)
//!< Position of baud rate scaler
#define DSPI_CTAR_BR(x)                 (((x)&0x0FUL))

// Transfer control - 32-bit access
#define DSPI_TFR_CONT                   (0x80000000UL)
//!< Position of Continuous peripheral chip select enable
#define DSPI_TFR_CTAS(x)                (((x)&0x07UL)<<28)
//!< Position of clock and transfer attributes select
#define DSPI_TFR_EOQ                    (0x08000000UL)
//!< Position of end of queue
#define DSPI_TFR_CTCNT                  (0x04000000UL)
//!< Position ofclear spi tcnt
#define DSPI_TFR_CS7                    (0x00800000UL)
//!< Position of CS7 Negation
#define DSPI_TFR_CS6                    (0x00400000UL)
//!< Position of CS6 Negation
#define DSPI_TFR_CS5                    (0x00200000UL)
//!< Position of CS5 Negation
#define DSPI_TFR_CS4                    (0x00100000UL)
//!< Position of CS4 Negation
#define DSPI_TFR_CS3                    (0x00080000UL)
//!< Position of CS3 Negation
#define DSPI_TFR_CS2                    (0x00040000UL)
//!< Position of CS2 Negation
#define DSPI_TFR_CS1                    (0x00020000UL)
//!< Position of CS1 Negation
#define DSPI_TFR_CS0                    (0x00010000UL)
//!< Position of CS0 Negation
#endif                                  // __DSPI_H__                       */
//** EndOfFile dspi.h **************************************************************************************************
