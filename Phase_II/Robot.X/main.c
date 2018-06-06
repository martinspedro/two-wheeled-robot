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

/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define DETECT_OBSTACLES    //!< If defined, obtacle detection is active

#define StartState WAIT		//!< Robot Operation State Machine Initial State


/*******************************************************************************
 *                        VARIABLES DEFINITION
 ******************************************************************************/
enum Robot_State    //! Robot State Machine Possible States
{    
    WAIT,           //!< Waits for User Instructions
    PROCESS,        //!< Prepares the robot to execute user requests
    RUNNING,        //!< Executing User Requests
    STOPPING        //!< Finnish executing user requests.
};

/* VARIABLE DECLARATION AND INITITALIZATION */
unsigned char received_byte_id  = 0;    //!< Received Intruction ID
unsigned char received_byte_arg = 0;    //!< Received Intruction Argument
unsigned char current_byte_id   = 0;    //!< Instruction ID of the operation being executed

uint16_t distance_left   = 0;           //!< Left sensor distance (mm) to nearest obstacle
uint16_t distance_center = 0;           //!< Center sensor distance (mm) to nearest obstacle
uint16_t distance_right  = 0;           //!< Right sensor distance (mm) to nearest obstacle

uint8_t is_rotation = 0;                //!< Flag to indicate is current instruction is a movent or a rotatation

enum Robot_State CS = StartState;       //!< Current State of Robot State Machine 

int mleft_setpoint, mright_setpoint;
    

/*******************************************************************************
 *                          MAIN CODE
 ******************************************************************************/

/** \brief Robot Main Program
 * 
 * \param  None
 * \return None.
 * 
 * \author Pedro Martins
 * \author Andre Gradim
 */
void main(void) 
{    
    /* GENERIC I/O CONFIG */
    init_IO();
    
    /* CONFIGURATIONS */
    config_UART1(115200, 8, 'N', 1);    // UART
    configure_DRV8833_interface();      // LOCOMOTION CONTROL
    config_Timer4();                    // PID ISR 
    openI2C2();                         // I2C BUS
    configure_external_interrupts();    // Quadrature Encoders
    configure_global_interrupts();      // Global Interrupts
    
    
    /* ENABLES */
    ENABLE_UART1_PHERIPHERAL;           // UART1 Peripheral, TX and RX
    enable_DRV8833();                   // Locomotion
    ENABLE_TIMER_4;                     // Turn PID timer ON
    
    /* INTERRUPTIONS ENABLES */
    ENABLE_UART1_ALL_INTERRUPTS;
    ENABLE_ENCODERS;
    Enable_Global_Interrupts();


    

    
    initAllSensors();                   // Init DIstance Sensors (requires UART)
    
    put_string("Init done! Waiting START button...\n");
    while(!START_BUTTON);             // Wait for Start order
    /* START-UP SEQUENCE */
    put_string("Awaiting handshake... ");
    manage_initial_handshake();
    
    put_string("SUCCESS!\n\nROBOT Main Application.\nFirmware last modified on: ");
    put_string(__DATE__); put_string(", "); put_string(__TIME__); put_char('\n');
    
    /* TOGGLE STATUS LEDS */
    ROBOT_INIT_SUCESS_LED = 1;
    ERROR_LED = 0;
    
    
    
    
    
    put_string("ROBOT ACTIVE!\n");
    
    init_encoder_state();   // Initialize encoder state
    ENABLE_PID;
    uint8_t last_stop;
    
    int enc_left, enc_right;
    
    while(1)
    {   
        /*
        readEncoders(&enc_left, &enc_right);
        put_uint16(enc_left);
        put_char('\t');
        put_uint16(enc_right);
        put_char('\n');*/

        if(STOP_BUTTON && CS != WAIT){
            CS=STOPPING;
        }
        last_stop = STOP_BUTTON;
        
        // <editor-fold defaultstate="collapsed" desc="PARSE USER REQUESTS">
        if( get_char(&received_byte_id) == UART_SUCCESS )
        {
            
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
        // </editor-fold>
        
        // <editor-fold defaultstate="collapsed" desc="MOTOR FAULT CONDITION VERIFICATION">
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
        // </editor-fold>
        
        switch(CS)
        {
            case PROCESS:
                // <editor-fold defaultstate="collapsed" desc="PROCESS USER REQUESTS">
                while( get_char(&received_byte_arg) == UART_SUCCESS);   // Wait for Instruction Arguments
                
                // init_encoder_state();   // Initialize encoder state
                //reset_enc_pulse_cnt();  // Reset all encoder pulse counters
                
                // dFilter rotations from movement
                is_rotation = (uint8_t)((current_byte_id & 0x02) >> 1);
                
                // Truncate and optimize rotation if required
                if( is_rotation && (received_byte_arg > MAX_ANGLE) )
                {
                    received_byte_arg -= MAX_ANGLE;
                    
                    // if it is not clockwise is counterclockwise, then set to clockwise
                    current_byte_id = (current_byte_id == ID_ROTATE_CLOCKWISE) ? ID_ROTATE_COUNTERCLOCKWISE : ID_ROTATE_CLOCKWISE;
                    //put_string("IS rotation\n");
                }
                
                // Actuate on DRV8833
                if(set_movement_direction(current_byte_id) == ROBOT_ERROR)
                {
                    //put_char(current_byte_id);
                    //put_char('\n');
                    ERROR_LED = 1;
                    put_string("ERROR");
                }
                
                /*// Enable PID control algorithm if it is a movement
                if(current_byte_id == ID_MOVE_FORWARD)
                {
                    ENABLE_PID;
                }*/
                
                CS = RUNNING;
               
            // </editor-fold>
            break;
            
            
            case RUNNING:
                // <editor-fold defaultstate="collapsed" desc="EXECUTING USER REQUESTS">
                // put_string("RUNNING\n");
                
                // Read Distance Sensors
                
                /* If obstacle detection is enabled and the robot is moving forward, 
                   enable obstacle detection and emergency stop conditions */
                
                if(current_byte_id == ID_MOVE_FORWARD && tofReadDistanceAllSensors(&distance_left, &distance_center, &distance_right) == SUCCESS)
                {
                    
                    #ifdef DETECT_OBSTACLES
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
                    #endif
                }
                

                put_uint16(distance_left); 
                put_string(" - ");
                put_uint16(distance_center); 
                put_string(" - ");
                put_uint16(distance_right); 
                put_char('\n');
            // </editor-fold>
            break;
            
            
            case STOPPING:
                // <editor-fold defaultstate="collapsed" desc="STOP ROBOT MOVEMENT">
                put_string("STOPPING\n");
                
                mleft_setpoint = 0;
                mright_setpoint = 0;
                DISABLE_PID;
                brake_all_motors();
                ENABLE_PID;
                CS = WAIT;
            // </editor-fold>
            break;   
            case WAIT:
                CS = WAIT;
            break;
        }
        
    }
    
    // stop robot if STOP button is pressed
    mleft_setpoint = 0;
    mright_setpoint = 0;
    //brake_all_motors();
    put_string("STOPPED!\n");
    while(1);
    
}

