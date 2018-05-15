/* 
 * File:   main.c
 * Author: Andr� Gradim
 *
 * Created on May 4, 2018, 7:14 PM
 */

#include "../DEVCFGx_config_bits.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <proc/p32mx795f512l.h>
#include "../UART.X/uart1.h"
#include "../I2C.X/i2c2.h"
#include "mpu6050.h"
#include "../interrupts.h"

#define TEST_ACC
//#define TEST_GYRO
//#define TEST_TEMP

//#define USE_TEXT

//void initI2C2();

/*
 * 
 */
int main(int argc, char** argv) {
    
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
    
    put_string("Initializing MPU:\n");
    init_MPU();
    put_string("MPU init done!\n");
    
    
    //MPU6050_data mpu6050;
    uint16_t a1,a2,a3;
    uint16_t g1,g2,g3;
    uint16_t temperature;
    
    #ifndef TEST_ACC
    #ifndef TEST_GYRO
    #ifndef TEST_TEMP
    put_string("ERROR: no test defined!");
    return 0;
    #endif
    #endif
    #endif


    while(1){
        read_data(&a1,&a2,&a3,&g1,&g2,&g3,&temperature);
        #ifdef TEST_ACC
        #ifdef USE_TEXT
        put_string("A: ");
        #endif

        put_uint16(a1);
        put_char(' ');
        put_uint16(a2);
        put_char(' ');
        put_uint16(a3);
        put_char(' ');
        #endif


        #ifdef TEST_GYRO
        #ifdef USE_TEXT
        put_string("G: ");
        #endif
        put_uint16(g1);
        put_char(' ');
        put_uint16(g2);
        put_char(' ');
        put_uint16(g3);
        put_char(' ');
        #endif


        #ifdef TEST_TEMP
        #ifdef USE_TEXT
        put_string("T: ");
        #endif
        put_uint16(temperature);
        #endif

        put_char('\n');

        
        //delay a few (5ms) milisecconds before new measurements
        int temp = 0;
        while( temp < 7150){
            temp = temp + 1;
        }
    }

    return (EXIT_SUCCESS);
}

