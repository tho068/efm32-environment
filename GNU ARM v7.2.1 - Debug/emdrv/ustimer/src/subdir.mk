################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../emdrv/ustimer/src/ustimer.c 

OBJS += \
./emdrv/ustimer/src/ustimer.o 

C_DEPS += \
./emdrv/ustimer/src/ustimer.d 


# Each subdirectory must supply rules for building sources it contributes
emdrv/ustimer/src/ustimer.o: ../emdrv/ustimer/src/ustimer.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DEFM32GG990F1024=1' '-DDEBUG=1' -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//platform/CMSIS/Include" -I"C:\Users\Thomas Holden\source\efm32-environment\emdrv\ustimer\config" -I"C:\Users\Thomas Holden\source\efm32-environment\emdrv\common\inc" -I"C:\Users\Thomas Holden\source\efm32-environment\emdrv\ustimer\inc" -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//hardware/kit/common/bsp" -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//platform/emlib/inc" -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//hardware/kit/common/drivers" -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//platform/Device/SiliconLabs/EFM32GG/Include" -I"D:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5//hardware/kit/EFM32GG_STK3700/config" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"emdrv/ustimer/src/ustimer.d" -MT"emdrv/ustimer/src/ustimer.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


