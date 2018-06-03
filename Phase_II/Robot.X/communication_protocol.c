/** 
 * \file   communication_protocol.h
 * \brief  Communication Protocol Module Header file
 * \pre    Uses UART1
 * 
 * \author Pedro Martins
 * \date   Created on May 29, 2018, 8:55 AM
 */

#include "../UART.X/uart1.h"
#include "communication_protocol.h"

void manage_initial_handshake()
{
    unsigned char id;
    while(1)
    {   
        // Wait until the receiver gets data
        while( get_char(&id) == UART_ERROR );
        
        //If a correct handshake is issued, move on. Else retry
        if( id == ID_HANDSHAKE_REQUEST ){
            break;
        } else {
            continue;
        }
    }
    
    // Send ACK after receiving Correct Initialization ID
    put_char(ID_HANDSHAKE_ACK); 
}   
