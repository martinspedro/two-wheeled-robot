/** 
 * \file   main.c
 * \brief  UART1 Device Driver Test Main C File
 * 
 * \author Pedro Martins
 * \date   Created on March 13, 2018, 10:56 AM
 */

#include "../DEVCFGx_config_bits.h"

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#include "../global.h"
#include "uart1.h"

#define DEBUG_MODE 1
#if DEBUG_MODE == 0
    #define DEBUG_NUM
#elif DEBUG_MODE == 1
    #define DEBUG_STRINGS
#elif DEBUG_MODE == 2
    #define DEBUG_ECHO
#endif

void main(void){
    
    unsigned char c;
    uint8_t num;
    config_UART1(115200, 8, 'N', 1);
    ENABLE_UART1_PHERIPHERAL;
    
    
    // Set RA3 as outpout
    TRISAbits.TRISA3 = 0;
    

    while(1)
    {
        PORTAbits.RA3 = 0;
        send_char('a');
        
        
        #ifdef DEBUG_ECHO
        c = read_char();
        send_char(c);
        #endif

        #ifdef DEBUG_STRINGS
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
        else
            send_char('E');
        #endif     
        
        #ifdef DEBUG_NUM
        num = read_uint8();
        print_uint8(num);
        #endif

        send_char('\n');
        PORTAbits.RA3 = 1;
        
    }
}

