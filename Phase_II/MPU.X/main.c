/* 
 * File:   main.c
 * Author: André Gradim
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
    
    put_string("MPU init:\n");
    init_MPU();
    put_string("MPU init done!\n");
    
    
    //MPU6050_data mpu6050;
    uint16_t a1,a2,a3;
    uint16_t g1,g2,g3;
    uint16_t temperature;
    
    //Change led pin accordingly
    //TRISBbits.TRISB3 = 0;    
    int attempt = 0;
    uint8_t temp;
    while(1){
        //readBytes(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_INT_STATUS ,1, &temp);
        //if(temp & 0x01){
            //LATBbits.LATB3 = 1;
            //put_uint8(attempt);
            //put_char('\n');
            attempt++;
            //readMPU(mpu6050);
            read_data(&a1,&a2,&a3,&g1,&g2,&g3,&temperature);
            //put_string("A: ");
            put_uint16(a1);
            put_char(' ');
            put_uint16(a2);
            put_char(' ');
            put_uint16(a3);
            //put_char(' ');

            //put_string("G: ");
            //put_uint16(g1);
            //put_char(' ');
            //put_uint16(g2);
            //put_char(' ');
            //put_uint16(g3);
            //put_char(' ');

            //put_string("T: ");
            //put_uint16(temperature);
            put_char('\n');

            //LATBbits.LATB3 = 0;
            //delay a few milisecconds before new measurements
            int temp = 0;
            while( temp < 7150){
                temp = temp + 1;
            }

       // }
    }

    return (EXIT_SUCCESS);
}

