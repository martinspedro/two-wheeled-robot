/** 
 * \file   encoder.h
 * \brief  Encoder configuration  file
 * 
 * \author Pedro Martins
 * \date   Created on May 1, 2018, 5:11 PM
 */

#ifndef ENCODER_H
#define	ENCODER_H

#include <xc.h>

/*******************************************************************************
 *                          DEBUG MODES
 ******************************************************************************/
// #define DEBUG               //!< If defined, debugs Encoder State throught LEDs
// #define DEBUG_WITH_UART     //!< If defined, debugs Encoders State throught UART


/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define ENABLE_EXT_INT1  {IEC0bits.INT1IE = 1;}     //!< Enables  INT1 interrupt 
#define DISABLE_EXT_INT1 {IEC0bits.INT1IE = 0;}     //!< Disables INT1 interrupt 
#define ENABLE_EXT_INT2  {IEC0bits.INT2IE = 1;}     //!< Enables  INT2 interrupt 
#define DISABLE_EXT_INT2 {IEC0bits.INT2IE = 0;}     //!< Disables INT2 interrupt 
#define ENABLE_EXT_INT3  {IEC0bits.INT3IE = 1;}     //!< Enables  INT3 interrupt 
#define DISABLE_EXT_INT3 {IEC0bits.INT3IE = 0;}     //!< Disables INT3 interrupt 
#define ENABLE_EXT_INT4  {IEC0bits.INT4IE = 1;}     //!< Enables  INT4 interrupt 
#define DISABLE_EXT_INT4 {IEC0bits.INT4IE = 0;}     //!< Disables INT4 interrupt 

#define ENABLE_ENCODERS   {ENABLE_EXT_INT1; ENABLE_EXT_INT2; ENABLE_EXT_INT3; ENABLE_EXT_INT4;}
#define DISABLE_ENCODERS  {DISABLE_EXT_INT1; DISABLE_EXT_INT2; DISABLE_EXT_INT3; DISABLE_EXT_INT4;}


#define ENCODER_ERROR   1   //!< Return value in case of Error
#define ENCODER_SUCCESS 0   //!< Return value in case of Success

extern volatile int16_t pulse_count_L;      //!< Pulse Count for Left Wheel
extern volatile int16_t pulse_count_R;      //!< Pulse Count for Right Wheel

/*******************************************************************************
 *                        FUNCTION HEADERS DEFINITION
 ******************************************************************************/

/** \brief Configures External Interrupts Pins
 * 
 * \pre    Global Interrupts must be configured
 * \param  None
 * \return None
 * 
 * \author Pedro Martins
 */
void configure_external_interrupts(void);

/** \brief Initializes encoder state
 * 
 * \pre     Encoders pin must be configured as digital inputs
 * \param   None
 * \return  None
 * \remarks Temporarily disables external interrupts
 * 
 * \author Pedro Martins
 */
void init_encoder_state(void);

/** \brief Resets Encoder Pulse Counter
 * 
 * \pre     Encoder module must be configured
 * \param   None
 * \return  None
 * \remarks Temporarily disables external interrupts
 * 
 * \author Pedro Martins
 */
void reset_enc_pulse_cnt(void);

#endif	/* ENCODER_H */

