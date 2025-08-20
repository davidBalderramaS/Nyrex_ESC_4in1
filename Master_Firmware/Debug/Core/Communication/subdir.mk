################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Communication/SPI_Config.c \
../Core/Communication/USART1_RX.c \
../Core/Communication/USART_printf.c 

OBJS += \
./Core/Communication/SPI_Config.o \
./Core/Communication/USART1_RX.o \
./Core/Communication/USART_printf.o 

C_DEPS += \
./Core/Communication/SPI_Config.d \
./Core/Communication/USART1_RX.d \
./Core/Communication/USART_printf.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Communication/%.o Core/Communication/%.su Core/Communication/%.cyclo: ../Core/Communication/%.c Core/Communication/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Communication

clean-Core-2f-Communication:
	-$(RM) ./Core/Communication/SPI_Config.cyclo ./Core/Communication/SPI_Config.d ./Core/Communication/SPI_Config.o ./Core/Communication/SPI_Config.su ./Core/Communication/USART1_RX.cyclo ./Core/Communication/USART1_RX.d ./Core/Communication/USART1_RX.o ./Core/Communication/USART1_RX.su ./Core/Communication/USART_printf.cyclo ./Core/Communication/USART_printf.d ./Core/Communication/USART_printf.o ./Core/Communication/USART_printf.su

.PHONY: clean-Core-2f-Communication

