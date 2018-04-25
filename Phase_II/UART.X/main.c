/* 
 * File:   main.c
 * Author: martinspedro
 *
 * Created on March 13, 2018, 10:56 AM
 */

#include "../devcfgx_config_bits.h"

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "../global.h"
#include "uart1.h"





int main(int argc, char** argv){
    
    unsigned char c;
    uint8_t num;
    config_UART1(115200, 8, 'N', 1);
    enable_UART1();
    
    
    // Set RA3 as outpout
    TRISAbits.TRISA3 = 0;
    

    while(1)
    {
        PORTAbits.RA3 = 0;
        send_char('a');
        c = read_char();
        if(c == '1')
            print_uint8(2);
        else if(c == '2')
            print_uint8(17);
        else if(c == '3')
            print_uint16(227);
        else if(c == '4')
            print_uint16(1234);
        else if(c == '5')
            print_uint16(54321);
        
        send_char('\n');
        num = read_uint8();
        print_uint8(num);
        
        PORTAbits.RA3 = 1;
        
    }
    
    return (EXIT_SUCCESS);  
}

