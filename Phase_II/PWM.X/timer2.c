/** 
 * \file    timer2.c
 * \brief   Timer 2 Module C configuration class file
 * \remarks Used by the PWM modules
 * 
 * The Timer 2 is the timer dedicated to the Output and Compare Peripheral, used
 * as a PWM Module
 * 
 * \author Pedro Martins
 * \date   Created on May 5, 2018, 7:39 PM
 */


#include <stdio.h>
#include <stdlib.h>

#include "../global.h"
#include "../interrupts.h"

#include "pwm.h"
#include "timer2.h"

/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define TIMER2_IPL  0        //!< Interrupt Priority Level for TIMER 2
#define TIMER2_IPSL 0        //!< Interrupt Sub Priority Level for TIMER 2


#define TMR2_PRESCALER 1        //!< Timer 2 Prescaler

/** \brief PWM Period Value
 * 
 * The PWM period can be calculated by
 * \f[\frac{PBCLK}{FREQ\_PWM \times TMR2\_PRESCALER} - 1\f]
 */
#define TMR2_PERIOD  PBCLK / (FREQ_PWM * TMR2_PRESCALER) - 1

#define CLEAR_TMR2_IF {IFS0bits.T2IF = 0;}    //!< Clear Timer 2 Interrupt Flag
#define CLEAR_TMR2 {TMR2 = 0;}                //!< Clear Timer 2 Count Register


/*******************************************************************************
 *                         CLASS METHODS
 ******************************************************************************/

void config_Timer2(void)
{
    DISABLE_TIMER_2;
    CLEAR_TMR2;
    
    /* Enable Timer2 module operation when CPU enters IDLE mode */
    T2CONbits.SIDL = 0;
    
    /* Disable Timer 2 Gate Accumulation */
    T2CONbits.TGATE = 0;
    
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
    T2CONbits.TCKPS = 0b000;
    
    /* Select independent operation from Timer 2 and 3 */
    T2CONbits.T32 = 0;
    
    /* Select Internal Peripheral Clock as Clock Source */
    T2CONbits.TCS = 0;
    
    /* Set Timer 2 Period */
     PR2 = TMR2_PERIOD;
     
    /* Set Interrupt Priority Level and Sublevel */
    IPC2bits.T2IP = TIMER2_IPL;
    IPC2bits.T2IS = TIMER2_IPSL;
}



/** \brief ISR for Timer 2
 * 
 * \pre    Global Interrupts must be configured and enabled
 * \pre    Timer 2 must be configured and enabled
 * 
 * \remarks This interrupt service routine is empty because it is not executed
 * 
 * \param  None.
 * \return None.
 * 
 * Interruption Service Routine for Timer 2 (TMR2)
 * This Timer is associated with the PWM module
 * 
 * The Interruption Priority Level is 0 and the compiler must write software to
 * perform the context switching (IPL0SOFT)
 * 
 * \author Pedro Martins
 */
void __ISR(_TIMER_2_VECTOR, IPL0SOFT) TIMER2_ISR(void)
{
    CLEAR_TMR2_IF;
}