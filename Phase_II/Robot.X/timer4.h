/** 
 * \file   timer4.h
 * \brief  Timer 4 Module Header class file
 * 
 * The Timer 4 is the timer dedicated to PID control algorithm
 * 
 * \author Pedro Martins
 * \date   Created on May 5, 2018, 7:58 PM
 */

#include <xc.h>

#ifndef TIMER4_H
#define	TIMER4_H


/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define ENABLE_TIMER_4  {T4CONbits.ON = 1;}     //!< Enables Timer 4 Peripheral
#define DISABLE_TIMER_4 {T4CONbits.ON = 0;}     //!< Disables Timer 4 Peripheral

#define ENABLE_TIMER4_INTERRUPTS  {IEC0bits.T4IE = 1;}      //!< Enables Timer 4 Interrupts
#define DISABLE_TIMER4_INTERRUPTS {IEC0bits.T4IE = 0;}      //!< Disables Timer 4 Interrupts

#define CLEAR_TMR4_IF {IFS0bits.T4IF = 0;}      //!< Clears Timer 4 Interrupt Flag

#define TMR4_INT_PERIOD 50000          //!< Timer 4 Interrupt Period


/*******************************************************************************
 *                        FUNCTION HEADERS DEFINITION
 ******************************************************************************/

/** \brief Configures Timer 4
 * 
 * Configures Timer 4 as a 16 bit timer with the Peripheral Clock as Clock Source
 * 
 * \remarks The independent operation of Timer 4 and 5 is selected on Timer 4 configuration
 * 
 * \param  None.
 * \return None.
 * 
 * \author Pedro Martins
 */
void config_Timer4(void);

#endif	/* TIMER4_H */

