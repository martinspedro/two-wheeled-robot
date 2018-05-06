/** 
 * \file   DRV8833.h
 * \brief  DRV8833 module device driver Header file
 * 
 * \author Pedro Martins
 * \date   Created on May 5, 2018, 6:11 PM
 */
#ifndef MOTORS_H
#define	MOTORS_H

#define nSLEEP LATDbits.LATD5
#define nFAULT PORTDbits.RD6

#define ENABLE_DRV8833  {nSLEEP = 1;}
#define DISABLE_DRV8833 {nSLEEP = 0;}

#define M1_ISEN_ADC_CH 13
#define M2_ISEN_ADC_CH 14

#define MIN_DUTY 0
#define MAX_DUTY 100

#endif	/* MOTORS_H */

