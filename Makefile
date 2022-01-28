
INCLUDE_DIR = include
SRC_DIR = src
TARGET_DIR = target
BIN_NAME = sorts
CC = clang
OBJS_DIR = $(TARGET_DIR)/objs
CFLAGS=-I$(INCLUDE_DIR)

# Make the binary.
all: make_TARGET_DIR $(TARGET_DIR)/$(BIN_NAME)

# Make and run the binary.
run: all
	./$(TARGET_DIR)/$(BIN_NAME)

# Delete the target directory.
clean:
	rm -r $(TARGET_DIR)/

# Create the target directory.
make_TARGET_DIR:
	mkdir -p $(TARGET_DIR)/
	mkdir -p $(OBJS_DIR)/

# Compile object files by building their C files.
$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Build the binary with the required object files.
$(TARGET_DIR)/$(BIN_NAME): $(OBJS_DIR)/main.o $(OBJS_DIR)/alg_sorts.o
	$(CC) -o $(TARGET_DIR)/$(BIN_NAME) $(OBJS_DIR)/main.o $(OBJS_DIR)/alg_sorts.o

.PHONY: make_TARGET_DIR all clean run

