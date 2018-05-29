/* 
 * File:   timer2.h
 * Author: martinspedro
 *
 * Created on May 5, 2018, 7:58 PM
 */

#include <xc.h>

#ifndef TIMER4_H
#define	TIMER4_H

#define ENABLE_TIMER_4  {T4CONbits.ON = 1;}
#define DISABLE_TIMER_4 {T4CONbits.ON = 0;}

#define ENABLE_TIMER4_INTERRUPTS  {IEC0bits.T4IE = 1;}
#define DISABLE_TIMER4_INTERRUPTS {IEC0bits.T4IE = 0;}

#define CLEAR_TMR4_INT_FLAG {IFS0bits.T4IF = 0;}

#define PRESCALER_PID_INT_PERIOD 50000

void config_Timer4(void);

#endif	/* TIMER4_H */

