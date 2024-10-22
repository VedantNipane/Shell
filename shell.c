#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include "shell_helpers.h"

#define MAX_INPUT_LENGTH 1024
#define MAX_HISTORY 20
#define DISPLAY_HISTORY 10
#define HISTORY_FILE "/mnt/c/Users/vedan/OneDrive - International Institute of Information Technology/ADHYAYA 7/Algo OS/Assignment 3/command_history.txt"
char original_dir[MAX_INPUT_LENGTH];

int main()
{
    char cwd[MAX_INPUT_LENGTH];
    char hostname[MAX_INPUT_LENGTH];
    char *username = getenv("USER");

    // Load the command history from the file
    load_history();

    // Get the hostname
    if (gethostname(hostname, sizeof(hostname)) != 0)
    {
        perror("gethostname");
        return 1;
    }

    // Infinite loop for the shell
    while (1)
    {
        // Get the current working directory
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            perror("getcwd");
            return 1;
        }

        // Shorten the path if it is the home directory
        const char *lastDir = getShortenedPath(cwd);

        // Print the shell prompt
        printf("<%s@%s:~/%s> ", username, hostname, lastDir);

        char *input = NULL;
        size_t input_length = 0;
        ssize_t characters_read = getline(&input, &input_length, stdin);

        if (characters_read == -1)
        {
            perror("getline");
            free(input);
            exit(1);
        }

        // Remove newline character
        if (characters_read > 0 && input[characters_read - 1] == '\n')
        {
            input[characters_read - 1] = '\0';
        }

        // Check if input is empty (just Enter pressed)
        if (strlen(input) == 0)
        {
            free(input);
            continue;  // Skip processing if no command is entered
        }

        // Allocate and copy input
        char *copy_input = (char *)malloc(strlen(input) + 1);
        strcpy(copy_input, input);

        // Prepare for tokenization
        char *arg_v[MAX_INPUT_LENGTH];
        int arg_c;
        tokenize(input, arg_v, &arg_c);

        // Check if no tokens were found
        if (arg_c == 0)
        {
            free(input);
            free(copy_input);
            continue;  // Skip processing if no arguments are found
        }

        // Add the command to history only if it's not a duplicate and not empty
        if (arg_c > 0)
        {
            if (strcmp(arg_v[0], "history") != 0 || arg_c == 1)
            {
                add_to_history(copy_input); // Save the command to history
            }
        }

        // Check for exit command
        if (strcmp(arg_v[0], "exit") == 0)
        {
            save_history(); // Save history before exiting
            free(input);
            free(copy_input);
            exit(0);
        }

        // Execute built-in commands
        if (strcmp(arg_v[0], "pwd") == 0)
        {
            shell_pwd();
        }
        else if (strcmp(arg_v[0], "echo") == 0)
        {
            shell_echo(arg_v, arg_c);
        }
        else if (strcmp(arg_v[0], "cd") == 0)
        {
            if (arg_c > 2)
            {
                // Error: Too many arguments
                printf("cd: too many arguments\n");
            }
            else
            {
                shell_cd(arg_v[1]); // Execute 'cd' with the argument (which could be NULL)
            }
        }
        else if (strcmp(arg_v[0], "history") == 0)
        {
            display_history(); // Display the history
        }
        else
        {
            // Handle unknown commands
            printf("Command not found: %s\n", arg_v[0]);
        }

        save_history();
        free(input);
        free(copy_input);
    }

    return 0;
}
