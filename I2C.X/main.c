/* 
 * File:   main.c
 * Author: André Gradim
 *
 * Created on March 26, 2018, 10:32 AM
 */

#include "header_pragma.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "uart.h"
#include "i2c1.h"

//void initI2C2();

/*
 * 
 */
int main(int argc, char** argv) {
    
    configureUART1(115200,40000000);
    openI2C2();
    
    
    
    while(1){   
        putChar('R');
        char in = getChar();
        
        
        /////////////////////////////////
        /*putChar('w'); 
        
        waitI2C2();
        startI2C2();
        
        uint8_t dev_address = 0x68;
        uint8_t buf_size = 2;
        uint8_t transfer_buf[] = {0x71, 0x01};
                
        masterSend(dev_address, transfer_buf, buf_size);
        
        waitI2C2();
        stopI2C2();
        
        */
        
        ///////////////////////////////
        putChar('r');
        
        waitI2C2();
        startI2C2();
        
        uint8_t dev_address = 0x68;
        uint8_t buf_size = 1;
        uint8_t transfer_buf2[] = {0x72};
                
        masterSend(dev_address, transfer_buf2, buf_size);
        
        waitI2C2();
        stopI2C2();
        
        ///
        
        waitI2C2();
        startI2C2();
        dev_address = 0x68;
        
        masterSend(dev_address, NULL, 0);
        
        
        uint8_t bytes_to_read = 4;
        uint8_t buffer[bytes_to_read];
        
        masterReceive( buffer, bytes_to_read);
        
        waitI2C2();
        stopI2C2();
        
        
        
        
        
        
        
    }

    return (EXIT_SUCCESS);
}



