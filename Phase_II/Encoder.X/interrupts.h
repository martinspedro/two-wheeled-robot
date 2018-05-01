/**
 * \file interrupts.h
 * \brief Interrupt configuration Header File
 * \author Pedro Martins
 * \date Created on May 1, 2018, 10:22 AM
 */


#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

#define ENABLE_EXT_INT0  {IEC0bits.INT0IE = 1;}
#define DISABLE_EXT_INT0 {IEC0bits.INT0IE = 0;}
#define ENABLE_EXT_INT1  {IEC0bits.INT1IE = 1;}
#define DISABLE_EXT_INT1 {IEC0bits.INT1IE = 0;}

#define EXT_INT0_IPL 6
#define EXT_INT1_IPL 6

#define EXT_INT0_ISPL 0
#define EXT_INT1_ISPL 0

#define Disable_Global_Interrupts()  asm volatile("di")
#define Enable_Global_Interrupts()   asm volatile("ei")

//#define Disable_Pheripheral_Interrupts() __builtin_
//#define Enable_Pheripheral_Interrupts()

// Might be needed
#define set_isr_state(state) {__builtin_set_isr_state(state);}
#define get_isr_state(state) {__builtin_get_isr_state(state);}

/********************************************************************
* Function: 	config_interrupts()
* Precondition: None.
* Input: 		None.
* Output:		None.
* Side Effects:	Configures.
* Overview:     Gets the data from UART RX FIFO.
* Note:		 	None.
********************************************************************/
void config_interrupts(void);

#endif	/* INTERRUPTS_H */

