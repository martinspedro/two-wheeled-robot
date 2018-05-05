/** 
 * \file interrupts.c
 * \brief Global Interrupt configuration C file
 * 
 * \author Pedro Martins
 * \date Created on April 28, 2018, 5:36 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#include "interrupts.h"


/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
/** \brief Single Vector Requested Priority Level
 * Should only be used if single vector mode interruptions are enable
 */
#define SV_REQUESTED_PRIORITY_LVL INTSTATbits.SRIPL     

/** \brief Interrupt Vector Bits presented to the CPU
 * Should only be used if multi vector mode interruptions are enable
 */
#define INTERRUPT_VECTOR_BITS     INTSTATbits.VEC


#define set_isr_state(state) {__builtin_set_isr_state(state);}
#define get_isr_state(state) {__builtin_get_isr_state(state);}



/*******************************************************************************
 *                         CLASS METHODS
 ******************************************************************************/
void configure_global_interrupts(void)
{
    Disable_Global_Interrupts();
    
    /* Deactivate Single vector shadow register
     * 
     * Single Vector Shadow Register Set bit (1)
     *   1 = Single vector is presented with a shadow register set
     *   0 = Single vector is not presented with a shadow register set
     */
    INTCONbits.SS0 = 0;
    
    /* Select Multi vector configuration mode
     * 
     * Multi Vector Configuration bit
     *   1 = Interrupt Controller configured for multi vectored mode
     *   0 = Interrupt Controller configured for single vectored mode
     */
    INTCONbits.MVEC = 1;
    
    /* Disable Interrupt Proximity Timer
     * 
     * Interrupt Proximity Timer Control bits
     *   111 = Interrupts of group priority 7 or lower start the Interrupt Proximity timer
     *   110 = Interrupts of group priority 6 or lower start the Interrupt Proximity timer
     *   101 = Interrupts of group priority 5 or lower start the Interrupt Proximity timer
     *   100 = Interrupts of group priority 4 or lower start the Interrupt Proximity timer
     *   011 = Interrupts of group priority 3 or lower start the Interrupt Proximity timer
     *   010 = Interrupts of group priority 2 or lower start the Interrupt Proximity timer
     *   001 = Interrupts of group priority 1 start the Interrupt Proximity timer
     *   000 = Disables Interrupt Proximity timer
     */
    INTCONbits.TPC = 0b000;
}


