/* 
 * File:   adc.c
 * Author: martinspedro
 *
 * Created on April 9, 2018, 16:43 PM
 * 
 * 
 */

#include <xc.h>
#include "../global.h"

#define MANUAL_MODE

#define ADC_ERROR   1
#define ADC_SUCCESS 0

#define ADC_MAX_VALUE 1023
#define ADC_INT_ROUND 511
#define AVDD VDD
#define AVSS 0

#define IO_ANALOG_PIN_REGISTER TRISB

#define HAS_CONVERSION_FINISHED AD1CON1bits.DONE
#define BUFFER_FILL_STATUS  AD1CON2bits.BUFS
#ifdef MANUAL_MODE
    #define START_CONVERSION {AD1CON1bits.SAMP = 1;}
    #define END_CONVERSION   {AD1CON1bits.SAMP = 0;}
#endif


/* @brief ADC configuration routine
 * This routine initializes the ADC module
 * It does NOT selects the ADC channel or initialize the ADC channel 
 * corresponding pin
 * 
 * @param uint16_t channel 
 * @author Pedro Martins
 */
void adc_init(void)
{
    /* Disable ADC module for configuration
     *
     * ADC Operating Mode bit
     *    1 = A/D converter module is operating
     *    0 = A/D converter is off
     */
    AD1CON1bits.ON = 0;

    /* Enable ADC while CPU is IDLE
     * 
     * Stop in IDLE Mode bit
     *  1 = Discontinue module operation when device enters IDLE mode
     *  0 = Continue module operation in IDLE mode
     */
    AD1CON1bits.SIDL = 0;
    
    /* Use integer 16 bits as output format
     * 
     * Data Output Format bits
     *   011 = Signed Fractional 16-bit (DOUT = 0000 0000 0000 0000 sddd dddd dd00 0000)
     *   010 = Fractional 16-bit (DOUT = 0000 0000 0000 0000 dddd dddd dd00 0000)
     *   001 = Signed Integer 16-bit (DOUT = 0000 0000 0000 0000 ssss sssd dddd dddd)
     *   000 = Integer 16-bit (DOUT = 0000 0000 0000 0000 0000 00dd dddd dddd)
     *   111 = Signed Fractional 32-bit (DOUT = sddd dddd dd00 0000 0000 0000 0000)
     *   110 = Fractional 32-bit (DOUT = dddd dddd dd00 0000 0000 0000 0000 0000)
     *   101 = Signed Integer 32-bit (DOUT = ssss ssss ssss ssss ssss sssd dddd dddd)
     *   100 = Integer 32-bit (DOUT = 0000 0000 0000 0000 0000 00dd dddd dddd)
     */
    AD1CON1bits.FORM = 0b000;
    
    /* Use ADC in manual mode. Clearing SAMP bit ends sampling and starts conversion 
     * 
     * Conversion Trigger Source Select bits
     *   111 = Internal counter ends sampling and starts conversion (auto convert)
     *   110 = Reserved
     *   101 = Reserved
     *   100 = Reserved
     *   011 = Reserved
     *   010 = Timer 3 period match ends sampling and starts conversion
     *   001 = Active transition on INT0 pin ends sampling and starts conversion
     *   000 = Clearing SAMP bit ends sampling and starts conversion
     */
    AD1CON1bits.SSRC = 0b000;
    
    /* ADC overwrites buffer contents after each conversion
     * 
     * Stop Conversion Sequence bit (when the first A/D converter interrupt is generated)
     *   1 = Stop conversions when the first ADC interrupt is generated. 
     *       Hardware clears the ASAM bit when the ADC interrupt is generated.
     *   0 = Normal operation, buffer contents will be overwritten by the next 
     *       conversion sequence
     */
    AD1CON1bits.CLRASAM = 0;
    
    /* Setting SAMP bit starts a new conversion
     * 
     * ADC Sample Auto-Start bit
     *   1 = Sampling begins immediately after last conversion completes; SAMP bit is automatically set.
     *   0 = Sampling begins when SAMP bit is set
     */
    AD1CON1bits.ASAM = 0;
    
    /* ADC sample/hold amplifier default state is HOLD
     * 
     * ADC Sample Enable bit
     *   1 = The ADC SHA is sampling
     *   0 = The ADC sample/hold amplifier is holding
     *
     *   When ASAM = 0, writing '1' to this bit starts sampling.
     *   When SSRC = 000, writing '0' to this bit will end sampling and start conversion.
     */
    AD1CON1bits.SAMP = 0;
    
    /* Voltage Reference for ADC is the voltage for PIC
     * 
     * Voltage Reference Configuration bits
     * 
     *           ADC VR+           |        ADC VR-
     *   --------------------------------------------------
     *   000      AVDD             |         AVSS
     *   001   External VREF+ pin  |         AVSS
     *   010      AVDD             |  External VREF- pin
     *   011   External VREF+ pin  |  External VREF- pin
     *   1xx      AVDD             |         AVSS
     */
    AD1CON2bits.VCFG = 0b000;
    
    /* Disable Offset Calibration mode
     * 
     * Input Offset Calibration Mode Select bit
     *   1 = Enable Offset Calibration mode
     *       VINH and VINL of the SHA are connected to VR-
     *   0 = Disable Offset Calibration mode
     *       The inputs to the SHA are controlled by AD1CHS or AD1CSSL
     */
    AD1CON2bits.OFFCAL = 0;
    
    /* Disable Input Scanning
     * 
     * Scan Input Selections for CH0+ SHA Input for MUX A Input Multiplexer Setting bit
     *   1 = Scan inputs
     *   0 = Do not scan inputs
     */
    AD1CON2bits.CSCNA = 0;
    
    /* Define 1 interrupt per converted sample
     * 
     * Sample/Convert Sequences Per Interrupt Selection bits
     *   1111 = Interrupts at the completion of conversion for each 16 th sample/convert sequence
     *   1110 = Interrupts at the completion of conversion for each 15 th sample/convert sequence
     *   .....
     *   0001 = Interrupts at the completion of conversion for each 2 nd sample/convert sequence
     *   0000 = Interrupts at the completion of conversion for each sample/convert sequence
     */
    AD1CON2bits.SMPI = 0b0000;
    
    /* Configure ADC buffer as a 16 word buffer
     * 
     * ADC Result Buffer Mode Select bit
     *   1 = Buffer configured as two 8-word buffers, ADC1BUF(7...0), ADC1BUF(15...8)
     *   0 = Buffer configured as one 16-word buffer ADC1BUF(15...0.)
     */
    AD1CON2bits.BUFM = 0;
    
    /* Use MUX A input multiplexer settings for the Analog channels
     *
     * Alternate Input Sample Mode Select bit
     *   1 = Uses MUX A input multiplexer settings for first sample, then 
     *       alternates between MUX B and MUX A input multiplexer settings for 
     *       all subsequent samples
     *   0 = Always use MUX A input multiplexer settings
     */
    AD1CON2bits.ALTS = 0;
            
    /* ADC clock source is the peripheral bus clock
     * 
     * ADC Conversion Clock Source bit
     *  1 = ADC internal RC clock
     *  0 = Clock derived from Peripheral Bus Clock (PBclock)
     */
    AD1CON3bits.ADRC = 0;
    
    /*
     * Auto-Sample Time bits
     *   11111 = 31 T AD
     *   ·····
     *   00001 = 1 T AD
     *   00000 = 0 T AD (Not allowed)
     */
    //AD1CON3bits.SAMC = 
    
    /* 
     *
     * ADC Conversion Clock Select bits 
     *   11111111 = TPB ? 2 ? (ADCS<7:0> + 1) = 512 ? TPB = TAD
     *   ?
     *   ?
     *   ?
     *   00000001 = TPB ? 2 ? (ADCS<7:0> + 1) = 4 ? TPB = TAD
     *   00000000 = TPB ? 2 ? (ADCS<7:0> + 1) = 2 ? TPB = TAD
     */
    AD1CON3bits.ADCS = 0b00011110;
    
    /* MUX B negative input is VR-
     * 
     * Negative Input Select bit for MUX B
     *   1 = Channel 0 negative input is AN1
     *   0 = Channel 0 negative input is VR-
     */
    AD1CHSbits.CH0NB = 0;
    
    /* Select MUX B positive input as AN0 (unused - connect to AVss)
     * 
     * CH0SB<3:0>: Positive Input Select bits for MUX B
     *   1111 = Channel 0 positive input is AN15
     *   1110 = Channel 0 positive input is AN14
     *   1101 = Channel 0 positive input is AN13
     *   ?
     *   ?
     *   ?
     *   0001 = Channel 0 positive input is AN1
     *   0000 = Channel 0 positive input is AN0
     */
    AD1CHSbits.CH0SB = 0b000;
    
    /* MUX A negative input is VR-
     * 
     * Negative Input Select bit for MUX A Multiplexer Setting
     *   1 = Channel 0 negative input is AN1
     *   0 = Channel 0 negative input is VR-     
     */
    AD1CHSbits.CH0NA = 0;
    
    /* Select MUX A positive input as AN0 (unused - connect to AVss)
     * 
     * CH0SB<3:0>: Positive Input Select bits for MUX B
     *   1111 = Channel 0 positive input is AN15
     *   1110 = Channel 0 positive input is AN14
     *   1101 = Channel 0 positive input is AN13
     *   ?
     *   ?
     *   ?
     *   0001 = Channel 0 positive input is AN1
     *   0000 = Channel 0 positive input is AN0
     */
    AD1CHSbits.CH0SA = 0b000;
    
    /* Skip all channels for ADC input pin scan
     * 
     * CSSL<15:0>: ADC Input Pin Scan Selection bits
     *   1 = Select ANx for input scan
     *   0 = Skip ANx for input scan
     */
    AD1CSSLbits.CSSL = 0x0000;
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
    uint16_t channel_bit_string = (uint16_t) (0b1 << (channel & 0x0F)) & 0x0FF;
    
    // Configure I/O PIN register
    IO_ANALOG_PIN_REGISTER = (IO_ANALOG_PIN_REGISTER & (channel_bit_string));
    
    // Select IO pin as analog input
    AD1PCFGbits.PCFG = AD1PCFGbits.PCFG & (!channel_bit_string);
    
    // Select ADC channel
    AD1CHSbits.CH0SA = (channel & 0x0F);
    
    
    return ADC_SUCCESS;
}

/* @brief Select ADC channel for conversion
 * 
 * @param uint16_t channel 
 * @author Pedro Martins
 */
uint8_t select_ADC_ch(uint8_t channel)
{
    if (channel > 15)
    {
        return ADC_ERROR;
    }
    AD1CHSbits.CH0SA = channel & 0x0F;
    return ADC_SUCCESS;
}

/* @brief Enable ADC module
 * 
 * @param uint16_t channel 
 * @author Pedro Martins
 */
void enable_ADC(void)
{
    AD1CON1bits.ON = 1;
}

void start_conversion(void)
{
    START_CONVERSION
}

void end_conversion(void)
{
    END_CONVERSION
}

uint8_t conversion_finnished(void)
{
    return HAS_CONVERSION_FINISHED;
}

uint8_t bin_2_volt(uint16_t analog_value)
{
	return (uint8_t)( (analog_value * (AVDD - AVSS) + ADC_INT_ROUND)/ADC_MAX_VALUE);
}

uint16_t get_analog_value(void)
{
    return (ADC1BUF0 & 0x3FF);
}