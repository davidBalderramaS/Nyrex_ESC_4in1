################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Sensor_Handling/ADC.c 

OBJS += \
./Core/Sensor_Handling/ADC.o 

C_DEPS += \
./Core/Sensor_Handling/ADC.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Sensor_Handling/%.o Core/Sensor_Handling/%.su Core/Sensor_Handling/%.cyclo: ../Core/Sensor_Handling/%.c Core/Sensor_Handling/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Sensor_Handling

clean-Core-2f-Sensor_Handling:
	-$(RM) ./Core/Sensor_Handling/ADC.cyclo ./Core/Sensor_Handling/ADC.d ./Core/Sensor_Handling/ADC.o ./Core/Sensor_Handling/ADC.su

.PHONY: clean-Core-2f-Sensor_Handling

