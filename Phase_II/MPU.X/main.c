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

//void initI2C2();

/*
 * 
 */
int main(int argc, char** argv) {
    
    config_UART1(115200, 8, 'N', 1);
    openI2C2();
    
    init_MPU();
    static MPU6050_data mpu6050;
    
    
    //Change led pin accordingly
    TRISBbits.TRISB3 = 0;    
    
    while(1){
        
        LATBbits.LATB3 = 1;
        
        readMPU(mpu6050);
        put_string("A: ");
        put_uint16(mpu6050.Accel.X);
        put_char(' ');
        
        put_uint16(mpu6050.Accel.Y);
        put_char(' ');
        
        put_uint16(mpu6050.Accel.Z);
        put_char(' ');
        
        put_string("G: ");
        put_uint16(mpu6050.Gyro.X);
        put_char(' ');
        
        put_uint16(mpu6050.Gyro.Y);
        put_char(' ');
        
        put_uint16(mpu6050.Gyro.Z);
        put_char('\n');
        
        put_string("T: ");
        put_uint16(mpu6050.Temperature);
        put_char('\n');
        
        LATBbits.LATB3 = 0;
        //delay a few milisecconds before new measurements
        
        
        
    }

    return (EXIT_SUCCESS);
}

