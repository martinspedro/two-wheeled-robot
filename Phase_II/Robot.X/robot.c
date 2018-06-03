/* 
 * \file:  robot.c
 * \brief  Robot Configuration and Control C File
 * 
 * \author Pedro Martins
 * \author Andre Gradim
 * 
 * \date   Created on May 29, 2018, 12:21 AM
 */

#include "robot.h"


/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define	SAMPLING_T	10		//!< Sampling Time for PID routine (ms)
#define RPM_OUT     400     //!< Maximum number of Rotations Per Minute (RPM) of motor

/** \brief Maximum value for the desired setpoint
 * Given by the equation: 
 * \f[SP_{MAX} = \frac{CPR_{Quadrature} \cdot Gear-ratio_{motor} \cdot RPM_{Out} \cdot T_{samp}}{60 \cdot 1000}\f]
 */
#define SP_MAX		((QUADRATURE_CPR * MOTOR_GEAR_RATIO * RPM_OUT * SAMPLING_T) / 60000)

#define INTEGRAL_CLIP 80    //!< Cliping Limit for the Integral component


/*******************************************************************************
 *                       CLASS VARIABLES DEFINITION
 ******************************************************************************/
const signed int KP_num=10;     //!< Numerator of Proportional Constant for PID Controller
const signed int KP_den=10;     //!< Denominator of Proportional Constant for PID Controller
const signed int KI_num=1;      //!< Numerator of Integral Constant for PID Controller
const signed int KI_den=15;     //!< Denominator of Integral Constant for PID Controller


/*******************************************************************************
 *                         CLASS METHODS
 ******************************************************************************/

uint8_t set_movement_direction(uint8_t id)
{
    // check if ID is valid
    if( (id < ID_MOVE_FORWARD) || (id > ID_ROTATE_COUNTERCLOCKWISE) )
        return ROBOT_ERROR;
    
    switch(id)
    {
        case ID_MOVE_FORWARD:
            move_forward_fast_decay(MLEFT_SETPOINT_SPEED, MRIGHT_SETPOINT_SPEED);
            break;
        case ID_MOVE_BACKWARDS:
            move_backwards_fast_decay(MLEFT_SETPOINT_SPEED, MRIGHT_SETPOINT_SPEED);
            break;
        case ID_ROTATE_CLOCKWISE:
            rotate_clockwise_fast_decay(MLEFT_SETPOINT_SPEED, MRIGHT_SETPOINT_SPEED);
            break;
        case ID_ROTATE_COUNTERCLOCKWISE:
            rotate_counterclockwise_fast_decay(MLEFT_SETPOINT_SPEED, MRIGHT_SETPOINT_SPEED);
            break;
        default:
            return ROBOT_ERROR;
    }
    
    return ROBOT_SUCCESS;
}



/** \brief ISR for PID Control Algorithm
 * 
 * \pre    Global Interrupts must be configured and enabled
 * \pre    Timer 4 must be configured and enabled
 * 
 * \param  None.
 * \return None.
 * 
 * Interruption Service Routine for control algorithm (PID), using Timer 4
 * 
 * The Interruption Priority Level is 6 and the compiler must write software to
 * perform the context switching (IPL6SOFT)
 * 
 * \author Pedro Martins
 * \author Andre Gradim
 * \author J.L.Azevedo (23/10/2014)
 */
void __ISR(_TIMER_4_VECTOR, IPL6SOFT) PID_ISR(void)
{
    LED3 = 1;
    
    static int error, prop = 0;
	static int integralMLeft, integralMRight = 0;
	static int cmdMLeft, cmdMRight;

    /* Left Motor PID */
	error = -((pulse_count_L * 100/SP_MAX) - MLEFT_SETPOINT_SPEED);
	prop = (KP_num * error) / KP_den;
	integralMLeft += (error * KI_num) / KI_den;

    // Clip Integral values
	integralMLeft = integralMLeft > INTEGRAL_CLIP ? INTEGRAL_CLIP : integralMLeft;
	integralMLeft = integralMLeft < -INTEGRAL_CLIP ? -INTEGRAL_CLIP : integralMLeft;

	cmdMLeft = prop + (integralMLeft);

    // Truncate PWM values
	cmdMLeft = cmdMLeft > 100 ? 100 : cmdMLeft;
	cmdMLeft = cmdMLeft < -100 ? -100 : cmdMLeft;

    /* Right Motor PID */
	error = -((pulse_count_R * 100 / SP_MAX) - MRIGHT_SETPOINT_SPEED);
	prop= (KP_num * error) / KP_den;
	integralMRight += (error* KI_num) / KI_den;

    // Clip Integral values
	integralMRight = integralMRight > INTEGRAL_CLIP ? INTEGRAL_CLIP : integralMRight;
	integralMRight = integralMRight < -INTEGRAL_CLIP ? -INTEGRAL_CLIP : integralMRight;

	cmdMRight = prop + (integralMRight );

    // Truncate PWM values
	cmdMRight = cmdMRight > 100 ? 100 : cmdMRight;
	cmdMRight = cmdMRight < -100 ? -100 : cmdMRight;
    
    
    // Actuate on motors. If PWM is negative use |PWM| and change direction 
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
	
    
    // reset pulse count for encoders
    reset_enc_pulse_cnt();
    
    
    CLEAR_PID_IF;
}
