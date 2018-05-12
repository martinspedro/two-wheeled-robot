/** 
 * \file   i2c2.h
 * \brief  I2C2 module header file
 * 
 * \author André Gradim
 * \date   Created on May 8, 2018, 7:50 PM
 */

#include <xc.h>

//* ************************************************************************** */
// Section: Interface Functions                                                */
//* ************************************************************************** */

/** \brief Configures and enables I2C2 module
 * 
 * \pre    None
 * \param  None
 * \return None
 * 
 * \author André Gradim
 */
void openI2C2();

/** \brief Disables I2C2 module
 * 
 * \pre    None
 * \param  None
 * \return None
 * 
 * \author André Gradim
 */
void closeI2C2();

/** \brief Send data to dev_address, automatically selects W|!R byte on address
 * 
 * \pre    None
 * \param  dev_address - Device address, data - Array containing the data to send, data_size - Number of bytes to send
 * \return None
 * 
 * \author André Gradim
 */
void masterSend(uint8_t dev_address, uint8_t* data, uint8_t data_size);

/** \brief Gets bytes_to_read bytes from I2C bus into buffer
 * 
 * \pre    None
 * \param  buffer[] - place to hold the bytes, bytes_to_read - n. of bytes to read
 * \return None
 * 
 * \author André Gradim
 */
void masterReceive(uint8_t* buffer,uint8_t bytes_to_read);

/** \brief Check if receive buffer is full
 * 
 * \pre    None
 * \param  None
 * \return 1 when full
 * 
 * \author André Gradim
 */
int dataReadyI2C2(void);

//* ************************************************************************** */
// Section: Internal functions                                                 */
//* ************************************************************************** */

/** \brief Start sequence initializer
 * 
 * \pre    I2C bus must be idle
 * \param  None
 * \return 0 on success
 * 
 * \author André Gradim
 */
int startI2C2();

/** \brief Stop sequence initializer
 * 
 * \pre    I2C bus must be idle
 * \param  None
 * \return 0 on success
 * 
 * \author André Gradim
 */
int stopI2C2();

/** \brief Resytart sequence initializer
 * 
 * \pre    I2C bus must be idle
 * \param  None
 * \return 0 on success
 * 
 * \author André Gradim
 */
int restartI2C2();

/** \brief Send !ACK or NACK sequence
 * 
 * \pre    None
 * \param  !ACK or NACK(0 or 1) as input
 * \return 0 on success, other in case of error
 * 
 * \author André Gradim
 */
int ackI2C2(int ackType);


/** \brief Check if I2C bus is idle
 * 
 * \pre    None
 * \param  None
 * \return 1 when bus is idle
 * 
 * \author André Gradim
 */
int idleI2C2(void);

/** \brief Busy wait until I2C bus is idle
 * 
 * \pre    None
 * \param  None
 * \return None
 * 
 * \author André Gradim
 */
void waitI2C2(void);

/** \brief Enable reception and gets 1 byte from I2C bus
 * 
 * \pre    None
 * \param  None
 * \return 1 when full
 * 
 * \author André Gradim
 */
uint8_t masterReadI2C2(void);

/** \brief Send 1 byte to I2C bus
 * 
 * \pre    None
 * \param  Byte to send
 * \return 0 on success [1 on bus collision (not implemented)]
 * 
 * \author André Gradim
 */
uint8_t masterWriteI2C2(uint8_t data_out);



/* *****************************************************************************
 End of File
 */
