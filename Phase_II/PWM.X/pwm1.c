/** 
 * \file   pwm1.c
 * \brief  Pulse Width Modulation Module 1 Configuration C file
 * 
 * \author Pedro Martins
 * \date   Created on April 2, 2018, 7:50 PM
 */


#include <xc.h>
#include "../global.h"
#include "pwm.h"
#include "pwm1.h"


/*******************************************************************************
 *                         CLASS METHODS
 ******************************************************************************/

void output_compare_1_init(void) 
{
    /***************************************************************************
     *                    OUTPUT AND COMPARE MODULE                            *
     **************************************************************************/
    
    DISABLE_OUTPUT_COMPARE_PERIPHERAL_1;     // Disable PWM output pin while doing the setup now

    
    /* Select 16 bit timer source
     * 
     * 32-bit Compare Mode bit
     *   1 = OCxR<31:0> and/or OCxRS<31:0> are used for comparisons to the 32-bit timer source
     *   0 = OCxR<15:0> and OCxRS<15:0> are used for comparisons to the 16-bit timer source
     */
    OC1CONbits.OC32 = 0;
    
    /* Enable PWM module operation when CPU enters IDLE mode
     * 
     * Stop in IDLE Mode bit
     *   1 = Discontinue operation when CPU enters IDLE mode
     *   0 = Continue operation in IDLE mode
     */
    OC1CONbits.SIDL = 0;
    
    /* Use Timer2 as PWM clock source
     * 
     * Output Compare Timer Select bit
     *   1 = Timer3 is the clock source for this OCMP module
     *   0 = Timer2 is the clock source for this OCMP module
     */
    OC1CONbits.OCTSEL = 0;
    
    /* Output and Compare Module operates as a PWM module. Fault pin is disable
     * 
     * Output Compare Mode Select bits
     *   111 = PWM mode on OCx; Fault pin enabled
     *   110 = PWM mode on OCx; Fault pin disabled
     *   101 = Initialize OCx pin low; generate continuous output pulses on OCx pin
     *   100 = Initialize OCx pin low; generate single output pulse on OCx pin
     *   011 = Compare event toggles OCx pin
     *   010 = Initialize OCx pin high; compare event forces OCx pin low
     *   001 = Initialize OCx pin low; compare event forces OCx pin high
     *   000 = Output compare peripheral is disabled but continues to draw current
     */
    OC1CONbits.OCM = 0b110;
    
    /***************************************************************************
     *                            INTERRUPTS                                   *
     **************************************************************************/
    
    /* Disable Output and Compare Interrupts for module 1
     * 
     * Output Compare 1 Interrupt Enable bit
     *   1 = Interrupt is enabled
     *   0 = Interrupt is disabled
     */
    IEC0bits.OC1IE = 0;
    
    /* Disable Interrupts priority for Output and Compare Module 1
     * 
     * OC1IP<2:0>: Output Compare 1 Interrupt Priority bits
     *   111 = Interrupt priority is 7
     *   110 = Interrupt priority is 6
     *   101 = Interrupt priority is 5
     *   100 = Interrupt priority is 4
     *   011 = Interrupt priority is 3
     *   010 = Interrupt priority is 2
     *   001 = Interrupt priority is 1
     *   000 = Interrupt is disabled
     */
    IPC1bits.OC1IP = 0b000;
    
    /* Select lowest interrupt subpriority
     * 
     * Output Compare 1 Interrupt Subpriority bits
     *   11 = Interrupt subpriority is 3
     *   10 = Interrupt subpriority is 2
     *   01 = Interrupt subpriority is 1
     *   00 = Interrupt subpriority is 0
     */
    IPC1bits.OC1IS = 0b00;
    
    /***************************************************************************
     *                               PWM                                 
     **************************************************************************/
    
    /* Set secondary output and compare register to zero duty cycle
     *
     * OCxRS: Output Compare x Secondary Compare Register
     *   OCxRS<31:16>: Upper 16 bits of 32-bit compare value when OC32 (OCxCON<5>) = 1
     *   OCxRS<15:0>:  Lower 16 bits of 32-bit compare value or entire 16 bits of 
     *                 16-bit compare value when OC32 = 0
     */
    OC1RS = PWM1_INITIAL_DUTY;
    
    /* Set main output and compare register to zero duty cycle
     *
     * OCxR: Output Compare ?x? Compare Register
     *   OCxR<31:16>: Upper 16 bits of 32-bit compare value, when OC32 (OCxCON<5>) = 1
     *   OCxR<15:0>:  Lower 16 bits of 32-bit compare value or entire 16 bits of 
     *                16-bit compare value when OC32 = 0
     */
    OC1R = PWM1_INITIAL_DUTY;
}


uint8_t set_PWM1_duty_cycle(uint8_t duty_cycle) 
{
    uint8_t exit_cond = PWM_SUCCESS;
    uint32_t new_OC1RS;
    
    if (duty_cycle > 100)
    {
        duty_cycle = 100;
        exit_cond = PWM_ERROR;
    }
    
    #ifdef PWM_ROUNDING
        new_OC1RS  = ( ( (PR2 * duty_cycle) * 10 / 100) + 5) / 10;
    #else
        new_OC1RS = (PR2 * duty_cycle) / 100;
    #endif 

    OC1RS = (uint16_t) (new_OC1RS & 0x0000FFFF);
    
    return exit_cond;
}
