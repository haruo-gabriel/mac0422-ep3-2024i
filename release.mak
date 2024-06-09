# Define compiler
CC := gcc
LDFLAGS := -lreadline -lm

# Define source files and target executable
SRCS := src/ep3.c src/utils.c src/prompt.c src/comandos.c src/bitmap.c src/fat.c src/arquivo.c
OBJS := $(SRCS:.c=.o)
TARGET := ep3

# Check compilation mode
ifeq ($(MODE),debug)
CFLAGS := -Wall -Wextra -g
else
CFLAGS := -Wall -Wextra
endif

# Default target
all: $(TARGET)

# Rule to compile each source file to an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link the target
$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Rule to run the target
run: $(TARGET)
	./$(TARGET)

# Rule to clean the build
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all run clean