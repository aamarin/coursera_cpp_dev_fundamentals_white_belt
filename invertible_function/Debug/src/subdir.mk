################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/invertible_function.cpp 

OBJS += \
./src/invertible_function.o 

CPP_DEPS += \
./src/invertible_function.d 


# Each subdirectory must supply rules for building sources it contributes
src/invertible_function.o: ../src/invertible_function.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/invertible_function.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


