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

.DEFAULT_GOAL:=help

##@ Docs

.PHONY: help
help:  ## Display this help
	@awk 'BEGIN {FS = ":.*##"; printf "\nUsage:\n  make \033[36m\033[0m\n"} /^[a-zA-Z_-]+:.*?##/ { printf "  \033[36m%-10s\033[0m %s\n", $$1, $$2 } /^##@/ { printf "\n\033[1m%s\033[0m\n", substr($$0, 5) } ' $(MAKEFILE_LIST)

##@ Build

.PHONY: all
all: prep $(TARGET_DIR)/$(BIN_NAME)  ## Make the test binary.

.PHONY: test
test: all  ## Make and run the test binary.
	@echo ""
	@./$(TARGET_DIR)/$(BIN_NAME)

.PHONY: prep
prep:  ## Create the target directory.
	mkdir -p $(TARGET_DIR)/
	mkdir -p $(OBJS_DIR)/

##@ Cleanup

.PHONY: fmt
fmt:  ## Format sources in-place.
	clang-format -i $(SRC_FILES) $(HEADER_FILES)

.PHONY: clean
clean:  ## Delete the target directory.
	rm -r $(TARGET_DIR)/

##@ Analysis

.PHONY: check
check:  ## Check sources with cppcheck.
	cppcheck $(SRC_FILES) $(HEADER_FILES)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET_DIR)/$(BIN_NAME): $(OBJ_FILES)
	$(CC) -o $(TARGET_DIR)/$(BIN_NAME) $(OBJ_FILES)

