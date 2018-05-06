/** 
 * \file   pwm1.h
 * \brief  PWM 1 Module Header file
 * \pre    Uses Timer 2
 * 
 * \author Pedro Martins
 * \date   Created on April 8, 2018, 12:06 PM
 */

#ifndef PWM1_H
#define	PWM1_H

/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define ENABLE_OUTPUT_COMPARE_PERIPHERAL_1  {OC1CONbits.ON = 1;}    //!< Enable PWM Module 1
#define DISABLE_OUTPUT_COMPARE_PERIPHERAL_1 {OC1CONbits.ON = 0;}    //!< Disable PWM Module 1

#define PWM1_INITIAL_DUTY 0x0000    //!< Initial PWM1 duty-cycle 


/*******************************************************************************
 *                        FUNCTION HEADERS DEFINITION
 ******************************************************************************/

/** \brief Configures Output Compare Module 1
 * 
 * \pre    Timer 2 must configured to be used by the PWM module
 * \param  None
 * \return None
 * 
 * \author Pedro Martins
 */
void output_compare_1_init(void) ;

/** \brief Set duty-cycle of PWM Module 1
 * 
 * \pre    Output and Compare Peripheral 1 must be configured as a PWM Module and Enabled.
 * \pre    Timer 2 must configured to be used by the PWM module
 * 
 * \param  duty_cycle Desired duty-cycle for PWM
 * 
 * \return PWM_SUCCESS if duty-cycle is valid, i.e., \f$duty\_cycle \in [0, 100]\f$
 * \return PWM_ERROR if duty-cycle is invalid, i.e, \f$duty\_cycle > 100\f$
 * 
 * \author Pedro Martins
 */
uint8_t set_PWM1_duty_cycle(uint8_t duty_cycle);

#endif	/* PWM1_H */

