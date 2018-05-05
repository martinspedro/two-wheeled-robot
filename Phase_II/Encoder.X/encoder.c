/** 
 * \file encoder.c
 * \brief Encoder Module configuration C file
 * 
 * \author Pedro Martins
 * \date Created on May 1, 2018, 5:11 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#include "../global.h"
#include "../interrupts.h"
#include "encoder.h"
#include "../UART.X/uart1.h"

#define USE_CHIPKIT

/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define RESET_IF_EXT_INT0 {IFS0bits.INT0IF = 0;}    //!< Reset Interrupt Flag for External Interrupt Pin 0 (INT0)
#define RESET_IF_EXT_INT1 {IFS0bits.INT1IF = 0;}    //!< Reset Interrupt Flag for External Interrupt Pin 1 (INT1)
#define RESET_IF_EXT_INT2 {IFS0bits.INT2IF = 0;}    //!< Reset Interrupt Flag for External Interrupt Pin 2 (INT2)
#define RESET_IF_EXT_INT3 {IFS0bits.INT3IF = 0;}    //!< Reset Interrupt Flag for External Interrupt Pin 3 (INT3)

#define EXT_INT_RISING_EDGE  1      //!< External Interrupt Edge Polarity sensible to Rising Edge Detection 
#define EXT_INT_FALLING_EDGE 0      //!< External Interrupt Edge Polarity sensible to Falling Edge Detection


#define ENCODER_LEFT_A   PORTEbits.RE8      //!< I/O Pin for A Encoder of Left Wheel  
#define ENCODER_LEFT_B   PORTEbits.RE9      //!< I/O Pin for B Encoder of Left Wheel  

#define ENCODER_RIGHT_A  PORTAbits.RA14     //!< I/O Pin for A Encoder of Right Wheel 
#define ENCODER_RIGHT_B  PORTAbits.RA15     //!< I/O Pin for B Encoder of Right Wheel 

#define TOGGLE_LEFT_A_ENC_EDGE {INTCONINV = 0x0002;}    //!< Toggle Interrupt on Change Edge Detection for Left Encoder A 
#define TOGGLE_LEFT_B_ENC_EDGE {INTCONINV = 0x0004;}    //!< Toggle Interrupt on Change Edge Detection for Left Encoder B

#ifdef USE_CHIPKIT
    #define ENCODER_LEFT_A   PORTEbits.RE8      //!< I/O Pin for A Encoder of Left Wheel  
    #define ENCODER_LEFT_B   PORTEbits.RE9      //!< I/O Pin for B Encoder of Left Wheel  
#else 
    #define ENCODER_LEFT_A   PORTEbits.RE8      //!< I/O Pin for A Encoder of Left Wheel  
    #define ENCODER_LEFT_B   PORTEbits.RE9      //!< I/O Pin for B Encoder of Left Wheel  

    #define ENCODER_RIGHT_A  PORTAbits.RA14     //!< I/O Pin for A Encoder of Right Wheel 
    #define ENCODER_RIGHT_B  PORTAbits.RA15     //!< I/O Pin for B Encoder of Right Wheel 
#endif

/*******************************************************************************
 *                       CLASS VARIABLES DEFINITION
 ******************************************************************************/

volatile enum  State CS_left;
static volatile enum  State CS_right;

volatile uint8_t print_flag = 0;
volatile int16_t pulse_count_L = 0;
volatile int16_t pulse_count_R = 0;

volatile uint8_t invalid_encoder_transition;


const int8_t QUAD_ENC_LUT_A[4] = {+1, -1, -1, +1};
const int8_t QUAD_ENC_LUT_B[4] = {-1, +1, +1, -1};


/*******************************************************************************
 *                         CLASS METHODS
 ******************************************************************************/
void configure_external_interrupts(void)
{
    // Disable External Interrupts
    DISABLE_EXT_INT1;
    DISABLE_EXT_INT2;
    
    // Reset Interrupt Flags
    RESET_IF_EXT_INT0;
    RESET_IF_EXT_INT1;
    
    // Configure External Interrupts Edge Detection as Rising Edge
    INTCONbits.INT1EP = EXT_INT_RISING_EDGE;
    INTCONbits.INT2EP = EXT_INT_RISING_EDGE;
    
    // Set Priority and sub-priority levels for INT1 & INT2
    IPC1bits.INT1IP = EXT_INT1_IPL  & 0x07;
    IPC1bits.INT1IS = EXT_INT1_ISPL & 0x03;
    
    IPC2bits.INT2IP = EXT_INT2_IPL  & 0x07;
    IPC2bits.INT2IS = EXT_INT2_ISPL & 0x03;
}


void init_encoder_state(void)
{
    CS_left  = ( (ENCODER_LEFT_A  << 1) | ENCODER_LEFT_B  );
    CS_right = ( (ENCODER_RIGHT_A << 1) | ENCODER_RIGHT_B );           
}

/** \brief ISR for A Encoder of Left Motor 
 * 
 * \pre    Global and External Interrupts must be configured and enabled
 * \param  None.
 * \return None.
 * 
 * Interruption Service Routine for External Interrupt Pin 1 (INT1)
 * The interruption source priority is 6 and the compiler must write software to
 * perform the context switching
 * 
 * \author Pedro Martins
 */
void __ISR(_EXTERNAL_1_VECTOR, IPL6SOFT) LEFT_MOTOR_ENCODER_A(void)
{
    LATBbits.LATB4 = 1;
    
    //pulse_count_L = pulse_count_L + QUAD_ENC_LUT_A[(INTCONbits.INT1EP << 2) + ENCODER_LEFT_B];
    
    // if a rising edge was detected
    
    if(INTCONbits.INT1EP == EXT_INT_RISING_EDGE)        
    {
        // if the current state is '00' and B = 0, positive movement
        if( (CS_left == S0) && (ENCODER_LEFT_B == 0) )   
        {
            CS_left = S2;
            pulse_count_L++;
        }
        // if the current state is '01' and B = 1, negative movement
        else if ( (CS_left == S1) && (ENCODER_LEFT_B == 1) ) 
        {
            CS_left = S3;
            pulse_count_L--;
        }
        else
        {
            invalid_encoder_transition = ENCODER_ERROR;
        }   
    }
    else if(INTCONbits.INT1EP == EXT_INT_FALLING_EDGE) 
    {
        // if the current state is '11' and B = 0, positive movement
        if( (CS_left == S2) && (ENCODER_LEFT_B == 0) )   
        {
            CS_left = S0;
            pulse_count_L--;
        }
        // if the current state is '10' and B = 1, negative movement
        else if ( (CS_left == S3) && (ENCODER_LEFT_B == 1) ) 
        {
            CS_left = S1;
            pulse_count_L++;
        }
        else
        {
            invalid_encoder_transition = ENCODER_ERROR;
        }   
    }
    else
    {
        invalid_encoder_transition = ENCODER_ERROR;

    }
    
    
    print_flag = 1;
    TOGGLE_LEFT_A_ENC_EDGE;     // Invert edge detection polarity
    RESET_IF_EXT_INT1;
    LATBbits.LATB4 = 0;
    
}


/** \brief ISR for B Encoder of Left Motor 
 * 
 * \pre    Global and External Interrupts must be configured and enabled
 * \param  None.
 * \return None.
 * 
 * Interruption Service Routine for External Interrupt Pin 2 (INT2)
 * The interruption source priority is 6 and the compiler must write software to
 * perform the context switching
 * 
 * \author Pedro Martins
 */
void __ISR(_EXTERNAL_2_VECTOR, IPL6SOFT) LEFT_MOTOR_ENCODER_B(void)
{
    LATBbits.LATB4 = 1;
    
    // if a rising edge was detected
    if(INTCONbits.INT2EP == EXT_INT_RISING_EDGE)        
    {
        // if the current state is '10' and A = 0, positive movement
        if( (CS_left == S0) && (ENCODER_LEFT_A == 0) )   
        {
            CS_left = S1;
            pulse_count_L--;
        }
        // if the current state is '00' and B = 1, negative movement
        else if ( (CS_left == S2) && (ENCODER_LEFT_A == 1) ) 
        {
            CS_left = S3;
            pulse_count_L++;
        }
        else
        {
            invalid_encoder_transition = ENCODER_ERROR;
        }   
    }
    else if(INTCONbits.INT2EP == EXT_INT_FALLING_EDGE) 
    {
        // if the current state is '00' and B = 0, positive movement
        if( (CS_left == S1) && (ENCODER_LEFT_A == 0) )   
        {
            CS_left = S0;
            pulse_count_L++;
        }
        // if the current state is '01' and B = 1, negative movement
        else if ( (CS_left == S3) && (ENCODER_LEFT_A == 1) ) 
        {
            CS_left = S2;
            pulse_count_L--;
        }
        else
        {
            invalid_encoder_transition = ENCODER_ERROR;
        }   
    } 
    else
    {
        invalid_encoder_transition = ENCODER_ERROR;
    }   

    
    print_flag = 1;
    TOGGLE_LEFT_B_ENC_EDGE;     // Invert edge detection polarity
    RESET_IF_EXT_INT2;
    LATBbits.LATB4 = 0;
}