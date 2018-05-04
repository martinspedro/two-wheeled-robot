/** 
 * \file encoder.h
 * \brief Encoder configuration  file
 * 
 * \author Pedro Martins
 * \date Created on May 1, 2018, 5:11 PM
 */

#ifndef ENCODER_H
#define	ENCODER_H

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

#define EXT_INT1_IPL  6     //!< External Interrupt Pin 1 Priority Level     
#define EXT_INT1_ISPL 0     //!< External Interrupt Pin 1 Sub-Priority Level 

#define EXT_INT2_IPL  6     //!< External Interrupt Pin 2 Priority Level     
#define EXT_INT2_ISPL 0     //!< External Interrupt Pin 2 Sub-Priority Level 

#define ENCODER_ERROR   1   //!< Return value in case of Error
#define ENCODER_SUCCESS 0   //!< Return value in case of Success

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


#endif	/* ENCODER_H */

