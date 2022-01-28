
include_dir = include
src_dir = src
target_dir = target
objs_dir = $(target_dir)/objs
bin_name = sorts
CC = clang
CFLAGS=-I$(include_dir)

# Make the binary.
all: make_target_dir $(target_dir)/$(bin_name)

# Make and run the binary.
run: all
	./$(target_dir)/$(bin_name)

# Delete the target directory.
clean:
	rm -r $(target_dir)/

# Create the target directory.
make_target_dir:
	mkdir -p $(target_dir)/
	mkdir -p $(objs_dir)/

# Compile object files by building their C files.
$(objs_dir)/%.o: $(src_dir)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Build the binary with the required object files.
$(target_dir)/$(bin_name): $(objs_dir)/main.o $(objs_dir)/alg_sorts.o
	$(CC) -o $(target_dir)/$(bin_name) $(objs_dir)/main.o $(objs_dir)/alg_sorts.o

.PHONY: make_target_dir all clean run

