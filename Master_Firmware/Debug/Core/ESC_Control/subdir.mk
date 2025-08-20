################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/ESC_Control/COMP_Loop_Config.c \
../Core/ESC_Control/OpenLoop_Config.c \
../Core/ESC_Control/PWM_To_Drivers.c 

OBJS += \
./Core/ESC_Control/COMP_Loop_Config.o \
./Core/ESC_Control/OpenLoop_Config.o \
./Core/ESC_Control/PWM_To_Drivers.o 

C_DEPS += \
./Core/ESC_Control/COMP_Loop_Config.d \
./Core/ESC_Control/OpenLoop_Config.d \
./Core/ESC_Control/PWM_To_Drivers.d 


# Each subdirectory must supply rules for building sources it contributes
Core/ESC_Control/%.o Core/ESC_Control/%.su Core/ESC_Control/%.cyclo: ../Core/ESC_Control/%.c Core/ESC_Control/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-ESC_Control

clean-Core-2f-ESC_Control:
	-$(RM) ./Core/ESC_Control/COMP_Loop_Config.cyclo ./Core/ESC_Control/COMP_Loop_Config.d ./Core/ESC_Control/COMP_Loop_Config.o ./Core/ESC_Control/COMP_Loop_Config.su ./Core/ESC_Control/OpenLoop_Config.cyclo ./Core/ESC_Control/OpenLoop_Config.d ./Core/ESC_Control/OpenLoop_Config.o ./Core/ESC_Control/OpenLoop_Config.su ./Core/ESC_Control/PWM_To_Drivers.cyclo ./Core/ESC_Control/PWM_To_Drivers.d ./Core/ESC_Control/PWM_To_Drivers.o ./Core/ESC_Control/PWM_To_Drivers.su

.PHONY: clean-Core-2f-ESC_Control

