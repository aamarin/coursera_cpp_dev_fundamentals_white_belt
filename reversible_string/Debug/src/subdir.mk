################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/reversible_string.cpp 

OBJS += \
./src/reversible_string.o 

CPP_DEPS += \
./src/reversible_string.d 


# Each subdirectory must supply rules for building sources it contributes
src/reversible_string.o: ../src/reversible_string.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/reversible_string.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


