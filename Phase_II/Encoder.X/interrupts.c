/** 
 * \file interrupts.c
 * \brief Interrupt configuration C file
 * 
 * \author Pedro Martins
 * \date Created on April 28, 2018, 5:36 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/attribs.h> 

#include "interrupts.h"
#include "../global.h"
#include "../UART.X/uart1.h"

/** \brief Single Vector Requested Priority Level
 * Should only be used if single vector mode interruptions are enable
 */
#define SV_REQUESTED_PRIORITY_LVL INTSTATbits.SRIPL     

/** \brief Interrupt Vector Bits presented to the CPU
 * Should only be used if multi vector mode interruptions are enable
 */
#define INTERRUPT_VECTOR_BITS     INTSTATbits.VEC


#define RESET_IF_EXT_INT0 {IFS0bits.INT0IF = 0;}    //!< Reset Interrupt Flag for External Interrupt Pin 0 >
#define RESET_IF_EXT_INT1 {IFS0bits.INT1IF = 0;}    //!< Reset Interrupt Flag for External Interrupt Pin 1 >


#define EXT_INT_RISING_EDGE  1 //!< External Interrupt Edge Polarity sensible to Rising Edge Detection  >
#define EXT_INT_FALLING_EDGE 0 //!< External Interrupt Edge Polarity sensible to Falling Edge Detection >

#define set_isr_state(state) {__builtin_set_isr_state(state);}
#define get_isr_state(state) {__builtin_get_isr_state(state);}




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


void configure_external_interrupts(void)
{
    // Reset Interrupt Flags
    RESET_IF_EXT_INT0;
    RESET_IF_EXT_INT1;
    
    // Configure External Interrupts Edge Detection as Rising Edge
    INTCONbits.INT0EP = EXT_INT_RISING_EDGE;
    INTCONbits.INT1EP = EXT_INT_RISING_EDGE;
    
    // Set Priority and sub-priority levels for INT0 & INT1
    IPC0bits.INT0IP = EXT_INT0_IPL  & 0x07;
    IPC0bits.INT0IS = EXT_INT0_ISPL & 0x03;
    
    IPC1bits.INT1IP = EXT_INT1_IPL  & 0x07;
    IPC1bits.INT1IS = EXT_INT1_ISPL & 0x03;
}


/** \brief ISR for External Interrupt Pin 0
 * 
 * \pre    Global and External Interrupts must be configured and enabled
 * \param  None.
 * \return None.
 * 
 * Interruption Service Routine for External Interrupt Pin 0
 * The interruption source priority is 6 and the compiler must write software to
 * perform the context switching
 * 
 * \author Pedro Martins
 */
void __ISR(_EXTERNAL_0_VECTOR, IPL6SOFT) _INT0Interrupt(void)
{
    static volatile uint8_t aux = 0;
    
    DISABLE_EXT_INT0
    INTCONINV = 0x0001;     // Invert polarity
    
    PORTAbits.RA3 = PORTDbits.RD0;
    print_uint8((aux++) & 0x0FF);
    send_char(' ');
    print_uint8(INTCONbits.INT0EP & 0x0FF);
    send_char('\n');
        
    RESET_IF_EXT_INT0 
    ENABLE_EXT_INT0   
}