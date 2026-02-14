################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Src/gpio.c \
../Src/Src/rcc.c 

OBJS += \
./Src/Src/gpio.o \
./Src/Src/rcc.o 

C_DEPS += \
./Src/Src/gpio.d \
./Src/Src/rcc.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Src/%.o Src/Src/%.su Src/Src/%.cyclo: ../Src/Src/%.c Src/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DSTM32 -DNUCLEO_F767ZI -DSTM32F7 -DSTM32F767xx -c -I../Inc -I../mcu/Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../mcu/Src -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-Src

clean-Src-2f-Src:
	-$(RM) ./Src/Src/gpio.cyclo ./Src/Src/gpio.d ./Src/Src/gpio.o ./Src/Src/gpio.su ./Src/Src/rcc.cyclo ./Src/Src/rcc.d ./Src/Src/rcc.o ./Src/Src/rcc.su

.PHONY: clean-Src-2f-Src

