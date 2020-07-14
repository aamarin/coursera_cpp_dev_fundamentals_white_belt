################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/names_and_surnames.cpp 

OBJS += \
./src/names_and_surnames.o 

CPP_DEPS += \
./src/names_and_surnames.d 


# Each subdirectory must supply rules for building sources it contributes
src/names_and_surnames.o: ../src/names_and_surnames.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/names_and_surnames.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


