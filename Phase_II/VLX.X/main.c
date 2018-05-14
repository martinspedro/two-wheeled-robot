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
#include "../interrupts.h"

//to test address changes uncomment
//#define TEST_NEW_ADDRESS

#define DEFAULT_ADDRESS 0x29

#define NEW_ADDRESS 0x30


#ifndef TEST_NEW_ADDRESS
#define ADDRESS1 DEFAULT_ADDRESS
#endif

#ifdef TEST_NEW_ADDRESS
#define ADDRESS1 NEW_ADDRESS
#endif



int main(int argc, char** argv){
    
    config_UART1(115200, 8, 'N', 1);

    ENABLE_UART1_PHERIPHERAL;
    flush_RX_buffer();
    flush_TX_buffer();
    ENABLE_UART1_ERROR_DETECTION_INT;
    ENABLE_UART1_TX_INT;
    ENABLE_UART1_RX_INT;
    
    configure_global_interrupts();
    Enable_Global_Interrupts();
    
    openI2C2();
    
    int i;
    int iDistance;
    int model, revision;
	
    put_string("Initializing VLX");
    #ifdef TEST_NEW_ADDRESS
    setAddress(DEFAULT_ADDRESS,NEW_ADDRESS);
    #endif


	i = initSensor(ADDRESS1, 1); // set long range mode (up to 2m)
    
	if (i !=1 ){
        put_string("ERROR in init: ");
        put_uint8(i);
		return 1; // problem - quit
	}
    put_string("\nVLX init done!\n");
    
	i = tofGetModel(ADDRESS1, &model, &revision);
    
	put_string("Model ID: ");
    put_uint16((uint16_t) model);
    put_char('\n');
    
    put_string("Revision ID: ");
    put_uint16((uint16_t) revision);
	put_char('\n');
    
    char p;
    get_char(&p);
    
    int x;
    int temp = 0;
    
    while(1){ 
        
        iDistance = tofReadDistance(ADDRESS1);
		if (iDistance < 4096){ // valid range?
			put_uint16((uint16_t) iDistance);
            put_char('\n');
        }
            
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

