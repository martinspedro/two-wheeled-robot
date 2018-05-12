/** 
 * \file   circular_buffer.h
 * \brief  Circular buffer implementation Header File
 * 
 * \author Pedro Martins
 * \date   Created on May 12, 2018, 14:00
 */

#define BUF_SIZE 8                  // length of the circular buffer
#define INDEX_MASK	(BUF_SIZE - 1)	// mask to increment the counter

// structure of the circular buffer to use in the device driver
typedef struct
{
    unsigned char data[BUF_SIZE];	// data of the buffer
    uint8_t head;			// oldest element of the buffer
    uint8_t tail;			// newest element of the buffer
    uint8_t count;			// Number of caracters in buffer not yet processed
                                // (either to send to UART or to read from UART
    uint8_t overrun;
} circularBuffer;


