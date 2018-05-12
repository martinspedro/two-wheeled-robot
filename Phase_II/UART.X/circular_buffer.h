/** 
 * \file   circular_buffer.h
 * \brief  Circular buffer implementation Header File
 * 
 * \author Pedro Martins
 * \date   Created on May 12, 2018, 14:00
 */

#define BUF_SIZE 8                  //!< Length of the circular buffer
#define INDEX_MASK	(BUF_SIZE - 1)	//!< Mask to perform circular buffer arithmetic increment/decrement

/** \struct circularBuffer
 * 
 * \brief Circular Buffer for UART TX and RX registers
 * 
 * \var circularBuffer::head 
 *      HEAD of the circular buffer. Oldest element of the buffer
 * \var circularBuffer::tail 
 *      TAIL of the circular buffer. Newest element of the buffer
 * \var circularBuffer::count 
 *      Number of elements in the buffer not yet processed.
 * \var circularBuffer::overrun 
 *      Flag to signal an overrun error
 */
typedef struct
{
    unsigned char data[BUF_SIZE];	// data of the buffer
    uint8_t head;
    uint8_t tail;
    uint8_t count;			  
    uint8_t overrun;
} circularBuffer;


