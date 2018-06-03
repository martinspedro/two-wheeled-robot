/** 
 * \file    timer2.h
 * \brief   Timer 2 Module Header class file
 * \remarks Used by the PWM modules
 * 
 * The Timer 2 is the timer dedicated to the Output and Compare Peripheral, used
 * as a PWM Module
 * 
 * \author Pedro Martins
 * \date   Created on May 5, 2018, 7:58 PM
 */
#include <xc.h>

#ifndef TIMER2_H
#define	TIMER2_H

/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define ENABLE_TIMER_2  {T2CONbits.ON = 1;}     //!< Enables Timer 2 Peripheral
#define DISABLE_TIMER_2 {T2CONbits.ON = 0;}     //!< Disables Timer 2 Peripheral

#define ENABLE_TIMER2_INTERRUPTS  {IEC0bits.T2IE = 1;}       //!< Enables Timer 2 Interruptions
#define DISABLE_TIMER2_INTERRUPTS {IEC0bits.T2IE = 0;}       //!< Disables Timer 2 Interruptions
/*******************************************************************************
 *                        FUNCTION HEADERS DEFINITION
 ******************************************************************************/

/** \brief Configures Timer 2
 * 
 * Configures Timer 2 as a 16 bit timer with the Peripheral Clock as Clock Source
 * 
 * \remarks The independent operation of Timer 2 and 3 is selected on Timer 2 configuration
 * 
 * \param  None.
 * \return None.
 * 
 * \author Pedro Martins
 */
void config_Timer2(void);

#endif	/* TIMER2_H */

