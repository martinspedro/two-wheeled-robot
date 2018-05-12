/** 
 * \file   uart1.h
 * \brief  UART1 Device Driver Header File
 * 
 * \author Pedro Martins
 * \date   Created on March 19, 2018, 8:48 PM
 */


#ifndef UART1_H
#define	UART1_H

#include <xc.h>


/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
#define BLOCKING_MODE       //!< If defined, UART 1 pheripheral operates without interruptions, using blocking routines

#define UART_ERROR   1      //!< Return value macro that indicates an error has occurred
#define UART_SUCCESS 0      //!< Return value macro that indicates the operation terminated succesfully 

#define ENABLE_UART1     {U1MODEbits.ON = 1;}     //!< Enable UART 1 Pheripheral
#define DISABLE_UART1    {U1MODEbits.ON = 0;}     //!< Disable UART 1 Pheripheral
#define ENABLE_UART1_TX  {U1STAbits.UTXEN = 1;}   //!< Enable UART 1 Transmitter module
#define DISABLE_UART1_TX {U1STAbits.UTXEN = 0;}   //!< Disable UART 1 Transmitter module
#define ENABLE_UART1_RX  {U1STAbits.URXEN = 1;}   //!< Enable UART 1 Receiver module
#define DISABLE_UART1_RX {U1STAbits.URXEN = 1;}   //!< Disable UART 1 Receiver module


#define TRANSMIT_BREAK_BIT             {U1STAbits.UTXBRK = 1;}      //!< Transmit a break bit on the next transmission
#define DISABLE_BREAK_BIT_TRANSMISSION {U1STAbits.UTXBRK = 0;}      //!< Disable Break Transmission
#define BREAK_BIT_TRANSMISSION_STATUS   U1STAbits.UTXBRK            //!< Break bit transmission status

#define ENABLE_UART1_PHERIPHERAL  {ENABLE_UART1_TX; ENABLE_UART1_RX; ENABLE_UART1;}     //!< Enables UART1 Pheripheral, TX and RX Modules
#define DISABLE_UART1_PHERIPHERAL {DISABLE_UART1_TX; DISABLE_UART1_RX; DISABLE_UART1;}  //!< Disables UART1 Pheripheral, TX and RX Modules


/** \brief Transmit buffer full status. 
 * \return 1 if the TX buffer is full, 
 * \return 0 if at least one more character can be written in the TX buffer
 */
#define UART1_TX_FULL_STATUS                 U1STAbits.UTXBF     

/** \brief Transmit Shift Register (U1TSR) empty status.
 *  \return 1 if the last transmission is completed (both the shift register and  
 *            the transmit buffer are empty)
 *  \return 0 if a transmission is in progressed/queued in the TX buffer
 */
#define UART1_TX_SHIFT_REGISTER_EMPTY_STATUS U1STAbits.TRMT      

/** \brief Receiver Idle status (U1RSR register)
 * \return 1 if RX is idle 
 * \return 0 if data is being received
 */
#define UART1_RX_IDDLE_STATUS                U1STAbits.RIDLE   

/** \brief Receive Buffer Data Available bit
 * 
 * \return 1 if buffer has data (at least one more character can be read)
 * \return 0 if the RX buffer is empty
 */
#define UART1_RX_DATA_AVAILABLE_STATUS       U1STAbits.URXDA    

#define UART1_PARITY_ERROR_OCCURRED  U1STAbits.PERR     //!< Parity Error Status bit \return 1 if an error as been detected for the current character
#define UART1_FRAMING_ERROR_OCCURRED U1STAbits.FERR     //!< Framing Error Status bit \return 1 if an error as been detected for the current character

/** \briefReceiver Buffer Overrun Error Status bit 
 * 
 * The bit is set in hardware and can be cleared using the macro CLEAR_OVERRUN_ERROR_FLAG
 * Clear the OERR flag resets the RX buffer and the RSR to empty state
 * 
 * \return 1 if the RX buffer has overflowed
 * \return 0 if the RX buffer has not overflowed
 */
#define UART1_OVERRUN_ERROR_OCCURRED U1STAbits.OERR     

/** \brief Clear Overrun error flag. 
 * 
 * Resets the Receiver buffer and RSR to empty state
 */
#define CLEAR_OVERRUN_ERROR_FLAG {U1STAbits.OERR = 0;}      


#define ENABLE_UART1_ERROR_DETECTION_INT     {IEC0bits.U1EIE = 1;}
#define DISABLE_UART1_ERROR_DETECTION_INT    {IEC0bits.U1EIE = 0;}
#define ENABLE_UART1_TX_INT                  {IEC0bits.U1TXIE = 1;}
#define DISABLE_UART1_TX_INT                 {IEC0bits.U1TXIE = 0;}
#define ENABLE_UART1_RX_INT                  {IEC0bits.U1RXIE = 1;}
#define DISABLE_UART1_RX_INT                 {IEC0bits.U1RXIE = 0;}


#define DISABLE_UART1_ALL_INTERRUPTS  {DISABLE_UART1_ERROR_DETECTION_INT; DISABLE_UART1_TX_INT; DISABLE_UART1_RX_INT;}
#define ENABLE_UART1_ALL_INTERRUPTS  {ENABLE_UART1_ERROR_DETECTION_INT; ENABLE_UART1_TX_INT; ENABLE_UART1_RX_INT;}

/*******************************************************************************
 *                        FUNCTION HEADERS DEFINITION
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
void config_UART1(uint32_t baudrate, uint8_t data_bits, unsigned char parity, uint8_t stop_bits);



uint8_t send_char(unsigned char c);
uint8_t print_uint8(uint8_t value);
uint8_t print_uint16(uint16_t value);
uint8_t read_uint8(void);

void flush_RX_buffer(void);
void flush_TX_buffer(void);
void put_char(char c);
void put_string(char *s);
uint8_t get_char(char *pchar);

#endif	/* UART1_H */

