/** 
 * \file   uart1.c
 * \brief  UART1 Device Driver COnfiguration C File
 * 
 * \author Pedro Martins
 * \date   Created on March 13, 2018, 11:15 AM
 */


#include <xc.h>

#include "../global.h"
#include "../interrupts.h"

#include "circular_buffer.h"
#include "uart1.h"


/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define DEFAULT_BAUDRATE 115200     //!< Default baudrate for UART 1 Pheripheral
#define MIN_BAUDRATE     600        //!< Minimum accepted baudrate
#define MAX_BAUDRATE     115200     //!< Maximum accepted baudrate

#define DEFAULT_STOP_BITS 1         //!< Default number of stop bits
#define DEFAULT_DATA_BITS 8         //!< Default number of data bits

#define INTEGER_2_ASCII_OFFSET 0x30 //!< Constant used to convert a decimal digit to ASCII
#define SYNC_CHAR 0x55              //!< Synchronism character used in auto-baud detection mode


#define DISABLE_WAKE_UP {U1MODEbits.WAKE = 0;}      //!< Disable MCU wake up from sleep state through UART
#define ENABLE_WAKE_UP  {U1MODEbits.WAKE = 1;}      //!< Enable MCU wake up from sleep state through UART

#define DISABLE_LOOPBACK {U1MODEbits.LPBACK = 0;}   //!< Disable Loopback Mode
#define ENABLE_LOOPBACK  {U1MODEbits.LPBACK = 1;}   //!< Enable Loopback Mode

#define DISABLE_AUTOMATIC_BAUD_RATE {U1MODEbits.ABAUD = 0;} //!< Enable Automatic Baud Rate detection for UART 1
#define ENABLE_AUTOMATIC_BAUD_RATE  {U1MODEbits.ABAUD = 1;} //!< Disable Automatic Baud Rate detection for UART 1

#define DISABLE_AUTO_ADDRESS_DETECT_MODE {U1STAbits.ADM_EN = 0;}    //!< Disable Auto Address Detection Mode for UART 1
#define ENABLE_AUTO_ADDRESS_DETECT_MODE  {U1STAbits.ADM_EN = 1;}    //!< Enable Auto Address Detection Mode for UART 1

#define ADDRESS_CHAR_DETECT_STATUS U1STAbits.ADDEN      //!< Status bit for Address mode Detection (used in multiprocessor UART Communications)
#define AUTO_ADDRESS_MASK_BITS     U1STAbits.ADDR       //!< Automatic Address Mask bits, if automatic address detection is enabled

#define UART1_SIMPLEX_MODE_OPERATION {U1MODEbits.RTSMD = 1;}        //!< Ready to Send (RTS) operates in Simplex Mode
#define UART1_FLOW_CONTROL_MODE_OPERATION {U1MODEbits.RTSMD = 0;}   //!< Ready to Send (RTS) operates in Flow Control Mode

/** \brief UART RX uses Positive (standard) logic
 * 
 * UART RX represents a '1' with the high voltage level (VDD) and a '0' with 
 * the low voltage level (GND)
 *
 * Therefore, UART RX Idle State is '1' (VDD)
 */
#define USE_POSITIVE_LOGIC_FOR_RX_DATA {U1MODEbits.RXINV = 0;} 

/** \brief UART RX uses Negative (inverse) logic
 * 
 * UART RX represents a '0' with the high voltage level (VDD) and a '1' with 
 * the low voltage level (GND)
 *
 * Therefore, UART RX Idle State is '0' (GND)
 */
#define USE_NEGATIVE_LOGIC_FOR_RX_DATA {U1MODEbits.RXINV = 1;}


/** \brief UART TX Polarity Inversion
 * 
 * If the IrDA mode is DISABLED (U1MODEbits.IREN = 0), the UART TX represents a 
 * '1' with an high voltage level (VDD) and a '0' with the low voltage level (GND).
 * Therefore, UART RX Idle State is '1' (VDD)
 * 
 * If the IrDA mode is ENABLED (U1MODEbits.IREN = 1), the UART TX represents a 
 * '0' with an high voltage level (VDD) and a '1' with the low voltage level (GND).
 * Therefore, UART RX Idle State is '0' (GND)
 */
#define USE_POSITIVE_LOGIC_FOR_TX_DATA {U1STAbits.UTXINV = 0;} 

/** \brief UART TX Polarity Inversion
 * 
 * If the IrDA mode is DISABLED (U1MODEbits.IREN = 0), the UART TX represents a 
 * '0' with an high voltage level (VDD) and a '1' with the low voltage level (GND).
 * Therefore, UART RX Idle State is '0' (GND)
 * 
 * If the IrDA mode is ENABLED (U1MODEbits.IREN = 1), the UART TX represents a 
 * '1' with an high voltage level (VDD) and a '0' with the low voltage level (GND).
 * Therefore, UART RX Idle State is '1' (VDD)
 */
#define USE_NEGATIVE_LOGIC_FOR_TX_DATA {U1STAbits.UTXINV = 1;}



#define UART1_IPL  3        //!< Interrupt Priority Level for UART 1
#define UART1_IPSL 0        //!< Interrupt Sub Priority Level for UART 1

#define CLEAR_IF_UART1_TX               {IFS0bits.U1TXIF = 0;}      //!< Clear TX Interrupt Flag for UART 1
#define CLEAR_IF_UART1_RX               {IFS0bits.U1RXIF = 0;}      //!< Clear RX Interrupt Flag for UART 1
#define CLEAR_IF_UART1_ERROR_DETECTION  {IFS0bits.U1EIF = 0;}       //!< Clear Error Detection Interrupt Flag for UART 1

#define IF_UART1_TX                 IFS0bits.U1TXIF     //!< TX Interrupt Flag for UART 1
#define IF_UART1_RX                 IFS0bits.U1RXIF     //!< RX Interrupt Flag for UART 1
#define IF_UART1_ERROR_DETECTION    IFS0bits.U1EIF      //!< Error Detection Interrupt Flag for UART 1


/*******************************************************************************
 *                       CLASS VARIABLES DEFINITION
 ******************************************************************************/

volatile circularBuffer tx_buffer; //!< Transmission circular buffer for TX data
volatile circularBuffer rx_buffer; //!< Reception circular buffer for RX data


/*******************************************************************************
 *                         CLASS METHODS
 ******************************************************************************/
void config_UART1(uint32_t baudrate, uint8_t data_bits, unsigned char parity, uint8_t stop_bits) {
    // Fully disable UART 1, all related interruptions and clear  interruptions flag
    DISABLE_UART1_PHERIPHERAL;
    DISABLE_UART1_ALL_INTERRUPTS;
    CLEAR_IF_UART1_TX;
    CLEAR_IF_UART1_RX;
    CLEAR_IF_UART1_ERROR_DETECTION;

    /***************************************************************************
     *                      VALIDATE USER INPUT 
     ***************************************************************************/
    // Truncate desired baudrate
    baudrate = (baudrate < MIN_BAUDRATE || baudrate > MAX_BAUDRATE) ? DEFAULT_BAUDRATE : baudrate;

    // truncate invalid data bits
    data_bits = (data_bits != 8 || data_bits != 9) ? DEFAULT_DATA_BITS : data_bits;

    // Truncate stop bits
    stop_bits = (stop_bits != 1 || stop_bits != 2) ? DEFAULT_STOP_BITS : stop_bits;


    /***************************************************************************
     *                        GENERAL SETUP 
     ***************************************************************************/

    /* Continue UART operation in Idle Mode */
    U1MODEbits.SIDL = 0;

    /* Disable IrDA Encoder and Decoder */
    U1MODEbits.IREN = 0;

    /* Ready to send operates in Flow Control Mode */
    UART1_FLOW_CONTROL_MODE_OPERATION;


    /* Enable UxTX & UxRX and disable the usage of UxCTS, UxRTS pins
     * 
     * UEN<1:0>: UARTx Enable bits (4)
     *  11 = UxTX, UxRX and UxBCLK pins are enabled and used; UxCTS pin is controlled by corresponding
     *       bits in the PORTx register
     *  10 = UxTX, UxRX, UxCTS and UxRTS pins are enabled and used
     *  01 = UxTX, UxRX and UxRTS pins are enabled and used; UxCTS pin is controlled by corresponding
     *       bits in the PORTx register
     *  00 = UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/UxBCLK pins are controlled by
     *       corresponding bits in the PORTx register
     */
    U1MODEbits.UEN = 0b00;

    /* Disable Wake-up through UART */
    DISABLE_WAKE_UP;

    /* Disable Loopback mode */
    DISABLE_LOOPBACK;

    /* Disable Automatic Baud Rate */
    DISABLE_AUTOMATIC_BAUD_RATE

    /*  UxRX Idle state is '1'
     * '1' = VDD
     * '0' = GND
     */
    USE_POSITIVE_LOGIC_FOR_RX_DATA;

    /* Disable Automatic Address Detection Mode (used in a multiprocessor environment)*/
    DISABLE_AUTO_ADDRESS_DETECT_MODE;

    /* High Speed Mode Disabled - uses 4 samples to determine the logic level */
    U1MODEbits.BRGH = 0;

    /*  UxTX Idle state is '1'
     * '1' = VDD
     * '0' = GND
     */
    USE_POSITIVE_LOGIC_FOR_TX_DATA;


    /***************************************************************************
     *                            USER SETUP 
     ***************************************************************************/

    /* Baud-Rate value for the Baud Rate Divisor bits register */
    U1BRG = (uint16_t) (PBCLK / (16 * baudrate) - 1);


    /* Set parity and data selection bits
     * 
     * 11 -> 9 bit data, no parity
     * 10 -> 8 bit data, odd parity
     * 01 -> 8 bit data, even parity
     * 00 -> 8 bit data, no parity 
     */
    if (data_bits == 8) {
        switch (parity) {
            case 'E': // Even parity
                U1MODEbits.PDSEL = 0b01;
                break;
            case 'O': // Odd parity
                U1MODEbits.PDSEL = 0b10;
                break;
            case 'N': // No parity & default value
            default:
                U1MODEbits.PDSEL = 0b00;
                break;
        }
    } else {
        // No parity options available for 9 bits
        U1MODEbits.PDSEL = 0b11;
    }

    /* Sets the stop bits
     * 
     * STSEL: Stop Selection bit
     *   1 = 2 Stop bits
     *   0 = 1 Stop bit
     */
    U1MODEbits.STSEL = stop_bits - 1;

    /***************************************************************************
     *                            INTERRUPTS
     ***************************************************************************/
#ifdef USE_INTERRUPTS
    /* TX Interrupt is generated when there is at least one empty space
     * 
     * TX Interrupt Mode Selection bits (1)
     *   For 4-level deep FIFO UART modules:
     *   11 = Reserved, do not use
     *   10 = Interrupt is generated when the transmit buffer becomes empty
     *   01 = Interrupt is generated when all characters have been transmitted
     *   00 = Interrupt is generated when the transmit buffer contains at least one empty space
     * 
     *   For 8-level deep FIFO UART modules:
     *   11 = Reserved, do not use
     *   10 = Interrupt is generated and asserted while the transmit buffer is empty
     *   01 = Interrupt is generated and asserted when all characters have been transmitted
     *   00 = Interrupt is generated and asserted while the transmit buffer contains at least one empty space
     */
    U1STAbits.UTXISEL = 0b00;

    /* RX interrupt is generated when there is at least one received character
     * 
     * Receive Interrupt Mode Selection bit (1)
     *   For 4-level deep FIFO UART modules:
     *     11 = Interrupt flag bit is set when receive buffer becomes full (i.e., has 4 data characters)
     *     10 = Interrupt flag bit is set when receive buffer becomes 3/4 full (i.e., has 3 data characters)
     *     0x = Interrupt flag bit is set when a character is received
     * 
     *   For 8-level deep FIFO UART modules:
     *     11 = Reserved; do not use
     *     10 = Interrupt flag bit is asserted while receive buffer is 3/4 or more full (i.e., has 6 or more data characters)
     *     01 = Interrupt flag bit is asserted while receive buffer is 1/2 or more full (i.e., has 4 or more data characters)
     *     00 = Interrupt flag bit is asserted while receive buffer is not empty (i.e., has at least 1 data character)
     */
    U1STAbits.URXISEL = 0b00;

    /* Set Interrupt Priority and Sub-priority Levels */
    IPC6bits.U1IP = UART1_IPL & 0x07;
    IPC6bits.U1IS = UART1_IPSL & 0x03;
#endif
}


void flush_RX_buffer(void) 
{
    DISABLE_UART1_RX_INT;   // Begin Critical Section

    rx_buffer.head = 0;
    rx_buffer.tail = 0;
    rx_buffer.head = 0;

    ENABLE_UART1_RX_INT;    // End Critical Section
}


void flush_TX_buffer(void) 
{
    DISABLE_UART1_TX_INT;   // Begin Critical Section

    tx_buffer.head = 0;
    tx_buffer.tail = 0;
    tx_buffer.head = 0;

    ENABLE_UART1_TX_INT;    // End Critical Section
}


void put_char(char c) {
#ifndef USE_INTERRUPTS
    while (UART1_TX_FULL_STATUS);

    U1TXREG = c;
#else
    while (tx_buffer.count == BUF_SIZE); // Wait while buffer is full

    tx_buffer.data[tx_buffer.tail] = c;
    tx_buffer.tail = (tx_buffer.tail + 1) & INDEX_MASK;

    DISABLE_UART1_TX_INT; // Begin of critical section
    tx_buffer.count++;
    ENABLE_UART1_TX_INT; // End of critical section
#endif
}


void put_uint8(uint8_t value) 
{
    put_char( (value / 10) + INTEGER_2_ASCII_OFFSET);   // High 
    put_char( (value % 10) + INTEGER_2_ASCII_OFFSET);   // Low
}


void put_uint16(uint16_t value) 
{
    put_char( (value / 10000)          + INTEGER_2_ASCII_OFFSET );     // fifth  nibble
    put_char( ((value % 10000) / 1000) + INTEGER_2_ASCII_OFFSET );     // fourth nibble
    put_char( ((value % 1000) / 100)   + INTEGER_2_ASCII_OFFSET );     // third  nibble
    put_char( ((value % 100) / 10)     + INTEGER_2_ASCII_OFFSET );     // second nibble
    put_char( ((value % 10))           + INTEGER_2_ASCII_OFFSET );     // first  nibble
}


void put_string(char *s) 
{
    while (*s != '\0')
    {
        put_char(*s);
        s++;
    }
}


uint8_t get_char(char *p_char) 
{
#ifndef USE_INTERRUPTS
    while (!UART1_RX_DATA_AVAILABLE_STATUS);
    
    *p_char = U1RXREG;

    if (UART1_OVERRUN_ERROR_OCCURRED) {
        CLEAR_OVERRUN_ERROR_FLAG;
    }
    
    return UART_SUCCESS;
#else
    if (rx_buffer.count == 0) {
        return UART_ERROR;
    }

    DISABLE_UART1_RX_INT;

    *p_char = rx_buffer.data[rx_buffer.head];
    rx_buffer.count--;
    rx_buffer.head = (rx_buffer.head + 1) & INDEX_MASK;

    ENABLE_UART1_RX_INT;

    return UART_SUCCESS;
#endif
}


uint8_t get_uint8(uint8_t *p_uint8) 
{
    uint8_t high, low, return_high, return_low;
    
    return_high = get_char(&high);
    return_low  = get_char(&low);

    *p_uint8 = ( (high - INTEGER_2_ASCII_OFFSET )* 10 + low - INTEGER_2_ASCII_OFFSET);
    
    return (return_high | return_low);
}


/** \brief ISR for UART 1
 * 
 * \pre    Global Interrupts must be configured and enabled
 * \pre    UART 1 must be configured and enabled
 * 
 * \param  None.
 * \return None.
 * 
 * Interruption Service Routine for UART 1
 * Deals with TX and RX interrupts, manipulating the Circular Buffer
 * The ISR can handle OVERRUN errors, signaling them through the rx_buffer.overrun 
 * flag
 * 
 * The Interruption Priority Level is 3 and the compiler must write software to
 * perform the context switching (IPL3SOFT)
 * 
 * \author Pedro Martins
 */
void __ISR(_UART1_VECTOR, IPL3SOFT) UART_ISR(void) {
    // Interruption caused by TX module
    if (IF_UART1_TX == 1) 
    {
        // while the transmission buffer has at least one empty slot and is not full
        while (tx_buffer.count > 0 && (UART1_TX_FULL_STATUS == 0)) {
            U1TXREG = tx_buffer.data[tx_buffer.head];
            tx_buffer.head = (tx_buffer.head + 1) & INDEX_MASK;
            tx_buffer.count--;
        }

        if (tx_buffer.count == 0) {
            DISABLE_UART1_TX_INT;
        }

        CLEAR_IF_UART1_TX;
    }

    // Interruption caused by the RX module
    if (IF_UART1_RX == 1) 
    {
        while (UART1_RX_DATA_AVAILABLE_STATUS == 1) {
            rx_buffer.data[rx_buffer.tail] = U1RXREG;
            rx_buffer.tail = (rx_buffer.tail + 1) & INDEX_MASK;

            if (rx_buffer.count < BUF_SIZE)
                rx_buffer.count++;
            else
                rx_buffer.head = (rx_buffer.head + 1) & INDEX_MASK;
        }
        CLEAR_IF_UART1_RX;
    }

    // Interruption caused by errors
    if (IF_UART1_ERROR_DETECTION == 1) 
    {
        if (UART1_OVERRUN_ERROR_OCCURRED == 1) {
            rx_buffer.overrun = 1; 
            CLEAR_OVERRUN_ERROR_FLAG; 
            CLEAR_IF_UART1_ERROR_DETECTION;
        }
    }
}