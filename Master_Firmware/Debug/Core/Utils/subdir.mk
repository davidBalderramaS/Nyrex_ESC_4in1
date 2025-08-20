################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Utils/Delay_Timer.c \
../Core/Utils/Utils.c 

OBJS += \
./Core/Utils/Delay_Timer.o \
./Core/Utils/Utils.o 

C_DEPS += \
./Core/Utils/Delay_Timer.d \
./Core/Utils/Utils.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Utils/%.o Core/Utils/%.su Core/Utils/%.cyclo: ../Core/Utils/%.c Core/Utils/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Utils

clean-Core-2f-Utils:
	-$(RM) ./Core/Utils/Delay_Timer.cyclo ./Core/Utils/Delay_Timer.d ./Core/Utils/Delay_Timer.o ./Core/Utils/Delay_Timer.su ./Core/Utils/Utils.cyclo ./Core/Utils/Utils.d ./Core/Utils/Utils.o ./Core/Utils/Utils.su

.PHONY: clean-Core-2f-Utils

