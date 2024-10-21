// shell_helpers.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "shell_helpers.h"

#define MAX_INPUT_LENGTH 1024
#define MAX_HISTORY 20
#define DISPLAY_HISTORY 10
#define HISTORY_FILE "/mnt/c/Users/vedan/OneDrive - International Institute of Information Technology/ADHYAYA 7/Algo OS/Assignment 3/command_history.txt"

char *history[MAX_HISTORY];
int history_count = 0;

void shell_pwd()
{
    char *curr_directory = NULL;
    printf("%s\n", getcwd(curr_directory, MAX_INPUT_LENGTH));
    return;
}

void shell_echo(char *arg_v[], int arg_c)
{
    if (arg_c == 1)
    {
        printf("\n"); // No arguments, just print a newline
    }
    else
    {
        for (int i = 1; i < arg_c; i++)
        {
            // Check if the argument is enclosed in double quotes
            if (arg_v[i][0] == '"')
            {
                // Print the content within quotes
                // Only if there's a closing quote
                if (arg_v[i][strlen(arg_v[i]) - 1] == '"')
                {
                    // Remove quotes and print
                    arg_v[i][strlen(arg_v[i]) - 1] = '\0'; // Null-terminate before the last quote
                    printf("%s", arg_v[i] + 1);            // Print without the opening quote
                }
                else
                {
                    // If no closing quote, print the whole thing
                    printf("%s ", arg_v[i] + 1); // Print without the opening quote
                }
            }
            else
            {
                printf("%s ", arg_v[i]); // Print regular arguments
            }
        }
        printf("\n"); // Print newline at the end
    }
}

void shell_cd(char *path)
{
    char old_dir[MAX_INPUT_LENGTH];
    char new_dir[MAX_INPUT_LENGTH];

    // Save the current directory to 'old_dir' before changing it
    if (getcwd(old_dir, sizeof(old_dir)) == NULL)
    {
        perror("getcwd");
        return;
    }

    const char *home_dir = getenv("HOME");

    if (path == NULL || strcmp(path, "") == 0 || strcmp(path, "~") == 0)
    {
        // Change to home directory if no path or "~" is provided
        if (home_dir != NULL)
        {
            if (chdir(home_dir) != 0)
            {
                perror("cd");
                return;
            }
        }
        else
        {
            fprintf(stderr, "cd: HOME environment variable not set\n");
            return;
        }
    }
    else if (strcmp(path, "-") == 0)
    {
        // Change to the previous directory if "-" is provided
        const char *previous_dir = getenv("OLDPWD");
        if (previous_dir != NULL)
        {
            printf("%s\n", previous_dir); // Print the previous directory
            if (chdir(previous_dir) != 0)
            {
                perror("cd");
                return;
            }
        }
        else
        {
            fprintf(stderr, "cd: OLDPWD environment variable not set\n");
            return;
        }
    }
    else
    {
        // Change to the given directory (including "..")
        if (chdir(path) != 0)
        {
            perror("cd");
            return;
        }
    }

    // After successfully changing the directory, update OLDPWD and PWD
    if (getcwd(new_dir, sizeof(new_dir)) == NULL)
    {
        perror("getcwd");
        return;
    }

    setenv("OLDPWD", old_dir, 1);
    setenv("PWD", new_dir, 1);

    // printf("Changed current working directory to: %s\n", new_dir);
    // printf("Old directory is: %s\n", old_dir);
    return;
}

// Load history from the file
void load_history()
{
    FILE *file = fopen(HISTORY_FILE, "r");
    if (file)
    {
        char buffer[MAX_INPUT_LENGTH];
        while (fgets(buffer, sizeof(buffer), file) && history_count < MAX_HISTORY)
        {
            buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
            history[history_count] = strdup(buffer);
            history_count++;
        }
        fclose(file);
    }
}

// Save history to the file
void save_history()
{
    // Now save the history to the file
    FILE *file = fopen(HISTORY_FILE, "w");
    if (file)
    {
        for (int i = 0; i < history_count; i++)
        {
            fprintf(file, "%s\n", history[i]);
        }
        fclose(file);
    }
}


// Add a command to history
void add_to_history(const char *command)
{
    // Prevent adding the same command as the previous one
    if (history_count > 0 && strcmp(history[history_count - 1], command) == 0)
    {
        return; // Ignore duplicate
    }

    // Add the new command to the history
    if (history_count < MAX_HISTORY)
    {
        history[history_count] = strdup(command);
        history_count++;
    }
    else
    {
        // Overwrite the oldest command
        free(history[0]); // Free the memory for the oldest command
        for (int i = 1; i < MAX_HISTORY; i++)
        {
            history[i - 1] = history[i]; // Shift commands left
        }
        history[MAX_HISTORY - 1] = strdup(command); // Add the new command
    }
}

// Display history
void display_history()
{
    int start = (history_count > DISPLAY_HISTORY) ? history_count - DISPLAY_HISTORY : 0;
    for (int i = start; i < history_count; i++)
    {
        printf("%d %s\n", i + 1, history[i]);
    }
}

const char *getShortenedPath(const char *path)
{
    const char *home = getenv("home");
    if (home != NULL && strncmp(path, home, strlen(home)) == 0)
    {
        return path + strlen(home) + 1; // Skip the / character
    }
    return path; // No change to the path if it's not in the home directory
}

void tokenize(const char *input, char *arg_v[], int *arg_c)
{
    *arg_c = 0;
    char *token = strtok((char *)input, " ");
    while (token != NULL && *arg_c < MAX_INPUT_LENGTH)
    {
        arg_v[(*arg_c)++] = token;
        token = strtok(NULL, " ");
    }
}
