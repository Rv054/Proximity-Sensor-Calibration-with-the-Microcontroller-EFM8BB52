# Proximity Sensor Calibration with the Microcontroller EFM8BB52

## 1. Project Overview

This project aims to interface the **VL53L1X Time-of-Flight distance sensor** (via the [Proximity 15 Click board by MikroElektronika]) with the **Silicon Labs EFM8BB52** microcontroller. The goal is to measure distances continuously and print the output over a UART terminal. Due to initialization challenges, a fallback experiment was also conducted using the ESP32 microcontroller for comparative analysis.

## 2. System Architecture

- **Sensor**: VL53L1X ToF sensor (Proximity 15 Click)
- **Microcontroller**: EFM8BB52 (8051-based)
- **Interface**: I2C (via SMBus)
- **Output**: UART Terminal (for distance monitoring)

## 3. File Descriptions

### ✅ `main.c`
- Initializes all hardware peripherals via `enter_DefaultMode_from_RESET()`.
- Initializes the VL53L1X sensor using `VL53L1X_Init()` and starts ranging.
- In the main loop:
  - Reads distance using `VL53L1X_ReadDistance()`
  - Prints the result via UART.
- Includes:
  - Delay utility (`delay_ms`)
  - UART printing (`UART_send`, `UART_send_str`, `print_hex_byte`)
  - I2C transfer function `I2C0_transfer(...)`

### ✅ `VL53L1X.h` / `VL53L1X.c`
- Contains a simplified custom driver for the VL53L1X sensor.
- Functions included:
  - Initialization and reset (`VL53L1X_Init`)
  - Ranging control (`VL53L1X_StartRanging`, `VL53L1X_StopRanging`)
  - Distance reading (`VL53L1X_ReadDistance`)
  - Low-level I2C register access
  - Optional distance/timing configuration
- Uses blocking delay and I2C calls for simplicity.

### ✅ `InitDevice.c` / `InitDevice.h`
- Auto-generated via Simplicity Studio Hardware Configurator.
- Sets up:
  - Clock system
  - UART0
  - SMBus (I2C)
  - Port configurations for SDA, SCL, LED, and XSHUT
  - Global interrupts (enabled)

## 4. Flow of Execution

1. **Power-Up**
2. **XSHUT Pin Release (Sensor Wake-Up)**
3. **Sensor Initialization (I2C Reg Read/Write)**
4. **Start Continuous Ranging**
5. **Read Distance Register (0x0096)**
6. **Print Value to UART**
7. **Repeat Every 1s**

## 5. How to Build and Test

1. Clone the project into Simplicity Studio.
2. Ensure the hardware is connected:
   - VL53L1X SCL/SDA ↔ EFM8BB52 P1.6 / P1.5
   - XSHUT connected to P1.3
3. Power and flash the firmware.
4. Open UART terminal (9600 baud) to view results.

## 6. Known Issues

- The EFM8BB52 is able to communicate over I2C (evidenced by valid register reads) but the VL53L1X fails to start proper ranging.
- Sensor gets stuck in boot wait or returns default values (like `0x0024`) despite proper I2C signaling.
- Sensor works as expected on ESP32 using equivalent logic.

## 7. Future Work

- Port same code to a higher-end microcontroller (e.g., ESP32 or STM32).
- Use interrupt-driven SMBus and UART logic.
- Add GUI for real-time display and calibration.

## 8. Dependencies

- Silicon Labs Simplicity Studio
- EFM8BB52 SDK
- Proximity 15 Click hardware (VL53L1X)
