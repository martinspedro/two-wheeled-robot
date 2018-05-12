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

#define I2C1_EI IEC1bits.I2C2MIE = 1;
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
// Section: Interface Functions                                                */
//* ************************************************************************** */

//To active interrupts remove comment (not fully implemented yet)
#define INTERRUPTS_ON

uint8_t insert_i2c_buffer(I2C_MESSAGE_BLOCK* pBuffer){
    if(i2c_buffer.count < I2C_BUFFER_SIZE){
        i2c_buffer.buffer[i2c_buffer.tail] = *pBuffer;
        
        (i2c_buffer.tail == I2C_BUFFER_SIZE)?(i2c_buffer.tail = 0):(i2c_buffer.tail++);

        I2C2_DI
        i2c_buffer.count++;
        I2C1_EI
                
        return 0;
    }
    
    return 1;
}

uint8_t pop_i2c_buffer(I2C_MESSAGE_BLOCK* pBuffer){
    if(i2c_buffer.count > 0){
        pBuffer = &i2c_buffer.buffer[i2c_buffer.head];
    
        (i2c_buffer.head == I2C_BUFFER_SIZE)?(i2c_buffer.head =0):(i2c_buffer.head++);

        I2C2_DI
        i2c_buffer.count--;
        I2C1_EI
        return 0;
    }

    return 1;
}



void openI2C2( ){
    I2C2CONbits.A10M = 0;       //use 7 bit slave address
    //I2C2CONbits.DISSLW = 0;   // slew rate disable for 400kHz
    
    I2C2BRG = 0x02C;            //set the brg for 400kHz
    
    #ifdef INTERRUPTS_ON
    
    i2c_state = S_MASTER_IDLE;

    
    i2c_buffer.count = 0;
    i2c_buffer.head = i2c_buffer.buffer[0];
    i2c_buffer.tail = i2c_buffer.buffer[0];

     
    IEC1bits.I2C2MIE = 1;
    IEC1bits.I2C2SIE = 0;
    IEC1bits.I2C2BIE = 0;
    
    
    #endif

     
    
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
    
    #ifndef INTERRUPTS_ON
        while(I2C2CONbits.SEN == 1);
    #endif
    
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
    
    #ifndef INTERRUPTS_ON
        while(I2C2CONbits.PEN == 1);
    #endif
    
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
    
    #ifndef INTERRUPTS_ON
        while(I2C2CONbits.RSEN == 1);
    #endif
    
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
              
        #ifndef INTERRUPTS_ON
            while(I2C2CONbits.ACKEN == 1);
        #endif
    
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
    #ifndef INTERRUPTS_ON
    while(idleI2C2() == 0 ); 
    #endif
    //master isn't disable (5 least significant bits not 0)
    
    I2C2CONbits.RCEN = 1;
    #ifdef DEBUG_I2C
    putchar('n');
    #endif
    #ifndef INTERRUPTS_ON

    while(I2C2STATbits.RBF == 0); //wait until reception is done
    
    #endif
    //Next it's needed to send acknowledge sequence (|ACK or NACK))
    uint8_t temp = I2C2RCV;
    return temp;
}

uint8_t masterWriteI2C2(uint8_t data_out){
     #ifndef INTERRUPTS_ON
    while(!idleI2C2());
    #endif
    I2C2TRN = data_out;
    
    #ifndef INTERRUPTS_ON
        while(I2C2STATbits.TRSTAT == 1);
    #endif 
    //Next needs to check for |ACK sequence

    //return() -> add bus collision detection
}

void masterSend(uint8_t dev_address, uint8_t* data, uint8_t data_size){
    
    uint8_t  temp_address;
    if( data_size == 0 || data == NULL){ //send a read request
        temp_address = dev_address << 1 | 1;
    }else{
        temp_address = dev_address << 1 | 0;
    }
    
    //send the address byte + |W//R
    do{
        masterWriteI2C2(temp_address);
        while(!idleI2C2());
    }while(!ackCompleteI2C2());
    
    uint8_t index;
    for(index = 0; index < data_size; index++){
        //send each byte of the data
        do{
            masterWriteI2C2(data[index]);
            while(!idleI2C2());
        }while(!ackCompleteI2C2());
    }    
}


void masterReceive(uint8_t* buffer,uint8_t bytes_to_read){
    uint8_t index = 0;
    while( index < bytes_to_read){
        //read from I2C2RCV buffer
        buffer[index] = masterReadI2C2();
        index++;
        
        while(!idleI2C2());
        
        if( I2C2STATbits.I2COV == 1){
            //putchar('O');//return error
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





void __ISR(_I2C2_VECTOR, IPL5SOFT) I2C2_ISR(void){
    
    if(IFS1bits.I2C2BIF == 1){ //Interrupt triggered by bus collision
        
        
    }
    
    
    if(IFS1bits.I2C2MIF == 1){ // Interrupt triggered by master event
        switch(i2c_state){
            case S_MASTER_IDLE:
                if(i2c_buffer.count > 0){
                    if(pop_i2c_buffer(&i2c_message) == 1){
                        while(1);
                    }

                    I2C2_START = 1; 
                    i2c_state = S_MASTER_SEND_ADDR;
                    
                }
            break;

            case S_MASTER_SEND_ADDR:

                /* Start has been sent, send the address byte */

                // extract the information for this message
                uint8_t i2c_address = i2c_message.address;

                //No data to send, it's a read request
                if(i2c_message.length == 0 || i2c_message.pbuffer == NULL){
                    i2c_address = i2c_address << 1 | 1;
                }else{
                    i2c_address = i2c_address << 1 | 0;
                }

                // Transmit the address
                masterWriteI2C2(i2c_address);

                if(i2c_address & 0x01){   //READ
                    // Next state is to wait for address to be acked
                    i2c1_state = S_MASTER_ACK_ADDR;
                }
                else{   //WRITE
                    // Next state is transmit
                    i2c1_state = S_MASTER_SEND_DATA;
                }
            
            break;

            case S_MASTER_SEND_DATA:

                // Make sure the previous byte was acknowledged
                if(I2C_ACK_BIT == 1){
                    // Transmission was not acknowledged
                   
                    // Reset the Ack flag
                    I2C_ACK_BIT= 0;

                    // Send a stop flag and go back to idle
                    stopI2C2();

                }else{
                    // Did we send them all ?
                    if(i2c_message.length-- == 0U){
                        // yup sent them all!

                        // update the trb pointer
                        p_i2c1_trb_current++;

                        // are we done with this string of requests?
                        if(--i2c1_trb_count == 0){
                            I2C1_Stop(I2C1_MESSAGE_COMPLETE);
                        }else{
                            // no!, there are more TRB to be sent.
                            //I2C1_START_CONDITION_ENABLE_BIT = 1;

                            // In some cases, the slave may require
                            // a restart instead of a start. So use this one
                            // instead.
                            I2C1_REPEAT_START_CONDITION_ENABLE_BIT = 1;

                            // start the i2c request
                            i2c1_state = S_MASTER_SEND_ADDR;

                        }
                    }else{
                        // Grab the next data to transmit
                        masterWriteI2C2(i2c_message.pbuffer++);
                    }
                }
            break;
           

        case S_MASTER_RESTART:

            /* check for pending i2c Request */

            // ... trigger a REPEATED START
            I2C1_REPEAT_START_CONDITION_ENABLE_BIT = 1;

            // start the i2c request
            i2c1_state = S_MASTER_SEND_ADDR;

            break;

        case S_MASTER_SEND_ADDR_10BIT_LSB:

            if(I2C1_ACKNOWLEDGE_STATUS_BIT)
            {
                i2c1_object.i2cErrors++;
                I2C1_Stop(I2C1_MESSAGE_ADDRESS_NO_ACK);
            }
            else
            {
                // Remove bit 0 as R/W is never sent here
                I2C1_TRANSMIT_REG = (i2c_address >> 1) & 0x00FF;

                // determine the next state, check R/W
                if(i2c_address & 0x01)
                {
                    // if this is a read we must repeat start
                    // the bus to perform a read
                    i2c1_state = S_MASTER_10BIT_RESTART;
                }
                else
                {
                    // this is a write continue writing data
                    i2c1_state = S_MASTER_SEND_DATA;
                }
            }

            break;

        case S_MASTER_10BIT_RESTART:

            if(I2C1_ACKNOWLEDGE_STATUS_BIT)
            {
                i2c1_object.i2cErrors++;
                I2C1_Stop(I2C1_MESSAGE_ADDRESS_NO_ACK);
            }
            else
            {
                // ACK Status is good
                // restart the bus
                I2C1_REPEAT_START_CONDITION_ENABLE_BIT = 1;

                // fudge the address so S_MASTER_SEND_ADDR works correctly
                // we only do this on a 10-bit address resend
                i2c_address = 0x00F0 | ((i2c_address >> 8) & 0x0006);

                // set the R/W flag
                i2c_address |= 0x0001;

                // set the address restart flag so we do not change the address
                i2c_10bit_address_restart = 1;

                // Resend the address as a read
                i2c1_state = S_MASTER_SEND_ADDR;
            }

            break;

        

        

        case S_MASTER_ACK_ADDR:

            /* Make sure the previous byte was acknowledged */
            if(I2C1_ACKNOWLEDGE_STATUS_BIT)
            {

                // Transmission was not acknowledged
                i2c1_object.i2cErrors++;

                // Send a stop flag and go back to idle
                I2C1_Stop(I2C1_MESSAGE_ADDRESS_NO_ACK);

                // Reset the Ack flag
                I2C1_ACKNOWLEDGE_STATUS_BIT = 0;
            }
            else
            {
                I2C1_RECEIVE_ENABLE_BIT = 1;
                i2c1_state = S_MASTER_ACK_RCV_DATA;
            }
            break;

        case S_MASTER_RCV_DATA:

            /* Acknowledge is completed.  Time for more data */

            // Next thing is to ack the data
            i2c1_state = S_MASTER_ACK_RCV_DATA;

            // Set up to receive a byte of data
            I2C1_RECEIVE_ENABLE_BIT = 1;

            break;

        case S_MASTER_ACK_RCV_DATA:

            // Grab the byte of data received and acknowledge it
            *pi2c_buf_ptr++ = I2C1_RECEIVE_REG;

            // Check if we received them all?
            if(--i2c_bytes_left)
            {

                /* No, there's more to receive */

                // No, bit 7 is clear.  Data is ok
                // Set the flag to acknowledge the data
                I2C1_ACKNOWLEDGE_DATA_BIT = 0;

                // Wait for the acknowledge to complete, then get more
                i2c1_state = S_MASTER_RCV_DATA;
            }
            else
            {

                // Yes, it's the last byte.  Don't ack it
                // Flag that we will nak the data
                I2C1_ACKNOWLEDGE_DATA_BIT = 1;

                I2C1_FunctionComplete();
            }

            // Initiate the acknowledge
            I2C1_ACKNOWLEDGE_ENABLE_BIT = 1;
            break;

        case S_MASTER_RCV_STOP:                
        case S_MASTER_SEND_STOP:

            // Send the stop flag
            I2C1_Stop(I2C1_MESSAGE_COMPLETE);
            break;

        default:

            // This case should not happen, if it does then
            // terminate the transfer
            i2c1_object.i2cErrors++;
            I2C1_Stop(I2C1_LOST_STATE);
            break; 

        }
    }
    
    
}





/* *****************************************************************************
 End of File
 */
