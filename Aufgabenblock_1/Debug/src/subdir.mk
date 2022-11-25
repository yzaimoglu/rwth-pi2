################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Fahrrad.cpp \
../src/Fahrzeug.cpp \
../src/PKW.cpp \
../src/main.cpp 

CPP_DEPS += \
./src/Fahrrad.d \
./src/Fahrzeug.d \
./src/PKW.d \
./src/main.d 

OBJS += \
./src/Fahrrad.o \
./src/Fahrzeug.o \
./src/PKW.o \
./src/main.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Fahrrad.d ./src/Fahrrad.o ./src/Fahrzeug.d ./src/Fahrzeug.o ./src/PKW.d ./src/PKW.o ./src/main.d ./src/main.o

.PHONY: clean-src

