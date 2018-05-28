/** 
 * \file   adc.c
 * \brief  ADC device driver implementation C file
 * 
 * \author Pedro Martins
 * \date   Created on April 9, 2018, 16:43 PM
 */

#include <xc.h>

#include "../global.h"
#include "adc.h"
#include "../interrupts.h"
#include "timer3.h"

/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define ADC_MAX_VALUE 1023      //!< ADC maximum read value
#define ADC_INT_ROUND 511       //!< Value used to round analog value to the nearest integer

#define AVDD VDD                //!< Analog Positive Voltage Reference
#define AVSS 0                  //!< Analog Negative Voltage Reference

#define IO_ANALOG_PIN_REGISTER      TRISB     //!< Analog Pin Register
#define IO_ANALOG_PIN_SET_REGISTER  TRISBSET  //!< Analog Pin Set Register

#define NUM_CONVERSIONS_PER_INTERRUPT 8     //!< 8 Conversions will be written to the buffer

#ifdef AUTO_SAMPLING_MODE
    #define ACQUISITION_TIME_TAD      16
    #define CONVERSION_CLOCK_PERIOD   124
#endif

#ifdef CLOCKED_MODE
    #define ACQUISITION_TIME_TAD      31//16
    #define CONVERSION_CLOCK_PERIOD   124
#endif

#define DEFAULT_ADC_CH_MUXA 0x0     //!< Default A Input Multiplexer channel
#define DEFAULT_ADC_CH_MUXB 0x0     //!< Default B Input Multiplexer Channel

#define RESET_IF_ADC {IFS1bits.AD1IF = 0;}  //!< Clear ADC Interrupt Flag

#define ADC_IPL  4     //!< ADC Priority Level     
#define ADC_ISPL 0     //!< ADC Sub-Priority Level 



#define ADC_BUFFER_ADDRESS (&ADC1BUF0)      //!< ADC Buffer Start Address

/*******************************************************************************
 *                       CLASS VARIABLES DEFINITION
 ******************************************************************************/
static volatile uint16_t adc_value_1;
static volatile uint16_t adc_value_2;

/*******************************************************************************
 *                         CLASS METHODS
 ******************************************************************************/
void adc_peripheral_init(void)
{
    DISABLE_ADC;    // Disable ADC module to enable configuration
    DISABLE_ADC_INTERRUPTS;
    RESET_ANALOG_PINS;      // Set all pins as digital
    RESET_IF_ADC;
    
    /***************************************************************************
     *                        ADC CONTROL REGISTERS
     **************************************************************************/
    
    /* ADC Peripheral continues to operate while CPU is in IDLE mode */
    AD1CON1bits.SIDL = 0;
    
    /* Use 16 bit integer as output format for ADC measurements
     * 
     * Integer 16-bit (DOUT = 0000 0000 0000 0000 0000 00dd dddd dddd)
     */
    AD1CON1bits.FORM = 0b000;
    
    /* Conversion Trigger Source Select bits
     * 
     *    MANUAL MODE        - Clearing SAMP bit ends sampling and starts conversion
     *    AUTO_SAMPLING_MODE - Internal counter ends sampling and starts conversion 
     *                         (auto convert)
     */
    #ifdef MANUAL_MODE
        AD1CON1bits.SSRC = 0b000;
    #elif AUTO_SAMPLING_MODE
        AD1CON1bits.SSRC = 0b111;
    #elif CLOCKED_MODE
        AD1CON1bits.SSRC = 0b010;
    #endif

    /* Buffer contents will be overwritten by the ADC next conversion sequence 
     * (Normal Operation)
     */
    AD1CON1bits.CLRASAM = 0;

    
    /* ADC Sample Auto-Start bit
     * 
     *    MANUAL MODE        - Setting SAMP bit starts sampling
     *    AUTO_SAMPLING_MODE - Sampling begins immediately after the last conversion 
     *                         is completed and SAMP bit is automatically set.
     */
    #ifdef MANUAL_MODE
        AD1CON1bits.ASAM = 0;
    #elif AUTO_SAMPLING_MODE
        AD1CON1bits.ASAM = 0;
    #elif CLOCKED_MODE
        AD1CON1bits.ASAM = 0;
    #endif  
    
    /* ADC sample/hold amplifier default state 
     * 
     *    MANUAL MODE        - The ADC sample/hold amplifier is holding.
     *                         Writing '1' to this bit (SAMP) starts sampling.
     *                         Writing '0' to this bit will end sampling and start conversion.
     *    AUTO_SAMPLING_MODE - The ADC SHA is sampling
     */
    #ifdef MANUAL_MODE
        AD1CON1bits.SAMP = 0;
    #elif AUTO_SAMPLING_MODE 
        AD1CON1bits.SAMP = 0;
    #elif CLOCKED_MODE
        AD1CON1bits.SAMP = 0;
    #endif 
    
    
    /* Select the same Voltage Reference for ADC as PIC
     * AVDD = VDD
     * AVSS = GND
     */
    AD1CON2bits.VCFG = 0b000;
    
    /* Disable Offset Calibration mode.
     * The inputs to the SHA are controlled by AD1CHS or AD1CSSL
     */
    DISABLE_INPUT_OFFSET_CALIBRATION_MODE;
    
    /*  Scan Input Selections for CH0+ SHA Input for MUX A Input 
     * 
     *    MANUAL MODE        - Do not scan inputs
     *    AUTO_SAMPLING_MODE - Scan inputs
     */
    #ifdef MANUAL_MODE
        DISABLE_INPUT_SCANNING;
    #elif AUTO_SAMPLING_MODE
        //ENABLE_INPUT_SCANNING
        DISABLE_INPUT_SCANNING;
        AD1CSSL = 0;
    #elif CLOCKED_MODE
        DISABLE_INPUT_SCANNING;
    #endif 
    AD1CSSL = 0;
    
    /* Sample/Convert Sequences Per Interrupt Selection bits
     * 
     *    MANUAL MODE        - 0 sample/convert sequences per interrupt
     *    AUTO_SAMPLING_MODE - NUM_SAMPLES_PER_INTERRUPT sample/convert sequences per interrupt
     */
    #ifdef MANUAL_MODE
        AD1CON2bits.SMPI = 0b000;
    #elif AUTO_SAMPLING_MODE
        AD1CON2bits.SMPI = NUM_CONVERSIONS_PER_INTERRUPT - 1;
    #elif CLOCKED_MODE
        AD1CON2bits.SMPI = NUM_CONVERSIONS_PER_INTERRUPT - 1;
    #endif 
    
    
    /* ADC Result Buffer Mode Select bit
     * 
     *    MANUAL MODE        - Buffer configured as one 16-word buffer ADC1BUF(15...0.)
     *    AUTO_SAMPLING_MODE - Buffer configured as two 8-word buffers, 
     *                         ADC1BUF(7...0), ADC1BUF(15...8)
     */
    #ifdef MANUAL_MODE
        AD1CON2bits.BUFM = 0;
    #elif AUTO_SAMPLING_MODE
        AD1CON2bits.BUFM = 0;
    #elif CLOCKED_MODE
        AD1CON2bits.BUFM = 0;
    #endif 
    
    
    /* Always use MUX A input multiplexer settings for the Analog channels */
    AD1CON2bits.ALTS = 0;
            
    /* Use the Peripheral Bus Clock for the ADC clock source */
    AD1CON3bits.ADRC = 0;
    
    /* Auto-Sample Time bits
     * 
     *    MANUAL MODE        - Not set
     *    AUTO_SAMPLING_MODE - Each conversion is sampled for ACQUISITION_TIME_TAD 
     */
    #ifdef AUTO_SAMPLING_MODE
        AD1CON3bits.SAMC = ACQUISITION_TIME_TAD;
    #elif CLOCKED_MODE
        AD1CON3bits.SAMC = ACQUISITION_TIME_TAD;
    #endif

    /* ADC Conversion Clock Select bits 
     *
     *    MANUAL MODE        - TAD = 769.23 ns
     *    AUTO_SAMPLING_MODE - TAD = 6.25 us. Guarantees that by reading 8 values
     *                         (half of the buffer), generates an interrupt every 1 ms
     * 
     */
    #ifdef MANUAL_MODE
        AD1CON3bits.ADCS = 0b00011110;
    #elif AUTO_SAMPLING_MODE
        AD1CON3bits.ADCS = CONVERSION_CLOCK_PERIOD;
    #elif CLOCKED_MODE
        AD1CON3bits.ADCS = CONVERSION_CLOCK_PERIOD;
    #endif
    
    /***************************************************************************
    *                   ADC CHANNEL SELECTION REGISTERS
    **************************************************************************/
    
    /* Select VR- for channel 0 negative input in MUX B */
    AD1CHSbits.CH0NB = 0;
    
    /* Select MUX B positive input as DEFAULT_ADC_CH_MUXB */
    AD1CHSbits.CH0SB = DEFAULT_ADC_CH_MUXB;
    
    /* Select VR- for channel 0 negative input in MUX A */
    AD1CHSbits.CH0NA = 0;
    
    /* Select MUX A positive input as DEFAULT_ADC_CH_MUXA */
    AD1CHSbits.CH0SA = DEFAULT_ADC_CH_MUXA;
    
    
    /***************************************************************************
    *                         INTERRUPTS
    **************************************************************************/
    // Set Priority and sub-priority levels for INT1 & INT2
    IPC6bits.AD1IP = ADC_IPL  & 0x07;
    IPC6bits.AD1IS = ADC_ISPL & 0x03;
}

uint8_t config_input_scan(uint8_t channel)
{
    if (channel > 15)
    {
        return ADC_ERROR;
    }
    
    /* Converts the hexadecimal channel value to a binary string.
     * The bit in the position given the number channel is set
     * e.g. channel = 3 => channel_bit_string = 0000 0000 0000 1000
     */
    uint16_t channel_bit_string = (uint16_t) ( (0b1 << (channel & 0x0F)) & 0x0FFFF );
    
    /* Selects channels for ANx input scan (active '1') */
    AD1CSSLSET = channel_bit_string & 0x0FFFF;
    
    return ADC_SUCCESS;
}


uint8_t init_ADC_ch(uint8_t channel)
{
    if (channel > 15)
    {
        return ADC_ERROR;
    }
    
    // Converts the hexadecimal channel value to a binary string.
    // The bit in the position given the number channel is set
    // e.g. channel = 3 => channel_bit_string = 0000 0000 0000 1000
    uint16_t channel_bit_string = (uint16_t) ( (0b1 << (channel & 0x0F)) & 0x0FFFF );
    
    // Configure I/O PIN register: '1' => Input
    IO_ANALOG_PIN_SET_REGISTER = channel_bit_string;
    
    // Select IO pin as analog input: '0' => Analog Pin
    AD1PCFGCLR = channel_bit_string;
    
    // Select ADC channel
    AD1CHSbits.CH0SA = (channel & 0x0F);
    
    
    return ADC_SUCCESS;
}



uint8_t select_ADC_ch(uint8_t channel)
{
    if (channel > 15)
    {
        return ADC_ERROR;
    }
    
    AD1CHSbits.CH0SA = channel & 0x0F;
    return ADC_SUCCESS;
}



uint8_t bin_2_volt(uint16_t analog_value)
{
	return (uint8_t)( (analog_value * (AVDD - AVSS) + ADC_INT_ROUND)/ADC_MAX_VALUE);
}


uint16_t get_analog_value(void)
{
    return (ADC1BUF0 & 0x3FF);
}


void __ISR(_ADC_VECTOR, IPL4SOFT) ADC_ISR(void)
{
    LATDbits.LATD4 = 1;
    
    //AD1CON1bits.ASAM = 1;
    /*
    volatile int  *adc_buffer_p;
    adc_buffer_p = (BUFFER_FILL_STATUS == 1) ? ADC_BUFFER_ADDRESS : ADC_BUFFER_ADDRESS + 0x80;
   
    adc_value_1 = 0;
    adc_value_2 = 0;
   
    uint8_t k;
    for( k = 1; k < NUM_CONVERSIONS_PER_INTERRUPT; k += 2)
    {
        adc_value_1 += *(adc_buffer_p);
        adc_value_2 += *(adc_buffer_p + 1);
        adc_buffer_p++;
    }
    
   // put_char('q');
   // put_char('\n');
    
    adc_value_1 = adc_value_1 >> 4;
    adc_value_2 = adc_value_2 >> 4;
    
    */
    RESET_IF_ADC;

    LATDbits.LATD4 = 0;
    //AD1CON1bits.ASAM = 1;
}