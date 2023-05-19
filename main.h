#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAXLINE 1024 /* maximum length of a command line */
#define PROMPT "$ " /* prompt symbol */
#define DELIM " \t\n" /* delimiters for strtok */
#define PATH_DELIM ":" /* delimiters for PATH */
#define READONCE 200 /*Number of char to read*/

/* function prototypes */
void parse_line(char *line, char **argv, int *argc);
void execute_command(char *path, char **argv, char *shell_name,
		int line_number);
char *find_path(char *command);
int file_exists(char *path);
void exit_shell(void);
void print_env(void);
size_t _getchar(void);
ssize_t _getline(char **buffer);
size_t handle_cases(char *line);

#endif
