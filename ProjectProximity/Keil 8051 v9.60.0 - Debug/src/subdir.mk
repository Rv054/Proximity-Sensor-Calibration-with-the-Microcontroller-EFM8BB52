################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
A51_UPPER_SRCS += \
C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/SILABS_STARTUP.A51 

C_SRCS += \
../src/InitDevice.c \
../src/VL53L1X.c \
../src/main.c 

OBJS += \
./src/InitDevice.OBJ \
./src/SILABS_STARTUP.OBJ \
./src/VL53L1X.OBJ \
./src/main.OBJ 


# Each subdirectory must supply rules for building sources it contributes
src/%.OBJ: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/InitDevice.OBJ: C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB52/inc/SI_EFM8BB52_Register_Enums.h C:/Users/User/SimplicityStudio/v5_workspace/6_Testing_I2C/inc/InitDevice.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB52/inc/SI_EFM8BB52_Defs.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h

src/SILABS_STARTUP.OBJ: C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/SILABS_STARTUP.A51 src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Assembler'
	AX51 "@$(patsubst %.OBJ,%.__ia,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/VL53L1X.OBJ: C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB52/inc/SI_EFM8BB52_Register_Enums.h C:/Users/User/SimplicityStudio/v5_workspace/6_Testing_I2C/inc/VL53L1X.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB52/inc/SI_EFM8BB52_Defs.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h

src/main.OBJ: C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB52/inc/SI_EFM8BB52_Register_Enums.h C:/Users/User/SimplicityStudio/v5_workspace/6_Testing_I2C/inc/InitDevice.h C:/Users/User/SimplicityStudio/v5_workspace/6_Testing_I2C/inc/VL53L1X.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB52/inc/SI_EFM8BB52_Defs.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h


