/* 
 * File:   main.c
 * Author: Andr� Gradim
 *
 * Created on May 7, 2018, 11:10 AM
 */


#include "header_pragma.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "uart1.h"
#include "i2c2.h"

//void initI2C2();

/*
 * 
 */
int main(int argc, char** argv) {
    
    //configureUART1(115200,40000000);
    config_UART1(115200, 8, 'N', 1);
    enable_UART1();
    
    
    openI2C2();
    send_char('H');
    
    int i;
    int iDistance;
    int model, revision;
    uint8_t dev_add = 0x29;
	// For Raspberry Pi's, the I2C channel is usually 1
	// For other boards (e.g. OrangePi) it's 0
	i = tofInit(dev_add, 1); // set long range mode (up to 2m)
    
	if (i != 1)
	{
        send_char('F');
		return -1; // problem - quit
	}
    send_char('d');
    
	i = tofGetModel(dev_add, &model, &revision);
    send_char('r');
    print_uint16((uint16_t) model);
    
    print_uint16((uint16_t) revision);
	//printf("Model ID - %d\n", model);
	//printf("Revision ID - %d\n", revision);
    int x;
    int temp = 0;
    
    for (i=0; i<1200; i++) // read values 20 times a second for 1 minute
	{
		iDistance = tofReadDistance(dev_add);
		if (iDistance < 4096) // valid range?
			print_uint16((uint16_t) iDistance);
        send_char('\n');
		for(x =0 ; x <10; x++){
            temp = 0;
            while( temp < 7150){
                temp = temp + 1;
            }
        }
	}


    
    while(1){   
        
        



    //     putChar('R');
    //     char in = getChar();
        
        
    //     /////////////////////////////////
    //     /*putChar('w'); 
        
    //     waitI2C2();
    //     startI2C2();
        
    //     uint8_t dev_address = 0x68;
    //     uint8_t buf_size = 2;
    //     uint8_t transfer_buf[] = {0x71, 0x01};
                
    //     masterSend(dev_address, transfer_buf, buf_size);
        
    //     waitI2C2();
    //     stopI2C2();
        
    //     */
        
    //     ///////////////////////////////
    //     putChar('r');
        
    //     waitI2C2();
    //     startI2C2();
        
    //     uint8_t dev_address = 0x68;
    //     uint8_t buf_size = 1;
    //     uint8_t transfer_buf2[] = {0x19};
                
    //     masterSend(dev_address, transfer_buf2, buf_size);
        
    //     waitI2C2();
    //     stopI2C2();
        
    //     ///
        
    //     waitI2C2();
    //     startI2C2();
    //     dev_address = 0x68;
        
    //     masterSend(dev_address, NULL, 0);
        
        
    //     uint8_t bytes_to_read = 1;
    //     uint8_t buffer[bytes_to_read];
        
    //     masterReceive( buffer, bytes_to_read);
        
    //     waitI2C2();
    //     stopI2C2();
        
    //     /////////////////////////////////
    //     putChar('w'); 
        
    //     waitI2C2();
    //     startI2C2();
        
    //     dev_address = 0x68;
    //     buf_size = 2;
    //     uint8_t transfer_buf[] = {0x19, 0x22};
                
    //     masterSend(dev_address, transfer_buf, buf_size);
        
    //     waitI2C2();
    //     stopI2C2();
        
       
        
        
        
        
        
    }

    return (EXIT_SUCCESS);
}



