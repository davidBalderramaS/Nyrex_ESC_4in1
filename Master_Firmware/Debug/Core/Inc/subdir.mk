################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/stm32g4xx_hal_msp.c \
../Core/Inc/stm32g4xx_it.c \
../Core/Inc/syscalls.c \
../Core/Inc/sysmem.c \
../Core/Inc/system_stm32g4xx.c 

OBJS += \
./Core/Inc/stm32g4xx_hal_msp.o \
./Core/Inc/stm32g4xx_it.o \
./Core/Inc/syscalls.o \
./Core/Inc/sysmem.o \
./Core/Inc/system_stm32g4xx.o 

C_DEPS += \
./Core/Inc/stm32g4xx_hal_msp.d \
./Core/Inc/stm32g4xx_it.d \
./Core/Inc/syscalls.d \
./Core/Inc/sysmem.d \
./Core/Inc/system_stm32g4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/%.o Core/Inc/%.su Core/Inc/%.cyclo: ../Core/Inc/%.c Core/Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc

clean-Core-2f-Inc:
	-$(RM) ./Core/Inc/stm32g4xx_hal_msp.cyclo ./Core/Inc/stm32g4xx_hal_msp.d ./Core/Inc/stm32g4xx_hal_msp.o ./Core/Inc/stm32g4xx_hal_msp.su ./Core/Inc/stm32g4xx_it.cyclo ./Core/Inc/stm32g4xx_it.d ./Core/Inc/stm32g4xx_it.o ./Core/Inc/stm32g4xx_it.su ./Core/Inc/syscalls.cyclo ./Core/Inc/syscalls.d ./Core/Inc/syscalls.o ./Core/Inc/syscalls.su ./Core/Inc/sysmem.cyclo ./Core/Inc/sysmem.d ./Core/Inc/sysmem.o ./Core/Inc/sysmem.su ./Core/Inc/system_stm32g4xx.cyclo ./Core/Inc/system_stm32g4xx.d ./Core/Inc/system_stm32g4xx.o ./Core/Inc/system_stm32g4xx.su

.PHONY: clean-Core-2f-Inc

