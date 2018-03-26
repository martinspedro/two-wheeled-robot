/* 
 * File:   uart1.h
 * Author: martinspedro
 *
 * Created on March 19, 2018, 8:48 PM
 */

#ifndef UART1_H
#define	UART1_H

#ifdef	__cplusplus
extern "C" {
#endif

void config_UART1(uint32_t baudrate, uint8_t data_bits, unsigned char parity, uint8_t stop_bits);
void enable_UART1(void);
uint8_t can_read_UART1(void);

#ifdef	__cplusplus
}
#endif

#endif	/* UART1_H */

