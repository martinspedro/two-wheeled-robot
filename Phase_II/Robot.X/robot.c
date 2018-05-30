/* 
 * File:   robot.c
 * Author: martinspedro
 *
 * Created on May 29, 2018, 12:21 AM
 */

#include "robot.h"
#include "../interrupts.h"
#include "timer4.h"

// ***************************************************************************
// Controller parameters
#define	SAMPLING_T	10		// [ms]
#define RPM_OUT = 1
#define SP_MAX		((RPM_OUT * MOTOR_GEAR_RATIO * QUADRATURE_CPR * SAMPLING_T) / 60000)
#define INTEGRAL_CLIP	70				// Cliping value of the Integral component


const signed int KP_num=1, KP_den=1;	// Propotional constant
const signed int KI_num=0, KI_den=2;	// Integral constant



uint8_t set_movement_direction(uint8_t id)
{
    if( (id < ID_MOVE_FORWARD) || (id > ID_ROTATE_COUNTERCLOCKWISE) )
        return ROBOT_ERROR;
    
    switch(id)
    {
        case ID_MOVE_FORWARD:
            move_forward(MLEFT_SETPOINT_SPEED, MRIGHT_SETPOINT_SPEED);
            break;
        case ID_MOVE_BACKWARDS:
            move_backwards(MLEFT_SETPOINT_SPEED, MRIGHT_SETPOINT_SPEED);
            break;
        case ID_ROTATE_CLOCKWISE:
            rotate_clockwise(MLEFT_SETPOINT_SPEED, MRIGHT_SETPOINT_SPEED);
            break;
        case ID_ROTATE_COUNTERCLOCKWISE:
            rotate_counterclockwise(MLEFT_SETPOINT_SPEED, MRIGHT_SETPOINT_SPEED);
            break;
        default:
            return ROBOT_ERROR;
    }
    
    return ROBOT_SUCCESS;
}


void __ISR(_TIMER_4_VECTOR, IPL6SOFT) PID_ISR(void)
{
    LED3 = 1;
   // LATDbits.LATD4 = 1;
    static int error, prop = 0;
	static int integralMLeft, integralMRight = 0;
	static int cmdMLeft, cmdMRight;

	error = -(pulse_count_L - MLEFT_SETPOINT_SPEED);
	prop = (KP_num * error) / KP_den;
	integralMLeft += error;

	integralMLeft = integralMLeft > INTEGRAL_CLIP ? INTEGRAL_CLIP : integralMLeft;
	integralMLeft = integralMLeft < -INTEGRAL_CLIP ? -INTEGRAL_CLIP : integralMLeft;

	cmdMLeft = prop + (integralMLeft * KI_num) / KI_den;

	cmdMLeft = cmdMLeft > 100 ? 100 : cmdMLeft;
	cmdMLeft = cmdMLeft < -100 ? -100 : cmdMLeft;

	error = -(pulse_count_R - MRIGHT_SETPOINT_SPEED);
	prop= (KP_num * error) / KP_den;
	integralMRight += error;

	integralMRight = integralMRight > INTEGRAL_CLIP ? INTEGRAL_CLIP : integralMRight;
	integralMRight = integralMRight < -INTEGRAL_CLIP ? -INTEGRAL_CLIP : integralMRight;

	cmdMRight = prop + (integralMRight * KI_num) / KI_den;

	cmdMRight = cmdMRight > 100 ? 100 : cmdMRight;
	cmdMRight = cmdMRight < -100 ? -100 : cmdMRight;

    /*
    if(aux == 1)
    {
        put_uint16(puls);
        put_char('\n');
        put_uint16(integralMRight);
        aux = 0;
    }
    */
    if(cmdMLeft > 0)
    {
        forward_fast_decay_left(cmdMLeft);
    }
    else
    {
        reverse_fast_decay_left(-cmdMLeft);
    }
    
    if(cmdMRight > 0)
    {
        forward_fast_decay_right(cmdMRight);
    }
    else
    {
        reverse_fast_decay_right(-cmdMRight);
    }
	
    CLEAR_TMR4_INT_FLAG;
   // LATDbits.LATD4 = 0;
}

void init_IO(void)
{
    TRISGCLR = 0x7000;      // Set LEDs as output and resets them
    LATGCLR  = 0x7000;
}