/** 
 * \file   pwm3.h
 * \brief  PWM 3 Module Header file
 * \pre    Uses Timer 2
 * 
 * \author Pedro Martins
 * \date   Created on May 6, 2018, 9:30 AM
 */
#ifndef PWM3_H
#define	PWM3_H

/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define ENABLE_OUTPUT_COMPARE_PERIPHERAL_3  {OC3CONbits.ON = 1;}    //!< Enable PWM Module 3
#define DISABLE_OUTPUT_COMPARE_PERIPHERAL_3 {OC3CONbits.ON = 0;}    //!< Disable PWM Module 3

#define PWM3_INITIAL_DUTY 0x0000    //!< Initial PWM3 duty-cycle


/*******************************************************************************
 *                        FUNCTION HEADERS DEFINITION
 ******************************************************************************/

/** \brief Configures Output Compare Module 3
 * 
 * \pre    Timer 2 must configured to be used by the PWM module
 * \param  None
 * \return None
 * 
 * \author Pedro Martins
 */
void output_compare_3_init(void) ;

/** \brief Set duty-cycle of PWM Module 3
 * 
 * \pre    Output and Compare Peripheral 3 must be configured as a PWM Module and Enabled.
 * \pre    Timer 2 must configured to be used by the PWM module
 * 
 * \param  duty_cycle Desired duty-cycle for PWM
 * 
 * \return PWM_SUCCESS if duty-cycle is valid, i.e., \f$duty\_cycle \in [0, 100]\f$
 * \return PWM_ERROR if duty-cycle is invalid, i.e, \f$duty\_cycle > 100\f$
 * 
 * \author Pedro Martins
 */
uint8_t set_PWM3_duty_cycle(uint8_t duty_cycle);

#endif	/* PWM3_H */

