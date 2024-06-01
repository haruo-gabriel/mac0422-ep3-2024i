# Define compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra
DEBUGFLAGS := -g

# Define source files and target executable
SRCS := src/ep3.c scr/comandos.c src/prompt.c src/utils.c
TARGET := ep3

# Default target
all: $(TARGET)

# Rule to compile and link the target
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $^ -lreadline -o $@

# Rule to compile and link the target with debug information
debug: CFLAGS += $(DEBUGFLAGS)
debug: $(TARGET)
	gdb -x script.gdb ./$(TARGET)

# Rule to run the target
run: $(TARGET)
	./$(TARGET)

# Rule to clean the build
clean:
	rm -f $(TARGET)

.PHONY: all debug run clean