################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../myDrivers/hal/rcc/rcc.c 

OBJS += \
./myDrivers/hal/rcc/rcc.o 

C_DEPS += \
./myDrivers/hal/rcc/rcc.d 


# Each subdirectory must supply rules for building sources it contributes
myDrivers/hal/rcc/%.o myDrivers/hal/rcc/%.su myDrivers/hal/rcc/%.cyclo: ../myDrivers/hal/rcc/%.c myDrivers/hal/rcc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/moosa/STM32CubeIDE/workspace_1.17.0/sensors/myDrivers" -I"C:/Users/moosa/STM32CubeIDE/workspace_1.17.0/sensors/myDrivers/q7seg" -I"C:/Users/moosa/STM32CubeIDE/workspace_1.17.0/sensors/myDrivers/hal/rcc" -I"C:/Users/moosa/STM32CubeIDE/workspace_1.17.0/sensors/myDrivers/hal/gpio" -I"C:/Users/moosa/STM32CubeIDE/workspace_1.17.0/sensors/myDrivers/hal" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-myDrivers-2f-hal-2f-rcc

clean-myDrivers-2f-hal-2f-rcc:
	-$(RM) ./myDrivers/hal/rcc/rcc.cyclo ./myDrivers/hal/rcc/rcc.d ./myDrivers/hal/rcc/rcc.o ./myDrivers/hal/rcc/rcc.su

.PHONY: clean-myDrivers-2f-hal-2f-rcc

