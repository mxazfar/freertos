# Compiler and Tools
CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb -g -nostartfiles
LDFLAGS = -T src/linker.ld

# Include Paths
CFLAGS +=  -I"src" -I"src/device files" -I"src/hal" -I"src/hal/gpio" -I"src/hal/rcc" -I"src/q7seg" -I"src/FreeRTOS/include"

# Directories
SRCDIR = src
BUILDDIR = build

# Source and Object Files
SRCS = $(wildcard $(SRCDIR)/*.c) \
       $(wildcard $(SRCDIR)/device\ files/*.c) \
       $(wildcard $(SRCDIR)/hal/**/*.c) \
	   $(wildcard $(SRCDIR)/q7seg/*.c) \
	   $(wildcard $(SRCDIR)/FreeRTOS/**/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRCS))

# Target Output
TARGET = $(BUILDDIR)/main.elf

# Rules
all: $(TARGET)

# Link all object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

# Compile .c files into .o files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	if exist $(BUILDDIR) rmdir /s /q $(BUILDDIR)

print:
	@echo "SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"