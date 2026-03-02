.PHONY: all run clean

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = Virtual_Machine.exe
SOURCES = Virtual\ Machine.c
OBJECTS = Virtual\ Machine.o

# Default target
all: $(TARGET)

# Build executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Build successful: $(TARGET)"

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean complete"

# Rebuild everything
rebuild: clean all

# Help
help:
	@echo "Virtual Machine Makefile"
	@echo ""
	@echo "Targets:"
	@echo "  make all      - Build the executable (default)"
	@echo "  make run      - Build and run the program"
	@echo "  make clean    - Remove build artifacts"
	@echo "  make rebuild  - Clean and rebuild"
	@echo "  make help     - Show this message"
