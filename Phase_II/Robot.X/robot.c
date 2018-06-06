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
#include "../VLX.X/tof.h"


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

/** \brief Initialization of all distance sensors
 * 
 * \pre     I2C, UART must be active
 * \pre     3 VL53L0X must be connect to the bus
 * \pre     XSHUT pin from 2 of the VL53L0X must be connect to EXTRA_1 and EXTRA_2 pins
 * 
 * \param  None.
 * \return None.
 * 
 * 
 * \author Andre Gradim
 * \author Pedro Martins
 */
void initAllSensors(){
    EXTRA_1_OUTPUT
    EXTRA_2_OUTPUT
  
    //set sensors in shutdown mode ( 0 -> shutdown; 1 -> wake)
    EXTRA_1_LAT = 0;
    EXTRA_2_LAT = 0;

    //Change address from DEFAULT to CENTER
    setAddress(DEFAULT_ADDRESS,CENTER);
    
    //Wake LEFT sensor from shutdown
    EXTRA_2_LAT = 1;
    
    int i;
    
    //Initialize CENTER sensor while LEFT is booting
    i = initSensor(CENTER, 1); // set long range mode (up to 2m)
    if (i !=1 ){
        put_string("ERROR in init center: ");
        put_uint8(i);
	}
    i = 0;
    
    //Change address from DEFAULT to CENTER
    setAddress(DEFAULT_ADDRESS,LEFT);

    //Wake RIGHT sensor from shutdown
    EXTRA_1_LAT = 1;
    
    
    //Initialize LEFT sensor while RIGHT is booting
    i = initSensor(LEFT, 1); // set long range mode (up to 2m)
    
	if (i !=1 ){
        put_string("ERROR in init left: ");
        put_uint8(i);
	}
    i = 0;
    
    //Change address from DEFAULT to CENTER
    setAddress(DEFAULT_ADDRESS,RIGHT);
    
    //Initialize RIGHT sensor
    i = initSensor(RIGHT, 1); // set long range mode (up to 2m)
    
	if (i !=1 ){
        put_string("ERROR in init right: ");
        put_uint8(i);
	}

    //Set EXTRA pins as INPUTs
    EXTRA_1_INPUT
    EXTRA_2_INPUT    
}

/** \brief Perform measurements of the 3 sensors
 * 
 * \pre     I2C, UART must be active
 * \pre     3 VL53L0X must be connect to the bus with LEFT,CENTER and RIGHT address
 * 
 * \param  dev_left     Pointer to variable to save data from left sensor
 * \param  dev_center   Pointer to variable to save data from center sensor
 * \param  dev_right    Pointer to variable to save data from right sensor
 * \return SUCCESS on success 
 * \return ERROR_GET_DISTANCE when error occured in reading distance
 * \return ERROR_TIMEOUT when a timeout occurs in communications
 * 
 * 
 * \author Andre Gradim
 * \author Pedro Martins
 */
int tofReadDistanceAllSensors(uint16_t* dev_left, uint16_t* dev_center, uint16_t* dev_right)
{
  int iTimeout;
  uint8_t dev_add_list[] = {LEFT, CENTER, RIGHT};
  uint8_t dev_add;

  uint8_t temp = 0;
  for( temp = 0; temp < 3; temp++){
      dev_add = dev_add_list[temp]; 
      measure_request(dev_add);
  }
  
  // "Wait until start bit has been cleared"
  iTimeout = 0;
  temp = 0;
  int val;
  while (1)
  {
    val = 0;
    for( temp = 0; temp < 3; temp++){
      dev_add = dev_add_list[temp];
      val += sensor_measure_ready(dev_add);
    }
    if(val == 0){
      break;
    }
    
    iTimeout++;
    delay5ms();
    if (iTimeout > 50)
    {
      return ERROR_TIMEOUT;
    }
  }

  *dev_left = readRangeContinuousMillimeters(dev_add_list[0]);
  *dev_center = readRangeContinuousMillimeters(dev_add_list[1]);
  *dev_right = readRangeContinuousMillimeters(dev_add_list[2]);
  
  if(dev_left == 0 | dev_center == 0 | dev_right == 0){
      return ERROR_GET_DISTANCE;
  }
  return SUCCESS;

} 

