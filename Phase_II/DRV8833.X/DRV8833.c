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
#define MOTOR_LEFT_A_SET_PWM(duty_cycle)  set_PWM2_duty_cycle(duty_cycle)   //!< Assign PWM2 Peripheral MOTOR1 A Control Signal
#define MOTOR_LEFT_B_SET_PWM(duty_cycle)  set_PWM3_duty_cycle(duty_cycle)   //!< Assign PWM3 Peripheral MOTOR1 B Control Signal
#define MOTOR_RIGHT_A_SET_PWM(duty_cycle) set_PWM5_duty_cycle(duty_cycle)   //!< Assign PWM5 Peripheral MOTOR2 A Control Signal
#define MOTOR_RIGHT_B_SET_PWM(duty_cycle) set_PWM4_duty_cycle(duty_cycle)   //!< Assign PWM4 Peripheral MOTOR2 B Control Signal

#define nSLEEP_TRIS TRISDbits.TRISD5    //!< Assign TRIS Register bit for nSLEEP pin
#define nFAULT_TRIS TRISDbits.TRISD6    //!< Assign TRIS Register bit for nSLEEP pin

#define CONFIGURE_nSLEEP {nSLEEP_TRIS = 0;}         //!< Configure nSLEEP as output
#define CONFIGURE_nFAULT {nFAULT_TRIS = 1;}         //!< Configure nFAULT as input

#define ENABLE_WPU_nFAULT {CNPUEbits.CNPUE15 = 1;}  //!< Enable Weak Pull Up on nFault Pin

/*******************************************************************************
 *                         CLASS METHODS
 ******************************************************************************/

void configure_DRV8833_interface(void)
{
    DISABLE_DRV8833;

    // Configure I/O
    CONFIGURE_nSLEEP;   
    CONFIGURE_nFAULT;   
    ENABLE_WPU_nFAULT;
    
    // Configure current monitoring
    adc_peripheral_init();
    
    init_ADC_ch(M1_ISEN_ADC_CH);
    init_ADC_ch(M2_ISEN_ADC_CH);
   
    // Configure PWM
    config_Timer2();
    
    output_compare_2_init();
    output_compare_3_init();
    output_compare_4_init();
    output_compare_5_init();
    
    // Set all motor to open state
    open_all_motors();
}

void enable_DRV8833(void)
{
    ENABLE_DRV8833;     // first instruction. Internal DRV8833 Logic requires some time to init
    
    ENABLE_ADC;
            
    ENABLE_TIMER_2;
            
    ENABLE_OUTPUT_COMPARE_PERIPHERAL_2;
    ENABLE_OUTPUT_COMPARE_PERIPHERAL_3;
    ENABLE_OUTPUT_COMPARE_PERIPHERAL_4;
    ENABLE_OUTPUT_COMPARE_PERIPHERAL_5;
}

uint8_t DRV8833_fault_condition(void)
{
    if(nFAULT == DRV8833_ERROR)
    {
        open_all_motors();
    }
    return !(nFAULT);
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

/* FAST DECAY */
void move_forward_fast_decay(uint8_t duty_cycle_left, uint8_t duty_cycle_right)
{
    forward_fast_decay_left(duty_cycle_left);
    forward_fast_decay_right(duty_cycle_right);
}

void move_backwards_fast_decay(uint8_t duty_cycle_left, uint8_t duty_cycle_right)
{
    reverse_fast_decay_left(duty_cycle_left);
    reverse_fast_decay_right(duty_cycle_right);
}

void rotate_clockwise_fast_decay(uint8_t duty_cycle_left, uint8_t duty_cycle_right)
{
    forward_fast_decay_left(duty_cycle_left);
    reverse_fast_decay_right(duty_cycle_right);
}

void rotate_counterclockwise_fast_decay(uint8_t duty_cycle_left, uint8_t duty_cycle_right)
{
    reverse_fast_decay_left(duty_cycle_left);
    forward_fast_decay_right(duty_cycle_right);
}


/* SLOW DECAY */
void move_forward_slow_decay(uint8_t duty_cycle_left, uint8_t duty_cycle_right)
{
    forward_slow_decay_left(duty_cycle_left);
    forward_slow_decay_right(duty_cycle_right);
}

void move_backwards_slow_decay(uint8_t duty_cycle_left, uint8_t duty_cycle_right)
{
    reverse_slow_decay_left(duty_cycle_left);
    reverse_slow_decay_right(duty_cycle_right);
}

void rotate_clockwise_slow_decay(uint8_t duty_cycle_left, uint8_t duty_cycle_right)
{
    forward_slow_decay_left(duty_cycle_left);
    reverse_slow_decay_right(duty_cycle_right);
}

void rotate_counterclockwise_slow_decay(uint8_t duty_cycle_left, uint8_t duty_cycle_right)
{
    reverse_slow_decay_left(duty_cycle_left);
    forward_slow_decay_right(duty_cycle_right);
}

// </editor-fold>