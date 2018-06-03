/**
 * \file   interrupts.h
 * \brief  Global Interrupt configuration Header File
 * 
 * \author Pedro Martins
 * \date   Created on May 1, 2018, 10:22 AM
 */


#include <sys/attribs.h> 

#ifndef INTERRUPTS_H
#define INTERRUPTS_H


/*******************************************************************************
 *                           MACROS DEFINITION
 ******************************************************************************/
#define Enable_Global_Interrupts()   asm volatile("ei")     //!< Enables Global Interrupts  
#define Disable_Global_Interrupts()  asm volatile("di")     //!< Disables Global Interrupts 


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


#endif	/* INTERRUPTS_H */

