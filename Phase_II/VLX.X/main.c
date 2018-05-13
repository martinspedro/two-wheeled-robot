/* 
 * File:   main.c
 * Author: Andr� Gradim
 *
 * Created on May 7, 2018, 11:10 AM
 */


#include "../DEVCFGx_config_bits.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../I2C.X/i2c2.h"
#include "../UART.X/uart1.h"
#include "tof.h"

//void initI2C2();

/*
 * 
 */
int main(int argc, char** argv) {
    
    config_UART1(115200, 8, 'N', 1);
    
    
    
    openI2C2();
    put_char('H');
    
    int i;
    int iDistance;
    int model, revision;
    uint8_t dev_add = 0x29;
	// For Raspberry Pi's, the I2C channel is usually 1
	// For other boards (e.g. OrangePi) it's 0
	i = tofInit(dev_add, 1); // set long range mode (up to 2m)
    
	if (i != 1)
	{
        put_char('F');
		return -1; // problem - quit
	}
    put_char('d');
    
	i = tofGetModel(dev_add, &model, &revision);
    put_char('r');
    
	put_string("Model ID: ");
    put_uint16((uint16_t) model);
    put_char('\n');
    
    put_string("Revision ID: ");
    put_uint16((uint16_t) revision);
	put_char('\n');
    
    int x;
    int temp = 0;
    
        
    while(1){ 
        
        iDistance = tofReadDistance(dev_add);
		if (iDistance < 4096) // valid range?
			put_uint16((uint16_t) iDistance);
            put_char('\n');
            
            //delay 50 ms
		for(x =0 ; x <10; x++){
            temp = 0;
            while( temp < 7150){
                temp = temp + 1;
            }
        }
   
        
    }

    return (EXIT_SUCCESS);
}



