################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/clock.c \
../Src/isr.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system.c \
../Src/watchdog.c 

OBJS += \
./Src/clock.o \
./Src/isr.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system.o \
./Src/watchdog.o 

C_DEPS += \
./Src/clock.d \
./Src/isr.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system.d \
./Src/watchdog.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32 -DNUCLEO_F767ZI -DSTM32F7 -DSTM32F767ZITx -DSTM32F767xx -c -I../Inc -I../mcu/Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I"C:/Users/ghrug/STM32CubeIDE/workspace_1.15.0/BearMetal/Drivers/Src" -I"C:/Users/ghrug/STM32CubeIDE/workspace_1.15.0/BearMetal/Drivers/Inc" -I"C:/Users/ghrug/STM32CubeIDE/workspace_1.15.0/BearMetal/BSP/Inc" -I"C:/Users/ghrug/STM32CubeIDE/workspace_1.15.0/BearMetal/Config/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/clock.cyclo ./Src/clock.d ./Src/clock.o ./Src/clock.su ./Src/isr.cyclo ./Src/isr.d ./Src/isr.o ./Src/isr.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system.cyclo ./Src/system.d ./Src/system.o ./Src/system.su ./Src/watchdog.cyclo ./Src/watchdog.d ./Src/watchdog.o ./Src/watchdog.su

.PHONY: clean-Src

