# Define compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -g

# Define source files and target executable
SRCS := ep3.c comandos.c shell.c
TARGET := ep3

# Default target
all: $(TARGET)

# Rule to compile and link the target
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $^ -lreadline -o $@

# Rule to clean the build
clean:
	rm -f $(TARGET)

.PHONY: all clean