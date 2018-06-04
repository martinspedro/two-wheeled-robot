/* 
 * \file:  robot.h
 * \brief  Robot Configuration and Control Header Files
 * 
 * \author Pedro Martins
 * \author Andre Gradim
 * 
 * \date   Created on May 29, 2018, 12:21 AM
 */

#include <xc.h>

#include "../global.h"
#include "../interrupts.h"

#include "../UART.X/uart1.h"
#include "../DRV8833.X/DRV8833.h"
#include "../Encoder.X/encoder.h"
#include "../VLX.X/tof.h"
#include "../MPU.X/mpu6050.h"

#include "IO.h"
#include "communication_protocol.h"
#include "timer4.h"

#ifndef ROBOT_H
#define	ROBOT_H

/*******************************************************************************
 *                      ROBOT PHYSICAL CONSTRAINTS 
 ******************************************************************************/
// 
#define WHEEL_DIAMETER          60                  //!< Wheel Diamenter in mm
#define WHEEL_RADIO             WHEEL_DIAMETER/2    //!< Wheel Ratio in mm
#define WHEEL_PERIMETER         189                 //!< Wheel Perimeter in mm
#define WHEEL_2_WHEEL_DIST      158                 //!< Wheel to Wheel Distance in mm

#define MOTOR_GEAR_RATIO        75                  //!< Motor Gear Ration
#define COUNTS_PER_REV          12                  //!< Encoder Counts per extended encoder shaft revolution
#define QUADRATURE_CPR          4*COUNTS_PER_REV    //!< Counts per revolution of the quadrature encoder state machine


/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define ROBOT_ERROR   1          //!< Return value macro that indicates an error has occurred
#define ROBOT_SUCCESS 0          //!< Return value macro that indicates the operation terminated succesfully 

#define MAX_ANGLE 180            //!< Maximum rotation angle in one direction

#define MLEFT_SETPOINT_SPEED  50    //!< Left Wheel Velocity Setpoint  (in function of PWM %)
#define MRIGHT_SETPOINT_SPEED 50    //!< Right Wheek Velocity Setpoint (in function of PWM %)

#define MAX_LEFT_DISTANCE   50      //!< Minimum obstacle distance (mm) for Left Obstacle Sensor
#define MAX_CENTER_DISTANCE 75      //!< Minimum obstacle distance (mm) for Center Obstacle Sensor
#define MAX_RIGHT_DISTANCE  50      //!< Minimum obstacle distance (mm) for Right Obstacle Sensor


#define ENABLE_PID   ENABLE_TIMER4_INTERRUPTS       //!< Encapsulate PID Timer Enable Instruction
#define DISABLE_PID  DISABLE_TIMER4_INTERRUPTS      //!< Encapsulate PID Timer Disable Instruction
#define CLEAR_PID_IF CLEAR_TMR4_IF                  //!< Encapsulate PID Timer Clear Interrupt Flag Instruction


/*******************************************************************************
 *                        FUNCTION HEADERS DEFINITION
 ******************************************************************************/

/** \brief Set motors desired operation 
 * 
 *  Using the communication protocol ID selects motors desired operation mode and
 *  executes DRV8833 routines
 * 
 * \param  id Instruction ID from the communication protocol
 * 
 * \return ROBOT_ERROR   if ID is invalid or not a movement/rotatio ID
 * \return ROBOT_SUCCESS if ID is valid
 * 
 * \author Pedro Martins
 */
uint8_t set_movement_direction(uint8_t id);

#endif	/* ROBOT_H */

