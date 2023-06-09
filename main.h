#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <signal.h>
#include <stddef.h>

#define MAXLINE 1024	  /* maximum length of a command line */
#define PROMPT "$ "	  /* prompt symbol */
#define DELIM " \t\r\n\a" /* delimiters for strtok */
#define PATH_DELIM ":"	  /* delimiters for PATH */
#define READONCE 60	  /*Number of char to read*/

/* function prototypes */
void sigint_handler(int sig);
void parse_line(char *line, char **argv, int *argc);
void execute_command(char *path, char **argv, char *shell_name,
		     int line_number, char **env);
char *get_path_env(char **env);
char *find_path(char *command, char **env);
char *build_full_path(char *dir, char *command);
int file_exists(char *path);
void exit_shell(char *line);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
void print_env(char **env);
int _getchar(void);
ssize_t _getline(char **bufline, size_t *nread, FILE *stdi);
size_t handle_cases(char *line, char **env);
char *_strchr(char *s, char c);
char *_strdup(char *str);
int _isspace(int c);
char *_strndup(char *str, size_t n);
char *_strncpy(char *dest, char *src, int n);
char *_getenv(char *varenv, char **env);
int _strncmp(char *str1, char *str2, size_t n);
size_t _strcspn(char *str, char *reject);
#endif
