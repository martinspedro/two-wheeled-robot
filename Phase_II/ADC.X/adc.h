/** \file adc.h
 * 
 * \brief ADC device driver header file
 * \author: Pedro Martins
 *
 * \date Created on April 9, 2018, 4:25 PM
 */

#ifndef ADC_H
#define	ADC_H

#define MANUAL_MODE


#ifdef MANUAL_MODE
void start_conversion(void);
void end_conversion(void);
#endif

void adc_init(void);
void enable_ADC(void);
uint8_t select_ADC_ch(uint8_t channel);
uint8_t init_ADC_ch(uint8_t channel);
uint8_t conversion_finnished(void);

uint16_t get_analog_value(void);
#endif	/* ADC_H */

