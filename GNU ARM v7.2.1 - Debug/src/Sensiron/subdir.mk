################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Sensiron/SensironCo2.cpp 

OBJS += \
./src/Sensiron/SensironCo2.o 

CPP_DEPS += \
./src/Sensiron/SensironCo2.d 


# Each subdirectory must supply rules for building sources it contributes
src/Sensiron/SensironCo2.o: ../src/Sensiron/SensironCo2.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C++ Compiler'
	arm-none-eabi-g++ -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG990F1024=1' -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/CMSIS/Include" -I"C:\Users\Thomas\SimplicityStudio\v4_workspace\NovaPMSensor\src\ModBusRTU" -I"C:\Users\Thomas\SimplicityStudio\v4_workspace\NovaPMSensor\src\Sps30" -I"C:\Users\Thomas\SimplicityStudio\v4_workspace\NovaPMSensor\src\ATParser" -I"C:\Users\Thomas\SimplicityStudio\v4_workspace\NovaPMSensor\src\Common" -I"C:\Users\Thomas\SimplicityStudio\v4_workspace\NovaPMSensor\src\Nbiot" -I"C:\Users\Thomas\SimplicityStudio\v4_workspace\NovaPMSensor\src\NovaSensor" -I"C:\Users\Thomas\SimplicityStudio\v4_workspace\NovaPMSensor\src\Sensiron" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//hardware/kit/EFM32GG_STK3700/config" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"src/Sensiron/SensironCo2.d" -MT"src/Sensiron/SensironCo2.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


