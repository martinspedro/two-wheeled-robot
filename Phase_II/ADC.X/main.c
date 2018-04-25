/* 
 * File:   main.c
 * Author: martinspedro
 *
 * Created on April 9, 2018, 4:25 PM
 */

#include "../devcfgx_config_bits.h"
#include "../global.h"
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "../UART.X/uart1.h"

void delay(void){
    int i = 0;
    for( i = 0 ; i < 65000; i++)
    {
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
    uint16_t analog_value;
    TRISAbits.TRISA3 = 0;
    TRISFbits.TRISF2 = 0;
    LATAbits.LATA3 = 1;
    LATFbits.LATF2 = 1;
    
    config_UART1(115200, 8, 'N', 1);
    enable_UART1();
    
    send_char('1');
    
    adc_init();
    init_ADC_ch(0);
    enable_ADC();
    
    while(1){
        PORTAbits.RA3 = 1;
        PORTFbits.RF2 = 1;
        
        
        start_conversion();
        delay();
        
        end_conversion();
        send_char('S');
        while(!conversion_finnished());
        send_char('D');
        send_char(' ');
        PORTAbits.RA3 = 0;
        
        analog_value = get_analog_value();
        print_uint8(bin_2_volt(analog_value));
        
        send_char('\n');
        PORTFbits.RF2 = 0;
    }
    return (EXIT_SUCCESS);
}

