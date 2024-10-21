// shell_helpers.h
#ifndef SHELL_HELPERS_H
#define SHELL_HELPERS_H

void shell_pwd();
void shell_echo(char **arg_v, int arg_c);
void shell_cd(char *path);
void add_to_history(const char *command);
void display_history();
void load_history();
void save_history();
const char *getShortenedPath(const char *path);
void tokenize(const char *input, char **arg_v, int *arg_c);

#endif // SHELL_HELPERS_H
