################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/gcd.cpp 

OBJS += \
./src/gcd.o 

CPP_DEPS += \
./src/gcd.d 


# Each subdirectory must supply rules for building sources it contributes
src/gcd.o: ../src/gcd.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/gcd.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


