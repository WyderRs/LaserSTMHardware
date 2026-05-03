################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/lib/funcG.c \
../Core/lib/g_code.c \
../Core/lib/t_config.c 

OBJS += \
./Core/lib/funcG.o \
./Core/lib/g_code.o \
./Core/lib/t_config.o 

C_DEPS += \
./Core/lib/funcG.d \
./Core/lib/g_code.d \
./Core/lib/t_config.d 


# Each subdirectory must supply rules for building sources it contributes
Core/lib/%.o Core/lib/%.su Core/lib/%.cyclo: ../Core/lib/%.c Core/lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-lib

clean-Core-2f-lib:
	-$(RM) ./Core/lib/funcG.cyclo ./Core/lib/funcG.d ./Core/lib/funcG.o ./Core/lib/funcG.su ./Core/lib/g_code.cyclo ./Core/lib/g_code.d ./Core/lib/g_code.o ./Core/lib/g_code.su ./Core/lib/t_config.cyclo ./Core/lib/t_config.d ./Core/lib/t_config.o ./Core/lib/t_config.su

.PHONY: clean-Core-2f-lib

