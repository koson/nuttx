/************************************************************************************
 * configs/sama5df3x-ek/include/board.h
 *
 *   Copyright (C) 2013 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ************************************************************************************/

#ifndef __CONFIGS_SAMA5D3X_EK_INCLUDE_BOARD_H
#define __CONFIGS_SAMA5D3X_EK_INCLUDE_BOARD_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>

/************************************************************************************
 * Definitions
 ************************************************************************************/

/* Clocking *************************************************************************/
/* After power-on reset, the sam3u device is running on a 4MHz internal RC.  These
 * definitions will configure clocking
 *
 *   MAINOSC:  Frequency = 12MHz (crysta)
 *   PLLA: PLL Divider = 1, Multiplier = 66 to generate PLLACK = 792MHz
 *   Master Clock (MCK): Source = PLLACK/2, Prescalar = 1, MDIV = 3 to generate
*      MCK      =  132MHz
 *     CPU clock = 396MHz
 */

/* Main oscillator register settings.
 *
 *   The start up time should be should be:
 *   Start Up Time = 8 * MOSCXTST / SLCK = 56 Slow Clock Cycles.
 */

#define BOARD_CKGR_MOR_MOSCXTST    (62 << PMC_CKGR_MOR_MOSCXTST_SHIFT) /* Start-up Time */

/* PLLA configuration.
 *
 *   Divider = 1
 *   Multipler = 66
 */

#define BOARD_CKGR_PLLAR_COUNT     (63 << PMC_CKGR_PLLAR_COUNT_SHIFT)
#define BOARD_CKGR_PLLAR_OUT       (0)
#define BOARD_CKGR_PLLAR_MUL       (65 << PMC_CKGR_PLLAR_MUL_SHIFT)
#define BOARD_CKGR_PLLAR_DIV       PMC_CKGR_PLLAR_DIV_BYPASS

/* PMC master clock register settings.
 *
 *  Master/Processor Clock Source Selection = PLLA
 *  Master/Processor Clock Prescaler        = 1
 *  PLLA Divider                            = 2
 *  Master Clock Division (MDIV)            = 3
 *
 *  NOTE: Bit PLLADIV2 must always be set to 1 when MDIV is set to 3.
 *
 *  Prescaler input                         = 792MHz / 2 = 396MHz
 *  Prescaler output                        = 792MHz / 1 = 396MHz
 *  Processor Clock (PCK)                   = 396MHz
 *  Master clock (MCK)                      = 396MHz / 3 = 132MHz
 */

#define BOARD_PMC_MCKR_CSS         PMC_MCKR_CSS_PLLA
#define BOARD_PMC_MCKR_PRES        PMC_MCKR_PRES_DIV1
#define BOARD_PMC_MCKR_PLLADIV     PMC_MCKR_PLLADIV2
#define BOARD_PMC_MCKR_MDIV        PMC_MCKR_MDIV_PCKDIV3

/* USB UTMI PLL start-up time */

#define BOARD_CKGR_UCKR_UPLLCOUNT  (3 << PMC_CKGR_UCKR_UPLLCOUNT_SHIFT)

/* Resulting frequencies */

#define BOARD_MAINOSC_FREQUENCY    (12000000)  /* MAINOSC: 12MHz crystal on-board */
#define BOARD_PLLA_FREQUENCY       (792000000) /* PLLACK:  66 * 12Mhz / 1 */
#define BOARD_PCK_FREQUENCY        (396000000) /* CPU:     PLLACK / 2 / 1  */
#define BOARD_MCK_FREQUENCY        (132000000) /* MCK:     PLLACK / 2 / 1 / 3 */

/* HSMCI clocking
 *
 * Multimedia Card Interface clock (MCCK or MCI_CK) is Master Clock (MCK)
 * divided by (2*(CLKDIV+1)).
 *
 *   MCI_SPEED = MCK / (2*(CLKDIV+1))
 *   CLKDIV = MCI / MCI_SPEED / 2 - 1
 *
 * Where CLKDIV has a range of 0-255.
 */

/* MCK = 96MHz, CLKDIV = 119, MCI_SPEED = 96MHz / 2 * (119+1) = 400 KHz */

#define HSMCI_INIT_CLKDIV          (119 << HSMCI_MR_CLKDIV_SHIFT)

/* MCK = 96MHz, CLKDIV = 3, MCI_SPEED = 96MHz / 2 * (3+1) = 12 MHz */

#define HSMCI_MMCXFR_CLKDIV        (3 << HSMCI_MR_CLKDIV_SHIFT)

/* MCK = 96MHz, CLKDIV = 1, MCI_SPEED = 96MHz / 2 * (1+1) = 24 MHz */

#define HSMCI_SDXFR_CLKDIV         (1 << HSMCI_MR_CLKDIV_SHIFT)
#define HSMCI_SDWIDEXFR_CLKDIV     HSMCI_SDXFR_CLKDIV

/* FLASH wait states
 *
 * FWS Max frequency
 *     1.62V 1.8V
 * --- ----- ------
 *  0  24MHz 27MHz
 *  1  40MHz 47MHz
 *  2  72MHz 84MHz
 *  3  84MHz 96MHz
 */

#define BOARD_FWS                  3

/* LED definitions ******************************************************************/
/* There are two LEDs on the SAMA5D3 series-CM board that can be controlled
 * by software.  A  blue LED is controlled via GPIO pins.  A red LED normally
 * provides an indication that power is supplied to the board but can also
 * be controlled via software.
 *
 *   PE25.  This blue LED is pulled high and is illuminated by pulling PE25
 *   low.
 *
 *   PE24.  The red LED is also pulled high but is driven by a transistor so
 *   that it is illuminated when power is applied even if PE24 is not
 *   configured as an output.  If PE24 is configured as an output, then the
 *   LCD is illuminated by a high output.
 */

/* LED index values for use with sam_setled() */

#define BOARD_BLUE        0
#define BOARD_RED         1
#define BOARD_NLEDS       2

/* LED bits for use with sam_setleds() */

#define BOARD_BLUE_BIT    (1 << BOARD_BLUE)
#define BOARD_RED_BIT     (1 << BOARD_RED)


/* These LEDs are not used by the board port unless CONFIG_ARCH_LEDS is
 * defined.  In that case, the usage by the board port is defined in
 * include/board.h and src/sam_leds.c. The LEDs are used to encode OS-related
 * events as follows:
 *
 *      SYMBOL            Val    Meaning                     LED state
 *                                                         Blue     Red
 *      ----------------- ---   -----------------------  -------- --------   */
#define LED_STARTED       0  /* NuttX has been started     OFF      OFF      */
#define LED_HEAPALLOCATE  0  /* Heap has been allocated    OFF      OFF      */
#define LED_IRQSENABLED   0  /* Interrupts enabled         OFF      OFF      */
#define LED_STACKCREATED  1  /* Idle stack created         ON       OFF      */
#define LED_INIRQ         2  /* In an interrupt              No change       */
#define LED_SIGNAL        2  /* In a signal handler          No change       */
#define LED_ASSERTION     2  /* An assertion failed          No change       */
#define LED_PANIC         3  /* The system has crashed     OFF      Blinking */
#undef  LED_IDLE             /* MCU is is sleep mode         Not used        */

/* Thus if the blue LED is statically on, NuttX has successfully booted and
 * is, apparently, running normmally.  If the red is flashing at
 * approximately 2Hz, then a fatal error has been detected and the system
 * has halted.
 */

/* Button definitions ***************************************************************/
/* There are five push button switches on the SAMA5D3X-EK base board:
 *
 *   1. One Reset, board reset (BP1)
 *   2. One Wake up, push button to bring the processor out of low power mode
 *     (BP2)
 *   3. One User momentary Push Button
 *   4. One Disable CS Push Button
 *
 * Only the momentary push button is controllable by software (labeled
 * "PB_USER1" on the board):
 *
 *   - PE27.  Pressing the switch connect PE27 to grounded.  Therefore, PE27
 *     must be pulled high internally.  When the button is pressed the SAMA5
 *     will sense "0" is on PE27.
 */

#define BUTTON_USER1      0
#define NUM_BUTTONS       1

#define BUTTON_USER1_BIT  (1 << BUTTON_USER1)

/************************************************************************************
 * Assembly Language Macros
 ************************************************************************************/

#ifdef __ASSEMBLY__
	.macro	config_sdram
	.endm
#endif /* __ASSEMBLY__ */

/************************************************************************************
 * Public Data
 ************************************************************************************/

#ifndef __ASSEMBLY__

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C" {
#else
#define EXTERN extern
#endif

/************************************************************************************
 * Public Function Prototypes
 ************************************************************************************/
/************************************************************************************
 * Name: sam_boardinitialize
 *
 * Description:
 *   All SAMA5 architectures must provide the following entry point.  This entry point
 *   is called early in the intitialization -- after all memory has been configured
 *   and mapped but before any devices have been initialized.
 *
 ************************************************************************************/

void sam_boardinitialize(void);

/************************************************************************************
 * Name:  sam_ledinit, sam_setled, and sam_setleds
 *
 * Description:
 *   If CONFIG_ARCH_LEDS is defined, then NuttX will control the on-board LEDs.  If
 *   CONFIG_ARCH_LEDS is not defined, then the following interfaces are available to
 *   control the LEDs from user applications.
 *
 ************************************************************************************/

#ifndef CONFIG_ARCH_LEDS
void sam_ledinit(void);
void sam_setled(int led, bool ledon);
void sam_setleds(uint8_t ledset);
#endif

/************************************************************************************
 * Name: up_buttoninit
 *
 * Description:
 *   up_buttoninit() must be called to initialize button resources.  After that,
 *   up_buttons() may be called to collect the current state of all buttons or
 *   up_irqbutton() may be called to register button interrupt handlers.
 *
 ************************************************************************************/

#ifdef CONFIG_ARCH_BUTTONS
void up_buttoninit(void);

/************************************************************************************
 * Name: up_buttons
 *
 * Description:
 *   After up_buttoninit() has been called, up_buttons() may be called to collect
 *   the state of all buttons.  up_buttons() returns an 8-bit bit set with each bit
 *   associated with a button.  See the BUTTON* definitions above for the meaning of
 *   each bit in the returned value.
 *
 ************************************************************************************/

uint8_t up_buttons(void);

/************************************************************************************
 * Name: up_irqbutton
 *
 * Description:
 *   This function may be called to register an interrupt handler that will be
 *   called when a button is depressed or released.  The ID value is one of the
 *   BUTTON* definitions provided above. The previous interrupt handler address is
 *   returned (so that it may restored, if so desired).
 *
 ************************************************************************************/

#ifdef CONFIG_PIOA_IRQ
xcpt_t up_irqbutton(int id, xcpt_t irqhandler);
#endif
#endif /* CONFIG_ARCH_BUTTONS */

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* !__ASSEMBLY__ */
#endif  /* __CONFIGS_SAMA5D3X_EK_INCLUDE_BOARD_H */
