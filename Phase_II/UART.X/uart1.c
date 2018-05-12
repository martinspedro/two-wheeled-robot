/** 
 * \file   uart1.c
 * \brief  UART1 Device Driver COnfiguration C File
 * 
 * \author Pedro Martins
 * \date   Created on March 13, 2018, 11:15 AM
 */


#include <xc.h>
#include "../global.h"
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



#define UART1_IPL  3
#define UART1_IPSL 0

#define UART1_TX_IPL  3
#define UART1_RX_IPSL 0

#define ENABLE_UART1_INT  {IEC0bits.U1EIE = 1;}
#define DISABLE_UART1_INT {IEC0bits.U1EIE = 0;}
#define ENABLE_UART1_TX_INT  {IEC0bits.U1TXIE = 1;}
#define DISABLE_UART1_TX_INT {IEC0bits.U1TXIE = 0;}
#define ENABLE_UART1_RX_INT  {IEC0bits.U1RXIE = 1;}
#define DISABLE_UART1_RX_INT {IEC0bits.U1RXIE = 0;}

#define CLEAR_IF_UART1_TX {IFS0bits.U1TXIF = 0;}
#define CLEAR_IF_UART1_RX {IFS0bits.U1RXIF = 0;}
#define CLEAR_IF_UART1    {IFS0bits.U1EIF = 0;}



/*******************************************************************************
 *                         CLASS METHODS
 ******************************************************************************/
/** \brief UART Configuration Function
 * 
 * \param baudrate   Desired baudrate for UART operation
 * \param data_bits  Desired data bits for UART communications
 * \param parity     Parity tyope desired for UART 
 * \param stop_bits  Desired number of stop bits for UART communications
 * 
 * The baudrate equation is given by: 
 * \f[Baud-Rate = \frac{F_{PB}}{16 \cdot (UxBRG + 1)}\f]
 * which yelds the value of the baudrate register, 
 * \f[UxBRG = \frac{F_{PB}}{16 \cdot Baud-Rate} - 1\f]
 * 
 * \author Pedro Martins
 */
void config_UART1(uint32_t baudrate, uint8_t data_bits, unsigned char parity, uint8_t stop_bits)
{
    DISABLE_UART1_PHERIPHERAL;
    
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
    
    /* Set Mode Selection for U1RTS to flow control mode
     * 
     * RTSMD: Mode Selection for UxRTS Pin bit
     *   1 = UxRTS pin is in Simplex mode
     *   0 = UxRTS pin is in Flow Control mode
     */
    U1MODEbits.RTSMD = 0;     
    
    
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
    
    /* High Baud Rate Enable bit
     * 1 - High speed mode enable -> 4x baud clock enable
     *     Uses 4x the baud rate clock and uses each sample to determine the 
     *     logic level
     * 0 - High speed mode disable -> 16x baud clock enable
     *     Uses 16x the baud rate clock and uses 4 samples to determine the 
     *     logic level
     */
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
    U1BRG = (uint16_t) (PBCLK / (16 * baudrate) - 1 );

    
    /* Set parity and data selection bits
     * 
     * 11 -> 9 bit data, no parity
     * 10 -> 8 bit data, odd parity
     * 01 -> 8 bit data, even parity
     * 00 -> 8 bit data, no parity 
     */
    if (data_bits == 8)
    {
        switch (parity)
        {
            case 'E':       // Even parity
                U1MODEbits.PDSEL = 0b01;
                break;
            case 'O':       // Odd parity
                U1MODEbits.PDSEL = 0b10;
                break;
            case 'N':       // No parity & default value
            default:
                U1MODEbits.PDSEL = 0b00; 
                break;
        }
    }
    else 
    {   
        // No parity options available for 9 bits
        U1MODEbits.PDSEL = 0b11; 
    }
    
     /* Sets the stop bits
      * 
      * STSEL: Stop Selection bit
      *   1 = 2 Stop bits
      *   0 = 1 Stop bit
      */
    U1MODEbits.STSEL =  stop_bits - 1;
    
    /***************************************************************************
    *                            INTERRUPTS
    ***************************************************************************/
    
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
    IPC6bits.U1IP = UART1_IPL  & 0x07;
    IPC6bits.U1IS = UART1_IPSL & 0x03;
}



/** @brief Blocking UART send char function
 * @author Pedro Martins
 * 
 * Verifies if the UART TX buffer is not full and then sends a character using 
 * the UART1 module
 * 
 */
uint8_t send_char(unsigned char c){
    while(UART1_TX_FULL_STATUS);
    
    U1TXREG = c;
    return UART_SUCCESS;
}

/** @brief Blocking UART read char function
 * @author Pedro Martins
 * 
 * Waits while UART RX buffer does not have data and then reads a character using 
 * the UART1 module
 * 
 * @TODO: Implement error verification features and inform to caller an error as occured
 * 
 */
unsigned char read_char(void){
    unsigned char c;
    
    
    while(!UART1_RX_DATA_AVAILABLE_STATUS);
    
    if(UART1_OVERRUN_ERROR_OCCURRED)
    {
        c = U1RXREG;
        CLEAR_OVERRUN_ERROR_FLAG;
    }
    else
    {
        c = U1RXREG;
    }
    
    return c;
}

/** @brief Blocking UART print 8 bit integer function
 * @author Pedro Martins
 * 
 * Sends a 8 bit integer via UART1
 * Uses send_char function
 * 
 */
uint8_t print_uint8(uint8_t value){
    uint8_t high = (value / 10 ) + INTEGER_2_ASCII_OFFSET;
    uint8_t low  = (value % 10 ) + INTEGER_2_ASCII_OFFSET;
    
    send_char(high);
    send_char(low);
    
    return UART_SUCCESS;
}

/* @brief Blocking UART print 16 bit integer function
 * @author Pedro Martins
 * 
 * Sends a 8 bit integer via UART1
 * Uses send_char function
 * 
 */
uint8_t print_uint16(uint16_t value){        
    uint8_t fifth_nibble =    (value / 10000 ) + INTEGER_2_ASCII_OFFSET;
    uint8_t fourth_nibble = ( (value % 10000 ) / 1000 ) + INTEGER_2_ASCII_OFFSET;
    uint8_t third_nibble  = ( (value % 1000 ) / 100   ) + INTEGER_2_ASCII_OFFSET;
    uint8_t second_nibble = ( (value % 100 ) / 10     )     + INTEGER_2_ASCII_OFFSET;
    uint8_t first_nibble  = ( (value % 10 )       ) + INTEGER_2_ASCII_OFFSET;
    
    send_char(fifth_nibble);
    send_char(fourth_nibble);
    send_char(third_nibble);
    send_char(second_nibble);
    send_char(first_nibble);
}

/** @brief Blocking UART read 8 bit integer function
 * @author Pedro Martins
 * 
 * Sends a 8 bit integer via UART1
 * Uses send_char function
 * 
 */
uint8_t read_uint8(void){
    uint8_t high = read_char() - INTEGER_2_ASCII_OFFSET;
    uint8_t low  = read_char() - INTEGER_2_ASCII_OFFSET;
    
    return high * 10 + low;
}

