/** 
 * \file main.c
 * \brief Interrupt device driver main test file
 * 
 * \author Pedro Martins
 * \date Created on May 1, 2018, 11:05 AM
 */

#include "../devcfgx_config_bits.h"
#include "../global.h"
#include "interrupts.h"
#include "encoder.h"
#include "../UART.X/uart1.h"


void main(void) {
    TRISAbits.TRISA3 = 0;
    PORTAbits.RA3 = 0;
    TRISDbits.TRISD0 = 1;
    
    config_UART1(115200, 8, 'N', 1);
    enable_UART1();
    send_char('S');
    configure_global_interrupts();
    configure_external_interrupts();
    
    Enable_Global_Interrupts();
    //ENABLE_EXT_INT1;
    ENABLE_EXT_INT2;
    
    while(1);
}

