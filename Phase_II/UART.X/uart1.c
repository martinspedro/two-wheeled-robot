/* 
 * File:   uart1.c
 * Author: martinspedro
 *
 * Created on March 13, 2018, 11:15 AM
 */

#include <xc.h>
#include "uart1.h"

#define SYSCLK  80000000L // System clock frequency, in Hz
#define PBCLOCK 40000000L // Peripheral Bus Clock frequency, in Hz

#define UART_ERROR   1
#define UART_SUCCESS 0

#define ENABLE_UART1    {U1MODEbits.ON = 1;}     // Activate UART 1
#define ENABLE_UART1_TX {U1STAbits.UTXEN = 1;}   // Activate UART 1 TX Module
#define ENABLE_UART1_RX {U1STAbits.URXEN = 1;}   // Activate UART 1 RX Module

#define TRANSMIT_BREAK_BIT {U1STAbits.UTXBRK = 1;} // Transmit a break bit

#define IS_UART1_TX_FULL  U1STAbits.UTXBF
#define IS_UART1_TX_EMPTY U1STAbits.TRMT

#define IS_UART1_RX_IDDLE U1STAbits.RIDLE
#define UART1_RX_HAS_DATA U1STAbits.URXDA


#define DEFAULT_BAUDRATE 115200
#define MIN_BAUDRATE     600
#define MAX_BAUDRATE     115200

#define DEFAULT_STOP_BITS 1
#define DEFAULT_DATA_BITS 8

#define DISABLE_UART1    {U1MODEbits.ON = 0;}     // Disable UART 1

/* @brief UART Configuration Function
 * The baudrate equation is given by: 
 * $Baud-Rate = \frac{F_{PB}}{16 \cdot (UxBRG + 1)}$, 
 * which yelds the value of the baudrate register, 
 * $UxBRG = \frac{F_{PB}}{16 \cdot Baud-Rate} - 1$
 * 
 * @author Pedro Martins
 */
void config_UART1(uint32_t baudrate, uint8_t data_bits, unsigned char parity, uint8_t stop_bits){
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
    *                            USER SETUP 
    ***************************************************************************/
    
    /* High Baud Rate Enable bit
     * 1 - High speed mode enable -> 4x baud clock enable
     *     Uses 4x the baud rate clock and uses each sample to determine the 
     *     logic level
     * 0 - High speed mode disable -> 16x baud clock enable
     *     Uses 16x the baud rate clock and uses 4 samples to determine the 
     *     logic level
     */
    U1MODEbits.BRGH = 0;
    
    
    /* Baud-Rate value for the Baud Rate Divisor bits register
     *
     */
    U1BRG = 259; //(uint16_t) (PBCLOCK / (16 * baudrate) - 1 );

    
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
    U1MODEbits.STSEL = 0;
    U1MODEbits.PDSEL = 0b00; 
    /***************************************************************************
    *                        GENERAL SETUP 
    ***************************************************************************/
   
    /* SIDL: Stop in Idle Mode bit
     *  1 = Discontinue operation when device enters Idle mode
     *  0 = Continue operation in Idle mode 
     */
    U1MODEbits.SIDL = 0;
    
    /* Disable IrDA Encoder and Decoder Enable bit
     * 
     * IREN: IrDA Encoder and Decoder Enable bit
     *  1 = IrDA is enabled
     *  0 = IrDA is disabled
     */
    U1MODEbits.IREN = 0; 
    
    /* Set Mode Selection for U1RTS to flow control mode
     * 
     * RTSMD: Mode Selection for UxRTS Pin bit
     *   1 = UxRTS pin is in Simplex mode
     *   0 = UxRTS pin is in Flow Control mode
     */
    U1MODEbits.RTSMD = 1;     
    
    
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
    U1MODEbits.UEN = 0b01;
    
    /* Disable Wake-up through UART
     * 
     * WAKE: Enable Wake-up on Start bit Detect During Sleep Mode bit
     *  1 = Wake-up enabled
     *  0 = Wake-up disabled
     */
    U1MODEbits.WAKE = 0;
    
    /* Disable Loopback mode
     * 
     * LPBACK: UARTx Loopback Mode Select bit
     *  1 = Loopback mode is enabled
     *  0 = Loopback mode is disabled
     */
    U1MODEbits.LPBACK = 0;
    
    
    /* Disable Automatic Baud Rate
     * 
     * ABAUD: Auto-Baud Enable bit
     *  1 = Enable baud rate measurement on the next character ? requires reception of Sync character
     *      (0x55); cleared by hardware upon completion
     *  0 = Baud rate measurement disabled or completed
     */
    U1MODEbits.ABAUD = 0;
    
    /* Use standard logic in UART
     * '0' -> Low
     * '1' -> High
     * 
     * RXINV: Receive Polarity Inversion bit
     *  1 = UxRX Idle state is ?0?
     *  0 = UxRX Idle state is ?1?
     */
    U1MODEbits.RXINV = 0;
}


/* @brief UART enable function
 * @author Pedro Martins
 * 
 * Enables the tranmission (TX) and Reception (RX) modules of the UART 1 and 
 * then activate the UART 1 operation
 * 
 */
void enable_UART1(void){
    ENABLE_UART1_TX;
    U1STAbits.URXEN = 1;
    ENABLE_UART1; 
}


/* @brief UART send char function
 * @author Pedro Martins
 * 
 * Verifies if the UART TX buffer is not full and then sends a character using 
 * the UART1 module
 * 
 */
uint8_t send_char(unsigned char c){
    while(IS_UART1_TX_FULL);
    
        U1TXREG = c;
        return UART_SUCCESS;
    
    //else
    //    return UART_ERROR;
}

/* @brief UART send char function
 * @author Pedro Martins
 * 
 * Verifies if the UART TX buffer is not full and then sends a character using 
 * the UART1 module
 * 
 */
unsigned char read_char(void){
    unsigned char aux;
    send_char('c');
    if(U1STAbits.RIDLE)
        send_char('R');
    if(U1STAbits.FERR)
        send_char('F');
    if(U1STAbits.OERR)
        send_char('O');
    if(U1STAbits.URXDA)
        send_char('D');
    
    while(U1STAbits.RIDLE);
    
    if(U1STAbits.OERR == 1)
    {
        aux = U1RXREG;
        U1STAbits.OERR = 0;
    }
    else
        aux = U1RXREG;
    return aux;

}

uint8_t can_read_UART1(){
    return UART1_RX_HAS_DATA;
}