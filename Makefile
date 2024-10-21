# Variables
CC = gcc
CFLAGS = -Wall -g # Use -g for debugging, and -Wall to enable warnings
OBJS = shell.o shell_helpers.o

# Default target
all: shell

# Build the shell program
shell: $(OBJS)
	$(CC) -o shell $(OBJS)

# Compile source files into object files
shell.o: shell.c shell_helpers.h
	$(CC) $(CFLAGS) -c shell.c

shell_helpers.o: shell_helpers.c shell_helpers.h
	$(CC) $(CFLAGS) -c shell_helpers.c

# Clean target to remove compiled files
clean:
	rm -f *.o shell
