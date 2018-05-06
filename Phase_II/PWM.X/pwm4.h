/** 
 * \file   pwm4.h
 * \brief  PWM 4 Module Header file
 * \pre    Uses Timer 2
 * 
 * \author Pedro Martins
 * \date   Created on May 6, 2018, 9:31 AM
 */


#ifndef PWM4_H
#define	PWM4_H

/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define ENABLE_OUTPUT_COMPARE_PERIPHERAL_4  {OC4CONbits.ON = 1;}    //!< Enable PWM Module 4
#define DISABLE_OUTPUT_COMPARE_PERIPHERAL_4 {OC4CONbits.ON = 0;}    //!< Disable PWM Module 4

#define PWM4_INITIAL_DUTY 0x0000    //!< Initial PWM4 duty-cycle


/*******************************************************************************
 *                        FUNCTION HEADERS DEFINITION
 ******************************************************************************/

/** \brief Configures Output Compare Module 4
 * 
 * \pre    Timer 2 must configured to be used by the PWM module
 * \param  None
 * \return None
 * 
 * \author Pedro Martins
 */
void output_compare_4_init(void) ;

/** \brief Set duty-cycle of PWM Module 4
 * 
 * \pre    Output and Compare Peripheral 4 must be configured as a PWM Module and Enabled.
 * \pre    Timer 2 must configured to be used by the PWM module
 * 
 * \param  duty_cycle Desired duty-cycle for PWM
 * 
 * \return PWM_SUCCESS if duty-cycle is valid, i.e., \f$duty\_cycle \in [0, 100]\f$
 * \return PWM_ERROR if duty-cycle is invalid, i.e, \f$duty\_cycle > 100\f$
 * 
 * \author Pedro Martins
 */
uint8_t set_PWM4_duty_cycle(uint8_t duty_cycle);

#endif	/* PWM4_H */

