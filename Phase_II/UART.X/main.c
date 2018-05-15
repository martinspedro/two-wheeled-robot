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
#include "../interrupts.h"
#include "uart1.h"

#define DEBUG_MODE 3
#if DEBUG_MODE == 0
    #define DEBUG_NUM
#elif DEBUG_MODE == 1
    #define DEBUG_STRINGS
#elif DEBUG_MODE == 2
    #define DEBUG_ECHO
#elif DEBUG_MODE == 3
    #define DEBUG_INT_CIRCULAR_BUF
#endif

void main(void)
{
    unsigned char c;
    uint8_t num_8bit;
    uint16_t num_16bit;
    
    /* Configuration */
    TRISAbits.TRISA3 = 0;       // Set RA3 as output
    LATAbits.LATA3 = 0;
    
    config_UART1(115200, 8, 'N', 1);
    ENABLE_UART1_PHERIPHERAL;
    
    #ifdef USE_INTERRUPTS
        ENABLE_UART1_ERROR_DETECTION_INT;
        ENABLE_UART1_TX_INT;
        ENABLE_UART1_RX_INT;
        
        configure_global_interrupts();
        Enable_Global_Interrupts();
    #endif

        
    /* TEST */
    put_string("PIC32 UART Device-Driver\n\n");
    
    put_string("Test strings will be sent...\n");
    put_string("Upper case Letters: ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
    put_string("Lower case Letters:abcdefghijklmnopqrstuvwxyz\n");
    put_string("Numbers: 0123456789\n");
    put_string("Commonly used symbols: |!\"#$%&/()=?»«'}][{£@\');\n");
    put_string("\nString Test completed!\n");
    
    
    put_string("\nThe character 'A' will be sent... ");
    put_char('A');
    put_string("\nThe character '1' will be sent... ");
    put_char('1');
    
    put_string("\nInsert a char: ");
    #ifdef USE_INTERRUPTS
    while(get_char(&c) == UART_ERROR);
    put_string("\nCharacter successfully received! The received character was: ");
    #else
    if(get_char(&c) == UART_ERROR) {
        put_string("\nAn error occurred! The received character was: ");
    } else {
        put_string("\nCharacter successfully received! The received character was: ");
    }
    #endif
    put_char(c);
    put_string("\nCharacter test completed!\n");
    
    put_string("\nAn 8 bit unsigned integer ('3') will be sent... ");
    put_uint8(3);
    put_string("\nAn 8 bit unsigned integer ('16') will be sent... ");
    put_uint8(16);
    #ifndef USE_INTERRUPTS
    put_string("\nInsert a 8 bit unsigned integer: ");
    if(get_uint8(&num_8bit) == UART_ERROR) {
        put_string("\nAn error occurred! The received 8 bit unsigned integer was: ");
    } else {
        put_string("\nCharacter successfully received! The received 8 bit unsigned integer was: ");
    }
    put_uint8(num_8bit);
    #else
    put_char('\n');
    #endif
    put_string("\n8 bit unsigned integer test completed!\n");

    put_string("\nAn 16 bit unsigned integer ('1') will be sent... ");
    put_uint16(1);
    put_string("\nAn 16 bit unsigned integer ('33') will be sent... ");
    put_uint16(33);
    put_string("\nAn 16 bit unsigned integer ('425') will be sent... ");
    put_uint16(425);
    put_string("\nAn 16 bit unsigned integer ('2213') will be sent... ");
    put_uint16(2213);
    put_string("\nAn 16 bit unsigned integer ('65021') will be sent... ");
    put_uint16(65021);
    put_string("\n16 bit unsigned integer test completed!\n");
    
    put_string("\nPIC32 UART Device-Driver completed!\n\n");
    
 
    PORTAbits.RA3 = 1;
    
    while(1);
}

