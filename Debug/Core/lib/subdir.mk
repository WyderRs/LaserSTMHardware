################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/lib/LCD1602.c \
../Core/lib/SD.c \
../Core/lib/funcG.c \
../Core/lib/g_code.c \
../Core/lib/machine.c 

OBJS += \
./Core/lib/LCD1602.o \
./Core/lib/SD.o \
./Core/lib/funcG.o \
./Core/lib/g_code.o \
./Core/lib/machine.o 

C_DEPS += \
./Core/lib/LCD1602.d \
./Core/lib/SD.d \
./Core/lib/funcG.d \
./Core/lib/g_code.d \
./Core/lib/machine.d 


# Each subdirectory must supply rules for building sources it contributes
Core/lib/%.o Core/lib/%.su Core/lib/%.cyclo: ../Core/lib/%.c Core/lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-lib

clean-Core-2f-lib:
	-$(RM) ./Core/lib/LCD1602.cyclo ./Core/lib/LCD1602.d ./Core/lib/LCD1602.o ./Core/lib/LCD1602.su ./Core/lib/SD.cyclo ./Core/lib/SD.d ./Core/lib/SD.o ./Core/lib/SD.su ./Core/lib/funcG.cyclo ./Core/lib/funcG.d ./Core/lib/funcG.o ./Core/lib/funcG.su ./Core/lib/g_code.cyclo ./Core/lib/g_code.d ./Core/lib/g_code.o ./Core/lib/g_code.su ./Core/lib/machine.cyclo ./Core/lib/machine.d ./Core/lib/machine.o ./Core/lib/machine.su

.PHONY: clean-Core-2f-lib

