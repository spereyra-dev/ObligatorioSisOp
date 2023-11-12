# Makefile for YES

# Variable for the C compiler being used
CC = gcc

# Variable for compiler flags
CFLAGS = -Wall -Wextra -g

# Source files (.c files)
CFILES = main.c funcion_first_fit.c funcion_print_bitmap.c funcion_set_or_clear_bits.c create_new_chunk.c my_malloc.c

# Header files (.h files)
HFILES = my_malloc_manager.h

# Object files (.o files)
OBJFILES = $(CFILES:.c=.o)

# Output executable name
OUT = YES

# Main target
$(OUT): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJFILES)

# Rule for generating object files
%.o: %.c $(HFILES)
	$(CC) $(CFLAGS) -c $< -o $@

# Phony target to remove all build files
.PHONY: clean
clean:
	rm -f $(OBJFILES) $(OUT)