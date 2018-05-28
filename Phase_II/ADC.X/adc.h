/** 
 * \file   adc.h
 * \brief  ADC device driver header file
 * 
 * \author Pedro Martins
 * \date   Created on April 9, 2018, 4:25 PM
 */

#ifndef ADC_H
#define	ADC_H

#include <xc.h>

/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define CLOCKED_MODE 2

//#define AUTO_SAMPLING_MODE 1
//#define MANUAL_MODE

#define ADC_ERROR   1
#define ADC_SUCCESS 0

#define ENABLE_ADC  {AD1CON1bits.ON = 1;}
#define DISABLE_ADC {AD1CON1bits.ON = 0;}

#define RESET_INPUT_SCAN_PINS  {AD1CSSLbits.CSSL = 0x0000;}
#define DISABLE_INPUT_SCANNING {AD1CON2bits.CSCNA = 0;}
#define ENABLE_INPUT_SCANNING  {AD1CON2bits.CSCNA = 1;}


#define ENABLE_INPUT_OFFSET_CALIBRATION_MODE  {AD1CON2bits.OFFCAL = 1;}
#define DISABLE_INPUT_OFFSET_CALIBRATION_MODE {AD1CON2bits.OFFCAL = 0;}

#define ENABLE_ADC_INTERRUPTS   {IEC1bits.AD1IE = 1;}     //!< Enables  ADC interrupt 
#define DISABLE_ADC_INTERRUPTS  {IEC1bits.AD1IE = 0;}     //!< Disables ADC interrupt 

#define RESET_ANALOG_PINS {AD1PCFG = 0xFFFF;}
#define HAS_CONVERSION_FINISHED AD1CON1bits.DONE
#define BUFFER_FILL_STATUS AD1CON2bits.BUFS

#ifdef MANUAL_MODE
    #define START_SAMPLING   {AD1CON1bits.SAMP = 1;}
    #define START_CONVERSION {AD1CON1bits.SAMP = 0;}
#endif


/*******************************************************************************
 *                        FUNCTION HEADERS DEFINITION
 ******************************************************************************/

/** \brief ADC configuration routine
 * 
 * This routine initializes the ADC module
 * It does NOT selects the ADC channel or initialize the ADC channel 
 * corresponding pin
 * 
 * \author Pedro Martins
 */
void adc_peripheral_init(void);


/** \brief ADC Input Scaning configuration routine
 * 
 * This routine configures the pins to be sequentially scanned
 * 
 * \author Pedro Martins
 */
uint8_t config_input_scan(uint8_t channel);


/** \brief Initializes an ADC channel
 * 
 * Sets the given channel pin as analog input and changes ADC multiplexer input 
 * to the given pin
 * 
 * \param uint8_t channel The number of the corresponding ADC channel
 * \author Pedro Martins
 * \todo should be replaced by a vector of channels
 */
uint8_t init_ADC_ch(uint8_t channel);


/** \brief Select the input channel for the ADC
 * 
 * Assumes that the channel as already being initialized
 * 
 * \param uint8_t channel The number of the corresponding ADC channel
 * \author Pedro Martins
 */
uint8_t select_ADC_ch(uint8_t channel);


/** \brief Converts the analog value read in voltage
 * 
 * \f[\frac{analog\_value \cdot (A_{V_{DD}} - A_{V_{SS}} + ADC\_INT\_ROUND}{ADC\_MAX\_VALUE}\f]
 * 
 * \param uint16_t analog_value
 * \author Pedro Martins
 */
uint8_t bin_2_volt(uint16_t analog_value);


/** \brief Reads the first position of the buffer
 * 
 * 
 * \author Pedro Martins
 */
uint16_t get_analog_value(void);

#endif	/* ADC_H */

