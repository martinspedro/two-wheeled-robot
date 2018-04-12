/* 
 * File:   pwm.c
 * Author: martinspedro
 *
 * Created on April 2, 2018, 7:50 PM
 * 
 * @brief Uses Timer2
 */


#include <xc.h>
#include "../global.h"

/* @brief Motors PWM configuration routine
 * 
 * @author Pedro Martins
 */
void PWM_init() {
    /***************************************************************************
     *                    OUTPUT AND COMPARE MODULE                            *
     **************************************************************************/
    
    
    /* Disable PWM output pin while doing the setup now
     * 
     * Output Compare Peripheral On bit
     *   1 = Output Compare peripheral is enabled.
     *   0 = Output Compare peripheral is disabled and not drawing current.
     */
    OC1CONbits.ON = 0;
    
    /* Select 16 bit timer source
     * 
     * 32-bit Compare Mode bit
     *   1 = OCxR<31:0> and/or OCxRS<31:0> are used for comparisions to the 32-bit timer source
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
    //OC1CONbits.OCTSEL = 0;
    
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
    
    /* Set Period of PWM
     * 
     * Period Register
     *    PR<15:0>: 16-bit Timer2 period match value. Provides lower half of the
     *              32-bit period match value when Timer2 and Timer3 are 
     *              configured to form a 32-bit timer.
     */
     PR2 = 767;
     
     /* Set secondary output and compare register to half the duty cycle
     *
     * OCxRS: Output Compare x Secondary Compare Register
     *   OCxRS<31:16>: Upper 16 bits of 32-bit compare value when OC32 (OCxCON<5>) = 1
     *   OCxRS<15:0>:  Lower 16 bits of 32-bit compare value or entire 16 bits of 
     *                 16-bit compare value when OC32 = 0
     */
    OC1RS = 399;
    
    /* Set main output and compare register to half the duty cycle
     *
     * OCxR: Output Compare ?x? Compare Register
     *   OCxR<31:16>: Upper 16 bits of 32-bit compare value, when OC32 (OCxCON<5>) = 1
     *   OCxR<15:0>:  Lower 16 bits of 32-bit compare value or entire 16 bits of 
     *                16-bit compare value when OC32 = 0
     */
    OC1R = 0x0000;
    
    
    
    
   
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
     *                              TIMER 2                                    *
     **************************************************************************/
    
    /* Enable Timer 2
     * 
     * TMR2 On bit
     *   1 = Peripheral is enabled
     *   0 = Peripheral is disabled
     */
    T2CONbits.ON = 1;
    
    /* Enable Timer2 module operation when CPU enters IDLE mode
     * 
     * Stop in IDLE Mode bit
     *   1 = Discontinue operation when CPU enters IDLE mode
     *   0 = Continue operation in IDLE mode
     */
    T2CONbits.SIDL = 0;
    
    /* Disable Timer 2 Gate Accumulation
     * 
     * Timer Gated Time Accumulation Enable bit
     *   When TCS = 1:
     *      This bit is ignored and reads as ?0?
     *   When TCS = ?0?:
     *      1 = Gated time accumulation is enabled
     *      0 = Gated time accumulation is disabled
     */
    T2CONbits.TGATE = 0;
    
    /* Select 1:1 prescaler
     * 
     * Timer Input Clock Prescale Select bits
     *   111 = 1:256 prescale value
     *   110 = 1:64  prescale value
     *   101 = 1:32  prescale value
     *   100 = 1:16  prescale value
     *   011 = 1:8   prescale value
     *   010 = 1:4   prescale value
     *   001 = 1:2   prescale value
     *   000 = 1:1   prescale value
     */
    T2CONbits.TCKPS = 0b000;
    
    /* Select independent operation from Timer 2 and 3
     * 
     * 32-bit Timer Mode Select bits
     *   1 = TMR2 and TMR3 form a 32-bit timer
     *   0 = TMR2 and TMR3 are separate 16-bit timers
     * 
     */
    T2CONbits.T32 = 0;
    
    /* Select Internal Peripheral Clock as Clock Source
     * 
     * TMR2 Clock Source Select bit
     *   1 = External clock from T2CK pin
     *   0 = Internal peripheral clock
     */
    T2CONbits.TCS = 0;
}

/* @brief Enable Output and Compare Module 1
 * 
 * @author Pedro Martins
 */
void PWM_enable() {
     /* Output Compare Peripheral On bit
      *  1 = Output Compare peripheral is enabled.
      *  0 = Output Compare peripheral is disabled and not drawing current.
      */
    OC1CONbits.ON = 1;    
}

/* @brief Set duty-cycle for PWM
 * 
 * @author Pedro Martins
 */
void set_duty_cycle(uint16_t duty) {
    uint32_t new_OC1RS; 
    //new_OC1RS  = ( ( (PR2 * duty) * 10 / 100) + 5) / 10;
    new_OC1RS = (PR2 * duty) / 100;
    OC1RS = (uint16_t) (new_OC1RS & 0x0000FFFF);
}
