#include <SI_EFM8BB52_Register_Enums.h>
#include "VL53L1X.h"

//unsigned int distance;
//unsigned int timeout;
//uint16_t  model_id;

extern idata unsigned char I2C0_BUF_OUT[8];
extern idata unsigned char I2C0_BUF_IN[8];

//static unsigned int fast_osc_frequency;
//static unsigned int osc_calibrate_val;

static void VL53L1X_WriteReg16(unsigned int reg, unsigned int value);
static unsigned int VL53L1X_ReadReg16(unsigned int reg);
static unsigned int VL53L1X_ReadReg(unsigned int reg);
static void VL53L1X_WriteReg(unsigned int reg, unsigned int value);
static void VL53L1X_WriteReg32(uint16_t reg, uint32_t value);
extern bit I2C0_transfer(unsigned int address, unsigned int *write_buf, unsigned int *read_buf, unsigned int write_len, unsigned int read_len);
extern void delay_ms(unsigned int ms);

// Low-level register access functions
static void VL53L1X_WriteReg(unsigned int reg, unsigned int value)
{
    I2C0_BUF_OUT[0] = (reg >> 8) & 0xFF;
    I2C0_BUF_OUT[1] = reg & 0xFF;
    I2C0_BUF_OUT[2] = value;
    I2C0_transfer(VL53L1X_DEFAULT_ADDR << 1, I2C0_BUF_OUT, I2C0_BUF_IN, 3, 0);
}

static unsigned int VL53L1X_ReadReg(unsigned int reg)
{
    I2C0_BUF_OUT[0] = (reg >> 8) & 0xFF;
    I2C0_BUF_OUT[1] = reg & 0xFF;
    I2C0_transfer(VL53L1X_DEFAULT_ADDR << 1, I2C0_BUF_OUT, I2C0_BUF_IN, 2, 1);
    return I2C0_BUF_IN[0];
}

static void VL53L1X_WriteReg16(unsigned int reg, unsigned int value)
{
    I2C0_BUF_OUT[0] = (reg >> 8) & 0xFF;
    I2C0_BUF_OUT[1] = reg & 0xFF;
    I2C0_BUF_OUT[2] = (value >> 8) & 0xFF;
    I2C0_BUF_OUT[3] = value & 0xFF;
    I2C0_transfer(VL53L1X_DEFAULT_ADDR << 1, I2C0_BUF_OUT, I2C0_BUF_IN, 4, 0);
}

static void VL53L1X_WriteReg32(uint16_t reg, uint32_t value)
{
    I2C0_BUF_OUT[0] = (uint8_t)(reg >> 8);   // High byte of register
    I2C0_BUF_OUT[1] = (uint8_t)(reg & 0xFF); // Low byte of register
    I2C0_BUF_OUT[2] = (uint8_t)(value >> 24); // Most significant byte
    I2C0_BUF_OUT[3] = (uint8_t)(value >> 16);
    I2C0_BUF_OUT[4] = (uint8_t)(value >> 8);
    I2C0_BUF_OUT[5] = (uint8_t)(value & 0xFF); // Least significant byte
    I2C0_transfer((VL53L1X_DEFAULT_ADDR << 1), (uint8_t *)I2C0_BUF_OUT, 6, 0);
}

static unsigned int VL53L1X_ReadReg16(unsigned int reg)
{
    I2C0_BUF_OUT[0] = (reg >> 8) & 0xFF;
    I2C0_BUF_OUT[1] = reg & 0xFF;
    I2C0_transfer(VL53L1X_DEFAULT_ADDR << 1, I2C0_BUF_OUT, I2C0_BUF_IN, 2, 2);
    return ((unsigned int)I2C0_BUF_IN[0] << 8) | I2C0_BUF_IN[1];
}

// Public functions
bit VL53L1X_Init(void)
{
    uint16_t model_id;
    uint32_t timeout;

    model_id = VL53L1X_ReadReg16(0x010F);
    if (model_id != 0xEACC)
        return 0;

    VL53L1X_WriteReg(0x0000, 0x00); // Software reset
    delay_ms(100);
    VL53L1X_WriteReg(0x0000, 0x01);
    delay_ms(100);

    // Boot complete check
    timeout = VL53L1X_TIMEOUT_MS;
    //while ((VL53L1X_ReadReg(0x00E5) & 0x01) == 0 && timeout--) ;
    while (!(VL53L1X_ReadReg(0x00E5) & 0x01))
        {
            delay_ms(1);
            if (--timeout == 0)
              return 0;
        }
    // Step 4: Basic configuration (STATIC INIT)
    VL53L1X_WriteReg(0x0891, 0x00); // PAD_I2C_HV__EXTSUP_CONFIG

    // Configure default static settings
    VL53L1X_WriteReg16(0x002D, 0x0A00); // DSS_CONFIG__TARGET_TOTAL_RATE_MCPS = 1024

    VL53L1X_WriteReg(0x00FF, 0x01); // SYSTEM__GROUPED_PARAMETER_HOLD = 1

    // Distance Mode: Long
    VL53L1X_WriteReg(0x0050, 0x0F); // VCSEL_PERIOD_A
    VL53L1X_WriteReg(0x0051, 0x0D); // VCSEL_PERIOD_B
    VL53L1X_WriteReg(0x0072, 0xB8); // VALID_PHASE_HIGH
    VL53L1X_WriteReg(0x005E, 0x0F); // WOI_SD0
    VL53L1X_WriteReg(0x005F, 0x0D); // WOI_SD1
    VL53L1X_WriteReg(0x0060, 14);   // INITIAL_PHASE_SD0
    VL53L1X_WriteReg(0x0061, 14);   // INITIAL_PHASE_SD1

    // Timing Budget: 50ms
    VL53L1X_WriteReg16(0x006E, 0x01C2); // TIMEOUT_MACROP_A
    VL53L1X_WriteReg16(0x006F, 0x01C2); // TIMEOUT_MACROP_B

    // DSS configuration
    VL53L1X_WriteReg(0x0070, 0x01); // DSS_CONFIG__ROI_MODE_CONTROL
    VL53L1X_WriteReg16(0x002E, 0x0800); // DSS_CONFIG__MANUAL_EFFECTIVE_SPADS_SELECT = 2048

    VL53L1X_WriteReg(0x00FF, 0x00); // SYSTEM__GROUPED_PARAMETER_HOLD = 0

    // Final seed configuration
    VL53L1X_WriteReg(0x0064, 0x00); // SYSTEM__SEED_CONFIG

    return 1;
}

void VL53L1X_StartRanging(void)
{
    uint16_t osc_calibrate_val;
    // Intermeasurement period (adjust based on timing budget)
    osc_calibrate_val = VL53L1X_ReadReg16(0x00DE);  // RESULT__OSC_CALIBRATE_VAL

    if (osc_calibrate_val != 0)
    {
        VL53L1X_WriteReg32(0x006C, osc_calibrate_val * 50);  // SYSTEM__INTERMEASUREMENT_PERIOD
    }
    else
    {
        VL53L1X_WriteReg32(0x006C, 50 * 0x800);  // Fallback safe value
    }

    VL53L1X_WriteReg(0x0007, 0x40); // SYSTEM__MODE_START = Continuous Ranging
}

void VL53L1X_StopRanging(void)
{
    VL53L1X_WriteReg(0x0007, 0x00); // SYSTEM__MODE_START = Continuous Ranging
}

unsigned int VL53L1X_ReadDistance(void)
{
    uint16_t model_id;
    uint32_t timeout;
    unsigned int distance;

    timeout = VL53L1X_TIMEOUT_MS;
    while (!(VL53L1X_ReadReg(0x0089) & 0x01) && timeout--) ;

    distance = VL53L1X_ReadReg16(0x0096);
    VL53L1X_WriteReg(0x0086, 0x01); // Clear interrupt

    return distance;
}

bit VL53L1X_SetDistanceMode(unsigned int mode)
{
    switch (mode)
    {
        case VL53L1X_DISTANCEMODE_SHORT:
            VL53L1X_WriteReg(0x0050, 0x07);
            VL53L1X_WriteReg(0x0051, 0x05);
            break;

        case VL53L1X_DISTANCEMODE_MEDIUM:
            VL53L1X_WriteReg(0x0050, 0x0B);
            VL53L1X_WriteReg(0x0051, 0x09);
            break;

        case VL53L1X_DISTANCEMODE_LONG:
            VL53L1X_WriteReg(0x0050, 0x0F);
            VL53L1X_WriteReg(0x0051, 0x0D);
            break;

        default:
            return 0;
    }

    return 1;
}

bit VL53L1X_SetTimingBudget(unsigned int timing_budget_us)
{
    if (timing_budget_us < 20000 || timing_budget_us > 1000000)
        return 0;

    VL53L1X_WriteReg16(0x0004, timing_budget_us);
    return 1;
}

void VL53L1X_SetROISize(unsigned int width, unsigned int height)
{
    width  = (width  > 16) ? 16 : width;
    height = (height > 16) ? 16 : height;
    VL53L1X_WriteReg(0x013E, (height - 1) << 4 | (width - 1));
}

void VL53L1X_SetROICenter(unsigned int spad_number)
{
    VL53L1X_WriteReg(0x013D, spad_number);
}

unsigned int VL53L1X_GetROICenter(void)
{
    return VL53L1X_ReadReg(0x013D);
}
