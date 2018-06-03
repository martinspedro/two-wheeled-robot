/** 
 * \file   IO.h
 * \brief  Input/Output Mapping and configurations Header File
 * 
 * \author Pedro Martins
 * \date   Created on June 3, 2018, 11:59 AM
 */

#include <xc.h>

#ifndef IO_H
#define	IO_H

/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define START_BUTTON PORTFbits.RF0      //!< START button pin mapping
#define STOP_BUTTON  PORTFbits.RF1      //!< STOP button pin mapping


#define LED1 LATGbits.LATG13            //!< LED1 pin mapping
#define LED2 LATGbits.LATG12            //!< LED2 pin mapping
#define LED3 LATGbits.LATG14            //!< LED3 pin mapping

#define ROBOT_INIT_SUCESS_LED LED1      //!< Assign LED2 to provide INIT SUCESS LED Feedback
#define ERROR_LED             LED2      //!< Assign LED1 to provide ERROR LED Feedback
#define OBSTACLE_DETECTED_LED LED3      //!< Assign LED3 to provide ERROR LED Feedback


#define EXTRA_1_INPUT  {TRISDbits.TRISD8  = 1;}   //!< Set EXTRA PIN 1 as Input
#define EXTRA_1_OUTPUT {TRISDbits.TRISD8  = 0;}   //!< Set EXTRA PIN 1 as Output
#define EXTRA_2_INPUT  {TRISDbits.TRISD9  = 1;}   //!< Set EXTRA PIN 2 as Input
#define EXTRA_2_OUTPUT {TRISDbits.TRISD9  = 0;}   //!< Set EXTRA PIN 2 as Output
#define EXTRA_3_INPUT  {TRISDbits.TRISD10 = 1;}   //!< Set EXTRA PIN 3 as Input
#define EXTRA_3_OUTPUT {TRISDbits.TRISD10 = 0;}   //!< Set EXTRA PIN 3 as Output

#define EXTRA_1_LAT  LATDbits.LATD8     //!< EXTRA PIN 1 LAT Register Bit
#define EXTRA_2_LAT  LATDbits.LATD9     //!< EXTRA PIN 2 LAT Register Bit
#define EXTRA_3_LAT  LATDbits.LATD10    //!< EXTRA PIN 3 LAT Register Bit

#define EXTRA_1_PORT LATDbits.LATD8     //!< EXTRA PIN 1 PORT Register Bit 
#define EXTRA_2_PORT LATDbits.LATD9     //!< EXTRA PIN 2 PORT Register Bit
#define EXTRA_3_PORT LATDbits.LATD10    //!< EXTRA PIN 3 PORT Register Bit


/*******************************************************************************
 *                         CLASS METHODS
 ******************************************************************************/

/** \brief Initializes the IO Pins on the Robot
 * 
 * Currently only sets LEDs as output and clears their value
 * 
 * \param  None.
 * \return None.
 * 
 * \author Pedro Martins
 */
void init_IO(void);

#endif	/* IO_H */

