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
 *                          OPERATION MODE
 ******************************************************************************/
#define USE_INTERRUPTS      //!< If defined, UART 1 pheripheral operates using interruptions and a circular SW buffer


/*******************************************************************************
 *                          MACROS DEFINITION
 ******************************************************************************/
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

#define BREAK_BIT_TRANSMISSION_STATUS  U1STAbits.UTXBRK            //!< Break bit transmission status

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

/** \brief Receiver Buffer Overrun Error Status bit 
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


#define ENABLE_UART1_ERROR_DETECTION_INT     {IEC0bits.U1EIE = 1;}      //!< Enable UART1 Interruption due to errors in Transmission and Reception
#define DISABLE_UART1_ERROR_DETECTION_INT    {IEC0bits.U1EIE = 0;}      //!< Disable UART1 Interruption due to errors in Transmission and Reception
#define ENABLE_UART1_TX_INT                  {IEC0bits.U1TXIE = 1;}     //!< Enable UART1 Transmitter module Interruption 
#define DISABLE_UART1_TX_INT                 {IEC0bits.U1TXIE = 0;}     //!< Disable UART1 Transmitter module Interruption 
#define ENABLE_UART1_RX_INT                  {IEC0bits.U1RXIE = 1;}     //!< Enable UART1 Reception module Interruption 
#define DISABLE_UART1_RX_INT                 {IEC0bits.U1RXIE = 0;}     //!< Disable UART1 Reception module Interruption 


/** \brief Disable all UART 1 Interrupts
 * 
 * Disables Error Detection, Transmission and Reception Interrupts for UART 1
 */
#define DISABLE_UART1_ALL_INTERRUPTS {DISABLE_UART1_ERROR_DETECTION_INT; DISABLE_UART1_TX_INT; DISABLE_UART1_RX_INT;}

/** \brief Enables all UART 1 Interrupts
 * 
 * Enables Error Detection, Transmission and Reception Interrupts for UART 1
 */
#define ENABLE_UART1_ALL_INTERRUPTS  {ENABLE_UART1_ERROR_DETECTION_INT; ENABLE_UART1_TX_INT; ENABLE_UART1_RX_INT;}



/*******************************************************************************
 *                        FUNCTION HEADERS DEFINITION
 ******************************************************************************/

/** \brief UART Configuration Routine
 * 
 * Configures the UART Peripheral General Register, the transmitter and reception 
 * modules 
 * 
 * The baudrate equation is given by \f[Baud-Rate = \frac{F_{PB}}{16 \cdot (UxBRG + 1)}\f]
 * which yelds the value of the baudrate register, \f[UxBRG = \frac{F_{PB}}{16 \cdot Baud-Rate} - 1\f]
 * 
 * \pre    None.
 * \param  baudrate   Desired baudrate for UART operation
 * \param  data_bits  Desired data bits for UART communications
 * \param  parity     Parity tyope desired for UART 
 * \param  stop_bits  Desired number of stop bits for UART communications
 * \return None.
 * 
 * \author Pedro Martins
 */
void config_UART1(uint32_t baudrate, uint8_t data_bits, unsigned char parity, uint8_t stop_bits);


/** \brief Flushes all data from RX buffer
 * 
 * Resets all buffer variables to initial state, flushing all the data
 * 
 * \pre    None.
 * \param  None.
 * \return None.
 * 
 * \author Pedro Martins
 */
void flush_RX_buffer(void);

/** \brief Flushes all data from TX buffer
 * 
 * Resets all buffer variables to initial state, flushing all the data
 * 
 * \pre    UART 1 must be configured
 * \param  None.
 * \return None.
 * 
 * \author Pedro Martins
 */
void flush_TX_buffer(void);


/** \brief Puts a char in the UART Transmitter FIFO
 * 
 * Verifies if the UART TX buffer is not full and then sends a character using 
 * the UART1 module
 * 
 * \pre    UART 1 must be configured
 * \param  c The char to be sent 
 * \return None.
 * 
 * If the macro INTERRUPTS_ON is defined, the routine uses the software circular 
 * buffer  and enables the interrupts related with the TX module, if not enabled 
 * yet. This function halts the code execution until the software TX buffer has 
 * at least one empty space 
 *  
 * If the macro INTERRUPTS_ON is not defined, the routine does not use the 
 * software circular buffer, blocking until the TX FIFO (in hardware) is not full,
 * writing directly the char into the FIFO
 * 
 * 
 * \author Pedro Martins
 */
void put_char(char c);


/** \brief Puts an uint8 number in the UART Transmitter FIFO
 * 
 * Verifies if the UART TX buffer is not full and then sends a character using 
 * the UART1 module
 * 
 * \pre    UART 1 must be configured
 * \param  value The unsigned 8 bit integer to be sent
 * \return None.
 * 
 * This function uses the put_char function and performs the conversion between an
 * 8 bit unsigned integer to two chars.
 * 
 * If the macro INTERRUPTS_ON is defined, this function uses the interrupt driven
 * implementation of put_char 
 *  
 * If the macro INTERRUPTS_ON is not defined, this function uses the put_char 
 * implementation that operates directly on the register level (bypassing the 
 * software circular buffer)
 * 
 * 
 * \author Pedro Martins
 */
void put_uint8(uint8_t value);


/** \brief Puts an uint16 number in the UART Transmitter FIFO
 * 
 * Verifies if the UART TX buffer is not full and then sends a character using 
 * the UART1 module
 * 
 * \pre    UART 1 must be configured
 * \param  value The unsigned 16 bit integer to be sent
 * \return None.
 * 
 * This function uses the put_char function and performs the conversion between an
 * 16 bit unsigned integer to five chars.
 * 
 * If the macro INTERRUPTS_ON is defined, this function uses the interrupt driven
 * implementation of put_char 
 *  
 * If the macro INTERRUPTS_ON is not defined, this function uses the put_char 
 * implementation that operates directly on the register level (bypassing the 
 * software circular buffer)
 * 
 * 
 * \author Pedro Martins
 */
void put_uint16(uint16_t value);


/** \brief Puts a string in the UART Transmitter FIFO
 * 
 * Verifies if the UART TX buffer is not full and then sends a character using 
 * the UART1 module
 * 
 * \pre    UART 1 must be configured
 * \param  *s The address of the char array to be sent
 * \return None.
 * 
 * This function uses the put_char function to send individually each character 
 * of the string
 * 
 * If the macro INTERRUPTS_ON is defined, this function uses the interrupt driven
 * implementation of put_char 
 * 
 * If the macro INTERRUPTS_ON is not defined, this function uses the put_char 
 * implementation that operates directly on the register level (bypassing the 
 * software circular buffer)
 * 
 * 
 * \author Pedro Martins
 */
void put_string(char *s);


/** \brief Gets a char of the UART Reception Buffer
 * 
 * \pre    UART 1 must be configured
 * \param  *p_char The address of the char variable to store the read character
 * \return UART_ERROR if the number of characters in the RX buffer is zero
 * \return UART_SUCCESS if a character is successfully read from the RX buffer
 * 
 * 
 * If the macro  INTERRUPTS_ON is defined, the routine uses the software circular 
 * buffer and enables the interrupts related with the RX module, if not enabled 
 * yet. This function returns an UART_ERROR if called with an empty buffer
 *  
 * If the macro INTERRUPTS_ON is not defined, the routine does not use the 
 * software circular buffer, blocking until the RX FIFO (in hardware) has data 
 * available to be read, getting the char directly from the FIFO
 * 
 * 
 * \author Pedro Martins
 */
uint8_t get_char(char *p_char);


/** \brief Gets an 8 bit unsigned integer of the UART Reception Buffer
 * 
 * 
 * \pre    UART 1 must be configured
 * \param  *p_uint8 The address of the 8 bit unsigned integer variable to store the read number
 * \return UART_ERROR if the number of one of the characters in the RX buffer is zero
 * \return UART_SUCCESS if both characters are successfully read from the RX buffer
 * 
 * This function uses the get_char function and performs the conversion between two
 * characters to an 8 bit unsigned integer.
 * 
 * 
 * If the macro  INTERRUPTS_ON is defined, the routine uses the software circular 
 * buffer and enables the interrupts related with the RX module, if not enabled 
 * yet. This function returns an UART_ERROR if called with an empty buffer
 *  
 * If the macro INTERRUPTS_ON is not defined, the routine does not use the 
 * software circular buffer, blocking until the RX FIFO (in hardware) has data 
 * available to be read, getting the char directly from the FIFO
 * 
 * 
 * \author Pedro Martins
 */
uint8_t get_uint8(uint8_t *p_uint8);

#endif	/* UART1_H */

