/** 
 * \file   pwm5.h
 * \brief  PWM 5 Module Header file
 * \pre    Uses Timer 2
 * 
 * \author Pedro Martins
 * \date   Created on May 30, 2018, 01:17 AM
 */

#ifndef PWM5_H
#define	PWM5_H

/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define ENABLE_OUTPUT_COMPARE_PERIPHERAL_5  {OC5CONbits.ON = 1;}    //!< Enable PWM Module 5
#define DISABLE_OUTPUT_COMPARE_PERIPHERAL_5 {OC5CONbits.ON = 0;}    //!< Disable PWM Module 5

#define PWM5_INITIAL_DUTY 0x0000    //!< Initial PWM5 duty-cycle 


/*******************************************************************************
 *                        FUNCTION HEADERS DEFINITION
 ******************************************************************************/

/** \brief Configures Output Compare Module 5
 * 
 * \pre    Timer 2 must configured to be used by the PWM module
 * \param  None
 * \return None
 * 
 * \author Pedro Martins
 */
void output_compare_5_init(void) ;

/** \brief Set duty-cycle of PWM Module 5
 * 
 * \pre    Output and Compare Peripheral 5 must be configured as a PWM Module and Enabled.
 * \pre    Timer 2 must configured to be used by the PWM module
 * 
 * \param  duty_cycle Desired duty-cycle for PWM
 * 
 * \return PWM_SUCCESS if duty-cycle is valid, i.e., \f$duty\_cycle \in [0, 100]\f$
 * \return PWM_ERROR if duty-cycle is invalid, i.e, \f$duty\_cycle > 100\f$
 * 
 * \author Pedro Martins
 */
uint8_t set_PWM5_duty_cycle(uint8_t duty_cycle);

#endif	/* PWM5_H */

