# Proximity-Sensor-Calibration-with-the-Microcontroller-EFM8BB52

### 1. Project Overview

This project aims to interface with a MikroElektronika Proximity 15 Click board using a Silicon Labs EFM8BB52 microcontroller. The goal is to initialize the sensor, configure it for continuous distance measurement, read the distance values in millimeters, and output them (currently planned via `printf`). The project utilizes a dedicated driver library (`proximity15.h`, `proximity15.c`) for sensor communication and control.

### 2. File Descriptions

The project consists of the following main files:

* **`proximity15.h` (Header File):**
    * Defines the Application Programming Interface (API) for the Proximity 15 Click driver.
    * Contains definitions for sensor register addresses, constants (like default I2C address, model ID, configuration values), and command values.
    * Declares data structures used by the driver (`proximity15_t` for context, `proximity15_cfg_t` for configuration).
    * Includes enumerations for return values (`proximity15_return_value_t`) and timing budget options (`proximity15_timing_budget_t`).
    * Provides function prototypes for all public functions available to control and interact with the sensor.

* **`proximity15.c` (Implementation File):**
    * Provides the concrete implementation for all functions declared in `proximity15.h`.
    * Contains the low-level logic for communicating with the sensor via I2C, including formatting register addresses and data.
    * Includes a static array (`proximity15_default_config`) holding numerous default register values applied during initialization.
    * Implements sensor control sequences like software reset, enabling/disabling, starting/stopping ranging.
    * Relies on an underlying Hardware Abstraction Layer (HAL) provided by the MikroElektronika environment for I2C (`i2c_master_*`) and GPIO (`digital_out_*`, `digital_in_*`) operations.
    * Requires specific delay functions (`Delay_500us`, `Delay_1sec`) from the platform libraries.

* **`main.c` (Main Application File):**
    * The main entry point (`main` function) for the application running on the EFM8BB52 microcontroller.
    * Includes necessary headers for the microcontroller, standard libraries, and the `proximity15` driver.
    * Demonstrates the basic usage flow of the Proximity 15 driver:
        * Configuring the driver settings (pin connections, I2C speed/address) in a `proximity15_cfg_t` structure. **(Note: Pin connections are currently placeholders)**.
        * Initializing the driver (`proximity15_init`).
        * Verifying communication with the sensor (`proximity15_check_communication`).
        * Applying default sensor settings (`proximity15_default_cfg`).
        * Starting continuous distance ranging (`proximity15_start_ranging`).
        * Entering an infinite loop to periodically read the distance (`proximity15_get_distance`) and print it using `printf`.
    * Includes basic error handling after initialization steps.
    * Requires platform-specific setup for hardware (clocks, peripherals) and `printf` output (e.g., UART).
    * Uses a `delay_ms` function within the main loop.

### 3. Function Descriptions

#### Key Library Functions (`proximity15.h`/`.c`)

* `proximity15_cfg_setup(cfg)`: Initializes the configuration structure (`cfg`) with default values (pins unconnected, standard I2C speed, default address).
* `proximity15_init(ctx, cfg)`: Initializes the I2C communication and GPIO pins based on the `cfg` structure. Requires prior hardware initialization (clocks, I2C peripheral).
* `proximity15_default_cfg(ctx)`: Performs a full default configuration sequence on the sensor (enables, checks comms, resets, writes default registers, sets long mode, 50ms budget, 100ms period, starts ranging, waits for first reading, clears interrupt).
* `proximity15_write_registers(ctx, reg, tx_buf, tx_len)` / `proximity15_read_registers(ctx, reg, rx_buf, rx_len)`: Core functions for writing/reading multiple bytes to/from specific 16-bit sensor register addresses via I2C.
* `proximity15_write_register(ctx, reg, tx_data)` / `proximity15_read_register(ctx, reg, rx_data)`: Convenience functions for single-byte register access.
* `proximity15_check_communication(ctx)`: Reads the sensor's Model ID and Module Type registers and verifies them against expected values.
* `proximity15_software_reset(ctx)`: Performs a software reset sequence on the sensor.
* `proximity15_get_distance(ctx, distance)`: Waits (blocks) for the INT pin to signal data ready, reads the distance value (in mm) from the sensor, stores it in `distance`, and **clears the sensor interrupt internally**.
* `proximity15_enable_sensor(ctx)` / `proximity15_disable_sensor(ctx)`: Controls the sensor's hardware shutdown (XSHUT) pin.
* `proximity15_get_int_pin(ctx)`: Reads the current state of the interrupt pin.
* `proximity15_start_ranging(ctx)` / `proximity15_stop_ranging(ctx)`: Starts or stops the continuous measurement process.
* `proximity15_clear_interrupt(ctx)`: Manually clears the sensor's interrupt flag by writing to a specific register.
* `proximity15_set_inter_measurement_period(ctx, time_ms)`: Configures the time delay between measurements in continuous mode.
* `proximity15_set_distance_mode(ctx, mode)` / `proximity15_get_distance_mode(ctx, mode)`: Sets or gets the ranging mode (Short or Long).
* `proximity15_set_timing_budget(ctx, time)` / `proximity15_get_timing_budget(ctx, time)`: Sets or gets the measurement timing budget (e.g., 15ms, 50ms, 200ms), which affects range and ambient light immunity.

#### Main Application Structure (`main.c`)

* **`main()` function:**
    * Defines the `proximity15_cfg` structure, setting I2C parameters (**needs correct pin definitions**).
    * Calls `proximity15_init`, `proximity15_check_communication`, and `proximity15_default_cfg` sequentially, with error checks.
    * Calls `proximity15_start_ranging`.
    * Enters `while(1)` loop:
        * Calls `proximity15_get_distance` to get the distance measurement (this function blocks until data is ready).
        * Prints the distance via `printf` if successful.
        * Calls `delay_ms(100)` to wait before the next reading attempt.
        * **(Should remove the extra `proximity15_clear_interrupt` call here as it's handled internally by `get_distance`)**

### 4. Remaining Tasks / Next Steps

Before the project can be fully functional and compiled/tested, the following items need to be addressed:

1.  **Pin Mapping:** Update the placeholder `0` values for `scl`, `sda`, `xsh`, and `int_pin` in the `proximity15_cfg` structure within `main.c` to match the actual EFM8BB52 pins connected to the Proximity 15 Click board.
2.  **Hardware Initialization:** Ensure that the EFM8BB52's core systems and peripherals are correctly initialized before `proximity15_init` is called. This typically includes:
    * System clock configuration.
    * GPIO setup (port modes, crossbar configuration if applicable for EFM8).
    * I2C peripheral initialization.
    * UART peripheral initialization (if using `printf` for output).
    *(This might be handled by code generated by tools like Simplicity Studio, potentially within the commented-out `InitDevice.h` or similar platform initialization files).*
3.  **`printf` Retargeting:** Configure the standard output stream (`stdout`) so that `printf` sends data to the desired interface (likely the initialized UART).
4.  **Delay Function Implementation:** Verify that the required delay functions (`Delay_500us`, `Delay_1sec` used in `proximity15.c`, and `delay_ms` used in `main.c`) are available, correctly implemented, and reliable on the EFM8BB52 platform. Ensure consistency if necessary.
5.  **Code Correction:** Remove the redundant call to `proximity15_clear_interrupt(&proximity15_dev);` from the `while(1)` loop in `main.c`.
6.  **Compilation and Debugging:** Compile the code using the appropriate toolchain for the EFM8BB52 and debug its execution on the target hardware.
