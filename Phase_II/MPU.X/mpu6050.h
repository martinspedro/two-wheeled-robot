/* 
 * File:   mpu6050.h
 * Author: Andr� Gradim
 *
 * Created on May 4, 2018, 7:15 PM
 */

#include <stdint.h>



#ifndef MPU6050_H
#define	MPU6050_H


typedef struct
{
    uint16_t X;
    uint16_t Y;
    uint16_t Z;
}MPU_reading;

typedef struct
{
 struct
 {
  int16_t X;
  int16_t Y;
  int16_t Z;
 }Accel;
 int16_t Temperature;
 struct
 {
  int16_t X;
  int16_t Y;
  int16_t Z;
 }Gyro;
}MPU6050_data;

// MPU 6050 functions

/** \brief Initialize MPU6050 registers for normal operation
 * 
 * \pre    Must be the first functioin to run
 * \param  None
 * \return None
 * 
 * \author André Gradim
 */
void init_MPU(void);

/** \brief Read accel,gyro and temp. data into separate pointers
 * 
 * \pre    Device must be initialized
 * \param  v1 struct with 3 uint16_t
 * \param  v2 struct with 3 uint16_t
 * \param  temp variable to store temp. data
 * \return None
 * 
 * \author André Gradim
 */
void read_data(uint16_t* a1,uint16_t* a2, uint16_t* a3, uint16_t* g1, uint16_t* g2, uint16_t* g3, uint16_t* temp);


/** \brief Get accel. offset X
 * 
 * \pre    None
 * \return Offset value
 * 
 * \author André Gradim
 */
int16_t getXAccelOffset();

/** \brief Set accel. offset X
 * 
 * \pre    None
 * \param offset Offset value
 * \return None
 * 
 * \author André Gradim
 */
void setXAccelOffset(int16_t offset);


/** \brief Get accel. offset Y
 * 
 * \pre    None
 * \return Offset value
 * 
 * \author André Gradim
 */
int16_t getYAccelOffset();
/** \brief Set accel. offset Y
 * 
 * \pre    None
 * \param offset Offset value
 * \return None
 * 
 * \author André Gradim
 */
void setYAccelOffset(int16_t offset);


/** \brief Get accel. offset Z
 * 
 * \pre    None
 * \return Offset value
 * 
 * \author André Gradim
 */
int16_t getZAccelOffset();

/** \brief Set accel. offset Z
 * 
 * \pre    None
 * \param offset Offset value
 * \return None
 * 
 * \author André Gradim
 */
void setZAccelOffset(int16_t offset);


/** \brief Get gyro. offset X
 * 
 * \pre    None
 * \return Offset value
 * 
 * \author André Gradim
 */
int16_t getXGyroOffset();

/** \brief Set gyro. offset X
 * 
 * \pre    None
 * \param offset Offset value
 * \return None
 * 
 * \author André Gradim
 */
void setXGyroOffset(int16_t offset);


/** \brief Get gyro. offset Y
 * 
 * \pre    None
 * \return Offset value
 * 
 * \author André Gradim
 */
int16_t getYGyroOffset();

/** \brief Set gyro. offset X
 * 
 * \pre    None
 * \param offset Offset value
 * \return None
 * 
 * \author André Gradim
 */
void setYGyroOffset(int16_t offset);


/** \brief Get gyro. offset Z
 * 
 * \pre    None
 * \return Offset value
 * 
 * \author André Gradim
 */
int16_t getZGyroOffset();

/** \brief Set gyro. offset Z
 * 
 * \pre    None
 * \param offset Offset value
 * \return None
 * 
 * \author André Gradim
 */
void setZGyroOffset(int16_t offset);







#endif	/* MPU6050_H */

