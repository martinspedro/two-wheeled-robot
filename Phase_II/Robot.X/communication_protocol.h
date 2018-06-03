/** 
 * \file   communication_protocol.h
 * \brief  Communication Protocol Module Configuration C file
 * \pre    Uses UART1
 * 
 * \author Pedro Martins
 * \date   Created on May 29, 2018, 1:16 AM
 */


#ifndef COMMUNICATION_PROTOCOL_H
#define	COMMUNICATION_PROTOCOL_H

/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define ID_HANDSHAKE_REQUEST           0x00     //!< Handshake requested by Master
#define ID_HANDSHAKE_ACK               0x02     //!< Handshake acknowledge by Slave
#define ID_DEBUG_MESSAGE               0x04     //!< ID used to send a debug message to the master

#define ID_MOVE_FORWARD                0x20     //!< Instruction Request: Move forward
#define ID_MOVE_BACKWARDS              0x21     //!< Instruction Request: Move backwards
#define ID_ROTATE_CLOCKWISE            0x22     //!< Instruction Request: Rotate Clockwise
#define ID_ROTATE_COUNTERCLOCKWISE     0x23     //!< Instruction Request: Rotate Counter Clockwise
#define ID_EMERGENCY_STOP              0x24     //!< Instruction Request: Stop Immediatelly

#define ID_HOLE_DETECTED               0x25     //!< A hole is detected
#define ID_MOVEMENT_ROTATION_COMPLETED 0x26     //!< Rotation is completed
#define ID_MOTORS_EXCESSIVE_CURRENT    0x27     //!< Motors current is above safety threshold
#define ID_CURRENT_MOTOR_1             0x28     //!< Current Measurement value for Motor 1
#define ID_CURRENT_MOTOR_2             0x29     //!< Current Measurement value for Motor 2
#define ID_CURRENT_MOTOR_3             0x2A     //!< Current Measurement value for Motor 3
#define ID_CURRENT_MOTOR_4             0x2B     //!< Current Measurement value for Motor 4
#define ID_ROBOT_POSITION              0x2C     //!< Robot Relative Position Coordinates

#define DEBUG_MESSAGE_MAX_SIZE         8        //!< Maximum number of characters for the Debug Message


// Undefine Macros for not supported functionalities
#undef ID_HOLE_DETECTED 
#undef ID_CURRENT_MOTOR_3 
#undef ID_CURRENT_MOTOR_4


/*******************************************************************************
 *                        FUNCTION HEADERS DEFINITION
 ******************************************************************************/

/** \brief Manages Handshake between the robot and the user
 * 
 * \pre    Robot must be initialized
 * \pre    UART must be configured and running
 * 
 * \author Pedro Martins
 */
void manage_initial_handshake();


#endif	/* COMMUNICATION_PROTOCOL_H */

