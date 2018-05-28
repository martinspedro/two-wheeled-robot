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
#include "timer3.h"

void delay(void){
    int i = 0;
    for( i = 0 ; i < 320000; i++)
    {
        Nop();
    }
}


void main(void) 
{
    adc_peripheral_init();
    init_ADC_ch(0);
    init_ADC_ch(1);
    config_input_scan(0);
    config_input_scan(1);
    
    ENABLE_INPUT_SCANNING;
    config_UART1(115200, 8, 'N', 1);
    config_Timer3();
    configure_global_interrupts();
    
    TRISDbits.TRISD4 = 0;
    TRISDbits.TRISD5 = 0;
    LATDbits.LATD4 = 0;
    LATDbits.LATD5 = 0;
    
    TRISAbits.TRISA3 = 0;
    LATAbits.LATA3 = 1;
    
    
    //
    //ENABLE_ADC;
   // ENABLE_TIMER_3;
    
    #ifdef MANUAL_MODE
        uint16_t analog_value;
        uint8_t num;
    #elif AUTO_SAMPLING_MODE
        ENABLE_ADC_INTERRUPTS;
        
        ENABLE_UART1_ERROR_DETECTION_INT;
        ENABLE_UART1_TX_INT;
        ENABLE_UART1_RX_INT;
        
        Enable_Global_Interrupts();
        
        AD1CON1bits.ASAM = 1;
    #elif CLOCKED_MODE
        ;
        
        ENABLE_UART1_ERROR_DETECTION_INT;
        ENABLE_UART1_TX_INT;
        ENABLE_UART1_RX_INT;
    #endif

    ENABLE_UART1_PHERIPHERAL;
    ENABLE_TIMER3_INTERRUPTS;
    Enable_Global_Interrupts();
    
    
    put_string("Initialization Completed!\n\n");
    
    
    AD1CON1bits.ASAM = 1;
    //ENABLE_ADC_INTERRUPTS;
    
    ENABLE_ADC;
    ENABLE_TIMER_3;
    //AD1CON1bits.SAMP = 1;
    //delay();
    //AD1CON1bits.SAMP = 0;
    
    
    
    
    //AD1CON1bits.ASAM = 1;		// start conversion
    
    
    while(1){
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
}

