/** 
 * \file   DRV8833.c
 * \brief  DRV8833 module device driver configuration C file
 * 
 * \author Pedro Martins
 * \date   Created on May 5, 2018, 6:11 PM
 */

#include <xc.h>

#include "../global.h"

#include "DRV8833.h"


/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define MOTOR_LEFT_A_SET_PWM(duty_cycle)  set_PWM1_duty_cycle(duty_cycle)
#define MOTOR_LEFT_B_SET_PWM(duty_cycle)  set_PWM2_duty_cycle(duty_cycle)
#define MOTOR_RIGHT_A_SET_PWM(duty_cycle) set_PWM3_duty_cycle(duty_cycle)
#define MOTOR_RIGHT_B_SET_PWM(duty_cycle) set_PWM4_duty_cycle(duty_cycle)

#define nSLEEP_TRIS TRISDbits.TRISD5
#define nFAULT_TRIS TRISDbits.TRISD6



/*******************************************************************************
 *                         CLASS METHODS
 ******************************************************************************/

void configure_DRV8833_interface(void)
{
    DISABLE_DRV8833;

    // Configure I/O
    nSLEEP_TRIS = 0;   // nSLEEP (Output)
    nFAULT_TRIS = 1;   // nFAULT (Input)
   
    
    // Configure current monitoring
    adc_peripheral_init();
    
    init_ADC_ch(M1_ISEN_ADC_CH);
    init_ADC_ch(M2_ISEN_ADC_CH);
   
    // Configure PWM
    config_Timer2();
    
    output_compare_1_init();
    output_compare_2_init();
    output_compare_3_init();
    output_compare_4_init();
    
    // Set all motor to open state
    open_all_motors();
}

void enable_DRV8833(void)
{
    ENABLE_DRV8833;     // first because of the delay time required to init internal states
    
    ENABLE_ADC;
            
    ENABLE_TIMER_2;
            
    ENABLE_OUTPUT_COMPARE_PERIPHERAL_1;
    ENABLE_OUTPUT_COMPARE_PERIPHERAL_2;
    ENABLE_OUTPUT_COMPARE_PERIPHERAL_3;
    ENABLE_OUTPUT_COMPARE_PERIPHERAL_4;
}

uint8_t DRV8833_fault_condition(void)
{
    if(nFAULT == DRV8833_ERROR)
    {
        open_all_motors();
    }
    return (nFAULT);
}


// <editor-fold defaultstate="collapsed" desc="ON-OFF MOTOR METHODS">
/*******************************************************************************
 *                         ON-OFF MOTOR METHODS
 ******************************************************************************/
void open_all_motors(void)
{
    MOTOR_LEFT_A_SET_PWM(0);
    MOTOR_LEFT_B_SET_PWM(0);
    MOTOR_RIGHT_A_SET_PWM(0);
    MOTOR_RIGHT_B_SET_PWM(0);
}

void brake_all_motors(void)
{
    MOTOR_LEFT_A_SET_PWM(100);
    MOTOR_LEFT_B_SET_PWM(100);
    MOTOR_RIGHT_A_SET_PWM(100);
    MOTOR_RIGHT_B_SET_PWM(100);
}

void open_left_motor(void)
{
    MOTOR_LEFT_A_SET_PWM(0);
    MOTOR_LEFT_B_SET_PWM(0);
}

void open_right_motor(void)
{
    MOTOR_RIGHT_A_SET_PWM(0);
    MOTOR_RIGHT_B_SET_PWM(0);
}

void reverse_left_motor(void)
{
    MOTOR_LEFT_A_SET_PWM(0);
    MOTOR_LEFT_B_SET_PWM(100);
}

void reverse_right_motor(void)
{
    MOTOR_RIGHT_A_SET_PWM(0);
    MOTOR_RIGHT_B_SET_PWM(100);
}

void forward_left_motor(void)
{
    MOTOR_LEFT_A_SET_PWM(100);
    MOTOR_LEFT_B_SET_PWM(0);
}

void forward_right_motor(void)
{
    MOTOR_RIGHT_A_SET_PWM(100);
    MOTOR_RIGHT_B_SET_PWM(0);
}

void brake_left_motor(void)
{
    MOTOR_LEFT_A_SET_PWM(100);
    MOTOR_LEFT_B_SET_PWM(100);
}

void brake_right_motor(void)
{
    MOTOR_RIGHT_A_SET_PWM(100);
    MOTOR_RIGHT_B_SET_PWM(100);
}

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="PWM MOTOR METHODS">
/*******************************************************************************
 *                       PWM MOTOR METHODS
 ******************************************************************************/
void forward_fast_decay_left(uint8_t duty_cycle)
{
    duty_cycle = (duty_cycle > MAX_DUTY) ? MAX_DUTY : duty_cycle;
    duty_cycle = (duty_cycle < MIN_DUTY) ? MIN_DUTY : duty_cycle;
    
    
    MOTOR_LEFT_A_SET_PWM(duty_cycle);
    MOTOR_LEFT_B_SET_PWM(0);
}

void forward_slow_decay_left(uint8_t duty_cycle)
{
    duty_cycle = (duty_cycle > MAX_DUTY) ? MAX_DUTY : duty_cycle;
    duty_cycle = (duty_cycle < MIN_DUTY) ? MIN_DUTY : duty_cycle;
    
    
    MOTOR_LEFT_A_SET_PWM(100);
    MOTOR_LEFT_B_SET_PWM(duty_cycle);
}

void reverse_fast_decay_left(uint8_t duty_cycle)
{
    duty_cycle = (duty_cycle > MAX_DUTY) ? MAX_DUTY : duty_cycle;
    duty_cycle = (duty_cycle < MIN_DUTY) ? MIN_DUTY : duty_cycle;
    
    
    MOTOR_LEFT_A_SET_PWM(0);
    MOTOR_LEFT_B_SET_PWM(duty_cycle);
}

void reverse_slow_decay_left(uint8_t duty_cycle)
{
    duty_cycle = (duty_cycle > MAX_DUTY) ? MAX_DUTY : duty_cycle;
    duty_cycle = (duty_cycle < MIN_DUTY) ? MIN_DUTY : duty_cycle;
    
    
    MOTOR_LEFT_A_SET_PWM(duty_cycle);
    MOTOR_LEFT_B_SET_PWM(100);
}



void forward_fast_decay_right(uint8_t duty_cycle)
{
    duty_cycle = (duty_cycle > MAX_DUTY) ? MAX_DUTY : duty_cycle;
    duty_cycle = (duty_cycle < MIN_DUTY) ? MIN_DUTY : duty_cycle;
    
    
    MOTOR_RIGHT_A_SET_PWM(duty_cycle);
    MOTOR_RIGHT_B_SET_PWM(0);
}

void forward_slow_decay_right(uint8_t duty_cycle)
{
    duty_cycle = (duty_cycle > MAX_DUTY) ? MAX_DUTY : duty_cycle;
    duty_cycle = (duty_cycle < MIN_DUTY) ? MIN_DUTY : duty_cycle;
    
    
    MOTOR_RIGHT_A_SET_PWM(100);
    MOTOR_RIGHT_B_SET_PWM(duty_cycle);
}

void reverse_fast_decay_right(uint8_t duty_cycle)
{
    duty_cycle = (duty_cycle > MAX_DUTY) ? MAX_DUTY : duty_cycle;
    duty_cycle = (duty_cycle < MIN_DUTY) ? MIN_DUTY : duty_cycle;
    
    
    MOTOR_RIGHT_A_SET_PWM(0);
    MOTOR_RIGHT_B_SET_PWM(duty_cycle);
}

void reverse_slow_decay_right(uint8_t duty_cycle)
{
    duty_cycle = (duty_cycle > MAX_DUTY) ? MAX_DUTY : duty_cycle;
    duty_cycle = (duty_cycle < MIN_DUTY) ? MIN_DUTY : duty_cycle;
    
    
    MOTOR_RIGHT_A_SET_PWM(duty_cycle);
    MOTOR_RIGHT_B_SET_PWM(100);
}

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="MOTORS DIRECTION CONTROLLER">

void move_forward(uint8_t duty_cycle_left, uint8_t duty_cycle_right)
{
    forward_fast_decay_left(duty_cycle_left);
    forward_fast_decay_right(duty_cycle_right);
}

void move_backwards(uint8_t duty_cycle_left, uint8_t duty_cycle_right)
{
    reverse_fast_decay_left(duty_cycle_left);
    reverse_fast_decay_right(duty_cycle_right);
}

void rotate_clockwise(uint8_t duty_cycle_left, uint8_t duty_cycle_right)
{
    forward_fast_decay_left(duty_cycle_left);
    reverse_fast_decay_right(duty_cycle_right);
}

void rotate_counterclockwise(uint8_t duty_cycle_left, uint8_t duty_cycle_right)
{
    forward_fast_decay_left(duty_cycle_left);
    reverse_fast_decay_right(duty_cycle_right);
}

// </editor-fold>