#include "mpu6050.h"
#include "../I2C.X/i2c2.h"

void init_MPU(void)
{
    
    
   /* uint8_t data = 0x80;
    
    writeBytes(MPU6050_DEFAULT_ADDRESS,MPU6050_RA_PWR_MGMT_1,1, &data);
    
    data = 0x07;
    writeBytes(MPU6050_DEFAULT_ADDRESS,MPU6050_RA_SMPLRT_DIV,1, &data);
    
    uint8_t data1[] = {0x01,0x00};
    writeBytes(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, 2,data1);
    
    uint8_t data2[] = {0x00,0x00};
    writeBytes(MPU6050_DEFAULT_ADDRESS,MPU6050_RA_GYRO_CONFIG,2, data2);
    */
    setClockSource(MPU6050_CLOCK_PLL_XGYRO);
    setFullScaleGyroRange(MPU6050_GYRO_FS_1000);
    setFullScaleAccelRange(MPU6050_ACCEL_FS_8);
    setSleepEnabled(0); // thanks to Jack Elston for pointing this one out!
    
   
}


void readMPU(MPU6050_data* Sensor){
    uint8_t number_bytes_read = 14;
    uint8_t rx_bytes[14];
    
    
    readBytes(MPU6050_DEFAULT_ADDRESS,MPU6050_RA_ACCEL_XOUT_H,number_bytes_read, rx_bytes );
    put_char('o');
    //I2C comms done
    
    (*Sensor).Accel.X= rx_bytes[0]<<8 | rx_bytes[1];
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


void read_data(uint16_t* a1,uint16_t* a2, uint16_t* a3, uint16_t* g1, uint16_t* g2, uint16_t* g3, uint16_t* temp){

    uint8_t number_bytes_read = 14;
    uint8_t rx_bytes[14];
    
    
    readBytes(MPU6050_DEFAULT_ADDRESS,MPU6050_RA_ACCEL_XOUT_H,number_bytes_read, rx_bytes );
    
    
    //I2C comms done
    
    *a1= rx_bytes[0]<<8 | rx_bytes[1];
    *a2= rx_bytes[2]<<8 | rx_bytes[3];
    *a3= rx_bytes[4]<<8 | rx_bytes[5];
    
    uint16_t temperature = rx_bytes[6]<<8 | rx_bytes[7];
    *g1= rx_bytes[8]<<8 | rx_bytes[9];
    *g2 = rx_bytes[10]<<8 | rx_bytes[11];
    *g3 = rx_bytes[12]<<8 | rx_bytes[13];
    
    //Temperature convertion from the MPU datasheet
    //temp =  temp/340 + 36.53 = (temp+12420.2))/340
    temperature = temperature + 12420;
    temperature = temperature/340;
    
    *temp = temperature;

}

void setClockSource(uint8_t source) {
    writeBits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);
}

void setFullScaleGyroRange(uint8_t range) {
    writeBits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
}

void setFullScaleAccelRange(uint8_t range) {
    writeBits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);
}
void setSleepEnabled(uint8_t enabled) {
    writeBit(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, enabled);
}


