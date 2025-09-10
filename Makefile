# Built with assistance of LLM

CC := gcc
CFLAGS := -Wall -Wextra -Iinclude -g
LDFLAGS := -lgvc -lcgraph

SRC_DIR := src
EXAMPLES_DIR := examples
BUILD_DIR := build
BIN_DIR := bin

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
SRC_OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

EXAMPLE_FILES := $(wildcard $(EXAMPLES_DIR)/*.c)
EXAMPLE_NAMES := $(notdir $(basename $(EXAMPLE_FILES)))
EXAMPLE_OBJS := $(patsubst $(EXAMPLES_DIR)/%.c, $(BUILD_DIR)/%.o, $(EXAMPLE_FILES))
EXAMPLE_BINS := $(patsubst %, $(BIN_DIR)/%, $(EXAMPLE_NAMES))

.PHONY: all
all: $(BIN_DIR) $(BUILD_DIR) $(EXAMPLE_BINS)

# Build rule for source object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

# Build rule for example object files
$(BUILD_DIR)/%.o: $(EXAMPLES_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

# Link example executables
$(BIN_DIR)/%: $(BUILD_DIR)/%.o $(SRC_OBJS) | $(BIN_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*.o $(BIN_DIR)/*
