/** 
 * \file   DRV8833.h
 * \brief  DRV8833 module device driver Header file
 * 
 * \author Pedro Martins
 * \date   Created on May 5, 2018, 6:11 PM
 */


#ifndef MOTORS_H
#define	MOTORS_H

#include <xc.h>

#include "../ADC.X/adc.h"
#include "../PWM.X/timer2.h"
#include "../PWM.X/pwm2.h"
#include "../PWM.X/pwm3.h"
#include "../PWM.X/pwm4.h"
#include "../PWM.X/pwm5.h"

/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define DRV8833_ERROR   0
#define DRV8833_SUCCESS 1

#define nSLEEP LATDbits.LATD5       //!< DRV8833 Sleep pin (active Low, input)
#define nFAULT PORTDbits.RD6        //!< DRV8833 Fault pin (active Low, output)

#define M1_ISEN_ADC_CH 13           //!< ADC Channel for curent measurement of motor 1
#define M2_ISEN_ADC_CH 14           //!< ADC Channel for curent measurement of motor 2

#define ENABLE_DRV8833  {nSLEEP = 1;}   //!< Enable DRV8833 module (drive nSleep pin high)
#define DISABLE_DRV8833 {nSLEEP = 0;}   //!< Disable DRV8833 module (drive nSleep pin low)

#define MIN_DUTY 0          //!< Mininum duty-cycle to be applied to the motors
#define MAX_DUTY 100        //!< Maximum duty-cycle to be applied to the motors

#define DRV8833_ERROR_MESSAGE "DRV8833 ERROR!\n"
/*******************************************************************************
 *                        FUNCTION HEADERS DEFINITION
 ******************************************************************************/


/** \brief Configures DRV8833 Interface
 * 
 * \pre    None.
 * \param  None.
 * \return None.
 * 
 * Configures the I/O pins required, the PWM modules and ADC.
 * 
 * 
 * \author Pedro Martins
 */
void configure_DRV8833_interface(void);

/** \brief Enables the DRV8833 Interface and all dependent peripherals
 * 
 * \pre    DRV8833 is configured.
 * \param  None.
 * \return None.
 * 
 * \author Pedro Martins
 */
void enable_DRV8833(void);

/** \brief DRV8833 Fault Condition Verification
 * 
 * \pre    DRV8833 is configured and enabled
 * \param  None.
 * \return DRV8833_SUCCESS if no fault condition has occurred
 * \return DRV8833_ERROR if any fault condition has occurred
 * 
 * \author Pedro Martins
 */
uint8_t DRV8833_fault_condition(void);

/** \brief Opens all motors using ON-OFF drive
 * 
 * \pre    DRV8833 is configured and enabled.
 * \param  None.
 * \return None.
 * 
 * \author Pedro Martins
 */
void open_all_motors(void);

/** \brief Brakes all motors using ON-OFF drive
 * 
 * \pre    DRV8833 is configured and enabled.
 * \param  None.
 * \return None.
 * 
 * \author Pedro Martins
 */
void brake_all_motors(void);

/** \brief Opens left motor using ON-OFF drive
 * 
 * \pre    DRV8833 is configured and enabled.
 * \param  None.
 * \return None.
 * 
 * \author Pedro Martins
 */
void open_left_motor(void);

/** \brief Opens right motor using ON-OFF drive
 * 
 * \pre    DRV8833 is configured and enabled.
 * \param  None.
 * \return None.
 * 
 * \author Pedro Martins
 */
void open_right_motor(void);

/** \brief Reverse movement on left motor using ON-OFF drive
 * 
 * \pre    DRV8833 is configured and enabled.
 * \param  None.
 * \return None.
 * 
 * \author Pedro Martins
 */
void reverse_left_motor(void);

/** \brief Reverse movement on right motor using ON-OFF drive
 * 
 * \pre    DRV8833 is configured and enabled.
 * \param  None.
 * \return None.
 * 
 * \author Pedro Martins
 */
void reverse_right_motor(void);

/** \brief Forward movement on left motor using ON-OFF drive
 * 
 * \pre    DRV8833 is configured and enabled.
 * \param  None.
 * \return None.
 * 
 * \author Pedro Martins
 */
void forward_left_motor(void);

/** \brief Forward movement on right motor using ON-OFF drive
 * 
 * \pre    DRV8833 is configured and enabled.
 * \param  None.
 * \return None.
 * 
 * \author Pedro Martins
 */
void forward_right_motor(void);

/** \brief Brake left motor using ON-OFF drive
 * 
 * \pre    DRV8833 is configured and enabled.
 * \param  None.
 * \return None.
 * 
 * \author Pedro Martins
 */
void brake_left_motor(void);

/** \brief Brake right motor using ON-OFF drive
 * 
 * \pre    DRV8833 is configured and enabled.
 * \param  None.
 * \return None.
 * 
 * \author Pedro Martins
 */
void brake_right_motor(void);

/** \brief Forward movement on left motor using fast decay mode
 * 
 * \pre    DRV8833 is configured and enabled.
 * \param  duty_cycle Desired motor dutycycle \f$\in [0, 100]\f$
 * \return None.
 * 
 * \author Pedro Martins
 */
void forward_fast_decay_left(uint8_t duty_cycle);

/** \brief Forward movement on left motor using slow decay mode
 * 
 * \pre    DRV8833 is configured and enabled.
 * \param  duty_cycle Desired motor dutycycle \f$\in [0, 100]\f$
 * \return None.
 * 
 * \author Pedro Martins
 */
void forward_slow_decay_left(uint8_t duty_cycle);

/** \brief Reverse movement on left motor using fast decay mode
 * 
 * \pre    DRV8833 is configured and enabled.
 * \param  duty_cycle Desired motor dutycycle \f$\in [0, 100]\f$
 * \return None.
 * 
 * \author Pedro Martins
 */
void reverse_fast_decay_left(uint8_t duty_cycle);

/** \brief Reverse movement on left motor using slow decay mode
 * 
 * \pre    DRV8833 is configured and enabled.
 * \param  duty_cycle Desired motor dutycycle \f$\in [0, 100]\f$
 * \return None.
 * 
 * \author Pedro Martins
 */
void reverse_slow_decay_left(uint8_t duty_cycle);

/** \brief Forward movement on right motor using fast decay mode
 * 
 * \pre    DRV8833 is configured and enabled.
 * \param  duty_cycle Desired motor dutycycle \f$\in [0, 100]\f$
 * \return None.
 * 
 * \author Pedro Martins
 */
void forward_fast_decay_right(uint8_t duty_cycle);

/** \brief Forward movement on right motor using slow decay mode
 * 
 * \pre    DRV8833 is configured and enabled.
 * \param  duty_cycle Desired motor dutycycle \f$\in [0, 100]\f$
 * \return None.
 * 
 * \author Pedro Martins
 */
void forward_slow_decay_right(uint8_t duty_cycle);

/** \brief Reverse movement on right motor using fast decay mode
 * 
 * \pre    DRV8833 is configured and enabled.
 * \param  duty_cycle Desired motor dutycycle \f$\in [0, 100]\f$
 * \return None.
 * 
 * \author Pedro Martins
 */
void reverse_fast_decay_right(uint8_t duty_cycle);

/** \brief Reverse movement on right motor using slow decay mode
 * 
 * \pre    DRV8833 is configured and enabled.
 * \param  duty_cycle Desired motor dutycycle \f$\in [0, 100]\f$
 * \return None.
 * 
 * \author Pedro Martins
 */
void reverse_slow_decay_right(uint8_t duty_cycle);
#endif	/* MOTORS_H */

