/* 
 * File:   main.c
 * Author: Andr� Gradim
 *
 * Created on March 26, 2018, 10:32 AM
 */

#include "../DEVCFGx_config_bits.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../interrupts.h"
#include "../UART.X/uart1.h"
#include "i2c2.h"


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

    put_string("Number of devices connected: ");
    uint8_t array[254];
    uint8_t count = i2c_ping(array);
    //uint8_t count = 0;
    //array[0] = 0x29;
    //array[1] = 0x67;
    
    put_string("Number of devices connected: ");
    put_uint8(count);
    put_char('\n');
    //put_char(((*array>>4) & 0x0F) + '0');
    //       put_char((*array & 0x0F) + '0');
    //put_char('\n');
    
    if(count > 0){
        put_string("List of addresses: \n");
        uint8_t index = 0;
        for(index = 0; index < count; index++){
            put_uint8(index);
            put_string(" -> 0x");
            put_char(((array[index]>>4) & 0x0F) + '0');
            put_char((array[index] & 0x0F) + '0');
            put_char('\n');
        }
    }else{
        put_string("No device connected to the I2C bus\n");
    }
    
    //uint8_t temp1=0;
    char aux;
    while(get_char(&aux) == 1 );
    
    if(count > 0){
        clearI2CBuffer();
        uint8_t temp1 = 0;

        if(readByte(array[0],0x75,&temp1)){
            put_string("ERROR: read problem");
        }

        put_string("Value: ");
        put_uint16(temp1);
        put_char('\t');
        put_char((temp1>>4 < 9)?(((temp1>>4) & 0x0F) + '0'):((temp1>>4) & 0x0F) + 'A'-10);
        put_char((temp1 & 0x0F) + '0');
        put_char('\n');
    }
    
   
        
    while(1){
        
        
    }

    return (EXIT_SUCCESS);
}



