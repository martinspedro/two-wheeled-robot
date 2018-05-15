/* 
 * File:   main.c
 * Author: martinspedro
 *
 * Created on April 9, 2018, 4:25 PM
 */

#include "../DEVCFGx_config_bits.h"
#include "../global.h"
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "../UART.X/uart1.h"
#include "../interrupts.h"
#include "adc.h"
#include "../interrupts.h"

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


int main(int argc, char** argv) {
    uint16_t analog_value;
    
    TRISDbits.TRISD4 = 0;
    TRISDbits.TRISD5 = 0;
    LATDbits.LATD4 = 0;
    LATDbits.LATD5 = 0;
    
    TRISAbits.TRISA3 = 0;
    LATAbits.LATA3 = 1;
    
#ifdef MANUAL_MODE
        uint8_t num;
    config_UART1(115200, 8, 'N', 1);
    ENABLE_UART1_PHERIPHERAL;
#endif
    
    adc_peripheral_init();
    init_ADC_ch(0);
    config_input_scan(0);
    
    
    #ifdef AUTO_SAMPLING_MODE
        configure_global_interrupts();
        ENABLE_ADC_INTERRUPTS;
        Enable_Global_Interrupts();
    #endif
    
    ENABLE_ADC;
    
    while(1){
        //LATBbits.LATB5 = IFS1bits.AD1IF;
        //IFS1bits.AD1IF = 0;
        
        //LATBbits.LATB5 = HAS_CONVERSION_FINISHED;
        
        #ifdef MANUAL_MODE
            PORTAbits.RA3 = 1;

            START_SAMPLING;
            delay();

            START_CONVERSION;
            put_char('S');
            while(!HAS_CONVERSION_FINISHED);
            
            put_char('C');
            put_char(' ');
            PORTAbits.RA3 = 0;

            analog_value = get_analog_value();
            put_uint8(bin_2_volt(analog_value));

            put_char('\n');
        #endif
    }
    return (EXIT_SUCCESS);
}

