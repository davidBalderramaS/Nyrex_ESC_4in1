################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Back_EMF/COMPx.c 

OBJS += \
./Core/Back_EMF/COMPx.o 

C_DEPS += \
./Core/Back_EMF/COMPx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Back_EMF/%.o Core/Back_EMF/%.su Core/Back_EMF/%.cyclo: ../Core/Back_EMF/%.c Core/Back_EMF/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Back_EMF

clean-Core-2f-Back_EMF:
	-$(RM) ./Core/Back_EMF/COMPx.cyclo ./Core/Back_EMF/COMPx.d ./Core/Back_EMF/COMPx.o ./Core/Back_EMF/COMPx.su

.PHONY: clean-Core-2f-Back_EMF

