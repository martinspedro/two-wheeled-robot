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




int main(int argc, char** argv){
    
    config_UART1(115200, 8, 'N', 1);

    ENABLE_UART1_PHERIPHERAL;
    flush_RX_buffer();
    flush_TX_buffer();
    ENABLE_UART1_ERROR_DETECTION_INT;
    ENABLE_UART1_TX_INT;
    ENABLE_UART1_RX_INT;
    openI2C2();
    configure_global_interrupts();
    Enable_Global_Interrupts();
        
    /*
    int i;
    int iDistance;
    int model, revision;
	
    uint8_t values[10];
    uint8_t count = i2c_ping(values);
    //uint8_t count = 0;
    uint8_t index = 0;
    
    put_string("Addresses on the line (before): \n");
    for(index = 0; index < count; index++){
        put_uint8(index);
        put_string(" -> ");
        put_uint8(values[index]);
        put_char('\n');
    }
    
    
    put_string("Initializing VLX \n");
    #ifdef TEST_NEW_ADDRESS
    put_string("Changing address:\n ");
    setAddress(DEFAULT_ADDRESS,NEW_ADDRESS);
    #endif
    */
    
	/*int i = initSensor(0x30, 1); // set long range mode (up to 2m)
    
	if (i !=1 ){
        put_string("ERROR in init: ");
        put_uint8(i);
		return 1; // problem - quit
	}
    put_string("\nVLX init done!\n");
    
    
    
    uint8_t new_values[10];
    count = i2c_ping(new_values);
    
    index = 0;
    
    put_string("Addresses on the line (after): \n");
    for(index = 0; index < count; index++){
        put_uint8(index);
        put_string(" -> ");
        put_uint8(new_values[index]);
        put_char('\n');
    }
    
    while(1);*/
    /*
	i = tofGetModel(ADDRESS1, &model, &revision);
    
	put_string("Model ID: ");
    put_uint16((uint16_t) model);
    put_char('\n');
    
    put_string("Revision ID: ");
    put_uint16((uint16_t) revision);
	put_char('\n');*/
    /*
    char p;
    get_char(&p);
    
    int x;
    int temp = 0;
    uint16_t last = 0, last2 = 0;
    uint16_t val = 0;
    */
    put_string("Init all sensors\n");
    /*_TRISD8 = 0;
    _LATD8 = 0;
    setAddress()*/
    
    //initSensor(0x29,1);
    initAllSensors();
    put_string("Done!\n");
    uint16_t d_left, d_center, d_right;
            
    
    while(1){ 
        
        //d_center = tofReadDistance(0x30);
        //d_center = tofReadDistance(0x29);
        //d_center = tofReadDistance(0x34);
        tofReadDistanceAllSensors(&d_left, &d_center, & d_right);
        
        
        put_uint16(d_left);
        
        put_char('\t');
        put_uint16(d_center);
        
        put_char('\t');
        put_uint16(d_right);
        put_char('\n');
        
        
        /*iDistance = tofReadDistance(ADDRESS1);
		if (iDistance < 4096){ // valid range?
            val = (uint16_t) (iDistance + last+ last2)/3;
            
            val = (uint16_t) (iDistance + val)/2;
            
			put_uint16(iDistance);
            put_char('\n');
            last = (uint16_t) iDistance;
            last2 = last;
            //last = (uint16_t) iDistance;
        }*/
            
        //delay 50 ms
		/*for(x =0 ; x <5; x++){
            temp = 0;
            while( temp < 7150){
                temp = temp + 1;
            }
        }*/

    }
    return (EXIT_SUCCESS);
}

