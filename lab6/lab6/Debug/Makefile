################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../Drivers


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../Drivers/adc.c \
../Drivers/can.c \
../Drivers/controls.c \
../Drivers/interrupt.c \
../Drivers/mcp2515.c \
../Drivers/menu.c \
../Drivers/oled.c \
../Drivers/pong.c \
../Drivers/spi.c \
../Drivers/timer.c \
../Drivers/uart.c \
../Drivers/xmem.c \
../lab6.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
Drivers/adc.o \
Drivers/can.o \
Drivers/controls.o \
Drivers/interrupt.o \
Drivers/mcp2515.o \
Drivers/menu.o \
Drivers/oled.o \
Drivers/pong.o \
Drivers/spi.o \
Drivers/timer.o \
Drivers/uart.o \
Drivers/xmem.o \
lab6.o

OBJS_AS_ARGS +=  \
Drivers/adc.o \
Drivers/can.o \
Drivers/controls.o \
Drivers/interrupt.o \
Drivers/mcp2515.o \
Drivers/menu.o \
Drivers/oled.o \
Drivers/pong.o \
Drivers/spi.o \
Drivers/timer.o \
Drivers/uart.o \
Drivers/xmem.o \
lab6.o

C_DEPS +=  \
Drivers/adc.d \
Drivers/can.d \
Drivers/controls.d \
Drivers/interrupt.d \
Drivers/mcp2515.d \
Drivers/menu.d \
Drivers/oled.d \
Drivers/pong.d \
Drivers/spi.d \
Drivers/timer.d \
Drivers/uart.d \
Drivers/xmem.d \
lab6.d

C_DEPS_AS_ARGS +=  \
Drivers/adc.d \
Drivers/can.d \
Drivers/controls.d \
Drivers/interrupt.d \
Drivers/mcp2515.d \
Drivers/menu.d \
Drivers/oled.d \
Drivers/pong.d \
Drivers/spi.d \
Drivers/timer.d \
Drivers/uart.d \
Drivers/xmem.d \
lab6.d

OUTPUT_FILE_PATH +=lab6.elf

OUTPUT_FILE_PATH_AS_ARGS +=lab6.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler



























Drivers/%.o: ../Drivers/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega162 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega162 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="lab6.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega162  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "lab6.elf" "lab6.hex"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "lab6.elf" "lab6.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "lab6.elf" > "lab6.lss"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "lab6.elf" "lab6.srec"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-size.exe" "lab6.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "lab6.elf" "lab6.a" "lab6.hex" "lab6.lss" "lab6.eep" "lab6.map" "lab6.srec" "lab6.usersignatures"
	