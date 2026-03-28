################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Src/adc_drv.c \
../Drivers/Src/gpio_drv.c \
../Drivers/Src/rcc_drv.c \
../Drivers/Src/timer_drv.c \
../Drivers/Src/uart_drv.c 

OBJS += \
./Drivers/Src/adc_drv.o \
./Drivers/Src/gpio_drv.o \
./Drivers/Src/rcc_drv.o \
./Drivers/Src/timer_drv.o \
./Drivers/Src/uart_drv.o 

C_DEPS += \
./Drivers/Src/adc_drv.d \
./Drivers/Src/gpio_drv.d \
./Drivers/Src/rcc_drv.d \
./Drivers/Src/timer_drv.d \
./Drivers/Src/uart_drv.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Src/%.o Drivers/Src/%.su Drivers/Src/%.cyclo: ../Drivers/Src/%.c Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32 -DNUCLEO_F767ZI -DSTM32F7 -DSTM32F767ZITx -DSTM32F767xx -c -I../Inc -I../mcu/Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I"C:/Users/ghrug/STM32CubeIDE/workspace_1.15.0/BearMetal/Drivers/Src" -I"C:/Users/ghrug/STM32CubeIDE/workspace_1.15.0/BearMetal/Drivers/Inc" -I"C:/Users/ghrug/STM32CubeIDE/workspace_1.15.0/BearMetal/BSP/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Src

clean-Drivers-2f-Src:
	-$(RM) ./Drivers/Src/adc_drv.cyclo ./Drivers/Src/adc_drv.d ./Drivers/Src/adc_drv.o ./Drivers/Src/adc_drv.su ./Drivers/Src/gpio_drv.cyclo ./Drivers/Src/gpio_drv.d ./Drivers/Src/gpio_drv.o ./Drivers/Src/gpio_drv.su ./Drivers/Src/rcc_drv.cyclo ./Drivers/Src/rcc_drv.d ./Drivers/Src/rcc_drv.o ./Drivers/Src/rcc_drv.su ./Drivers/Src/timer_drv.cyclo ./Drivers/Src/timer_drv.d ./Drivers/Src/timer_drv.o ./Drivers/Src/timer_drv.su ./Drivers/Src/uart_drv.cyclo ./Drivers/Src/uart_drv.d ./Drivers/Src/uart_drv.o ./Drivers/Src/uart_drv.su

.PHONY: clean-Drivers-2f-Src

