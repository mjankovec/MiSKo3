################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/external/ColorSpaces.c \
../Drivers/external/XPT2046_touch.c \
../Drivers/external/lcd.c \
../Drivers/external/lcd_demo.c \
../Drivers/external/lcd_grafika.c \
../Drivers/external/lcd_ili9341.c \
../Drivers/external/lcd_ugui.c \
../Drivers/external/ugui.c 

C_DEPS += \
./Drivers/external/ColorSpaces.d \
./Drivers/external/XPT2046_touch.d \
./Drivers/external/lcd.d \
./Drivers/external/lcd_demo.d \
./Drivers/external/lcd_grafika.d \
./Drivers/external/lcd_ili9341.d \
./Drivers/external/lcd_ugui.d \
./Drivers/external/ugui.d 

OBJS += \
./Drivers/external/ColorSpaces.o \
./Drivers/external/XPT2046_touch.o \
./Drivers/external/lcd.o \
./Drivers/external/lcd_demo.o \
./Drivers/external/lcd_grafika.o \
./Drivers/external/lcd_ili9341.o \
./Drivers/external/lcd_ugui.o \
./Drivers/external/ugui.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/external/%.o Drivers/external/%.su: ../Drivers/external/%.c Drivers/external/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../USB_Device/App -I../USB_Device/Target -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/external/Inc -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-external

clean-Drivers-2f-external:
	-$(RM) ./Drivers/external/ColorSpaces.d ./Drivers/external/ColorSpaces.o ./Drivers/external/ColorSpaces.su ./Drivers/external/XPT2046_touch.d ./Drivers/external/XPT2046_touch.o ./Drivers/external/XPT2046_touch.su ./Drivers/external/lcd.d ./Drivers/external/lcd.o ./Drivers/external/lcd.su ./Drivers/external/lcd_demo.d ./Drivers/external/lcd_demo.o ./Drivers/external/lcd_demo.su ./Drivers/external/lcd_grafika.d ./Drivers/external/lcd_grafika.o ./Drivers/external/lcd_grafika.su ./Drivers/external/lcd_ili9341.d ./Drivers/external/lcd_ili9341.o ./Drivers/external/lcd_ili9341.su ./Drivers/external/lcd_ugui.d ./Drivers/external/lcd_ugui.o ./Drivers/external/lcd_ugui.su ./Drivers/external/ugui.d ./Drivers/external/ugui.o ./Drivers/external/ugui.su

.PHONY: clean-Drivers-2f-external

