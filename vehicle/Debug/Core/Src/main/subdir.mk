################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/main/fn_state.c \
../Core/Src/main/main.c \
../Core/Src/main/variable_cal.c 

OBJS += \
./Core/Src/main/fn_state.o \
./Core/Src/main/main.o \
./Core/Src/main/variable_cal.o 

C_DEPS += \
./Core/Src/main/fn_state.d \
./Core/Src/main/main.d \
./Core/Src/main/variable_cal.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/main/%.o Core/Src/main/%.su Core/Src/main/%.cyclo: ../Core/Src/main/%.c Core/Src/main/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H753xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/ARM/DSP/Inc -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-main

clean-Core-2f-Src-2f-main:
	-$(RM) ./Core/Src/main/fn_state.cyclo ./Core/Src/main/fn_state.d ./Core/Src/main/fn_state.o ./Core/Src/main/fn_state.su ./Core/Src/main/main.cyclo ./Core/Src/main/main.d ./Core/Src/main/main.o ./Core/Src/main/main.su ./Core/Src/main/variable_cal.cyclo ./Core/Src/main/variable_cal.d ./Core/Src/main/variable_cal.o ./Core/Src/main/variable_cal.su

.PHONY: clean-Core-2f-Src-2f-main

