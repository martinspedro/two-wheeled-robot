/** 
 * \file   pwm.h
 * \brief  Pulse Width Modulation Global Definitions
 * 
 * \author Pedro Martins
 * \date   Created on May 6, 2018, 9:44 AM
 */

#ifndef PWM_H
#define	PWM_H

#define PWM_ERROR   1       //!< PWM Functions return in case of error
#define PWM_SUCCESS 0       //!< PWM Functions return in case of success

#define FREQ_PWM    52080   //!< Desired Frequency for all PWM modules


/** \brief Disables or Enables PWM duty-cycle register value rounding
 * If the macro is defined, the value used in the PWM register is rounded to the 
 * nearest integer.
 * 
 * If undefined, the duty-cycle register value is truncated and rounded to the 
 * integer less or equal to the given decimal number
 */
#undef  OCxRS_ROUNDING      

#endif	/* PWM_H */

