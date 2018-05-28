/** 
 * \file   timer3.c
 * \brief  Timer 3 Module C configuration class file
 * 
 * The Timer 3 is the timer dedicated to the Output and Compare Peripheral, used
 * as a PWM Module
 * 
 * \author Pedro Martins
 * \date   Created on May 28, 2018, 00:13 AM
 */


#include <stdio.h>
#include <stdlib.h>
#include "../global.h"
#include "../interrupts.h"
#include "timer3.h"
#include "../UART.X/uart1.h"
/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define TIMER3_IPL  2        //!< Interrupt Priority Level for TIMER 3
#define TIMER3_IPSL 1        //!< Interrupt Sub Priority Level for TIMER 3


#define CLEAR_TMR3_INT_FLAG {IFS0bits.T3IF = 0;}
#define CLEAR_TMR3 {TMR3 = 0;}

/*******************************************************************************
 *                         CLASS METHODS
 ******************************************************************************/

/* Select independent operation from Timer 2 and 3 is selected on TImer 2*/
void config_Timer3(void)
{
    DISABLE_TIMER_3;
    DISABLE_TIMER3_INTERRUPTS;
    CLEAR_TMR3;
    CLEAR_TMR3_INT_FLAG;
    
    /* Enable Timer3 module operation when CPU enters IDLE mode
     * 
     * Stop in IDLE Mode bit
     *   1 = Discontinue operation when CPU enters IDLE mode
     *   0 = Continue operation in IDLE mode
     */
    T3CONbits.SIDL = 0;
    
    /* Disable Timer 3 Gate Accumulation
     * 
     * Timer Gated Time Accumulation Enable bit
     *   When TCS = 1:
     *      This bit is ignored and reads as ?0?
     *   When TCS = ?0?:
     *      1 = Gated time accumulation is enabled
     *      0 = Gated time accumulation is disabled
     */
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
    
     
    /* Select Internal Peripheral Clock as Clock Source
     * 
     * TMR3 Clock Source Select bit
     *   1 = External clock from T2CK pin
     *   0 = Internal peripheral clock
     */
    T3CONbits.TCS = 0;
    
    /* Set Period of PWM
     * 
     * Period Register
     *    PR<15:0>: 16-bit Timer2 period match value. Provides lower half of the
     *              32-bit period match value when Timer2 and Timer3 are 
     *              configured to form a 32-bit timer.
     */
     PR3 = PR3_PERIOD;
     
     IPC3bits.T3IP = TIMER3_IPL;
     IPC3bits.T3IS = TIMER3_IPSL;
}

void __ISR(_TIMER_3_VECTOR, IPL2SOFT) TIMER3_ISR(void)
{
    LATDbits.LATD4 = 1;
    CLEAR_TMR3_INT_FLAG;
    //AD1CON1bits.ASAM = 1;		// start conversion
    put_uint16(ADC1BUF0);
    put_char('\n');
    put_uint16(ADC1BUF1);
    put_char('\n');
    LATDbits.LATD4 = 0;

}