################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Fahrausnahme.cpp \
../src/Fahren.cpp \
../src/Fahrrad.cpp \
../src/Fahrzeug.cpp \
../src/Kreuzung.cpp \
../src/Losfahren.cpp \
../src/PKW.cpp \
../src/Parken.cpp \
../src/SimuClient.cpp \
../src/SimuClientSocket.cpp \
../src/Simulationsobjekt.cpp \
../src/Streckenende.cpp \
../src/Verhalten.cpp \
../src/Weg.cpp \
../src/main.cpp 

CPP_DEPS += \
./src/Fahrausnahme.d \
./src/Fahren.d \
./src/Fahrrad.d \
./src/Fahrzeug.d \
./src/Kreuzung.d \
./src/Losfahren.d \
./src/PKW.d \
./src/Parken.d \
./src/SimuClient.d \
./src/SimuClientSocket.d \
./src/Simulationsobjekt.d \
./src/Streckenende.d \
./src/Verhalten.d \
./src/Weg.d \
./src/main.d 

OBJS += \
./src/Fahrausnahme.o \
./src/Fahren.o \
./src/Fahrrad.o \
./src/Fahrzeug.o \
./src/Kreuzung.o \
./src/Losfahren.o \
./src/PKW.o \
./src/Parken.o \
./src/SimuClient.o \
./src/SimuClientSocket.o \
./src/Simulationsobjekt.o \
./src/Streckenende.o \
./src/Verhalten.o \
./src/Weg.o \
./src/main.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I/Users/yagi/boost -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Fahrausnahme.d ./src/Fahrausnahme.o ./src/Fahren.d ./src/Fahren.o ./src/Fahrrad.d ./src/Fahrrad.o ./src/Fahrzeug.d ./src/Fahrzeug.o ./src/Kreuzung.d ./src/Kreuzung.o ./src/Losfahren.d ./src/Losfahren.o ./src/PKW.d ./src/PKW.o ./src/Parken.d ./src/Parken.o ./src/SimuClient.d ./src/SimuClient.o ./src/SimuClientSocket.d ./src/SimuClientSocket.o ./src/Simulationsobjekt.d ./src/Simulationsobjekt.o ./src/Streckenende.d ./src/Streckenende.o ./src/Verhalten.d ./src/Verhalten.o ./src/Weg.d ./src/Weg.o ./src/main.d ./src/main.o

.PHONY: clean-src

