#include "mpu6050.h"
#include "i2c2.h"

void init_MPU(void)
{
    startI2C2();
    uint8_t data[] = { MPU6050_RA_PWR_MGMT_1, 0x80};
    
    masterSend(MPU6050_DEFAULT_ADDRESS, data, 2);
    
    //free(data);
    restartI2C2();
    
    uint8_t data1[] = { MPU6050_RA_SMPLRT_DIV, 0x07};
    masterSend(MPU6050_DEFAULT_ADDRESS, data,2);
    
    //free(data1);
    
    restartI2C2();
    
    uint8_t data2[] = { MPU6050_RA_PWR_MGMT_1,0x01,0x00};
    masterSend(MPU6050_DEFAULT_ADDRESS, data,3);
        
    //free(data2);

    restartI2C2();
    
    uint8_t data3[] = { MPU6050_RA_GYRO_CONFIG,0x00,0x00};
    masterSend(MPU6050_DEFAULT_ADDRESS, data,3);
        
    //free(data3);

    stopI2C2();
    
}


void readMPU(MPU6050_data* Sensor){
    startI2C2();
    uint8_t data[]={MPU6050_RA_ACCEL_XOUT_H};
    masterSend(MPU6050_DEFAULT_ADDRESS, data,1);
    
    restartI2C2();
    masterSend(MPU6050_DEFAULT_ADDRESS, NULL,0);
    
    uint8_t number_bytes_read = 14;
    uint8_t rx_bytes[14];
    
    masterReceive(rx_bytes, number_bytes_read);
    
    stopI2C2();
    
    //I2C comms done
    
    Sensor->Accel.X= rx_bytes[0]<<8 | rx_bytes[1];
    Sensor->Accel.Y= rx_bytes[2]<<8 | rx_bytes[3];
    Sensor->Accel.Z= rx_bytes[4]<<8 | rx_bytes[5];
    
    uint32_t temp = rx_bytes[6]<<8 | rx_bytes[7];
    Sensor->Gyro.X = rx_bytes[8]<<8 | rx_bytes[9];
    Sensor->Gyro.Y = rx_bytes[10]<<8 | rx_bytes[11];
    Sensor->Gyro.Z = rx_bytes[12]<<8 | rx_bytes[13];
    
    //Temperature convertion from the MPU datasheet
    //temp =  temp/340 + 36.53 = (temp+12420.2))/340
    temp = temp + 12420;
    temp = temp/340;
    
    Sensor-> Temperature = temp;
    
}
/*
void MPU6050_testConnection()
{  
    I2C_Master_Start();
    I2C_Master_Write( MPU6050_WR_ADDRESS);
    I2C_Master_Write( MPU6050_RA_WHO_AM_I);
    
    I2C_Master_Restart();
    I2C_Master_Write(MPU6050_RD_ADDRESS);
    uint16_t WHO = I2C_Master_Read(NACK);
    I2C_Master_Stop();
    
//    char str1[] = "\n/************ \nAddress = ";
//    char str2[] = "\n/************ \n";
//    vspfunc("%s %d %s", str1, WHO, str2);
//    UART_send_string(getBuffer());
    
    UART_send_string("\n/************ \n");
    UART_send_string("Address = ");
    UART_send_int(WHO);
    UART_send_string("\n/************ \n");
}

void MPU6050_ReadReg(uint8_t reg)
{  
    I2C_Master_Start();
    I2C_Master_Write( MPU6050_WR_ADDRESS);
    I2C_Master_Write( reg );
    
    I2C_Master_Restart();
    I2C_Master_Write(MPU6050_RD_ADDRESS);
    uint16_t regContents = I2C_Master_Read(NACK);
    I2C_Master_Stop();
    
    UART_send_string("\n/************ \n");
    UART_send_string("Register = ");
    UART_send_int(regContents);
    UART_send_string("\n/************ \n");
}
*/