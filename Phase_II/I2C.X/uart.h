/* ************************************************************************** */
/** UART configuration

 */
/* ************************************************************************** */

#ifndef _UART_1    /* Guard against multiple inclusion */
#define _UART_1

void configureUART1(int baudrate, int frequency);

char getChar();
void putChar(char inputChar);




#endif /* _UART_1 */

/* *****************************************************************************
 End of File
 */
