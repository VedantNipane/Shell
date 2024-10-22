// shell_helpers.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "shell_helpers.h"
#include <ctype.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 1024

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

