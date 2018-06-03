/* 
 * \file:  main.c
 * \brief  Robot main program 
 * 
 * \author Pedro Martins
 * \author Andre Gradim
 * \date   Created on May 28, 2018, 11:41 PM
 */

#include "../DEVCFGx_config_bits.h"


#include <stdio.h>
#include <stdlib.h>
#include <xc.h>


#include "robot.h"

#define DETECT_OBSTACLES

#define StartState WAIT		//!< Robot Operation State Machine Initial State

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

uint16_t distance_left = 0;
uint16_t distance_center = 0;
uint16_t distance_right = 0;

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
    
    openI2C2();
    
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
    
    initAllSensors();
    
    /* START-UP SEQUENCE */
    put_string("Awaiting handshake... ");
    manage_initial_handshake();
    
    put_string("SUCCESS!\n\nROBOT Main Application.\nFirmware last modified on: ");
    put_string(__DATE__); put_string(", "); put_string(__TIME__); put_char('\n');
    
    ROBOT_INIT_SUCESS_LED = 1;
    ERROR_LED = 0;
    
    
    //while(!START_BUTTON);
    
    put_string("ROBOT ENABLED!\n");
    
    while(!STOP_BUTTON)
    {
        if( DRV8833_fault_condition() == DRV8833_ERROR && (CS == RUNNING) )
        {
            ERROR_LED = 1;
            put_string(DRV8833_ERROR_MESSAGE);
            CS = STOPPING;
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
                if(current_byte_id == ID_MOVE_FORWARD)
                {
                    ENABLE_PID;
                }
               
            break;
            
            case RUNNING:
                //put_string("RUNNING\n");
                
                tofReadDistanceAllSensors(&distance_left, &distance_center, &distance_right);
                put_uint16(distance_left); 
                put_string(" - ");
                put_uint16(distance_center); 
                put_string(" - ");
                put_uint16(distance_right); 
                put_char('\n');
                
                #ifdef DETECT_OBSTACLES
                if(current_byte_id == ID_MOVE_FORWARD)
                {
                    if (distance_center <= MAX_CENTER_DISTANCE)
                    {
                        put_string("OBSTACLE DETECTED! CENTER\n");
                        OBSTACLE_DETECTED_LED = 1;        
                        CS = STOPPING;
                    } else if(distance_left <= MAX_LEFT_DISTANCE) {
                        put_string("OBSTACLE DETECTED! LEFT\n");
                        OBSTACLE_DETECTED_LED = 1;        
                        CS = STOPPING;
                    } else if(distance_right <= MAX_RIGHT_DISTANCE) {
                        put_string("OBSTACLE DETECTED! RIGHT\n");
                        OBSTACLE_DETECTED_LED = 1;        
                        CS = STOPPING;
                    } else {   
                        CS = RUNNING;
                    }
                }
                #endif
                break;
            case STOPPING:
                put_string("STOPPING\n");
                DISABLE_PID;
                brake_all_motors();
                CS = WAIT;
            break;
                
        }
        
    }
    
    brake_all_motors();
    put_string("STOPPED!\n");
        
}

