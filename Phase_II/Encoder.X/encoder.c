/** 
 * \file   encoder.c
 * \brief  Encoder Module configuration C file
 * 
 * \author Pedro Martins
 * \date   Created on May 1, 2018, 5:11 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#include "../global.h"
#include "../interrupts.h"
#include "encoder.h"



// #define DEBUG               //!< If defined, debugs Encoder State throught LEDs
// #define DEBUG_WITH_UART     //!< If defined, debugs Encoders State throught UART

/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define RESET_IF_EXT_INT1 {IFS0bits.INT1IF = 0;}    //!< Reset Interrupt Flag for External Interrupt Pin 1 (INT1)
#define RESET_IF_EXT_INT2 {IFS0bits.INT2IF = 0;}    //!< Reset Interrupt Flag for External Interrupt Pin 2 (INT2)
#define RESET_IF_EXT_INT3 {IFS0bits.INT3IF = 0;}    //!< Reset Interrupt Flag for External Interrupt Pin 3 (INT3)
#define RESET_IF_EXT_INT4 {IFS0bits.INT4IF = 0;}    //!< Reset Interrupt Flag for External Interrupt Pin 4 (INT4)

#define TOGGLE_LEFT_A_ENC_EDGE  {INTCONINV = 0x0002;}    //!< Toggle Interrupt on Change Edge Detection for Left Encoder A 
#define TOGGLE_LEFT_B_ENC_EDGE  {INTCONINV = 0x0004;}    //!< Toggle Interrupt on Change Edge Detection for Left Encoder B
#define TOGGLE_RIGHT_A_ENC_EDGE {INTCONINV = 0x0008;}    //!< Toggle Interrupt on Change Edge Detection for Right Encoder A 
#define TOGGLE_RIGHT_B_ENC_EDGE {INTCONINV = 0x0010;}    //!< Toggle Interrupt on Change Edge Detection for Right Encoder B

#define ENCODER_LEFT_A   PORTEbits.RE8      //!< I/O Pin for A Encoder of Left Wheel  
#define ENCODER_LEFT_B   PORTEbits.RE9      //!< I/O Pin for B Encoder of Left Wheel  
#define ENCODER_RIGHT_A  PORTAbits.RA14     //!< I/O Pin for A Encoder of Right Wheel 
#define ENCODER_RIGHT_B  PORTAbits.RA15     //!< I/O Pin for B Encoder of Right Wheel 

#define EXT_INT1_IPL  6     //!< External Interrupt Pin 1 Priority Level     
#define EXT_INT1_ISPL 0     //!< External Interrupt Pin 1 Sub-Priority Level 
#define EXT_INT2_IPL  6     //!< External Interrupt Pin 2 Priority Level     
#define EXT_INT2_ISPL 0     //!< External Interrupt Pin 2 Sub-Priority Level 
#define EXT_INT3_IPL  6     //!< External Interrupt Pin 3 Priority Level     
#define EXT_INT3_ISPL 0     //!< External Interrupt Pin 3 Sub-Priority Level 
#define EXT_INT4_IPL  6     //!< External Interrupt Pin 4 Priority Level     
#define EXT_INT4_ISPL 0     //!< External Interrupt Pin 4 Sub-Priority Level 

#define EXT_INT_RISING_EDGE  1      //!< External Interrupt Edge Polarity sensible to Rising Edge Detection 
#define EXT_INT_FALLING_EDGE 0      //!< External Interrupt Edge Polarity sensible to Falling Edge Detection


/*******************************************************************************
 *                       CLASS VARIABLES DEFINITION
 ******************************************************************************/
enum Quad_Enc_State     //!< Quadrature Encoder State Machine Possible States
{
    S0 = 0b00,          //!< Left Encoder Low,  Right Encoder Low
    S1 = 0b01,          //!< Left Encoder Low,  Right Encoder High
    S2 = 0b10,          //!< Left Encoder High, Right Encoder Low
    S3 = 0b11           //!< Left Encoder High, Right Encoder High
};

/** \brief Quadrature Encoder LUT for Encoder signal A transitions
 * LookUp Table used to actualize pulse count if Encoder Signal A toggles its value
 */
const int8_t QUAD_ENC_LUT_A[4] = {-1, +1, +1, -1};      

/** \brief Quadrature Encoder LUT for Encoder signal A transitions
 * LookUp Table used to actualize pulse count if Encoder Signal A toggles its value
 */
const int8_t QUAD_ENC_LUT_B[4] = {+1, -1, -1, +1};


volatile enum  Quad_Enc_State CS_left;      //!< Left Encoder Current State Variable
volatile enum  Quad_Enc_State CS_right;     //!< Right Encoder Current State Variable


volatile int16_t pulse_count_L = 0;         
volatile int16_t pulse_count_R = 0;

/*******************************************************************************
 *                         CLASS METHODS
 ******************************************************************************/
void configure_external_interrupts(void)
{
    // Disable External Interrupts
    DISABLE_EXT_INT1;
    DISABLE_EXT_INT2;
    DISABLE_EXT_INT3;
    DISABLE_EXT_INT4;
    
    // Reset Interrupt Flags
    RESET_IF_EXT_INT1;
    RESET_IF_EXT_INT2;
    RESET_IF_EXT_INT3;
    RESET_IF_EXT_INT4;
    
    // Configure External Interrupts Edge Detection as Rising Edge
    INTCONbits.INT1EP = EXT_INT_RISING_EDGE;
    INTCONbits.INT2EP = EXT_INT_RISING_EDGE;
    INTCONbits.INT3EP = EXT_INT_RISING_EDGE;
    INTCONbits.INT4EP = EXT_INT_RISING_EDGE;
    
    // Set Priority and sub-priority levels for INT1 & INT2
    IPC1bits.INT1IP = EXT_INT1_IPL  & 0x07;
    IPC1bits.INT1IS = EXT_INT1_ISPL & 0x03;
    
    IPC2bits.INT2IP = EXT_INT2_IPL  & 0x07;
    IPC2bits.INT2IS = EXT_INT2_ISPL & 0x03;
    
    IPC3bits.INT3IP = EXT_INT3_IPL  & 0x07;
    IPC3bits.INT3IS = EXT_INT3_ISPL & 0x03;
    
    IPC4bits.INT4IP = EXT_INT4_IPL  & 0x07;
    IPC4bits.INT4IS = EXT_INT4_ISPL & 0x03;
}


void init_encoder_state(void)
{
    DISABLE_ENCODERS;
    CS_left  = ( (ENCODER_LEFT_A  << 1) | ENCODER_LEFT_B  );
    CS_right = ( (ENCODER_RIGHT_A << 1) | ENCODER_RIGHT_B );           
    ENABLE_ENCODERS;
}

void reset_enc_pulse_cnt(void)
{
    DISABLE_ENCODERS;
    pulse_count_L = 0;
    pulse_count_R = 0;
    ENABLE_ENCODERS;
}


/** \brief ISR for Encoder A of Left Motor 
 * 
 * \pre    Global and External Interrupts must be configured and enabled
 * \pre    External Interrupts must be configured and enabled
 * 
 * \param  None.
 * \return None.
 * 
 * Interruption Service Routine for External Interrupt Pin 1 (INT1)
 * The INT1 is connected to the Signal A from the Encoder of the Left Motor
 * 
 * The Interruption Priority Level is 6 and the compiler must write software to
 * perform the context switching (IPL6SOFT)
 * 
 * \author Pedro Martins
 */
void __ISR(_EXTERNAL_1_VECTOR, IPL6SOFT) LEFT_MOTOR_ENCODER_A(void)
{
    #ifdef DEBUG
        LATBbits.LATB4 = 1;
        LATBbits.LATB5 = CS_left & 0x01;
        LATBbits.LATB6 = (CS_left & 0x02) >> 1;
    #endif

    CS_left = (INTCONbits.INT1EP == EXT_INT_RISING_EDGE) ? (CS_left | 0b10) : (CS_left & 0b01);
    pulse_count_L += QUAD_ENC_LUT_A[ (INTCONbits.INT1EP << 1) + ENCODER_LEFT_B ];
    
    #ifdef DEBUG_WITH_UART
        put_char( (CS_left & 0x01) + 0x30);
        put_char( ( (CS_left & 0x02) >> 1 ) + 0x30);
        put_char('\n');
    #endif
    
    TOGGLE_LEFT_A_ENC_EDGE;     // Invert edge detection polarity
    RESET_IF_EXT_INT1;
    
    #ifdef DEBUG
        LATBbits.LATB4 = 0;
    #endif
}


/** \brief ISR for Encoder B of Left Motor 
 * 
 * \pre    Global and External Interrupts must be configured and enabled
 * \pre    External Interrupts must be configured and enabled
 * 
 * \param  None.
 * \return None.
 * 
 * Interruption Service Routine for External Interrupt Pin 2 (INT2)
 * The INT2 is connected to the Signal B from the Encoder of the Left Motor
 * 
 * The Interruption Priority Level is 6 and the compiler must write software to
 * perform the context switching (IPL6SOFT)
 * 
 * \author Pedro Martins
 */
void __ISR(_EXTERNAL_2_VECTOR, IPL6SOFT) LEFT_MOTOR_ENCODER_B(void)
{
    #ifdef DEBUG
        LATBbits.LATB4 = 1;
        LATBbits.LATB5 = CS_left & 0x01;
        LATBbits.LATB6 = (CS_left & 0x02) >> 1;
    #endif
    
    CS_left = (INTCONbits.INT2EP == EXT_INT_RISING_EDGE) ? (CS_left | 0b01) : (CS_left & 0b10);
    pulse_count_L += QUAD_ENC_LUT_B[ (INTCONbits.INT2EP << 1) + ENCODER_LEFT_A ];
   
    #ifdef DEBUG_WITH_UART
        put_char( (CS_left & 0x01) + 0x30);
        put_char( ( (CS_left & 0x02) >> 1 ) + 0x30);
        put_char('\n');
    #endif
    
    TOGGLE_LEFT_B_ENC_EDGE;     // Invert edge detection polarity
    RESET_IF_EXT_INT2;
    
    #ifdef DEBUG
        LATBbits.LATB4 = 0;
    #endif
}


/** \brief ISR for Encoder A of Right Motor 
 * 
 * \pre    Global and External Interrupts must be configured and enabled
 * \pre    External Interrupts must be configured and enabled
 * 
 * \param  None.
 * \return None.
 * 
 * Interruption Service Routine for External Interrupt Pin 3 (INT3)
 * The INT3 is connected to the Signal A from the Encoder of the Right Motor
 * 
 * The Interruption Priority Level is 6 and the compiler must write software to
 * perform the context switching (IPL6SOFT)
 * 
 * \author Pedro Martins
 */
void __ISR(_EXTERNAL_3_VECTOR, IPL6SOFT) RIGHT_MOTOR_ENCODER_A(void)
{
    #ifdef DEBUG
        LATBbits.LATB4 = 1;
        LATBbits.LATB5 = CS_left & 0x01;
        LATBbits.LATB6 = (CS_left & 0x02) >> 1;
    #endif

    CS_right = (INTCONbits.INT3EP == EXT_INT_RISING_EDGE) ? (CS_right | 0b10) : (CS_right & 0b01);
    pulse_count_R += QUAD_ENC_LUT_A[ (INTCONbits.INT3EP << 1) + ENCODER_LEFT_B ];
    
    #ifdef DEBUG_WITH_UART
        put_char( (CS_right & 0x01) + 0x30);
        put_char( ( (CS_right & 0x02) >> 1 ) + 0x30);
        put_char('\n');
    #endif

    TOGGLE_RIGHT_A_ENC_EDGE;     // Invert edge detection polarity
    RESET_IF_EXT_INT3;
    
    #ifdef DEBUG
        LATBbits.LATB4 = 0;
    #endif
}


/** \brief ISR for Encoder B of Right Motor 
 * 
 * \pre    Global and External Interrupts must be configured and enabled
 * \pre    External Interrupts must be configured and enabled
 * 
 * \param  None.
 * \return None.
 * 
 * Interruption Service Routine for External Interrupt Pin 4 (INT4)
 * The INT4 is connected to the Signal B from the Encoder of the Right Motor
 * 
 * The Interruption Priority Level is 6 and the compiler must write software to
 * perform the context switching (IPL6SOFT)
 * 
 * \author Pedro Martins
 */
void __ISR(_EXTERNAL_4_VECTOR, IPL6SOFT) RIGHT_MOTOR_ENCODER_B(void)
{
    #ifdef DEBUG
        LATBbits.LATB4 = 1;
        LATBbits.LATB5 = CS_left & 0x01;
        LATBbits.LATB6 = (CS_left & 0x02) >> 1;
    #endif
    
    CS_right = (INTCONbits.INT4EP == EXT_INT_RISING_EDGE) ? (CS_right | 0b01) : (CS_right & 0b10);
    pulse_count_R += QUAD_ENC_LUT_B[ (INTCONbits.INT4EP << 1) + ENCODER_LEFT_A ];
   
    #ifdef DEBUG_WITH_UART
        put_char( (CS_right & 0x01) + 0x30);
        put_char( ( (CS_right & 0x02) >> 1 ) + 0x30);
        put_char('\n');
    #endif
        
    TOGGLE_RIGHT_B_ENC_EDGE;     // Invert edge detection polarity
    RESET_IF_EXT_INT4;
    
    #ifdef DEBUG
        LATBbits.LATB4 = 0;
    #endif
}
