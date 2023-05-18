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
	int status; /* status of the child process */
	pid_t pid; /* process id of the child */

	while (1) /* main loop */
	{
		write(STDOUT_FILENO, PROMPT, strlen(PROMPT)); /* write the prompt to stdout */
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
		argv[0] = line; /* set the first argument to the command */
		argv[1] = NULL; /* set the second argument to NULL */
		pid = fork(); /* create a new process */
		if (pid < 0) /* error in fork */
		{
			perror("fork"); /* print an error message */
			exit(1); /* exit with status 1 */
		}
		else if (pid == 0) /* child process */
		{
			execve(line, argv, NULL); /* execute the command with no environment variables */
			perror(line); /* print an error message if execve fails */
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
