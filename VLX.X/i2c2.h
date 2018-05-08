/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */
#include <xc.h>

void openI2C2();
void closeI2C2();


int startI2C2();
int stopI2C2();
int restartI2C2();

int ackI2C2(int ackType);


int idleI2C2(void);
void waitI2C2(void);

int dataReadyI2C2(void);

uint8_t masterReadI2C2(void);
uint8_t masterWriteI2C2(uint8_t data_out);


void masterSend(uint8_t dev_address, uint8_t* data, uint8_t data_size);


/* *****************************************************************************
 End of File
 */
