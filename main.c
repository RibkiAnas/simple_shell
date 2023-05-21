#include "main.h"

/**
 * main - Entry point
 * @argc: count of arguments.
 * @argv: arguments
 * @env: the environment arg
 *
 * Return: 0 if Success
 */
int main(int argc, char **argv, char **env)
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
		nread = _getline(&line, &len, stdin); /* read a line from stdin */
		if (nread == -1) /* error or end of file */
		{
			write(STDOUT_FILENO, "\n", 1); /* write a new line to stdout */
			break; /* exit the loop */
		}
		if (line[nread - 1] == '\n') /* remove the trailing newline */
			line[nread - 1] = '\0';

		if (handle_cases(line, env) == 0 || nread == 0)
/*this to make sure that we use one of those commands exept exit ofc*/
			continue;

		arg_count = 0; /* initialize the argument count to zero */
		parse_line(line, args, &arg_count);

		path = find_path(args[0]); /* find the full path of the command */
		execute_command(path, args, argv[0], line_number);
		free(path); /* Free full_path*/
		line_number++;
	}
	free(line); /* free the buffer */
	return (0); /* exit with status 0 */
}
/**
 *handle_cases - this function handle the cases of clear, env and exit commands
 *@line: given string
 * @env: the environment arg
 *Return: 0 if succes
 */
size_t handle_cases(char *line, char **env)
{
	/* exit the shell if the command is exit */
	if (_strcmp(line, "exit") == 0)
		exit_shell(line);

	if (_strcmp(line, "clear") == 0)
	{
		write(STDOUT_FILENO, "\033[2J\033[H", 7);
		/*this line to clear the screen*/
		return (0);
	}
	if (_strcmp(line, "env") == 0)
	{
		/* print the environment if the command is env */
		print_env(env);
		return (0);
	}
	return (1); /*this is a sign that there is no command used*/
}
/**
 * parse_line - parsing a given line into an array of arguments
 * @line: given string.
 * @argv: arguments.
 * @argc: count of arguments
 */
void parse_line(char *line, char **argv, int *argc)
{
	int i = 0; /* index for iterating over the characters in the line string */
	int j = 0; /* index for storing arguments in the argv array */
	int start = -1; /* index of the first character of a token */
	int end = -1; /* index of the last character of a token */

	while (line[i] != '\0')/* iterate over the characters in the line string */
	{
		/* if the current character is not a delimiter */
		if (strchr(DELIM, line[i]) == NULL)
		{
			if (start == -1)/* if start is not set, set it to the current index */
				start = i;
			end = i;/* set end to the current index */
		}
		else
		{
			if (start != -1 && end != -1)/* if start and end are set */
			{
				/* add a null terminator after the last character of the token */
				line[end + 1] = '\0';
				/* store the address of the first character */
				/* of the token in the argv array */
				argv[j++] = &line[start];
				start = -1;/* reset start and end */
				end = -1;
			}
		}
		i++;
	}

	/* if start and end are set after the loop */
	if (start != -1 && end != -1)
	{
		/* add a null terminator after the last character of the token */
		line[end + 1] = '\0';
		/* store the address of the first character */
		/* of the token in the argv array */
		argv[j++] = &line[start];
	}
	*argc = j;
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
	char digit;

	if (path == NULL) /* command not found in PATH or invalid */
	{
		write(STDERR_FILENO, shell_name, _strlen(shell_name));
		write(STDERR_FILENO, ": ", 2);
		if (line_number == 0)
			write(STDERR_FILENO, "0", 1);
		else
		{
			while (line_number > 0)
			{
				digit = (line_number % 10) + '0';
				write(STDERR_FILENO, &digit, 1);
				line_number /= 10;
			}
		}
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, argv[0], _strlen(argv[0]));
		write(STDERR_FILENO, ": not found\n", 12);
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
		execve(path, argv, NULL);/*execute the command with no env variables*/
		perror(path);/* print an error message if execve fails*/
		exit(1);/* exit with status 1*/
	}
	else/* parent process*/
	{
		wait(&status);/* wait for the child to terminate*/
	}
}
