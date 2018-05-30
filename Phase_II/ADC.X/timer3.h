/* 
 * File:   timer2.h
 * Author: martinspedro
 *
 * Created on May 5, 28, 2018, 12:09 AM
 */

#include <xc.h>

#ifndef TIMER3_H
#define	TIMER3_H

#define ENABLE_TIMER_3  {T3CONbits.ON = 1;}
#define DISABLE_TIMER_3 {T3CONbits.ON = 0;}

#define ENABLE_TIMER3_INTERRUPTS  {IEC0bits.T3IE = 1;}
#define DISABLE_TIMER3_INTERRUPTS {IEC0bits.T3IE = 0;}


#define PR3_PERIOD 50000


void config_Timer3(void);

#endif	/* TIMER3_H */



