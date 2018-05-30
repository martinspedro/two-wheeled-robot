/* 
 * File:   main.c
 * Author: martinspedro
 *
 * Created on May 28, 2018, 11:41 PM
 */

#include "../DEVCFGx_config_bits.h"


#include <stdio.h>
#include <stdlib.h>
#include <xc.h>


#include "robot.h"


#define StartState WAIT		// Start State

enum State {                // State Machine
	WAIT,	
    PROCESS,
	RUNNING,
    STOPPING,
    ODOMETRY
};

/* VARIABLE DECLARATION AND INITITALIZATION */
unsigned char received_byte_id = 0;
unsigned char received_byte_arg = 0;

// id of the operation being executed
unsigned char current_byte_id = 0;

void main(void) 
{    
    enum State CS = StartState;	
    
    /* GENERIC I/O CONFIG */
    init_IO();
    
    /* CONFIGURATIONS */
    config_UART1(115200, 8, 'N', 1);
    
    configure_DRV8833_interface();
            
    config_Timer4();
    
    configure_global_interrupts();
    configure_external_interrupts();
    
    /* ENABLES */
    ENABLE_UART1_PHERIPHERAL;
    enable_DRV8833();
    ENABLE_TIMER_4;
    
    /* INTERRUPTIONS ENABLES */
    ENABLE_UART1_ALL_INTERRUPTS;
    ENABLE_ENCODERS;
    Enable_Global_Interrupts();
    
    
    /* START-UP SEQUENCE */
    put_string("Awaiting handshake... ");
    manage_initial_handshake();
    
    put_string("SUCCESS!\n\nROBOT Main Application.\nFirmware last modified on: ");
    put_string(__DATE__); put_string(", "); put_string(__TIME__); put_char('\n');
    
    ROBOT_INIT_SUCESS_LED = 1;
    ERROR_LED = 0;
    
    
    while(!START_BUTTON);
    
    put_string("ROBOT ENABLED!\n");
    
    while(!STOP_BUTTON)
    {
        if( DRV8833_fault_condition() == DRV8833_ERROR && (CS == RUNNING) )
        {
            ERROR_LED = 1;
            put_string(DRV8833_ERROR_MESSAGE);
        }
        else
        {
            ERROR_LED = 0;
        }
     
        if( get_char(&received_byte_id) == UART_SUCCESS )
        {
            // <editor-fold defaultstate="collapsed" desc="UART read">
            // If only the ID is expected (emergency stop)...
            if( (received_byte_id == ID_EMERGENCY_STOP) )// && (CS != STOPPING) )
            {
                put_string("EMERGENCY STOP\n");
                
                DISABLE_PID;
                brake_all_motors();
                
                CS = STOPPING;
            }
            
            // If is a movement or rotate instruction and is in WAIT state
            else if ( (CS == WAIT) && 
                    (received_byte_id >= ID_MOVE_FORWARD &&
                     received_byte_id <= ID_ROTATE_COUNTERCLOCKWISE) )
            {
                current_byte_id = received_byte_id;
                
                
                //put_string("\nPROCESS\n");
                CS = PROCESS;
            }
        }
        
        switch(CS)
        {
            case PROCESS:
                while( get_char(&received_byte_arg) == UART_SUCCESS);
                
                init_encoder_state();   // Initialize encoder state
                reset_enc_pulse_cnt();
                
                // define if is a rotation or a move 
                is_rotation = (uint8_t)((current_byte_id & 0x02) >> 1);
                
                // Truncate rotation
                if( is_rotation && (received_byte_arg > MAX_ANGLE) )
                {
                    received_byte_arg -= MAX_ANGLE;
                    
                    // if it is not clockwise is counterclockwise, then set to clockwise
                    current_byte_id = (current_byte_id == ID_ROTATE_CLOCKWISE) ? ID_ROTATE_COUNTERCLOCKWISE : ID_ROTATE_CLOCKWISE;
                    put_string("IS rotation\n");
                          
                }
                
                if(set_movement_direction(current_byte_id) == ROBOT_ERROR)
                {
                    //put_char(current_byte_id);
                    //put_char('\n');
                    ERROR_LED = 1;
                    put_string("ERROR");
                }
                
                //put_char( current_byte_id);
                CS = RUNNING;
                
                //ENABLE_PID;
            break;
            
            case RUNNING:
                //put_string("RUNNING\n");
                
                CS = RUNNING;
                break;
            case STOPPING:
                //put_string("STOPPING\n");
                //DISABLE_PID;
                brake_all_motors();
                CS = WAIT;
            break;
                
        }
        
    }
    
    brake_all_motors();
    put_string("STOPPED!\n");
        
}

