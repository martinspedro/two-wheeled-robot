/** 
 * \file   timer3.c
 * \brief  Timer 3 Module C configuration class file
 * \remarks Timer 3 is the timer dedicated to the Analog to Digital Converter (ADC)
 * 
 * \author Pedro Martins
 * \date   Created on May 28, 2018, 00:13 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "../interrupts.h"

#include "timer3.h"


/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define TIMER3_IPL  2        //!< Interrupt Priority Level for TIMER 3
#define TIMER3_IPSL 1        //!< Interrupt Sub Priority Level for TIMER 3

#define CLEAR_TMR3_IF {IFS0bits.T3IF = 0;}    //!< Clear Timer 3 Interrupt Flag
#define CLEAR_TMR3 {TMR3 = 0;}                //!< Clear Timer 3 Count Register


/*******************************************************************************
 *                         CLASS METHODS
 ******************************************************************************/

void config_Timer3(void)
{
    DISABLE_TIMER_3;
    DISABLE_TIMER3_INTERRUPTS;
    CLEAR_TMR3;
    CLEAR_TMR3_IF;
    
    /* Enable Timer3 module operation when CPU enters IDLE mode */
    T3CONbits.SIDL = 0;
    
    /* Disable Timer 3 Gate Accumulation */
    T3CONbits.TGATE = 0;
    
    /* Select 1:1 prescaler
     * 
     * Timer Input Clock Prescale Select bits
     *   111 = 1:256 prescale value
     *   110 = 1:64  prescale value
     *   101 = 1:32  prescale value
     *   100 = 1:16  prescale value
     *   011 = 1:8   prescale value
     *   010 = 1:4   prescale value
     *   001 = 1:2   prescale value
     *   000 = 1:1   prescale value
     */
    T3CONbits.TCKPS = 0b000;
    
     
    /* Select Internal Peripheral Clock as Clock Source */
    T3CONbits.TCS = 0;
    
    /* Set Timer Period */
     PR3 = PR3_PERIOD;
     
     /* Set Interrupt Priority Level and Sublevel */
     IPC3bits.T3IP = TIMER3_IPL;
     IPC3bits.T3IS = TIMER3_IPSL;
}



/** \brief ISR for Timer 3
 * 
 * \pre    Global Interrupts must be configured and enabled
 * \pre    Timer 3 must be configured and enabled
 * 
 * \remarks This interrupt service routine is empty because it is not executed
 * 
 * \param  None.
 * \return None.
 * 
 * Interruption Service Routine for Timer 3 (TMR3)
 * This Timer is associated with the ADC module
 * 
 * The Interruption Priority Level is 2 and the compiler must write software to
 * perform the context switching (IPL2SOFT)
 * 
 * \author Pedro Martins
 */
void __ISR(_TIMER_3_VECTOR, IPL2SOFT) TIMER3_ISR(void)
{
    CLEAR_TMR3_IF;
}