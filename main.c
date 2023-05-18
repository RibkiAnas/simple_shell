#include "main.h"

/**
 * main - Entry point
 *
 * Return: 0 if Success
 */
int main(void)
{
	char *line = NULL; /* buffer for the command line */
	size_t len = 0; /* length of the buffer */
	ssize_t nread; /* number of bytes read */
	char *argv[MAXLINE]; /* array of arguments for execve */
	int argc; /* number of arguments */
	char *token; /* pointer to a token */
	int status; /* status of the child process */
	pid_t pid; /* process id of the child */
	char *path; /* full path of the command */

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
			break;
		argc = 0; /* initialize the argument count to zero */
		token = strtok(line, DELIM); /* get the first token from the line */
		while (token != NULL) /* loop through all tokens */
		{
			argv[argc] = token; /* set the argument to the token */
			argc++; /* increment the argument count */
			token = strtok(NULL, DELIM); /* get the next token from the line */
		}
		argv[argc] = NULL; /* set the second argument to NULL */
		path = find_path(argv[0]); /* find the full path of the command */
		if (path == NULL) /* command not found in PATH or invalid */
		{
			/* print an error message to stderr */
			fprintf(stderr, "%s: command not found\n", argv[0]);
			continue; /* skip forking and go to next iteration */
		}
		pid = fork(); /* create a new process */
		if (pid < 0) /* error in fork */
		{
			perror("fork"); /* print an error message */
			exit(1); /* exit with status 1 */
		}
		else if (pid == 0) /* child process */
		{
			/* execute the command with no environment variables */
			execve(path, argv, NULL);
			perror(path); /* print an error message if execve fails */
			exit(1); /* exit with status 1 */
		}
		else /* parent process */
		{
			wait(&status); /* wait for the child to terminate */
		}
	}
	free(line); /* free the buffer */
	return (0); /* exit with status 0 */
}
