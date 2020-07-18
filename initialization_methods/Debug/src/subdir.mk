################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/initialization_methods.cpp 

OBJS += \
./src/initialization_methods.o 

CPP_DEPS += \
./src/initialization_methods.d 


# Each subdirectory must supply rules for building sources it contributes
src/initialization_methods.o: ../src/initialization_methods.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/initialization_methods.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


