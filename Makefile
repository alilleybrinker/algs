# SPDX-License-Identifier: MIT

INCLUDE_DIR = include
SRC_DIR = src
TARGET_DIR = target
BIN_NAME = test
CC = clang
OBJS_DIR = $(TARGET_DIR)/objs
SRC_FILES = $(wildcard $(SRC_DIR)/*)
HEADER_FILES = $(wildcard $(INCLUDE_DIR)/*)
OBJ_FILES = $(patsubst src/%.c,$(OBJS_DIR)/%.o,$(SRC_FILES))
override CFLAGS += -I$(INCLUDE_DIR) -Wall -Werror -pedantic

# Make the binary.
all: make_target_dir $(TARGET_DIR)/$(BIN_NAME)

# Make and run the test binary.
test: all
	@echo ""
	@./$(TARGET_DIR)/$(BIN_NAME)

# Delete the target directory.
clean:
	rm -r $(TARGET_DIR)/

# Format all source and header files in-place.
fmt:
	clang-format -i $(SRC_FILES) $(HEADER_FILES)

# Check all source and header files with cppcheck.
check:
	cppcheck $(SRC_FILES) $(HEADER_FILES)

# Create the target directory.
make_target_dir:
	mkdir -p $(TARGET_DIR)/
	mkdir -p $(OBJS_DIR)/

# List all targets in this file.
#
# Modified from the excellent source:
# https://stackoverflow.com/a/26339924
list:
	@LC_ALL=C $(MAKE) -pRrq -f $(lastword $(MAKEFILE_LIST)) : 2>/dev/null \
		| awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' \
		| sort \
		| egrep -v -e '^[^[:alnum:]]' -e '^$@$$'

# Compile object files by building their C files.
$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Build the binary with the required object files.
$(TARGET_DIR)/$(BIN_NAME): $(OBJ_FILES)
	$(CC) -o $(TARGET_DIR)/$(BIN_NAME) $(OBJ_FILES)

.PHONY: all test clean fmt check make_target_dir list

