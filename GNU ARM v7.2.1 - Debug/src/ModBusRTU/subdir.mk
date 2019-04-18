################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ModBusRTU/ModBusRTU.cpp \
../src/ModBusRTU/ModBusRTUFrame.cpp 

OBJS += \
./src/ModBusRTU/ModBusRTU.o \
./src/ModBusRTU/ModBusRTUFrame.o 

CPP_DEPS += \
./src/ModBusRTU/ModBusRTU.d \
./src/ModBusRTU/ModBusRTUFrame.d 


# Each subdirectory must supply rules for building sources it contributes
src/ModBusRTU/ModBusRTU.o: ../src/ModBusRTU/ModBusRTU.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C++ Compiler'
	arm-none-eabi-g++ -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG990F1024=1' -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//platform/CMSIS/Include" -I"C:\Users\Thomas Holden\source\efm32-environment\src\ModBusRTU" -I"C:\Users\Thomas Holden\source\efm32-environment\src\Sps30" -I"C:\Users\Thomas Holden\source\efm32-environment\src\ATParser" -I"C:\Users\Thomas Holden\source\efm32-environment\src\Common" -I"C:\Users\Thomas Holden\source\efm32-environment\src\Nbiot" -I"C:\Users\Thomas Holden\source\efm32-environment\src\NovaSensor" -I"C:\Users\Thomas Holden\source\efm32-environment\src\Sensiron" -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//hardware/kit/common/bsp" -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//platform/emlib/inc" -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//hardware/kit/common/drivers" -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//platform/Device/SiliconLabs/EFM32GG/Include" -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//hardware/kit/EFM32GG_STK3700/config" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"src/ModBusRTU/ModBusRTU.d" -MT"src/ModBusRTU/ModBusRTU.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ModBusRTU/ModBusRTUFrame.o: ../src/ModBusRTU/ModBusRTUFrame.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C++ Compiler'
	arm-none-eabi-g++ -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG990F1024=1' -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//platform/CMSIS/Include" -I"C:\Users\Thomas Holden\source\efm32-environment\src\ModBusRTU" -I"C:\Users\Thomas Holden\source\efm32-environment\src\Sps30" -I"C:\Users\Thomas Holden\source\efm32-environment\src\ATParser" -I"C:\Users\Thomas Holden\source\efm32-environment\src\Common" -I"C:\Users\Thomas Holden\source\efm32-environment\src\Nbiot" -I"C:\Users\Thomas Holden\source\efm32-environment\src\NovaSensor" -I"C:\Users\Thomas Holden\source\efm32-environment\src\Sensiron" -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//hardware/kit/common/bsp" -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//platform/emlib/inc" -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//hardware/kit/common/drivers" -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//platform/Device/SiliconLabs/EFM32GG/Include" -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//hardware/kit/EFM32GG_STK3700/config" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"src/ModBusRTU/ModBusRTUFrame.d" -MT"src/ModBusRTU/ModBusRTUFrame.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


