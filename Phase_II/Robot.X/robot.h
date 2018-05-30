/* 
 * File:   robot.h
 * Author: martinspedro
 *
 * Created on May 29, 2018, 12:21 AM
 */

#include <xc.h>

#include "../global.h"
#include "../interrupts.h"

#include "../UART.X/uart1.h"
#include "../DRV8833.X/DRV8833.h"
#include "../Encoder.X/encoder.h"

#include "communication_protocol.h"
#include "timer4.h"

#ifndef ROBOT_H
#define	ROBOT_H

#define ROBOT_ERROR   1
#define ROBOT_SUCCESS 0


#define START_BUTTON PORTFbits.RF0
#define STOP_BUTTON  PORTFbits.RF1

#define LED1 LATGbits.LATG12
#define LED2 LATGbits.LATG13
#define LED3 LATGbits.LATG14

#define ERROR_LED             LED1
#define ROBOT_INIT_SUCESS_LED LED2
#define OBSTACLE_DETECTED_LED LED3

#define EXTRA_1_INPUT  {TRISD8bits.RD8  = 1;}
#define EXTRA_1_OUTPUT {TRISD8bits.RD8  = 0;}
#define EXTRA_2_INPUT  {TRISD8bits.RD9  = 1;}
#define EXTRA_2_OUTPUT {TRISD8bits.RD9  = 0;}
#define EXTRA_3_INPUT  {TRISD8bits.RD10 = 1;}
#define EXTRA_3_OUTPUT {TRISD8bits.RD10 = 0;}

#define MAX_ANGLE 180



#define ENABLE_PID  ENABLE_TIMER4_INTERRUPTS
#define DISABLE_PID DISABLE_TIMER4_INTERRUPTS

#define MLEFT_SETPOINT_SPEED  35      // %
#define MRIGHT_SETPOINT_SPEED 35   // %

#define MAX_LEFT_DISTANCE 50 // mm
#define MAX_CENTER_DISTANCE 75 // mm
#define MAX_RIGHT_DISTANCE 50 // mm

// flag to distinguish between move and rotate
uint8_t is_rotation = 0;

void init_IO(void);

uint8_t set_movement_direction(uint8_t id);

#endif	/* ROBOT_H */

