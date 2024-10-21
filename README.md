# Assignment 3 - Operating Systems and Algorithms

## Topic: Custom Shell Implementation

### Features

- **cd**: Changes the current working directory. Supports both relative and absolute paths, as well as special directories like `~` (home) and `-` (previous directory). Throws an error if more than one argument is provided.
  
- **echo**: Displays text with some formatting capabilities, including support for handling special characters like `"` and `'`.

- **pwd**: Displays the current working directory.

- **history**: Displays the command history. Keeps track of the last 20 commands entered and saves them in a file.

- **exit**: Terminates the shell and saves the history to a file before exiting.

### Functions Implemented:

- `void shell_pwd()`: Prints the current working directory.
- `void shell_echo(char **arg_v, int arg_c)`: Prints arguments passed after the `echo` command.
- `void shell_cd(char *path)`: Changes the current directory to the specified path.
- `void add_to_history(const char *command)`: Adds a command to the history log.
- `void display_history()`: Displays the most recent commands from the history.
- `void load_history()`: Loads previously saved commands from a file into the history.
- `void save_history()`: Saves the command history to a file.
- `const char *getShortenedPath(const char *path)`: Returns a shortened path for display in the shell prompt.
- `void tokenize(const char *input, char **arg_v, int *arg_c)`: Splits the input into tokens for further processing.

### How to Run

1. **Compile and Run via Makefile**:
    ```bash
    make
    ./shell
    ```

2. **Direct Compilation and Execution**:
    ```bash
    gcc -o shell shell.c shell_helpers.c
    ./shell
    ```

### Author
Vedant Liladhar Nipane  
Roll no: 2021102040  
Email: vedant.nipane@students.iiit.ac.in
