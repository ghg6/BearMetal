################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mcu/Src/gpio.c \
../mcu/Src/rcc.c 

OBJS += \
./mcu/Src/gpio.o \
./mcu/Src/rcc.o 

C_DEPS += \
./mcu/Src/gpio.d \
./mcu/Src/rcc.d 


# Each subdirectory must supply rules for building sources it contributes
mcu/Src/%.o mcu/Src/%.su mcu/Src/%.cyclo: ../mcu/Src/%.c mcu/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DSTM32 -DNUCLEO_F767ZI -DSTM32F7 -DSTM32F767xx -c -I../Inc -I../mcu/Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../mcu/Src -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-mcu-2f-Src

clean-mcu-2f-Src:
	-$(RM) ./mcu/Src/gpio.cyclo ./mcu/Src/gpio.d ./mcu/Src/gpio.o ./mcu/Src/gpio.su ./mcu/Src/rcc.cyclo ./mcu/Src/rcc.d ./mcu/Src/rcc.o ./mcu/Src/rcc.su

.PHONY: clean-mcu-2f-Src

