#ifndef INC_VL53L1X_H_
#define INC_VL53L1X_H_

#include <SI_EFM8BB52_Register_Enums.h>
#include <stdint.h>

// I2C address
#define VL53L1X_DEFAULT_ADDR 0x29

// Default timeout for waiting for sensor data (in milliseconds)
#define VL53L1X_TIMEOUT_MS 500

// Distance modes
#define VL53L1X_DISTANCEMODE_SHORT   1
#define VL53L1X_DISTANCEMODE_MEDIUM  2
#define VL53L1X_DISTANCEMODE_LONG    3

// Public function prototypes
bit VL53L1X_Init(void);
void VL53L1X_StartRanging(void);
void VL53L1X_StopRanging(void);
unsigned int VL53L1X_ReadDistance(void);
bit VL53L1X_SetDistanceMode(unsigned int mode);
bit VL53L1X_SetTimingBudget(unsigned int timing_budget_us);
void VL53L1X_SetROISize(unsigned int width, unsigned int height);
void VL53L1X_SetROICenter(unsigned int spad_number);
unsigned int VL53L1X_GetROICenter(void);
extern bit I2C0_transfer(unsigned int address, unsigned int *write_buf, unsigned int *read_buf, unsigned int write_len, unsigned int read_len);


#endif /* INC_VL53L1X_H_ */
