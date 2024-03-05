/*SOC
**********************************************************************
**  _______  _______ _________ _______  _______ _________ _______   **
** (  ____ \(  ____ \\__   __/(  ___  )(  ____ )\__   __/(  ___  )  **
** | (    \/| (    \/   ) (   | (   ) || (    )|   ) (   | (   ) |  **
** | (_____ | |         | |   | |   | || (____)|   | |   | (___) |  **
** (_____  )| |         | |   | |   | ||  _____)   | |   |  ___  |  **
**       ) || |         | |   | |   | || (         | |   | (   ) |  **
** /\____) || (____/\___) (___| (___) || )         | |   | )   ( |  **
** \_______)(_______/\_______/(_______)|/          )_(   |/     \|  **
**                                                                  **
** (c) 2002..2004 Sciopta Systems GmbH, Litronic AG/ Schweiz        **
**                                                                  **
**********************************************************************
** ID: S07229BS3                                                    **
** $Revision: 1.1 $                                                 **
** $Date: 2008/02/29 14:50:44 $                                     **
** Resethook for phyCoreMPC5554                                     **
** RH: xx.05.08 EBI init adjusted  for CPU03 and CB12, EBDF=3!      **
** RH: 24.07.08 PLL now setup in 4 Steps to smooth ramp up and avoid**
**              lock  problems during frequency change              **
**              Hold Wdg. Pin on High                               **
** RH: 29.07.08 Cache inval. and ClkOut div 4 before PLL setup up   **
**              L2RAM ECC clear                                     **
**              Cache Enable after PLL has locked on final frq.     **
** WH: 25.10.10 Waitstates to CS1 (PSRAM) and CS3 (SMSC) increased  **
**                            2->4            2->3                  **
** PS: 09.03.12 FWR separation: Parts done by FWR removed.          **
**********************************************************************
*/
#define __ASM_INCLUDED__
#include <arch/os.h> /* CPUTYPES */
#include <machine/ppc/ppc_asm.h>

/*
**********************************************************************
**                            reset_hook
**********************************************************************
*/
  .text

  FUNC(reset_hook)

  mflr  r31                             // save return address

  bl    exception_init                  // setup INTC and IVORs

  mtlr  r31
  li    r3,0
  blr                                   // return to kernel

  END_FUNC(reset_hook)

  .end
