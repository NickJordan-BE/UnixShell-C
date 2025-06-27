# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g

# Source and output
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TARGET = $(BIN_DIR)/main

# Automatically find .c and .h files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $(TARGET)

# Compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object and binary files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Optional: run the program
run: $(TARGET)
	./$(TARGET)

# Optional: format source code (requires clang-format)
format:
	clang-format -i $(SRC_DIR)/*.c $(INCLUDE_DIR)/*.h

.PHONY: all clean run format
