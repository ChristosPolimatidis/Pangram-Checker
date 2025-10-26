################################################################
# Makefile for Code Challenge #7: Pangram checker
################################################################

CC = gcc
CFLAGS = -Wall -Werror

# Source files
SRCS = main.c pangram.c

# Object files
OBJS = $(SRCS:.c=.o)

# Output executable
TARGET = pangram_checker

# Default target
all: $(TARGET)

# Link the final program
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lcjson

# Compile each .c into .o
%.o: %.c pangram.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)
