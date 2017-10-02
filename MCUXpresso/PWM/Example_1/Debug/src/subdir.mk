################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Example_1.cpp \
../src/cr_cpp_config.cpp \
../src/cr_startup_lpc11xx.cpp 

C_SRCS += \
../src/crp.c 

OBJS += \
./src/Example_1.o \
./src/cr_cpp_config.o \
./src/cr_startup_lpc11xx.o \
./src/crp.o 

CPP_DEPS += \
./src/Example_1.d \
./src/cr_cpp_config.d \
./src/cr_startup_lpc11xx.d 

C_DEPS += \
./src/crp.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_CMSIS=CMSIS_CORE_LPC11xx -DCPP_USE_HEAP -D__LPC11XX__ -I"Y:\LPC1114-Tutorial-Examples\MCUXpresso\PWM\CMSIS_CORE_LPC11xx\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_CMSIS=CMSIS_CORE_LPC11xx -DCPP_USE_HEAP -D__LPC11XX__ -I"Y:\LPC1114-Tutorial-Examples\MCUXpresso\PWM\CMSIS_CORE_LPC11xx\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


