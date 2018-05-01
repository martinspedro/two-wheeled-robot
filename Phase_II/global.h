/** 
 * \file global.h
 * \brief Global configurations for E4 project
 * 
 * \author Pedro Martins
 * \date Created on April 3, 2018, 10:41 AM
 */


#ifndef GLOBAL_H
#define	GLOBAL_H


/*******************************************************************************
 *                        OSCILLATOR
 ******************************************************************************/
#define SYSCLK 80000000L    //!< System Clock Frequency (Hz))
#define PBCLK  SYSCLK/2L    //!< Pheripheral System Clock Frequency (Hz))
    

/*******************************************************************************
 *                        ELECTRICAL
 ******************************************************************************/
#define VDD 33              //!< PIC Input Voltage
    

#endif	/* GLOBAL_H */

