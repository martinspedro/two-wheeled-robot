/* ************************************************************************** */
/** UART1 Configuration

 */
#include <xc-pic32m.h>
#include <xc.h>

void configureUART1(int baudrate, int frequency){
    
    //configuração da UART
    //UxMODE
    U1MODEbits.ON = 1;      //ON: UARTx Enable bit 
                            //| 1 - Enabled | 0 - Disabled
    U1MODEbits.SIDL = 0;    //SIDL: Stop In IDLE Mode bit
                            //| 1 - Discontinue | 0 - Continue
    U1MODEbits.IREN = 0;    // IrDA Encoder and Decoder Enable bit
                            //| 1- IrDA enabled | 0 - IrDA disabled
    U1MODEbits.RTSMD = 0;   //RTSMD: Mode selection for UxRTS Pin bit
                            //| 1 - UxRTS is in simplex mode | 0 - UxRTS is in Flow control mode
    U1MODEbits.UEN = 00;    //UEN: UARTx enable bits
                            //11 = UxTX, UxRX and UxBCLK pins are enabled and used; UxCTS pin is controlled by corresponding bits in the PORTx register
                            //10 = UxTX, UxRX, UxCTS and UxRTS pins are enabled and used
                            //01 = UxTX, UxRX and UxRTS pins are enabled and used; UxCTS pin is controlled by corresponding bits in the PORTx register
                            //00 = UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/UxBCLK pins are controlled by corresponding bits in the PORTx register
    U1MODEbits.WAKE = 0;    //WAKE: Enable Wake-up on Start bit Detect During Sleep Mode bit
                            //1 = Wake-up is enabled
                            //0 = Wake-up is disabled 
    U1MODEbits.LPBACK = 0;  //LPBACK: UARTx Loopback Mode Select bit
                            //1 = Loopback mode is enabled
                            //0 = Loopback mode is disabled    
    U1MODEbits.ABAUD = 0;
    U1MODEbits.RXINV = 0;
    U1MODEbits.BRGH = 1;
    U1MODEbits.PDSEL0 = 0;
    U1MODEbits.PDSEL1 = 0;
    U1MODEbits.STSEL = 0;
    
    U1STAbits.ADM_EN = 0;
    U1STAbits.ADDR = 0x0;
    U1STAbits.UTXISEL = 0x0;
    U1STAbits.UTXINV = 0;
    U1STAbits.URXEN = 1;
    U1STAbits.UTXBRK = 0;
    U1STAbits.UTXEN = 1;
    U1STAbits.URXISEL = 0x0;
    U1STAbits.ADDEN = 0;
    U1STAbits.OERR = 0;
    //baudrate 
    //U1BRG = ((frequency/(4*baudrate))-1);
    
    U1BRG = 0x56;
    __XC_UART = 1;
    
}

char getChar(){
    
    //if(OERR == 1)
    while(U1STAbits.URXDA == 0);
    return U1RXREG;
    
}
void putChar(char inputChar){
    while(U1STAbits.UTXBF == 1);
    U1TXREG = inputChar;
    
}




