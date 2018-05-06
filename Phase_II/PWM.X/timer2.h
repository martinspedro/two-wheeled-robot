/* 
 * File:   timer2.h
 * Author: martinspedro
 *
 * Created on May 5, 2018, 7:58 PM
 */

#include <xc.h>

#ifndef TIMER2_H
#define	TIMER2_H

#define ENABLE_TIMER_2  {T2CONbits.ON = 1;}
#define DISABLE_TIMER_2 {T2CONbits.ON = 0;}


void config_Timer2(void);

#endif	/* TIMER2_H */

