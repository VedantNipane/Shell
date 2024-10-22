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
#define MAX_HISTORY 20
#define DISPLAY_HISTORY 10
#define HISTORY_FILE "/mnt/c/Users/vedan/OneDrive - International Institute of Information Technology/ADHYAYA 7/Algo OS/Assignment 3/command_history.txt"

char *history[MAX_HISTORY];
int history_count = 0;

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
