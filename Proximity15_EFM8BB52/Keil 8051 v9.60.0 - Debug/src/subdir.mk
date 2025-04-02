################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
A51_UPPER_SRCS += \
C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/SILABS_STARTUP.A51 

C_SRCS += \
../src/main.c \
../src/proximity15.c 

OBJS += \
./src/SILABS_STARTUP.OBJ \
./src/main.OBJ \
./src/proximity15.OBJ 


# Each subdirectory must supply rules for building sources it contributes
src/SILABS_STARTUP.OBJ: C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/SILABS_STARTUP.A51 src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Assembler'
	AX51 "@$(patsubst %.OBJ,%.__ia,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/%.OBJ: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/main.OBJ: C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB52/inc/SI_EFM8BB52_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5/developer/toolchains/keil_8051/9.60/INC/STDIO.H C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/Users/User/SimplicityStudio/v5_workspace/Proximity15_EFM8BB52/src/proximity15.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB52/inc/SI_EFM8BB52_Defs.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h

src/proximity15.OBJ: C:/Users/User/SimplicityStudio/v5_workspace/Proximity15_EFM8BB52/src/proximity15.h


