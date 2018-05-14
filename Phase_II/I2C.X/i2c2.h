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


/** \brief Check if receive buffer is full
 * 
 * \pre    None
 * \param  None
 * \return 1 when full
 * 
 * \author André Gradim
 */
int dataReadyI2C2(void);


/** \brief Generic read operation from ic2 device
 * 
 * \pre    None
 * \param  devAddr device address
 * \param  reg Register to read from
 * \param n_bytes # bytes to read
 * \param buffer  Place to store the data
 * \return 0 on success [1 on bus collision (not implemented)]
 * 
 * \author André Gradim
 */
uint8_t readBytes(uint8_t devAddr, uint8_t reg, uint8_t n_bytes, uint8_t* buffer);

/** \brief Single byte read operation from ic2 device
 * 
 * \pre    None
 * \param  devAddr device address
 * \param  reg Register to read from
 * \param buffer  Place to store the data
 * \return 0 on success [1 on bus collision (not implemented)]
 * 
 * \author André Gradim
 */
uint8_t readByte(uint8_t devAddr, uint8_t reg, uint8_t* buffer);

/** \brief Generic write operation from ic2 device
 * 
 * \pre    None
 * \param  devAddr device address
 * \param  reg Register to write to
 * \param  n_bytes # bytes to write
 * \param  buffer  Place where the data to write is stored
 * \return 0 on success [1 on bus collision (not implemented)]
 * 
 * \author André Gradim
 */
uint8_t writeBytes(uint8_t devAddr, uint8_t reg, uint8_t n_bytes, uint8_t* buffer);

/** \brief Single byte write operation to ic2 device
 * 
 * \pre    None
 * \param  devAddr device address
 * \param  reg Register to write to
 * \param  buffer  Place where the data to write is stored
 * \return 0 on success [1 on bus collision (not implemented)]
 * 
 * \author André Gradim
 */
uint8_t writeByte(uint8_t devAddr, uint8_t reg, uint8_t buffer);

/** \brief Write set of bits into byte operation to ic2 device
 * 
 * 
 * \pre    None
 * \param  devAddr device address
 * \param  reg Register to write to
 * \param  bitStart Order of the start bit
 * \param  length Size of the set
 * \param  data  Value of the set of bits
 * \return 0 on success [1 on bus collision (not implemented)]
 * 
 * \author André Gradim
 */
uint8_t writeBits(uint8_t devAddr, uint8_t reg, uint8_t bitStart, uint8_t length, uint8_t data);


/** \brief Write bit into byte operation to ic2 device
 * 
 * \pre    None
 * \param  devAddr device address
 * \param  reg Register to write to
 * \param  bitNum  Number of the bit to change
 * \param data Value of the bit to change
 * \return 0 on success [1 on bus collision (not implemented)]
 * 
 * \author André Gradim
 */
uint8_t writeBit(uint8_t devAddr, uint8_t reg, uint8_t bitNum, uint8_t data); 


/* *****************************************************************************
 End of File
 */
