################################################################################
# Automatically-generated file. Do not edit!
################################################################################

export WINEDEBUG=-all

# Keil tools exit code 1 is warnings only, so don't treat as an error in make
RC := test $$? -lt 2

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Proximity15_EFM8BB52
BUILD_ARTIFACT_EXTENSION := omf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main-build

# Main-build Target
main-build: Proximity15_EFM8BB52.omf

# Tool invocations
Proximity15_EFM8BB52.omf: echo_path $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: Keil 8051 Linker'
	LX51 "@Proximity15_EFM8BB52.lnp" || $(RC)
	@echo 'Finished building target: $@'

# Change from all upper case to the expected case
	@-mv "PROXIMITY15_EFM8BB52.OMF.CRBUILD" "$@"

# Generate hex file: Proximity15_EFM8BB52.hex
	@Ohx51 "Proximity15_EFM8BB52.omf" "HEXFILE (Proximity15_EFM8BB52.hex)" "H386" 2>&1 >/dev/null

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS) Proximity15_EFM8BB52.omf
	-@echo ' '

.PHONY: all clean dependents main-build

-include ../makefile.targets
# echo the path
echo_path:
	@echo PATH=$$PATH
	@echo ' '

