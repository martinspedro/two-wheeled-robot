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
#include <xc.h>

#include "../global.h"
#include "../interrupts.h"

#include "timer4.h"

/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define TIMER4_IPL  6        //!< Interrupt Priority Level for TIMER 4
#define TIMER4_IPSL 2        //!< Interrupt Sub Priority Level for TIMER 4



#define CLEAR_TMR4 {TMR4 = 0;}

/*******************************************************************************
 *                         CLASS METHODS
 ******************************************************************************/

void config_Timer4(void)
{
    DISABLE_TIMER_4;
    CLEAR_TMR4;
    
    /* Enable Timer4 module operation when CPU enters IDLE mode
     * 
     * Stop in IDLE Mode bit
     *   1 = Discontinue operation when CPU enters IDLE mode
     *   0 = Continue operation in IDLE mode
     */
    T4CONbits.SIDL = 0;
    
    /* Disable Timer 4 Gate Accumulation
     * 
     * Timer Gated Time Accumulation Enable bit
     *   When TCS = 1:
     *      This bit is ignored and reads as ?0?
     *   When TCS = ?0?:
     *      1 = Gated time accumulation is enabled
     *      0 = Gated time accumulation is disabled
     */
    T4CONbits.TGATE = 0;
    
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
    T4CONbits.TCKPS = 0b011;
    
    /* Select independent operation from Timer 2 and 3
     * 
     * 32-bit Timer Mode Select bits
     *   1 = TMR2 and TMR3 form a 32-bit timer
     *   0 = TMR2 and TMR3 are separate 16-bit timers
     * 
     */
    T4CONbits.T32 = 0;
    
    /* Select Internal Peripheral Clock as Clock Source
     * 
     * TMR2 Clock Source Select bit
     *   1 = External clock from T2CK pin
     *   0 = Internal peripheral clock
     */
    T4CONbits.TCS = 0;
    
    /* Set Period of PWM
     * 
     * Period Register
     *    PR<15:0>: 16-bit Timer2 period match value. Provides lower half of the
     *              32-bit period match value when Timer2 and Timer3 are 
     *              configured to form a 32-bit timer.
     */
     PR4 = PRESCALER_PID_INT_PERIOD;
     
     // INterrupts
     IPC4bits.T4IP = TIMER4_IPL;
     IPC4bits.T4IS = TIMER4_IPSL;
}


