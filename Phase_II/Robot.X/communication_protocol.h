/* 
 * File:   communication_protocol.h
 * Author: martinspedro
 *
 * Created on May 29, 2018, 1:16 AM
 */

#ifndef COMMUNICATION_PROTOCOL_H
#define	COMMUNICATION_PROTOCOL_H

// ***************************************************************************
// COMMUNICATION
#define ID_HANDSHAKE_REQUEST           0x00
#define ID_LOCOMOTION_INIT_OK          0x02
#define ID_DEBUG_MESSAGE               0x04

#define ID_MOVE_FORWARD                0x20
#define ID_MOVE_BACKWARDS              0x21
#define ID_ROTATE_CLOCKWISE            0x22
#define ID_ROTATE_COUNTERCLOCKWISE     0x23
#define ID_EMERGENCY_STOP              0x24

#define ID_HOLE_DETECTED               0x25
#define ID_MOVEMENT_ROTATION_COMPLETED 0x26
#define ID_MOTORS_EXCESSIVE_CURRENT    0x27
#define ID_CURRENT_MOTOR_1             0x28
#define ID_CURRENT_MOTOR_2             0x29
#define ID_CURRENT_MOTOR_3             0x2A
#define ID_CURRENT_MOTOR_4             0x2B
#define ID_ROBOT_POSITION              0x2C

#define DEBUG_MESSAGE_MAX_SIZE         1


void manage_initial_handshake();


#endif	/* COMMUNICATION_PROTOCOL_H */

