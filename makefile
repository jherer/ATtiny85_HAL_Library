
# Build mode: hardware (HW) or simulation (SIM)
BUILD ?= HW # Hardware build by default

# Simulation toolchain
GCC = gcc
SIM_CONFIG ?= 
TESTBENCH ?= testbench/testbench_default.c

# Hardware toolchain
AVR_GCC = avr-gcc
OBJCOPY	= avr-objcopy
PORT	= COM6	# COM port may change based on USB driver setup or which USB port you use
MCU		= attiny85 # Microcontroller
ISP		= stk500v1 # In-circuit serial programmer method
BAUD	= 19200 # Baudrate
F_CPU	= 16000000UL
# avrdude.config file path
CONF	= C:/Users/joshu/AppData/Local/Arduino15/packages/arduino/tools/avrdude/8.0.0-arduino1/etc/avrdude.conf


# Tell the makefile these are command names, not files
.PHONY: build run clean testbench

BUILD_ROOT	= build
BUILD_DIR	= $(BUILD_ROOT)
SRC_DIRS 	= src/system src/services src/drivers src/hal src/platform
APP_DIR		?= src/examples/app_template # User source

SRCS = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
APP_SRCS += $(wildcard $(APP_DIR)/*.c)

OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)
OBJS += $(patsubst %.c, $(BUILD_DIR)/app/%.o, $(notdir $(APP_SRCS)))
DEPS = $(OBJS:%.o=%.d)

INCFLAGS = -Iinclude
LDFLAGS = # Linker flags
CFLAGS	= \
$(INCFLAGS) \
-DF_CPU=$(F_CPU) \
$(foreach def, $(SIM_CONFIG), -D$(def)) \
-Wall \
-Wno-unused-function \
-Wno-unused-variable \
-Os \
-std=gnu11 \
-MMD -MP \


# ----------------------------
#	HARDWARE BUILD
# ----------------------------
ifeq ($(BUILD), HW)
CC			= $(AVR_GCC) # Avr firmware compiler
CFLAGS		+= -DHW # Hardware compiler flag
BUILD_DIR 	= build/hardware
SRCS		+= src/main_hw.c # Add hardware main to sources

# Location and name for the output .elf and .hex files
TARGET_NAME		= $(BUILD_DIR)/firmware
TARGET_ELF 		= $(TARGET_NAME).elf
TARGET_HEX 		= $(TARGET_NAME).hex

CFLAGS += -mmcu=$(MCU) # Add HW compiler flags
LDFLAGS	+= -mmcu=$(MCU) # Add HW linker flags

 # avrdude flags
AVRDUDE_FLAGS = -p$(MCU) \
-P$(PORT) \
-b$(BAUD) \
-c$(ISP) \
-C$(CONF)

# Flash firmware to microcontroller
run: $(TARGET_HEX) build
	avrdude $(AVRDUDE_FLAGS) -U flash:w:'$<':a

build: $(TARGET_HEX)
$(TARGET_ELF): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(TARGET_HEX): $(TARGET_ELF)
	$(OBJCOPY) -O ihex $< $@

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET_ELF) $(TARGET_HEX)
	rmdir $(SRC_DIRS:%=$(BUILD_DIR)/%)
	rmdir $(BUILD_DIR)/app $(BUILD_DIR)/src
	rmdir $(BUILD_DIR)
	rmdir $(BUILD_ROOT) # Attempt to remove build root if empty
	
endif


# ----------------------------
#	SIMULATION BUILD
# ----------------------------
ifeq ($(BUILD), SIM)
# Toolchain
CC = $(GCC) # Compiler
CFLAGS += -DSIM # Define sim flag ONLY if compiled for sim
BUILD_DIR = build/sim
SRC_DIRS += src/sim
SRCS += src/main_sim.c # Add simulation main to sources
TARGET = $(BUILD_DIR)/sim.exe # Define target as compiled exe output

run: build
	$(TARGET)

# Always recompile testbench
TESTBENCH_OBJ_DIR = $(BUILD_DIR)/testbench
TESTBENCH_OBJ = $(TESTBENCH_OBJ_DIR)/current_testbench.o
OBJS += $(TESTBENCH_OBJ)

testbench:
	mkdir -p "$(TESTBENCH_OBJ_DIR)"
	$(CC) $(CFLAGS) -c $(TESTBENCH) -o $(TESTBENCH_OBJ)

build: testbench $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)
	rmdir $(SRC_DIRS:%=$(BUILD_DIR)/%)
	rmdir $(BUILD_DIR)/app $(BUILD_DIR)/src $(BUILD_DIR)/testbench
	rmdir $(BUILD_DIR)
	rmdir $(BUILD_ROOT) # Attempt to remove build root if empty
	
endif


# Compile source files from framework
$(BUILD_DIR)/%.o: %.c
	mkdir -p "$(dir $@)"
	$(CC) $(CFLAGS) -c $< -o $@

# Compile source files from user app directory
$(BUILD_DIR)/app/%.o: $(APP_DIR)/%.c
	mkdir -p "$(dir $@)"
	$(CC) $(CFLAGS) -c $< -o $@


-include $(DEPS)


