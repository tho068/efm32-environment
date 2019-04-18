################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/Sps30/subdir.mk
-include src/Sensiron/subdir.mk
-include src/NovaSensor/subdir.mk
-include src/Nbiot/subdir.mk
-include src/ModBusRTU/subdir.mk
-include src/Common/subdir.mk
-include src/ATParser/subdir.mk
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
all: efm32-environment.axf

# Tool invocations
efm32-environment.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C++ Linker'
	arm-none-eabi-g++ -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "efm32-environment.ld" --specs=nosys.specs -Xlinker --gc-sections -Xlinker -Map="efm32-environment.map" --specs=nano.specs -u _printf_float -o efm32-environment.axf "./CMSIS/EFM32GG/startup_gcc_efm32gg.o" "./CMSIS/EFM32GG/system_efm32gg.o" "./emlib/bsp_trace.o" "./emlib/em_cmu.o" "./emlib/em_gpio.o" "./emlib/em_i2c.o" "./emlib/em_leuart.o" "./emlib/em_system.o" "./emlib/em_timer.o" "./emlib/em_usart.o" "./emlib/retargetio.o" "./emlib/retargetswo.o" "./src/ATParser/ATParser.o" "./src/Common/timer.o" "./src/ModBusRTU/ModBusRTU.o" "./src/ModBusRTU/ModBusRTUFrame.o" "./src/Nbiot/nbiot.o" "./src/NovaSensor/NovaSensor.o" "./src/Sensiron/SensironCo2.o" "./src/Sps30/Sps30.o" "./src/main.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: efm32-environment.hex'
	arm-none-eabi-objcopy -O ihex "efm32-environment.axf" "efm32-environment.hex"
	@echo ' '

	@echo 'Building bin file: efm32-environment.bin'
	arm-none-eabi-objcopy -O binary "efm32-environment.axf" "efm32-environment.bin"
	@echo ' '

	@echo 'Building s37 file: efm32-environment.s37'
	arm-none-eabi-objcopy -O srec "efm32-environment.axf" "efm32-environment.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "efm32-environment.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(C_DEPS)$(CPP_DEPS) efm32-environment.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
