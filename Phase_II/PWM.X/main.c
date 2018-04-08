/* 
 * File:   main.c
 * Author: martinspedro
 *
 * Created on April 2, 2018, 7:50 PM
 */
#include "../devcfgx_config_bits.h"
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "../global.h"
#include "pwm.h"
/*
 * 
 */
int main(int argc, char** argv) {
    // Set RA3 as outpout
    TRISAbits.TRISA3 = 0;
    
    PWM_init();
    PWM_enable();
    set_duty_cycle(50);
    PORTAbits.RA3 = 1;
    while(1);
    return (EXIT_SUCCESS);
}

