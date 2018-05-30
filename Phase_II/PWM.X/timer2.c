/** 
 * \file   timer2.c
 * \brief  Timer 2 Module C configuration class file
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

#include "pwm.h"
#include "timer2.h"

/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define TMR2_PRESCALER 1

#define PWM_PERIOD    PBCLK / (FREQ_PWM * TMR2_PRESCALER) - 1



/*******************************************************************************
 *                         CLASS METHODS
 ******************************************************************************/

void config_Timer2(void)
{
    DISABLE_TIMER_2;
    
    /* Enable Timer2 module operation when CPU enters IDLE mode
     * 
     * Stop in IDLE Mode bit
     *   1 = Discontinue operation when CPU enters IDLE mode
     *   0 = Continue operation in IDLE mode
     */
    T2CONbits.SIDL = 0;
    
    /* Disable Timer 2 Gate Accumulation
     * 
     * Timer Gated Time Accumulation Enable bit
     *   When TCS = 1:
     *      This bit is ignored and reads as ?0?
     *   When TCS = ?0?:
     *      1 = Gated time accumulation is enabled
     *      0 = Gated time accumulation is disabled
     */
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
    
    /* Select independent operation from Timer 2 and 3
     * 
     * 32-bit Timer Mode Select bits
     *   1 = TMR2 and TMR3 form a 32-bit timer
     *   0 = TMR2 and TMR3 are separate 16-bit timers
     * 
     */
    T2CONbits.T32 = 0;
    
    /* Select Internal Peripheral Clock as Clock Source
     * 
     * TMR2 Clock Source Select bit
     *   1 = External clock from T2CK pin
     *   0 = Internal peripheral clock
     */
    T2CONbits.TCS = 0;
    
    /* Set Period of PWM
     * 
     * Period Register
     *    PR<15:0>: 16-bit Timer2 period match value. Provides lower half of the
     *              32-bit period match value when Timer2 and Timer3 are 
     *              configured to form a 32-bit timer.
     */
     PR2 = PWM_PERIOD;
}