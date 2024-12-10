## Topic: Custom Shell Implementation

### Features

- **cd**: Changes the current working directory. Supports both relative and absolute paths, as well as special directories like `~` (home) and `-` (previous directory). Throws an error if more than one argument is provided.
  
- **echo**: Displays text with some formatting capabilities, including support for handling special characters like `"` and `'`.

- **pwd**: Displays the current working directory.

- **history**: Displays the command history. Keeps track of the last 20 commands entered and saves them in a file.

- **exit**: Terminates the shell and saves the history to a file before exiting.

### File Structure and Functionality

Here is an overview of the files in this project and their respective roles:

- **`shell.c`**:
  - The main driver of the shell program. It handles input/output, invokes shell commands, and processes user commands.
  
- **`shell_cd.c`**:
  - Contains the function `void shell_cd(char *path)` which changes the current working directory to the specified path.
  
- **`shell_directory.c`**:
  - Implements two key functions:
    - `const char *getShortenedPath(const char *path)`: Returns a shortened version of the current working directory path for display in the shell prompt.
    - `void tokenize(const char *input, char **arg_v, int *arg_c)`: Splits the input command into individual tokens for processing.
  
- **`shell_echo.c`**:
  - Implements the `void shell_echo(char **arg_v, int arg_c)` function, which processes and prints arguments passed after the `echo` command.

- **`shell_history.c`**:
  - Contains the implementation for managing shell history:
    - `void add_to_history(const char *command)`: Adds the entered command to the history log.
    - `void display_history()`: Displays the command history.
    - `void load_history()`: Loads saved commands from a file into the history log when the shell starts.
    - `void save_history()`: Saves the command history to a file when the shell exits.
    
- **`shell_pwd.c`**:
  - Implements the `void shell_pwd()` function which prints the current working directory when the `pwd` command is invoked.

- **`shell_helpers.h`**:
  - The header file containing the declarations of functions used across multiple `.c` files in the project, including:
    - `void shell_cd(char *path)`
    - `void shell_echo(char **arg_v, int arg_c)`
    - `void shell_pwd()`
    - `void add_to_history(const char *command)`
    - `void display_history()`
    - `void load_history()`
    - `void save_history()`
    - `const char *getShortenedPath(const char *path)`
    - `void tokenize(const char *input, char **arg_v, int *arg_c)`

### How to Compile and Run

1. **Using Makefile**:
    ```bash
    make
    ./shell
    ```

2. **Direct Compilation**:
    ```bash
    gcc -o shell shell.c shell_cd.c shell_directory.c shell_echo.c shell_history.c shell_pwd.c
    ./shell
    ```

### Author
Vedant Liladhar Nipane  
Roll No: 2021102040  
Email: vedant.nipane@students.iiit.ac.in
