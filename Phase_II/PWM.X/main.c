/** 
 * \file main.c
 * \brief PWMs main file 
 * 
 * \author Pedro Martins
 * \date Created on April 2, 2018, 7:50 PM
 */

#include "../DEVCFGx_config_bits.h"

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#include "../global.h"

#include "timer2.h"
#include "pwm1.h"
#include "pwm2.h"
#include "pwm3.h"
#include "pwm4.h"


void main(void) {
    TRISAbits.TRISA3 = 0;
    
    config_Timer2();
            
    output_compare_1_init();
    output_compare_2_init();
    output_compare_3_init();
    output_compare_4_init();
    
    set_PWM1_duty_cycle(1);
    set_PWM2_duty_cycle(50);
    set_PWM3_duty_cycle(60);
    set_PWM4_duty_cycle(100);
    
    ENABLE_TIMER_2;
            
    ENABLE_OUTPUT_COMPARE_PERIPHERAL_1;
    ENABLE_OUTPUT_COMPARE_PERIPHERAL_2;
    ENABLE_OUTPUT_COMPARE_PERIPHERAL_3;
    ENABLE_OUTPUT_COMPARE_PERIPHERAL_4;
    
    PORTAbits.RA3 = 1;
    
    while(1);
}

