#include "main.h"

/**
 * main - Entry point
 * @argc: count of arguments.
 * @argv: arguments
 *
 * Return: 0 if Success
 */
int main(int argc, char **argv)
{
	char *line = NULL; /* buffer for the command line */
	size_t len = 0; /* length of the buffer */
	ssize_t nread; /* number of bytes read */
	char *args[MAXLINE]; /* array of arguments for execve */
	int arg_count; /* number of arguments */
	char *path; /* full path of the command */
	int line_number = 1;

	(void)argc; /* explicitly indicate that argc is unused */

	while (1) /* main loop */
	{
		/* write the prompt to stdout */
		write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
		nread = getline(&line, &len, stdin); /* read a line from stdin */
		if (nread == -1) /* error or end of file */
		{
			write(STDOUT_FILENO, "\n", 1); /* write a new line to stdout */
			break; /* exit the loop */
		}
		if (line[nread - 1] == '\n') /* remove the trailing newline */
			line[nread - 1] = '\0';
		if (strcmp(line, "exit") == 0) /* exit the shell if the command is exit */
			exit_shell();

		/* print the environment if the command is env */
		if (strcmp(line, "env") == 0)
		{
			print_env(); /* call the print_env function */
			continue; /* skip forking and go to next iteration */
		}
		arg_count = 0; /* initialize the argument count to zero */
		parse_line(line, args, &arg_count);

		path = find_path(args[0]); /* find the full path of the command */
		execute_command(path, args, argv[0], line_number);
		line_number++;
	}
	free(line); /* free the buffer */
	return (0); /* exit with status 0 */
}
/**
 * parse_line - parsing a given line into an array of arguments
 * @line: given string.
 * @argv: arguments.
 * @argc: count of arguments
 */
void parse_line(char *line, char **argv, int *argc)
{
	char *token;

	token = strtok(line, DELIM);/* get the first token from the line*/
	while (token != NULL)/* loop through all tokens*/
	{
		argv[*argc] = token;/* set the argument to the token*/
		(*argc)++;/* increment the argument count*/
		token = strtok(NULL, DELIM);/* get the next token from the line*/
	}
	argv[*argc] = NULL;/* set the second argument to NULL*/
}

/**
 * execute_command - executing a given command
 * @path: path of the command.
 * @argv: arguments.
 * @shell_name: name of the shell.
 * @line_number: number of the line.
 */
void execute_command(char *path, char **argv,
		     char *shell_name, int line_number)
{
	int status;
	pid_t pid;

	if (path == NULL) /* command not found in PATH or invalid */
	{
		/* print an error message to stderr*/
		fprintf(stderr, "%s: %d: %s: not found\n", shell_name, line_number, argv[0]);
		return;
	}

	pid = fork();/* create a new process*/
	if (pid < 0)/* error in fork*/
	{
		perror("fork");/* print an error message*/
		exit(1);/* exit with status 1*/
	}
	else if (pid == 0)/* child process*/
	{
		/* execute the command with no environment variables*/
		execve(path, argv, NULL);
		perror(path);/* print an error message if execve fails*/
		exit(1);/* exit with status 1*/
	}
	else/* parent process*/
	{
		wait(&status);/* wait for the child to terminate*/
	}
}
