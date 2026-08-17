################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/lib/DS18B20.c \
../Core/lib/DriverLib.c \
../Core/lib/LCD2004.c \
../Core/lib/SD.c 

OBJS += \
./Core/lib/DS18B20.o \
./Core/lib/DriverLib.o \
./Core/lib/LCD2004.o \
./Core/lib/SD.o 

C_DEPS += \
./Core/lib/DS18B20.d \
./Core/lib/DriverLib.d \
./Core/lib/LCD2004.d \
./Core/lib/SD.d 


# Each subdirectory must supply rules for building sources it contributes
Core/lib/%.o Core/lib/%.su Core/lib/%.cyclo: ../Core/lib/%.c Core/lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-lib

clean-Core-2f-lib:
	-$(RM) ./Core/lib/DS18B20.cyclo ./Core/lib/DS18B20.d ./Core/lib/DS18B20.o ./Core/lib/DS18B20.su ./Core/lib/DriverLib.cyclo ./Core/lib/DriverLib.d ./Core/lib/DriverLib.o ./Core/lib/DriverLib.su ./Core/lib/LCD2004.cyclo ./Core/lib/LCD2004.d ./Core/lib/LCD2004.o ./Core/lib/LCD2004.su ./Core/lib/SD.cyclo ./Core/lib/SD.d ./Core/lib/SD.o ./Core/lib/SD.su

.PHONY: clean-Core-2f-lib

