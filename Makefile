

INCLUDE_DIR = include
SRC_DIR = src
TARGET_DIR = target
BIN_NAME = sorts
CC = clang
OBJS_DIR = $(TARGET_DIR)/objs
SRC_FILES = $(wildcard $(SRC_DIR)/*)
HEADER_FILES = $(wildcard $(INCLUDE_DIR)/*)
OBJ_FILES = $(patsubst src/%.c,$(OBJS_DIR)/%.o,$(SRC_FILES))
CFLAGS = -I$(INCLUDE_DIR)

# Make the binary.
all: make_target_dir $(TARGET_DIR)/$(BIN_NAME)

# Make and run the binary.
run: all
	@echo ""
	@./$(TARGET_DIR)/$(BIN_NAME)

# Delete the target directory.
clean:
	rm -r $(TARGET_DIR)/

fmt:
	clang-format -i $(SRC_FILES) $(HEADER_FILES)

# Print the variables we care about.
vars:
	@echo $(OBJ_FILES)

# Create the target directory.
make_target_dir:
	mkdir -p $(TARGET_DIR)/
	mkdir -p $(OBJS_DIR)/

# Compile object files by building their C files.
$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Build the binary with the required object files.
$(TARGET_DIR)/$(BIN_NAME): $(OBJ_FILES)
	$(CC) -o $(TARGET_DIR)/$(BIN_NAME) $(OBJ_FILES)

.PHONY: make_target_dir all clean run vars fmt

