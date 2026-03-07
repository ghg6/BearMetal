################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/Src/rcc_bsp.c \
../BSP/Src/uart_bsp.c 

OBJS += \
./BSP/Src/rcc_bsp.o \
./BSP/Src/uart_bsp.o 

C_DEPS += \
./BSP/Src/rcc_bsp.d \
./BSP/Src/uart_bsp.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/Src/%.o BSP/Src/%.su BSP/Src/%.cyclo: ../BSP/Src/%.c BSP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32 -DNUCLEO_F767ZI -DSTM32F7 -DSTM32F767ZITx -DSTM32F767xx -c -I../Inc -I../mcu/Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I"C:/Users/ghrug/STM32CubeIDE/workspace_1.15.0/BearMetal/Drivers/Src" -I"C:/Users/ghrug/STM32CubeIDE/workspace_1.15.0/BearMetal/Drivers/Inc" -I"C:/Users/ghrug/STM32CubeIDE/workspace_1.15.0/BearMetal/BSP/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-BSP-2f-Src

clean-BSP-2f-Src:
	-$(RM) ./BSP/Src/rcc_bsp.cyclo ./BSP/Src/rcc_bsp.d ./BSP/Src/rcc_bsp.o ./BSP/Src/rcc_bsp.su ./BSP/Src/uart_bsp.cyclo ./BSP/Src/uart_bsp.d ./BSP/Src/uart_bsp.o ./BSP/Src/uart_bsp.su

.PHONY: clean-BSP-2f-Src

