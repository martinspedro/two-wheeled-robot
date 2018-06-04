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

#define INTEGRAL_CLIP 60    //!< Cliping Limit for the Integral component

/*******************************************************************************
 *                       CLASS VARIABLES DEFINITION
 ******************************************************************************/
const int KP_num=2;     //!< Numerator of Proportional Constant for PID Controller
const int KP_den=1;     //!< Denominator of Proportional Constant for PID Controller
const int KI_num=0;      //!< Numerator of Integral Constant for PID Controller
const int KI_den=100;     //!< Denominator of Integral Constant for PID Controller


extern int mleft_setpoint, mright_setpoint;

/*******************************************************************************
 *                         CLASS METHODS
 ******************************************************************************/

uint8_t set_movement_direction(uint8_t id)
{
    //mleft_setpoint = 0;
    //mright_setpoint = 0;
    // check if ID is valid
    if( (id < ID_MOVE_FORWARD) || (id > ID_ROTATE_COUNTERCLOCKWISE) )
        return ROBOT_ERROR;
    
    switch(id)
    {
        case ID_MOVE_FORWARD:
            mleft_setpoint  =   MLEFT_SETPOINT_SPEED;
            mright_setpoint =   MRIGHT_SETPOINT_SPEED;
            //move_forward_fast_decay(MLEFT_SETPOINT_SPEED, MRIGHT_SETPOINT_SPEED);
            break;
        case ID_MOVE_BACKWARDS:
            mleft_setpoint  = - MLEFT_SETPOINT_SPEED;
            mright_setpoint = - MRIGHT_SETPOINT_SPEED;
            //move_backwards_fast_decay(MLEFT_SETPOINT_SPEED, MRIGHT_SETPOINT_SPEED);
            break;
        case ID_ROTATE_CLOCKWISE:
            mleft_setpoint  =   MLEFT_SETPOINT_SPEED;
            mright_setpoint = - MRIGHT_SETPOINT_SPEED;
            //rotate_clockwise_fast_decay(MLEFT_SETPOINT_SPEED, MRIGHT_SETPOINT_SPEED);
            break;
        case ID_ROTATE_COUNTERCLOCKWISE:
            mleft_setpoint  = - MLEFT_SETPOINT_SPEED;
            mright_setpoint =   MRIGHT_SETPOINT_SPEED;
            //rotate_counterclockwise_fast_decay(MLEFT_SETPOINT_SPEED, MRIGHT_SETPOINT_SPEED);
            break;
        default:
            
            mleft_setpoint  =  0;
            mright_setpoint =  0;
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
    
    signed int error= 0, prop = 0;
	static int integralMLeft = 0, integralMRight = 0;
    int cmdMLeft, cmdMRight;
      
    mleft_setpoint = (mleft_setpoint >  100)?( 100): mleft_setpoint;
    mleft_setpoint = (mleft_setpoint < -100)?(-100): mleft_setpoint;
   
    mright_setpoint = (mright_setpoint >  100)?( 100): mright_setpoint;
    mright_setpoint = (mright_setpoint < -100)?(-100): mright_setpoint;
   
    //enc_left = pulse_count_L;
    //enc_right = pulse_count_R;
    int enc_left, enc_right;
    readEncoders(&enc_left, &enc_right);
    // reset pulse count for encoders
    reset_enc_pulse_cnt();
    
    
    /* Left Motor PID */
    //error = 0;
	error = (mleft_setpoint ) - (enc_left); //* SP_MAX / 100
	prop = (KP_num * error) / KP_den;
	integralMLeft += (KI_num * error)/KI_den ;

    // Clip Integral values
	integralMLeft = integralMLeft > INTEGRAL_CLIP ? INTEGRAL_CLIP : integralMLeft;
	integralMLeft = integralMLeft < -INTEGRAL_CLIP ? -INTEGRAL_CLIP : integralMLeft;

	cmdMLeft = prop + (integralMLeft);

    // Truncate PWM values
	cmdMLeft = cmdMLeft > 100 ? 100 : cmdMLeft;
	cmdMLeft = cmdMLeft < -100 ? -100 : cmdMLeft;

    /* Right Motor PID */
	error = (mright_setpoint) - (enc_right); //* SP_MAX / 100
	prop= (KP_num * error) / KP_den;
	integralMRight += (KI_num * error)/KI_den ;

    // Clip Integral values
	integralMRight = integralMRight > INTEGRAL_CLIP ? INTEGRAL_CLIP : integralMRight;
	integralMRight = integralMRight < -INTEGRAL_CLIP ? -INTEGRAL_CLIP : integralMRight;

	cmdMRight = prop + (integralMRight);

    // Truncate PWM values
	cmdMRight = cmdMRight > 100 ? 100 : cmdMRight;
	cmdMRight = cmdMRight < -100 ? -100 : cmdMRight;
    
    
    
    
    // Actuate on motors. If PWM is negative use |PWM| and change direction 
    if(cmdMLeft  == 0){
        brake_left_motor();
        
    }
    else if(cmdMLeft > 0)
    {
        forward_fast_decay_left(cmdMLeft);
    }
    else
    {
        reverse_fast_decay_left(-cmdMLeft);
    }
    
    
    
    if(cmdMRight == 0){
        brake_right_motor();
        
    }
    else if(cmdMRight> 0)
    {
        forward_fast_decay_right(cmdMRight);
    }
    else
    {
        reverse_fast_decay_right(-cmdMRight);
    }
	
    
    
    LED3 = 0;
    
    CLEAR_PID_IF;
}
