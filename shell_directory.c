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
