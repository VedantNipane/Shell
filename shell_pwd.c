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

void shell_pwd()
{
    char *curr_directory = NULL;
    printf("%s\n", getcwd(curr_directory, MAX_INPUT_LENGTH));
    return;
}
