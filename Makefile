# Makefile for STM32 Projects
#
# John Saenz
#
# Created based off STM32CubeMX Makefiles and
# Kevin Cuzener's Makefile:
# https://github.com/kcuzner/stm32f103c8-blink/blob/master/Makefile
#

# Project Structure
PROJECT = tamagotchi

SOURCE_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
OBJECT_DIR = $(BUILD_DIR)/obj

# CPU
CPU = cortex-m0plus
# FPU (if present)

# Float-abi (if present)


# Tools
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
AR = arm-none-eabi-ar
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size
OBJDUMP = arm-none-eabi-objdump
OCD = openocd

# Sources
C_SRC   = $(wildcard $(SOURCE_DIR)/*.c)
ASM_SRC = $(wildcard $(SOURCE_DIR)/*.s)
C_SRC   += $(wildcard $(SOURCE_DIR)/hardware/*.c)
ASM_SRC += $(wildcard $(SOURCE_DIR)/hardware/*.s)
C_SRC   += $(wildcard $(SOURCE_DIR)/drivers/*.c)
ASM_SRC += $(wildcard $(SOURCE_DIR)/drivers/*.s)

INCLUDE = -I$(INCLUDE_DIR)
LINKER = STM32L010XX_FLASH.ld

# Flags
CPU_FLAGS = -mcpu=$(CPU) -mthumb $(FPU) $(FLOAT_ABI)
DEVICE_FLAG = -DSTM32L010x8
OPTIMIZATION_FLAG = -O2
DEBUG_FLAG = -g

GC_FLAGS = -Wall $(DEBUG_FLAG) $(CPU_FLAGS) $(DEVICE_FLAG) $(OPTIMIZATION_FLAG) -fdata-sections -ffunction-sections -specs=nosys.specs \
				$(INCLUDE)

AS_FLAGS  = -mcpu=$(CPU)
LD_FLAGS  = -T$(LINKER) $(CPU_FLAGS) -Wl,--gc-sections --specs=nosys.specs -static

# Building

OBJECTS = $(addprefix $(OBJECT_DIR)/,$(notdir $(C_SRC:.c=.o)))
OBJECTS += $(addprefix $(OBJECT_DIR)/,$(notdir $(ASM_SRC:.s=.o)))

all: $(BUILD_DIR)/$(PROJECT).elf

flash: $(BUILD_DIR)/$(PROJECT).elf
	$(OCD) -f./openocd/openocd.cfg \
	-f./openocd/flash.cfg

debug: $(BUILD_DIR)/$(PROJECT).elf
	$(OCD) -f./openocd/openocd.cfg \
	-fopenocd/debug.cfg

hex: $(BUILD_DIR)/$(PROJECT).elf
	$(OBJCOPY) -R .stack -O ihex $(BUILD_DIR)/$(PROJECT).elf $(BUILD_DIR)/$(PROJECT).hex

bin: $(BUILD_DIR)/$(PROJECT).elf
	$(OBJCOPY) -R .stack -O binary $(BUILD_DIR)/$(PROJECT).elf $(BUILD_DIR)/$(PROJECT).bin

$(BUILD_DIR)/$(PROJECT).elf: $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(OBJECTS) $(LD_FLAGS) -o $(BUILD_DIR)/$(PROJECT).elf
	$(OBJDUMP) -D $(BUILD_DIR)/$(PROJECT).elf > $(BUILD_DIR)/$(PROJECT).lst
	$(SIZE) $(BUILD_DIR)/$(PROJECT).elf > $(BUILD_DIR)/$(PROJECT)_size.txt

# Compilation

# Root of Source
$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(GC_FLAGS) -c $< -o $@

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.s
	@mkdir -p $(dir $@)
	$(AS) $(AS_FLAGS) -o $@ $<

# Hardware
$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/hardware/%.c
	@mkdir -p $(dir $@)
	$(CC) $(GC_FLAGS) -c $< -o $@

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/hardware/%.s
	@mkdir -p $(dir $@)
	$(AS) $(AS_FLAGS) -o $@ $<

# Drivers
$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/drivers/%.c
	@mkdir -p $(dir $@)
	$(CC) $(GC_FLAGS) -c $< -o $@

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/drivers/%.s
	@mkdir -p $(dir $@)
	$(AS) $(AS_FLAGS) -o $@ $<

