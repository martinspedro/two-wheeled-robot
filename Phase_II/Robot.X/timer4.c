/** 
 * \file   timer4.c
 * \brief  Timer 4 Module C configuration class file
 * 
 * The Timer 4 is the timer dedicated to PID control algorithm
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


#define CLEAR_TMR4 {TMR4 = 0;}      //!< Clear Timer 4 Count Register

/*******************************************************************************
 *                         CLASS METHODS
 ******************************************************************************/

void config_Timer4(void)
{
    DISABLE_TIMER_4;
    CLEAR_TMR4;
    
    /* Enable Timer4 module operation when CPU enters IDLE mode */
    T4CONbits.SIDL = 0;
    
    /* Disable Timer 4 Gate Accumulation */
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
    
    /* Select independent operation from Timer 4 and 5 */
    T4CONbits.T32 = 0;
    
    /* Select Internal Peripheral Clock as Clock Source */
    T4CONbits.TCS = 0;
    
    /* Set Period of Timer 4 interrupt */
     PR4 = TMR4_INT_PERIOD;
     
     // INterrupts
     IPC4bits.T4IP = TIMER4_IPL;
     IPC4bits.T4IS = TIMER4_IPSL;
}


