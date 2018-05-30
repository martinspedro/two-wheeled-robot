/** 
 * \file   i2c2.c
 * \brief  I2C2 module configuration and device driver
 * 
 * \author André Gradim
 * \date   Created on May 8, 2018, 7:50 PM
 */
#include <proc/p32mx795f512l.h>
#include "i2c2.h"
#include "../interrupts.h"


//* ************************************************************************** */
// Section: Macros                                                             */
//* ************************************************************************** */

//To active interrupts remove comment (not fully implemented yet)
//#define INTERRUPTS_ON



#define I2C2_EI IEC1bits.I2C2MIE = 1;
#define I2C2_DI IEC1bits.I2C2MIE = 0;

#define I2C2_START      I2C2CONbits.SEN         // I2C START control bit.
#define I2C2_STOP       I2C2CONbits.PEN         // I2C STOP control bit.
#define I2C2_RESTART    I2C2CONbits.RSEN        // I2C Repeated START control bit.
#define I2C2_RCEN       I2C2CONbits.RCEN        // I2C Receive enable control bit
#define I2C_ACKDT       I2C2CONbits.ACKDT       // I2C ACK data control bit.
#define I2C_ACKEN       I2C2CONbits.ACKEN       // I2C ACK start control bit.

#define I2C_WC_BIT      I2C1STATbits.IWCOL      // Defines the write collision status bit.
#define I2C_ACK_BIT     I2C1STATbits.ACKSTAT    // I2C ACK status bit.

#define NACK 1
#define ACK 0

#define I2C_BUFFER_SIZE 8

typedef enum{
    S_MASTER_IDLE,
    S_MASTER_RESTART,
    S_MASTER_SEND_ADDR,
    S_MASTER_SEND_DATA,
    S_MASTER_SEND_STOP,
    S_MASTER_ACK_ADDR,
    S_MASTER_RCV_DATA,
    S_MASTER_RCV_STOP,
    S_MASTER_ACK_RCV_DATA,
    S_MASTER_NOACK_STOP,
    S_MASTER_SEND_ADDR_10BIT_LSB,
    S_MASTER_10BIT_RESTART,
    
} I2C_MASTER_STATES;

typedef struct{
    uint8_t  address;           // Bits <7:1> are the 7 bit address
                                // Bit 0 is R/W (1 for read)
    uint8_t   length;           // the # of bytes in the buffer
    uint8_t   *pbuffer;         // a pointer to a buffer of length bytes
} I2C_MESSAGE_BLOCK;


typedef struct{
    I2C_MESSAGE_BLOCK buffer[I2C_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t count;
}I2C_BUFFER;


//* ************************************************************************** */
// Section: Local Variables                                                    */
//* ************************************************************************** */

static I2C_MASTER_STATES i2c_state = S_MASTER_IDLE;
static I2C_BUFFER i2c_buffer;
static I2C_MESSAGE_BLOCK i2c_message;


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

/** \brief Send data to dev_address, automatically selects W|!R byte on address
 * 
 * \pre    None
 * \param  dev_address - Device address, data - Array containing the data to send, data_size - Number of bytes to send
 * \return 0 on success, 1 when NACK
 * 
 * \author André Gradim
 */
uint8_t masterSend(uint8_t dev_address, uint8_t* data, uint8_t data_size);

/** \brief Gets bytes_to_read bytes from I2C bus into buffer
 * 
 * \pre    None
 * \param  buffer[] - place to hold the bytes, bytes_to_read - n. of bytes to read
 * \return None
 * 
 * \author André Gradim
 */
void masterReceive(uint8_t* buffer,uint8_t bytes_to_read);



//* ************************************************************************** */
// Section: Interface Functions                                                */
//* ************************************************************************** */

void openI2C2( ){
    I2C2CONbits.ON = 0;         // make sure the module is disabled
    
    //I2C2CONbits.DISSLW = 0;   // slew rate disable for 400kHz
    
    I2C2BRG = 0x02C;            //set the brg for 400kHz
    
   

    I2C2CONbits.ON = 1;         // enable i2c2 module
}



void closeI2C2(){
    I2C2CONbits.ON = 0;         // Disable module
}

int startI2C2(){
    /* This routine starts a Start condition
     * on success returns 0
     * 
     */
    // Needs that the 5 least sig. bits of I2C2CONbits are 0
    if( idleI2C2() == 0){
        return 2;
    }
     
    I2C2CONbits.SEN = 1; //activate start condition bit
    
    while(I2C2CONbits.SEN == 1);
    
    if(I2C2STATbits.BCL == 1){
        return 1;
    }else{
        return 0;
    } 
}

int stopI2C2(){
    /* This routine starts a Stop condition
     * on success returns 0
     *  
     */
    // Needs that the 5 least sig. bits of I2C2CONbits are 0
    if( idleI2C2() == 0){
        return 2;
    }
     
    I2C2CONbits.PEN = 1; //activate stop condition bit

    #ifdef INTERRUPTS_ON
        i2c_state = S_MASTER_IDLE;
    #endif
    
    while(I2C2CONbits.PEN == 1);
    
    if(I2C2STATbits.BCL == 1){
        return 1;
    }else{
        return 0;
    } 
}

int restartI2C2(){
    /* This routine starts a ReStart condition
     * on success returns 0
     *  
     */
    
    // Needs that the 5 least sig. bits of I2C2CONbits are 0
    if( idleI2C2() == 0){
        return 2;
    }
     
    I2C2CONbits.RSEN = 1; //activate restart condition bit
    
        while(I2C2CONbits.RSEN == 1);
    
    if(I2C2STATbits.BCL == 1){
        return 1;
    }else{
        return 0;
    } 
}


/* ackI2C2 - generate ack signal for slave
 * checks if master is disabled and initializes the ack sequence 
 * 
 * ackType -> 0 for |ACK and 1 for NACK
 * 
 */

int ackI2C2(int ackType){
    
    I2C2CONbits.ACKDT = ackType;
    
    if( idleI2C2() ){        
        I2C2CONbits.ACKEN = 1;
              
            while(I2C2CONbits.ACKEN == 1);
        
        return 0;
    }else{
        return 1;
    }    
}

int ackCompleteI2C2(){
    return (I2C2STATbits.ACKSTAT == 0); // slave received good data
}

int idleI2C2(void){
    /* Wait until I2C Bus is Inactive */
    return !(I2C2CONbits.SEN || I2C2CONbits.PEN || I2C2CONbits.RSEN || 
            I2C2CONbits.RCEN || I2C2CONbits.ACKEN || I2C2STATbits.TRSTAT);
}


void waitI2C2(void){
    /*waitI2C2 - blocking way of forcing the line to wait until idle
     */
    while(!idleI2C2());
}


int dataReadyI2C2(void){
    return (I2C2STATbits.RBF);
}


uint8_t masterReadI2C2(void){
    while(idleI2C2() == 0 ); 
    
    //master isn't disable (5 least significant bits not 0)
    
    I2C2CONbits.RCEN = 1;
    #ifdef DEBUG_I2C
    putchar('n');
    #endif

    

    while(I2C2STATbits.RBF == 0); //wait until reception is done
    
    

    //Next it's needed to send acknowledge sequence (|ACK or NACK))
    uint8_t aux =I2C2RCV;
    return aux;
    
}

uint8_t masterWriteI2C2(uint8_t data_out){
    
    while(!idleI2C2());
    
    I2C2TRN = data_out;
    
   
    while(I2C2STATbits.TRSTAT == 1);
    
    
    


    //return() -> add bus collision detection
}

uint8_t masterSend(uint8_t dev_address, uint8_t* data, uint8_t data_size){
    
    uint8_t  temp_address;
    if( data_size == 0 || data == NULL){ //send a read request
        temp_address = dev_address << 1 | 1;
    }else{
        temp_address = dev_address << 1 | 0;
    }
    
    //send the address byte + |W//R
    //do{
        masterWriteI2C2(temp_address);
        
        if(I2C2STATbits.ACKSTAT != 0){
            return 1;
        }
        
        
        while(!idleI2C2());
    //}while(!ackCompleteI2C2());
    
    uint8_t index;
    for(index = 0; index < data_size; index++){
        //send each byte of the data
        //do{
            masterWriteI2C2(data[index]);
            while(!idleI2C2());
            
            if(I2C2STATbits.ACKSTAT != 0){
                return 1;
            }
        //}while(!ackCompleteI2C2());
    }  
    return 0;
}


void masterReceive(uint8_t* buffer,uint8_t bytes_to_read){
    uint8_t index = 0;
    while( index < bytes_to_read){
        //read from I2C2RCV buffer
        buffer[index] = masterReadI2C2();
        index++;
        
        while(!idleI2C2());
        
        if( I2C2STATbits.I2COV == 1){
            I2C2STATbits.I2COV = 0;
            put_string("ERROR::............................");
        }

        if (index == bytes_to_read){
            //No more to receive, send NACK to terminate transaction
            ackI2C2(NACK);
        }else{
            //Send ACK to acknowledge and continue
            ackI2C2(ACK);
        }
    }
}

uint8_t readBytes(uint8_t devAddr, uint8_t reg, uint8_t n_bytes, uint8_t* buffer){
    startI2C2();
    if(masterSend(devAddr, &reg,1)){
        *buffer = 0x00;
        return 1;
    }
    
    restartI2C2();
    if(masterSend(devAddr, NULL,0)){
        *buffer = 0x00;
        return 1;
    }
    
    masterReceive(buffer, n_bytes);
    
    stopI2C2();
    //implement error detection
    
    return 0;
}

uint8_t readByte(uint8_t devAddr, uint8_t reg, uint8_t* buffer){
    *buffer = 0;
    return readBytes(devAddr,reg,1,buffer);
}

int8_t readBits(uint8_t devAddr, uint8_t reg, uint8_t bitStart, uint8_t length, uint8_t *data, uint16_t timeout) {
    // 01101001 read byte
    // 76543210 bit numbers
    //    xxx   args: bitStart=4, length=3
    //    010   masked
    //   -> 010 shifted
    uint8_t b;
    if (readByte(devAddr, reg, &b) == 0) {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        b &= mask;
        b >>= (bitStart - length + 1);
        *data = b;
        return 0;
    }
    return 1;
}

int8_t readBit(uint8_t devAddr, uint8_t reg, uint8_t bitNum, uint8_t *data) {
    uint8_t b;
    if(readByte(devAddr, reg, &b)) return 1;
    *data = b & (1 << bitNum);
    return 0;
}



uint8_t writeBytes(uint8_t devAddr, uint8_t reg, uint8_t n_bytes, uint8_t* buffer){
    startI2C2();
    
    uint8_t temp[n_bytes + 1];
    temp[0] =  reg;
    
    uint8_t i = 0;
    
    for( i = 0; i < n_bytes; i++){
        temp[i+1] = buffer[i];
    }
    
    
    uint8_t error = masterSend(devAddr, temp, n_bytes + 1);
    
    stopI2C2();
    //implement error detection
    if(error) return 1;
    return 0;
}

uint8_t writeByte(uint8_t devAddr, uint8_t reg, uint8_t buffer){
    return writeBytes(devAddr,reg,1, &buffer);
}



uint8_t writeBits(uint8_t devAddr, uint8_t reg, uint8_t bitStart, uint8_t length, uint8_t data) {
    
    uint8_t b;
    if (readBytes(devAddr, reg,1, &b) == 0) {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        data <<= (bitStart - length + 1);
        data &= mask;
        b &= ~(mask);
        b |= data; 
        if(writeBytes(devAddr, reg,1, &b)) return 1;
        return 0;
    } else {
        return 1;
    }
}

uint8_t writeBit(uint8_t devAddr, uint8_t reg, uint8_t bitNum, uint8_t data) {
    uint8_t b;
    if(readBytes(devAddr, reg,1, &b)) return 1;
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
    return writeBytes(devAddr, reg,1, &b);
}


uint8_t i2c_ping(uint8_t* pointer){
    //uint8_t array[10]; -> 
    uint8_t count=0;

    uint8_t address = 0; 
     
    uint8_t attempt;
    
    //for(address = 1; address < 0x7F; address++){
    uint8_t temp;
    
    
    for(address = 0x0F; address < 0x7F;address++){
        startI2C2();
        attempt = masterSend(address,&temp,1);
        stopI2C2();
        if(attempt == 0){
            *pointer = address;
            pointer++;  
            count++;
        }
    }
    
    return count;
        
    //}

}
void clearI2CBuffer(){
    uint8_t temp1=I2C2RCV;
    I2C2STATbits.I2COV = 0;
}







/* *****************************************************************************
 End of File
 */
