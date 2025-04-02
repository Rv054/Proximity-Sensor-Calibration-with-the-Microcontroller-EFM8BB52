// Includes
#include <SI_EFM8BB52_Register_Enums.h>                // SFR declarations
#include <stdio.h>
#include "stdint.h"
//#include "InitDevice.h"
#include "proximity15.h"                   // API for Proximity 15 click sensor

proximity15_t proximity15_dev;
typedef int32_t err_t; // Define err_t

void SiLabs_Startup (void)
{
  // Disable the watchdog here
}

int main (void)
{
  // ... (Your initialization code) ...

  proximity15_cfg_t proximity15_cfg = {
      .scl = 0,  // Replace with actual SCL pin
      .sda = 0,  // Replace with actual SDA pin
      .xsh = 0,  // Replace with actual XSH pin
      .int_pin = 0, // Replace with actual INT pin
      .i2c_speed = 100000,
      .i2c_address = PROXIMITY15_SET_DEV_ADDR
  };

  err_t init_result = proximity15_init(&proximity15_dev, &proximity15_cfg);
  if (init_result != PROXIMITY15_OK) {
      printf("Proximity 15 initialization failed!\n");
      while (1)
        ; // Handle error
  }

  init_result = proximity15_check_communication(&proximity15_dev);
  if (init_result != PROXIMITY15_OK) {
      printf("Proximity 15 communication check failed!\n");
      while (1)
        ; // Handle error
  }

  init_result = proximity15_default_cfg(&proximity15_dev);
  if (init_result != PROXIMITY15_OK) {
      printf("Proximity 15 default config failed!\n");
      while (1)
        ; // Handle error
  }

  proximity15_start_ranging(&proximity15_dev);

  while (1) {
      uint16_t distance;
      err_t result = proximity15_get_distance(&proximity15_dev, &distance);
      if (result == PROXIMITY15_OK) {
          printf("Distance: %d mm\n", distance);
      } else {
          printf("Error reading distance!\n");
      }
      proximity15_clear_interrupt(&proximity15_dev);
      delay_ms(100);
  }
}
