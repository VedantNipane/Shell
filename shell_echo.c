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

void shell_echo(char *arg_v[], int arg_c)
{
    if (arg_c == 1)
    {
        printf("\n"); // No arguments, just print a newline
    }
    else
    {
        bool inside_quotes = false; // Flag to track whether we are inside quotes

        for (int i = 1; i < arg_c; i++)
        {
            char *arg = arg_v[i];

            // If an argument starts with a double quote
            if (arg[0] == '"' && !inside_quotes)
            {
                inside_quotes = true;
                printf("%s", arg); // Print the argument as it is
            }
            // If an argument ends with a double quote
            else if (arg[strlen(arg) - 1] == '"' && inside_quotes)
            {
                printf(" %s", arg); // Print the argument
                inside_quotes = false; // We're done with the quoted section
            }
            else if (inside_quotes)
            {
                printf(" %s", arg); // Print the rest of the quoted section
            }
            else
            {
                printf("%s", arg); // Regular argument, print as it is
            }

            // Add a space between arguments (but not after the last one)
            if (i < arg_c - 1)
            {
                printf(" ");
            }
        }

        printf("\n"); // Print newline at the end
    }
}

