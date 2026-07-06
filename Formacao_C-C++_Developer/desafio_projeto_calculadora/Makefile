CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Iinclude
LDFLAGS ?=

BUILD_DIR := build
BIN_DIR := bin
TARGET := $(BIN_DIR)/programmer_calc
TEST_TARGET := $(BIN_DIR)/test_calculator

SRC := \
	src/domain/base.c \
	src/domain/calculator.c \
	src/app/programmer_calculator.c \
	src/cli/main.c

LIB_SRC := \
	src/domain/base.c \
	src/domain/calculator.c \
	src/app/programmer_calculator.c

TEST_SRC := tests/test_calculator.c

.PHONY: all clean run test windows dirs

all: $(TARGET)

dirs:
	mkdir -p $(BUILD_DIR) $(BIN_DIR)

$(TARGET): $(SRC) | dirs
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $@

run: $(TARGET)
	./$(TARGET)

$(TEST_TARGET): $(LIB_SRC) $(TEST_SRC) | dirs
	$(CC) $(CFLAGS) $(LIB_SRC) $(TEST_SRC) $(LDFLAGS) -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

windows:
	mkdir -p $(BIN_DIR)
	x86_64-w64-mingw32-gcc $(CFLAGS) $(SRC) $(LDFLAGS) -o $(BIN_DIR)/programmer_calc.exe

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
