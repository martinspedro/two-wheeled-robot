/**
 * \file   main.c
 * \brief  Interrupt device driver main test file
 * 
 * \author Pedro Martins
 * \date   Created on May 1, 2018, 11:05 AM
 */

#include "../DEVCFGx_config_bits.h"
#include "../global.h"
#include "../interrupts.h"
#include "encoder.h"

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

void main(void) {
    TRISAbits.TRISA3 = 0;
    PORTAbits.RA3 = 1;
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB5 = 0;
    TRISBbits.TRISB6 = 0;
    
    configure_global_interrupts();
    configure_external_interrupts();
    
    Enable_Global_Interrupts();
    ENABLE_EXT_INT1;
    ENABLE_EXT_INT2;
    ENABLE_EXT_INT3;
    ENABLE_EXT_INT4;
    
    while(1);
}

