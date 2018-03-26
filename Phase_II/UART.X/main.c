/* 
 * File:   main.c
 * Author: martinspedro
 *
 * Created on March 13, 2018, 10:56 AM
 */

#include "devcfgx_config_bits.h"


#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "uart1.h"


#define SYSCLK  80000000L // System clock frequency, in Hz
#define PBCLOCK 40000000L // Peripheral Bus Clock frequency, in Hz



int main(int argc, char** argv){
    
    unsigned char c;
    
    config_UART1(9600, 8, 'N', 1);
    enable_UART1();
    
    
    // Set RA3 as outpout
    TRISAbits.TRISA3 = 0;
    

    while(1)
    {
        PORTAbits.RA3 = 0;
        PORTAbits.RA3 = send_char('A');
        
        c = read_char();
        PORTAbits.RA3 = 1;
        send_char(c);
    }
    
    return (EXIT_SUCCESS);  
}

