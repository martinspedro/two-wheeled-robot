/* 
 * File:   communication_protocol.h
 * Author: martinspedro
 *
 * Created on May 29, 2018, 8:55 AM
 */

#include "../UART.X/uart1.h"
#include "communication_protocol.h"

void manage_initial_handshake()
{
    unsigned char id;
    while( 1 ){
        
        //Wait for the receiver to get data
        while( get_char(&id) == UART_ERROR );
        
        //If the correct byte is received, move on
        if( id == ID_HANDSHAKE_REQUEST ){
            break;
        } else {
            continue;
        }
    }
    
    //After the correct ID has been received, send the confirmation
    put_char(ID_LOCOMOTION_INIT_OK); 
}   
