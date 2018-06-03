/** 
 * \file   timer3.h
 * \brief  Timer 3 Module Header class file
 * \remarks Timer 3 is the timer dedicated to the Analog to Digital Converter (ADC)
 * 
 * \author Pedro Martins
 * \date   Created on May 28, 2018, 12:09 AM
 */

#include <xc.h>

#ifndef TIMER3_H
#define	TIMER3_H

/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define ENABLE_TIMER_3  {T3CONbits.ON = 1;}     //!< Enables Timer 3 Peripheral
#define DISABLE_TIMER_3 {T3CONbits.ON = 0;}     //!< Disables Timer 3 Peripheral

#define ENABLE_TIMER3_INTERRUPTS  {IEC0bits.T3IE = 1;}       //!< Enables Timer 3 Interruptions
#define DISABLE_TIMER3_INTERRUPTS {IEC0bits.T3IE = 0;}       //!< Disables Timer 3 Interruptions

#define PR3_PERIOD 50000        //!< Timer 3 Period Register Value



/*******************************************************************************
 *                        FUNCTION HEADERS DEFINITION
 ******************************************************************************/

/** \brief Configures Timer 3
 * 
 * Configures Timer 3 as a 16 bit timer with the Peripheral Clock as Clock Source
 * 
 * \remarks The independent operation of Timer 2 and 3 is selected on Timer 2 configuration
 * 
 * \param  None.
 * \return None.
 * 
 * \author Pedro Martins
 */
void config_Timer3(void);

#endif	/* TIMER3_H */
