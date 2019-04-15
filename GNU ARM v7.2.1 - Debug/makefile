################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
-include CMSIS/EFM32GG/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: NovaPMSensor.axf

# Tool invocations
NovaPMSensor.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C++ Linker'
	arm-none-eabi-g++ -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "NovaPMSensor.ld" --specs=nosys.specs -Xlinker --gc-sections -Xlinker -Map="NovaPMSensor.map" --specs=nano.specs -u _printf_float -o NovaPMSensor.axf "./CMSIS/EFM32GG/startup_gcc_efm32gg.o" "./CMSIS/EFM32GG/system_efm32gg.o" "./emlib/bsp_trace.o" "./emlib/em_cmu.o" "./emlib/em_gpio.o" "./emlib/em_i2c.o" "./emlib/em_leuart.o" "./emlib/em_system.o" "./emlib/em_timer.o" "./emlib/em_usart.o" "./emlib/retargetio.o" "./emlib/retargetswo.o" "./src/ATParser.o" "./src/NovaSensor.o" "./src/SensironCo2.o" "./src/main.o" "./src/nbiot.o" "./src/timer.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: NovaPMSensor.hex'
	arm-none-eabi-objcopy -O ihex "NovaPMSensor.axf" "NovaPMSensor.hex"
	@echo ' '

	@echo 'Building bin file: NovaPMSensor.bin'
	arm-none-eabi-objcopy -O binary "NovaPMSensor.axf" "NovaPMSensor.bin"
	@echo ' '

	@echo 'Building s37 file: NovaPMSensor.s37'
	arm-none-eabi-objcopy -O srec "NovaPMSensor.axf" "NovaPMSensor.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "NovaPMSensor.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(C_DEPS)$(CPP_DEPS) NovaPMSensor.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
