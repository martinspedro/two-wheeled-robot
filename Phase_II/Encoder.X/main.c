/** 
 * \file main.c
 * \brief Interrupt device driver main test file
 * 
 * \author Pedro Martins
 * \date Created on May 1, 2018, 11:05 AM
 */

#include "../devcfgx_config_bits.h"
#include "../global.h"
#include "../interrupts.h"
#include "../UART.X/uart1.h"
#include "encoder.h"

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

void main(void) {
    TRISAbits.TRISA3 = 0;
    PORTAbits.RA3 = 1;
    TRISBbits.TRISB4 = 0;
    
    config_UART1(115200, 8, 'N', 1);
    enable_UART1();
    send_char('S');
    
    configure_global_interrupts();
    configure_external_interrupts();
    
    Enable_Global_Interrupts();
    ENABLE_EXT_INT1;
    ENABLE_EXT_INT2;
    
    while(1)
    {
        
        if (print_flag == 1)
        {
            print_uint8(CS_left);
            send_char('\n');
            /*
            if(invalid_encoder_transition == ENCODER_ERROR)
            {
                send_char('E');
                invalid_encoder_transition = ENCODER_SUCCESS;
            }
            
            print_uint16(pulse_count_L);
            send_char('\n');
            */
            print_flag = 0;
        }
        
    }
}

