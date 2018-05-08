/* ************************************************************************** */

#include <proc/p32mx795f512l.h>

#include "i2c1.h"

/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************

#define NACK 1
#define ACK 0


#define masterDisabled() (I2C2CONbits.SEN == 0 && I2C2CONbits.PEN == 0 && \
    I2C2CONbits.RSEN == 0 && I2C2CONbits.RCEN == 0 && I2C2CONbits.ACKEN == 0)


void openI2C2( ){//int sendAck){
    
    I2C2CONbits.A10M = 0; //7 bit slave address
    //I2C2CONbits.DISSLW = 0;
    
    /*if(sendAck == 1){
        I2C2CONbits.ACKDT = 0; //|ACKs sent
    }else{
        I2C2CONbits.ACKDT = 1; //NACK sent
    }*/
    
    I2C2BRG = 0x02C; //set the brg for 400kHz
    
    I2C2CONbits.ON = 1;   
}



void closeI2C2(){
    
    // simply disable the module
    
    I2C2CONbits.ON = 0;
    
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

unsigned char masterReadI2C2(void){
    
    while(idleI2C2() == 0 ); 
    //master isn't disable (5 least significant bits not 0)
    
    I2C2CONbits.RCEN = 1;
    putchar('n');
    //#ifndef INTERRUPTS_ON
    while(I2C2STATbits.RBF == 0); //wait until reception is done
    //#endif
    //Next it's needed to send acknowledge sequence (|ACK or NACK))
    unsigned char temp = I2C2RCV;
    return temp;
}

uint8_t masterWriteI2C2(uint8_t data_out){
    while(!idleI2C2());
    I2C2TRN = data_out;
    
    #ifndef INTERRUPTS_ON
        while(I2C2STATbits.TRSTAT == 1);
    #endif 
    //Next needs to check for |ACK sequence
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
            putchar('O');//return error
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





/* *****************************************************************************
 End of File
 */
