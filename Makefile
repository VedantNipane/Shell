# Variables
CC = gcc
CFLAGS = -Wall -g  # Use -g for debugging, and -Wall to enable warnings
OBJS = shell.o shell_cd.o shell_directory.o shell_echo.o shell_history.o shell_pwd.o

# Default target
all: shell

# Build the shell program by linking all object files
shell: $(OBJS)
	$(CC) $(CFLAGS) -o shell $(OBJS)

# Compile each source file into an object file
shell.o: shell.c shell_helpers.h
	$(CC) $(CFLAGS) -c shell.c

shell_cd.o: shell_cd.c shell_helpers.h
	$(CC) $(CFLAGS) -c shell_cd.c

shell_directory.o: shell_directory.c shell_helpers.h
	$(CC) $(CFLAGS) -c shell_directory.c

shell_echo.o: shell_echo.c shell_helpers.h
	$(CC) $(CFLAGS) -c shell_echo.c

shell_history.o: shell_history.c shell_helpers.h
	$(CC) $(CFLAGS) -c shell_history.c

shell_pwd.o: shell_pwd.c shell_helpers.h
	$(CC) $(CFLAGS) -c shell_pwd.c

# Clean target to remove compiled files
clean:
	rm -f *.o shell
