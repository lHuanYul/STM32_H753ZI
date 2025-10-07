################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/connectivity/sdmmc/basic.c \
../Core/Src/connectivity/sdmmc/main.c 

OBJS += \
./Core/Src/connectivity/sdmmc/basic.o \
./Core/Src/connectivity/sdmmc/main.o 

C_DEPS += \
./Core/Src/connectivity/sdmmc/basic.d \
./Core/Src/connectivity/sdmmc/main.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/connectivity/sdmmc/%.o Core/Src/connectivity/sdmmc/%.su Core/Src/connectivity/sdmmc/%.cyclo: ../Core/Src/connectivity/sdmmc/%.c Core/Src/connectivity/sdmmc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H753xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/ARM/DSP/Inc -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-connectivity-2f-sdmmc

clean-Core-2f-Src-2f-connectivity-2f-sdmmc:
	-$(RM) ./Core/Src/connectivity/sdmmc/basic.cyclo ./Core/Src/connectivity/sdmmc/basic.d ./Core/Src/connectivity/sdmmc/basic.o ./Core/Src/connectivity/sdmmc/basic.su ./Core/Src/connectivity/sdmmc/main.cyclo ./Core/Src/connectivity/sdmmc/main.d ./Core/Src/connectivity/sdmmc/main.o ./Core/Src/connectivity/sdmmc/main.su

.PHONY: clean-Core-2f-Src-2f-connectivity-2f-sdmmc

