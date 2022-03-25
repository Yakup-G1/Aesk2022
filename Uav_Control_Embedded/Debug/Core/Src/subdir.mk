################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/AESK_Data_Pack_lib.c \
../Core/Src/AESK_GL.c \
../Core/Src/AESK_Log_System.c \
../Core/Src/AESK_NRF24.c \
../Core/Src/AESK_Ring_Buffer.c \
../Core/Src/AhrsFilter.c \
../Core/Src/AhrsFilter2.c \
../Core/Src/DSHOT.c \
../Core/Src/FLASH.c \
../Core/Src/Filter.c \
../Core/Src/GPS_UBX.c \
../Core/Src/Hmc5883L.c \
../Core/Src/KalmanImu.c \
../Core/Src/Kumanda.c \
../Core/Src/MS5611.c \
../Core/Src/MotorPowerCalculate.c \
../Core/Src/PID.c \
../Core/Src/PositionControl.c \
../Core/Src/ReadingSensor.c \
../Core/Src/TFMini_S.c \
../Core/Src/TJ_MPU6050.c \
../Core/Src/Uav_Global.c \
../Core/Src/lps22hd.c \
../Core/Src/main.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c 

OBJS += \
./Core/Src/AESK_Data_Pack_lib.o \
./Core/Src/AESK_GL.o \
./Core/Src/AESK_Log_System.o \
./Core/Src/AESK_NRF24.o \
./Core/Src/AESK_Ring_Buffer.o \
./Core/Src/AhrsFilter.o \
./Core/Src/AhrsFilter2.o \
./Core/Src/DSHOT.o \
./Core/Src/FLASH.o \
./Core/Src/Filter.o \
./Core/Src/GPS_UBX.o \
./Core/Src/Hmc5883L.o \
./Core/Src/KalmanImu.o \
./Core/Src/Kumanda.o \
./Core/Src/MS5611.o \
./Core/Src/MotorPowerCalculate.o \
./Core/Src/PID.o \
./Core/Src/PositionControl.o \
./Core/Src/ReadingSensor.o \
./Core/Src/TFMini_S.o \
./Core/Src/TJ_MPU6050.o \
./Core/Src/Uav_Global.o \
./Core/Src/lps22hd.o \
./Core/Src/main.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o 

C_DEPS += \
./Core/Src/AESK_Data_Pack_lib.d \
./Core/Src/AESK_GL.d \
./Core/Src/AESK_Log_System.d \
./Core/Src/AESK_NRF24.d \
./Core/Src/AESK_Ring_Buffer.d \
./Core/Src/AhrsFilter.d \
./Core/Src/AhrsFilter2.d \
./Core/Src/DSHOT.d \
./Core/Src/FLASH.d \
./Core/Src/Filter.d \
./Core/Src/GPS_UBX.d \
./Core/Src/Hmc5883L.d \
./Core/Src/KalmanImu.d \
./Core/Src/Kumanda.d \
./Core/Src/MS5611.d \
./Core/Src/MotorPowerCalculate.d \
./Core/Src/PID.d \
./Core/Src/PositionControl.d \
./Core/Src/ReadingSensor.d \
./Core/Src/TFMini_S.d \
./Core/Src/TJ_MPU6050.d \
./Core/Src/Uav_Global.d \
./Core/Src/lps22hd.d \
./Core/Src/main.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/AESK_Data_Pack_lib.d ./Core/Src/AESK_Data_Pack_lib.o ./Core/Src/AESK_GL.d ./Core/Src/AESK_GL.o ./Core/Src/AESK_Log_System.d ./Core/Src/AESK_Log_System.o ./Core/Src/AESK_NRF24.d ./Core/Src/AESK_NRF24.o ./Core/Src/AESK_Ring_Buffer.d ./Core/Src/AESK_Ring_Buffer.o ./Core/Src/AhrsFilter.d ./Core/Src/AhrsFilter.o ./Core/Src/AhrsFilter2.d ./Core/Src/AhrsFilter2.o ./Core/Src/DSHOT.d ./Core/Src/DSHOT.o ./Core/Src/FLASH.d ./Core/Src/FLASH.o ./Core/Src/Filter.d ./Core/Src/Filter.o ./Core/Src/GPS_UBX.d ./Core/Src/GPS_UBX.o ./Core/Src/Hmc5883L.d ./Core/Src/Hmc5883L.o ./Core/Src/KalmanImu.d ./Core/Src/KalmanImu.o ./Core/Src/Kumanda.d ./Core/Src/Kumanda.o ./Core/Src/MS5611.d ./Core/Src/MS5611.o ./Core/Src/MotorPowerCalculate.d ./Core/Src/MotorPowerCalculate.o ./Core/Src/PID.d ./Core/Src/PID.o ./Core/Src/PositionControl.d ./Core/Src/PositionControl.o ./Core/Src/ReadingSensor.d ./Core/Src/ReadingSensor.o ./Core/Src/TFMini_S.d ./Core/Src/TFMini_S.o ./Core/Src/TJ_MPU6050.d ./Core/Src/TJ_MPU6050.o ./Core/Src/Uav_Global.d ./Core/Src/Uav_Global.o ./Core/Src/lps22hd.d ./Core/Src/lps22hd.o ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o

.PHONY: clean-Core-2f-Src

