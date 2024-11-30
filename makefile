# Toolchain
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

# Flags
CFLAGS = -mcpu=cortex-m4 -mthumb -nostdlib
LDFLAGS = -T src/linker.ld

# Directories
SRCDIR = src
INCDIR = $(SRCDIR)/device files
BUILDDIR = build

# Files
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)
TARGET = $(BUILDDIR)/main.elf

# Rules
.PHONY: all clean flash

all: $(TARGET)

# Build the ELF file
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	$(SIZE) $@

# Compile C source files to object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -I"$(INCDIR)" -c $< -o $@

# Create the build directory if it doesn't exist
$(BUILDDIR):
	mkdir -p $@

# Clean the build directory
clean:
	rm -rf $(BUILDDIR)

# Flash the firmware (optional, using OpenOCD as an example)
flash: $(TARGET)
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program $(TARGET) verify reset exit"
