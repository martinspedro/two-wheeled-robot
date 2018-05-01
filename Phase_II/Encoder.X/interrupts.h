/**
 * \file interrupts.h
 * \brief Interrupt configuration Header File
 * \author Pedro Martins
 * \date Created on May 1, 2018, 10:22 AM
 */


#include <xc.h>

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

/*******************************************************************************
 *                           MACRO DEFINITION
 ******************************************************************************/
#define ENABLE_EXT_INT0  {IEC0bits.INT0IE = 1;}     //!< Enables INT0 interrupt  >
#define DISABLE_EXT_INT0 {IEC0bits.INT0IE = 0;}     //!< Disables INT0 interrupt >
#define ENABLE_EXT_INT1  {IEC0bits.INT1IE = 1;}     //!< Enables INT1 interrupt  >
#define DISABLE_EXT_INT1 {IEC0bits.INT1IE = 0;}     //!< Disables INT1 interrupt >


#define EXT_INT0_IPL 6      //!< External Interrupt Pin 0 Priority Level     >
#define EXT_INT0_ISPL 0     //!< External Interrupt Pin 0 Sub-Priority Level >

#define EXT_INT1_IPL 6      //!< External Interrupt Pin 1 Priority Level     >
#define EXT_INT1_ISPL 0     //!< External Interrupt Pin 1 Sub-Priority Level >


#define Enable_Global_Interrupts()   asm volatile("ei")     //!< Enables Global Interrupts  >
#define Disable_Global_Interrupts()  asm volatile("di")     //!< Disables Global Interrupts >




/*******************************************************************************
 *                        FUNCTION HEADERS DEFINITION
 ******************************************************************************/

/** \brief Configures Global Interrupts
 * 
 * \pre    None
 * \param  None
 * \return None
 * 
 * \author Pedro Martins
 */
void configure_global_interrupts(void);

/** \brief Configures External Interrupts Pins
 * 
 * \pre    Global Interrupts must be configured
 * \param  None
 * \return None
 * 
 * \author Pedro Martins
 */
void configure_external_interrupts(void);


#endif	/* INTERRUPTS_H */

