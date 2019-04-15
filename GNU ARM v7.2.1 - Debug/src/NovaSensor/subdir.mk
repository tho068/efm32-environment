################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/NovaSensor/NovaSensor.cpp 

OBJS += \
./src/NovaSensor/NovaSensor.o 

CPP_DEPS += \
./src/NovaSensor/NovaSensor.d 


# Each subdirectory must supply rules for building sources it contributes
src/NovaSensor/NovaSensor.o: ../src/NovaSensor/NovaSensor.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C++ Compiler'
	arm-none-eabi-g++ -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG990F1024=1' -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//platform/CMSIS/Include" -I"C:\Users\Thomas Holden\source\efm32-environment\src\ATParser" -I"C:\Users\Thomas Holden\source\efm32-environment\src\Common" -I"C:\Users\Thomas Holden\source\efm32-environment\src\Nbiot" -I"C:\Users\Thomas Holden\source\efm32-environment\src\NovaSensor" -I"C:\Users\Thomas Holden\source\efm32-environment\src\Sensiron" -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//hardware/kit/common/bsp" -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//platform/emlib/inc" -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//hardware/kit/common/drivers" -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//platform/Device/SiliconLabs/EFM32GG/Include" -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//hardware/kit/EFM32GG_STK3700/config" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"src/NovaSensor/NovaSensor.d" -MT"src/NovaSensor/NovaSensor.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


